#include <platform_stdlib.h>
#include <platform_opts.h>
#include <wifi_conf.h>
#include <osdep_service.h>
#include "os_sched.h"
#include "os_task.h"
#include <platform_opts_bt.h>
#include <gap_conn_le.h>

#if CONFIG_BT

#if defined(CONFIG_PLATFORM_8710C) && defined(CONFIG_FTL_ENABLED)
#include <ftl_int.h>

const uint8_t ftl_phy_page_num = 3;	/* The number of physical map pages, default is 3: BT_FTL_BKUP_ADDR, BT_FTL_PHY_ADDR1, BT_FTL_PHY_ADDR0 */
const uint32_t ftl_phy_page_start_addr = BT_FTL_BKUP_ADDR;

void app_ftl_init(void)
{
	DBG_INFO_MSG_OFF(_DBG_SPI_FLASH_);
	DBG_ERR_MSG_ON(_DBG_SPI_FLASH_);

	ftl_init(ftl_phy_page_start_addr, ftl_phy_page_num);
}
#endif //CONFIG_PLATFORM_8710C && CONFIG_FTL_ENABLED

extern void bt_coex_init(void);

void bt_example_init_thread(void *param)
{
	(void)param;
	T_GAP_DEV_STATE new_state;

#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	rtw_create_secure_context(configMINIMAL_SECURE_STACK_SIZE);
#endif

	/*Wait WIFI init complete*/
	while (!(wifi_is_up(RTW_STA_INTERFACE) || wifi_is_up(RTW_AP_INTERFACE))) {
		os_delay(1000);
	}

	/*Init BT*/

	bt_coex_init();

	/*Wait BT init complete*/
	do {
		os_delay(100);
		le_get_gap_param(GAP_PARAM_DEV_STATE, &new_state);
	} while (new_state.gap_init_state != GAP_INIT_STATE_STACK_READY);

	os_task_delete(NULL);
}

void bt_example_init(void)
{
#if ((defined(CONFIG_BT_MESH_PROVISIONER) && CONFIG_BT_MESH_PROVISIONER) || \
	(defined(CONFIG_BT_MESH_DEVICE) && CONFIG_BT_MESH_DEVICE))
	void *task = NULL;

	if (os_task_create(&task, ((const char *)"bt example init"), bt_example_init_thread,
					   NULL, 1024, 1) != true) {
		printf("\n\r%s xTaskCreate(bt example init) failed", __FUNCTION__);
	}
#endif // BT example flags
}

#endif //CONFIG_BT
