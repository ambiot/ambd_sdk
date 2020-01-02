#include "example_audio_amr.h"
#include <platform/platform_stdlib.h>
#include "platform_opts.h"
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>
#include <disk_if/inc/sdcard.h>
#include "section_config.h"
#include "rl6548.h"

#if CONFIG_EXAMPLE_AUDIO_AMR

#define WRITE_RAW_DATA_SD 0
#define AMR_ENC_EN			0

//------------------------------------- ---CONFIG Parameters-----------------------------------------------//
#define NUM_CHANNELS CH_MONO

#define NB_SAMPLING_FREQ SR_8K
#define WB_SAMPLING_FREQ SR_16K

                                 //Options:- SR_8KHZ     =>8000hz  - PASS       
                                 //          SR_16KHZ    =>16000hz - PASS

#define AMRNB_FILE_NAME "sound.amr"    //Specify the file name you wish to play that is present in the SDCARD
#define AMRWB_FILE_NAME "sound-wb.amr"
#define WAV_FILE_NAME "sound.wav"
#define WAV_WB_FILE_NAME "sound-wb.wav"

//------------------------------------- ---CONFIG Parameters-----------------------------------------------//
static u8 *sp_tx_buf = NULL;
static u8 sp_zero_buf[SP_ZERO_BUF_SIZE];

static SP_InitTypeDef SP_InitStruct;
static SP_GDMA_STRUCT SPGdmaStruct;
static SP_OBJ sp_obj;
static SP_TX_INFO sp_tx_info;
static int audio_inited = 0;

/* From WmfDecBytesPerFrame in dec_input_format_tab.cpp */
const int sizes_nb[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };

/* From pvamrwbdecoder_api.h, by dividing by 8 and rounding up */
const int sizes_wb[] = { 17, 23, 32, 36, 40, 46, 50, 58, 60, 5, -1, -1, -1, -1, -1, 0 };

enum AMR_TYPE {
	AMR_INVALID = -1,
	AMR_NB = 0,
	AMR_WB
};

/* Copied from enc/src/gsmamr_enc.h */
enum Mode {
	MR475 = 0,/* 4.75 kbps */
	MR515,    /* 5.15 kbps */
	MR59,     /* 5.90 kbps */
	MR67,     /* 6.70 kbps */
	MR74,     /* 7.40 kbps */
	MR795,    /* 7.95 kbps */
	MR102,    /* 10.2 kbps */
	MR122,    /* 12.2 kbps */
	MRDTX,    /* DTX       */
	N_MODES   /* Not Used  */
};

static u8 *sp_get_free_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
	
	if (ptx_block->tx_gdma_own)
		return NULL;
	else{
		return (u8*)ptx_block->tx_addr;
	}	
}

static void sp_write_tx_page(u8 *src, u32 length)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
	
	memcpy((void*)ptx_block->tx_addr, src, length);
	ptx_block->tx_gdma_own = 1;
	sp_tx_info.tx_usr_cnt++;
	if (sp_tx_info.tx_usr_cnt == SP_DMA_PAGE_NUM){
		sp_tx_info.tx_usr_cnt = 0;
	}
}

static void sp_release_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);
	
	if (sp_tx_info.tx_empty_flag){
	}
	else{
		ptx_block->tx_gdma_own = 0;
		sp_tx_info.tx_gdma_cnt++;
		if (sp_tx_info.tx_gdma_cnt == SP_DMA_PAGE_NUM){
			sp_tx_info.tx_gdma_cnt = 0;
		}
	}
}

static u8 *sp_get_ready_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);
	
	if (ptx_block->tx_gdma_own){
		sp_tx_info.tx_empty_flag = 0;
		return (u8*)ptx_block->tx_addr;
	}
	else{
		sp_tx_info.tx_empty_flag = 1;
		return (u8*)sp_tx_info.tx_zero_block.tx_addr;	//for audio buffer empty case
	}
}

static u32 sp_get_ready_tx_length(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);

	if (sp_tx_info.tx_empty_flag){
		return sp_tx_info.tx_zero_block.tx_length;
	}
	else{
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
	GDMA_SetSrcAddr(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_addr);
	GDMA_SetBlkSize(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_length>>2);
	
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, ENABLE);
}

static void sp_rx_complete(void *data, char* pbuf)
{
	//
}

static void sp_init_hal(pSP_OBJ psp_obj)
{
	u32 div;
	
	PLL_I2S_Set(ENABLE);		//enable 98.304MHz PLL. needed if fs=8k/16k/32k/48k/96k
	//PLL_PCM_Set(ENABLE);		//enable 45.1584MHz PLL. needed if fs=44.1k/8.2k

	RCC_PeriphClockCmd(APBPeriph_AUDIOC, APBPeriph_AUDIOC_CLOCK, ENABLE);
	RCC_PeriphClockCmd(APBPeriph_SPORT, APBPeriph_SPORT_CLOCK, ENABLE);	

	//set clock divider to gen clock sample_rate*256 from 98.304M.
	switch(psp_obj->sample_rate){
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
		default:
			DBG_8195A("sample rate not supported!!\n");
			break;
	}
	PLL_Div(div);

	/*codec init*/
	CODEC_Init(psp_obj->sample_rate, psp_obj->word_len, psp_obj->mono_stereo, psp_obj->direction);
}

static void sp_conf_hal(pSP_OBJ psp_obj){
	u32 div;

	//set clock divider to gen clock sample_rate*256 from 98.304M.
	switch(psp_obj->sample_rate){
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
		default:
			DBG_8195A("sample rate not supported!!\n");
			break;
	}
	PLL_Div(div);

	CODEC_SetSr(psp_obj->sample_rate);
	
}

static void sp_init_tx_variables(int amr_type)
{
	int i;
	int page_size;

	if (amr_type == AMR_NB){
		page_size = NB_SP_DMA_PAGE_SIZE;
	}
	else{
		page_size = WB_SP_DMA_PAGE_SIZE;
	}

	for(i=0; i<SP_ZERO_BUF_SIZE; i++){
		sp_zero_buf[i] = 0;
	}
	sp_tx_info.tx_zero_block.tx_addr = (u32)sp_zero_buf;
	sp_tx_info.tx_zero_block.tx_length = (u32)SP_ZERO_BUF_SIZE;
	
	sp_tx_info.tx_gdma_cnt = 0;
	sp_tx_info.tx_usr_cnt = 0;
	sp_tx_info.tx_empty_flag = 0;
	
	for(i=0; i<SP_DMA_PAGE_NUM; i++){
		sp_tx_info.tx_block[i].tx_gdma_own = 0;
		sp_tx_info.tx_block[i].tx_addr = (u32)(sp_tx_buf+i*page_size);
		sp_tx_info.tx_block[i].tx_length = page_size;
	}
}
void audio_play_sd_amr(u8* filename){
	int drv_num = 0;
	int frame_size = 0;
	u32 read_length = 0;
	FRESULT res; 
	FATFS 	m_fs;
	FIL		m_file[2];  
	char	logical_drv[4]; //root diretor
	char abs_path[32]; //Path to input file
	DWORD bytes_left;
	DWORD file_size;
	int i = 0;
	int bw = 0;
	volatile u32 tim1 = 0;
	volatile u32 tim2 = 0;
	u32 start_heap, tx_addr, tx_length;
	int *ptx_buf;
	char header[9];
	void *amr = NULL;
	enum AMR_TYPE amr_type = AMR_INVALID;
#if WRITE_RAW_DATA_SD
	char abs_path_op[16]; //Path to output file
	const char *outfile = "sound_amr.pcm";
#endif
	
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
	if(drv_num < 0){
		printf("Rigester disk driver to FATFS fail.\n");
		return;
	}else{
		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}

	if(f_mount(&m_fs, logical_drv, 1)!= FR_OK){
		printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
		goto unreg;
	}
	memset(abs_path, 0x00, sizeof(abs_path));
	strcpy(abs_path, logical_drv);
	sprintf(&abs_path[strlen(abs_path)],"%s", filename);

	//Open source file
	res = f_open(&m_file[0], abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file
	if(res != FR_OK){
		printf("Open source file %s fail.\n", filename);
		goto umount;
	}
	
	file_size = (&m_file[0])->fsize;
	bytes_left = file_size;
	printf("File size of %s is %d\n", filename, file_size);

	memset(header, 0, 9);
	res = f_read(&m_file[0], header, 6, (UINT*)&read_length);
	if (res == FR_OK && read_length == 6 && memcmp(header, "#!AMR\n", 6) == 0) {
		printf("It's an AMRNB audio file\n");
		amr_type = AMR_NB;
		sp_tx_buf = malloc(NB_SP_DMA_PAGE_SIZE * SP_DMA_PAGE_NUM);
		if(!sp_tx_buf){
			printf("malloc failed for sp buffer\n");
			goto exit;
		}
		sp_obj.mono_stereo = NUM_CHANNELS;
		sp_obj.sample_rate = NB_SAMPLING_FREQ;
		sp_obj.word_len = WL_16;
		sp_obj.direction = APP_LINE_OUT;	
		
		if(!audio_inited){
			sp_init_hal(&sp_obj);
			audio_inited = 1;
		}
		else{
			sp_conf_hal(&sp_obj);
		}
		
		sp_init_tx_variables(amr_type);

		/*configure Sport according to the parameters*/
		AUDIO_SP_StructInit(&SP_InitStruct);
		SP_InitStruct.SP_MonoStereo= sp_obj.mono_stereo;
		SP_InitStruct.SP_WordLen = sp_obj.word_len;

		AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);
		
		AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
		AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);

		tx_addr = (u32)sp_get_ready_tx_page();
		tx_length = sp_get_ready_tx_length();
		AUDIO_SP_TXGDMA_Init(0, &SPGdmaStruct.SpTxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_tx_complete, (u8*)tx_addr, tx_length);

	}else{
		memset(header, 0, 9);
		f_lseek(&m_file[0], 0);
		res = f_read(&m_file[0], header, 9, (UINT*)&read_length);
		if (res == FR_OK && read_length == 9 && memcmp(header, "#!AMR-WB\n", 9) == 0) {
			printf("It's an AMRWB audio file\n");
			amr_type = AMR_WB;
			sp_tx_buf = malloc(WB_SP_DMA_PAGE_SIZE * SP_DMA_PAGE_NUM);
			if(!sp_tx_buf){
				printf("malloc failed for sp buffer\n");
				goto exit;
			}
			sp_obj.mono_stereo = NUM_CHANNELS;
			sp_obj.sample_rate = WB_SAMPLING_FREQ;
			sp_obj.word_len = WL_16;
			sp_obj.direction = APP_LINE_OUT;	
	
			if(!audio_inited){
				sp_init_hal(&sp_obj);
				audio_inited = 1;
			}
			else{
				sp_conf_hal(&sp_obj);
			}
			
			sp_init_tx_variables(amr_type);

			/*configure Sport according to the parameters*/
			AUDIO_SP_StructInit(&SP_InitStruct);
			SP_InitStruct.SP_MonoStereo= sp_obj.mono_stereo;
			SP_InitStruct.SP_WordLen = sp_obj.word_len;

			AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);
			
			AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
			AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);

			tx_addr = (u32)sp_get_ready_tx_page();
			tx_length = sp_get_ready_tx_length();
			AUDIO_SP_TXGDMA_Init(0, &SPGdmaStruct.SpTxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_tx_complete, (u8*)tx_addr, tx_length);

		}
	}
	if(amr_type == AMR_INVALID){
		printf("Bad header\n");
		goto exit;
	}

#if WRITE_RAW_DATA_SD
	if(amr_type == AMR_WB)
		outfile = "sound-amrwb.pcm";
	memset(abs_path_op, 0x00, sizeof(abs_path_op));
	strcpy(abs_path_op, logical_drv);
	sprintf(&abs_path_op[strlen(abs_path_op)],"%s", outfile);
	res = f_open(&m_file[1], abs_path_op, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);  // open read only file
	if(res != FR_OK){
		printf("Open source file %(s) fail.\n", outfile);
		goto exit;
	}
#endif
	start_heap = xPortGetFreeHeapSize();
	if(amr_type == AMR_NB){
		frame_size = NB_SP_DMA_PAGE_SIZE/2;
		amr = (void *)Decoder_Interface_init();
	}
	else if(amr_type == AMR_WB){
		frame_size = WB_SP_DMA_PAGE_SIZE/2;
		amr = (void *)D_IF_init();
	}
	if(!amr){
		printf("decoder interface init failed\r\n");
		goto exit;
	}
	tim1 = rtw_get_current_time();
	do{
		/* Read a block */
		uint8_t buffer[500], littleendian[WB_SP_DMA_PAGE_SIZE], *ptr;
		int size, i;
		int16_t outbuffer[WB_SP_DMA_PAGE_SIZE/2];
		/* Read the mode byte */
		res = f_read(&m_file[0], buffer, 1, (UINT*)&read_length);
		if (res != FR_OK || read_length != 1){
			if(read_length == 0)
				printf("read done\r\n");
			else
				printf("read the mode byte failed\r\n");
			break;
		}
		/* Find the packet size */
		if(amr_type == AMR_NB)
			size = sizes_nb[(buffer[0] >> 3) & 0x0f];
		else if(amr_type == AMR_WB)
			size = sizes_wb[(buffer[0] >> 3) & 0x0f];
		if(size < 0)
			break;

		res = f_read(&m_file[0], buffer + 1, size, (UINT*)&read_length);
		if(res != FR_OK){
			printf("read failed\r\n");
			break;
		}

		/* Decode the packet */
		if(amr_type == AMR_NB)
			Decoder_Interface_Decode(amr, buffer, outbuffer, 0);
		else if(amr_type == AMR_WB)
			D_IF_decode(amr, buffer, outbuffer, 0);

		/* Convert to little endian and write to wav */
		ptr = littleendian;
		for (i = 0; i < frame_size; i++) {
			*ptr++ = (outbuffer[i] >> 0) & 0xff;
			*ptr++ = (outbuffer[i] >> 8) & 0xff;
		}

#if WRITE_RAW_DATA_SD
		do{
			res = f_write(&m_file[1], littleendian, frame_size*2, (u32*)&bw);
			if(res){
				f_lseek(&m_file[1], 0); 
				printf("Write error.\n");
			}
			//printf("Write %d bytes.\n", bw);
		}while(bw < frame_size*2);
		bw = 0;
#endif
#if 1
		retry:
			ptx_buf = (int*)sp_get_free_tx_page();
			if(ptx_buf){
				sp_write_tx_page((void*)littleendian, frame_size*2);
			}else{
				vTaskDelay(1);
				goto retry;
			}
#endif
	}while(1);

	tim2 = rtw_get_current_time();
	printf("decoding finished (Heap used: 0x%x, Time passed: %dms)\n", start_heap - xPortGetFreeHeapSize(), (tim2-tim1));
	printf("PCM done\n");

	if(amr_type == AMR_NB)
		Decoder_Interface_exit(amr);
	else if(amr_type == AMR_WB)
		D_IF_exit(amr);

exit:
	DelayMs(100);
	AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, DISABLE);
	AUDIO_SP_TxStart(AUDIO_SPORT_DEV, DISABLE);	
	GDMA_Cmd(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum, DISABLE);
	GDMA_ChnlFree(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum);

	if(sp_tx_buf)
		free(sp_tx_buf);
	// close source file
	res = f_close(&m_file[0]);
	if(res){
		printf("close file (%s) fail.\n", filename);
	}
#if WRITE_RAW_DATA_SD
	res = f_close(&m_file[1]);
	if(res){
		printf("close file (%s) fail.\n", outfile);
	}
#endif

umount:
	if(f_mount(NULL, logical_drv, 1) != FR_OK){
		printf("FATFS unmount logical drive fail.\n");
	}

unreg:	
	if(FATFS_UnRegisterDiskDriver(drv_num))	
		printf("Unregister disk driver from FATFS fail.\n");
	
}

#if 	AMR_ENC_EN
void amrnb_enc_sd_wav(u8* filename){
	int drv_num = 0;
	int frame_size = 0;
	u32 read_length = 0;
	FRESULT res; 
	FATFS 	m_fs;
	FIL		m_file[2];  
	char	logical_drv[4]; //root diretor
	char abs_path[32]; //Path to input file
	DWORD bytes_left;
	DWORD file_size;
	int i = 0;
	int bw = 0;
	volatile u32 tim1 = 0;
	volatile u32 tim2 = 0;
	u32 start_heap;
	void *amr = NULL;
	int dtx = 1; // TBD
	int channels = 1;
	enum Mode mode = MR122;
	char abs_path_op[16]; //Path to output file
	const char *outfile = "sound_amrnb_enc.amr";
	
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
	if(drv_num < 0){
		printf("Rigester disk driver to FATFS fail.\n");
		return;
	}else{
		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}

	if(f_mount(&m_fs, logical_drv, 1)!= FR_OK){
		printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
		goto unreg;
	}
	memset(abs_path, 0x00, sizeof(abs_path));
	strcpy(abs_path, logical_drv);
	sprintf(&abs_path[strlen(abs_path)],"%s", filename);

	//Open source file
	res = f_open(&m_file[0], abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file
	if(res != FR_OK){
		printf("Open source file %s fail.\n", filename);
		goto umount;
	}
	
	file_size = (&m_file[0])->fsize;
	bytes_left = file_size;
	printf("File size of %s is %d\n", filename, file_size);
	f_lseek(&m_file[0], 44); // skip the wav header

	memset(abs_path_op, 0x00, sizeof(abs_path_op));
	strcpy(abs_path_op, logical_drv);
	sprintf(&abs_path_op[strlen(abs_path_op)],"%s", outfile);
	res = f_open(&m_file[1], abs_path_op, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);  // open read only file
	if(res != FR_OK){
		printf("Open source file %(s) fail.\n", outfile);
		goto exit;
	}

	start_heap = xPortGetFreeHeapSize();
	amr = (void *)Encoder_Interface_init(dtx);
	if(!amr){
		printf("decoder interface init failed\r\n");
		goto exit;
	}
	tim1 = rtw_get_current_time();
	res = f_write(&m_file[1], "#!AMR\n", 6, (u32*)&bw);
	if(res != FR_OK){
		printf("Write header to file %(s) fail.\n", outfile);
		goto exit;
	}
	do{
		/* Read a block */
		u8 inputBuf[1*2*160]; //channel*2*160, only encode one channel
		u16 buf[160];
		u8 outbuf[500];
		int read, n;
		/* Read the mode byte */
		res = f_read(&m_file[0], inputBuf, sizeof(inputBuf), (UINT*)&read_length);
		read_length /= channels;
		read_length /= 2;
		if (res != FR_OK || read_length < 160){
			if(read_length == 0)
				printf("read done\r\n");
			else
				printf("read the mode byte failed\r\n");
			break;
		}

		for (i = 0; i < 160; i++) {
			const uint8_t* in = &inputBuf[2*1*i];
			buf[i] = in[0] | (in[1] << 8);
		}

		n = Encoder_Interface_Encode(amr, mode, buf, outbuf, 0);

		do{
			res = f_write(&m_file[1], outbuf, n, (u32*)&bw);
			if(res){
				f_lseek(&m_file[1], 0); 
				printf("Write error.\n");
			}
			//printf("Write %d bytes.\n", bw);
		}while(bw < n);
		bw = 0;
	}while(1);

	tim2 = rtw_get_current_time();
	printf("encoding finished (Heap used: 0x%x, Time passed: %dms)\n", start_heap - xPortGetFreeHeapSize(), (tim2-tim1));

	Encoder_Interface_exit(amr);

exit:
	// close source file
	res = f_close(&m_file[0]);
	if(res){
		printf("close file (%s) fail.\n", filename);
	}
	res = f_close(&m_file[1]);
	if(res){
		printf("close file (%s) fail.\n", outfile);
	}

umount:
	if(f_mount(NULL, logical_drv, 1) != FR_OK){
		printf("FATFS unmount logical drive fail.\n");
	}

unreg:	
	if(FATFS_UnRegisterDiskDriver(drv_num))	
		printf("Unregister disk driver from FATFS fail.\n");
	
}

void amrwb_enc_sd_wav(u8* filename){
	int drv_num = 0;
	int frame_size = 0;
	u32 read_length = 0;
	FRESULT res; 
	FATFS 	m_fs;
	FIL		m_file[2];  
	char	logical_drv[4]; //root diretor
	char abs_path[32]; //Path to input file
	DWORD bytes_left;
	DWORD file_size;
	int i = 0;
	int bw = 0;
	volatile u32 tim1 = 0;
	volatile u32 tim2 = 0;
	u32 start_heap;
	void *amr = NULL;
	int dtx = 0; // TBD
	int channels = 1, inputSize;
    u8 *inputBuf;
	int mode = 8;
	char abs_path_op[16]; //Path to output file
	const char *outfile = "sound_amrwb_enc.amr";
	
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
	if(drv_num < 0){
		printf("Rigester disk driver to FATFS fail.\n");
		return;
	}else{
		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}

	if(f_mount(&m_fs, logical_drv, 1)!= FR_OK){
		printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
		goto unreg;
	}
	memset(abs_path, 0x00, sizeof(abs_path));
	strcpy(abs_path, logical_drv);
	sprintf(&abs_path[strlen(abs_path)],"%s", filename);

	//Open source file
	res = f_open(&m_file[0], abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file
	if(res != FR_OK){
		printf("Open source file %s fail.\n", filename);
		goto umount;
	}
	
	file_size = (&m_file[0])->fsize;
	bytes_left = file_size;
	printf("File size of %s is %d\n", filename, file_size);
	f_lseek(&m_file[0], 44); // skip the wav header

	memset(abs_path_op, 0x00, sizeof(abs_path_op));
	strcpy(abs_path_op, logical_drv);
	sprintf(&abs_path_op[strlen(abs_path_op)],"%s", outfile);
	res = f_open(&m_file[1], abs_path_op, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);  // open read only file
	if(res != FR_OK){
		printf("Open source file %(s) fail.\n", outfile);
		goto exit;
	}
	inputSize = channels*2*320;
	inputBuf = (uint8_t*) malloc(inputSize);

	start_heap = xPortGetFreeHeapSize();
	amr = (void *)E_IF_init();
	if(!amr){
		printf("decoder interface init failed\r\n");
		goto exit;
	}
	tim1 = rtw_get_current_time();
	res = f_write(&m_file[1], "#!AMR-WB\n", 9, (u32*)&bw);
	if(res != FR_OK){
		printf("Write header to file %(s) fail.\n", outfile);
		goto exit;
	}
	do{
		int read, i, n;
		short buf[320];
		uint8_t outbuf[500];
		/* Read the mode byte */
		res = f_read(&m_file[0], inputBuf, inputSize, (UINT*)&read_length);
		read_length /= channels;
		read_length /= 2;
		if (res != FR_OK || read_length < 320){
			if(read_length == 0)
				printf("read done\r\n");
			else
				printf("read the mode byte failed\r\n");
			break;
		}

		for (i = 0; i < 320; i++) {
			const uint8_t* in = &inputBuf[2*channels*i];
			buf[i] = in[0] | (in[1] << 8);
		}
		n = E_IF_encode(amr, mode, buf, outbuf, dtx);
		do{
			res = f_write(&m_file[1], outbuf, n, (u32*)&bw);
			if(res){
				f_lseek(&m_file[1], 0); 
				printf("Write error.\n");
			}
			//printf("Write %d bytes.\n", bw);
		}while(bw < n);
		bw = 0;
	}while(1);

	tim2 = rtw_get_current_time();
	printf("encoding finished (Heap used: 0x%x, Time passed: %dms)\n", start_heap - xPortGetFreeHeapSize(), (tim2-tim1));

	E_IF_exit(amr);

exit:
	// close source file
	res = f_close(&m_file[0]);
	if(res){
		printf("close file (%s) fail.\n", filename);
	}
	res = f_close(&m_file[1]);
	if(res){
		printf("close file (%s) fail.\n", outfile);
	}

umount:
	if(f_mount(NULL, logical_drv, 1) != FR_OK){
		printf("FATFS unmount logical drive fail.\n");
	}

unreg:	
	if(FATFS_UnRegisterDiskDriver(drv_num))	
		printf("Unregister disk driver from FATFS fail.\n");

    if(inputBuf)
        free(inputBuf);
}
#endif

void example_audio_amr_thread(void* param){
	printf("Audio codec AMR demo begin......\n"); 
	audio_play_sd_amr(AMRNB_FILE_NAME);
	vTaskDelay(1000);
	audio_play_sd_amr(AMRWB_FILE_NAME);
#if 	AMR_ENC_EN
	vTaskDelay(1000);
	amrnb_enc_sd_wav(WAV_FILE_NAME);
	vTaskDelay(1000);
	amrwb_enc_sd_wav(WAV_WB_FILE_NAME);
#endif

exit:
	vTaskDelete(NULL);
}

void example_audio_amr(void)
{
	if(xTaskCreate(example_audio_amr_thread, ((const char*)"example_audio_amr_thread"), 4096, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_audio_amr_thread) failed", __FUNCTION__);
}

#endif
