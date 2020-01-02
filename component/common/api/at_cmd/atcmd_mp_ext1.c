#include <platform_stdlib.h>
#include <platform_opts.h>
#include <gpio_api.h>
#include "log_service.h"
#include "osdep_service.h"
#include "atcmd_mp.h"
#include "serial_api.h"
#include "serial_ex_api.h"

#if CONFIG_ATCMD_MP_EXT1

#define MP_EXT1_PREFIX		"[ATM1]: "
#define MP_EXT1_PRINTF(...) \
		do{ \
			_AT_PRINTK(MP_EXT1_PREFIX); \
			_AT_PRINTK(__VA_ARGS__); \
		}while(0)

//------------------------------------------------------------------------------
static int mp_ext1_efuse(void **argv, int argc)
{	
	int ret = -1;
	
	if(argc == 1){
		int result = -1;
		if(strcmp(argv[0], "moc100" ) == 0){
			result = HalCheckEfuseMICO100();
			if(result == 1){
				MP_EXT1_PRINTF("check efuse success.\n");
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
				wlan_network();
#endif
				ret = 0;
			}else if(result == 2){
				MP_EXT1_PRINTF("efuse had data.\n");
				ret = 1;
			}else{
				MP_EXT1_PRINTF("check efuse fail.\n");
			}
		}else{
			MP_EXT1_PRINTF("efuse command error.\n");
		}
	}
	return ret;
}

//------------------------------------------------------------------------------
#define EFUSE_USAGE			"ATM1=efuse,moc100\n"

at_mp_ext_item_t at_mp_ext1_items[] = {
	{"efuse",		mp_ext1_efuse,				EFUSE_USAGE},
};

void fATM1(void *arg)
{
	int argc = 0, ret, idx, cmd_cnt;
	char *argv[MAX_ARGC] = {0};
	
	MP_EXT1_PRINTF("_AT_MP_EXT1_\n");
	cmd_cnt = sizeof(at_mp_ext1_items)/sizeof(at_mp_ext1_items[0]);
	argc = parse_param(arg, argv);
	if(argc == 1){
		_AT_PRINTK("\n");
		MP_EXT1_PRINTF("Command usage :\n");
		for(idx = 0; idx < cmd_cnt; idx++)
			_AT_PRINTK("%s", at_mp_ext1_items[idx].mp_ext_usage);
	}else{
		for(idx = 0; idx < cmd_cnt; idx++){
			if(strcmp(argv[1], at_mp_ext1_items[idx].mp_ext_cmd) == 0){
				int (*fun)(void **argv, int argc) = at_mp_ext1_items[idx].mp_ext_fun;
				ret = fun((void**)&argv[2], argc-2);
				return;
			}
		}
		MP_EXT1_PRINTF("unknown command %s.\n", argv[1]);
	}
}

#endif // #if CONFIG_ATCMD_MP_EXT1

