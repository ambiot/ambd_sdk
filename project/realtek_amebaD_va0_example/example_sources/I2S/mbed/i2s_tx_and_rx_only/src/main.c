/* This is RX only and TX only example */
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

//The size of this buffer should be multiples of 32 and its head address should align to 32 
//to prevent problems that may occur when CPU and DMA access this area simultaneously. 
u8 i2s_tx_buf[I2S_DMA_PAGE_SIZE*I2S_DMA_PAGE_NUM]__attribute__((aligned(32)));
u8 i2s_rx_buf[I2S_DMA_PAGE_SIZE*I2S_DMA_PAGE_NUM]__attribute__((aligned(32)));

#define RECV_PAGE_NUM 	50
u8 recv_buf[I2S_DMA_PAGE_SIZE*RECV_PAGE_NUM]__attribute__((aligned(32)));

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

u32 count = 0;
u32 tx_process = 0;
u32 rx_process = 0;

void test_tx_complete(void *data, char *pbuf)
{   
	i2s_t *obj = (i2s_t *)data;
	int *ptx_buf;

	if (rx_process) {
		
	} else if(count < RECV_PAGE_NUM){
		ptx_buf = i2s_get_tx_page(obj);
		_memcpy((void*)ptx_buf, (void*)&recv_buf[I2S_DMA_PAGE_SIZE*count], I2S_DMA_PAGE_SIZE);
		i2s_send_page(obj, (uint32_t*)ptx_buf);
		count++;
	} else {
		count = 0;
		tx_process = 0;
		rx_process = 1;
		i2s_set_direction(obj, I2S_DIR_RX);
		i2s_recv_page(obj);
	}
}

void test_rx_complete(void *data, char* pbuf)
{
    i2s_t *obj = (i2s_t *)data;
    int *ptx_buf;

    //DCache_Invalidate(((u32)(pbuf) & CACHE_LINE_ADDR_MSK), (I2S_DMA_PAGE_SIZE + CACHE_LINE_SIZE));
	DCache_Invalidate((u32)(pbuf), I2S_DMA_PAGE_SIZE);
	if (tx_process) {
		i2s_recv_page(obj);
	} else if(count < RECV_PAGE_NUM){
		rx_process = 1;
		_memcpy((void*)&recv_buf[I2S_DMA_PAGE_SIZE*count], (void*)pbuf, I2S_DMA_PAGE_SIZE);
		count++;
		i2s_recv_page(obj);
	} else {
		i2s_recv_page(obj);
		
		count = 1;
		rx_process = 0;
		tx_process = 1;
		i2s_set_direction(obj, I2S_DIR_TX);
		ptx_buf = i2s_get_tx_page(obj);
		_memcpy((void*)ptx_buf, (void*)recv_buf, I2S_DMA_PAGE_SIZE);
		i2s_send_page(obj, (uint32_t*)ptx_buf);    // loopback
	}
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
	i2s_obj.channel_num = CH_MONO;
	i2s_obj.sampling_rate = SR_16KHZ;
	i2s_obj.word_length = WL_16b;
	i2s_obj.direction = I2S_DIR_RX;    
	i2s_init(&i2s_obj, I2S_SCLK_PIN, I2S_WS_PIN, I2S_SD_TX_PIN, I2S_SD_RX_PIN, I2S_MCK_PIN);
	i2s_set_dma_buffer(&i2s_obj, (char*)i2s_tx_buf, (char*)i2s_rx_buf, \
		I2S_DMA_PAGE_NUM, I2S_DMA_PAGE_SIZE);
	i2s_tx_irq_handler(&i2s_obj, (i2s_irq_handler)test_tx_complete, (uint32_t)&i2s_obj);
	i2s_rx_irq_handler(&i2s_obj, (i2s_irq_handler)test_rx_complete, (uint32_t)&i2s_obj);
    
	i2s_recv_page(&i2s_obj);
	
	while(1);

}
