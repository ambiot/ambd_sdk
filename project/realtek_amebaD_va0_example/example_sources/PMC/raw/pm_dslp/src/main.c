#include "ameba_soc.h"

#define AON_timer	0
#define WakePin		1
#define RTC			2
#define Keyscan		3
#define Captouch	4

static u32 wakeup = 0;		//choose wake up source, user should enble the source in rtl8721dlp_sleepcfg.c
static u32 dslptime = 10000;

KM4SLEEP_ParamDef DSLP_Para;

void main(void)
{

	/* register IPC interrupt */	
	InterruptRegister(IPC_INTHandler, IPC_IRQ, (u32)IPCM0_DEV, 5);
	InterruptEn(IPC_IRQ, 5);

	/* init console */
	shell_init_ram();
	ipc_table_init();

	u32 temp;
	
	SOCPS_AONWakeClear(BIT_ALL_WAKE_STS);
	DSLP_Para.sleep_time = 0;

	switch(wakeup){

		case 0:
			/* enable aontimer to wakeup in rtl8721dlp_sleepcfg.c */
			DBG_8195A("aon_timer to wakeup\n");
			DSLP_Para.sleep_time = dslptime;
			break;

		case 1:
			/* enable aon wakepin to wakeup in rtl8721dlp_sleepcfg.c */
			/* choose the wakepin and polarity you want in rtl8721dlp_sleepcfg.c */
			DBG_8195A("wakepin to wakeup\n");
			break;

		case 2:
			/* enable rtc to wakeup in rtl8721dlp_sleepcfg.c */
			DBG_8195A(" rtc to wakeup\n ");
			RTC_AlarmCmd(ENABLE);
			break;

		case 3:
			/*enable keyscan to wakeup in rtl8721dlp_sleepcfg.c and keyscan should be initialized*/
			DBG_8195A("keyscan to wakeup\n");
			break;

		case 4:
			/*enable captouch to wakeup in rtl8721dlp_sleepcfg.c and captouch should be initialized*/
			DBG_8195A("captouch to wakeup\n");
			break;

		default:
			DBG_8195A("Unknown wakeup source\n");
			break;
	}
	DSLP_Para.dlps_enable = TRUE;

	ipc_send_message(IPC_INT_KM4_TICKLESS_INDICATION, (u32)&DSLP_Para);

	while(1);

}

