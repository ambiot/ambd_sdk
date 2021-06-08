#include "main.h"
#include <platform/platform_stdlib.h>
#include "osdep_service.h"
#include "rl6548.h"
#include "resample_library.h"

#include "sine_48.00k_1ch_16bit.c"
PSRAM_BSS_SECTION short voice_sample[480000];
RESAMPLE_STAT48TO16 state;

static SP_InitTypeDef SP_InitStruct;
static SP_GDMA_STRUCT SPGdmaStruct;
static SP_OBJ sp_obj;
static SP_TX_INFO sp_tx_info;

//The size of this buffer should be multiples of 32 and its head address should align to 32 
//to prevent problems that may occur when CPU and DMA access this area simultaneously. 
static u8 sp_tx_buf[SP_DMA_PAGE_SIZE*SP_DMA_PAGE_NUM]__attribute__((aligned(32)));
static u8 sp_zero_buf[SP_ZERO_BUF_SIZE]__attribute__((aligned(32)));

u8 *sp_get_free_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
	
	if (ptx_block->tx_gdma_own)
		return NULL;
	else{
		return (u8*)ptx_block->tx_addr;
	}
}

void sp_write_tx_page(u8 *src, u32 length)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
	
	memcpy((void*)ptx_block->tx_addr, src, length);
	ptx_block->tx_gdma_own = 1;
	sp_tx_info.tx_usr_cnt++;
	if (sp_tx_info.tx_usr_cnt == SP_DMA_PAGE_NUM){
		sp_tx_info.tx_usr_cnt = 0;
	}
}

void sp_release_tx_page(void)
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

u8 *sp_get_ready_tx_page(void)
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

u32 sp_get_ready_tx_length(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);

	if (sp_tx_info.tx_empty_flag){
		return sp_tx_info.tx_zero_block.tx_length;
	}
	else{
		return ptx_block->tx_length;
	}
}

void sp_tx_complete(void *Data)
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
	GPIO_InitTypeDef GPIO_InitStruct_temp;
	
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

static void sp_init_tx_variables(void)
{
	int i;

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
		sp_tx_info.tx_block[i].tx_addr = (u32)sp_tx_buf+i*SP_DMA_PAGE_SIZE;
		sp_tx_info.tx_block[i].tx_length = SP_DMA_PAGE_SIZE;
	}
}



#define RESAMPLE_OUT_LEN (SP_DMA_PAGE_SIZE>>1)
void example_audio_resample_thread(void* param)
{
	int i = 0;
	u32 tx_addr;
	u32 tx_length;
	pSP_OBJ psp_obj = (pSP_OBJ)param;
	u32 resample_size;
	u32 sample_size = sizeof(pcm_data)>>1;
	short voice_resample[RESAMPLE_OUT_LEN];
	int temp[RESAMPLE_OUT_LEN*3 + 16];

	app_init_psram();
	
	DBG_8195A("Audio resample demo begin......\n");
	memcpy((char*)voice_sample, (char*)pcm_data, sizeof(pcm_data));
	resample_size = sample_size/3;
	DBG_8195A("sample size: %d, resample size: %d......\n", sample_size, resample_size);
	ResampleReset48khzTo16khz(&state);

	sp_init_hal(psp_obj);
	CODEC_SetVolume(0x90, 0x90);
	
	sp_init_tx_variables();

	/*configure Sport according to the parameters*/
	AUDIO_SP_StructInit(&SP_InitStruct);
	SP_InitStruct.SP_MonoStereo= psp_obj->mono_stereo;
	SP_InitStruct.SP_WordLen = psp_obj->word_len;

	AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);
	
	AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
	AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);
	
	tx_addr = (u32)sp_get_ready_tx_page();
	tx_length = sp_get_ready_tx_length();
	AUDIO_SP_TXGDMA_Init(0, &SPGdmaStruct.SpTxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_tx_complete, (u8*)tx_addr, tx_length);

	while(1){	
		if(sp_get_free_tx_page()){
			memset(voice_resample, 0, SP_DMA_PAGE_SIZE);
			memset(temp, 0, sizeof(temp));
			Resample48khzTo16khz(voice_sample+i*(RESAMPLE_OUT_LEN*3), RESAMPLE_OUT_LEN*3, voice_resample, &state, temp);
			sp_write_tx_page((u8 *)voice_resample, SP_DMA_PAGE_SIZE);
			i++;	
			if ((i+1)*SP_DMA_PAGE_SIZE > resample_size*2){
				i = 0;
				//ResampleReset48khzTo16khz(&state);
			}

		}
		else{
			vTaskDelay(1);
		}		
	}
exit:
	vTaskDelete(NULL);
}

void main(void)
{
	sp_obj.sample_rate = SR_16K;
	sp_obj.word_len = WL_16;
	sp_obj.mono_stereo = CH_MONO;
	sp_obj.direction = APP_LINE_OUT;
	if(xTaskCreate(example_audio_resample_thread, ((const char*)"example_audio_resample_thread"), 1024, (void *)(&sp_obj), tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_audio_resample_thread) failed", __FUNCTION__);

	vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
}

