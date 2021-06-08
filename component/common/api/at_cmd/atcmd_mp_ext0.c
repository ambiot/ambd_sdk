#include <platform_stdlib.h>
#include <platform_opts.h>
#include <gpio_api.h>
#include "log_service.h"
#include "osdep_service.h"
#include "atcmd_mp.h"
#include "serial_api.h"
#include "serial_ex_api.h"

#if CONFIG_ATCMD_MP_EXT0

#define UART_TX    			PA_7
#define UART_RX    			PA_6

#define UART_BT_TX			PC_9
#define UART_BT_RX			PC_6

#define ANTENNA_SW0			PB_6
#define ANTENNA_SW1			PB_7

#define GPIO_BT_EN			PE_5
#define GPIO_WLAN_ACT		PC_3
#define GPIO_BT_SET			PC_1
#define GPIO_BT_ACT			PC_0
#define GPIO_WAKE_HOST		PE_2

#define GPIO_CLK_REQ		PC_7


#define MP_EXT0_PREFIX		"[ATM0]: "
#define MP_EXT0_PRINTF(...) \
		do{ \
			_AT_PRINTK(MP_EXT0_PREFIX); \
			_AT_PRINTK(__VA_ARGS__); \
		}while(0)

extern void bt_uart_bridge_set(uint32_t baudrate_0, uint32_t baudrate_1, uint8_t parity, uint8_t debug);
extern void bt_uart_bridge_close(void);
extern void bt_uart_bridge_open(PinName tx, PinName rx);
extern int uart_h5_to_h4_translate(int baudrate);
extern u8 key_2char2num(u8 hch, u8 lch);
//------------------------------------------------------------------------------
static int mp_ext0_efuse(void **argv, int argc)
{	
	int ret = -1;
	
	if(argc == 1){
		int result;
		if(strcmp(argv[0], "sip" ) == 0){
			result = HalCheckEfuseSip();
		}else if(strcmp(argv[0], "combo" ) == 0){
			result = HalCheckEfuseComboSip();
		}else if(strcmp(argv[0], "moc100" ) == 0){
			result = HalCheckEfuseMICO100();
		}
		if(result == 1){
			MP_EXT0_PRINTF("check efuse success.\n");
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
			wlan_network();
#endif
			ret = 0;
		}else if(result == 2){
			MP_EXT0_PRINTF("efuse had data.\n");
			ret = 1;
		}else{
			MP_EXT0_PRINTF("check efuse fail.\n");
		}
	}
	return ret;
}

static int mp_ext0_switch_antenna(void **argv, int argc)
{
	int ret = -1;
	gpio_t gpio_sw0, gpio_sw1;

	gpio_init(&gpio_sw0, ANTENNA_SW0);
	gpio_init(&gpio_sw1, ANTENNA_SW1);
	gpio_dir(&gpio_sw0, PIN_OUTPUT);
	gpio_dir(&gpio_sw1, PIN_OUTPUT);
	gpio_mode(&gpio_sw0, PullNone);     // No pull
	gpio_mode(&gpio_sw1, PullNone);

#if 1
	extern u16 GPIOState[11];
	GPIOState[1] &= ~0xC0;	// B6, B7
	if(strcmp(argv[0], "wlan" ) == 0){
		gpio_write(&gpio_sw0, 1);
		gpio_write(&gpio_sw1, 0);
		MP_EXT0_PRINTF("Switch antenna to WLAN.\n");
		ret = 0;
	}else if(strcmp(argv[0], "bt" ) == 0){
		gpio_write(&gpio_sw0, 0);
		gpio_write(&gpio_sw1, 1);
		MP_EXT0_PRINTF("Switch antenna to BT.\n");
		ret = 0;
	}
#else
	// need disable power saving mode first.
	if (strcmp(argv[0], "wlan" ) == 0){
		// MAC system Reg
		HAL_WRITE32(SYSTEM_CTRL_BASE, 0x320, HAL_READ32(SYSTEM_CTRL_BASE, 0x320) | BIT1);
		HAL_WRITE32(SYSTEM_CTRL_BASE, 0x2a4, HAL_READ32(SYSTEM_CTRL_BASE, 0x2a4) | BIT9);// bit 8: enable RFE CTRL 0 & 1, bit 9: enable RFE CTRL 2 & 3

		//ODM_SetBBReg(pDM_Odm, 0x74 , BIT0, 1);  // MAC output pin select DPDT_P and DPDT_N as output pin, bit 0: CTRL RFE CTRL 0 & 1 by BB, bit 2: CTRL RFE CTRL 2 & 3 by BB
		HAL_WRITE32(WIFI_REG_BASE, 0x74, 0xE);

		//ODM_SetBBReg(pDM_Odm, 0x944 , BIT2|BIT3, 3); // PAD.E enable RFE_CTRL 2 & 3
		//ODM_SetBBReg(pDM_Odm, 0x944 , BIT31, 0); // 0: disable buffer
		HAL_WRITE32(WIFI_REG_BASE, 0x944, 0xC);
		
		//ODM_SetBBReg(pDM_Odm, 0x930 , 0xF0, 7); // DPDT_P = 0
		//ODM_SetBBReg(pDM_Odm, 0x930 , 0xF, 7); // DPDT_N = 0
		HAL_WRITE32(WIFI_REG_BASE, 0x930, 0x7700);
		
		//ODM_SetBBReg(pDM_Odm, 0x92C, bMaskDWord, 0x4);
		HAL_WRITE32(WIFI_REG_BASE, 0x92C, 0x4);
		
		MP_EXT0_PRINTF("0x92C: 0x4\n");
	}else if (strcmp(argv[0], "bt" ) == 0){
		HAL_WRITE32(SYSTEM_CTRL_BASE, 0x320, HAL_READ32(SYSTEM_CTRL_BASE, 0x320) | BIT1);
		HAL_WRITE32(SYSTEM_CTRL_BASE, 0x2a4, HAL_READ32(SYSTEM_CTRL_BASE, 0x2a4) | BIT9);// bit 8: enable RFE CTRL 0 & 1, bit 9: enable RFE CTRL 2 & 3

		//ODM_SetBBReg(pDM_Odm, 0x74 , BIT0, 1);  // MAC output pin select DPDT_P and DPDT_N as output pin, bit 0: CTRL RFE CTRL 0 & 1 by BB, bit 2: CTRL RFE CTRL 2 & 3 by BB
		HAL_WRITE32(WIFI_REG_BASE, 0x74, 0xE);
		
		//ODM_SetBBReg(pDM_Odm, 0x944 , BIT2|BIT3, 3); // PAD.E enable RFE_CTRL 2 & 3
		//ODM_SetBBReg(pDM_Odm, 0x944 , BIT31, 0); // 0: disable buffer
		HAL_WRITE32(WIFI_REG_BASE, 0x944, 0xC);
		
		//ODM_SetBBReg(pDM_Odm, 0x930 , 0xF0, 7); // DPDT_P = 0
		//ODM_SetBBReg(pDM_Odm, 0x930 , 0xF, 7); // DPDT_N = 0
		HAL_WRITE32(WIFI_REG_BASE, 0x930, 0x7700);
		
		//ODM_SetBBReg(pDM_Odm, 0x92C, bMaskDWord, 0x8);
		HAL_WRITE32(WIFI_REG_BASE, 0x92C, 0x8);
		
		MP_EXT0_PRINTF("0x92C: 0x8\n");
	}
#endif
	return ret;
}

static int mp_ext0_bt_power(void **argv, int argc)
{
	gpio_t gpio_bt_en, gpio_wlan_act, gpio_bt_set, gpio_bt_act, gpio_wake_host;
	gpio_t gpio_clk_req;
		
	if(strcmp(argv[0], "on" ) == 0){
		// BT power on
		// disable jtag for releasing PE_2
		sys_jtag_off();
		// disable PTA for releasing PC_0, PC_1, PC_3
		PinCtrl(WL_BTCOEX, S0, OFF);
		
		// Init LED control pin
		gpio_init(&gpio_bt_en, GPIO_BT_EN);
		gpio_init(&gpio_wlan_act, GPIO_WLAN_ACT);
		gpio_init(&gpio_bt_set, GPIO_BT_SET);
		gpio_init(&gpio_bt_act, GPIO_BT_ACT);
		gpio_init(&gpio_wake_host, GPIO_WAKE_HOST);
		gpio_init(&gpio_clk_req, GPIO_CLK_REQ);
		
		gpio_dir(&gpio_bt_en, PIN_OUTPUT);    // Direction: Output
		gpio_dir(&gpio_wlan_act, PIN_OUTPUT);
		gpio_dir(&gpio_bt_set, PIN_OUTPUT);
		gpio_dir(&gpio_bt_act, PIN_OUTPUT);
		//gpio_dir(&gpio_wake_host, PIN_OUTPUT);
		gpio_dir(&gpio_wake_host, PIN_INPUT);	// Direction: Input, for power leakage
		gpio_dir(&gpio_clk_req, PIN_INPUT);		// Direction: Input, for power leakage
			
		gpio_mode(&gpio_bt_en, PullNone);     // No pull
		gpio_mode(&gpio_wlan_act, PullNone);
		gpio_mode(&gpio_bt_set, PullNone);
		gpio_mode(&gpio_bt_act, PullNone);
		gpio_mode(&gpio_wake_host, PullNone);
		gpio_mode(&gpio_clk_req, PullNone);
		
		// BT_EN_CHIP pull low
		gpio_write(&gpio_bt_en, 0);
		
		// delay 10 ms
		rtw_mdelay_os(10);
		
		// BT power-on trap pins
		gpio_write(&gpio_wlan_act, 0);
		gpio_write(&gpio_bt_set, 0);
		gpio_write(&gpio_bt_act, 0);
		//gpio_write(&gpio_wake_host, 0);
		
		// delay 10 ms
		rtw_mdelay_os(10);
		
		// BT_EN_CHIP pull high
		gpio_write(&gpio_bt_en, 1);
		
		// delay 10 ms, BT state machine needs 600us to keep power on trap value.
		rtw_mdelay_os(10);
		
		// Enable PTA for PTA test
		  // mp_start to disalbe ips and lps for writing wlan register
		wext_private_command("wlan0", "mp_start", 1);
		  // Init PTA
		PinCtrl(WL_BTCOEX, S0, ON);
		HAL_WRITE32(0x40080000, 0x74, ((HAL_READ32(0x40080000, 0x74)&0xFFF8FFFF)|0x10000));
		HAL_WRITE32(0x40080000, 0x790, (HAL_READ32(0x40080000, 0x790)|0x5));
		HAL_WRITE32(0x40080000, 0x76C, (HAL_READ32(0x40080000, 0x76C)|0x40100));
		HAL_WRITE32(0x40080000, 0x778, (HAL_READ32(0x40080000, 0x778)|BIT0));
		
		MP_EXT0_PRINTF("BT power on.\n");
		
	}else if(strcmp(argv[0], "off" ) == 0){
		// BT power off
		gpio_init(&gpio_bt_en, GPIO_BT_EN);
		gpio_dir(&gpio_bt_en, PIN_OUTPUT);    // Direction: Output
		gpio_mode(&gpio_bt_en, PullNone);     // No pull
		// BT_EN_CHIP pull low
		gpio_write(&gpio_bt_en, 0);
		MP_EXT0_PRINTF("BT power off.\n");
	}
	return 0;
}

static int mp_ext0_uart_bridge(void **argv, int argc)
{
	int pinmap = 0;
	char *ptmp;	
	if(argc == 3 || argc == 4){
		uint32_t baudrate0, baudrate1;
		uint8_t parity;
		
		baudrate0 = strtoul(argv[0], &ptmp, 10);
		baudrate1 = strtoul(argv[1], &ptmp, 10);
		parity = strtoul(argv[2], &ptmp, 10);
		if(argc == 4 && strcmp(argv[3], "debug") == 0)
			bt_uart_bridge_set(baudrate0, baudrate1, parity, 1);
		else
			bt_uart_bridge_set(baudrate0, baudrate1, parity, 0);
		MP_EXT0_PRINTF("UART bridge baudrate0 = %d, baudrate1 = %d, parity = %d\n", baudrate0, baudrate1, parity);
	}else if(argc == 1){
		if(strcmp(argv[0], "close") == 0){
			bt_uart_bridge_close();
			MP_EXT0_PRINTF("close UART bridge.\n");
			return 0;
		}
		pinmap = strtoul(argv[0], &ptmp, 10);
		MP_EXT0_PRINTF("UART Pinmap %d.\n", pinmap);
	}
	switch(pinmap){
		case 0: bt_uart_bridge_open(PA_7, PA_6); break;
		case 1: bt_uart_bridge_open(PA_4, PA_0); break;
		case 2: bt_uart_bridge_open(PB_5, PB_4); break;
		case 3: bt_uart_bridge_open(PD_3, PD_0); break;
		case 4: bt_uart_bridge_open(PD_7, PD_4); break;
		default: bt_uart_bridge_open(PA_7, PA_6); break;
	}
	MP_EXT0_PRINTF("open UART bridge.\n");
	return 0;
}

static int mp_ext0_gpio(void **argv, int argc)
{
	gpio_t gpio_test;
    int i, val, write=0, data=0;
	PinName pin[] = {	PA_0, PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7,
    					/*PB_0, PB_1,*/
    					PB_2, PB_3, PB_4, PB_5,
						PD_0, PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7, PD_8, PD_9,
						PE_3, PE_4 };
	
	// disable jtag for releasing PE_3, PE_4
	sys_jtag_off();
	
	if(argc > 0){
		if(strcmp(argv[0], "w") == 0){
			write = 1;
			if(strcmp(argv[1], "1") == 0)
				data = 1;
			MP_EXT0_PRINTF("gpio %s %s\n", argv[0], argv[1]);
		}
		for(i=0; i<(sizeof(pin)/sizeof(PinName)); i++){
			gpio_init(&gpio_test, pin[i]);
			if(write){
				gpio_dir(&gpio_test, PIN_OUTPUT);    // Direction: Output
				gpio_mode(&gpio_test, PullNone);     // No pull
				gpio_write(&gpio_test, data);
			}else{
				gpio_dir(&gpio_test, PIN_INPUT);     // Direction: Input
				gpio_mode(&gpio_test, PullUp);       // Pull-High
				val = gpio_read(&gpio_test);
				MP_EXT0_PRINTF("0x%02x = %d\n", pin[i], val);
			}
		}
	}
	return 0;
}

static int mp_ext0_h5_to_h4(void **argv, int argc)
{
	int ret;
	uint32_t delay;
	char *ptmp;
	
	if(argc == 1){
		delay = strtoul(argv[0], &ptmp, 10);
		if(delay < 10000){
			char *argv = "on";
			ret = mp_ext0_bt_power((void**)&argv, 1);
			rtw_mdelay_os(delay);	// wait FW boot up (1200ms) for UART h5toh4 stable
		}
	}
	ret = uart_h5_to_h4_translate(115200);
	if(ret == 0)
		MP_EXT0_PRINTF("UART H5 to H4 success.\n");
	else
		MP_EXT0_PRINTF("UART H5 to H4 fail.\n");
		
	return ret;
}

static int mp_ext0_pta(void **argv, int argc)
{
	uint32_t reg_hp_txrx, reg_lp_txrx, u32tmp;
	uint32_t reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;
	
	if(argc == 1){
		if(strcmp(argv[0], "off") == 0){
			PinCtrl(WL_BTCOEX, S0, OFF);
			MP_EXT0_PRINTF("PTA off.\n");
			return 0;
		}
	}
	// mp_start for disalbe ips and lps
	wext_private_command("wlan0", "mp_start", 1);

	//Init PTA
	PinCtrl(WL_BTCOEX, S0, ON);
	HAL_WRITE32(0x40080000, 0x74, ((HAL_READ32(0x40080000, 0x74)&0xFFF8FFFF)|0x10000));
	HAL_WRITE32(0x40080000, 0x790, (HAL_READ32(0x40080000, 0x790)|0x5));
	HAL_WRITE32(0x40080000, 0x76C, (HAL_READ32(0x40080000, 0x76C)|0x40100));
	HAL_WRITE32(0x40080000, 0x778, (HAL_READ32(0x40080000, 0x778)|BIT0));

	// wait for receive PTA signal
	rtw_mdelay_os(200);
	
	// get PAT Tx/Rx count
	reg_hp_txrx = 0x770;
	reg_lp_txrx = 0x774;	
	u32tmp = HAL_READ32(0x40080000, reg_hp_txrx);
	reg_hp_tx = u32tmp & 0x0000ffff;
	reg_hp_rx = (u32tmp & 0xffff0000) >> 16;

	u32tmp = HAL_READ32(0x40080000, reg_lp_txrx);
	reg_lp_tx = u32tmp & 0x0000ffff;
	reg_lp_rx = (u32tmp & 0xffff0000) >> 16;
	
	if((reg_hp_tx + reg_hp_rx + reg_lp_tx + reg_lp_rx) > 0){
		MP_EXT0_PRINTF("PTA success.\n");
	}else{
		MP_EXT0_PRINTF("PTA fail.\n");
	}
	return 0;
}

static int mp_ext0_uart(void **argv, int argc)
{
	int ret;
	serial_t sobj;
	uint8_t rx_buf[32];
	uint8_t	tx_buf[]={0x01,0x09,0x10,0x00};
	
	// open uart
	serial_init(&sobj, UART_BT_TX, UART_BT_RX);
	serial_baud(&sobj, 115200);
	serial_format(&sobj, 8, ParityNone, 1);	// H4
	// send data
	rtw_mdelay_os(10); // wait for BT boot stable
	serial_send_blocked(&sobj, (char*)tx_buf, 4, 4);
	// recv data
	ret = serial_recv_stream_timeout(&sobj, (char*)rx_buf, 7, 200, NULL);
	if(ret > 0) {
		if(rx_buf[0] != 0x04)
			ret = -1;
	}
	if(ret <= 0)
		MP_EXT0_PRINTF("BT UART fail.\n");
	else
		MP_EXT0_PRINTF("BT UART success.\n");
	// close uart
	serial_free(&sobj);
	PinCtrl(UART2, sobj.hal_uart_adp.PinmuxSelect, OFF); // fix ROM code: HalRuartDeInitRtl8195a to free PIN C6~C9
	
	return ret;
}

static int mp_ext0_uart_send(void **argv, int argc)
{
	int i, j, ret, tx_len, rx_len;
	serial_t sobj;
	uint8_t buf[64];
	
	if(argc == 2){
		char *ptmp;
		
		tx_len = strlen(argv[0]);
		if(tx_len % 2) return -1;
		tx_len /= 2;
		if(tx_len == 0) return -1;
		if(tx_len > 64) return -1;
		rx_len = strtoul(argv[1], &ptmp, 10);
		if(rx_len > 64) return -1;
		
		MP_EXT0_PRINTF("send: (%d) ", tx_len);
		for(i=0, j=0; i<tx_len; i++, j+=2){
			char *data = argv[0];
			buf[i] = key_2char2num(data[j], data[j+1]);
			_AT_PRINTK("%02x,", buf[i]);
		}
		_AT_PRINTK("\n");
		// open uart
		serial_init(&sobj, UART_BT_TX, UART_BT_RX);
		serial_baud(&sobj, 115200);
		serial_format(&sobj, 8, ParityNone, 1);
		// send data
		serial_send_blocked(&sobj, (char*)buf, tx_len, tx_len);
		// recv data
		if(rx_len > 0){
			ret = serial_recv_stream_timeout(&sobj, (char*)buf, rx_len, 1000, NULL);
			if (ret > 0) {
				MP_EXT0_PRINTF("recv: (%d) ", ret);
				for(i=0; i<ret; i++){
					_AT_PRINTK("%02x,", buf[i]);
				}
				_AT_PRINTK("\n");
			}
		}
		// close uart
		serial_free(&sobj);
		return 0;
	}
	return -1;
}

unsigned char BT_RTL8761A_3DH5_PKT_TX_Begin[][9] = {
// Len ,uart_ raw data
//Len 0    1    2    3    4    5    6    7 
0x08,0x01,0x4a,0xfd,0x04,0x9e,0xd5,0x60,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x00,0x00,0x10,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x00,0x00,0x10,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x02,0x00,0x8d,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x97,0xf0,0x0e,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x97,0xf8,0x0e,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x96,0x98,0xca,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x96,0xe8,0xdf,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x98,0x78,0xa0,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x99,0xd4,0x01,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x8e,0xf2,0x58,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x8f,0x9a,0x9f,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x90,0x99,0x2d,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x91,0xcc,0xf7,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x97,0x78,0x0e,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x99,0x00,0x00,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x00,0x00,0x10,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x3f,0x00,0x00,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x99,0x00,0x02,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x9e,0xd5,0x60,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x97,0x78,0x0f,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x97,0x78,0x0f,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x82,0xf1,0xff,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x80,0x02,0x00,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x9f,0x10,0x00,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x80,0x00,0x00,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x97,0x79,0x0f,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x97,0x78,0x0f,0x00
};

unsigned char BT_RTL8761A_3DH5_PKT_TX_Stop[][9] = {
// Len ,uart_ raw data
//Len 0    1    2    3    4    5    6    7    
0x08,0x01,0x4a,0xfd,0x04,0x99,0x00,0x00,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x97,0x70,0x00,0x00,	
0x08,0x01,0x4a,0xfd,0x04,0x00,0x00,0x00,0x00	
};

static int mp_ext0_bt_pkt_tx(void **argv, int argc)
{
	serial_t sobj;
	int i;
	
	// open uart
	serial_init(&sobj, UART_BT_TX, UART_BT_RX);
	serial_baud(&sobj, 115200);
	serial_format(&sobj, 8, ParityNone, 1);
	// send data
	if(argc == 1){
		if(strcmp(argv[0], "start") == 0){
			MP_EXT0_PRINTF("BT pkt tx start.\n");
			for(i=0; i<(sizeof(BT_RTL8761A_3DH5_PKT_TX_Begin)/9); i++){
				serial_send_blocked(&sobj, &BT_RTL8761A_3DH5_PKT_TX_Begin[i][1], BT_RTL8761A_3DH5_PKT_TX_Begin[i][0], BT_RTL8761A_3DH5_PKT_TX_Begin[i][0]);
			}
		}else if(strcmp(argv[0], "stop") == 0){
			MP_EXT0_PRINTF("BT pkt tx stop.\n");
			for(i=0; i<(sizeof(BT_RTL8761A_3DH5_PKT_TX_Stop)/9); i++){
				serial_send_blocked(&sobj, &BT_RTL8761A_3DH5_PKT_TX_Stop[i][1], BT_RTL8761A_3DH5_PKT_TX_Stop[i][0], BT_RTL8761A_3DH5_PKT_TX_Stop[i][0]);
			}
		}
	}
	// close uart
	serial_free(&sobj);
	return 0;
}

#define EFUSE_USAGE			"ATM0=efuse,CHIP <CHIP: combo>\n"
#define ANT_USAGE			"ATM0=antenna,TARGET <TARGET: wlan/bt>\n"
#define BT_POWER_USAGE		"ATM0=bt_power,ACT <ACT: on/off>\n"
#define UART_BRIDGE_USAGE	"ATM0=bridge\n"
#define GPIO_USAGE			"ATM0=gpio,ACT,DATA <ACT: r/w, DATA: 0/1>\n"
#define H5_TO_H4_USAGE		"ATM0=h5toh4\n"
#define PTA_USAGE			"ATM0=pta\n"
#define UART_USAGE			"ATM0=uart\n"
#define UART_SEND_USAGE		"ATM0=uart_send,DATA,RXLAN <DATA: send data, RXLAN: rx len>\n"
#define BT_INIT_USAGE		"ATM0=bt_init\n"
#define BT_TX_USAGE			"ATM0=bt_tx,ACT <ACT: start/stop>\n"

at_mp_ext_item_t at_mp_ext0_items[] = {
	{"efuse",		mp_ext0_efuse,				EFUSE_USAGE},
	{"antenna",		mp_ext0_switch_antenna,		ANT_USAGE},
	{"bt_power",	mp_ext0_bt_power,			BT_POWER_USAGE},
	{"bridge",		mp_ext0_uart_bridge,		UART_BRIDGE_USAGE},
	{"gpio",		mp_ext0_gpio,				GPIO_USAGE},
	{"h5toh4",		mp_ext0_h5_to_h4,			H5_TO_H4_USAGE},
	{"pta",			mp_ext0_pta,				PTA_USAGE},
	{"uart",		mp_ext0_uart,				UART_USAGE},
	{"uart_send",	mp_ext0_uart_send,			UART_SEND_USAGE},
//	{"bt_tx",		mp_ext0_bt_pkt_tx,			BT_TX_USAGE},
};

void fATM0(void *arg)
{
	int argc = 0, ret, idx, cmd_cnt;
	char *argv[MAX_ARGC] = {0};
	
	MP_EXT0_PRINTF("_AT_MP_EXT0_\n");
	cmd_cnt = sizeof(at_mp_ext0_items)/sizeof(at_mp_ext0_items[0]);
	argc = parse_param(arg, argv);
	if(argc == 1){
		_AT_PRINTK("\n");
		MP_EXT0_PRINTF("Command usage :\n");
		for(idx = 0; idx < cmd_cnt; idx++)
			_AT_PRINTK("%s", at_mp_ext0_items[idx].mp_ext_usage);
	}else{
		for(idx = 0; idx < cmd_cnt; idx++){
			if(strcmp(argv[1], at_mp_ext0_items[idx].mp_ext_cmd) == 0){
				int (*fun)(void **argv, int argc) = at_mp_ext0_items[idx].mp_ext_fun;
				ret = fun((void**)&argv[2], argc-2);
				return;
			}
		}
		MP_EXT0_PRINTF("unknown command %s.\n", argv[1]);
	}
}

#endif // #if CONFIG_ATCMD_MP_EXT0

