#include "main.h"
#include <platform/platform_stdlib.h>
#include "rl6548.h"

#define SRC_BIRD_SING	0

#if SRC_BIRD_SING
#include "birds_16000_2ch_16b.c"
#else
static short sine_wave[256] = {0, 0, 12539, 12539, 23170, 23170, 30273, 30273, 32767, 32767, 30273, 30273, 23170, 23170, 12539, 12539,
				0, 0, -12539, -12539, -23170, -23170, -30273, -30273, -32767, -32767, -30273, -30273, -23170, -23170, -12539, -12539,
				0, 0, 12539, 12539, 23170, 23170, 30273, 30273, 32767, 32767, 30273, 30273, 23170, 23170, 12539, 12539,
				0, 0, -12539, -12539, -23170, -23170, -30273, -30273, -32767, -32767, -30273, -30273, -23170, -23170, -12539, -12539,
				0, 0, 12539, 12539, 23170, 23170, 30273, 30273, 32767, 32767, 30273, 30273, 23170, 23170, 12539, 12539,
				0, 0, -12539, -12539, -23170, -23170, -30273, -30273, -32767, -32767, -30273, -30273, -23170, -23170, -12539, -12539,
				0, 0, 12539, 12539, 23170, 23170, 30273, 30273, 32767, 32767, 30273, 30273, 23170, 23170, 12539, 12539,
				0, 0, -12539, -12539, -23170, -23170, -30273, -30273, -32767, -32767, -30273, -30273, -23170, -23170, -12539, -12539,
				0, 0, 12539, 12539, 23170, 23170, 30273, 30273, 32767, 32767, 30273, 30273, 23170, 23170, 12539, 12539,
				0, 0, -12539, -12539, -23170, -23170, -30273, -30273, -32767, -32767, -30273, -30273, -23170, -23170, -12539, -12539,
				0, 0, 12539, 12539, 23170, 23170, 30273, 30273, 32767, 32767, 30273, 30273, 23170, 23170, 12539, 12539,
				0, 0, -12539, -12539, -23170, -23170, -30273, -30273, -32767, -32767, -30273, -30273, -23170, -23170, -12539, -12539,
				0, 0, 12539, 12539, 23170, 23170, 30273, 30273, 32767, 32767, 30273, 30273, 23170, 23170, 12539, 12539,
				0, 0, -12539, -12539, -23170, -23170, -30273, -30273, -32767, -32767, -30273, -30273, -23170, -23170, -12539, -12539,
				0, 0, 12539, 12539, 23170, 23170, 30273, 30273, 32767, 32767, 30273, 30273, 23170, 23170, 12539, 12539,
				0, 0, -12539, -12539, -23170, -23170, -30273, -30273, -32767, -32767, -30273, -30273, -23170, -23170, -12539, -12539,
};
#endif

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

void sp_rx_complete(void *data, char* pbuf)
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
			DiagPrintf("sample rate not supported!!\n");
			break;
	}
	PLL_Div(div);
	
	Pinmux_Config(_PA_28, PINMUX_FUNCTION_GPIO);	//audio switch
	PAD_PullCtrl(_PA_28, GPIO_PuPd_DOWN);
	Pinmux_Config(_PB_6, PINMUX_FUNCTION_GPIO);		//audio amplifier shutdown
	PAD_PullCtrl(_PB_6, GPIO_PuPd_DOWN);

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

void example_audio_spk_thread(void* param)
{
	int i = 0;
	u32 tx_addr;
	u32 tx_length;
	pSP_OBJ psp_obj = (pSP_OBJ)param;
	
	DiagPrintf("Audio speaker demo begin......\n");

	sp_init_hal(psp_obj);
	
	sp_init_tx_variables();

	/*configure Sport according to the parameters*/
	AUDIO_SP_StructInit(&SP_InitStruct);
	SP_InitStruct.SP_MonoStereo= psp_obj->mono_stereo;
	SP_InitStruct.SP_WordLen = psp_obj->word_len;

	AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);
	
	AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
	AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);

	#if SRC_BIRD_SING
	DiagPrintf("\nPlay bird sing on memory.\n");
	#else
	DiagPrintf("\nPlay 1kHz single tone.\n");
	#endif
	
	tx_addr = (u32)sp_get_ready_tx_page();
	tx_length = sp_get_ready_tx_length();
	AUDIO_SP_TXGDMA_Init(0, &SPGdmaStruct.SpTxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_tx_complete, (u8*)tx_addr, tx_length);

	while(1){
		if(sp_get_free_tx_page()){
			#if SRC_BIRD_SING	//playback bird sing
			sp_write_tx_page((u8 *)birds_sing+i*SP_DMA_PAGE_SIZE, SP_DMA_PAGE_SIZE);
			i++;	
			if ((i+1)*SP_DMA_PAGE_SIZE > birds_sing_size*4){
				i = 0;
			}
			#else	//play 1kHz single tone
			sp_write_tx_page((u8 *)sine_wave, SP_DMA_PAGE_SIZE);
			#endif
			

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
	sp_obj.mono_stereo = CH_STEREO;
	sp_obj.direction = APP_LINE_OUT;
	if(xTaskCreate(example_audio_spk_thread, ((const char*)"example_audio_spk_thread"), 512, (void *)(&sp_obj), tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DiagPrintf("\n\r%s xTaskCreate(example_audio_spk_thread) failed", __FUNCTION__);
     
	vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
}

