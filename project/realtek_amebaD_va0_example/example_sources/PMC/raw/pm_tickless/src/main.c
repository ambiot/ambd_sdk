#include "ameba_soc.h"
#include "main.h"

#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
extern VOID wlan_network(VOID);
#endif

static u32 app_loguart_suspend(u32 expected_idle_time, void *param)
{
	// For peripherals that need turned off before sleep, call disable or deinit peripheral here
	DBG_8195A("app_loguart_suspend\n");

	return TRUE;
}

static u32 app_loguart_resume(u32 expected_idle_time, void *param)
{
	// For peripherals that are turned off before sleep, call enable or init peripheral here
	DBG_8195A("app_loguart_resume\n");
	/*set km4 active time*/
	pmu_set_sysactive_time(5000);
	return TRUE;
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	/* init console */
	shell_recv_all_data_onetime = 1;

	InterruptRegister(IPC_INTHandler, IPC_IRQ, (u32)IPCM0_DEV, 10);
	InterruptEn(IPC_IRQ, 10);

	shell_init_rom(0, 0);	
	shell_init_ram();
	ipc_table_init();

	/* Register Log Uart Callback function */
	InterruptRegister((IRQ_FUN) shell_uart_irq_rom, UART_LOG_IRQ, (u32)NULL, 10);
	InterruptEn(UART_LOG_IRQ,10);

#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	rtw_efuse_boot_write();

	wlan_network();
#endif
	/*set KM4 sleep type*/
	pmu_set_sleep_type(SLEEP_PG);
	/*acquire wakelock to avoid KM4 enter sleep mode*/
	pmu_acquire_wakelock(PMU_OS);
	
	pmu_register_sleep_callback(PMU_LOGUART_DEVICE, (PSM_HOOK_FUN)app_loguart_suspend, NULL, (PSM_HOOK_FUN)app_loguart_resume, NULL);

	/*release wakelock to allow KM4 enter sleep mode*/
	pmu_release_wakelock(PMU_OS);
	/* Enable Schedule, Start Kernel */
	vTaskStartScheduler();
}
