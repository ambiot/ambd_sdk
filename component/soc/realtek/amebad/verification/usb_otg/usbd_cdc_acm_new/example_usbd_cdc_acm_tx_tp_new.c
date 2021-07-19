#include <platform_opts.h>
#if defined(CONFIG_EXAMPLE_USBD_CDC_ACM_TP_NEW) && CONFIG_EXAMPLE_USBD_CDC_ACM_TP_NEW
#include <platform_stdlib.h>
#include "usbd.h"
#include "usbd_cdc_acm.h"
#include "osdep_service.h"

#define USE_PSRAM 0

#if USE_PSRAM
#include "usb_cdc_send_data_psram.c"
#else
#include "usb_cdc_send_data_sram.c"
#endif

static u32 start_time = 0;
static u32 file_length = 0;
u32 bulk_in_size = 0;
#define SYNC_TEST_LEN  1024*1024

extern u8 SendTable[];

static usbd_config_t cdc_acm_cfg = {
	.speed = USBD_SPEED_HIGH,
	.max_ep_num = 4U,
	.rx_fifo_size = 512U,
	.nptx_fifo_size = 256U,
	.ptx_fifo_size = 64U,
	.intr_use_ptx_fifo = TRUE,
	.dma_enable = FALSE,
	.self_powered = CDC_ACM_SELF_POWERED,
	.isr_priority = 4U,
};

static u8 cdc_acm_cb_init(void);
static u8 cdc_acm_cb_deinit(void);
static u8 cdc_acm_cb_setup(u8 cmd, u8 *pbuf, u16 length, u16 value);
static u8 cdc_acm_cb_receive(u8 *pbuf, u32 Len);

static usbd_cdc_acm_cb_t cdc_acm_cb = {
	cdc_acm_cb_init,
	cdc_acm_cb_deinit,
	cdc_acm_cb_setup,
	cdc_acm_cb_receive
};

static usbd_cdc_acm_line_coding_t cdc_acm_line_coding;

static u16 cdc_acm_ctrl_line_state;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CDC media layer
  * @param  None
  * @retval status
  */
static u8 cdc_acm_cb_init(void)
{
	usbd_cdc_acm_line_coding_t *lc = &cdc_acm_line_coding;

	lc->bitrate = 150000;
	lc->format = 0x00;
	lc->parity_type = 0x00;
	lc->data_type = 0x08;

	return HAL_OK;
}

/**
  * @brief  DeInitializes the CDC media layer
  * @param  None
  * @retval status
  */
static u8 cdc_acm_cb_deinit(void)
{
	/* Do nothing */
	return HAL_OK;
}

/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface through this function.
  * @param  Buf: RX buffer
  * @param  Len: RX data length (in bytes)
  * @retval status
  */
static u8 cdc_acm_cb_receive(u8 *buf, u32 len)
{
	//usbd_cdc_acm_transmit(buf, len);
	//return usbd_cdc_acm_receive();
	return HAL_OK;
}

/**
  * @brief  Handle the CDC class control requests
  * @param  cmd: Command code
  * @param  buf: Buffer containing command data (request parameters)
  * @param  len: Number of data to be sent (in bytes)
  * @retval status
  */
static u8 cdc_acm_cb_setup(u8 cmd, u8 *pbuf, u16 len, u16 value)
{
	usbd_cdc_acm_line_coding_t *lc = &cdc_acm_line_coding;

	switch (cmd) {
	case CDC_SEND_ENCAPSULATED_COMMAND:
		/* Do nothing */
		break;

	case CDC_GET_ENCAPSULATED_RESPONSE:
		/* Do nothing */
		break;

	case CDC_SET_COMM_FEATURE:
		/* Do nothing */
		break;

	case CDC_GET_COMM_FEATURE:
		/* Do nothing */
		break;

	case CDC_CLEAR_COMM_FEATURE:
		/* Do nothing */
		break;

	case CDC_SET_LINE_CODING:
		if (len == 7) {
			lc->bitrate = (u32)(pbuf[0] | (pbuf[1] << 8) | (pbuf[2] << 16) | (pbuf[3] << 24));
			lc->format = pbuf[4];
			lc->parity_type = pbuf[5];
			lc->data_type = pbuf[6];
		}
		break;

	case CDC_GET_LINE_CODING:
		pbuf[0] = (u8)(lc->bitrate & 0xFF);
		pbuf[1] = (u8)((lc->bitrate >> 8) & 0xFF);
		pbuf[2] = (u8)((lc->bitrate >> 16) & 0xFF);
		pbuf[3] = (u8)((lc->bitrate >> 24) & 0xFF);
		pbuf[4] = lc->format;
		pbuf[5] = lc->parity_type;
		pbuf[6] = lc->data_type;
		break;

	case CDC_SET_CONTROL_LINE_STATE:
		/*
		wValue:	wValue, Control Signal Bitmap
				D2-15:	Reserved, 0
				D1:	RTS, 0 - Deactivate, 1 - Activate
				D0:	DTR, 0 - Not Present, 1 - Present
		*/
		if ((value & 0x02) && (cdc_acm_ctrl_line_state != value)) {
			cdc_acm_ctrl_line_state = value;
			printf("\nUSBD VCOM port activated\n");
		}
		break;

	case CDC_SEND_BREAK:
		/* Do nothing */
		break;

	default:
		break;
	}

	return HAL_OK;
}

static void acm_tx_thread(void *param)
{
	int ret = -1;
	u32 pass_time;
	u32 perf;
	u32 num = 0;
	u32 temp_length = 0;

	UNUSED(param);

	while (1) {
		if (file_length == 0) {
			start_time = SYSTIMER_TickGet();
		}

		while (1) {
			ret = usbd_cdc_acm_transmit((u8 *)(SendTable + temp_length), bulk_in_size);
			if (ret == HAL_OK) {
				break;
			} else {
				printf("\nFail to transmit sync data: %d\n", ret);
				rtw_mdelay_os(5);
			}
		}
		file_length += bulk_in_size;
		temp_length += bulk_in_size;

		if (temp_length >= sizeof(SendTable)) {
			temp_length = 0;
		}

		if (file_length >= SYNC_TEST_LEN) {
			pass_time = SYSTIMER_GetPassTime(start_time);
			perf = (file_length / 1024 * 100000) / pass_time;
			printf("Send Throughput %d.%d%d KB/s for %d byte @ %d ms\n", perf / 100, perf / 10 % 10, perf % 10, file_length, pass_time);
			file_length = 0;
			break;
		}

	}

	rtw_thread_exit();
}

static void example_usbd_cdc_acm_thread(void *param)
{
	int ret = 0;

	UNUSED(param);

	ret = usbd_init(&cdc_acm_cfg);
	if (ret != 0) {
		printf("\nFail to init USBD controller\n");
		goto example_usbd_cdc_acm_thread_fail;
	}

	ret = usbd_cdc_acm_init(512, bulk_in_size, &cdc_acm_cb);
	if (ret != 0) {
		printf("\nFail to init USBD CDC ACM class\n");
		usbd_deinit();
		goto example_usbd_cdc_acm_thread_fail;
	}

example_usbd_cdc_acm_thread_fail:
	rtw_thread_exit();
}

/*
usb 0 512			 // Initialize usbd cdc acm and set bulk in size to 512.
usb 1			 // Start tx thread
*/
u32 usb_cdc_test_cmd(u16 argc, u8  *argv[])
{
	int ret;
	int i;
	u32 mode;
	struct task_struct acm_task;
	struct task_struct tx_task;

	if (argc < 1) {
		DBG_8195A("Wrong argument number!\r\n");
		return _FALSE;
	}

	mode = _strtoul((const char *)(argv[0]), (char **)NULL, 10);
	if (argc > 1) {
		bulk_in_size = _strtoul((const char *)(argv[1]), (char **)NULL, 10);
		printf("bulk_in_size: %d\n", bulk_in_size);
	}

	if (mode == 0) {
		printf("USB CDC ACM Init\n");

		ret = rtw_create_task(&acm_task, "example_usbd_cdc_acm_thread", 1024, tskIDLE_PRIORITY + 5, example_usbd_cdc_acm_thread, NULL);
		if (ret != pdPASS) {
			printf("\nFail to create USBD CDC ACM thread\n");
		}
	} else if (mode == 1) {
		printf("Start tx\n");

		ret = rtw_create_task(&tx_task, "acm_tx_thread", 1024, tskIDLE_PRIORITY + 3, acm_tx_thread, NULL);
		if (ret != pdPASS) {
			printf("\nFail to create USBD CDC ACM tx thread: %d\n", ret);
			usbd_cdc_acm_deinit();
			usbd_deinit();
		}
	} else {
		DBG_8195A("Wrong argument\r\n");
	}

	return _TRUE;
}

CMD_TABLE_DATA_SECTION
const COMMAND_TABLE   usb_cdc_test_cmd_table[] = {
	{
		(const u8 *)"USB", 4, usb_cdc_test_cmd, (const u8 *)"\tUSB : \n"
		"\t\t USB CDC ACM Test \n"
	},
};

#endif

