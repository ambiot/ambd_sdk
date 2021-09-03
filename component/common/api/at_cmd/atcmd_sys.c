#include <platform_stdlib.h>
#include <platform_opts.h>
#ifdef CONFIG_PLATFORM_8195A
#include <hal_adc.h>
#endif

#include <gpio_api.h>   // mbed
#include <sys_api.h>
#include <flash_api.h>
#include "analogin_api.h"

#if !defined(CONFIG_PLATFORM_8195BHP) && !defined(CONFIG_PLATFORM_8710C)
#include <rtl_lib.h>
#endif
#include <build_info.h>
#include "log_service.h"
#include "atcmd_sys.h"
#include "main.h"
#include "atcmd_wifi.h"
#include "device_lock.h"

#if defined(configUSE_WAKELOCK_PMU) && (configUSE_WAKELOCK_PMU == 1)
#include "freertos_pmu.h"
#endif

#if !defined(CONFIG_PLATFORM_8195BHP) && !defined(CONFIG_PLATFORM_8710C)
extern u32 ConfigDebugErr;
extern u32 ConfigDebugInfo;
extern u32 ConfigDebugWarn;
#endif
#if defined(CONFIG_PLATFORM_8710C)
#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE==1)
extern s32 cmd_dump_word_s(u32 argc, u8 *argv[]);
extern s32 cmd_write_word_s(u32 argc, u8 *argv[]);
#define CmdDumpWord(argc, argv) cmd_dump_word_s(argc, argv)
#define CmdWriteWord(argc, argv) cmd_write_word_s(argc, argv)
#else
extern s32 cmd_dump_word(u32 argc, u8 *argv[]);
extern s32 cmd_write_word(u32 argc, u8 *argv[]);
#define CmdDumpWord(argc, argv) cmd_dump_word(argc, argv)
#define CmdWriteWord(argc, argv) cmd_write_word(argc, argv)
#endif
#else
extern u32 CmdDumpWord(IN u16 argc, IN u8 *argv[]);
extern u32 CmdWriteWord(IN u16 argc, IN u8 *argv[]);
#endif
#if defined(CONFIG_UART_YMODEM) && CONFIG_UART_YMODEM
extern int uart_ymodem(void);
#endif

//#if ATCMD_VER == ATVER_1
#if (configGENERATE_RUN_TIME_STATS == 1)
static char cBuffer[512];
#endif
//#endif

//-------- AT SYS commands ---------------------------------------------------------------
#if ATCMD_VER == ATVER_1

#if defined(CONFIG_PLATFORM_8710C)
void fATXX(void *arg)
{
    flash_t flash_Ptable;
    flash_erase_sector(&flash_Ptable, 0x00000000);
    sys_reset();
}
#endif

void fATSD(void *arg)
{
#if !defined(CONFIG_PLATFORM_8195BHP)
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	
	AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSD]: _AT_SYSTEM_DUMP_REGISTER_");
	if(!arg){
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSD] Usage: ATSD=REGISTER");
		return;
	}
	argc = parse_param(arg, argv);
	if(argc == 2 || argc == 3)
		CmdDumpWord(argc-1, (unsigned char**)(argv+1));
#endif
}

void fATSE(void *arg)
{
#if !defined(CONFIG_PLATFORM_8195BHP)
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	
	AT_DBG_MSG(AT_FLAG_EDIT, AT_DBG_ALWAYS, "[ATSE]: _AT_SYSTEM_EDIT_REGISTER_");
	if(!arg){
		AT_DBG_MSG(AT_FLAG_EDIT, AT_DBG_ALWAYS, "[ATSE] Usage: ATSE=REGISTER[VALUE]");
		return;
	}
	argc = parse_param(arg, argv);
	if(argc == 3)
		CmdWriteWord(argc-1, (unsigned char**)(argv+1));
#endif
}

void fATSC(void *arg)
{
	/* To avoid gcc warnings */
	( void ) arg;

	AT_DBG_MSG(AT_FLAG_OTA, AT_DBG_ALWAYS, "[ATSC]: _AT_SYSTEM_CLEAR_OTA_SIGNATURE_");
	sys_clear_ota_signature();
}

void fATSR(void *arg)
{
	/* To avoid gcc warnings */
	( void ) arg;
	
	AT_DBG_MSG(AT_FLAG_OTA, AT_DBG_ALWAYS, "[ATSR]: _AT_SYSTEM_RECOVER_OTA_SIGNATURE_");
	sys_recover_ota_signature();
}

#if defined(CONFIG_UART_YMODEM) && CONFIG_UART_YMODEM
void fATSY(void *arg)
{
	uart_ymodem();
}
#endif

#if defined(CONFIG_PLATFORM_8711B)
void fATSK(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	u8 key[16];

	AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK]: _AT_SYSTEM_RDP/RSIP_CONFIGURE_");
	if(!arg){
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RDP_EN");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RDP_KEY[value(hex)]");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] 	Example: ATSK=RDP_KEY[345487bbaa435bfe382233445ba359aa]");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RSIP_EN");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RSIP_DIS");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RSIP_KEY[value(hex)]");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=SB_EN");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=SB_PK_MD5[value(hex)]");
		return;
	}

	argc = parse_param(arg, argv);
	if(strcmp(argv[1], "RDP_EN") == 0){
		EFUSE_RDP_EN();
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] RDP is enable");
	}else if(strcmp(argv[1], "RDP_KEY") == 0){
		if(argc != 3){
			AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RDP_KEY[value(hex)]");
			return;
		}

		if(strlen(argv[2]) != 32){
			AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Err: RDP key length should be 16 bytes");
			return;
		}
		
		sscanf(argv[2], "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", 
			&key[0], &key[1], &key[2], &key[3], &key[4], &key[5], &key[6], &key[7], 
			&key[8], &key[9], &key[10], &key[11], &key[12], &key[13], &key[14], &key[15]);

		EFUSE_RDP_KEY(key);
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Set RDP key done");
	}else if(strcmp(argv[1], "RSIP_EN") == 0){
		efuse_otf_cmd(ENABLE);
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] RSIP is enable");
	}else if(strcmp(argv[1], "RSIP_DIS") == 0){
		efuse_otf_cmd(DISABLE);
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] RSIP is disable");
	}else if(strcmp(argv[1], "RSIP_KEY") == 0){
		if(argc != 3){
			AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RSIP_KEY[value(hex)]");
			return;
		}

		if(strlen(argv[2]) != 32){
			AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Err: RSIP key length should be 16 bytes");
			return;
		}
		
		sscanf(argv[2], "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", 
			&key[0], &key[1], &key[2], &key[3], &key[4], &key[5], &key[6], &key[7], 
			&key[8], &key[9], &key[10], &key[11], &key[12], &key[13], &key[14], &key[15]);

		EFUSE_OTF_KEY(key);
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Set RSIP key done");
	}else if(strcmp(argv[1], "SB_EN") == 0){
		u8 data = 0;
		u32 efuse_ctrl = HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_EFUSE_CTRL);
	
		EFUSERead8(efuse_ctrl, 0xD3, &data, L25EOUTVOLTAGE);
		if ((data & EFUSE_PHYSICAL_SBOOT_ON) != 0) {
			EFUSEWrite8(efuse_ctrl, 0xD3, data & (~EFUSE_PHYSICAL_SBOOT_ON), L25EOUTVOLTAGE);
			AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] : Security Boot is enable!");
		}else{
			AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] : Security Boot is already enabled!");
		}
	}else if(strcmp(argv[1], "SB_PK_MD5") == 0){
		u8 i = 0;
		
		if(argc != 3){
			AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=SB_PK_MD5[value(hex)]");
			return;
		}

		if(strlen(argv[2]) != 32){
			AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Err: MD5 value of public key should be 16 bytes");
			return;
		}
		
		sscanf(argv[2], "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", 
			&key[0], &key[1], &key[2], &key[3], &key[4], &key[5], &key[6], &key[7], 
			&key[8], &key[9], &key[10], &key[11], &key[12], &key[13], &key[14], &key[15]);

		for(i = 0; i < 16; i++) {
			EFUSEWrite8(HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_EFUSE_CTRL), 0xC1 + i, key[i], L25EOUTVOLTAGE);
		}
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Set SB md5 value of public key done");

	}else{
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RDP_EN");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RDP_KEY[value(hex)]");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] 	Example: ATSK=RDP_KEY[345487bbaa435bfe382233445ba359aa]");		
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RSIP_EN");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RSIP_DIS");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=RSIP_KEY[value(hex)]");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=SB_EN");
		AT_DBG_MSG(AT_FLAG_RDP, AT_DBG_ALWAYS, "[ATSK] Usage: ATSK=SB_PK_MD5[value(hex)]");
		
	}
	
}
#endif

#if defined(SUPPORT_MP_MODE) && SUPPORT_MP_MODE
void fATSA(void *arg)
{
#if !defined(CONFIG_PLATFORM_8195BHP) && !defined(CONFIG_PLATFORM_8710C) && !defined(CONFIG_PLATFORM_8721D)
	u32 tConfigDebugInfo = ConfigDebugInfo;
	int argc = 0, channel;
	char *argv[MAX_ARGC] = {0}, *ptmp;
	u16 offset, gain;
	
	AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA]: _AT_SYSTEM_ADC_TEST_");
	if(!arg){
		AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] Usage: ATSA=CHANNEL(1~3)");
		AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] Usage: ATSA=k_get");
		AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] Usage: ATSA=k_set[offet(hex),gain(hex)]");
		return;
	}
	
	argc = parse_param(arg, argv);
	if(strcmp(argv[1], "k_get") == 0){
		sys_adc_calibration(0, &offset, &gain);
//		AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] offset = 0x%04X, gain = 0x%04X", offset, gain);
	}else if(strcmp(argv[1], "k_set") == 0){
		if(argc != 4){
			AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] Usage: ATSA=k_set[offet(hex),gain(hex)]");
			return;
		}
		offset = strtoul(argv[2], &ptmp, 16);
		gain = strtoul(argv[3], &ptmp, 16);
		sys_adc_calibration(1, &offset, &gain);
//		AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] offset = 0x%04X, gain = 0x%04X", offset, gain);
	}else{
		channel = atoi(argv[1]);
		if(channel < 1 || channel > 3){
			AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] Usage: ATSA=CHANNEL(1~3)");
			return;
		}
		analogin_t   adc;
		u16 adcdat;
		
		// Remove debug info massage
		ConfigDebugInfo = 0;
		if(channel == 1)
			analogin_init(&adc, AD_1);
		else if(channel == 2)
			analogin_init(&adc, AD_2);
		else
			analogin_init(&adc, AD_3);
		adcdat = analogin_read_u16(&adc)>>4;
		analogin_deinit(&adc);
		// Recover debug info massage
		ConfigDebugInfo = tConfigDebugInfo;
		
		AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] A%d = 0x%04X", channel, adcdat);
	}
#elif defined(CONFIG_PLATFORM_8721D)
	int argc = 0, channel;
	char *argv[MAX_ARGC] = {0};
	analogin_t   adc;
	u16 adcdat;
	u8 max_ch_num =   8;
	u32 ch_list[8] = {AD_0, AD_1, AD_2, AD_3, AD_4, AD_5, AD_6, AD_7};

	AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA]: _AT_SYSTEM_ADC_TEST_");
	if(!arg){
		AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] Usage: ATSA=CHANNEL(0~7)");
		return;
	}

	argc = parse_param(arg, argv);

	channel = atoi(argv[1]);
	if(channel >= max_ch_num){
		AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] Usage: ATSA=CHANNEL(0~7)");
		return;
	}

	analogin_init(&adc, ch_list[channel]);
	adcdat = analogin_read_u16(&adc);
	analogin_deinit(&adc);
	
	AT_DBG_MSG(AT_FLAG_ADC, AT_DBG_ALWAYS, "[ATSA] A%d = 0x%04X", channel, adcdat);
#endif
}

void fATSG(void *arg)
{
#if defined(CONFIG_PLATFORM_8195A)
    gpio_t gpio_test;
    int argc = 0, val;
	char *argv[MAX_ARGC] = {0}, port, num;
	PinName pin = NC;
	u32 tConfigDebugInfo = ConfigDebugInfo;
    
	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: _AT_SYSTEM_GPIO_TEST_");
	if(!arg){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] Usage: ATSG=PINNAME(ex:A0)");
		return;
	}else{
		argc = parse_param(arg, argv);
		if(argc != 2){
			AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] Usage: ATSG=PINNAME(ex:A0)");
			return;
		}
	}
	port = argv[1][0];
	num = argv[1][1];
	if(port >= 'a' && port <= 'z')
		port -= ('a' - 'A');
	if(num >= 'a' && num <= 'z')
		num -= ('a' - 'A');
	switch(port){
		case 'A':
			switch(num){
				case '0': pin = PA_0; break; case '1': pin = PA_1; break; case '2': pin = PA_2; break; case '3': pin = PA_3; break;
				case '4': pin = PA_4; break; case '5': pin = PA_5; break; case '6': pin = PA_6; break; case '7': pin = PA_7; break;
			}
			break;
		case 'B':
			switch(num){
				case '0': pin = PB_0; break; case '1': pin = PB_1; break; case '2': pin = PB_2; break; case '3': pin = PB_3; break;
				case '4': pin = PB_4; break; case '5': pin = PB_5; break; case '6': pin = PB_6; break; case '7': pin = PB_7; break;
			}
			break;
		case 'C':
			switch(num){
				case '0': pin = PC_0; break; case '1': pin = PC_1; break; case '2': pin = PC_2; break; case '3': pin = PC_3; break;
				case '4': pin = PC_4; break; case '5': pin = PC_5; break; case '6': pin = PC_6; break; case '7': pin = PC_7; break;
				case '8': pin = PC_8; break; case '9': pin = PC_9; break;
			}
			break;
		case 'D':
			switch(num){
				case '0': pin = PD_0; break; case '1': pin = PD_1; break; case '2': pin = PD_2; break; case '3': pin = PD_3; break;
				case '4': pin = PD_4; break; case '5': pin = PD_5; break; case '6': pin = PD_6; break; case '7': pin = PD_7; break;
				case '8': pin = PD_8; break; case '9': pin = PD_9; break;
			}
			break;
		case 'E':
			switch(num){
				case '0': pin = PE_0; break; case '1': pin = PE_1; break; case '2': pin = PE_2; break; case '3': pin = PE_3; break;
				case '4': pin = PE_4; break; case '5': pin = PE_5; break; case '6': pin = PE_6; break; case '7': pin = PE_7; break;
				case '8': pin = PE_8; break; case '9': pin = PE_9; break; case 'A': pin = PE_A; break;
			}
			break;
		case 'F':
			switch(num){
				case '0': pin = PF_0; break; case '1': pin = PF_1; break; case '2': pin = PF_2; break; case '3': pin = PF_3; break;
				case '4': pin = PF_4; break; case '5': pin = PF_5; break;
			}
			break;
		case 'G':
			switch(num){
				case '0': pin = PG_0; break; case '1': pin = PG_1; break; case '2': pin = PG_2; break; case '3': pin = PG_3; break;
				case '4': pin = PG_4; break; case '5': pin = PG_5; break; case '6': pin = PG_6; break; case '7': pin = PG_7; break;
			}
			break;
		case 'H':
			switch(num){
				case '0': pin = PH_0; break; case '1': pin = PH_1; break; case '2': pin = PH_2; break; case '3': pin = PH_3; break;
				case '4': pin = PH_4; break; case '5': pin = PH_5; break; case '6': pin = PH_6; break; case '7': pin = PH_7; break;
			}
			break;
		case 'I':
			switch(num){
				case '0': pin = PI_0; break; case '1': pin = PI_1; break; case '2': pin = PI_2; break; case '3': pin = PI_3; break;
				case '4': pin = PI_4; break; case '5': pin = PI_5; break; case '6': pin = PI_6; break; case '7': pin = PI_7; break;
			}
			break;
		case 'J':
			switch(num){
				case '0': pin = PJ_0; break; case '1': pin = PJ_1; break; case '2': pin = PJ_2; break; case '3': pin = PJ_3; break;
				case '4': pin = PJ_4; break; case '5': pin = PJ_5; break; case '6': pin = PJ_6; break;
			}
			break;
		case 'K':
			switch(num){
				case '0': pin = PK_0; break; case '1': pin = PK_1; break; case '2': pin = PK_2; break; case '3': pin = PK_3; break;
				case '4': pin = PK_4; break; case '5': pin = PK_5; break; case '6': pin = PK_6; break;
			}
			break;
	}
	if(pin == NC){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: Invalid Pin Name");
		return;
	}
	// Remove debug info massage
	ConfigDebugInfo = 0;
	// Initial input control pin
	gpio_init(&gpio_test, pin);
	gpio_dir(&gpio_test, PIN_INPUT);     // Direction: Input
	gpio_mode(&gpio_test, PullUp);       // Pull-High
	val = gpio_read(&gpio_test);
	// Recover debug info massage
	ConfigDebugInfo = tConfigDebugInfo;
	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] %c%c = %d", port, num, val);

#elif defined(CONFIG_PLATFORM_8711B)
    gpio_t gpio_test;
    int argc = 0, val, num;
	char *argv[MAX_ARGC] = {0}, port;
	PinName pin = NC;
	u32 tConfigDebugInfo = ConfigDebugInfo;
    
	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: _AT_SYSTEM_GPIO_TEST_");
	if(!arg){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] Usage: ATSG=PINNAME(ex:A0)");
		return;
	}else{
		argc = parse_param(arg, argv);
		if(argc != 2){
			AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] Usage: ATSG=PINNAME(ex:A0)");
			return;
		}
	}
	port = argv[1][0];
	if(port >= 'a' && port <= 'z')
		port -= ('a' - 'A');
	num = atoi(argv[1] + 1);
	
	//PA_6~PA_11 are not allowed to be tested when code running on flash. 
	//PA_16~PA_17 or PA_29~PA_30 should not be tested when they are used as log UART RX and TX.
	switch(port){
		case 'A':
			switch(num){
				case 0: pin = PA_0; break; case 1: pin = PA_1; break; case 2: pin = PA_2; break; case 3: pin = PA_3; break;
				case 4: pin = PA_4; break; case 5: pin = PA_5; break;  /*case 6:pin = PA_6; break; case 7: pin = PA_7; break;
				case 8: pin = PA_8; break; case 9: pin = PA_9; break; case 10: pin = PA_10; break; case 11: pin = PA_11; break;*/
				case 12: pin = PA_12; break; case 13: pin = PA_13; break; case 14: pin = PA_14; break; case 15: pin = PA_15; break;
				case 16: pin = PA_16; break; case 17: pin = PA_17; break; case 18: pin = PA_18; break; case 19: pin = PA_19; break;
				case 20: pin = PA_20; break; case 21: pin = PA_21; break; case 22: pin = PA_22; break; case 23: pin = PA_23; break;
				case 24: pin = PA_24; break; case 25: pin = PA_25; break; case 26: pin = PA_26; break; case 27: pin = PA_27; break;
				case 28: pin = PA_28; break; case 29: pin = PA_29; break; case 30: pin = PA_30; break; case 31: pin = PA_31; break;
			}
			break;
		case 'B':
			switch(num){
				case 0: pin = PB_0; break; case 1: pin = PB_1; break; case 2: pin = PB_2; break; case 3: pin = PB_3; break;
				case 4: pin = PB_4; break; case 5: pin = PB_5; break; case 6: pin = PB_6; break; case 7: pin = PB_7; break;
			}
			break;
	}
	if(pin == NC){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: Invalid Pin Name");
		return;
	}
	// Remove debug info massage
	ConfigDebugInfo = 0;
	// Initial input control pin
	gpio_init(&gpio_test, pin);
	gpio_dir(&gpio_test, PIN_INPUT);     // Direction: Input
	gpio_mode(&gpio_test, PullUp);       // Pull-High
	val = gpio_read(&gpio_test);
	// Recover debug info massage
	ConfigDebugInfo = tConfigDebugInfo;
	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] %c%d = %d", port, num, val);

#elif defined(CONFIG_PLATFORM_8721D)
    gpio_t gpio_test;
    int argc = 0, val, num;
	char *argv[MAX_ARGC] = {0}, port;
	PinName pin = NC;
    
	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: _AT_SYSTEM_GPIO_TEST_");
	if(!arg){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] Usage: ATSG=PINNAME(ex:A0)");
		return;
	}else{
		argc = parse_param(arg, argv);
		if(argc != 2){
			AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] Usage: ATSG=PINNAME(ex:A0)");
			return;
		}
	}
	port = argv[1][0];
	if(port >= 'a' && port <= 'z')
		port -= ('a' - 'A');
	num = atoi(argv[1] + 1);
	
	//PB_12~PB_17 or PB_18~PB_23 are not allowed to be tested when code running on flash. 
	//PA_7~PA_8 should not be tested when they are used as log UART RX and TX.
	switch(port){
		case 'A':
			switch(num){
				case 0: pin = PA_0; break; case 1: pin = PA_1; break; case 2: pin = PA_2; break; case 3: pin = PA_3; break;
				case 4: pin = PA_4; break; case 5: pin = PA_5; break;  case 6:pin = PA_6; break; case 7: pin = PA_7; break;
				case 8: pin = PA_8; break; case 9: pin = PA_9; break; case 10: pin = PA_10; break; case 11: pin = PA_11; break;
				case 12: pin = PA_12; break; case 13: pin = PA_13; break; case 14: pin = PA_14; break; case 15: pin = PA_15; break;
				case 16: pin = PA_16; break; case 17: pin = PA_17; break; case 18: pin = PA_18; break; case 19: pin = PA_19; break;
				case 20: pin = PA_20; break; case 21: pin = PA_21; break; case 22: pin = PA_22; break; case 23: pin = PA_23; break;
				case 24: pin = PA_24; break; case 25: pin = PA_25; break; case 26: pin = PA_26; break; case 27: pin = PA_27; break;
				case 28: pin = PA_28; break; case 29: pin = PA_29; break; case 30: pin = PA_30; break; case 31: pin = PA_31; break;
			}
			break;
		case 'B':
			switch(num){
				case 0: pin = PB_0; break; case 1: pin = PB_1; break; case 2: pin = PB_2; break; case 3: pin = PB_3; break;
				case 4: pin = PB_4; break; case 5: pin = PB_5; break; case 6: pin = PB_6; break; case 7: pin = PB_7; break;
				case 8: pin = PB_8; break; case 9: pin = PA_9; break; case 10: pin = PA_10; break; case 11: pin = PA_11; break;
				/*case 12: pin = PB_12; break; case 13: pin = PB_13; break; case 14: pin = PB_14; break; case 15: pin = PB_15; break;
				case 16: pin = PB_16; break; case 17: pin = PB_17; break; case 18: pin = PB_18; break; case 19: pin = PB_19; break;*/
				case 20: pin = PB_20; break; case 21: pin = PB_21; break; case 22: pin = PB_22; break; case 23: pin = PB_23; break;
				case 24: pin = PB_24; break; case 25: pin = PB_25; break; case 26: pin = PB_26; break; case 27: pin = PB_27; break;
				case 28: pin = PB_28; break; case 29: pin = PB_29; break; case 30: pin = PB_30; break; case 31: pin = PB_31; break;
			}
			break;
	}
	if(pin == NC){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: Invalid Pin Name");
		return;
	}

	// Initial input control pin
	gpio_init(&gpio_test, pin);
	gpio_dir(&gpio_test, PIN_INPUT);     // Direction: Input
	gpio_mode(&gpio_test, PullUp);       // Pull-High
	val = gpio_read(&gpio_test);

	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] %c%d = %d", port, num, val);

#elif defined(CONFIG_PLATFORM_8710C)
	gpio_t gpio_test;
	int argc = 0, val, num;
	char *argv[MAX_ARGC] = {0}, port;

	PinName pin = NC;
	u32 tConfigDebugInfo = ConfigDebugInfo;
	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: _AT_SYSTEM_GPIO_TEST_");
	if(!arg){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] Usage: ATSG=PINNAME(ex:A0)");
		return;
	}else{
		argc = parse_param(arg, argv);
		if(argc != 2){
			AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] Usage: ATSG=PINNAME(ex:A0)");
			return;
		}
	}
	port = argv[1][0];
	if(port >= 'a' && port <= 'z')
		port -= ('a' - 'A');
	num = atoi(argv[1] + 1);
	//PA_7~PA_12  only available on RTL8720CF
	//PA_0~PA_4 should not be tested when they are used as JTAG/SWD.
	//PA_15~PA_16 or PA_0~PA_1 or PA_2~PA_3 or PA_13~PA_14 should not be tested when they are used as UART RX and TX.
	//PA_5, PA_6, PA_21 and PA_22 are not able to be tested
	switch(port){
		case 'A':
			switch(num){
				case 0: pin = PA_0; break; case 1: pin = PA_1; break; case 2: pin = PA_2; break; case 3: pin = PA_3; break;
				case 4: pin = PA_4; break; /*case 5: pin = PA_5; break;  case 6:pin = PA_6; break; case 7: pin = PA_7; break;
				case 8: pin = PA_8; break; case 9: pin = PA_9; break; case 10: pin = PA_10; break; case 11: pin = PA_11; break;
				case 12: pin = PA_12; break;*/ case 13: pin = PA_13; break; case 14: pin = PA_14; break; case 15: pin = PA_15; break;
				case 16: pin = PA_16; break; case 17: pin = PA_17; break; case 18: pin = PA_18; break; case 19: pin = PA_19; break;
				case 20: pin = PA_20; break; /* case 21: pin = PA_21; break; case 22: pin = PA_22; break;*/ case 23: pin = PA_23; break;
			}
			break;
	}
	if(pin == NC){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: Invalid Pin Name");
		return;
	}
	// Remove debug info massage
	ConfigDebugInfo = 0;
	// Initial input control pin
	gpio_init(&gpio_test, pin);
	gpio_dir(&gpio_test, PIN_INPUT);     // Direction: Input
	gpio_mode(&gpio_test, PullUp);       // Pull-High
	val = gpio_read(&gpio_test);
	// Recover debug info massage
	ConfigDebugInfo = tConfigDebugInfo;
	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG] %c%d = %d", port, num, val);
#endif
}

void fATSP(void *arg)
{
#if defined(CONFIG_PLATFORM_8195A)
	int   argc           = 0;
	char *argv[MAX_ARGC] = {0};

	unsigned long timeout; // ms
	unsigned long time_begin, time_current;

	gpio_t gpiob_1;
	int val_old, val_new;

	int expected_zerocount, zerocount;
	int test_result;

	// parameter check
	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSP]: _AT_SYSTEM_POWER_PIN_TEST_");
	if(!arg) {
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSP]: Usage: ATSP=gpiob1[timeout,zerocount]");
		return;
	} else {
		argc = parse_param(arg, argv);
		if (argc < 2) {
			AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSP]: Usage: ATSP=gpiob1[timeout,zerocount]");
			return;
		}
	}

	if ( strcmp(argv[1], "gpiob1" ) == 0 ) {
		if (argc < 4) {
			AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSP]: Usage: ATSP=gpiob1[timeout,zerocount]");
			return;
		}

		// init gpiob1 test
		test_result         = 0;
		timeout             = strtoul(argv[2], NULL, 10);
		expected_zerocount  = atoi(argv[3]);
		zerocount           = 0;
		val_old             = 1;

		sys_log_uart_off();

		gpio_init(&gpiob_1, PB_1);
		gpio_dir(&gpiob_1, PIN_INPUT);
		gpio_mode(&gpiob_1, PullDown);

		// gpiob1 test ++
		time_begin = time_current = xTaskGetTickCount();
		while (time_current < time_begin + timeout) {
			val_new = gpio_read(&gpiob_1);

			if (val_new != val_old && val_new == 0) {

				zerocount ++;
				if (zerocount == expected_zerocount) {
					test_result = 1;
					break;
				}
			}

			val_old = val_new;
			time_current = xTaskGetTickCount();
		}
		// gpio test --

		sys_log_uart_on();

		if (test_result == 1) {
			AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSP]: success");
		} else {
			AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSP]: fail, it only got %d zeros", zerocount);
		}
	}
#endif
}

#if !defined(CONFIG_PLATFORM_8195BHP) && !defined(CONFIG_PLATFORM_8710C)
int write_otu_to_system_data(flash_t *flash, uint32_t otu_addr)
{
	uint32_t data, i = 0;
	flash_read_word(flash, FLASH_SYSTEM_DATA_ADDR+0xc, &data);
	//printf("\n\r[%s] data 0x%x otu_addr 0x%x", __FUNCTION__, data, otu_addr);
	AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: data 0x%x otu_addr 0x%x", data, otu_addr);	
	if(data == ~0x0){
		flash_write_word(flash, FLASH_SYSTEM_DATA_ADDR+0xc, otu_addr);
	}else{
		//erase backup sector
		flash_erase_sector(flash, FLASH_RESERVED_DATA_BASE);
		//backup system data to backup sector
		for(i = 0; i < 0x1000; i+= 4){
			flash_read_word(flash, FLASH_SYSTEM_DATA_ADDR + i, &data);
			if(i == 0xc)
				data = otu_addr;
			flash_write_word(flash, FLASH_RESERVED_DATA_BASE + i,data);
		}
		//erase system data
		flash_erase_sector(flash, FLASH_SYSTEM_DATA_ADDR);
		//write data back to system data
		for(i = 0; i < 0x1000; i+= 4){
			flash_read_word(flash, FLASH_RESERVED_DATA_BASE + i, &data);
			flash_write_word(flash, FLASH_SYSTEM_DATA_ADDR + i,data);
		}
		//erase backup sector
		flash_erase_sector(flash, FLASH_RESERVED_DATA_BASE);
	}
	return 0;
}
#endif

void fATSB(void *arg)
{
#if !defined(CONFIG_PLATFORM_8195BHP) && !defined(CONFIG_PLATFORM_8710C)
	int   argc           = 0;
	char *argv[MAX_ARGC] = {0};
	u32 boot_gpio, rb_boot_gpio;
	u8 gpio_pin;
	u8 uart_port, uart_index;
	u8 gpio_pin_bar;
	u8 uart_port_bar;		
	flash_t flash;

	// parameter check
	AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: _AT_SYSTEM_BOOT_OTU_PIN_SET_");
	if(!arg) {
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: Usage: ATSB=[GPIO_PIN,TRIGER_MODE,UART]");
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: GPIO_PIN: PB_1, PC_4 ....");
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: TRIGER_MODE: low_trigger, high_trigger");
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: UART: UART0, UART2");
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: example: ATSB=[PC_2,low_trigger,UART2]");
		return;
	} else {
		argc = parse_param(arg, argv);
		if (argc != 4 ) {
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: Usage: ATSB=[GPIO_PIN,TRIGER_MODE,UART]");
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: GPIO_PIN: PB_1, PC_4 ....");
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: TRIGER_MODE: low_trigger, high_trigger");
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: UART: UART0, UART2");
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: example: ATSB=[PC_2,low_trigger,UART2]");
			return;
		}
	}

	if ( strncmp(argv[1], "P", 1) == 0 && strlen(argv[1]) == 4
		&& (strcmp(argv[2], "low_trigger") == 0 || strcmp(argv[2], "high_trigger") == 0)
		&& strncmp(argv[3], "UART", 4) == 0 && strlen(argv[3]) == 5) {
		if((argv[1][1] >= 0x41 && argv[1][1] <= 0x45) && (argv[1][3] >= 0x30 && argv[1][3] <= 0x39) &&(argv[3][4] >= 0x30 && argv[3][4] <= 0x32)){
			if(strcmp(argv[2], "high_trigger") == 0)
				gpio_pin = 1<< 7 | ((argv[1][1]-0x41)<<4) | (argv[1][3] - 0x30);
			else
				gpio_pin = ((argv[1][1]-0x41)<<4) | (argv[1][3] - 0x30);
			gpio_pin_bar = ~gpio_pin;
			uart_index = argv[3][4] - 0x30;
			if(uart_index == 0)
				uart_port = (uart_index<<4)|2;
			else if(uart_index == 2)
				uart_port = (uart_index<<4)|0;
			else{
				AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: Input UART index error. Please choose UART0 or UART2.");
				AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: example: ATSB=[PC_2,low_trigger,UART2]");
				return;
			}
			uart_port_bar = ~uart_port;
			boot_gpio = uart_port_bar<<24 | uart_port<<16 | gpio_pin_bar<<8 | gpio_pin;
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]:gpio_pin 0x%x", gpio_pin);
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]:gpio_pin_bar 0x%x", gpio_pin_bar);
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]:uart_port 0x%x", uart_port);
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]:uart_port_bar 0x%x", uart_port_bar);
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]:boot_gpio 0x%x", boot_gpio);
			write_otu_to_system_data(&flash, boot_gpio);
			flash_read_word(&flash, FLASH_SYSTEM_DATA_ADDR+0x0c, &rb_boot_gpio);			
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]:Read 0x900c 0x%x", rb_boot_gpio);
		}else{
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: Usage: ATSB=[GPIO_PIN,TRIGER_MODE,UART]");
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: GPIO_PIN: PB_1, PC_4 ....");
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: TRIGER_MODE: low_trigger, high_trigger");
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: UART: UART0, UART2");
			AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: example: ATSB=[PC_2,low_trigger,UART2]");
		}		
	}else{
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: Usage: ATSB=[GPIO_PIN,TRIGER_MODE,UART]");
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: GPIO_PIN: PB_1, PC_4 ....");
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: TRIGER_MODE: low_trigger, high_trigger");
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: UART: UART0, UART2");
		AT_DBG_MSG(AT_FLAG_DUMP, AT_DBG_ALWAYS, "[ATSB]: example: ATSB=[PC_2,low_trigger,UART2]");
		return;
	}
#endif
}
#endif

#if (configGENERATE_RUN_TIME_STATS == 1)
void fATSS(void *arg)	// Show CPU stats
{
	AT_PRINTK("[ATSS]: _AT_SYSTEM_CPU_STATS_");
	vTaskGetRunTimeStats((char *)cBuffer);
	AT_PRINTK("%s", cBuffer);
}
#endif

void fATSs(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	AT_PRINTK("[ATS@]: _AT_SYSTEM_DBG_SETTING_");
	if(!arg){
		AT_PRINTK("[ATS@] Usage: ATS@=[LEVLE,FLAG]");
	}else{
		argc = parse_param(arg, argv);
		if(argc == 3){
			char *ptmp;
			gDbgLevel = atoi(argv[1]);
			gDbgFlag = strtoul(argv[2], &ptmp, 16);
		}
	}
	AT_PRINTK("[ATS@] level = %d, flag = 0x%08X", gDbgLevel, gDbgFlag);
}

void fATSc(void *arg)
{
#if defined (CONFIG_PLATFORM_8721D)
	int argc = 0, config = 0;
	char *argv[MAX_ARGC] = {0};

	AT_PRINTK("[ATS!]: _AT_SYSTEM_CONFIG_SETTING_");
	if(!arg){
		AT_PRINTK("[ATS!] Usage: ATS!=[CONFIG(0,1,2),FLAG]");
	}else{
		argc = parse_param(arg, argv);
		if(argc == 3){
			char *ptmp;
			config = atoi(argv[1]);
			if(config == 0)
				ConfigDebug[LEVEL_ERROR] = strtoul(argv[2], &ptmp, 16);
			if(config == 1)
				ConfigDebug[LEVEL_INFO] = strtoul(argv[2], &ptmp, 16);
			if(config == 2)
				ConfigDebug[LEVEL_WARN] = strtoul(argv[2], &ptmp, 16);
		}
	}
	AT_PRINTK("[ATS!] ConfigDebugErr  = 0x%08X", ConfigDebug[LEVEL_ERROR]);
	AT_PRINTK("[ATS!] ConfigDebugInfo = 0x%08X", ConfigDebug[LEVEL_INFO]);
	AT_PRINTK("[ATS!] ConfigDebugWarn = 0x%08X", ConfigDebug[LEVEL_WARN]);
#else
	int argc = 0, config = 0;
	char *argv[MAX_ARGC] = {0};

	AT_PRINTK("[ATS!]: _AT_SYSTEM_CONFIG_SETTING_");
	if(!arg){
		AT_PRINTK("[ATS!] Usage: ATS!=[CONFIG(0,1,2),FLAG]");
	}else{
		argc = parse_param(arg, argv);
		if(argc == 3){
			char *ptmp;
			config = atoi(argv[1]);
			if(config == 0)
				ConfigDebugErr = strtoul(argv[2], &ptmp, 16);
			if(config == 1)
				ConfigDebugInfo = strtoul(argv[2], &ptmp, 16);
			if(config == 2)
				ConfigDebugWarn = strtoul(argv[2], &ptmp, 16);
		}
	}
	AT_PRINTK("[ATS!] ConfigDebugErr  = 0x%08X", ConfigDebugErr);
	AT_PRINTK("[ATS!] ConfigDebugInfo = 0x%08X", ConfigDebugInfo);
	AT_PRINTK("[ATS!] ConfigDebugWarn = 0x%08X", ConfigDebugWarn);
#endif
}

#define SUPPORT_CP_TEST 0
#if SUPPORT_CP_TEST
extern void MFi_auth_test(void);
void fATSM(void *arg)
{
	AT_PRINTK("[ATSM]: _AT_SYSTEM_CP_");
	MFi_auth_test();
}
#endif

void fATSt(void *arg)
{
	/* To avoid gcc warnings */
	( void ) arg;
	
	AT_PRINTK("[ATS#]: _AT_SYSTEM_TEST_");
}

#if defined(CONFIG_PLATFORM_8711B)
/*Function: Check if the input jtag key is matched with the jtag password derived from the SB key stored in EFUSE. 
		    If the input jtag key is correct, it will be stored in system data area of the flash. 
		    Otherwise, the last 1 of the error map will be written to 0, which is also stored in system data of the flash. */
static void sys_enable_jtag_by_password(char *keystring)
{
	flash_t flash;
	u8 key[8];
	u32 data, key32[8], i = 0, errmap = 0;
	int is_match = 0;
	
	if(strlen(keystring) < 16){
		AT_PRINTK("%s(): Key length should be 16 characters.", __func__);
		return;
	}
	AT_PRINTK("Enter JTAG Key: %s\n", keystring);
	sscanf((const char*)keystring, "%02x%02x%02x%02x%02x%02x%02x%02x", 
		&key32[0], &key32[1], &key32[2], &key32[3], &key32[4], &key32[5], &key32[6], &key32[7]);
	for(i=0; i<8; i++){
		key[i] = key32[i] & 0xFF;
	}

	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_read_word(&flash, FLASH_SYSTEM_DATA_ADDR + 0x40, &errmap);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
	AT_PRINTK("Error Map: 0x%x\n", (errmap & 0xFF));
	if((errmap & 0xFF) == 0){
		AT_PRINTK("You have tried too much times!Locked!\n", keystring);
		return;
	}

	// check if jtag key is correct
	is_match = boot_export_symbol.is_jtag_key_match(key);
	
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_read_word(&flash, FLASH_SYSTEM_DATA_ADDR + 0x44, &data);
	if(data != ~0x0){
		//erase backup sector
		flash_erase_sector(&flash, FLASH_RESERVED_DATA_BASE);
		//backup system data to backup sector
		for(i = 0; i < 0x1000; i+= 4){
			flash_read_word(&flash, FLASH_SYSTEM_DATA_ADDR + i, &data);
			//Erase Errmap and key
			if((i == 0x44) || (i == 0x48))
				data = 0xFFFFFFFF;
			if((i == 0x40) && is_match)
				data = 0xFFFFFFFF;
			flash_write_word(&flash, FLASH_RESERVED_DATA_BASE + i,data);
		}
		
		//erase system data
		flash_erase_sector(&flash, FLASH_SYSTEM_DATA_ADDR);
		//write data back to system data
		for(i = 0; i < 0x1000; i+= 4){
			flash_read_word(&flash, FLASH_RESERVED_DATA_BASE + i, &data);
			flash_write_word(&flash, FLASH_SYSTEM_DATA_ADDR + i,data);
		}
		//erase backup sector
		flash_erase_sector(&flash, FLASH_RESERVED_DATA_BASE);
	}
	//write jtag key
	flash_stream_write(&flash, FLASH_SYSTEM_DATA_ADDR + 0x44, 8, key);
	//update error map
	if(is_match == 0){
		flash_write_word(&flash, FLASH_SYSTEM_DATA_ADDR + 0x40, errmap<<1);
	}
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
}
#endif

void fATSJ(void *arg)
{
	/* To avoid gcc warnings */
	( void ) arg;
	
	//volatile int argc = 0;
	char *argv[MAX_ARGC] = {0};
	(void) argv;
#if defined (CONFIG_PLATFORM_8721D)
	#ifdef AMEBAD_TODO
	AT_PRINTK("[ATSJ]: _AT_SYSTEM_JTAG_");
	if(!arg){
		AT_PRINTK("[ATSJ] Usage: ATSJ=off");
	}else{
		parse_param(arg, argv);
		if (strcmp(argv[1], "off" ) == 0)
			sys_jtag_off();
#if defined(CONFIG_PLATFORM_8711B)
		else if (strcmp(argv[1], "key" ) == 0)
			sys_enable_jtag_by_password(argv[2]); //Enter "FFFFFFFFFFFFFFFF" to clear key in flash
#endif			
		else
			AT_PRINTK("ATSJ=%s is not supported!", argv[1]);
	}
	#endif
#else

	AT_PRINTK("[ATSJ]: _AT_SYSTEM_JTAG_");
	if(!arg){
		AT_PRINTK("[ATSJ] Usage: ATSJ=off");
	}else{
		parse_param(arg, argv);
		if (strcmp(argv[1], "off" ) == 0)
			sys_jtag_off();
#if defined(CONFIG_PLATFORM_8711B)
		else if (strcmp(argv[1], "key" ) == 0)
			sys_enable_jtag_by_password(argv[2]); //Enter "FFFFFFFFFFFFFFFF" to clear key in flash
#endif			
		else
			AT_PRINTK("ATSJ=%s is not supported!", argv[1]);
	}
#endif
}


#if WIFI_LOGO_CERTIFICATION_CONFIG

#define FLASH_ADDR_SW_VERSION 	FAST_RECONNECT_DATA+0x900
#define SW_VERSION_LENGTH 	32


void fATSV(void *arg)
{
	unsigned char sw_version[SW_VERSION_LENGTH+1];
	flash_t flash;

	if(!arg){
		printf("[ATSV]Usage: ATSV=[SW_VERSION]\n\r");
		return;
    }

	if(strlen((char*)arg) > SW_VERSION_LENGTH){
		printf("[ATSV] ERROR : SW_VERSION length can't exceed %d\n\r",SW_VERSION_LENGTH);
		return;
	}

	memset(sw_version,0,SW_VERSION_LENGTH+1);
	strncpy(sw_version, (char*)arg, strlen((char*)arg));

	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_erase_sector(&flash, FAST_RECONNECT_DATA);
	flash_stream_write(&flash, FLASH_ADDR_SW_VERSION, strlen((char*)arg), (uint8_t *) sw_version);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);

	printf("[ATSV] Write SW_VERSION to flash : %s\n\r",sw_version);

}
#endif


void fATSx(void *arg)
{
	/* To avoid gcc warnings */
	( void ) arg;
	
//	uint32_t ability = 0;
	char buf[64];

	AT_PRINTK("[ATS?]: _AT_SYSTEM_HELP_");
	AT_PRINTK("[ATS?]: COMPILE TIME: %s", RTL_FW_COMPILE_TIME);
//	wifi_get_drv_ability(&ability);
	strncpy(buf, "v", sizeof(buf));
//	if(ability & 0x1)
//		strcat(buf, "m");
#if defined(CONFIG_PLATFORM_8710C)
	strcat(buf, ".7.1." RTL_FW_COMPILE_DATE);
#elif defined(CONFIG_PLATFORM_8195BHP)
	strcat(buf, ".5.2." RTL_FW_COMPILE_DATE);
#elif defined(CONFIG_PLATFORM_8721D)
	strcat(buf, ".6.2." RTL_FW_COMPILE_DATE);
#else
	strcat(buf, ".4.0." RTL_FW_COMPILE_DATE);
#endif

#if WIFI_LOGO_CERTIFICATION_CONFIG
	flash_t		flash;
	unsigned char sw_version[SW_VERSION_LENGTH+1];

	memset(sw_version,0,SW_VERSION_LENGTH+1);

	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, FLASH_ADDR_SW_VERSION, SW_VERSION_LENGTH, (uint8_t *)sw_version);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);

	if(sw_version[0] != 0xff)
		AT_PRINTK("[ATS?]: SW VERSION: %s", sw_version);
	else
		AT_PRINTK("[ATS?]: SW VERSION: %s", buf);

#else
	AT_PRINTK("[ATS?]: SW VERSION: %s", buf);
#endif
}



#elif ATCMD_VER == ATVER_2

#define ATCMD_VERSION		"v2" //ATCMD MAJOR VERSION, AT FORMAT CHANGED
#define ATCMD_SUBVERSION	"2" //ATCMD MINOR VERSION, NEW COMMAND ADDED
#define ATCMD_REVISION		"1" //ATCMD FIX BUG REVISION
#define SDK_VERSION		"v3.5" //SDK VERSION
extern void sys_reset(void);
void print_system_at(void *arg);
extern void print_wifi_at(void *arg);
extern void print_tcpip_at(void *arg);

// uart version 2 echo info
extern unsigned char gAT_Echo;


void fATS0(void *arg){
	at_printf("\r\n[AT] OK");
}

void fATSh(void *arg){
	// print common AT command
	at_printf("\r\n[ATS?] ");
	at_printf("\r\nCommon AT Command:");
	print_system_at(arg);
#if CONFIG_WLAN
	at_printf("\r\nWi-Fi AT Command:");
	print_wifi_at(arg);
#endif

#if CONFIG_TRANSPORT
	at_printf("\r\nTCP/IP AT Command:");
	print_tcpip_at(arg);
#endif

	at_printf("\r\n[ATS?] OK");
}

void fATSR(void *arg){
	at_printf("\r\n[ATSR] OK");
	sys_reset();
}

void fATSV(void *arg){
	char at_buf[32];
	char fw_buf[32];

	// get at version
	strncpy(at_buf, ATCMD_VERSION"."ATCMD_SUBVERSION"."ATCMD_REVISION, sizeof(at_buf));

	// get fw version
	strncpy(fw_buf, SDK_VERSION, sizeof(fw_buf));
#if defined CONFIG_PLATFORM_8195A
	at_printf("\r\n[ATSV] OK:%s,%s(%s)",at_buf,fw_buf,RTL8195BFW_COMPILE_TIME);
#elif defined CONFIG_PLATFORM_8710C
	at_printf("\r\n[ATSV] OK:%s,%s(%s)",at_buf,fw_buf,RTL8710CFW_COMPILE_TIME);
#elif defined CONFIG_PLATFORM_8721D
	at_printf("\r\n[ATSV] OK:%s,%s(%s)",at_buf,fw_buf,RTL_FW_COMPILE_TIME);
#endif
}

#if defined(configUSE_WAKELOCK_PMU) && (configUSE_WAKELOCK_PMU == 1)
void fATSP(void *arg){
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	uint32_t lock_id;
	uint32_t bitmap;
	
	if (!arg) {
		AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ERROR, "\r\n[ATSP] Usage: ATSP=<a/r/?>");
		at_printf("\r\n[ATSP] ERROR:1");
		return;
	} else {
		if((argc = parse_param(arg, argv)) != 2){
			AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ERROR, "\r\n[ATSP] Usage: ATSP=<a/r/?>");
			at_printf("\r\n[ATSP] ERROR:1");
			return;
		}
	}

	switch(argv[1][0]) {
		case 'a': // acquire
		{
			pmu_acquire_wakelock(PMU_OS);
			//at_printf("\r\n[ATSP] wakelock:0x%08x", pmu_get_wakelock_status());			
			break;
		}

		case 'r': // release
		{
			pmu_release_wakelock(PMU_OS);
			//at_printf("\r\n[ATSP] wakelock:0x%08x", pmu_get_wakelock_status());
			break;
		}

		case '?': // get status
			break;
		default:
			AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ERROR, "\r\n[ATSP] Usage: ATSP=<a/r/?>");
			at_printf("\r\n[ATSP] ERROR:2");
			return;
	}
	bitmap = pmu_get_wakelock_status();
	at_printf("\r\n[ATSP] OK:%s", (bitmap&BIT(PMU_OS))?"1":"0");
}
#endif

void fATSE(void *arg){
	int argc = 0;
	int echo = 0, mask = gDbgFlag, dbg_lv = gDbgLevel;
	char *argv[MAX_ARGC] = {0};
	int err_no = 0;

	AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ALWAYS, "[ATSE]: _AT_SYSTEM_ECHO_DBG_SETTING");	
	if(!arg){
		AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ERROR, "[ATSE] Usage: ATSE=<echo>,<dbg_msk>,<dbg_lv>");
		err_no = 1;
		goto exit;
	}

	argc = parse_param(arg, argv);

	if(argc < 2 || argc > 4){
		err_no = 2;
		goto exit;
	}

#if (defined(CONFIG_EXAMPLE_UART_ATCMD) && CONFIG_EXAMPLE_UART_ATCMD)
	if(argv[1] != NULL){
		echo = atoi(argv[1]);
		if(echo>1 || echo <0){
			err_no = 3;
			goto exit;
		}
		gAT_Echo = echo?1:0;
	}
#endif

	if((argc > 2) && (argv[2] != NULL)){
		mask = strtoul(argv[2], NULL, 0);
		at_set_debug_mask(mask);
	}
	
	if((argc == 4) && (argv[3] != NULL)){
		dbg_lv = strtoul(argv[3], NULL, 0);
		at_set_debug_level(dbg_lv);
	}
	
exit:
	if(err_no)
		at_printf("\r\n[ATSE] ERROR:%d", err_no);
	else
		at_printf("\r\n[ATSE] OK");
	return;
}
#if CONFIG_WLAN
extern int EraseApinfo();
extern int Erase_Fastconnect_data();

void fATSY(void *arg){
#if CONFIG_EXAMPLE_WLAN_FAST_CONNECT
	Erase_Fastconnect_data();
#endif

#if (defined(CONFIG_EXAMPLE_UART_ATCMD) && CONFIG_EXAMPLE_UART_ATCMD)
	reset_uart_atcmd_setting();
#endif

#if CONFIG_OTA_UPDATE
	// Reset ota image  signature
	cmd_ota_image(0);
#endif	
	
	at_printf("\r\n[ATSY] OK");
	// reboot
	sys_reset();
}

#if CONFIG_OTA_UPDATE
extern int wifi_is_connected_to_ap( void );
void fATSO(void *arg){
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	
	if(!arg){
		AT_DBG_MSG(AT_FLAG_OTA, AT_DBG_ERROR, "\r\n[ATSO] Usage: ATSO=<ip>,<port>");
		at_printf("\r\n[ATSO] ERROR:1");
		return;
	}
	argv[0] = "update";
	if((argc = parse_param(arg, argv)) != 3){
		AT_DBG_MSG(AT_FLAG_OTA, AT_DBG_ERROR, "\r\n[ATSO] Usage: ATSO=<ip>,<port>");
		at_printf("\r\n[ATSO] ERROR:1");
		return;
	}

	// check wifi connect first
	if(wifi_is_connected_to_ap()==0){
		cmd_update(argc, argv);
		at_printf("\r\n[ATSO] OK");
		
	}else{
		at_printf("\r\n[ATSO] ERROR:3");
	}
}

void fATSC(void *arg){
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	int cmd = 0;
	
	if(!arg){
		AT_DBG_MSG(AT_FLAG_OTA, AT_DBG_ERROR, "\r\n[ATSC] Usage: ATSC=<0/1>");
		at_printf("\r\n[ATSC] ERROR:1");
		return;
	}
	if((argc = parse_param(arg, argv)) != 2){
		AT_DBG_MSG(AT_FLAG_OTA, AT_DBG_ERROR, "\r\n[ATSC] Usage: ATSC=<0/1>");
	  at_printf("\r\n[ATSC] ERROR:1");
	  return;
	}

	cmd = atoi(argv[1]);

	if((cmd!=0)&&(cmd!=1)){
		at_printf("\r\n[ATSC] ERROR:2");
		return;
	}
		
	at_printf("\r\n[ATSC] OK");

 	if(cmd == 1){
 		cmd_ota_image(1);
 	}
	else{
		cmd_ota_image(0);
	}
	// reboot
	sys_reset();
}
#endif

#if (defined(CONFIG_EXAMPLE_UART_ATCMD) && CONFIG_EXAMPLE_UART_ATCMD)
extern const u32 log_uart_support_rate[];

void fATSU(void *arg){
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	u32 baud = 0;
	u8 databits = 0;
	u8 stopbits = 0;
	u8 parity = 0;
	u8 flowcontrol = 0;
	u8 configmode = 0;
	int i;
	UART_LOG_CONF uartconf;
	
	if(!arg){
		AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ERROR, 
		"[ATSU] Usage: ATSU=<baud>,<databits>,<stopbits>,<parity>,<flowcontrol>,<configmode>");
		at_printf("\r\n[ATSU] ERROR:1");
		return;
	}
	if((argc = parse_param(arg, argv)) != 7){
		AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ERROR, 
		"[ATSU] Usage: ATSU=<baud>,<databits>,<stopbits>,<parity>,<flowcontrol>,<configmode>");
		at_printf("\r\n[ATSU] ERROR:1");
		return;
	}

	baud = atoi(argv[1]);
	databits = atoi(argv[2]);
	stopbits = atoi(argv[3]);
	parity = atoi(argv[4]);
	flowcontrol = atoi(argv[5]);
	configmode = atoi(argv[6]);
/*
    // Check Baud rate
    for (i=0; log_uart_support_rate[i]!=0xFFFFFF; i++) {
        if (log_uart_support_rate[i] == baud) {
            break;
        }
    }
    
    if (log_uart_support_rate[i]== 0xFFFFFF) {
		at_printf("\r\n[ATSU] ERROR:2");
        return;
    }
*/
	if(((databits < 5) || (databits > 8))||\
		((stopbits < 1) || (stopbits > 2))||\
		((parity < 0) || (parity > 2))||\
		((flowcontrol < 0) || (flowcontrol > 1))||\
		((configmode < 0) || (configmode > 3))\
		){
		at_printf("\r\n[ATSU] ERROR:2");
		return;
	}
	
	memset((void*)&uartconf, 0, sizeof(UART_LOG_CONF));
	uartconf.BaudRate = baud;
	uartconf.DataBits = databits;
	uartconf.StopBits = stopbits;
	uartconf.Parity = parity;
	uartconf.FlowControl = flowcontrol;
	AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ALWAYS, 
		"AT_UART_CONF: %d,%d,%d,%d,%d", uartconf.BaudRate, uartconf.DataBits,uartconf.StopBits,uartconf.Parity,uartconf.FlowControl);
	switch(configmode){
		case 0: // set current configuration, won't save
			uart_atcmd_reinit(&uartconf);
			break;
		case 1: // set current configuration, and save
			write_uart_atcmd_setting_to_system_data(&uartconf);
			uart_atcmd_reinit(&uartconf);
			break;
		case 2: // set configuration, reboot to take effect
			write_uart_atcmd_setting_to_system_data(&uartconf);
			break;
	}
	
	at_printf("\r\n[ATSU] OK");
}
#endif //#if (defined(CONFIG_EXAMPLE_UART_ATCMD) && CONFIG_EXAMPLE_UART_ATCMD)
#endif //#if CONFIG_WLAN

void fATSG(void *arg)
{
	gpio_t gpio_ctrl;
	int argc = 0, val, error_no = 0;
	char *argv[MAX_ARGC] = {0}, port, num;
	PinName pin = NC;

	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: _AT_SYSTEM_GPIO_CTRL_");

	if(!arg){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ERROR, 
		"[ATSG] Usage: ATSG=<R/W>,<PORT>,<DATA>,<DIR>,<PULL>");
		error_no = 1;
		goto exit;
	}
	if((argc = parse_param(arg, argv)) < 3){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ERROR, 
			"[ATSG] Usage: ATSG=<R/W>,<PORT>,<DATA>,<DIR>,<PULL>");
		error_no = 2;
		goto exit;
	}	

	port = argv[2][1];
	num = strtoul(&argv[2][3], NULL, 0);
	port -= 'A';
	pin = (port << 4 | num);
	AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "PORT: %s[%d]", argv[2], pin);
	
	if(gpio_set(pin) == 0xff)
	{
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ERROR, "[ATSG]: Invalid Pin Name [%d]", pin);
		error_no = 3;
		goto exit;
	}

	if(port != 0 && port != 1){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: Invalid Port");
		error_no = 3;
		goto exit;
	}

	if(num < 0||num>31){
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "[ATSG]: Invalid Pin Number");
		error_no = 3;
		goto exit;
	}

	gpio_init(&gpio_ctrl, pin);
	if(argv[4]){
		int dir = atoi(argv[4]);
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "DIR: %s", argv[4]);
		gpio_dir(&gpio_ctrl, dir);
	}
	if(argv[5]){
		int pull = atoi(argv[5]);
		AT_DBG_MSG(AT_FLAG_GPIO, AT_DBG_ALWAYS, "PULL: %s", argv[5]);
		gpio_mode(&gpio_ctrl, pull);
	}
	if(argv[1][0] == 'R'){
		gpio_dir(&gpio_ctrl, PIN_INPUT);
		val = gpio_read(&gpio_ctrl);
	}
	else if(argv[1][0] == 'W'){
		val = atoi(argv[3]);
		gpio_dir(&gpio_ctrl, PIN_OUTPUT);
		gpio_write(&gpio_ctrl, val);
	}
	
exit:
	if(error_no){
		at_printf("\r\n[ATSG] ERROR:%d", error_no);
	}
	else{
		at_printf("\r\n[ATSG] OK:%d", val);
	}
}

#endif //#elif ATCMD_VER == ATVER_2
#if defined(configUSE_WAKELOCK_PMU) && (configUSE_WAKELOCK_PMU == 1)
void fATSL(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	int err_no = 0;
	(void) err_no;
	uint32_t lock_id;

	AT_DBG_MSG(AT_FLAG_OS, AT_DBG_ALWAYS, "[ATSL]: _AT_SYS_WAKELOCK_TEST_");

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_OS, AT_DBG_ALWAYS, "[ATSL] Usage ATSL=[a/r/?][bitmask]");
		err_no = 1;
		goto exit;
	} else {
		argc = parse_param(arg, argv);
		if (argc < 2) {
			AT_DBG_MSG(AT_FLAG_OS, AT_DBG_ALWAYS, "[ATSL] Usage ATSL=[a/r/?][bitmask]");
			err_no = 2;
			goto exit;
		}
	}

	switch(argv[1][0]) {
		case 'a': // acquire
		{
			if (argc == 3) {
				lock_id = strtoul(argv[2], NULL, 16);
				pmu_acquire_wakelock(lock_id);
			}
			AT_DBG_MSG(AT_FLAG_OS, AT_DBG_ALWAYS, "[ATSL] wakelock:0x%08x", pmu_get_wakelock_status());			
			break;
		}

		case 'r': // release
		{
			if (argc == 3) {
				lock_id = strtoul(argv[2], NULL, 16);
				pmu_release_wakelock(lock_id);
			}
			AT_DBG_MSG(AT_FLAG_OS, AT_DBG_ALWAYS, "[ATSL] wakelock:0x%08x", pmu_get_wakelock_status());
			break;
		}

		case '?': // get status
			AT_DBG_MSG(AT_FLAG_OS, AT_DBG_ALWAYS, "[ATSL] wakelock:0x%08x", pmu_get_wakelock_status());
#if (configGENERATE_RUN_TIME_STATS == 1)
			//pmu_get_wakelock_hold_stats((char *)cBuffer);
			AT_DBG_MSG(AT_FLAG_OS, AT_DBG_ALWAYS, "%s", cBuffer);
#endif
			break;

#if (configGENERATE_RUN_TIME_STATS == 1)
		case 'c': // clean wakelock info (for recalculate wakelock hold time)
			AT_DBG_MSG(AT_FLAG_OS, AT_DBG_ALWAYS, "[ATSL] clean wakelock stat");
			//pmu_clean_wakelock_stat();
			break;
#endif
		default:
			AT_DBG_MSG(AT_FLAG_OS, AT_DBG_ALWAYS, "[ATSL] Usage ATSL=[a/r/?][bitmask]");
			err_no = 3;
			break;
	}
exit:
#if ATCMD_VER == ATVER_2
	if(err_no)
		at_printf("\r\n[ATSL] ERROR:%d", err_no);
	else
		at_printf("\r\n[ATSL] OK:0x%08x",pmu_get_wakelock_status());
#endif
	return;
}
#endif

log_item_t at_sys_items[] = {
#ifndef CONFIG_INIC_NO_FLASH
#if ATCMD_VER == ATVER_1
#if defined(CONFIG_PLATFORM_8710C)
	{"ATXX", fATXX,{NULL,NULL}},
#endif
	{"ATSD", fATSD,{NULL,NULL}},	// Dump register
	{"ATSE", fATSE,{NULL,NULL}},	// Edit register
#if defined(CONFIG_PLATFORM_8711B)
	{"ATSK", fATSK,},   // Set RDP/RSIP enable and key
#endif
#if CONFIG_OTA_UPDATE
	{"ATSC", fATSC,},	// Clear OTA signature
	{"ATSR", fATSR,},	// Recover OTA signature
#endif
#if defined(CONFIG_UART_YMODEM) && CONFIG_UART_YMODEM
	{"ATSY", fATSY,},	// uart ymodem upgrade
#endif
#if defined(SUPPORT_MP_MODE) && SUPPORT_MP_MODE
	{"ATSA", fATSA,},	// MP ADC test
	{"ATSG", fATSG,},	// MP GPIO test
	{"ATSP", fATSP,},	// MP Power related test
	{"ATSB", fATSB,},	// OTU PIN setup			
#endif
#if (configGENERATE_RUN_TIME_STATS == 1)
	{"ATSS", fATSS,},	// Show CPU stats
#endif
#if SUPPORT_CP_TEST
	{"ATSM", fATSM,},	// Apple CP test
#endif
#if !defined(CONFIG_PLATFORM_8195BHP) && !defined(CONFIG_PLATFORM_8710C)
	{"ATSJ", fATSJ,{NULL,NULL}}, //trun off JTAG
#endif
	{"ATS@", fATSs,{NULL,NULL}},	// Debug message setting
	{"ATS!", fATSc,{NULL,NULL}},	// Debug config setting
	{"ATS#", fATSt,{NULL,NULL}},	// test command
	{"ATS?", fATSx,{NULL,NULL}},	// Help
#if WIFI_LOGO_CERTIFICATION_CONFIG
	{"ATSV", fATSV},				// Write SW version for wifi logo test
#endif
#elif ATCMD_VER == ATVER_2 //#if ATCMD_VER == ATVER_1
	{"AT", 	 fATS0,},	// test AT command ready
	{"ATS?", fATSh,},	// list all AT command
	{"ATSR", fATSR,},	// system restart
	{"ATSV", fATSV,},	// show version info
#if defined(CONFIG_PLATFORM_8195A)
	{"ATSP", fATSP,},	// power saving mod
#endif
	{"ATSE", fATSE,},	// enable and disable echo
#if CONFIG_WLAN
	{"ATSY", fATSY,},	// factory reset
#if CONFIG_OTA_UPDATE
	{"ATSO", fATSO,},	// ota upgrate
	{"ATSC", fATSC,},	// chose the activited image
#endif
#if (defined(CONFIG_EXAMPLE_UART_ATCMD) && CONFIG_EXAMPLE_UART_ATCMD)
	{"ATSU", fATSU,},	// AT uart configuration
#endif
#endif
	{"ATSG", fATSG,},	// GPIO control
#endif // end of #if ATCMD_VER == ATVER_1

// Following commands exist in two versions
#if defined(configUSE_WAKELOCK_PMU) && (configUSE_WAKELOCK_PMU == 1)
	{"ATSL", fATSL,{NULL,NULL}},	 // wakelock test
#endif
#endif
};

#if ATCMD_VER == ATVER_2
void print_system_at(void *arg){
	int index;
	int cmd_len = 0;

	cmd_len = sizeof(at_sys_items)/sizeof(at_sys_items[0]);
	for(index = 0; index < cmd_len; index++)
		at_printf("\r\n%s", at_sys_items[index].log_cmd);
}
#endif
void at_sys_init(void)
{
	log_service_add_table(at_sys_items, sizeof(at_sys_items)/sizeof(at_sys_items[0]));
}

#if SUPPORT_LOG_SERVICE
log_module_init(at_sys_init);
#endif
