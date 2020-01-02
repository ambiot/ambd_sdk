#ifndef _EXAMPLE_AUDIO_M4A_SELFPARSE_H_
#define _EXAMPLE_AUDIO_M4A_SELFPARSE_H_

#include "ameba_soc.h"

#define M4A_DECODE_SIZE		4096
#define SP_DMA_PAGE_SIZE		M4A_DECODE_SIZE/2   // 2 ~ 4096
#define SP_DMA_PAGE_NUM    		8
#define SP_ZERO_BUF_SIZE		128

typedef struct {
	GDMA_InitTypeDef       	SpTxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
	GDMA_InitTypeDef       	SpRxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef		
}SP_GDMA_STRUCT, *pSP_GDMA_STRUCT;

typedef struct {
	u8 tx_gdma_own;
	u32 tx_addr;
	u32 tx_length;
	
}TX_BLOCK, *pTX_BLOCK;

typedef struct {
	TX_BLOCK tx_block[SP_DMA_PAGE_NUM];
	TX_BLOCK tx_zero_block;
	u8 tx_gdma_cnt;
	u8 tx_usr_cnt;
	u8 tx_empty_flag;
	
}SP_TX_INFO, *pSP_TX_INFO;

typedef struct {
	u32 sample_rate;
	u32 word_len;
	u32 mono_stereo;
	u32 direction;
	
}SP_OBJ, *pSP_OBJ;

typedef struct _SAL_PSRAM_MNGT_ADPT_ {
	PCTL_InitTypeDef       	PCTL_InitStruct;                //Pointer to PCTL initial data( HAL_I2C_INIT_DAT )
	PCTL_TypeDef*            PSRAMx;					   //Pointer to PCTL Device
} SAL_PSRAM_MNGT_ADPT, *PSAL_PSRAM_MNGT_ADPT;

void example_audio_m4a_selfparse_thread(void);

#endif
