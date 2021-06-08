
#include "ameba_soc.h"

#define AON_TIMER_WAKEUP	0
#define AON_WAKEPIN_WAKEUP	1
#define RTC_WAKEUP			2
#define KYESCAN_WAKEUP		3
#define CAPTOUCH_WAKEUP		4

static u32 wakeup_source = AON_TIMER_WAKEUP;		//choose wake up source, user should enble the source in rtl8721dlp_sleepcfg.c
static u32 dslptime = 10000;

KM4SLEEP_ParamDef DSLP_Para;

static void app_dslp_wake(void)
{
	u32 aon_wake_event = SOCPS_AONWakeReason();

	DBG_8195A("hs app_dslp_wake %x \n", aon_wake_event);

	if(BIT_GPIO_WAKE_STS & aon_wake_event) {
		DBG_8195A("DSLP AonWakepin wakeup, wakepin %x\n", SOCPS_WakePinCheck());
	}

	if(BIT_AON_WAKE_TIM0_STS & aon_wake_event) {
		SOCPS_AONTimerCmd(DISABLE);
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

	SOCPS_AONWakeClear(BIT_ALL_WAKE_STS);
}

void main(void)
{
	/* register IPC interrupt */	
	InterruptRegister(IPC_INTHandler, IPC_IRQ, (u32)IPCM0_DEV, 5);
	InterruptEn(IPC_IRQ, 5);

	/* init console */
	shell_init_ram();
	ipc_table_init();

	/*open log of DBG_8195A()*/
	DBG_ERR_MSG_ON(MODULE_MISC);

	if(TRUE == SOCPS_DsleepWakeStatusGet()) {
		app_dslp_wake();
	}

	app_keyscan_init(FALSE); /* 5uA */
	app_captouch_init(); /* 1uA */

	DSLP_Para.sleep_time = 0;

	switch(wakeup_source){

		case AON_TIMER_WAKEUP:
			/* enable aontimer to wakeup in rtl8721dlp_sleepcfg.c */
			DBG_8195A("set aon timer to wakeup\n");
			DSLP_Para.sleep_time = dslptime;
			break;

		case AON_WAKEPIN_WAKEUP:
			/* enable aon wakepin to wakeup in rtl8721dlp_sleepcfg.c */
			/* choose the wakepin and polarity you want in rtl8721dlp_sleepcfg.c */
			DBG_8195A("set aon wakepin to wakeup\n");
			break;

		case RTC_WAKEUP:
			/* enable rtc to wakeup in rtl8721dlp_sleepcfg.c */
			DBG_8195A("set rtc to wakeup\n ");
			RTC_AlarmCmd(ENABLE);
			break;

		case KYESCAN_WAKEUP:
			/*enable keyscan to wakeup in rtl8721dlp_sleepcfg.c and keyscan should be initialized*/
			DBG_8195A("set keyscan to wakeup\n");
			break;

		case CAPTOUCH_WAKEUP:
			/*enable captouch to wakeup in rtl8721dlp_sleepcfg.c and captouch should be initialized*/
			DBG_8195A("set captouch to wakeup\n");
			break;

		default:
			DBG_8195A("Unknown wakeup source\n");
			break;
	}
	DSLP_Para.dlps_enable = TRUE;

	asm volatile ("cpsid i" : : : "memory");
	
	ipc_send_message(IPC_INT_KM4_TICKLESS_INDICATION, (u32)&DSLP_Para);
	
	asm volatile ("wfe");
	asm volatile ("wfe");

	asm volatile ("cpsie i" : : : "memory");

	vTaskStartScheduler();

}
