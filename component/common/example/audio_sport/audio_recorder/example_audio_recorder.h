#ifndef EXAMPLE_AUDIO_RECORDER_H
#define EXAMPLE_AUDIO_RECORDER_H

#include "ameba_soc.h"

#define SP_DMA_PAGE_SIZE	512   // 2 ~ 4096
#define SP_DMA_PAGE_NUM    	4
#define SP_FULL_BUF_SIZE		128

#define RECORD_DET_TO	10

typedef   struct  
{
	char    fccID[4];     
	unsigned   long  dwSize;       
	unsigned   short    wFormatTag;    
	unsigned   short    wChannels;    
	unsigned   long     dwSamplesPerSec;  
	unsigned   long     dwAvgBytesPerSec;  
	unsigned   short    wBlockAlign;   
	unsigned   short    uiBitsPerSample;  
}WAVE_FMT; //Format Chunk

typedef   struct 
{
	char    fccID[4];    
	unsigned   long     dwSize;     
}WAVE_DATA; //Data Chunk

typedef   struct  
{
	char     fccID[4];    
	unsigned   long      dwSize;    
	char     fccType[4];   
}WAVE_HEAD; //RIFF WAVE Chunk

typedef struct{
	WAVE_HEAD w_header;
	WAVE_FMT w_fmt;
	WAVE_DATA w_data;
}WAVE_HEADER;

#define SP_DMA_PAGE_SIZE	768   // 2 ~ 4096
#define SP_DMA_PAGE_NUM    4   // Vaild number is 2~4
#define SP_FULL_BUF_SIZE		128

typedef struct {
	GDMA_InitTypeDef       	SpTxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
	GDMA_InitTypeDef       	SpRxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef		
}SP_GDMA_STRUCT, *pSP_GDMA_STRUCT;

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

#endif
