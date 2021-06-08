/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2015 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */


#include "diag.h"
#include "main.h"
#include "rtl8721d.h"

#define DMA_CPY_LEN     256
#define DMA_SRC_OFFSET  0
#define DMA_DST_OFFSET  0
	
uint8_t SRAM_NOCACHE_DATA_SECTION TestBuf1[512];
uint8_t SRAM_NOCACHE_DATA_SECTION TestBuf2[512];

volatile uint8_t dma_done;

struct gdma_s {
	u8 index;
	u8 ch_num;
	IRQ_FUN user_cb;
	u32 user_cb_data;
};
typedef struct gdma_s gdma_t;
gdma_t gdma;

void dma_done_handler( ) {
    DBG_8195A("DMA Copy Done!!\r\n");
    dma_done = 1;
}

static void Dma_memcpy_int(void *pData)
{
	gdma_t *dma_obj = (gdma_t *)pData;

	/* Clean Auto Reload Bit */
	GDMA_ChCleanAutoReload(dma_obj->index, dma_obj->ch_num, CLEAN_RELOAD_DST);

	/* Clear Pending ISR */
	GDMA_ClearINT(dma_obj->index, dma_obj->ch_num);

	GDMA_Cmd(dma_obj->index, dma_obj->ch_num, DISABLE);

	if (dma_obj->user_cb != NULL) {
		dma_obj->user_cb((VOID*)dma_obj->user_cb_data);
	}
}

int main(void) 
{
	int i;
	int err;
	GDMA_InitTypeDef GDMA_InitStruct;	
	u8 ch_num;
	gdma.index = 0;

	ch_num = GDMA_ChnlAlloc(gdma.index, (IRQ_FUN) Dma_memcpy_int, (u32)(&gdma), 10);

	if (0xFF == ch_num) {
		DBG_8195A("%s: Cannot allocate a GDMA Channel\n", __FUNCTION__);
		return;
	}
	gdma.user_cb = (IRQ_FUN)dma_done_handler;
	gdma.user_cb_data = (u32)(&gdma);
	gdma.ch_num = ch_num;
	
	for (i=0;i< 512;i++) {
		TestBuf1[i] = i;
	}
	_memset(TestBuf2, 0xff, 512);

	dma_done = 0;
	
	_memset((void *)&GDMA_InitStruct, 0, sizeof(GDMA_InitTypeDef));

	GDMA_InitStruct.GDMA_ChNum = gdma.ch_num;
	GDMA_InitStruct.GDMA_Index = gdma.index;
	GDMA_InitStruct.GDMA_IsrType = (TransferType|ErrType);

	DBG_8195A( "%s: ==> Src=0x%x Dst=0x%x Len=%d\r\n", __FUNCTION__, TestBuf1+DMA_SRC_OFFSET, TestBuf2+DMA_DST_OFFSET, DMA_CPY_LEN);
	
	if ((((u32)(TestBuf1+DMA_SRC_OFFSET)& 0x03)==0) &&	(((u32)(TestBuf2+DMA_DST_OFFSET) & 0x03)==0) && ((DMA_CPY_LEN & 0x03)== 0)) {
		/* 4-bytes aligned, move 4 bytes each transfer */
		GDMA_InitStruct.GDMA_SrcMsize   = MsizeEight;
		GDMA_InitStruct.GDMA_SrcDataWidth = TrWidthFourBytes;
		GDMA_InitStruct.GDMA_DstMsize = MsizeEight;
		GDMA_InitStruct.GDMA_DstDataWidth = TrWidthFourBytes;
		GDMA_InitStruct.GDMA_BlockSize =DMA_CPY_LEN >> 2;
	} else {
		GDMA_InitStruct.GDMA_SrcMsize   = MsizeEight;
		GDMA_InitStruct.GDMA_SrcDataWidth = TrWidthOneByte;
		GDMA_InitStruct.GDMA_DstMsize = MsizeEight;
		GDMA_InitStruct.GDMA_DstDataWidth = TrWidthOneByte;
		GDMA_InitStruct.GDMA_BlockSize = DMA_CPY_LEN;
	}

	GDMA_InitStruct.GDMA_SrcAddr = (u32)(TestBuf1+DMA_SRC_OFFSET);
	GDMA_InitStruct.GDMA_DstAddr = (u32)(TestBuf2+DMA_DST_OFFSET);     
	
	DBG_8195A("GDMA_InitStruct->GDMA_BlockSize = %d\n", GDMA_InitStruct.GDMA_BlockSize);

	GDMA_Init(gdma.index, gdma.ch_num, &GDMA_InitStruct);
	GDMA_Cmd(gdma.index, gdma.ch_num, ENABLE);
	
	while (dma_done == 0);

	err = 0;
	for (i=0;i<DMA_CPY_LEN;i++) {
		if (TestBuf2[i+DMA_DST_OFFSET] != TestBuf1[i+DMA_SRC_OFFSET]) {
			DiagPrintf("DMA Copy Memory Compare Err, %d %x %x\r\n", i, TestBuf1[i+DMA_SRC_OFFSET], TestBuf2[i+DMA_DST_OFFSET]);
			err = 1;
		}
	}

	if (!err) {
		DiagPrintf("DMA Copy Memory Compare OK!! %x\r\n", TestBuf2[DMA_DST_OFFSET+DMA_CPY_LEN]);
	}
	GDMA_ChnlFree(gdma.index, gdma.ch_num);

	while(1);
	return 0;
}