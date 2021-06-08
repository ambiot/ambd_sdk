#include <platform_opts.h>
#if defined(CONFIG_EXAMPLE_USBD_CDC_ACM_RP) && CONFIG_EXAMPLE_USBD_CDC_ACM_RP
#include <platform/platform_stdlib.h>
#include "usb.h"
#include "usbd_cdc_acm_if.h"
#include "osdep_service.h"

static u32 start_time = 0;
static u32 file_length = 0;

#define TOTAL_LEN 5242880 //1048576

u32 bulk_out_size = 0;

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

// This callback function will be invoked in USB IRQ task,
// it is not suggested to do time consuming jobs here.
static int acm_receive(void *buf, u16 length)
{
	int ret = USB_ESUCCESS;
	u32 pass_time;
	u32 perf;

	UNUSED(buf);

	if(file_length == 0) {
		start_time = SYSTIMER_TickGet();
		file_length += length;
	} else if(file_length >= TOTAL_LEN) {
		pass_time = SYSTIMER_GetPassTime(start_time);
		perf = (file_length / 1024 * 100000) / pass_time;
		printf("Recv Throughput %d.%d%d KB/s for %d byte @ %d ms\n", perf/100, perf/10 % 10, perf % 10, file_length, pass_time);
		file_length = 0;
	} else
		file_length += length;

	return ret;
}

usbd_cdc_acm_usr_cb_t cdc_acm_usr_cb = {
	.init = acm_init,
	.deinit = acm_deinit,
	.receive = acm_receive,
};

static void example_usbd_cdc_acm_thread(void *param)
{
	int ret = 0;
	
	UNUSED(param);
	
	ret = usb_init(USB_SPEED_HIGH);
	if (ret != 0) {
		printf("\nFail to init USBD controller\n");
		goto example_usbd_cdc_acm_thread_fail;
	}

	ret = usbd_cdc_acm_init(512, bulk_out_size, &cdc_acm_usr_cb);
	if (ret != 0) {
		printf("\nFail to init USBD CDC ACM class\n");
		usb_deinit();
		goto example_usbd_cdc_acm_thread_fail;
	}

	rtw_mdelay_os(100);

	printf("\nUSBD CDC ACM demo started\n");

	example_usbd_cdc_acm_thread_fail:
	rtw_thread_exit();
}

u32 usb_cdc_test_cmd(u16 argc, u8  *argv[])
{
	int ret;
	struct task_struct task;

	if (argc<1)
	{
		DBG_8195A("Wrong argument number!\r\n");
		return _FALSE;
	}

	bulk_out_size = _strtoul((const char*)(argv[0]), (char **)NULL, 10);//Mode

	ret = rtw_create_task(&task, "example_usbd_cdc_acm_thread", 1024, tskIDLE_PRIORITY + 5, example_usbd_cdc_acm_thread, NULL);
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

