#include "ameba_soc.h"
#include "main.h"


void app_captouch_init(void);
void app_keyscan_init(u8 reset_status);

void app_dslp_wake(void)
{
	u32 aon_wake_event = SOCPS_AONWakeReason();

	DBG_8195A("app_dslp_wake %x \n", aon_wake_event);

	if(BIT_GPIO_WAKE_STS & aon_wake_event) {
		DBG_8195A("DSLP GPIO wakeup %x\n", SOCPS_WakePinCheck());
	}

	if(BIT_AON_WAKE_TIM0_STS & aon_wake_event) {
		//SOCPS_AONTimerCmd(DISABLE);
		DBG_8195A("DSLP Aontimer wakeup \n");
	}

	if(BIT_RTC_WAKE_STS & aon_wake_event) {
		DBG_8195A("DSLP RTC wakeup \n");
	}

	if(BIT_DLPS_TSF_WAKE_STS & aon_wake_event) {
		DBG_8195A("DSLP TSF wakeup \n");
	}
	
	if(BIT_KEYSCAN_WAKE_STS & aon_wake_event) {
		DBG_8195A("DSLP KS wakeup\n");
	}

	if(BIT_CAPTOUCH_WAKE_STS & aon_wake_event) {
		DBG_8195A("DSLP Touch wakeup\n");
	}

	km4_boot_on();

	//SOCPS_AONWakeClear(BIT_ALL_WAKE_STS);
}


void app_init_debug(void)
{
	u32 debug[4];

	debug[LEVEL_ERROR] = BIT(MODULE_BOOT) | BIT(MODULE_EFUSE);
	debug[LEVEL_WARN]  = 0x0;
	debug[LEVEL_INFO]  = BIT(MODULE_BOOT);// | BIT(MODULE_EFUSE);
	debug[LEVEL_TRACE] = 0x0;

	debug[LEVEL_ERROR] = 0xFFFFFFFF;

	LOG_MASK(LEVEL_ERROR, debug[LEVEL_ERROR]);
	LOG_MASK(LEVEL_WARN, debug[LEVEL_WARN]);
	LOG_MASK(LEVEL_INFO, debug[LEVEL_INFO]);
	LOG_MASK(LEVEL_TRACE, debug[LEVEL_TRACE]);

	//DBG_PRINTF(MODULE_EFUSE, LEVEL_INFO, "app_init_debug: %x:%x:%x:%x\n",debug[0], debug[1], debug[2], debug[3]);
	//DBG_PRINTF(MODULE_EFUSE, LEVEL_ERROR, "app_init_debug: %x:%x:%x:%x\n",debug[0], debug[1], debug[2], debug[3]);

}

/* audio share pad, it need audio LDO enabled */
/* if not these pad can not work when pinmux to GPIO */
VOID app_audio_pad_enable(VOID)
{
	u32 temp = 0;

	/* enable Audio & GPIO shared PAD */
	//0x4800_0208[28] = 1'b1
	temp = HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_LP_FUNC_EN0);
	temp |= BIT_SYS_AMACRO_EN;
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_LP_FUNC_EN0, temp);

	//0x4800_0344[9] = 1'b1: £¨1: Enable Audio pad function, 0: disable£©
	temp = HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_AUDIO_SHARE_PAD_CTRL);
	temp |= BIT_LSYS_AC_ANA_PORB;
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_AUDIO_SHARE_PAD_CTRL, temp);

	/* When Audio Pad(GPIOD_0~6) used as GPIO, output voltage can reach 3.064V(A-Cut)/3.3V(B-Cut), */
	/* which can be configured by 0x4800_0344[7:1] */
	SOCPS_AudioLDO(ENABLE);
}

VOID app_pmu_init(VOID)
{
	u32 Temp;
	
	if (BKUP_Read(BKUP_REG0) & BIT_SW_SIM_RSVD){
		return;
	}

	pmu_set_sleep_type(SLEEP_CG);
	pmu_acquire_wakelock(PMU_OS);
	pmu_tickless_debug(ENABLE);

	//5: 0.9V
	//4: 0.85
	//3: 0.8V
	//2: 0.75V
	//1: 0.7V can not work normal
	//setting switch regulator PFM mode voltage 
	Temp=HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_SWR_PSW_CTRL);
	Temp &= 0x00FF0000;
#ifdef CONFIG_VERY_LOW_POWER
	Temp |= 0x3F007532;//8:1.05v 7:1.0v 6:0.95v 5:0.9v 4 stage waiting time 500us
	//Temp |= 0x7F007532;//8:1.05v 7:1.0v 6:0.95v 5:0.9v 4 stage waiting time 2ms
#else
	Temp |= 0x3F007654;//>0.81V is safe for MP
	//Temp |= 0x7F007654;//>0.81V is safe for MP
#endif
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_SWR_PSW_CTRL,Temp);

	/* Enable PFM to PWM delay to fix voltage peak issue when PFM=>PWM */
	Temp=HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_LP_SWR_CTRL1);
	Temp |= BIT_SWR_ENFPWMDELAY_H;
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_LP_SWR_CTRL1,Temp);

	/* Set SWR ZCD & Voltage */
	Temp=HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_SYS_EFUSE_SYSCFG1);
	if (wifi_config.wifi_ultra_low_power) {
		Temp &= ~(0x0f);//SWR @ 1.05V
		Temp |= (0x07);
		Temp &= ~BIT_MASK_SWR_REG_ZCDC_H; /* reg_zcdc_H: EFUSE[5]BIT[6:5] 00 0.1u@PFM */ /* 4uA @ sleep mode */
	} else {
		/* 2mA higher in active mode */
		Temp &= ~BIT_MASK_SWR_REG_ZCDC_H; /* reg_zcdc_H: EFUSE[5]BIT[6:5] 00 0.1u@PFM */ /* 4uA @ sleep mode */
	}
	/*Mask OCP setting, or some chip won't wake up after sleep*/
	//Temp &= ~BIT_MASK_SWR_OCP_L1;
	//Temp |= (0x03 << BIT_SHIFT_SWR_OCP_L1); /* PWM:600 PFM: 250, default OCP: BIT[10:8] 100 */
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_SYS_EFUSE_SYSCFG1,Temp);

	/* LDO & SWR switch time when DSLP, default is 0x200=5ms (unit is 1cycle of 100K=10us) */
	Temp=HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_AON_PMC_CTRL);
	Temp &= ~(BIT_AON_MASK_PMC_PSW_STABLE << BIT_AON_SHIFT_PMC_PSW_STABLE);
	Temp |= (0x60 << BIT_AON_SHIFT_PMC_PSW_STABLE);//set to 960us
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_AON_PMC_CTRL,Temp);	

	/* shutdown internal test pad GPIOF9 to fix wowlan power leakage issue */
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_GPIO_F9_PAD_CTRL, 0x0000DC00);	
}

VOID app_loguart_lowpower(VOID)
{
	RCC_PeriphClockSource_UART(UART2_DEV, UART_RX_CLK_OSC_LP);
	
	UART_MonitorParaConfig(UART2_DEV, 100, ENABLE);
	UART_RxMonitorCmd(UART2_DEV, ENABLE);
	UART_LPRxBaudSet(UART2_DEV, 115200, 2000000);
	UART_RxCmd(UART2_DEV, ENABLE);
}

void app_rtc_init(void)
{
	RTC_InitTypeDef RTC_InitStruct_temp;
	RTC_AlarmTypeDef RTC_AlarmStruct_temp;
	RTC_TimeTypeDef RTC_TimeStruct;
	u32 dslp_wakeup = SOCPS_DsleepWakeStatusGet();

	if (dslp_wakeup == FALSE) {
		RCC_PeriphClockSource_RTC(0);
		RTC_StructInit(&RTC_InitStruct_temp);

		//RTC_InitStruct_temp.RTC_SynchPrediv = (u32)0x03; /* 256 /4 = 128Hz*/
		
		/* Initialize the RTC_AsynchPrediv member */
		//RTC_InitStruct_temp.RTC_AsynchPrediv = (u32)1; /* 32768 /2 = 16K */
		/* Initialize the RTC_SynchPrediv member */
		//RTC_InitStruct_temp.RTC_SynchPrediv = (u32)0; /* 256 /256 = 16K*/
		
		RTC_Init(&RTC_InitStruct_temp);

		/* 32760 need add need add 15 cycles (256Hz) every 4 min*/
		//RTC_SmoothCalibConfig(RTC_CalibSign_Positive, 15,
		//	RTC_CalibPeriod_4MIN, RTC_Calib_Enable);

		/* set time when power on */
		RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
		if (RTC_TimeStruct.RTC_Seconds == 0 && RTC_TimeStruct.RTC_Minutes == 0) {
			RTC_TimeStructInit(&RTC_TimeStruct);
			RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
		}
			
		/* set alarm */
		RTC_AlarmStructInit(&RTC_AlarmStruct_temp); 		
		RTC_AlarmStruct_temp.RTC_AlarmTime.RTC_Days = 1;
		RTC_AlarmStruct_temp.RTC_AlarmTime.RTC_Hours = 1;
		RTC_AlarmStruct_temp.RTC_AlarmTime.RTC_Minutes = 1;
		RTC_AlarmStruct_temp.RTC_AlarmTime.RTC_Seconds = 30;
		RTC_AlarmStruct_temp.RTC_AlarmMask = RTC_AlarmMask_Hours | RTC_AlarmMask_Minutes;
		RTC_AlarmStruct_temp.RTC_Alarm2Mask = RTC_Alarm2Mask_Days;
		
		RTC_SetAlarm(RTC_Format_BIN, &RTC_AlarmStruct_temp);
		if (ps_config.km0_rtc_calibration) {
			RTC_32KAutoCalibConfig(1, RTC_32K_AUTOCAL_MINUTES);
		}
		//RTC_AlarmCmd(DISABLE);
	}

	//InterruptRegister(app_rtc_irq_handler, RTC_IRQ, NULL, 2);
	//InterruptEn(RTC_IRQ, 2);
}




//default main
int main(void)
{
	//u32 Temp = 0;

	InterruptRegister((IRQ_FUN)IPC_INTHandler, IPC_IRQ_LP, (u32)IPCM4_DEV, 2);
	InterruptEn(IPC_IRQ_LP, 2);

	//app_init_debug();

	if (ps_config.km0_osc2m_close == FALSE) {
		app_loguart_lowpower();
	}
	shell_init_ram();

	app_pmu_init();
	/*switch shell control to KM4 */
	InterruptDis(UART_LOG_IRQ_LP);

	if(SOCPS_DsleepWakeStatusGet() == TRUE) {
		app_dslp_wake();
	} else {
		km4_flash_highspeed_init();
#if !defined(CONFIG_WIFI_FW_VERIFY)
		km4_boot_on();
#endif
	}

	/* should init after SOCPS_AONWakeReason, or wake reason will be lost */
	app_rtc_init();
	
#if CONFIG_WIFI_FW_EN
	if ((BKUP_Read(0) & BIT_WIFI_ENABLE) != 0) {
		wifi_FW_init_ram();
	}
#endif
	
	app_audio_pad_enable();

	app_init_debug();
	//DiagPrintfD("M0U:%d\n", RTIM_GetCount(TIMM05));

	//Enable Schedule
	vTaskStartScheduler();
}

