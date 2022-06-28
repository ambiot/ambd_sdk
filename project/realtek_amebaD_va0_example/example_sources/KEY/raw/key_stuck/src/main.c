/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "ameba_soc.h"
#include "timers.h"

typedef struct
{
	u32 pinmux; /* PAx or PBx */
	u32 valid; /* 0 or 1 */
} KeyMatrix_TypeDef_App;

static KeyMatrix_TypeDef_App KeyRow[8] = 
{
	/* pinmux,	valid */
	{_PA_12,	1}, /* row 0 */
	{_PA_13,	1}, /* row 1 */
	{_PA_14,	1}, /* row 2 */
	{_PA_15,	1}, /* row 3 */
	{_PA_16,	1}, /* row 4 */
	{_PA_18,	0}, /* row 5 */
	{_PA_17,	0}, /* row 6 */
	{_PA_21, 0}, /* row 7 */
};

static KeyMatrix_TypeDef_App KeyColumn[8] =
{
	/* pinmux, 	valid */
	{_PA_26,	1}, /* Col 0 */
	{_PA_25,	1}, /* Col 1 */
	{_PA_19,	1}, /* Col 2 */
	{_PA_17,	1}, /* Col 3 */
	{_PA_18,	1}, /* Col 4 */
	{_PA_16,	0}, /* Col 5 */
	{_PA_15,	0}, /* Col 6 */
	{_PA_20,	1}, /* Col 7 */
};

static CapTouch_CHInitTypeDef CTCChan[4] =
{
	/*DiffThrehold, MbiasCurrent, ETCNNoiseThr, ETCPNoiseThr, CHEnable*/
	{60,			0x18,		30,			30,			ENABLE},  /* Channel 0 */
	{500,		0x08,		250,			250,			DISABLE}, /* Channel 1 */
	{500,		0x08,		250,			250,			DISABLE}, /* Channel 2 */
	{500,		0x0b,		250,			250,			DISABLE}, /* Channel 3 */
};

static u32 KS_ColSel = 0;
static u32 KS_RowSel = 0;
static u32 KS_RowDis = 0;
u32 g_KS_timeout_flag;
static TimerHandle_t app_keyscan_xTimers = NULL;
static void app_keyscan_init(u8 reset_status);

#define KEYSCAN_TIMEOUT_DELAY 10000 /*define key stuck timeout time*/

static void app_keyscan_data_process(u32 ksdata)
{
	u32 row = (ksdata & BIT_KS_ROW_INDEX) >> 4;
	u32 col = (ksdata & BIT_KS_COL_INDEX) >> 0;
	u32 press = (ksdata & BIT_KS_PRESS_EVENT) >> 8;
	
	DiagPrintf("ksdata:%x (row:%x col:%x press:%x) \n", ksdata, row, col, press);
}

static void app_keyscan_row_disable(u32 status)
{
	u32 index;

	if(TRUE == status) {
		for(index = 0; index < 8; index++) {
			if (KeyColumn[index].valid) {
				/*config column low to check which row stuck*/
				Pinmux_Config(KeyColumn[index].pinmux, PINMUX_FUNCTION_GPIO);
				GPIO_Direction(KeyColumn[index].pinmux, GPIO_Mode_OUT);	
				GPIO_WriteBit(KeyColumn[index].pinmux, GPIO_PIN_LOW);
			}
		}
		for(index = 0; index < 8; index++) {
			if (KeyRow[index].valid) {
				Pinmux_Config(KeyRow[index].pinmux, PINMUX_FUNCTION_GPIO);
				GPIO_Direction(KeyRow[index].pinmux, GPIO_Mode_IN);
				if(GPIO_PIN_LOW == GPIO_ReadDataBit(KeyRow[index].pinmux)) {
					KS_RowDis |= BIT(index);
					/*set stuck row pulldown to avoid power leakage*/
					PAD_PullCtrl(KeyRow[index].pinmux, GPIO_PuPd_DOWN);
				}
				Pinmux_Config(KeyRow[index].pinmux, PINMUX_FUNCTION_KEYSCAN_ROW);
			}
		}

		for(index = 0; index < 8; index++) {
			if (KeyColumn[index].valid) {
				PAD_PullCtrl(KeyColumn[index].pinmux, GPIO_PuPd_NOPULL);
				Pinmux_Config(KeyColumn[index].pinmux, PINMUX_FUNCTION_KEYSCAN_COL);
			}
		}
		KeyScan_SetColRow(KEYSCAN_DEV, KS_ColSel, (KS_RowSel & (~KS_RowDis)));

	} else {
		for(index = 0; index < 8; index++) {
			if (BIT(index) & KS_RowDis) {
				PAD_PullCtrl(KeyRow[index].pinmux, GPIO_PuPd_UP);
			}
		}
		KeyScan_SetColRow(KEYSCAN_DEV, KS_ColSel, KS_RowSel);
	}
}

static void app_keyscan_timeout_handler(void)
{
	pmu_release_wakelock(PMU_KEYSCAN_DEVICE);
	g_KS_timeout_flag = 1;
}

static void app_keyscan_timeout_init(void)
{
	app_keyscan_xTimers = xTimerCreate("Keyscan_Timeout_Timer", KEYSCAN_TIMEOUT_DELAY, pdFALSE, NULL, (TimerCallbackFunction_t)app_keyscan_timeout_handler);
	if(app_keyscan_xTimers == NULL)
		DiagPrintf("Keyscan_Timeout_Timer create error\n"); 
}

static void app_keyscan_irq_handler(void)
{
	u32 intr_status = KeyScan_GetINT(KEYSCAN_DEV); 
	u32 temp;
	u32 tempi;
	u32 ksdata[16];
	static u32 press_flag;
	portBASE_TYPE taskWokenstart = pdFALSE;
	portBASE_TYPE taskWokenstop = pdFALSE;
	/*clear intr*/
	KeyScan_ClearINT(KEYSCAN_DEV, intr_status);
	
	if (intr_status & BIT_KS_SCAN_EVENT_INT_STATUS) { //auto cleared
		SOCPS_AONWakeClear(BIT_KEYSCAN_WAKE_STS);
		temp = KeyScan_GetDataNum(KEYSCAN_DEV);
		KeyScan_Read(KEYSCAN_DEV, ksdata, temp);
		pmu_acquire_wakelock(PMU_KEYSCAN_DEVICE);
		if(0 == press_flag) {
			if (xTimerStartFromISR(app_keyscan_xTimers, &taskWokenstart) != pdPASS) {
				// The timer could not be set into the Active state.
				DiagPrintf("Failed to start timer");
			}
			portEND_SWITCHING_ISR(taskWokenstart);
			press_flag ++;
		}
		//DiagPrintf("SCAN_EVENT_INT FIFO Data:");
		for(tempi = 0; tempi < temp; tempi++) {
			app_keyscan_data_process(ksdata[tempi]);
		}
	}

	if (intr_status & BIT_KS_SCAN_FINISH_INT_STATUS) {
		DiagPrintf("KEYSCAN BIT_KS_SCAN_FINISH_INT_STATUS Intr\n");
	}

	if (intr_status & BIT_KS_ALL_RELEASE_INT_STATUS) {
		temp = KeyScan_GetDataNum(KEYSCAN_DEV);
		KeyScan_Read(KEYSCAN_DEV, ksdata, temp);
		
		DiagPrintf("ALL RELEASE \n");
		for(tempi = 0; tempi < temp; tempi++) {
			app_keyscan_data_process(ksdata[tempi]);
		}
		pmu_release_wakelock(PMU_KEYSCAN_DEVICE);
		
		xTimerStopFromISR(app_keyscan_xTimers, &taskWokenstop);
        	portEND_SWITCHING_ISR(taskWokenstop);

		g_KS_timeout_flag = 0;
		KS_RowDis = 0;
		press_flag = 0;
	}
}

static u32 app_keyscan_suspend(u32 expected_idle_time, void *param)
{
	/* To avoid gcc warning */
	( void ) expected_idle_time;
	( void ) param;

	if(g_KS_timeout_flag && (KEYSCAN_DEV->KS_CTRL & BIT_KS_BUSY_STATUS)) {
		DiagPrintf("ks dis\n");
		KeyScan_Cmd(KEYSCAN_DEV, DISABLE);
		app_keyscan_row_disable(TRUE);
		KeyScan_Cmd(KEYSCAN_DEV, ENABLE);
		return TRUE;
	}
	
	if(KEYSCAN_DEV->KS_CTRL & BIT_KS_BUSY_STATUS) {
		return FALSE;
	} else {
		g_KS_timeout_flag = 0;
	}

	/*reset keyscan for glitch issue*/
	if(SOCPS_AONWakeReason() & BIT_KEYSCAN_WAKE_STS) {
		SOCPS_AONWakeClear(BIT_KEYSCAN_WAKE_STS);
		DiagPrintf("ks reset\n");
		app_keyscan_init(TRUE);
	}

	return TRUE;
}

static u32 app_keyscan_resume(u32 expected_idle_time, void *param)
{
	/* To avoid gcc warning */
	( void ) expected_idle_time;
	( void ) param;

	if(SOCPS_AONWakeReason() & BIT_KEYSCAN_WAKE_STS) {
		pmu_set_sysactive_time(20);
	}
	
	if(g_KS_timeout_flag) {
		DiagPrintf("ks en\n");
		KeyScan_Cmd(KEYSCAN_DEV, DISABLE);
		app_keyscan_row_disable(FALSE);
		pmu_set_sysactive_time(20);
		KeyScan_Cmd(KEYSCAN_DEV, ENABLE);
	}
	return TRUE;
}

static void app_keyscan_init(u8 reset_status)
{
	u32 dslp_wakeup = SOCPS_DsleepWakeStatusGet();
	u32 index = 0;

	for(index = 0; index < 8; index++) {
		if (KeyColumn[index].valid) {
			if (FALSE == reset_status) {
				PAD_PullCtrl(KeyColumn[index].pinmux, GPIO_PuPd_NOPULL);
				Pinmux_Config(KeyColumn[index].pinmux, PINMUX_FUNCTION_KEYSCAN_COL);
			}
			KS_ColSel |= BIT(index);			
		}
	}
	
	for(index = 0; index < 8; index++) {
		if (KeyRow[index].valid) {
			if (FALSE == reset_status) {
				PAD_PullCtrl(KeyRow[index].pinmux, GPIO_PuPd_UP);
				Pinmux_Config(KeyRow[index].pinmux, PINMUX_FUNCTION_KEYSCAN_ROW);
			}
			KS_RowSel |= BIT(index);			
		}
	}

	DiagPrintf("app_keyscan_init column_sel:%08x, row_sel:%08x\n", KS_ColSel, KS_RowSel);

	/* keyscan not used */
	if ((KS_ColSel == 0) || (KS_RowSel == 0)) {
		return;
	}

	if ((dslp_wakeup == FALSE) || ((dslp_wakeup == TRUE) && (0 == KeyScan_GetDataNum(KEYSCAN_DEV)))) {
		KeyScan_InitTypeDef  KeyScan_InitStruct;

		/*reset keyscan when dslp keyscan wakeup while no key is scanned*/
		RCC_PeriphClockCmd_AON(APBPeriph_KEYSCAN, APBPeriph_KEYSCAN_CLOCK, DISABLE);
		RCC_PeriphClockCmd_AON(APBPeriph_KEYSCAN, APBPeriph_KEYSCAN_CLOCK, ENABLE);

		KeyScan_StructInit(&KeyScan_InitStruct);

		KeyScan_InitStruct.KS_ClkDiv = 49; /* KEYSCAN_2M */
		KeyScan_InitStruct.KS_ColSel = KS_ColSel;
		KeyScan_InitStruct.KS_RowSel = KS_RowSel;
		KeyScan_InitStruct.KS_WorkMode = KS_EVENT_TRIGGER_MODE;
		KeyScan_InitStruct.KS_LimitLevel = 2;
		KeyScan_Init(KEYSCAN_DEV, &KeyScan_InitStruct);

		//KeyScan_INTConfig(KEYSCAN_DEV, BIT_KS_FIFO_FULL_INT_MSK| BIT_KS_ALL_RELEASE_INT_MSK, ENABLE);
		KeyScan_INTConfig(KEYSCAN_DEV, BIT_KS_ALL_RELEASE_INT_MSK | BIT_KS_SCAN_EVENT_INT_MSK, ENABLE);
		KeyScan_Cmd(KEYSCAN_DEV, ENABLE);
	}

	if(FALSE == reset_status) {
		pmu_register_sleep_callback(PMU_KEYSCAN_DEVICE, (PSM_HOOK_FUN)app_keyscan_suspend, NULL, (PSM_HOOK_FUN)app_keyscan_resume, NULL);
		InterruptRegister((IRQ_FUN) app_keyscan_irq_handler, KEYSCAN_IRQ, NULL, 5);
		InterruptEn(KEYSCAN_IRQ, 5);
		app_keyscan_timeout_init();
	}
}

static void app_captouch_irq_handler(void)
{
	u8 ch;
	u32 IntStatus;
	
	IntStatus = CapTouch_GetISR(CAPTOUCH_DEV);
	CapTouch_INTClearPendingBit(CAPTOUCH_DEV, IntStatus);
	
	for(ch=0; ch<5; ch++) {
		if(IntStatus & CT_CHX_PRESS_INT(ch)) {
			DiagPrintf("Key	%x press \n",ch);
			pmu_set_sysactive_time(5);
			pmu_set_dsleep_active_time(10*1000); //10s lock
		}

		if(IntStatus & CT_CHX_RELEASE_INT(ch)) {
			DiagPrintf("Key	%x release \n", ch);
			pmu_set_sysactive_time(5);
			pmu_set_dsleep_active_time(10*1000); //10s lock
		}
	}

	if(IntStatus & BIT_CT_FIFO_OVERFLOW_INT) {
		DiagPrintf("BIT_CT_FIFO_OVERFLOW_INT \n");
	}
	
	if(IntStatus & BIT_CT_OVER_P_NOISE_THRESHOLD_INT) {		
		CapTouch_DbgDumpETC(CAPTOUCH_DEV, 0);
		
		DiagPrintf("BIT_CT_OVER_P_NOISE_THRESHOLD_INT \n");
		CapTouch_Cmd(CAPTOUCH_DEV, DISABLE);
		CapTouch_Cmd(CAPTOUCH_DEV, ENABLE);

		return;
	}
	
	/* when press it will come over and over ?? */
	if(IntStatus & BIT_CT_OVER_N_NOISE_THRESHOLD_INT) {
		//DiagPrintf("BIT_CT_OVER_N_NOISE_THRESHOLD_INT \n");
	}
}

static void app_captouch_init(void)
{
	u32 dslp_wakeup = SOCPS_DsleepWakeStatusGet();
	u32 temp = 0;
	u32 ch = 0;

	if (dslp_wakeup == FALSE) {
		CapTouch_InitTypeDef Touch_InitStruct;

		CapTouch_StructInit(&Touch_InitStruct);

		_memcpy((void*)Touch_InitStruct.CT_Channel, (void*)CTCChan, 4 * sizeof(CapTouch_CHInitTypeDef));

		for (ch = 0; ch < 4; ch++) {
			if (CTCChan[ch].CT_CHEnable == ENABLE) {
				PAD_PullCtrl((_PB_4 + ch), GPIO_PuPd_NOPULL);
			}
		}
		
		CapTouch_Init(CAPTOUCH_DEV, &Touch_InitStruct);
		CapTouch_Cmd(CAPTOUCH_DEV, ENABLE);
		CapTouch_INTConfig(CAPTOUCH_DEV, BIT_CT_ALL_INT_EN, ENABLE);

		//DelayMs(10);
		//CapTouch_DbgDumpETC(CAPTOUCH_DEV, 0);
	}
	
	/* Register interrupt Callback function */
	InterruptRegister((IRQ_FUN) app_captouch_irq_handler, CTOUCH_IRQ_LP, (u32)NULL, 10);
	InterruptEn(CTOUCH_IRQ_LP, 10);

	/* enable cap-touch wakeup */
	SOCPS_SetWakeEventAON(BIT_CAPTOUCH_WAKE_MSK, ENABLE);
	/* fix boot reason issue, when cap-touch wakeup */
	temp = HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_AON_PM_OPT);
	temp &= ~BIT_AON_PMC_EN_SNOZ2NORM;
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_AON_PM_OPT, temp);

	//DiagPrintf("km4 app_captouch_init dslp_wakeup:%x \n", dslp_wakeup);
}

void main(void)
{
	app_keyscan_init(FALSE);
	app_captouch_init();

	pmu_release_wakelock(PMU_OS);
	vTaskStartScheduler();
}
