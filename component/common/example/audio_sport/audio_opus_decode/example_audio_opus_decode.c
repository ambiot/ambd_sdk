#include "opus.h"
#include "opus_types.h"
#include "opus_private.h"
#include "opus_multistream.h"
#include "ameba_soc.h"
#include <platform/platform_stdlib.h>
#include "platform_opts.h"
#include "ogg/ogg.h"
#include "internal.h"
#include "opusfile.h"
#include "rl6548.h"
#include "ready_to_convert0.h"
//#include "ready_to_convert1.h"
//#include "ready_to_convert2.h"
//#include "ready_to_convert3.h"

#ifdef CONFIG_EXAMPLE_AUDIO_OPUS_DECODE
#define NUM_CHANNELS CH_STEREO
#define SAMPLING_FREQ SR_48K
#define SP_DMA_PAGE_SIZE 1920
#define SP_DMA_PAGE_NUM 4
#define SP_ZERO_BUF_SIZE 128

typedef struct {
	u32 sample_rate;
	u32 word_len;
	u32 mono_stereo;
	u32 direction;
	
}SP_OBJ, *pSP_OBJ;

typedef struct {
    u8 tx_gdma_own;
    u32 tx_addr;
    u32 tx_length;
}TX_BLOCK, *pTX_BLOCK;

typedef struct {
    TX_BLOCK tx_block[SP_DMA_PAGE_NUM];
    TX_BLOCK tx_zero_block;
    u8 tx_gdma_cnt;
    u8 tx_usr_cnt;
    u8 tx_empty_flag;
}SP_TX_INFO, *pSP_TX_INFO;

typedef struct {
    GDMA_InitTypeDef           SpTxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
    GDMA_InitTypeDef           SpRxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef    
}SP_GDMA_STRUCT, *pSP_GDMA_STRUCT;

static SP_OBJ sp_obj;
static SP_InitTypeDef SP_InitStruct;
static SP_GDMA_STRUCT SPGdmaStruct;
static SP_OBJ sp_obj;
static SP_TX_INFO sp_tx_info;
static u8 sp_tx_buf[SP_DMA_PAGE_SIZE*SP_DMA_PAGE_NUM];
static u8 sp_zero_buf[SP_ZERO_BUF_SIZE];

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
	ptx_block-> tx_gdma_own = 1;
	ptx_block -> tx_length = length;
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



static void sp_init_hal(pSP_OBJ psp_obj)
{
	u32 div;
	
	PLL_I2S_Set(ENABLE);		//enable 98.304MHz PLL. needed if fs=8k/16k/32k/48k/96k
	PLL_PCM_Set(ENABLE);		//enable 45.1584MHz PLL. needed if fs=44.1k/8.2k
	PLL_Sel(PLL_I2S);
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
	CODEC_SetVolume(80, 80);
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

void opus_audio_opus_decode_thread(void* param){
	u32 tx_addr;
	u32 tx_length;
	pSP_OBJ psp_obj = (pSP_OBJ)param;
	int *ptx_buf;
	sp_init_hal(psp_obj);
	
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

	int error = 0;
	int op_link = 0;
	int op_index = 0;
	int num1 = 0;
	int num2 = 0;
	int is_opus_or_not = 0;

	for(int i =0; i < 1; i++){
		int tim1 = 0;
		int tim2 = 0;
		int total_tim = 0;
		OggOpusFile* ogg_file1;
	if(i == 0){
		printf("at 0\n");
		ogg_file1 = op_open_memory(ready_to_convert0, sizeof(ready_to_convert0), &error);
	}

	if(i == 1){
		printf("at 1\n");
	//ogg_file1 = op_open_memory(ready_to_convert1, sizeof(ready_to_convert1), &error);
	
	}
	if(i == 2){
		printf("at 2\n");
	//	ogg_file1 = op_open_memory(ready_to_convert2, sizeof(ready_to_convert2), &error);
	}
	if(i == 3){
		printf("at %d\n", i);
	//	ogg_file1 = op_open_memory(ready_to_convert3, sizeof(ready_to_convert3), &error);		
	}
	opus_int16 pcm[5600] = {0};
	for(; ;){
		u8 * ptr;
		tim1 = RTIM_GetCount(TIM0);
		num1 = op_read(ogg_file1, pcm, 5600, NULL);
		tim2 = RTIM_GetCount(TIM0);
		total_tim += (tim2- tim1)*32;
		if(num1 == 0)
			break;
	
		ptr = (u8*)pcm;	
		retry:
		ptx_buf = (int*)sp_get_free_tx_page();
		if(ptx_buf){
		    	sp_write_tx_page(ptr, num1*2);
	
			retry2:
			if (sp_get_free_tx_page()){
				sp_write_tx_page(ptr+num1*2, num1*2);
			}
			else{
				vTaskDelay(1);
				goto retry2;
			}
				
		}else{
			vTaskDelay(1);
			goto retry;
		}
		
	}
		printf("time_total is %d\n", total_tim);
		op_free(ogg_file1);
    }
    vTaskDelete(NULL);
}


void example_audio_opus_decode(void)
{
    RTIM_Cmd(TIM0, ENABLE);
	sp_obj.mono_stereo = NUM_CHANNELS;
	sp_obj.sample_rate = SAMPLING_FREQ;
	sp_obj.word_len = WL_16;
	sp_obj.direction = APP_LINE_OUT;
	if(xTaskCreate(opus_audio_opus_decode_thread, ((const char*)"opus_audio_opus_decode_thread"), 10000, (void *)(&sp_obj), tskIDLE_PRIORITY + 1, NULL) != pdPASS)
	printf("\n\r%s xTaskCreate(opus_audio_opus_decode_thread) failed", __FUNCTION__);
}
#endif