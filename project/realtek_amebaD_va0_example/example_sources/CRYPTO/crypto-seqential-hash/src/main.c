/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */
#include "hal_crypto.h"

static const char md5_digest[] = { 0xD1, 0x74, 0xAB, 0x98, 0xD2, 0x77, 0xD9, 0xF5,
	   0xA5, 0x61, 0x1C, 0x2C, 0x9F, 0x41, 0x9D, 0x9F };

static unsigned char md5_test_buf[3][128] =
{
	{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
	{ "abcdefghijklmnopqrstuvwxyz" },
	{ "0123456789" }
};

u8 digest[64];

/*
 *
 *
 *  This test_md5_seq_hash function is used to test hardware md5 functoinality
 */
void test_md5_seq_hash(void)
{
	int ret;

	DiagPrintf("MD5 test\r\n"); 

	ret = rtl_crypto_md5_init();
	if (ret != SUCCESS) {
		DBG_8195A("init failed!, ret=%d\n", ret);
	}

	ret = rtl_crypto_md5_update(md5_test_buf[0], strlen(md5_test_buf[0]));
	if (ret != SUCCESS) {
		DBG_8195A("failed-1!, ret=%d\n", ret);
	}
	
	ret = rtl_crypto_md5_update(md5_test_buf[1], strlen(md5_test_buf[1]));
	if (ret != SUCCESS) {
		DiagPrintf("failed-2!, ret=%d\n", ret);
	}
	
	ret = rtl_crypto_md5_update(md5_test_buf[2], strlen(md5_test_buf[2]));
	if (ret != SUCCESS) {
		DiagPrintf("failed-3!, ret=%d\n", ret);
	}
		
	ret = rtl_crypto_md5_final((unsigned char *)&digest);
	if (ret != SUCCESS) {
		DiagPrintf(" final failed!, ret=%d\n", ret);
	}
	
	if ( _memcmp(digest, md5_digest, 16) == 0 ) {
		DiagPrintf("seq hash MD5 test result is correct, ret=%d\r\n", ret);
	} else {
		DiagPrintf("seq hash MD5 test result is wrong!!, ret=%d\r\n", ret);
	}
}

void main(void)
{
	DiagPrintf("CRYPTO Sequential Hash API Demo...\r\n");

	if ( rtl_cryptoEngine_init() != 0 ) {
		DiagPrintf("crypto engine init failed\r\n");            
	} else {
		DiagPrintf("init success\n");
	}

	test_md5_seq_hash();   

	while(1);
}

