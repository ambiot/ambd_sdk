#include "example_audio_recorder.h"
#include "platform_opts.h"
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>
#include <disk_if/inc/sdcard.h>
#include <platform_stdlib.h>
#include "osdep_service.h"
#include "rl6548.h"
#ifdef CONFIG_EXAMPLE_AUDIO_RECORDER
SRAM_NOCACHE_DATA_SECTION static u8 sp_rx_buf[SP_DMA_PAGE_SIZE*SP_DMA_PAGE_NUM];

static xSemaphoreHandle record_start_sema = NULL;
static xSemaphoreHandle record_end_sema = NULL;
static xSemaphoreHandle save_start_sema = NULL;
static xSemaphoreHandle save_end_sema = NULL;

static volatile u8 record_flag;
static u32 record_button = _PA_22;		//record button
static _timerHandle record_det_timer = NULL;


static u8 sp_full_buf[SP_FULL_BUF_SIZE];
static SP_InitTypeDef SP_InitStruct;
static SP_GDMA_STRUCT SPGdmaStruct;
static SP_OBJ sp_obj;
static SP_RX_INFO sp_rx_info;

static u8 *sp_get_ready_rx_page(void)
{
	pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_usr_cnt]);
	
	if (prx_block->rx_gdma_own)
		return NULL;
	else{
		return (u8*)prx_block->rx_addr;
	}
}

static void sp_read_rx_page(u8 *dst, u32 length)
{
	pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_usr_cnt]);

	memcpy(dst, (void const*)prx_block->rx_addr, length);	
	prx_block->rx_gdma_own = 1;
	sp_rx_info.rx_usr_cnt++;
	if (sp_rx_info.rx_usr_cnt == SP_DMA_PAGE_NUM){
		sp_rx_info.rx_usr_cnt = 0;
	}
}

static void sp_release_rx_page(void)
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

static u8 *sp_get_free_rx_page(void)
{
	pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_gdma_cnt]);
	
	if (prx_block->rx_gdma_own){
		sp_rx_info.rx_full_flag = 0;
		return (u8*)prx_block->rx_addr;
	}
	else{
		sp_rx_info.rx_full_flag = 1;
		return (u8*)sp_rx_info.rx_full_block.rx_addr;	//for audio buffer full case
	}
}

static u32 sp_get_free_rx_length(void)
{
	pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_gdma_cnt]);

	if (sp_rx_info.rx_full_flag){
		return sp_rx_info.rx_full_block.rx_length;
	}
	else{
		return prx_block->rx_length;
	}
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

	PAD_CMD(_PA_0, DISABLE);
	PAD_CMD(_PA_1, DISABLE);
	PAD_CMD(_PA_2, DISABLE);
	PAD_CMD(_PA_3, DISABLE);
	PAD_CMD(_PA_4, DISABLE);
	PAD_CMD(_PA_5, DISABLE);
	PAD_CMD(_PA_6, DISABLE);

	PAD_CMD(_PB_28, DISABLE);
	PAD_CMD(_PB_29, DISABLE);
	PAD_CMD(_PB_30, DISABLE);
	PAD_CMD(_PB_31, DISABLE);

	/*codec init*/
	//CODEC_Init(psp_obj->sample_rate, psp_obj->word_len, psp_obj->mono_stereo, psp_obj->direction);
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
		sp_rx_info.rx_block[i].rx_addr = (u32)(sp_rx_buf+i*SP_DMA_PAGE_SIZE);
		sp_rx_info.rx_block[i].rx_length = SP_DMA_PAGE_SIZE;
	}
}

static void sp_rx_complete(void *data)
{
	SP_GDMA_STRUCT *gs = (SP_GDMA_STRUCT *) data;
	PGDMA_InitTypeDef GDMA_InitStruct;
	u32 rx_addr;
	u32 rx_length;
	char *pbuf;
	
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

void record_det_isr(void)
{

	xTimerChangePeriod(record_det_timer, RECORD_DET_TO, TIMER_MAX_DELAY);
}

void record_det_timer_isr(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;	

	if (GPIO_ReadDataBit(record_button) == GPIO_PIN_LOW)
	{
		record_flag = 1;
		xSemaphoreGiveFromISR(record_start_sema, &xHigherPriorityTaskWoken);
		DBG_8195A("record start\n");
	}	
	else
	{
		record_flag = 0;
		xSemaphoreGiveFromISR(record_end_sema, &xHigherPriorityTaskWoken);
		DBG_8195A("record end\n");
	}
}

static void example_audio_init()
{
	printf("audio initial\r\n");

	pSP_OBJ psp_obj = &sp_obj;

	psp_obj->mono_stereo= CH_MONO;
	psp_obj->sample_rate = SR_16K;
	psp_obj->word_len = WL_16;
	psp_obj->direction = APP_AMIC_IN;	 
	sp_init_hal(psp_obj);
	
	sp_init_rx_variables();

	/*configure Sport according to the parameters*/
	AUDIO_SP_StructInit(&SP_InitStruct);
	SP_InitStruct.SP_MonoStereo= psp_obj->mono_stereo;
	SP_InitStruct.SP_WordLen = psp_obj->word_len;

	AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);
	u32 Tmp;

	Tmp = HAL_READ32(AUDIO_SPORT_REG_BASE, 0x4);
	Tmp |= ((u32)0x3) << 28;
	HAL_WRITE32(AUDIO_SPORT_REG_BASE, 0x4, Tmp);

	printf("audio init finish\r\n");
}

void record_button_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct_temp;

	record_det_timer = xTimerCreate((signed const char *)"RECORD_DET_Timer",
		portMAX_DELAY, _FALSE, NULL, (TimerCallbackFunction_t)record_det_timer_isr);

	//record_button pin configuration
	GPIO_INTConfig(record_button, DISABLE);	
	GPIO_Direction(record_button, GPIO_Mode_IN);
	if (GPIO_ReadDataBit(record_button) == GPIO_PIN_LOW)
	{
		record_flag = 1;
		DBG_8195A("init state: record start\n");
	}
	else
	{
		record_flag = 0;
		DBG_8195A("init state: record end\n");
	}
	GPIO_InitStruct_temp.GPIO_Pin = record_button;
	GPIO_InitStruct_temp.GPIO_Mode = GPIO_Mode_INT;
	GPIO_InitStruct_temp.GPIO_ITTrigger= GPIO_INT_Trigger_EDGE;
	GPIO_InitStruct_temp.GPIO_ITPolarity = GPIO_INT_POLARITY_ACTIVE_LOW;
	GPIO_InitStruct_temp.GPIO_ITDebounce = GPIO_INT_DEBOUNCE_ENABLE;
	GPIO_Init(&GPIO_InitStruct_temp);
	GPIO_UserRegIrq(record_button, (void*)record_det_isr, NULL);
	GPIO_INTMode(record_button, ENABLE, GPIO_INT_Trigger_BOTHEDGE, GPIO_INT_POLARITY_ACTIVE_LOW, GPIO_INT_DEBOUNCE_ENABLE);
	InterruptRegister(GPIO_INTHandler, GPIOA_IRQ, (u32)GPIOA_BASE, 10);		
	InterruptEn(GPIOA_IRQ, 10);
	GPIO_INTConfig(record_button, ENABLE);
}

void example_audio_save_thread(void* param)
{
	WAVE_HEADER w_header;
	int drv_num = 0;
	FATFS 	m_fs;
	FIL		m_file;  
	char	logical_drv[4]; //root diretor
	u32 bw;
	int res;
	u32 buf[SP_DMA_PAGE_SIZE>>2];
	u32 file_size;
	u32 file_cnt = 0;
	char abs_path_op[32]; //Path to output file
	const char *outfile = "record";

	strcpy(w_header.w_header.fccID, "RIFF");  
	strcpy(w_header.w_header.fccType, "WAVE");
	strcpy(w_header.w_fmt.fccID, "fmt ");
	w_header.w_fmt.dwSize=16;
	w_header.w_fmt.wFormatTag=1;
	w_header.w_fmt.wChannels=1;
	w_header.w_fmt.dwSamplesPerSec=16000;
	w_header.w_fmt.dwAvgBytesPerSec=w_header.w_fmt.dwSamplesPerSec*2;
	w_header.w_fmt.wBlockAlign=2;
	w_header.w_fmt.uiBitsPerSample=16; 
	strcpy(w_header.w_data.fccID, "data");

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


	while(1) {
		//while(xSemaphoreTake(save_start_sema, portMAX_DELAY) != pdTRUE);
		while(!record_flag);
		DBG_8195A("enter save process\n");
		memset(abs_path_op, 0x00, sizeof(abs_path_op));
		strcpy(abs_path_op, logical_drv);
		sprintf(&abs_path_op[strlen(abs_path_op)],"%s_%d.wav", outfile, file_cnt);
		res = f_open(&m_file, abs_path_op, FA_OPEN_ALWAYS | FA_READ | FA_WRITE|FA_CREATE_ALWAYS);  // open read and write file
		if(res != FR_OK){
			printf("Open source file %(s) fail.\n", outfile);
			goto umount;
		}

		res = f_write(&m_file, (void *)(&w_header), sizeof(w_header), &bw);
		if (res || (bw != sizeof(w_header))){
			f_lseek(&m_file, 0); 
			printf("Write error.\n");
			goto exit;
		}
		file_size = sizeof(w_header);
		
		//while(xSemaphoreTake(save_end_sema, portMAX_DELAY) != pdTRUE){
		while(record_flag){
			if (sp_get_ready_rx_page()){
				sp_read_rx_page((u8 *)buf, SP_DMA_PAGE_SIZE);
				res = f_write(&m_file, buf, SP_DMA_PAGE_SIZE, (u32*)&bw);
				if(res || (bw != SP_DMA_PAGE_SIZE)){
					f_lseek(&m_file, 0); 
					printf("Write error.\n");
					goto exit;
				}
				file_size += SP_DMA_PAGE_SIZE;
			}
			else{
				vTaskDelay(1);
			}		
		}

		f_lseek(&m_file, 4);
		file_size -= 8;
		res = f_write(&m_file, (void *)(&file_size), 4, &bw);
		if (res || (bw != 4)){
			f_lseek(&m_file, 0); 
			printf("Write error.\n");
			goto exit;
		}
		file_size -= (sizeof(w_header)-8);
		f_lseek(&m_file, sizeof(w_header)-4);
		res = f_write(&m_file, (void *)(&file_size), 4, &bw);
		if (res || (bw != 4)){
			f_lseek(&m_file, 0); 
			printf("Write error.\n");
			goto exit;
		}
		res = f_close(&m_file);
		if(res){
			printf("close file (%s) fail.\n", outfile);
		}
		file_size = 0;
		file_cnt++;
	}

exit:
	// close m_file
	res = f_close(&m_file);
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

void example_audio_recorder_thread(void* param)
{
	u32 rx_addr;
	u32 rx_length;

	vSemaphoreCreateBinary(record_start_sema);
	vSemaphoreCreateBinary(record_end_sema);
	vSemaphoreCreateBinary(save_start_sema);
	vSemaphoreCreateBinary(save_end_sema);
	

	printf("Audio codec recorder demo begin......\n");

	example_audio_init();

	record_button_init();

	if(xTaskCreate(example_audio_save_thread, ((const char*)"example_audio_save_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate failed", __FUNCTION__);

	while(1) {
		//while(xSemaphoreTake(record_start_sema, portMAX_DELAY) != pdTRUE);
		while(!record_flag);
		DBG_8195A("enter record process\n");

		CODEC_Init(sp_obj.sample_rate, sp_obj.word_len, sp_obj.mono_stereo, sp_obj.direction);	
		
		AUDIO_SP_RdmaCmd(AUDIO_SPORT_DEV, ENABLE);
		AUDIO_SP_RxStart(AUDIO_SPORT_DEV, ENABLE);
		
		rx_addr = (u32)sp_get_free_rx_page();
		rx_length = sp_get_free_rx_length();
		AUDIO_SP_RXGDMA_Init(0, &SPGdmaStruct.SpRxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_rx_complete, (u8*)rx_addr, rx_length);	
		//xSemaphoreGive(save_start_sema);
		//while(xSemaphoreTake(record_end_sema, portMAX_DELAY) != pdTRUE);
		while(record_flag);
		AUDIO_SP_RdmaCmd(AUDIO_SPORT_DEV, DISABLE);
		AUDIO_SP_RxStart(AUDIO_SPORT_DEV, DISABLE);
		
		GDMA_ClearINT(SPGdmaStruct.SpRxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpRxGdmaInitStruct.GDMA_ChNum);
		GDMA_Cmd(SPGdmaStruct.SpRxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpRxGdmaInitStruct.GDMA_ChNum, DISABLE);
		GDMA_ChnlFree(SPGdmaStruct.SpRxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpRxGdmaInitStruct.GDMA_ChNum);
		
		sp_init_rx_variables();
		//xSemaphoreGive(save_end_sema);
	}
}

void example_audio_recorder(void)
{
	if(xTaskCreate(example_audio_recorder_thread, ((const char*)"example_audio_recorder_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate failed", __FUNCTION__);
}
#endif
