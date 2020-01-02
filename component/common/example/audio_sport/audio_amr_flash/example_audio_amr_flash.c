#include "example_audio_amr_flash.h"
#include <platform/platform_stdlib.h>
#include "platform_opts.h"
#include "section_config.h"
#include "rl6548.h"
#include "ff.h"
#include "audio_play.h"
//data to be played are stored in .h file as an array whose name is "Array"
//#include "sound.h"
#include "sound_wb.h"

//------------------------------------- ---CONFIG Parameters-----------------------------------------------//
#define NUM_CHANNELS CH_MONO

#define NB_SAMPLING_FREQ SR_8K
#define WB_SAMPLING_FREQ SR_16K


//------------------------------------- ---CONFIG Parameters-----------------------------------------------//
static u8 *sp_tx_buf = NULL;
static u8 sp_zero_buf[SP_ZERO_BUF_SIZE];

static SP_InitTypeDef SP_InitStruct;
static SP_GDMA_STRUCT SPGdmaStruct;
static SP_OBJ sp_obj;
static SP_TX_INFO sp_tx_info;
static int audio_inited = 0;
static int flag; 
/* From WmfDecBytesPerFrame in dec_input_format_tab.cpp */
const static int sizes_nb[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };

/* From pvamrwbdecoder_api.h, by dividing by 8 and rounding up */
const static int sizes_wb[] = { 17, 23, 32, 36, 40, 46, 50, 58, 60, 5, -1, -1, -1, -1, -1, 0 };

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
	if(flag == 1)
		GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, ENABLE);
	else{
		AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, DISABLE);
		AUDIO_SP_TxStart(AUDIO_SPORT_DEV, DISABLE);	
		GDMA_Cmd(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum, DISABLE);
		GDMA_ChnlFree(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum);
	}
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

static void audio_play_flash_amr(){
	int frame_size = 0;
	u32 read_length = 0;
	int res; 
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
	
	res = mf_open(&fdst_amr, Array, sizeof(Array)); // open read only file
	if(res){
		printf("Open source file %d.\n", res);

	}
	
	file_size = (&fdst_amr)->size;
	bytes_left = file_size;
	printf("File size of %s is %d\n", "audio_welcome", file_size);
	

	amr = (void*)AMR_INVALID;
	
	//determine the type(NB or WB) of audio files
	res = mf_read(&fdst_amr, header, 6,  (UINT*)&read_length);
	if(res == 0 && read_length == 6 && memcmp(header, "#!AMR\n", 6) == 0 ){
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
	} else{
		fdst_amr.pos = 0;
		res = mf_read(&fdst_amr, header, 9,  (UINT*)&read_length);
		if (res == 0 && read_length == 9 && memcmp(header, "#!AMR-WB\n", 9) == 0) {
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
		}
	}

	if(!audio_inited){
		sp_init_hal(&sp_obj);
		audio_inited = 1;
	} else{
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

	if(amr_type == AMR_INVALID){
		printf("Bad header\n");
		goto exit;
	}

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
		res = mf_read(&fdst_amr, buffer, 1, (UINT*)&read_length);
		if (read_length != 1){
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

		res = mf_read(&fdst_amr, buffer+1, size, (UINT*)&read_length);

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

		retry:
			ptx_buf = (int*)sp_get_free_tx_page();
			if(ptx_buf){
				sp_write_tx_page((void*)littleendian, frame_size*2);
			}else{
				vTaskDelay(1);
				goto retry;
			}
	}while(1);

	tim2 = rtw_get_current_time();
	printf("decoding finished (Heap used: 0x%x, Time passed: %dms)\n", start_heap - xPortGetFreeHeapSize(), (tim2-tim1));
	printf("PCM done\n");

	if(amr_type == AMR_NB)
		Decoder_Interface_exit(amr);
	else if(amr_type == AMR_WB)
		D_IF_exit(amr);

exit:
	/*
	DelayMs(100);
	AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, DISABLE);
	AUDIO_SP_TxStart(AUDIO_SPORT_DEV, DISABLE);	
	GDMA_Cmd(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum, DISABLE);
	GDMA_ChnlFree(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum);
	*/
	if(sp_tx_buf)
		free(sp_tx_buf);
	res = mf_close(&fdst_amr);

	printf("[%s] end!\n",__func__);
}



void example_audio_amr_flash_thread(void* param){
	vTaskDelay(5000);
	printf("Audio codec AMR demo begin......\n");
	for(int i = 0; i < 200000; i++){
		printf("index is %d\n", i);
		//set flag to 1 before playing audio file
		flag = 1;
		audio_play_flash_amr();
		//set flag to 0 after playing audio file
		flag = 0;
		vTaskDelay(1000);
	}

exit:
	vTaskDelete(NULL);
}

void example_audio_amr_flash(void)
{
	if(xTaskCreate(example_audio_amr_flash_thread, ((const char*)"example_audio_amr_flash_thread"), 4096, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_audio_amr_flash_thread) failed", __FUNCTION__);
}

