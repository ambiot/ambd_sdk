#include <stdio.h>
#include "PinNames.h"
#include "basic_types.h"
#include "diag.h"

#include "i2c_api.h"
#include "pinmap.h"

#define I2C_MTR_SDA			PA_26
#define I2C_MTR_SCL			PA_25
#define I2C_BUS_CLK			100000  //hz

#define I2C_ALC5651_ADDR	(0x38/2)

#define RT5651_PRIV_INDEX	0x6a
#define RT5651_PRIV_DATA	0x6c

i2c_t   alc5651_i2c;
#define printf  DBG_8195A
#define REPEAT_READ

static void alc5651_delay(void)
{
    int i;

	i=10000;
    while (i) {
        i--;
        asm volatile ("nop\n\t");
    }
}

void alc5651_reg_write(unsigned int reg, unsigned int value)
{
	char buf[4];
	buf[0] = (char)reg;
	buf[1] = (char)(value>>8);
	buf[2] = (char)(value&0xff);

	i2c_write(&alc5651_i2c, I2C_ALC5651_ADDR, &buf[0], 3, 1);
	alc5651_delay();
}

void alc5651_reg_read(unsigned int reg, unsigned int *value)
{
	int tmp, tmp1;
	unsigned char *buf = (char*)&tmp;
	unsigned char *buf1 = (char*)&tmp1;

	buf[0] = (char)reg;
#ifndef REPEAT_READ
	i2c_write(&alc5651_i2c, I2C_ALC5651_ADDR, &buf[0], 1, 1);
	alc5651_delay();

	buf[0] = 0xaa;
	buf[1] = 0xaa;

	i2c_read(&alc5651_i2c, I2C_ALC5651_ADDR, &buf[0], 2, 1);
	alc5651_delay();

	*value= ((buf[0]&0xFF)<<8)|(buf[1]&0xFF);
#else
	i2c_repeatread(&alc5651_i2c, I2C_ALC5651_ADDR, &buf[0], 1,&buf1[0], 2);
	*value= ((buf1[0]&0xFF)<<8)|(buf1[1]&0xFF);
#endif
}

void alc5651_index_write(unsigned int reg, unsigned int value)
{
	alc5651_reg_write(RT5651_PRIV_INDEX, reg);
	alc5651_reg_write(RT5651_PRIV_DATA, value);
}

void alc5651_index_read(unsigned int reg, unsigned int *value)
{
	alc5651_reg_write(RT5651_PRIV_INDEX, reg);
	alc5651_reg_read(RT5651_PRIV_DATA, value);
}

void alc5651_reg_dump(void)
{
	int i;
	unsigned int value;

	printf("alc5651 codec reg dump\n\r");
	printf("------------------------\n\r");
	for(i=0;i<=0xff;i++){
		alc5651_reg_read(i, &value);
		printf("%02x : %04x\n\r", i, (unsigned short)value);
	}
	printf("------------------------\n\r");
}

void alc5651_index_dump(void)
{
	int i;
	unsigned int value;

	printf("alc5651 codec index dump\n\r");
	printf("------------------------\n\r");
	for(i=0;i<=0xff;i++){
		alc5651_index_read(i, &value);
		printf("%02x : %04x\n\r", i, (unsigned short)value);
	}
	printf("------------------------\n\r");
}

void alc5651_init(void)
{
    i2c_init(&alc5651_i2c, I2C_MTR_SDA, I2C_MTR_SCL);
    i2c_frequency(&alc5651_i2c, I2C_BUS_CLK);
}

void alc5651_set_word_len(int len_idx)	// interface2
{
	// 0: 16 1: 20 2: 24 3: 8
	unsigned int val;
	alc5651_reg_read(0x70,&val);
	val &= (~(0x3<<2));
	val |= (len_idx<<2);
	alc5651_reg_write(0x70,val);

}

void alc5651_init_interface1(void)
{
    alc5651_reg_write(0x00,0x0021);
    alc5651_reg_write(0x63,0xE8FE);
    alc5651_reg_write(0x61,0x5800);
    alc5651_reg_write(0x62,0x0C00);
    alc5651_reg_write(0x73,0x0000);
    alc5651_reg_write(0x2A,0x4242);
    alc5651_reg_write(0x45,0x2000);
    alc5651_reg_write(0x02,0x4848);
    alc5651_reg_write(0x8E,0x0019);
    alc5651_reg_write(0x8F,0x3100);
    alc5651_reg_write(0x91,0x0E00);
    alc5651_index_write(0x3D,0x3E00);
    alc5651_reg_write(0xFA,0x0011);
    alc5651_reg_write(0x83,0x0800);
    alc5651_reg_write(0x84,0xA000);
    alc5651_reg_write(0xFA,0x0C11);
    alc5651_reg_write(0x64,0x4010);
    alc5651_reg_write(0x65,0x0C00);
    alc5651_reg_write(0x61,0x5806);
    alc5651_reg_write(0x62,0xCC00);
    alc5651_reg_write(0x3C,0x004F);
    alc5651_reg_write(0x3E,0x004F);
    alc5651_reg_write(0x27,0x3820);
    alc5651_reg_write(0x77,0x0000);
}

//record+play(speaker+headphone/horn)
void alc5651_init_interface2(void)
{
	alc5651_reg_write(0x00,0x0001);
	alc5651_reg_write(0xFA,0x0801);
	alc5651_reg_write(0x63,0xA8F4);
	alc5651_reg_write(0x63,0xE8FC);
	alc5651_reg_write(0x61,0x9807);
	alc5651_reg_write(0x62,0x8800);
	alc5651_reg_write(0x64,0x8a00);
	alc5651_reg_write(0x65,0x0C00);
	alc5651_reg_write(0x6A,0x003D);
	alc5651_reg_write(0x6C,0x3600);
	alc5651_reg_write(0x73,0x0004);
	alc5651_reg_write(0x0D,0x9010);
	alc5651_reg_write(0x3C,0x007D);
	alc5651_reg_write(0x3E,0x007D);
	alc5651_reg_write(0x27,0x2020);
	alc5651_reg_write(0x02,0x4848);
	alc5651_reg_write(0x45,0xA000);
	alc5651_reg_write(0x2A,0x0202);
	alc5651_reg_write(0x73,0x0000);
	alc5651_reg_write(0x8E,0x0011);
	alc5651_reg_write(0x29,0x8080);
	alc5651_reg_write(0xEB,0x44C3);
    alc5651_reg_write(0x48,0x9800);
    alc5651_reg_write(0x01,0x4800);
}