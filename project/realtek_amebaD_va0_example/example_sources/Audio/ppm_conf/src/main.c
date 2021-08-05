#include "main.h"
#include <platform/platform_stdlib.h>
#include "osdep_service.h"
#include "rl6548.h"

#if (SP_DMA_PAGE_SIZE == 256)
static const s16 WinSmooth[128] = {
    19, 78, 175, 310, 483, 695, 943, 1228,
    1549, 1905, 2296, 2720, 3176, 3664, 4182, 4728,
    5303, 5904, 6529, 7178, 7849, 8540, 9250, 9976,
    10718, 11473, 12240, 13017, 13801, 14592, 15387, 16185,
    16982, 17779, 18572, 19360, 20141, 20913, 21674, 22423,
    23157, 23875, 24576, 25257, 25917, 26555, 27168, 27756,
    28316, 28849, 29352, 29824, 30264, 30672, 31045, 31384,
    31687, 31954, 32184, 32376, 32531, 32647, 32724, 32763,
    32763, 32724, 32647, 32531, 32376, 32184, 31954, 31687,
    31384, 31045, 30672, 30264, 29824, 29352, 28849, 28316,
    27756, 27168, 26555, 25917, 25257, 24576, 23875, 23157,
    22423, 21674, 20913, 20141, 19360, 18572, 17779, 16982,
    16185, 15387, 14592, 13801, 13017, 12240, 11473, 10718,
    9976, 9250, 8540, 7849, 7178, 6529, 5904, 5303,
    4728, 4182, 3664, 3176, 2720, 2296, 1905, 1549,
    1228, 943, 695, 483, 310, 175, 78, 19,
};
#elif (SP_DMA_PAGE_SIZE == 512)
static const s16 WinSmooth[256] = {
    5, 20, 44, 78, 122, 176, 239, 312, 395, 487, 589, 700, 821, 950, 1089, 1238,
    1395, 1561, 1736, 1920, 2112, 2313, 2523, 2740, 2966, 3200, 3442, 3691, 3948, 4213, 4484, 4763,
    5049, 5342, 5641, 5946, 6258, 6576, 6900, 7229, 7564, 7904, 8250, 8600, 8954, 9314, 9677, 10044,
    10416, 10790, 11169, 11550, 11934, 12321, 12710, 13101, 13495, 13890, 14286, 14684, 15083, 15483, 15883, 16283,
    16684, 17084, 17484, 17883, 18282, 18679, 19075, 19469, 19862, 20252, 20640, 21025, 21408, 21788, 22164, 22537,
    22907, 23272, 23633, 23990, 24343, 24691, 25033, 25371, 25703, 26030, 26351, 26665, 26974, 27277, 27572, 27862,
    28144, 28419, 28688, 28948, 29202, 29447, 29685, 29915, 30137, 30350, 30555, 30752, 30940, 31120, 31290, 31452,
    31605, 31748, 31883, 32008, 32124, 32230, 32327, 32415, 32492, 32561, 32619, 32668, 32707, 32736, 32756, 32766,
    32766, 32756, 32736, 32707, 32668, 32619, 32561, 32492, 32415, 32327, 32230, 32124, 32008, 31883, 31748, 31605,
    31452, 31290, 31120, 30940, 30752, 30555, 30350, 30137, 29915, 29685, 29447, 29202, 28948, 28688, 28419, 28144,
    27862, 27572, 27277, 26974, 26665, 26351, 26030, 25703, 25371, 25033, 24691, 24343, 23990, 23633, 23272, 22907,
    22537, 22164, 21788, 21408, 21025, 20640, 20252, 19862, 19469, 19075, 18679, 18282, 17883, 17484, 17084, 16684,
    16283, 15883, 15483, 15083, 14684, 14286, 13890, 13495, 13101, 12710, 12321, 11934, 11550, 11169, 10790, 10416,
    10044, 9677, 9314, 8954, 8600, 8250, 7904, 7564, 7229, 6900, 6576, 6258, 5946, 5641, 5342, 5049, 
    4763, 4484, 4213, 3948, 3691, 3442, 3200, 2966, 2740, 2523, 2313, 2112, 1920, 1736, 1561, 1395,
    1238, 1089, 950, 821, 700, 589, 487, 395, 312, 239, 176, 122, 78, 44, 20, 5,
};
#endif

static SP_InitTypeDef SP_InitStruct;
static SP_GDMA_STRUCT SPGdmaStruct;
static SP_OBJ sp_obj;
static SP_TX_INFO sp_tx_info;
static SP_RX_INFO sp_rx_info;
static SP_PPM_CONF sp_ppm_conf;

static u8 sp_tx_buf[(SP_DMA_PAGE_SIZE+4)*SP_DMA_PAGE_NUM];
static u8 sp_zero_buf[SP_ZERO_BUF_SIZE];

SRAM_NOCACHE_DATA_SECTION static u8 sp_rx_buf[SP_DMA_PAGE_SIZE*SP_DMA_PAGE_NUM];
static u8 sp_full_buf[SP_FULL_BUF_SIZE];

static _timerHandle ppm_conf_timer = NULL;

u8 *sp_get_free_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
	
	if (ptx_block->tx_gdma_own)
		return NULL;
	else{
		return ptx_block->tx_addr;
	}
}

#if 0
void sp_write_tx_page(u8 *src, u32 length)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
	
	memcpy(ptx_block->tx_addr, src, length);
	ptx_block->tx_gdma_own = 1;
	sp_tx_info.tx_usr_cnt++;
	if (sp_tx_info.tx_usr_cnt == SP_DMA_PAGE_NUM){
		sp_tx_info.tx_usr_cnt = 0;
	}
}
#endif

void sp_write_tx_page(u8 *src, u32 length)
{
	u32 i;
	s16 *tx_data;
	s16 tmp1, tmp2;
	
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
	memcpy(ptx_block->tx_addr, src, length);
	if (sp_ppm_conf.adj_en && sp_ppm_conf.adj_once){
		tx_data = (s16 *)ptx_block->tx_addr;
		if (sp_ppm_conf.adj_dir){

			for (i=0; i<(length>>1)-2; i=i+2){
				tmp1 = tx_data[i]*WinSmooth[i/2+(SP_DMA_PAGE_SIZE>>2)]/33000;
				tmp2 = tx_data[i+2]*WinSmooth[i/2]/33000;
				tx_data[i] = (tmp1+tmp2);
			}
			for (i=1; i<(length>>1)-1; i=i+2){
				tmp1 = tx_data[i]*WinSmooth[(i-1)/2+(SP_DMA_PAGE_SIZE>>2)]/33000;
				tmp2 = tx_data[i+2]*WinSmooth[(i-1)/2]/33000;				
				tx_data[i] = (tmp1+tmp2);
			}			
			ptx_block->tx_length = length-4;
		}
		else{
			tx_data[length>>1] = tx_data[(length>>1)-2];
			for (i=(length>>1)-2; i>0; i=i-2){
				tmp1 = tx_data[i]*WinSmooth[i/2+(SP_DMA_PAGE_SIZE>>2)]/33000;
				tmp2 = tx_data[i-2]*WinSmooth[i/2]/33000;
				tx_data[i] = (tmp1+tmp2);
			}
			tx_data[(length>>1)+1] = tx_data[(length>>1)-1];
			for (i=(length>>1)-1; i>1; i=i-2){
				tmp1 = tx_data[i]*WinSmooth[(i-1)/2+(SP_DMA_PAGE_SIZE>>2)]/33000;
				tmp2 = tx_data[i-2]*WinSmooth[(i-1)/2]/33000;
				tx_data[i] = (tmp1+tmp2);
			}
			ptx_block->tx_length = length+4;
		}
		sp_ppm_conf.adj_once = _FALSE;
	}
	else{
		ptx_block->tx_length = length;
	}
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
		return ptx_block->tx_addr;
	}
	else{
		DiagPrintf("empty\n");
		sp_tx_info.tx_empty_flag = 1;
		return sp_tx_info.tx_zero_block.tx_addr;	//for audio buffer empty case
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

u8 *sp_get_ready_rx_page(void)
{
	pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_usr_cnt]);
	
	if (prx_block->rx_gdma_own)
		return NULL;
	else{
		return prx_block->rx_addr;
	}
}

void sp_read_rx_page(u8 *dst, u32 length)
{
	pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_usr_cnt]);
	
	memcpy(dst, prx_block->rx_addr, length);
	prx_block->rx_gdma_own = 1;
	sp_rx_info.rx_usr_cnt++;
	if (sp_rx_info.rx_usr_cnt == SP_DMA_PAGE_NUM){
		sp_rx_info.rx_usr_cnt = 0;
	}
}

void sp_release_rx_page(void)
{
	pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_gdma_cnt]);
	
	if (sp_rx_info.rx_full_flag){
	}
	else{
		prx_block->rx_gdma_own = 0;
		sp_rx_info.rx_gdma_cnt++;
		if (sp_rx_info.rx_gdma_cnt == SP_DMA_PAGE_NUM){
			sp_rx_info.rx_gdma_cnt = 0;
		}
	}
}

u8 *sp_get_free_rx_page(void)
{
	pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_gdma_cnt]);
	
	if (prx_block->rx_gdma_own){
		sp_rx_info.rx_full_flag = 0;
		return prx_block->rx_addr;
	}
	else{
		DiagPrintf("full\n");
		sp_rx_info.rx_full_flag = 1;
		return sp_rx_info.rx_full_block.rx_addr;	//for audio buffer full case
	}
}

u32 sp_get_free_rx_length(void)
{
	pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_gdma_cnt]);

	if (sp_rx_info.rx_full_flag){
		return sp_rx_info.rx_full_block.rx_length;
	}
	else{
		return prx_block->rx_length;
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
	GDMA_SetSrcAddr(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_addr);
	GDMA_SetBlkSize(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_length>>2);
	
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, ENABLE);	
	sp_update_ppm_status(tx_length);	
}

void sp_rx_complete(void *Data)
{
	SP_GDMA_STRUCT *gs = (SP_GDMA_STRUCT *) Data;
	PGDMA_InitTypeDef GDMA_InitStruct;
	u32 rx_addr;
	u32 rx_length;
	
	GDMA_InitStruct = &(gs->SpRxGdmaInitStruct);
	
	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);

	sp_release_rx_page();
	rx_addr = (u32)sp_get_free_rx_page();
	rx_length = sp_get_free_rx_length();
	GDMA_SetDstAddr(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, rx_addr);
	GDMA_SetBlkSize(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, rx_length>>2);	
	
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, ENABLE);
}


void sp_update_ppm_status(u32 tx_length)
{	
	if (sp_ppm_conf.adj_en){
		sp_ppm_conf.adj_sum += sp_ppm_conf.adj_step*tx_length/4;
		if (sp_ppm_conf.adj_sum >= 1){
			sp_ppm_conf.adj_once = _TRUE;
			sp_ppm_conf.adj_sum -= 1;
		}
	}
	return tx_length;
}

void sp_set_dac_ppm(int clk_ppm)
{
	if (clk_ppm){
		sp_ppm_conf.adj_en = _TRUE;
		if (clk_ppm > 0){
			sp_ppm_conf.adj_dir = 1;
			sp_ppm_conf.adj_step = (float)clk_ppm/(float)1000000;
		}
		else{
			sp_ppm_conf.adj_dir = 0;
			sp_ppm_conf.adj_step = (float)(0-clk_ppm)/(float)1000000;
		}
		sp_ppm_conf.adj_sum = 0;
	}
	else{
		sp_ppm_conf.adj_en = 0;
	}
}

void sp_ppm_conf_timer_isr(void)
{
	static u8 toggle = 0;
	
	if (toggle){
		toggle = 0;
		sp_set_dac_ppm(100);
	}
	else{
		toggle = 1;
		sp_set_dac_ppm(-100);
	}
	xTimerChangePeriod(ppm_conf_timer, 2000, TIMER_MAX_DELAY);
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
		sp_tx_info.tx_block[i].tx_addr = sp_tx_buf+i*(SP_DMA_PAGE_SIZE+4);
		sp_tx_info.tx_block[i].tx_length = SP_DMA_PAGE_SIZE;
	}
}

static void sp_init_rx_variables(void)
{
	int i;

	sp_rx_info.rx_full_block.rx_addr = (u32)sp_full_buf;
	sp_rx_info.rx_full_block.rx_length = (u32)SP_FULL_BUF_SIZE;
	
	sp_rx_info.rx_gdma_cnt = 0;
	sp_rx_info.rx_usr_cnt = 0;
	sp_rx_info.rx_full_flag = 0;
	
	for(i=0; i<SP_DMA_PAGE_NUM; i++){
		sp_rx_info.rx_block[i].rx_gdma_own = 1;
		sp_rx_info.rx_block[i].rx_addr = sp_rx_buf+i*SP_DMA_PAGE_SIZE;
		sp_rx_info.rx_block[i].rx_length = SP_DMA_PAGE_SIZE;
	}
}

void example_audio_ppm_conf_thread(void* param)
{
	int i = 0;
	u32 buf[SP_DMA_PAGE_SIZE>>2];
	u32 tx_addr;
	u32 tx_length;
	u32 rx_addr;
	u32 rx_length;
	pSP_OBJ psp_obj = (pSP_OBJ)param;
	
	DiagPrintf("Audio ppm configuration demo begin......\n");

	ppm_conf_timer = xTimerCreate((signed const char *)"PPM_CONF_Timer",
		portMAX_DELAY, _FALSE, NULL, sp_ppm_conf_timer_isr);

	xTimerChangePeriod(ppm_conf_timer, 2000, TIMER_MAX_DELAY);
	
	sp_init_hal(psp_obj);
	
	sp_init_tx_variables();
	sp_init_rx_variables();

	/*configure Sport according to the parameters*/
	AUDIO_SP_StructInit(&SP_InitStruct);
	SP_InitStruct.SP_MonoStereo= psp_obj->mono_stereo;
	SP_InitStruct.SP_WordLen = psp_obj->word_len;

	AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);
	
	AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
	AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);
	AUDIO_SP_RdmaCmd(AUDIO_SPORT_DEV, ENABLE);
	AUDIO_SP_RxStart(AUDIO_SPORT_DEV, ENABLE);	

	rx_addr = (u32)sp_get_free_rx_page();
	rx_length = sp_get_free_rx_length();
	AUDIO_SP_RXGDMA_Init(0, &SPGdmaStruct.SpRxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_rx_complete, rx_addr, rx_length);	
	tx_addr = (u32)sp_get_ready_tx_page();
	tx_length = sp_get_ready_tx_length();
	AUDIO_SP_TXGDMA_Init(0, &SPGdmaStruct.SpTxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_tx_complete, tx_addr, tx_length);

	while(1){
		if (sp_get_free_tx_page() && sp_get_ready_rx_page()){
			sp_read_rx_page((u8 *)buf, SP_DMA_PAGE_SIZE);
			sp_write_tx_page((u8 *)buf, SP_DMA_PAGE_SIZE);
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
	mpu_init();
	app_mpu_nocache_init();

	sp_obj.sample_rate = SR_48K;
	sp_obj.word_len = WL_16;
	sp_obj.mono_stereo = CH_STEREO;
	sp_obj.direction = APP_AMIC_IN|APP_LINE_OUT;
	if(xTaskCreate(example_audio_ppm_conf_thread, ((const char*)"example_audio_ppm_conf_thread"), 512, (void *)(&sp_obj), tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		DiagPrintf("\n\r%s xTaskCreate(example_audio_ppm_conf_thread) failed", __FUNCTION__);

	vTaskStartScheduler();
	while(1){
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
}

