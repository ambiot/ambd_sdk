/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "ameba_soc.h"

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
	{_PA_21,	1}, /* row 7 */
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
	{60,			0x2A,		40,			40,			ENABLE},  /* Channel 0 */
	{500,		0x08,		250,			250,			DISABLE}, /* Channel 1 */
	{500,		0x08,		250,			250,			DISABLE}, /* Channel 2 */
	{500,		0x0b,		250,			250,			DISABLE}, /* Channel 3 */
};

static void app_keyscan_data_process(u32 ksdata)
{
	u32 row = (ksdata & BIT_KS_ROW_INDEX) >> 4;
	u32 col = (ksdata & BIT_KS_COL_INDEX) >> 0;
	u32 press = (ksdata & BIT_KS_PRESS_EVENT) >> 8;
	
	DiagPrintf("ksdata:%x (row:%x col:%x press:%x) \n", ksdata, row, col, press);
}

static void app_keyscan_irq_handler(void)
{
	u32 intr_status = KeyScan_GetINT(KEYSCAN_DEV); 
	u32 temp;
	u32 tempi;
	u32 ksdata[16];

	/*clear intr*/
	KeyScan_ClearINT(KEYSCAN_DEV, intr_status);
	
	if (intr_status & BIT_KS_SCAN_EVENT_INT_STATUS) { //auto cleared
	
		temp = KeyScan_GetDataNum(KEYSCAN_DEV);
		KeyScan_Read(KEYSCAN_DEV, ksdata, temp);

		DiagPrintf("SCAN_EVENT_INT FIFO Data:");
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
	}
}

static void app_keyscan_init(void)
{
	u32 dslp_wakeup = SOCPS_DsleepWakeStatusGet();
	u32 index = 0;
	u32 column_sel = 0;
	u32 row_sel = 0;

	for(index = 0; index < 8; index++) {
		if (KeyColumn[index].valid) {
			PAD_PullCtrl(KeyColumn[index].pinmux, GPIO_PuPd_NOPULL);
			Pinmux_Config(KeyColumn[index].pinmux, PINMUX_FUNCTION_KEYSCAN_COL);
			column_sel |= BIT(index);			
		}
	}
	
	for(index = 0; index < 8; index++) {
		if (KeyRow[index].valid) {
			PAD_PullCtrl(KeyRow[index].pinmux, GPIO_PuPd_UP);
			Pinmux_Config(KeyRow[index].pinmux, PINMUX_FUNCTION_KEYSCAN_ROW);
			row_sel |= BIT(index);			
		}
	}

	//DiagPrintf("app_keyscan_init column_sel:%08x, row_sel:%08x\n", column_sel, row_sel);

	/* keyscan not used */
	if ((column_sel == 0) || (row_sel == 0)) {
		return;
	}
	
	if (dslp_wakeup == FALSE) {
		KeyScan_InitTypeDef  KeyScan_InitStruct;

		KeyScan_StructInit(&KeyScan_InitStruct);

		KeyScan_InitStruct.KS_ClkDiv = 49; /* KEYSCAN_2M */
		KeyScan_InitStruct.KS_ColSel = column_sel;
		KeyScan_InitStruct.KS_RowSel = row_sel;
		KeyScan_InitStruct.KS_WorkMode = KS_EVENT_TRIGGER_MODE;
		KeyScan_InitStruct.KS_LimitLevel = 2;
		KeyScan_Init(KEYSCAN_DEV, &KeyScan_InitStruct);

		//KeyScan_RegDump();
		//KeyScan_INTConfig(KEYSCAN_DEV, BIT_KS_FIFO_FULL_INT_MSK| BIT_KS_ALL_RELEASE_INT_MSK, ENABLE);
		KeyScan_INTConfig(KEYSCAN_DEV, BIT_KS_ALL_RELEASE_INT_MSK | BIT_KS_SCAN_EVENT_INT_MSK, ENABLE);
		KeyScan_Cmd(KEYSCAN_DEV, ENABLE);
	}

	InterruptRegister((IRQ_FUN) app_keyscan_irq_handler, KEYSCAN_IRQ_LP, NULL, 7);
	InterruptEn(KEYSCAN_IRQ_LP, 7);
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
	app_keyscan_init();
	app_captouch_init();

	vTaskStartScheduler();
}
