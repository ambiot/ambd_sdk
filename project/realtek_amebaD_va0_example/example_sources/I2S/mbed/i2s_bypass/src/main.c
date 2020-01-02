/* This is software bypass example */
#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"

#include "i2s_api.h"

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
#include "alc5651.c"

i2s_t i2s_obj;

#define I2S_DMA_PAGE_SIZE	768   // 2 ~ 4096
#define I2S_DMA_PAGE_NUM    4   // Vaild number is 2~4

u8 i2s_tx_buf[I2S_DMA_PAGE_SIZE*I2S_DMA_PAGE_NUM];
u8 i2s_rx_buf[I2S_DMA_PAGE_SIZE*I2S_DMA_PAGE_NUM];

/* QFN48 Pinmux
// S0
#define I2S_SCLK_PIN		PB_20
#define I2S_WS_PIN		PB_21
#define I2S_SD_TX_PIN		PB_19
#define I2S_SD_RX_PIN	PB_22
#define I2S_MCK_PIN		PA_12
// S1
#define I2S_SCLK_PIN		PB_20
#define I2S_WS_PIN		PB_21
#define I2S_SD_TX_PIN		PB_19
#define I2S_SD_RX_PIN	PB_22
#define I2S_MCK_PIN		PB_23
*/

/* QFN68 Pinmux */  
// S0
#define I2S_SCLK_PIN			PA_2
#define I2S_WS_PIN			PA_4
#define I2S_SD_TX_PIN			PB_26
#define I2S_SD_RX_PIN		PA_0
#define I2S_MCK_PIN			PA_12
/*
// S1
#define I2S_SCLK_PIN			PB_29
#define I2S_WS_PIN			PB_31
#define I2S_SD_TX_PIN			PB_26
#define I2S_SD_RX_PIN		PB_22
#define I2S_MCK_PIN			PB_23
*/

void test_tx_complete(void *data, char *pbuf)
{    
	return ;
}

void test_rx_complete(void *data, char* pbuf)
{
    i2s_t *obj = (i2s_t *)data;
    int *ptx_buf;

    static u32 count=0;
    count++;
    if ((count&1023) == 1023)
    {
         DBG_8195A("%s \n", __func__);
    }

    DCache_Invalidate(((u32)(pbuf) & CACHE_LINE_ADDR_MSK), (I2S_DMA_PAGE_SIZE + CACHE_LINE_SIZE));

    ptx_buf = i2s_get_tx_page(obj);
    _memcpy((void*)ptx_buf, (void*)pbuf, I2S_DMA_PAGE_SIZE);
	i2s_send_page(obj, (uint32_t*)ptx_buf);    // loopback
    i2s_recv_page(obj);    // submit a new page for receive   
}

void main(void)
{
    int *ptx_buf;
    int i,j;
    
	alc5651_init();
	alc5651_init_interface2();	// connect to ALC interface 2
	
	// dump register 
	//alc5651_reg_dump();
	//alc5651_index_dump();

	// I2S init
	i2s_obj.channel_num = CH_STEREO;
	i2s_obj.sampling_rate = SR_44p1KHZ;
	i2s_obj.word_length = WL_16b;
	i2s_obj.direction = I2S_DIR_TXRX;    
	i2s_init(&i2s_obj, I2S_SCLK_PIN, I2S_WS_PIN, I2S_SD_TX_PIN, I2S_SD_RX_PIN, I2S_MCK_PIN);
    i2s_set_dma_buffer(&i2s_obj, (char*)i2s_tx_buf, (char*)i2s_rx_buf, \
        I2S_DMA_PAGE_NUM, I2S_DMA_PAGE_SIZE);
    i2s_tx_irq_handler(&i2s_obj, (i2s_irq_handler)test_tx_complete, (uint32_t)&i2s_obj);
    i2s_rx_irq_handler(&i2s_obj, (i2s_irq_handler)test_rx_complete, (uint32_t)&i2s_obj);
    
	/* rx need clock, let tx out first */
	i2s_send_page(&i2s_obj, (uint32_t*)i2s_get_tx_page(&i2s_obj));
	i2s_recv_page(&i2s_obj);
	
	while(1);

}
