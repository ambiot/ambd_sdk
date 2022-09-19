#include <platform_opts.h>
#if defined(CONFIG_EXAMPLE_USBD_CDC_ACM_TP) && CONFIG_EXAMPLE_USBD_CDC_ACM_TP
#include <platform/platform_stdlib.h>
#include "usb.h"
#include "usbd_cdc_acm_if.h"
#include "osdep_service.h"
#include "usb_cdc_send_data_psram.c"

static u32 start_time = 0;
static u32 file_length = 0;
u32 bulk_in_size = 0;
#define SYNC_TEST_LEN 2097152

// USBD CDC ACM applications
#define ACM_APP_ECHO_SYNC                     0     // Echo synchronously in USB IRQ thread, for ACM_BULK_XFER_SIZE <= ACM_BULK_IN_BUF_SIZE
#define ACM_APP_ECHO_ASYNC                    1     // Echo asynchronously in dedicated USB CDC ACM bulk in thread (USBD_CDC_ACM_USE_BULK_IN_THREAD == 1), for ACM_BULK_XFER_SIZE > ACM_BULK_IN_BUF_SIZE

#define CONFIG_USDB_CDC_ACM_APP              (ACM_APP_ECHO_SYNC)

#if (CONFIG_USDB_CDC_ACM_APP == ACM_APP_ECHO_ASYNC)
static _sema acm_bulk_xfer_sema;
static volatile int acm_bulk_xfer_status;
#endif

static int acm_init(void)
{
	start_time = 0;
	file_length = 0;

	return USB_ESUCCESS;
}

static int acm_deinit(void)
{
	start_time = 0;
	file_length = 0;

	return USB_ESUCCESS;
}

static int acm_receive(void *buf, u16 length)
{
	int ret = USB_ESUCCESS;
	
	UNUSED(buf);
	UNUSED(length);
	
	return ret;
}

#if (CONFIG_USDB_CDC_ACM_APP == ACM_APP_ECHO_ASYNC)
static void acm_transmit_complete(int status)
{
	rtw_up_sema(&acm_bulk_xfer_sema);
	acm_bulk_xfer_status = status;
}
#endif

usbd_cdc_acm_usr_cb_t cdc_acm_usr_cb = {
	.init = acm_init,
	.deinit = acm_deinit,
	.receive = acm_receive,
#if (CONFIG_USDB_CDC_ACM_APP == ACM_APP_ECHO_ASYNC)
	.transmit_complete = acm_transmit_complete,
#endif
};

static void acm_tx_thread(void *param)
{
	int ret = -USB_EBUSY;
	u32 pass_time;
	u32 perf;

	UNUSED(param);
	
	while (1) {
#if (CONFIG_USDB_CDC_ACM_APP == ACM_APP_ECHO_SYNC)
		if(file_length == 0)
			start_time = SYSTIMER_TickGet(); 
		while(1) {
			ret = usbd_cdc_acm_sync_transmit_data((void *)SendTable, bulk_in_size);
			if (ret == USB_ESUCCESS) {
				break;
			} else {
				printf("\nFail to transmit sync data: %d\n", ret);
				rtw_mdelay_os(5);
			}
		}
		file_length += bulk_in_size;
		if(file_length >= SYNC_TEST_LEN) {
			pass_time = SYSTIMER_GetPassTime(start_time);
			perf = (file_length / 1024 * 100000) / pass_time;
			printf("Send Throughput %d.%d%d KB/s for %d byte @ %d ms\n", perf/100, perf/10 % 10, perf % 10, file_length, pass_time);
			file_length = 0;
		}
#else // CONFIG_USDB_CDC_ACM_APP == ACM_APP_ECHO_ASYNC
		if(file_length == 0)
			start_time = SYSTIMER_TickGet();
		acm_bulk_xfer_status = USB_ESUCCESS;
		ret = usbd_cdc_acm_async_transmit_data((void *)SendTable,  total_len);
		if (ret == USB_ESUCCESS) {
			rtw_down_sema(&acm_bulk_xfer_sema);
			if (acm_bulk_xfer_status == USB_ESUCCESS) {
				file_length += total_len;
				if(file_length >= SYNC_TEST_LEN) {
					pass_time = SYSTIMER_GetPassTime(start_time);
					perf = (file_length / 1024 * 100000) / pass_time;
					printf("Send Throughput %d.%d%d KB/s for %d byte @ %d ms\n", perf/100, perf/10 % 10, perf % 10, file_length, pass_time);
					file_length = 0;
				}
			} else {
				rtw_mdelay_os(5);
				printf("\ncdc_bulk_in_handler fail: %d\n", acm_bulk_xfer_status);
			}
		} else {
			rtw_mdelay_os(1);
			//printf("\nFail to transmit async data: %d\n", ret);
		}
#endif
	}

	rtw_thread_exit();
}

static void example_usbd_cdc_acm_thread(void *param)
{
	int ret = 0;
	struct task_struct tx_task;

	UNUSED(param);

	ret = usb_init(USB_SPEED_HIGH);
	if (ret != 0) {
		printf("\nFail to init USBD controller\n");
		goto example_usbd_cdc_acm_thread_fail;
	}

	ret = usbd_cdc_acm_init(bulk_in_size, 512, &cdc_acm_usr_cb);
	if (ret != 0) {
		printf("\nFail to init USBD CDC ACM class\n");
		usb_deinit();
		goto example_usbd_cdc_acm_thread_fail;
	}

	ret = rtw_create_task(&tx_task, "acm_tx_thread", 512, tskIDLE_PRIORITY + 3, acm_tx_thread, NULL);
	if (ret != pdPASS) {
		printf("\nFail to create USBD CDC ACM tx thread: %d\n", ret);
		usbd_cdc_acm_deinit();
		usb_deinit();
		goto example_usbd_cdc_acm_thread_fail;
	}
	
	printf("\nUSBD CDC ACM demo started\n");

	example_usbd_cdc_acm_thread_fail:
	rtw_thread_exit();
}

u32 usb_cdc_test_cmd(u16 argc, u8  *argv[])
{
	int ret;
	struct task_struct acm_task;

	if (argc<1)
	{
		DBG_8195A("Wrong argument number!\r\n");
		return _FALSE;
	}

	bulk_in_size = _strtoul((const char*)(argv[0]), (char **)NULL, 10);//Mode

#if (CONFIG_USDB_CDC_ACM_APP == ACM_APP_ECHO_ASYNC)
	rtw_init_sema(&acm_bulk_xfer_sema, 0);
	acm_bulk_xfer_status = USB_ESUCCESS;
#endif

	ret = rtw_create_task(&acm_task, "example_usbd_cdc_acm_thread", 1024, tskIDLE_PRIORITY + 5, example_usbd_cdc_acm_thread, NULL);
	if (ret != pdPASS) {
		printf("\nFail to create USBD CDC ACM thread\n");
	}

	return _TRUE;
}

CMD_TABLE_DATA_SECTION
const COMMAND_TABLE   usb_cdc_test_cmd_table[] = {
	{(const u8*)"USB",4, usb_cdc_test_cmd, (const u8*)"\tUSB : \n"
								"\t\t USB CDC ACM Test \n"},
};

#endif

