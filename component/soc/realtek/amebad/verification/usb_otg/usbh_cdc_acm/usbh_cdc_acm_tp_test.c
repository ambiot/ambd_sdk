#include <platform_opts.h>
#if defined(CONFIG_EXAMPLE_USBH_CDC_ACM_VERIFY) && CONFIG_EXAMPLE_USBH_CDC_ACM_VERIFY
#include <platform/platform_stdlib.h>
#include "osdep_service.h"
#include "usb.h"
#include "usbh_cdc_acm_if.h"
#include "dwc_otg_driver.h"
#include "usbh_cdc_send_data_psram.c"
#include "usbh_cdc_send_data_sram.c"


u32 bulk_size;
u32 transfer_out_size, transfer_in_size;
u32 start, end, pass;
u8 * send_buf;
u32 is_psram;
_sema TestSema;
volatile int TotalRxLen = 0;

static void cdc_acm_init(void)
{
	printf("\nINIT\n");
}

static void cdc_acm_attach(void)
{
	printf("\nATTACH\n");
	TotalRxLen =0;
	//usbh_cdc_acm_read_open();
	rtw_up_sema(&TestSema);
}

static void cdc_acm_detach(void)
{
	printf("\nDETACH\n");
}


static void cdc_acm_receive(u8 *buf, u16 length)
{
	if(TotalRxLen == 0){
		start = SYSTIMER_TickGet();
	}
	
	TotalRxLen += length;
	
	if(TotalRxLen >= bulk_size){
		//usbh_cdc_acm_read_close();
		end = SYSTIMER_TickGet();
		if (end >= start) {
			pass = end - start;
		} else {
			pass = 0xFFFFFFFF - (start - end);
		}
		pass = pass * 1000/32768;
		printf("length: %dBytes, time: %dms, throughput: %dkB/s\n", TotalRxLen, pass, bulk_size/pass*100000/1024*10);
	}	
}


usbh_cdc_acm_usr_cb_t cdc_acm_usr_cb = {
	.init = cdc_acm_init,
	.attach = cdc_acm_attach,
	.detach = cdc_acm_detach,
	.receive = cdc_acm_receive,
};


void example_usbh_cdc_acm_thread_tx(void *param)
{
	int status;
	struct task_struct task;
	u32 len = bulk_size;

	printf("tx test\n");

	UNUSED(param);
	rtw_init_sema(&TestSema, 0);
	status = usb_init();
	if (status != USB_INIT_OK) {
		printf("\nFail to init USB host controller: %d\n", status);
		goto example_exit;
	}

	status = usbh_cdc_acm_init( transfer_in_size, transfer_out_size, &cdc_acm_usr_cb);
	if (status < 0) {
		printf("\nFail to init USB host cdc_acm driver: %d\n", status);
		usb_deinit();
	goto example_exit;
	}
	if(rtw_down_sema(&TestSema)){
		//usbh_cdc_acm_read_close();
		
		start = SYSTIMER_TickGet();
		while(len){
			if(len > is_psram){
				usbh_cdc_acm_write(send_buf, is_psram);
				len -= is_psram;
			}else{
				usbh_cdc_acm_write(send_buf, len);
				break;
			}
		}
		end = SYSTIMER_TickGet();
		
		if (end >= start) {
			pass = end - start;
		} else {
			pass = 0xFFFFFFFF - (start - end);
		}

		pass = pass * 1000/32768;
		
		printf("length: %d Bytes, time: %d ms, throughput: %d B/s\n", bulk_size, pass, bulk_size/1024*100000/pass*10);
	}
example_exit:	
	rtw_thread_exit();
}

void example_usbh_cdc_acm_thread_rx(void *param)
{
	int status;
	struct task_struct task;

	printf("rx test\n");

	u32 start, end, pass;

	UNUSED(param);
	rtw_init_sema(&TestSema, 0);
	status = usb_init();
	if (status != USB_INIT_OK) {
		printf("\nFail to init USB host controller: %d\n", status);
		goto example_exit;
	}

	status = usbh_cdc_acm_init( transfer_in_size, transfer_out_size, &cdc_acm_usr_cb);
	if (status < 0) {
		printf("\nFail to init USB host cdc_acm driver: %d\n", status);
		usb_deinit();
		goto example_exit;
	}

	
example_exit:	
	rtw_thread_exit();
}


void usbh_cdc_test_cmd(u16 argc, u8  *argv[])
{
	int status;
	struct task_struct task;

	printf("usbh_cdc_test_cmd\n");

	if (argc<1){
		DBG_8195A("Wrong argument number!\r\n");
		return _FALSE;
	}

	bulk_size = _strtoul((const u8*)(argv[1]), (u8 **)NULL, 10);//Mode

	printf("bulk_size:%d\n", bulk_size);

	transfer_in_size = _strtoul((const u8*)(argv[2]), (u8 **)NULL, 10);
	transfer_out_size = _strtoul((const u8*)(argv[3]), (u8 **)NULL, 10);

	if (_strcmp((const char*)argv[0], "tx") == 0) {
		status = rtw_create_task(&task, "example_usbh_cdc_acm_thread_tx", 512, tskIDLE_PRIORITY + 1, example_usbh_cdc_acm_thread_tx, NULL);
		if (status != pdPASS) {
			printf("\nFail to create USB host cdc_acm thread: %d\n", status);
		}
		if (_strcmp((const char*)argv[4], "psram") == 0) {
			send_buf = SendTablePsram;
			is_psram = total_len_psram;
		}else{
			send_buf = SendTable;
			is_psram = total_len;
		}
	}else if (_strcmp((const char*)argv[0], "rx") == 0) {
		status = rtw_create_task(&task, "example_usbh_cdc_acm_thread_rx", 512, tskIDLE_PRIORITY + 1, example_usbh_cdc_acm_thread_rx, NULL);
		if (status != pdPASS) {
			printf("\nFail to create USB host cdc_acm thread: %d\n", status);
		}
	}else{
		printf("\nunknown cmd\n");
	}

}

CMD_TABLE_DATA_SECTION
const COMMAND_TABLE   usbh_cdc_test_cmd_table[] = {
	{(const u8*)"USBH",4, usbh_cdc_test_cmd, (const u8*)"\tUSB : \n"
								"\t\t USB CDC ACM Test \n"},
};

#endif