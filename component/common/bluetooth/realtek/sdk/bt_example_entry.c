#include <platform_stdlib.h>
#include <platform_opts.h>
#include <platform_opts_bt.h>

#if CONFIG_BT

#if defined(CONFIG_PLATFORM_8710C) && defined(CONFIG_FTL_ENABLED)
#include <ftl_int.h>

const uint8_t ftl_phy_page_num = 3;	/* The number of physical map pages, default is 3: BT_FTL_BKUP_ADDR, BT_FTL_PHY_ADDR1, BT_FTL_PHY_ADDR0 */
const uint32_t ftl_phy_page_start_addr = BT_FTL_BKUP_ADDR;

void app_ftl_init(void)
{
	ftl_init(ftl_phy_page_start_addr, ftl_phy_page_num);
}
#endif //CONFIG_PLATFORM_8710C && CONFIG_FTL_ENABLED

#endif //CONFIG_BT
