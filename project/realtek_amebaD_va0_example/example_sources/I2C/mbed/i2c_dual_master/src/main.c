/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "PinNames.h"
#include "basic_types.h"
#include "diag.h"

#include "i2c_api.h"
#include "pinmap.h"
//#include "ex_api.h"

/*I2C pin location:
* I2C0:
*	  - S0:  PA_25(SCL)/PA_26(SDA).
*	  - S1:  PB_5(SCL)/PB_6(SDA).
*/

//I2C1_SEL S0
#define MBED_I2C_MTR_SDA    PA_26
#define MBED_I2C_MTR_SCL    PA_25

//I2C0_SEL S0
#define MBED_I2C_SLV_SDA    PA_26
#define MBED_I2C_SLV_SCL    PA_25

#define MBED_I2C_SLAVE_ADDR0    0x23
#define MBED_I2C_BUS_CLK        100000  //hz

#define I2C_DATA_LENGTH         127
uint8_t	i2cdatasrc[I2C_DATA_LENGTH];
uint8_t	i2cdatadst[I2C_DATA_LENGTH];
uint8_t	i2cdatardsrc[I2C_DATA_LENGTH];
uint8_t	i2cdatarddst[I2C_DATA_LENGTH];

#define I2C_MASTER_DEVICE

// RESTART verification
#define I2C_RESTART_DEMO	

i2c_t   i2cmaster;
i2c_t   i2cslave;

void i2c_slave_rx_check(void)
{

	int i2clocalcnt;
	int result = 0;
	
	DBG_8195A("check slave received data>>>\n");
	for (i2clocalcnt = 0; i2clocalcnt < I2C_DATA_LENGTH; i2clocalcnt+=2) {
		//DBG_8195A("i2c data: %02x \t %02x\n",i2cdatadst[i2clocalcnt],i2cdatadst[i2clocalcnt+1]);
	}
	//HalDelayUs(5000);

	// verify result
	result = 1;
#if !defined(I2C_RESTART_DEMO)
	for (i2clocalcnt = 0; i2clocalcnt < I2C_DATA_LENGTH; i2clocalcnt++) {
		if (i2cdatasrc[i2clocalcnt] != i2cdatadst[i2clocalcnt]) {
			result = 0;
			break;
		}
	}
#else
	if (i2cdatasrc[0] == i2cdatadst[0]) {
		if (i2cdatasrc[0] != i2cdatadst[0]) {
			result = 0;
		}
	} else if (i2cdatasrc[1] == i2cdatadst[0]) {
		for (i2clocalcnt = 1; i2clocalcnt < I2C_DATA_LENGTH; i2clocalcnt++) {
			if (i2cdatasrc[i2clocalcnt] != i2cdatadst[i2clocalcnt -1]) {
				DBG_8195A("idx:%d, src:%x, dst:%x\n", i2clocalcnt, i2cdatasrc[i2clocalcnt], i2cdatadst[i2clocalcnt]);
				for (i2clocalcnt = 0; i2clocalcnt < I2C_DATA_LENGTH; i2clocalcnt+=2) {
					DBG_8195A("i2c data: %02x \t %02x\n",i2cdatadst[i2clocalcnt],i2cdatadst[i2clocalcnt+1]);
				}
				result = 0;
				break;
			}
		}
	} else {
		for (i2clocalcnt = 0; i2clocalcnt < I2C_DATA_LENGTH; i2clocalcnt++) {
			if (i2cdatasrc[i2clocalcnt] != i2cdatadst[i2clocalcnt]) {
				DBG_8195A("idx:%d, src:%x, dst:%x\n", i2clocalcnt, i2cdatasrc[i2clocalcnt], i2cdatadst[i2clocalcnt]);
				result = 0;
				break;
			}
		}
	}
#endif

	DBG_8195A("\r\nSlave receive: Result is %s\r\n", (result) ? "success" : "fail");
	_memset(&i2cdatadst[0], 0x00, I2C_DATA_LENGTH);
}


void i2c_master_rx_check(void)
{

	int i2clocalcnt;
	int result = 0;

	DBG_8195A("check master received data>>>\n");
	for (i2clocalcnt = 0; i2clocalcnt < I2C_DATA_LENGTH; i2clocalcnt+=2) {
		//DBG_8195A("i2c data: %02x \t %02x\n",i2cdatarddst[i2clocalcnt],i2cdatarddst[i2clocalcnt+1]);
	}

	// verify result
	result = 1;
	for (i2clocalcnt = 0; i2clocalcnt < I2C_DATA_LENGTH; i2clocalcnt++) {
		if (i2cdatarddst[i2clocalcnt] != i2cdatardsrc[i2clocalcnt]) {
			result = 0;
			break;
		}
	}
	DBG_8195A("\r\nMaster receive: Result is %s\r\n", (result) ? "success" : "fail");

}

void main(void)
{
	int i2clocalcnt;

	// prepare for transmission
	_memset(&i2cdatasrc[0], 0x00, I2C_DATA_LENGTH);
	_memset(&i2cdatadst[0], 0x00, I2C_DATA_LENGTH);
	_memset(&i2cdatardsrc[0], 0x00, I2C_DATA_LENGTH);
	_memset(&i2cdatarddst[0], 0x00, I2C_DATA_LENGTH);

	for (i2clocalcnt=0; i2clocalcnt < I2C_DATA_LENGTH; i2clocalcnt++){
		i2cdatasrc[i2clocalcnt] = i2clocalcnt+0x2;
	}

	for (i2clocalcnt=0; i2clocalcnt < I2C_DATA_LENGTH; i2clocalcnt++){
		i2cdatardsrc[i2clocalcnt] = i2clocalcnt+1;
	}

#ifdef I2C_MASTER_DEVICE
	DBG_8195A("Slave addr=%x\n",MBED_I2C_SLAVE_ADDR0);
	_memset(&i2cmaster, 0x00, sizeof(i2c_t));
	i2c_init(&i2cmaster, MBED_I2C_MTR_SDA ,MBED_I2C_MTR_SCL);  
	i2c_frequency(&i2cmaster,MBED_I2C_BUS_CLK);
#ifdef I2C_RESTART_DEMO
	i2c_restart_enable(&i2cmaster);
#endif

	// Master write - Slave read
	DBG_8195A("\r\nMaster write>>>\n");
#ifdef I2C_RESTART_DEMO
	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatasrc[0], 1, 0);
	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatasrc[1], (I2C_DATA_LENGTH-1), 1);
#else
	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatasrc[0], I2C_DATA_LENGTH, 1);
#endif
	
	// Master read - Slave write
	DBG_8195A("Master read>>>\n");
#ifdef I2C_RESTART_DEMO
	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatasrc[0], 1, 0);
#endif
	i2c_read(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatarddst[0], I2C_DATA_LENGTH, 1);

	i2c_master_rx_check();

#else //I2C_SLAVE_DEVICE
	DBG_8195A("Slave addr=%x\n",MBED_I2C_SLAVE_ADDR0);
	_memset(&i2cslave, 0x00, sizeof(i2c_t));
	i2c_init(&i2cslave, MBED_I2C_SLV_SDA ,MBED_I2C_SLV_SCL);
	i2c_frequency(&i2cslave,MBED_I2C_BUS_CLK);
	i2c_slave_address(&i2cslave, 0, MBED_I2C_SLAVE_ADDR0, 0xFF);
	i2c_slave_mode(&i2cslave, 1);

	// Master write - Slave read
	DBG_8195A("\r\nSlave read>>>\n");
	i2c_slave_read(&i2cslave, &i2cdatadst[0], I2C_DATA_LENGTH);

	// Master read - Slave write
	DBG_8195A("Slave write>>>\n");
#ifdef I2C_RESTART_DEMO
	i2c_slave_read(&i2cslave, &i2cdatadst[0], 1);
#endif

	i2c_slave_rx_check();

	i2c_slave_set_for_rd_req(&i2cslave, 1);
	i2c_slave_write(&i2cslave, &i2cdatardsrc[0], I2C_DATA_LENGTH);
#endif // #ifdef I2C_SLAVE_DEVICE

	while(1){;}
}

