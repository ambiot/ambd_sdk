/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2015 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "device.h"
#include "rtl8710b_gspi_host.h"
#include "rtl8710b_inic.h"
#include "spi_api.h"
#include "spi_ex_api.h"
#include "gpio_api.h"
#include "gpio_irq_api.h"
#include "osdep_service.h"

#define CONFIG_GSPI_SLAVE	0
#define CONFIG_USE_INTERRUPT	1
#define PACK_SIZE	2048

#if !CONFIG_GSPI_SLAVE

/*host endian configuration
	little-endian (1)
	big-endan (0)				   
*/
#define CONFIG_HOST_ENDIAN	1

// SPI0
#define SPI0_MOSI  	PA_23
#define SPI0_MISO  	PA_22
#define SPI0_SCLK  	PA_18
#define SPI0_CS    	PA_19 // This pin is redundant
#if CONFIG_USE_INTERRUPT			
#define GPIO_INT	PA_27 // gspi external interrupt
#endif
#define GPIO_CS		PA_28

#define SPI0_FREQUENCY  (62500000/6)

static spi_t spi0_master;
static gpio_irq_t gpio_int;
static gpio_t gpio_cs;

typedef enum {
	READ_REG = 0,
	WRITE_REG
}_reg_ops;


// GSPI configuration (big endian recommended)
#define GSPI_CONFIG SPI_LITTLE_ENDIAN_32

// SPI master configuration
#define SPI_BITS		8 // Ameba SPI support 8bits and 16bits mode


struct spi_more_data {
	unsigned long more_data;
	unsigned long len;
};


#define SLAVE_SELECT()		gpio_write(&gpio_cs, 0)
#define SLAVE_DESELECT()	gpio_write(&gpio_cs, 1)

#define SPI_DUMMY 0xFF

// spi interrupt semaphore
_sema pspiIrqSemaphore;
// spi bus busy
_mutex SPIbusbusy;

volatile bool txDone = FALSE;
volatile bool rxDone = FALSE;
volatile bool txbusIdle = FALSE;


#define AGG_SIZE	5000
#define MAX_DUMMY_LEN 3
#define BUFFER_LEN	GSPI_CMD_LEN+SIZE_RX_DESC+PACK_SIZE+8+MAX_DUMMY_LEN // GSPI_CMD + TX_DEC + DATA + GSPI_STATUS

unsigned char TX_DATA[PACK_SIZE];
unsigned char RX_DATA[PACK_SIZE+SIZE_RX_DESC]; // extra 100 byte for SDIO header
u32 rx_done=0;

unsigned char TX_BUFFER[BUFFER_LEN];
unsigned char RX_BUFFER[BUFFER_LEN];

#endif

#define TASK_STACK_SIZE 		2048
#define TASK_PRIORITY			(tskIDLE_PRIORITY + 1)

#if CONFIG_GSPI_SLAVE
#include "spdio_api.h"
struct spdio_t spdio_dev;

#define SPDIO_TX_BD_NUM	6      // n*2, must be rounded to 2
#define SPDIO_RX_BD_NUM	6		// 
#define SPDIO_RX_BUFSZ	PACK_SIZE+64 //n*64, must be rounded to 64,  extra 64 for TX descriptor

#define CONFIG_RX_BUFFER_REUSE	1							

/*
*	param: pdata, package 
*/
char ex_gspi_tx(u8 *pdata, u16 size, u8 type){
	static int rx_cnt = 0;

	// LOOPBACK
	printf("receive package, size = %d (cnt = %d) heap=%d\n", size, ++rx_cnt, xPortGetFreeHeapSize());

	struct spdio_buf_t *tx_buf = (struct spdio_buf_t *)rtw_malloc(sizeof(struct spdio_buf_t));
	if(!tx_buf)
		return FAIL;
	tx_buf->buf_allocated = (u32)rtw_malloc(size + SPDIO_DMA_ALIGN_4);
	if(!tx_buf->buf_allocated)
	{
		rtw_mfree((u8 *)tx_buf, sizeof(struct spdio_buf_t));
		return FAIL;
	}
	tx_buf->size_allocated = size + SPDIO_DMA_ALIGN_4;
	
	tx_buf->buf_addr = (u32)N_BYTE_ALIGMENT((u32)(tx_buf->buf_allocated), SPDIO_DMA_ALIGN_4);

	//printf("buf_addr = %x\n", tx_buf->buf_addr);
	// copy data 
	memcpy((void*)tx_buf->buf_addr, pdata, size);
	
	tx_buf->buf_size = size;
    tx_buf->type = SPDIO_RX_DATA_USER; // you can define your own data type in spdio_rx_data_t and spdio_tx_data_t

	// loopback
	spdio_tx(&spdio_dev, tx_buf);
	return SUCCESS;
}

/*spdio rx done callback (HOST->Device), manage your package and buffer*/
char ex_gspi_rx_done_cb(void *priv, void *pbuf, u8 *pdata, u16 size, u8 type){
	struct spdio_t *obj = (struct spdio_t *)priv;
	struct spdio_buf_t* rx_buf = (struct spdio_buf_t*)pbuf;

	//2 handle package received
	ex_gspi_tx(pdata, size, type);

#if !CONFIG_RX_BUFFER_REUSE
	// manage rx_buf here
	rtw_mfree((char *)rx_buf->buf_allocated, rx_buf->size_allocated);

	//2  assign new buffer to RX 
	rx_buf->buf_allocated = (u32)rtw_malloc(obj->rx_bd_bufsz + SPDIO_DMA_ALIGN_4);
	rx_buf->size_allocated = obj->rx_bd_bufsz + SPDIO_DMA_ALIGN_4;

	// this buffer must be 4 byte alignment
	rx_buf->buf_addr = (u32)N_BYTE_ALIGMENT((u32)(rx_buf->buf_allocated), SPDIO_DMA_ALIGN_4);
#endif
	return SUCCESS;
}

/*spdio tx done callback(Device->HOST), manage buffer*/
// this API will be called after package have been read by HOST
char ex_gspi_tx_done_cb(void *priv, void *pbuf){

	struct spdio_buf_t* tx_buf = (struct spdio_buf_t*)pbuf;

	rtw_mfree((u8 *)tx_buf->buf_allocated, tx_buf->size_allocated);
	rtw_mfree((u8 *)tx_buf, sizeof(struct spdio_buf_t));
	return SUCCESS;
}

#else

int spi_transfer(uint8_t* buf, uint32_t buf_len)
{
    int i = 0;
    int ret = 0;

	rtw_mutex_get(&SPIbusbusy);
	SLAVE_SELECT();

	txbusIdle = FALSE; // ensure TX done 
	rxDone = FALSE; // ensure RX done

	if(spi_master_write_read_stream(&spi0_master, buf, buf, buf_len)!=0x00){
		ret = -1;
    }else{
		ret = 0;
	while((!txbusIdle) || (!rxDone)){
		      wait_us(20);
		if (++i > 2000) {
			DBG_8195A("SPI write and read Timeout...\r\n");
		              ret = -1;
			break;
		}
	}
    }

	/* Chip Select Pull High */
	SLAVE_DESELECT();
	rtw_mutex_put(&SPIbusbusy);
    return ret;
}



static int addr_convert(u32 addr)
{
	u32 domain_id = 0 ;
	u32 temp_addr = addr&0xffff0000;

	switch (temp_addr) {
		case SPI_LOCAL_OFFSET:
			domain_id = SPI_LOCAL_DOMAIN;
			break;
		case SPI_TX_FIFO_OFFSET:
			domain_id = SPI_TXFIFO_DOMAIN;
			break;
		case SPI_RX_FIFO_OFFSET:
			domain_id = SPI_RXFIFO_DOMAIN;
			break;
		default:
			break;
	}

	return domain_id;
}

static inline u32 DWORD_endian_reverse(u32 src, _gspi_conf_t gspi_conf)
{
	u32 temp = 0;
	switch(gspi_conf){
#if CONFIG_HOST_ENDIAN	/*host little-endian*/
		case SPI_LITTLE_ENDIAN_16:
			temp = (((src&0x000000ff)<<8)|((src&0x0000ff00)>>8)|
		((src&0x00ff0000)<<8)|((src&0xff000000)>>8));
			break;
		case SPI_LITTLE_ENDIAN_32:
			temp = (((src&0x000000ff)<<24)|((src&0x0000ff00)<<8)|
		((src&0x00ff0000)>>8)|((src&0xff000000)>>24));
			break;
		case SPI_BIG_ENDIAN_16:
		case SPI_BIG_ENDIAN_32:
			temp = src;
			break;
#else				/*host big-endian*/
		case SPI_LITTLE_ENDIAN_16:
			temp = (((src&0x0000ffff)<<16)|((src&0xffff0000)>>16);
			break;
		case SPI_LITTLE_ENDIAN_32:
			temp = src;
			break;
		case SPI_BIG_ENDIAN_16:
		case SPI_BIG_ENDIAN_32:
			temp = (((src&0x000000ff)<<24)|((src&0x0000ff00)<<8)|
		((src&0x00ff0000)>>8)|((src&0xff000000)>>24));
			break;
#endif
	}
	return temp;
}

/*
*  src buffer bit reorder
*/
static void buf_endian_reverse(u8* src, u32 len, u8* dummy_bytes, _gspi_conf_t gspi_conf)
{
	u32 *buf = (u32*)src;
	
	u16 count = len/4;
	u16 remain = len%4;
	int i = 0;

	if(remain)
		count ++;
	
	for(i = 0;i < count; i++){
		buf[i] = DWORD_endian_reverse(buf[i], gspi_conf);
	}

	if(remain)
			*dummy_bytes = 4 - remain;
	}


int gspi_read_write_reg(_reg_ops  ops_type, u32 addr, char * buf, int len,_gspi_conf_t gspi_conf)
{
	int  fun = 1, domain_id = 0x0; //LOCAL
	unsigned int cmd = 0 ;
	int byte_en = 0 ;//,i = 0 ;
	int ret = 0;
	unsigned char status[GSPI_STATUS_LEN] = {0};
	unsigned int data_tmp = 0;

	u32 spi_buf[4] = {0};

	if (len!=1 && len!=2 && len != 4) {
		return -1;
	}

	domain_id = addr_convert(addr);

	addr &= 0x7fff;
	len &= 0xff;
	if (ops_type == WRITE_REG) //write register
	{
		int remainder = addr % 4;
		u32 val32 = *(u32 *)buf;
		switch(len) {
			case 1:
				byte_en = (0x1 << remainder);
				data_tmp = (val32& 0xff)<< (remainder*8);
				break;
			case 2:
				byte_en = (0x3 << remainder);
				data_tmp = (val32 & 0xffff)<< (remainder*8);
				break;
			case 4:
				byte_en = 0xf;
				data_tmp = val32 & 0xffffffff;
				break;
			default:
				byte_en = 0xf;
				data_tmp = val32 & 0xffffffff;
				break;
		}
	}
	else //read register
	{
		switch(len) {
			case 1:
				byte_en = 0x1;
				break;
			case 2:
				byte_en = 0x3;
				break;
			case 4:
				byte_en = 0xf;
				break;
			default:
				byte_en = 0xf;
				break;
		}

		if(domain_id == SPI_LOCAL_DOMAIN)
			byte_en = 0;
	}


	cmd = FILL_SPI_CMD(byte_en, addr, domain_id, fun, ops_type);
	//4 command segment bytes reorder
	cmd = DWORD_endian_reverse(cmd, gspi_conf);

	if ((ops_type == READ_REG)&& (domain_id!= SPI_RXFIFO_DOMAIN)) {
		u32 read_data = 0;

		_memset(spi_buf, 0x00, sizeof(spi_buf));

		//SPI_OUT:32bit cmd
		//SPI_IN:64bits status+ XXbits data
		spi_buf[0] = cmd;
		spi_buf[1] = 0;
		spi_buf[2] = 0;
		spi_buf[3] = 0;

		spi_transfer((u8*)spi_buf, sizeof(spi_buf));

		memcpy(status, (u8 *) &spi_buf[1], GSPI_STATUS_LEN);
		read_data = spi_buf[3];
		
		*(u32*)buf = DWORD_endian_reverse(read_data, gspi_conf);
	}
	else if (ops_type == WRITE_REG ) {
		//4 data segment bytes reorder
		data_tmp = DWORD_endian_reverse(data_tmp, gspi_conf);
		//SPI_OUT:32bits cmd+ XXbits data
		//SPI_IN:64bits status
		spi_buf[0] = cmd;
		spi_buf[1] = data_tmp;
		spi_buf[2] = 0;
		spi_buf[3] = 0;
		
		spi_transfer((u8*)spi_buf, sizeof(spi_buf));

		memcpy(status, (u8 *) &spi_buf[2], GSPI_STATUS_LEN);
	}

	// translate status
	return ret;
}
u8 gspi_read8(u32 addr, s32 *err)
{
	u32 ret = 0;
	int val32 = 0 , remainder = 0 ;
	s32 _err = 0;

	_err = gspi_read_write_reg(READ_REG, addr&0xFFFFFFFC, (char *)&ret, 4, GSPI_CONFIG);
	remainder = addr % 4;
	val32 = ret;
	val32 = (val32& (0xff<< (remainder<<3)))>>(remainder<<3);

	if (err)
		*err = _err;

	return (u8)val32;

}


u16 gspi_read16(u32 addr, s32 *err)
{
   	u32 ret = 0;
	int val32 = 0 , remainder = 0 ;
	s32 _err = 0;

	_err = gspi_read_write_reg(READ_REG, addr&0xFFFFFFFC,(char *)&ret, 4, GSPI_CONFIG);
	remainder = addr % 4;
	val32 = ret;
	val32 = (val32& (0xffff<< (remainder<<3)))>>(remainder<<3);

	if (err)
		*err = _err;

	return (u16)val32;
}


u32 gspi_read32(u32 addr, s32 *err)
{
	unsigned int ret = 0;
	s32 _err = 0;

	_err = gspi_read_write_reg(READ_REG, addr&0xFFFFFFFC,(char *)&ret,4 ,GSPI_CONFIG);
	if (err)
		*err = _err;

	return  ret;
}


s32 gspi_write8(u32 addr, u8 buf, s32 *err)
{
	int ret = 0;

	ret = gspi_read_write_reg(WRITE_REG, addr, (char *)&buf,1, GSPI_CONFIG);
	if (err)
		*err = ret;
	return ret;
}

s32 gspi_write16(u32 addr, u16 buf, s32 *err)
{
	int ret = 0;

	ret = gspi_read_write_reg(WRITE_REG,addr,(char *)&buf,2, GSPI_CONFIG);
	if (err)
		*err = ret;
	return ret;
}

s32 gspi_write32(u32 addr, u32 buf, s32 *err)
{
	int	ret = 0;

	ret = gspi_read_write_reg(WRITE_REG, addr,(char *)&buf,4, GSPI_CONFIG);
	if (err)
		*err = ret;
	return ret;
}



int gspi_read_rx_fifo(u8 *buf, u32 len, struct spi_more_data * pmore_data,_gspi_conf_t gspi_conf)
{
	int fun = 1;
	u32 cmd = 0;
	u8* spi_buf = (u8 *) (buf);
	u8* spi_data = spi_buf + GSPI_CMD_LEN;
	u8* spi_status = spi_data + len;
	int spi_buf_len = GSPI_CMD_LEN + N_BYTE_ALIGMENT(len, 4) + GSPI_STATUS_LEN;
	u8 dummy_bytes = 0;
	
	cmd = FILL_SPI_CMD(len, ((len&0xff00) >>8), SPI_RXFIFO_DOMAIN, fun, (unsigned int)0);

	//4 command segment bytes reorder
	cmd = DWORD_endian_reverse(cmd, gspi_conf);
	memcpy(spi_buf, (u8 *)&cmd, GSPI_CMD_LEN);
	//4 clean data segment 
	memset(spi_data,0x00, len);
	//4  clean status segment 
	memset(spi_status, 0x00, GSPI_STATUS_LEN);
	
	spi_transfer((u8 *) spi_buf, spi_buf_len);
	
	// data segement reorder
	buf_endian_reverse(spi_data, len, &dummy_bytes, gspi_conf);	
	// status segment reorder
	spi_status += dummy_bytes;
	buf_endian_reverse(spi_status, GSPI_STATUS_LEN, &dummy_bytes, gspi_conf);

	pmore_data->more_data = GET_STATUS_HISR(spi_status) & SPI_HIMR_RX_REQUEST_MSK;
	pmore_data->len = GET_STATUS_RXQ_REQ_LEN(spi_status);
	return 0;
}

static int gspi_write_tx_fifo(u8 *buf, u32 len, _gspi_conf_t gspi_conf)
{
	int fun = 1; //TX_HIQ_FIFO
	unsigned int cmd = 0;
	u8 *spi_buf = (u8 *) (buf);
	u8* spi_data = spi_buf + GSPI_CMD_LEN;
	u8* spi_status;// = buf + len
	u32 spi_buf_len = 0;
	
	u32 NumOfFreeSpace;
	u8 wait_num = 0;
	u8 dummy_bytes = 0;

	NumOfFreeSpace = gspi_read32(LOCAL_REG_FREE_TX_SPACE, NULL);

	while (NumOfFreeSpace * (PACK_SIZE+SIZE_TX_DESC) < len) {
		if((++wait_num) >= 4){
			DBG_8195A("%s(): wait_num is >= 4\n", __FUNCTION__);
			return -1;
		}
		rtw_udelay_os(100); //delay 100us
		NumOfFreeSpace = gspi_read32(LOCAL_REG_FREE_TX_SPACE, NULL);
	}
	cmd = FILL_SPI_CMD(len, ((len&0xff00) >>8), SPI_TXFIFO_DOMAIN, fun, (unsigned int)1);
	//4 command segment bytes reorder
	cmd = DWORD_endian_reverse(cmd, gspi_conf);
	memcpy(spi_buf, (u8 *)&cmd, GSPI_CMD_LEN);
	
	//4 data segment bytes reorder
	buf_endian_reverse(spi_data, len, &dummy_bytes, gspi_conf);

	//4 status segment 
	spi_status = spi_data + len + dummy_bytes;
	memset(spi_status, 0x00, GSPI_STATUS_LEN);

	spi_buf_len = GSPI_CMD_LEN + len + dummy_bytes + GSPI_STATUS_LEN;
	
	spi_transfer((u8 *) spi_buf, spi_buf_len);
	
	// parse status infomation
	//	GET_STATUS_HISR(status)
	//	GET_STATUS_FREE_TX(status)
	//	GET_STATUS_RXQ_REQ_LEN(status)
	//	GET_STATUS_TX_SEQ(status)

	return 0;
}

static int gspi_write_page(u8 *buf, u32 len, u8 agg_cnt){
	int res;
	u32 tot_len = SIZE_TX_DESC + len;
	PGSPI_TX_DESC ptxdesc;
	
	// clean GSPI command and tx descriptor area
	memset(TX_BUFFER, 0, GSPI_CMD_LEN+SIZE_TX_DESC);

	ptxdesc = (PGSPI_TX_DESC)(TX_BUFFER + GSPI_CMD_LEN); // reserve 4 byte for GSPI cmd
	ptxdesc->txpktsize = len;
	ptxdesc->offset = SIZE_TX_DESC;
	ptxdesc->bus_agg_num = agg_cnt;
	ptxdesc->type = GSPI_CMD_TX;
	
	memcpy(TX_BUFFER+GSPI_CMD_LEN+SIZE_TX_DESC, buf, len);

	res = gspi_write_tx_fifo(TX_BUFFER, tot_len, GSPI_CONFIG);

	return res; 
}

int gspi_configuration(_gspi_conf_t gspi_conf){

	u8 conf = gspi_conf;
	u8 retry_t = 0;
	
retry:
	/*GSPI default mode: SPI_LITTLE_ENDIAN_32*/
	gspi_read_write_reg(WRITE_REG, SPI_LOCAL_OFFSET|SPI_REG_SPI_CFG,(char *)&conf,1 ,SPI_LITTLE_ENDIAN_32);

	// read gspi config
	conf = 0xff;
	conf = gspi_read8(SPI_LOCAL_OFFSET|SPI_REG_SPI_CFG, NULL);

	if(conf != gspi_conf){
		if(++ retry_t <= 3)
			goto retry;
		DBG_8195A("%s: config fail@ 0x%x\n", __FUNCTION__, conf);
		return 1;
	}

	char *s;
	switch (conf) {
		case SPI_LITTLE_ENDIAN_16:
			s = "LITTLE_ENDIAN|WORD_LEN_16"; break;
		case SPI_LITTLE_ENDIAN_32:
			s = "LITTLE_ENDIAN|WORD_LEN_32"; break;
		case SPI_BIG_ENDIAN_16:
			s = "BIG_ENDIAN|WORD_LEN_16"; break;
		case SPI_BIG_ENDIAN_32:
			s = "BIG_ENDIAN|WORD_LEN_32"; break;
		default:
			s = "UNKNOW CONFIGURATION"; break;
	};
	DBG_8195A("%s: Current configuration:%s\n", __FUNCTION__, s);
	return 0;
}

u8 check_trx_data(u8 *src,u8*dst,u16 len){
	u16 i;
	u8 result=1;
	for(i=0;i<len;i++)
		if(*(src+i) !=*(dst+i)){
			result=0;
			break;
		}
	return result;
}

#if CONFIG_USE_INTERRUPT
void spi_interrupt_thread(){
	u32 spi_hisr;
	u32 spi_himr;
	u32 rx_cnt = 0;
	while(1){
		if (rtw_down_sema(&pspiIrqSemaphore) == _FAIL){
			DBG_8195A("%s, Take Semaphore Fail\n", __FUNCTION__);
			goto exit;
		}

		spi_himr = gspi_read32(SPI_LOCAL_OFFSET | SPI_REG_HIMR, NULL);
		spi_hisr = gspi_read32(SPI_LOCAL_OFFSET | SPI_REG_HISR, NULL);

		if (spi_hisr & spi_himr){
			if(spi_hisr & SPI_HISR_RX_REQUEST) {
				u8* rx_buf = NULL;
				u8* payload = NULL;
				u32 rx_len = 0;
				u8 rx_len_rdy = 0;
				PINIC_RX_DESC prxdesc;
				struct spi_more_data more_data = {0};

				// clean RX buffer
				memset(RX_DATA, 0, AGG_SIZE + 100);
				rx_buf = RX_DATA;
				
				do {
					//validate RX_LEN_RDY before reading RX0_REQ_LEN
	                if(rx_len==0){
						rx_len_rdy = gspi_read8(SPI_LOCAL_OFFSET|(SPI_REG_RX0_REQ_LEN + 3), NULL);
						if(rx_len_rdy & BIT7){
							rx_len = (gspi_read32(SPI_LOCAL_OFFSET | SPI_REG_RX0_REQ_LEN, NULL)) &0xffffff;
						}
	                }
					
					if (rx_len >(PACK_SIZE+SIZE_RX_DESC))
						rx_len = PACK_SIZE+SIZE_RX_DESC;
					
					if(rx_len){
						
						memset(RX_BUFFER, 0, BUFFER_LEN);
						
						gspi_read_rx_fifo(RX_BUFFER, rx_len, &more_data,GSPI_CONFIG);
						
						memcpy(rx_buf, RX_BUFFER+GSPI_CMD_LEN, rx_len);

						prxdesc = (PINIC_RX_DESC)rx_buf;
						
						DBG_8195A("Receive Data lenth = %d (cnt = %d)\n",prxdesc->pkt_len, ++rx_cnt);

						payload = rx_buf + prxdesc->offset;
						rx_buf += rx_len;
						rx_len = 0;
						rx_done=1;
					}else{
						break;
					}
				}while(1);
			}				
		}
			// query other interrupt here
	}
exit:
	vTaskDelete(NULL);
}
#endif


// external GSPI interrupt handler
void gspi_irq_handler (uint32_t id, gpio_irq_event event)
{
//DBG_8195A("gspi_irq_handler....\n");
	if(!pspiIrqSemaphore)
		return;
	rtw_up_sema_from_isr(&pspiIrqSemaphore);
}

//  SPI master interrupt callback if use interrupt mode
void spi_tx_rx_intr_callback(void *pdata, SpiIrq event){

	switch(event){
		case SpiRxIrq:
			rxDone = TRUE;
			break;
		case SpiTxIrq:
			txDone = TRUE;
			break;
		default:
			DBG_8195A("unknown interrput evnent!\n");
	} 
}

void spi_tx_bus_idle_callback(void *pdata, SpiIrq event){
	txbusIdle = TRUE;
}

void spi_init_intr(){
#if CONFIG_USE_INTERRUPT
	// init gspi external interrupt
	gpio_irq_init(&gpio_int, GPIO_INT, gspi_irq_handler, NULL);
	gpio_irq_set(&gpio_int, IRQ_FALL, 1);	// Falling Edge Trigger
	gpio_irq_enable(&gpio_int);
#endif
	// init spi master tx/rx done interrupt
	spi_irq_hook(&spi0_master, (spi_irq_handler)spi_tx_rx_intr_callback, NULL);

	// init spi master tx bus idle interrupt
	spi_bus_tx_done_irq_hook(&spi0_master, (spi_irq_handler)spi_tx_bus_idle_callback, NULL);
}
void spi_init_master(){
	// init spi master 
	spi0_master.spi_idx=MBED_SPI1;
	spi_init(&spi0_master, SPI0_MOSI, SPI0_MISO, SPI0_SCLK, SPI0_CS);
	spi_format(&spi0_master, SPI_BITS, 0, 0);
	spi_frequency(&spi0_master, SPI0_FREQUENCY);
	printf("spi master frequency %d Hz\n",SPI0_FREQUENCY);
	
	gpio_init(&gpio_cs, GPIO_CS);
	gpio_mode(&gpio_cs, PullDown);
	gpio_dir(&gpio_cs, PIN_OUTPUT);

	SLAVE_DESELECT(); // deselect slave
}
#endif

void gspi_demo(void)
{
#if CONFIG_GSPI_SLAVE
    int i;

	DBG_8195A("Init GSPI slave....\n"); 

	spdio_dev.priv = NULL;
	spdio_dev.rx_bd_num = SPDIO_RX_BD_NUM;
	spdio_dev.tx_bd_num = SPDIO_TX_BD_NUM;
	spdio_dev.rx_bd_bufsz = SPDIO_RX_BUFSZ;

	spdio_dev.rx_buf = (struct spdio_buf_t *)rtw_malloc(SPDIO_RX_BD_NUM*sizeof(struct spdio_buf_t));

	for(i=0;i<SPDIO_RX_BD_NUM;i++){
		spdio_dev.rx_buf[i].buf_allocated = (u32)rtw_malloc(SPDIO_RX_BUFSZ + SPDIO_DMA_ALIGN_4);
		if(!spdio_dev.rx_buf[i].buf_allocated){
			printf("malloc failed for spdio buffer!\n");
			return;
		}
		spdio_dev.rx_buf[i].size_allocated = SPDIO_RX_BUFSZ + SPDIO_DMA_ALIGN_4;
		// this buffer must be 4 byte alignment
		spdio_dev.rx_buf[i].buf_addr = (u32)N_BYTE_ALIGMENT((u32)(spdio_dev.rx_buf[i].buf_allocated), SPDIO_DMA_ALIGN_4);
	}

	spdio_dev.rx_done_cb = ex_gspi_rx_done_cb;
	spdio_dev.tx_done_cb = ex_gspi_tx_done_cb;

	DBG_INFO_MSG_OFF(_DBG_SDIO_);  
	DBG_WARN_MSG_OFF(_DBG_SDIO_);
	DBG_ERR_MSG_ON(_DBG_SDIO_);
	
	spdio_init(&spdio_dev);
	DBG_8195A("Init GSPI slave Done,Ready for TRx....\n"); 
#else
	DBG_8195A("Init SPI master....\n");	
	u32 spi_himr = 0;
	u32 spi_hisr = 0;
	u32 spi_ictlr = 0;
	u32 rx_agg_ctrl = 0;
	s8 res = 0;
	int test_loop = 1000;
	u16 counter=0;
	
	//1 SPI host init
	spi_init_master();
	spi_init_intr();

	rtw_init_sema(&pspiIrqSemaphore, 0);
	// used for sync SPI bus, SPI bus shold not be interrupt 
	rtw_mutex_init(&SPIbusbusy);
	
	if( xTaskCreate( (TaskFunction_t)spi_interrupt_thread, "SPI INTERRUPT", (TASK_STACK_SIZE/4), NULL, TASK_PRIORITY+2, NULL) != pdPASS) {
		DBG_8195A("Cannot create SPI INTERRUPT task\n\r");
		goto err;
	}

	//1 GSPI slave configuration
	res = gspi_configuration(GSPI_CONFIG);
	if(res){
		DBG_8195A("gspi configure error....\n");
		while(1);
	}

	// INT_CTRL-clean INT control register 
	spi_ictlr = 0;
	gspi_write32(SPI_LOCAL_OFFSET |SPI_REG_INT_CTRL, spi_ictlr, NULL);

	// HISR - clean interrupt status register
	gspi_write32(SPI_LOCAL_OFFSET |SPI_REG_HISR, 0xFFFFFFFF, NULL);
		
	// HIMR - turn all off
	gspi_write32(SPI_LOCAL_OFFSET |SPI_REG_HIMR, SPI_HIMR_DISABLED, NULL);

	// Set intterrupt mask 
	spi_himr = (u32)(SPI_HISR_RX_REQUEST|SPI_HISR_CPWM1_INT);

	// Write and enable interrupt
	gspi_write32(SPI_LOCAL_OFFSET | SPI_REG_HIMR, spi_himr, NULL);

#if 1
	// set RX AGG control register
	rx_agg_ctrl = 0;
	gspi_write32(SPI_LOCAL_OFFSET | SPI_REG_RX_AGG_CTL, rx_agg_ctrl, NULL);
#endif

	DBG_8195A("Loopback Test Start...\n"); 
	// prepare test data (0x00-0xFF, 0x00-0xFF......)
	for(int i=0;i<PACK_SIZE;i++)
		memset(TX_DATA+i, i%256, 1);
	
	do{
		res = gspi_write_page(TX_DATA, PACK_SIZE, 1);
		if(res) {
			DBG_8195A("spi_write_page: Error!\n");
			// handle error msg here
		}
		counter=0;
		while (!rx_done){
			counter++;
			rtw_mdelay_os(10);
			if(counter==100){
			DBG_8195A("Master Rx data Timeout... test aborted!\n");	
				goto err;
			}
		}
		rx_done=0;
		
		if(check_trx_data(TX_DATA,RX_DATA+SIZE_RX_DESC,PACK_SIZE))
			DBG_8195A("loop %d Test Succeed!\n",1000-test_loop);
		else {
			DBG_8195A("loop %d Test Failed!\n",1000-test_loop);
			goto err;
		}
		rtw_mdelay_os(500);
	}while(--test_loop);

#if !CONFIG_USE_INTERRUPT
	
#endif
#endif
err:
	// spi_free(&spi0_master);

	/* Kill init thread after all init tasks done */
	vTaskDelete(NULL);
}

void main(void)
{
	// create demo Task
	if( xTaskCreate( (TaskFunction_t)gspi_demo, "GSPI DEMO", (TASK_STACK_SIZE/4), NULL, TASK_PRIORITY, NULL) != pdPASS) {
		DBG_8195A("Cannot create demo task\n\r");
	}
	
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#else
	#error !!!Need FREERTOS!!!
#endif
}
