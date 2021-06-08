#include "ameba_soc.h"
#include "opus.h"
#include "opus_types.h"
#include "opus_private.h"
#include <platform/platform_stdlib.h>
#include <fatfs_ext/inc/ff_driver.h>
#include <disk_if/inc/sdcard.h>
#include "opus_encode_decode.h"


static SP_OBJ sp_obj;
static SP_InitTypeDef SP_InitStruct;
static SP_GDMA_STRUCT SPGdmaStruct;
static SP_TX_INFO sp_tx_info;

//The size of this buffer should be multiples of 32 and its head address should align to 32
//to prevent problems that may occur when CPU and DMA access this area simultaneously.
static u8 sp_tx_buf[SP_DMA_PAGE_SIZE * SP_DMA_PAGE_NUM]__attribute__((aligned(32)));
static u8 sp_zero_buf[SP_ZERO_BUF_SIZE]__attribute__((aligned(32)));

/*
static void int_to_char(opus_uint16 i, unsigned char ch[2])
{
    ch[0] = (i>>8)&0xFF;
    ch[1] = i&0xFF;
}
*/


static void int_to_char(opus_uint32 i, unsigned char ch[4])
{
	ch[0] = i >> 24;
	ch[1] = (i >> 16) & 0xFF;
	ch[2] = (i >> 8) & 0xFF;
	ch[3] = i & 0xFF;
}


static opus_uint32 char_to_int(unsigned char ch[4])
{
	return ((opus_uint32)ch[0] << 24) | ((opus_uint32)ch[1] << 16)
		   | ((opus_uint32)ch[2] << 8) | (opus_uint32)ch[3];
}

static u8 *sp_get_free_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);

	if (ptx_block->tx_gdma_own) {
		return NULL;
	} else {
		return (u8 *)ptx_block->tx_addr;
	}
}

static void sp_write_tx_page(u8 *src, u32 length)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);

	memcpy((void *)ptx_block->tx_addr, src, length);
	ptx_block-> tx_gdma_own = 1;
	ptx_block -> tx_length = length;
	sp_tx_info.tx_usr_cnt++;
	if (sp_tx_info.tx_usr_cnt == SP_DMA_PAGE_NUM) {
		sp_tx_info.tx_usr_cnt = 0;
	}
}

static void sp_release_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);

	if (sp_tx_info.tx_empty_flag) {
	} else {
		ptx_block->tx_gdma_own = 0;
		sp_tx_info.tx_gdma_cnt++;
		if (sp_tx_info.tx_gdma_cnt == SP_DMA_PAGE_NUM) {
			sp_tx_info.tx_gdma_cnt = 0;
		}
	}
}

static u8 *sp_get_ready_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);

	if (ptx_block->tx_gdma_own) {
		sp_tx_info.tx_empty_flag = 0;
		return (u8 *)ptx_block->tx_addr;
	} else {
		sp_tx_info.tx_empty_flag = 1;
		return (u8 *)sp_tx_info.tx_zero_block.tx_addr;	//for audio buffer empty case
	}
}

static u32 sp_get_ready_tx_length(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);

	if (sp_tx_info.tx_empty_flag) {
		return sp_tx_info.tx_zero_block.tx_length;
	} else {
		return ptx_block->tx_length;
	}
}


static void sp_tx_complete(void *Data)
{
	SP_GDMA_STRUCT *gs = (SP_GDMA_STRUCT *) Data;
	PGDMA_InitTypeDef GDMA_InitStruct;
	u32 tx_addr;
	u32 tx_length;

	GDMA_InitStruct = &(gs->SpTxGdmaInitStruct);

	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);

	sp_release_tx_page();
	tx_addr = (u32)sp_get_ready_tx_page();
	tx_length = sp_get_ready_tx_length();

	//GDMA_SetSrcAddr(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_addr);
	//GDMA_SetBlkSize(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_length>>2);
	//GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, ENABLE);
	AUDIO_SP_TXGDMA_Restart(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_addr, tx_length);
}



static void sp_init_hal(pSP_OBJ psp_obj)
{
	u32 div;
	PLL_I2S_Set(ENABLE);		//enable 98.304MHz PLL. needed if fs=8k/16k/32k/48k/96k
	PLL_PCM_Set(ENABLE);		//enable 45.1584MHz PLL. needed if fs=44.1k/8.2k
	PLL_Sel(PLL_I2S);
	RCC_PeriphClockCmd(APBPeriph_AUDIOC, APBPeriph_AUDIOC_CLOCK, ENABLE);
	RCC_PeriphClockCmd(APBPeriph_SPORT, APBPeriph_SPORT_CLOCK, ENABLE);
	//set clock divider to gen clock sample_rate*256 from 98.304M.
	switch (psp_obj->sample_rate) {
	case SR_48K:
		div = 8;
		break;
	case SR_96K:
		div = 4;
		break;
	case SR_32K:
		div = 12;
		break;
	case SR_16K:
		div = 24;
		break;
	case SR_8K:
		div = 48;
		break;
	case SR_44P1K:
		div = 4;
		PLL_Sel(PLL_PCM);
		break;
	default:
		DBG_8195A("sample rate not supported!!\n");
		break;
	}
	PLL_Div(div);
	/*codec init*/
	CODEC_Init(psp_obj->sample_rate, psp_obj->word_len, psp_obj->mono_stereo, psp_obj->direction);
	CODEC_SetVolume(0xAF, 0xAF);
}

static void sp_init_tx_variables(void)
{
	int i;

	for (i = 0; i < SP_ZERO_BUF_SIZE; i++) {
		sp_zero_buf[i] = 0;
	}
	sp_tx_info.tx_zero_block.tx_addr = (u32)sp_zero_buf;
	sp_tx_info.tx_zero_block.tx_length = (u32)SP_ZERO_BUF_SIZE;

	sp_tx_info.tx_gdma_cnt = 0;
	sp_tx_info.tx_usr_cnt = 0;
	sp_tx_info.tx_empty_flag = 0;

	for (i = 0; i < SP_DMA_PAGE_NUM; i++) {
		sp_tx_info.tx_block[i].tx_gdma_own = 0;
		sp_tx_info.tx_block[i].tx_addr = (u32)sp_tx_buf + i * SP_DMA_PAGE_SIZE;
		sp_tx_info.tx_block[i].tx_length = SP_DMA_PAGE_SIZE;
	}
}


void opus_decode_func(char *filename)
{
	int drv_num = 0;
	int frame_size = 0;
	u32 read_length = 0;
	FRESULT res;
	FATFS 	m_fs;
	FIL		m_file;
	char	logical_drv[4]; //root diretor
	char abs_path[32]; //Path to inp
	short input[100];
	short output[1000];
	int *ptx_buf;
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
	if (drv_num < 0) {
		printf("Rigester disk driver to FATFS fail.\n");
		return;
	} else {
		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}
	if (f_mount(&m_fs, logical_drv, 1) != FR_OK) {
		printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
	}
	memset(abs_path, 0x00, sizeof(abs_path));
	strcpy(abs_path, logical_drv);
	sprintf(&abs_path[strlen(abs_path)], "%s", filename);
	//Open source file
	res = f_open(&m_file, abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file
	if (res != FR_OK) {
		printf("Open source file %s fail.\n", filename);
	}
	int error;
	OpusDecoder *dec;
	dec = opus_decoder_create(16000, 1, &error);

	sp_obj.sample_rate = SR_16K;
	sp_obj.word_len = WL_16;
	sp_obj.mono_stereo = CH_MONO;
	sp_obj.direction = APP_LINE_OUT;

	pSP_OBJ psp_obj = &sp_obj;
	sp_init_hal(psp_obj);

	sp_init_tx_variables();

	/*configure Sport according to the parameters*/
	AUDIO_SP_StructInit(&SP_InitStruct);
	SP_InitStruct.SP_MonoStereo = psp_obj->mono_stereo;
	SP_InitStruct.SP_WordLen = psp_obj->word_len;

	AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);

	AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
	AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);

	u32 tx_addr = (u32)sp_get_ready_tx_page();
	u32 tx_length = sp_get_ready_tx_length();
	AUDIO_SP_TXGDMA_Init(0, &SPGdmaStruct.SpTxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_tx_complete, (u8 *)tx_addr, tx_length);


	printf("decode start \n");
	for (;;) {
		unsigned char ch[4];
		int pcm_length, len;
		res = f_read(&m_file, ch, 4, (UINT *)&read_length);
		if (read_length < 4) {
			printf("read error 1\n");
			break;
		}

		len = char_to_int(ch);

		//read 4 more bytes as enc_final_range
		res = f_read(&m_file, ch, 4, (UINT *)&read_length);
		if (read_length < 4) {
			printf("read error 1\n");
			break;
		}

		res = f_read(&m_file, input, len, (UINT *)&read_length);
		if (read_length != len) {
			printf("read error 3\n");
			break;
		}

		pcm_length = opus_decode(dec, input, len, output, 1920, 0);

		//play audio data
retry:
		ptx_buf = (int *)sp_get_free_tx_page();
		if (ptx_buf) {
			sp_write_tx_page((void *)output, pcm_length * 2);
		} else {
			vTaskDelay(1);
			goto retry;
		}
	}
	//close resources and unmount peripherals
	res = f_close(&m_file);
	if (res) {
		printf("close file (%s) fail.\n", filename);
	}


	if (f_mount(NULL, logical_drv, 1) != FR_OK) {
		printf("FATFS unmount logical drive fail.\n");
	}


	if (FATFS_UnRegisterDiskDriver(drv_num)) {
		printf("Unregister disk driver from FATFS fail.\n");
	}

	AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, DISABLE);
	AUDIO_SP_TxStart(AUDIO_SPORT_DEV, DISABLE);
	GDMA_ClearINT(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum);
	GDMA_Cmd(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum, DISABLE);
	GDMA_ChnlFree(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum);

	opus_decoder_destroy(dec);

}

void opus_encode_func(char *sourcefile, char *dstfile)
{
	int drv_num;
	char logical_drv[4];
	FIL m_file, m_file1;
	char abs_path[32], abs_path1[32];
	FRESULT res, res1;
	FATFS m_fs;
	u32 enc_final_range = 0;
	//define variables related to opus encoding process
	int error, len, range;
	OpusEncoder *enc;

	//create an opus encoder
	enc = opus_encoder_create(16000, 1, OPUS_APPLICATION_AUDIO, &error);
	//refer to the document for more customized settings
	opus_encoder_ctl(enc, OPUS_SET_BITRATE(64000));
	opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(3));
	opus_encoder_ctl(enc, OPUS_SET_VBR(0));

	//prepare for reading SD card
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);

	if (drv_num < 0) {
		printf("Rigester disk driver to FATFS fail.\n");
		return ;
	} else {
		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}

	if (f_mount(&m_fs, logical_drv, 1) != FR_OK) {
		printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
	}

	//for reading file
	memset(abs_path, 0x00, sizeof(abs_path));
	strcpy(abs_path, logical_drv);
	sprintf(&abs_path[strlen(abs_path)], "%s", sourcefile);
	res = f_open(&m_file, abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file

	//for writing file
	memset(abs_path1, 0x00, sizeof(abs_path1));
	strcpy(abs_path1, logical_drv);
	sprintf(&abs_path1[strlen(abs_path1)], "%s", dstfile);
	res1 = f_open(&m_file1, abs_path1, FA_OPEN_ALWAYS | FA_READ | FA_WRITE | FA_CREATE_ALWAYS);

	printf("encode start\n");
	int tim1 = 0;
	int tim2 = 0;
	int tim_total = 0;
	while (1) {
		int byte_count = 0;
		int read_res;
		short buf[160];
		short output_packet[80];
		unsigned char int_field[4];

		//read pcm data
		read_res = f_read(&m_file, (void *)buf, sizeof(short) * 160, &byte_count);
		if (byte_count < sizeof(short) * 160) {
			break;
		}
		tim1 = RTIM_GetCount(TIM0);
		len = opus_encode(enc, buf, 160, output_packet, 80);
		opus_encoder_ctl(enc, OPUS_GET_FINAL_RANGE(&enc_final_range));
		tim2 = RTIM_GetCount(TIM0);
		tim_total += (tim2 - tim1) * 32;
		u32 bw;
		int file_write_res;

		//the first 4 bytes means the framesize
		int_to_char(len, int_field);

		file_write_res = f_write(&m_file1, int_field, 4, &bw);

		if (file_write_res || (bw != 4)) {
			printf("Write error 1.\n");
		}

		int_to_char(enc_final_range, int_field);
		file_write_res = f_write(&m_file1, int_field, 4, &bw);

		//write data to SD card
		file_write_res = f_write(&m_file1, output_packet, len, &bw);

		if (file_write_res || (bw != len)) {
			printf("Write error 3.\n");
		}
	}
	printf("encode end\n");
	//printf("time total is %d\n", tim_total/1000000);
	printf("time total is %d\n", tim_total);

	//close resources and unmount SD card
	f_close(&m_file);
	f_close(&m_file1);

	if (f_mount(NULL, logical_drv, 1) != FR_OK) {
		printf("FATFS unmount logical drive fail.\n");
	}

	if (FATFS_UnRegisterDiskDriver(drv_num)) {
		printf("Unregister disk driver from FATFS fail.\n");
	}
}


void opus_decode_test()
{
	opus_decode_func("1k_standard_1ch.opus");
}


void opus_encode_test()
{
	opus_encode_func("1k_standard_1ch_16k.pcm", "1k_standard_1ch.opus");
}

void opus_test_thread()
{
	printf("opus encode decode example\n");
	opus_encode_test();
	opus_decode_test();
	vTaskDelete(NULL);
}

void example_audio_opus()
{
	RTIM_Cmd(TIM0, ENABLE);
	if (xTaskCreate(opus_test_thread, ((const char *)"opus_test_thread"), 4000,  NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\n\r%s xTaskCreate(opus_test_thread) failed", __FUNCTION__);
	}
}
