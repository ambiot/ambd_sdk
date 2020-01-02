#ifndef _EXAMPLE_AUDIO_PPM_CONF_H_
#define _EXAMPLE_AUDIO_PPM_CONF_H_

#include "ameba_soc.h"

#define SP_DMA_PAGE_SIZE	512   // 2 ~ 4096
#define SP_DMA_PAGE_NUM    	4
#define SP_ZERO_BUF_SIZE		128
#define SP_FULL_BUF_SIZE		128

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
	u8 rx_gdma_own;
	u32 rx_addr;
	u32 rx_length;
	
}RX_BLOCK, *pRX_BLOCK;

typedef struct {
	RX_BLOCK rx_block[SP_DMA_PAGE_NUM];
	RX_BLOCK rx_full_block;
	u8 rx_gdma_cnt;
	u8 rx_usr_cnt;
	u8 rx_full_flag;
	
}SP_RX_INFO, *pSP_RX_INFO;

typedef struct {
	u32 sample_rate;
	u32 word_len;
	u32 mono_stereo;
	u32 direction;
	
}SP_OBJ, *pSP_OBJ;

typedef struct {
	u32 adj_en;
	u32 adj_dir;		//faster or slower, 1: faster, 0: slower
	u32 adj_once;
	float adj_step;		//step per sample
	float adj_sum;
}SP_PPM_CONF, *pSP_PPM_CONF;
#endif
