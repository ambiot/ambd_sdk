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
//#include "device.h"
//#include "i2c_api.h"
#include "pinmap.h"
//#include "ex_api.h"

struct i2c_m {
	uint32_t i2c_idx;
	I2C_TypeDef * I2Cx;
};
typedef struct i2c_m i2c_t;

u32 restart_enable = 0;
uint16_t i2c_target_addr[2];
u32 master_addr_retry = 1;

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
I2C_InitTypeDef I2CInitData[2];

//#define I2C_MASTER_DEVICE

// RESTART verification
//#define I2C_RESTART_DEMO	

i2c_t   i2cmaster;
i2c_t   i2cslave;

void i2c_Send_restart(I2C_TypeDef *I2Cx, u8* pBuf, u8 len, u8 restart);
/**
  * @brief  Initializes the I2C device, include clock/function/I2C registers.
  * @param  obj: i2c object define in application software.
  * @param  sda: SDA PinName according to pinmux spec.
  * @param  scl: SCL PinName according to pinmux spec.
  * @retval none  
  */
void i2c_Init(i2c_t *obj, PinName sda, PinName scl) 
{
	uint32_t i2c_idx;
	if ((sda == _PA_26) || (sda == _PB_6)) {
		i2c_idx = 0;
	}  else {
		assert_param(0);
	}

	//ConfigDebugErr &= (~(_DBG_I2C_|_DBG_GDMA_));
	//ConfigDebugInfo&= (~(_DBG_I2C_|_DBG_GDMA_));

	DBG_8195A("i2c_idx:%x\n",i2c_idx);

	obj->i2c_idx = i2c_idx;
	obj->I2Cx = I2C_DEV_TABLE[i2c_idx].I2Cx;
	
	/* Set I2C Device Number */
	I2CInitData[obj->i2c_idx].I2CIdx = i2c_idx;

	/* Load I2C default value */
	I2C_StructInit(&I2CInitData[obj->i2c_idx]);

	/* Assign I2C Pin Mux */
	I2CInitData[obj->i2c_idx].I2CMaster     = I2C_MASTER_MODE;
	I2CInitData[obj->i2c_idx].I2CSpdMod     = I2C_SS_MODE;
	I2CInitData[obj->i2c_idx].I2CClk        = 100;
	I2CInitData[obj->i2c_idx].I2CAckAddr    = 0;    

	
	/* I2C Pin Mux Initialization */
	Pinmux_Config(sda, PINMUX_FUNCTION_I2C);
	Pinmux_Config(scl, PINMUX_FUNCTION_I2C);

	PAD_PullCtrl(sda, GPIO_PuPd_UP);               
	PAD_PullCtrl(scl, GPIO_PuPd_UP);
	/* I2C HAL Initialization */
	I2C_Init(obj->I2Cx, &I2CInitData[obj->i2c_idx]);

	/* I2C Enable Module */
	I2C_Cmd(obj->I2Cx, ENABLE);
}

/**
  * @brief  Set i2c frequency.
  * @param  obj: i2c object define in application software.
  * @param  hz: i2c clock(unit is Hz).
  * @retval none  
  */
void i2c_Frequency(i2c_t *obj, int hz) 
{
	uint16_t i2c_default_clk    = (uint16_t) I2CInitData[obj->i2c_idx].I2CClk;
	uint16_t i2c_user_clk       = (uint16_t) (hz/1000);

	if (i2c_default_clk != i2c_user_clk) {
		/* Deinit I2C first */
		I2C_Cmd(obj->I2Cx, DISABLE);
		if (i2c_user_clk <= 100) {
			I2CInitData[obj->i2c_idx].I2CSpdMod = I2C_SS_MODE;
		}
		else if ((i2c_user_clk > 100) && (i2c_user_clk <= 400)) {
			I2CInitData[obj->i2c_idx].I2CSpdMod = I2C_FS_MODE;
		}
		else if (i2c_user_clk > 400) {
			I2CInitData[obj->i2c_idx].I2CSpdMod = I2C_HS_MODE;
		}
		else {
			I2CInitData[obj->i2c_idx].I2CSpdMod = I2C_SS_MODE;
		}

		/* Load the user defined I2C clock */
		I2CInitData[obj->i2c_idx].I2CClk = i2c_user_clk;

		/* Init I2C now */
		I2C_Init(obj->I2Cx, &I2CInitData[obj->i2c_idx]);
		I2C_Cmd(obj->I2Cx, ENABLE);     
	}
}

void i2c_Restart_enable(i2c_t *obj)
{
    uint32_t i2cen;

	if (obj->I2Cx->IC_ENABLE & BIT_CTRL_IC_ENABLE) {
		I2C_Cmd(obj->I2Cx, DISABLE);
		i2cen = 1;
	}

	obj->I2Cx->IC_CON |= BIT_CTRL_IC_CON_IC_RESTART_EN;

	if (i2cen) {
		I2C_Cmd(obj->I2Cx, ENABLE);
	}

	restart_enable = 1;
}

/**
  * @brief  I2C master write in poll mode.
  * @param  obj: i2c object define in application software.
  * @param  address: slave address which will be transmitted.
  * @param  data: point to the data to be sent.
  * @param  length: the length of data that to be sent.
  * @param  stop: specifies whether a STOP is issued after all the bytes are sent.
  * @retval the length of data send. 
  */
int i2c_Write(i2c_t *obj, int address, const char *data, int length, int stop) 
{
	if (i2c_target_addr[obj->i2c_idx] != address) {
		/* Deinit I2C first */
		I2C_Cmd(obj->I2Cx, DISABLE);

		/* Load the user defined I2C target slave address */
		i2c_target_addr[obj->i2c_idx] = address;
		I2CInitData[obj->i2c_idx].I2CAckAddr = address;

		/* Init I2C now */
		I2C_Init(obj->I2Cx, &I2CInitData[obj->i2c_idx]);
		I2C_Cmd(obj->I2Cx, ENABLE);   
	}

	if ((!restart_enable) |(1==stop)) {
		return (I2C_MasterWriteBrk(obj->I2Cx, (unsigned char*)data, length));
	} else {
		i2c_Send_restart(obj->I2Cx, (unsigned char*)data, length, 1);
	} 
	return length;
}

/**
  * @brief  I2C master read in poll mode.
  * @param  obj: i2c object define in application software.
  * @param  address: slave address which will be transmitted.
  * @param  data: point to the buffer to hold the received data.
  * @param  length: the length of data that to be received.
  * @param  stop: specifies whether a STOP is issued after all the bytes are received.
  * @retval the length of data received. 
  */
int i2c_Read(i2c_t *obj, int address, char *data, int length, int stop) 
{
	if (i2c_target_addr[obj->i2c_idx] != address) {
		/* Deinit I2C first */
		I2C_Cmd(obj->I2Cx, DISABLE);

		/* Load the user defined I2C target slave address */
		i2c_target_addr[obj->i2c_idx] = address;
		I2CInitData[obj->i2c_idx].I2CAckAddr = address;

		/* Init I2C now */
		I2C_Init(obj->I2Cx, &I2CInitData[obj->i2c_idx]);
		I2C_Cmd(obj->I2Cx, ENABLE);   
	}

	if (!master_addr_retry) {
		I2C_MasterRead(obj->I2Cx, (unsigned char*)data, length);
	} else {
		while (0 == I2C_MasterRead(obj->I2Cx, (unsigned char*)data, length)) {
			/* Wait for i2c enter trap state from trap_stop state*/
			DelayUs(100);
			
			/* Deinit I2C first */
			I2C_Cmd(obj->I2Cx, DISABLE);

			/* Load the user defined I2C target slave address */
			i2c_target_addr[obj->i2c_idx] = address;
			I2CInitData[obj->i2c_idx].I2CAckAddr = address;
			
			/* Init I2C now */		
			I2C_Init(obj->I2Cx, &I2CInitData[obj->i2c_idx]);
			I2C_Cmd(obj->I2Cx, ENABLE); 		
		}
	}

	return length;
}

/**
  * @brief  I2C master restart after all bytes are sent.
  * @param  I2Cx: where I2Cx can be I2C0_DEV or I2C1_DEV to select the I2C peripheral.
  * @param  pBuf: point to the data to be sent.
  * @param  len: the length of data that to be sent.
  * @param  restart: specifies whether a RESTART is issued after all the bytes are sent.
  * @retval none 
  */
void i2c_Send_restart(I2C_TypeDef *I2Cx, u8* pBuf, u8 len, u8 restart)
{
	u8 cnt = 0;
	
	/* Check the parameters */
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	/* Write in the DR register the data to be sent */
	for(cnt = 0; cnt < len; cnt++)
	{
		while((I2C_CheckFlagState(I2Cx, BIT_IC_STATUS_TFNF)) == 0);
		
		if(cnt >= len - 1)
		{
			/*generate restart signal*/
			I2Cx->IC_DATA_CMD = (*pBuf++) | (restart << 10);
		}
		else
		{
			I2Cx->IC_DATA_CMD = (*pBuf++);
		}
	}

	while((I2C_CheckFlagState(I2Cx, BIT_IC_STATUS_TFE)) == 0);
}

//#if DEVICE_I2CSLAVE
/**
  * @brief  Set i2c slave address.
  * @param  obj: i2c object define in application software.
  * @param  idx: i2c index, this parameter can be one of the following values:
  *		@arg 0 I2C0 Device
  *		@arg 1 I2C1 Device 
  * @param  address: slave address.
  * @param  mask: the mask of address  
  * @retval none  
  */
void i2c_Slave_address(i2c_t *obj, int idx, uint32_t address, uint32_t mask) 
{
	uint16_t i2c_default_addr   = (uint16_t) I2CInitData[obj->i2c_idx].I2CAckAddr;
	uint16_t i2c_user_addr      = (uint16_t) address;

	if (i2c_default_addr != i2c_user_addr) {
		/* Deinit I2C first */
		I2C_Cmd(obj->I2Cx, DISABLE);

		/* Load the user defined I2C clock */
		I2CInitData[obj->i2c_idx].I2CAckAddr    = i2c_user_addr;

		/* Init I2C now */
		I2C_Init(obj->I2Cx, &I2CInitData[obj->i2c_idx]);
		I2C_Cmd(obj->I2Cx, ENABLE);  
	}
}

void i2c_slave_rx_check(void)
{

    int     i2clocalcnt;
    int     result = 0;
	
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

	int     i2clocalcnt;
	int     result = 0;

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
    int     i2clocalcnt;

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
	i2c_Init(&i2cmaster, MBED_I2C_MTR_SDA ,MBED_I2C_MTR_SCL);  
	i2c_Frequency(&i2cmaster,MBED_I2C_BUS_CLK);
#ifdef I2C_RESTART_DEMO
	i2c_Restart_enable(&i2cmaster);
#endif

	// Master write - Slave read
	DBG_8195A("\r\nMaster write>>>\n");
#ifdef I2C_RESTART_DEMO
	i2c_Write(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatasrc[0], 1, 0);
	i2c_Write(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatasrc[1], (I2C_DATA_LENGTH-1), 1);
#else
	i2c_Write(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatasrc[0], I2C_DATA_LENGTH, 1);
#endif
	
	// Master read - Slave write
	DBG_8195A("Master read>>>\n");
#ifdef I2C_RESTART_DEMO
	i2c_Write(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatasrc[0], 1, 0);
#endif
	i2c_Read(&i2cmaster, MBED_I2C_SLAVE_ADDR0, &i2cdatarddst[0], I2C_DATA_LENGTH, 1);

	i2c_master_rx_check();

#else //I2C_SLAVE_DEVICE
	DBG_8195A("Slave addr=%x\n",MBED_I2C_SLAVE_ADDR0);
	_memset(&i2cslave, 0x00, sizeof(i2c_t));
	i2c_Init(&i2cslave, MBED_I2C_SLV_SDA ,MBED_I2C_SLV_SCL);
	i2c_Frequency(&i2cslave,MBED_I2C_BUS_CLK);
	i2c_Slave_address(&i2cslave, 0, MBED_I2C_SLAVE_ADDR0, 0xFF);
    
	I2C_Cmd(i2cslave.I2Cx, DISABLE);
	I2CInitData[i2cslave.i2c_idx].I2CMaster = I2C_SLAVE_MODE;
	I2C_Init(i2cslave.I2Cx, &I2CInitData[i2cslave.i2c_idx]);
	I2C_Cmd(i2cslave.I2Cx, ENABLE);

	// Master write - Slave read
	DBG_8195A("\r\nSlave read>>>\n");
	I2C_SlaveRead(i2cslave.I2Cx, &i2cdatadst[0], I2C_DATA_LENGTH);

	// Master read - Slave write
	DBG_8195A("Slave write>>>\n");
#ifdef I2C_RESTART_DEMO

	I2C_SlaveRead(i2cslave.I2Cx, &i2cdatadst[0], 1);
#endif

	i2c_slave_rx_check();
	
	//I2C_INTConfig(i2cslave.I2Cx, BIT_IC_INTR_MASK_M_RD_REQ, ENABLE);
	I2C_SlaveWrite(i2cslave.I2Cx, &i2cdatardsrc[0], I2C_DATA_LENGTH);
#endif // #ifdef I2C_SLAVE_DEVICE

    while(1){;}
}
