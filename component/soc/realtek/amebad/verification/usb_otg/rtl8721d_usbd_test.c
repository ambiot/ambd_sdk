#include "usb.h"
#include "usb_composite.h"
#include "rand.h"
#include "rtl8721d_usbd_test.h"

static struct usb_verify_device_t usbd_test_dev;
static u8 *GoldenData;
static u32 data_count = 0;
static _sema wait_equeue_sema; 

/*
*To Compare out and in data
*/
BOOL UsbdDataCompare(u8 *pSrc, u8 *pDst, u32 Length)
{
	int Index;
	
	for (Index = 0; Index < Length; ++Index){
		if(pSrc[Index] != pDst[Index]) {
			DBG_8195A("Src/Dst data[%d] = %x/%x\n", Index, pSrc[Index], pDst[Index]);
			if(Index != 0)
				DBG_8195A("Src/Dst data[%d] = %x/%x\n", Index-1, pSrc[Index-1], pDst[Index-1]);
			return _FALSE;
		}
	}
	return _TRUE;
}

/*
*To Generate Tx Data
*Mode:
	USBD_DATA_SEQ: fixed
	USBD_DATA_SEQ: sequential 
	USBD_DATA_RND: random
*/
void UsbdDataGenerate(u8 *pTxArray, u32 Length, u32 Mode)
{
	u32 i  = 0;
	_memset(pTxArray, 0x0, Length);

	switch (Mode)
	{
		case USBD_DATA_FIX:
			for(i = 0; i < Length; i++)
				pTxArray[i] = 0x3E;
			break;
		case USBD_DATA_SEQ:
			for(i = 0; i < Length; i++)
				pTxArray[i] = i & 0xFF;
			break;
		case USBD_DATA_RND:
			for(i = 0; i < Length; i++)
				pTxArray[i] =  Rand() & 0xFF;
			break;
		default:
			break;
	}
}

static void UsbdVerifyFreeRequest(struct usb_ep *ep, struct usb_request *req)
{
	if ((ep != NULL) && (req != NULL)) {
		if (req->buf != NULL) {
			rtw_free(req->buf);
			req->buf = NULL;
		}

		usb_ep_free_request(ep, req);
	}
}

static void usbd_verify_ctrl_out_complete(struct usb_ep *ep, struct usb_request *req)
{
	UNUSED(ep);
	u8 *mem = (u8 *)req->buf;
	
	if ((req->status == USB_ESUCCESS) && (req->actual == 2)) {
		DBG_8195A("Ep status(self-power, remote-wakeup): %d, %d\n", mem[0], mem[1]);
	}
}

void UsbdVerifyCtrl(const struct usb_control_request *ctrl)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	struct usb_ep *ep0 = vdev->ep0;
	struct usb_request  *req0 = vdev->req0;
	int status;

	if (USB_GET_TYPE(ctrl->bmRequestType) == USB_TYPE_VENDOR &&
	(ctrl->bRequest == 0) && (ctrl->wValue == 0x0100) && (ctrl->wLength == 2)) {
		req0->complete = usbd_verify_ctrl_out_complete;
		req0->length = ctrl->wLength;
		req0->zero = 0;
	}

	status = usb_ep_queue(ep0, req0, 1);
	if (status != 0 && status != -USB_ESHUTDOWN) {
		DBG_8195A("Fail to queue EP0 request: %d\n", status);
	}

	return status;
}

static void usbd_verify_bulk_in_complete(struct usb_ep *ep, struct usb_request *req)
{
	int status = req->status;
	int ret = 0;
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	
        /*check request status*/
	switch (status) {
		case USB_ESUCCESS: 			/* tx successfuly*/
			if((vdev->test_mode == 1) && vdev->long_run_flag) {
				ret = usb_ep_queue(ep, req, 1);
				if (ret) {
					DBG_8195A("Fail to enqueue bulk in request\n");
				}
			}
			break;
		/* FALLTHROUGH */
		case -USB_ECONNRESET:		/* unlink */
			DBG_8195A("ECONNRESET status = %d\n", status);
		case -USB_ESHUTDOWN:		/* disconnect etc */
			DBG_8195A("ESHUTDOWN status = %d\n", status);
			break;
		default:
			DBG_8195A("in_complete ERROR(%d)\n", status);
	}
}

static void usbd_verify_bulk_out_complete(struct usb_ep *ep, struct usb_request *req)
{
	int ret;
	int status = req->status;
	struct usb_verify_device_t *vdev = &usbd_test_dev;

	switch (status) {
		case USB_ESUCCESS:
			if(vdev->test_mode == 3) {	//loopback
				rtw_memset(vdev->bulk_in_buf, 0, vdev->bulk_buf_size);
				rtw_memcpy(vdev->bulk_in_buf, req->buf, req->actual);
				vdev->bulk_in_req->length = req->actual;
				ret = usb_ep_queue(vdev->bulk_in_ep, vdev->bulk_in_req, 1);
				if (ret < 0) {
					DBG_8195A("Fail to queue bulk in request\n");
				}
			} else {		//only receive
				if(UsbdDataCompare(GoldenData, (u8 *)req->buf, req->length)) {
					if(vdev->long_run_flag) {
						if(data_count == 5000) {
							data_count = 0;
							DBG_8195A("Success\n");
						}
						data_count ++;
					} else {
						DBG_8195A("Bulk out data success\n");
						break;
					}
				} else {
					DBG_8195A("Bulk out data fail\n");
					break;
				}
			}

			rtw_memset(vdev->bulk_out_buf, 0, vdev->bulk_buf_size);
			ret = usb_ep_queue(ep, req, 1);
			if (ret){
				DBG_8195A("Fail to queue bulk out request\n");
			}

			break;

		case -USB_ESHUTDOWN:
			DBG_8195A("Bulk out shutdown\n");
			break;

		default:
			DBG_8195A("Bulk out failed: %d\n", status);
			break;
		}
}

void UsbdVerifyBulk(void)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	struct usb_request  *req;
	int status = 0;

	if((vdev->test_mode & 0x2) == 2) {
		// BULK OUT
		if (vdev->bulk_out_ep != NULL) {
			GoldenData  = rtw_zmalloc(vdev->bulk_buf_size);
			if (!GoldenData) {
				DBG_8195A("Fail to allocate golden data buffer\n");
				goto exit;
			}
			UsbdDataGenerate(GoldenData, vdev->bulk_buf_size, USBD_DATA_SEQ);
			
			if (vdev->bulk_out_ep->driver_data != NULL) {
				usb_ep_disable(vdev->bulk_out_ep);
				vdev->bulk_out_ep->driver_data = NULL;
			}

			if (vdev->bulk_out_req != NULL) {
				UsbdVerifyFreeRequest(vdev->bulk_out_ep, vdev->bulk_out_req);
				vdev->bulk_out_req = NULL;
			}

			vdev->bulk_out_ep->desc = usb_get_descriptor(vdev->gadget, &verify_bulk_out_ep_HS, &verify_bulk_out_ep_FS);

			status = usb_ep_enable(vdev->bulk_out_ep, vdev->bulk_out_ep->desc);
			if (status < 0) {
				DBG_8195A("Fail to enable bulk out endpoint: %d\n", status);
				goto exit;
			}

			vdev->bulk_out_ep->driver_data = vdev;

			req = usb_ep_alloc_request(vdev->bulk_out_ep, 1);
			if (!req) {
				DBG_8195A("Fail to allocate bulk out request\n");
				goto exit;
			}

			vdev->bulk_out_buf = rtw_zmalloc(vdev->bulk_buf_size);
			if (vdev->bulk_out_buf == NULL) {
				DBG_8195A("Fail to allocate bulk out data buffer\n");
				goto exit;
			}

			vdev->bulk_out_req= req;
			req->buf = vdev->bulk_out_buf;
			req->dma = (dma_addr_t)req->buf;
			req->length = vdev->bulk_buf_size;
			req->complete = usbd_verify_bulk_out_complete;
			req->context = vdev;

			status = usb_ep_queue(vdev->bulk_out_ep, req, 1);
			if (status) {
				DBG_8195A("Fail to enqueue bulk out request\n");
				goto exit;
			}
		}
	}

	if((vdev->test_mode & 0x1) == 1) {
		// BULK IN
		if (vdev->bulk_in_ep != NULL) {
			if (vdev->bulk_in_ep->driver_data != NULL) {
				usb_ep_disable(vdev->bulk_in_ep);
				vdev->bulk_in_ep->driver_data = NULL;
			}

			if (vdev->bulk_in_req != NULL) {
				UsbdVerifyFreeRequest(vdev->bulk_in_ep, vdev->bulk_in_req);
				vdev->bulk_in_req = NULL;
			}

			vdev->bulk_in_ep->desc = usb_get_descriptor(vdev->gadget, &verify_bulk_in_ep_HS, &verify_bulk_in_ep_FS);

			status = usb_ep_enable(vdev->bulk_in_ep, vdev->bulk_in_ep->desc);
			if (status < 0) {
				DBG_8195A("Fail to enable bulk IN endpoint: %d\n", status);
				goto exit;
			}

			vdev->bulk_in_ep->driver_data = vdev;

			req = usb_ep_alloc_request(vdev->bulk_in_ep, 1);
			if (!req) {
				DBG_8195A("Fail to allocate bulk in request\n");
				goto exit;
			}

			vdev->bulk_in_buf = rtw_zmalloc(vdev->bulk_buf_size);
			if (vdev->bulk_in_buf == NULL) {
				DBG_8195A("Fail to allocate bulk in data buffer\n");
				goto exit;
			}

			 UsbdDataGenerate(vdev->bulk_in_buf , vdev->bulk_buf_size, USBD_DATA_SEQ);

			vdev->bulk_in_req= req;
			req->buf = vdev->bulk_in_buf;
			req->length = vdev->bulk_buf_size;
			req->dma = (dma_addr_t)req->buf;
			req->complete = usbd_verify_bulk_in_complete;
			req->context = vdev;
		}
		
		if(vdev->test_mode == 1) {
			status = usb_ep_queue(vdev->bulk_in_ep, req, 1);
			if (status) {
				DBG_8195A("Fail to enqueue bulk in request\n");
				goto exit;
			}
		}
	}
	return;

exit:
	if(vdev->bulk_out_buf)
		rtw_free(vdev->bulk_out_buf);
	if(vdev->bulk_out_ep && vdev->bulk_out_req)
		usb_ep_free_request(vdev->bulk_out_ep, vdev->bulk_out_req);
	if(vdev->bulk_in_buf)
		rtw_free(vdev->bulk_in_buf);
	if(vdev->bulk_out_ep && vdev->bulk_in_req)
		usb_ep_free_request(vdev->bulk_in_ep, vdev->bulk_in_req);
}

static void usbd_verify_iso_in_complete(struct usb_ep *ep, struct usb_iso_request *req)
{
	int status = req->status;

	UNUSED(ep);

	/*check request status*/
	switch (status) {
		case USB_ESUCCESS:             /* tx successfuly*/
			break;

		/* FALLTHROUGH */
		case -USB_ECONNRESET:   /* unlink */
			DBG_8195A("ECONNRESET\n");
			break;

		case -USB_ESHUTDOWN:    /* disconnect etc */
			DBG_8195A("ESHUTDOWN\n");
			break;

		default:
			DBG_8195A("ISO complete with error: %d\n", status);
	}
}

static void usbd_verify_iso_out_complete(struct usb_ep *ep, struct usb_iso_request *req)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	u8 *buf;
	u32 len;
	UNUSED(ep);

	if (req->proc_buf_num == 0) {
		buf = (u8 *)(req->buf0);
		len = req->data_per_frame;
	} else {
		buf = (u8 *)(req->buf1);
		len = req->data_per_frame1;
	}
	
	if(UsbdDataCompare(GoldenData, buf, len)) {
		if(vdev->long_run_flag) {
			rtw_memset(buf, 0, len);
			if(data_count == 5000) {
				data_count = 0;
				DBG_8195A("Success\n");
			}
			data_count ++;
		} else
			DBG_8195A("Iso out data success\n");
	} else {
		DBG_8195A("Iso out data fail\n");
	}
}

void UsbdVerifyIsoIn(void)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	struct usb_iso_request  *isoinreq;
	struct usb_iso_request  *isooutreq;
	int status = 0;
	int i;

	if (vdev->iso_in_ep != NULL) {
		for (i = 0; i < 2; i++) {
			vdev->iso_in_req_buf[i] = (u8 *)rtw_zmalloc(vdev->iso_buf_size);
			if (!vdev->iso_in_req_buf[i]) {
				DBG_8195A("Fail to allocate iso in request buffer\n");
				goto exit;
			}
			UsbdDataGenerate(vdev->iso_in_req_buf[i], vdev->iso_buf_size, USBD_DATA_SEQ);
		}
		
		if (vdev->iso_in_ep->driver_data != NULL) {
			iso_ep_stop(vdev->iso_in_ep, vdev->iso_in_req);	
			usb_ep_disable(vdev->iso_in_ep);
			vdev->iso_in_ep->driver_data = NULL;
		}

		if (vdev->iso_in_req != NULL) {
			free_iso_request(vdev->iso_in_ep, vdev->iso_in_req);
			vdev->iso_in_req = NULL;
		}

		vdev->iso_in_ep->desc = usb_get_descriptor(vdev->gadget, &verify_iso_in_ep_HS, &verify_iso_in_ep_FS);

		status = usb_ep_enable(vdev->iso_in_ep, vdev->iso_in_ep->desc);
		if (status < 0) {
			DBG_8195A("Fail to enable iso in endpoint: %d\n", status);
			goto exit;
		}

		vdev->iso_in_ep->driver_data = vdev;

		isoinreq = alloc_iso_request(vdev->iso_in_ep, 1, 1);
		if (!isoinreq) {
			DBG_8195A("Fail to allocate iso in request\n");
			goto exit;
		}

		isoinreq->buf0 = vdev->iso_in_req_buf[0];
		isoinreq->buf1 = vdev->iso_in_req_buf[1];
		isoinreq->dma0 = (dma_addr_t)isoinreq->buf0;
		isoinreq->dma1 = (dma_addr_t)isoinreq->buf1;
		isoinreq->buf_proc_intrvl = (1 << (vdev->iso_in_ep->desc->bInterval - 1));
		isoinreq->zero = 0;
		isoinreq->sync_frame = 0;
		isoinreq->data_pattern_frame = 0;
		isoinreq->data_per_frame = vdev->iso_buf_size;
		isoinreq->data_per_frame1 = vdev->iso_buf_size;
		isoinreq->start_frame = 0;
		isoinreq->flags |= USB_REQ_ISO_ASAP;
		isoinreq->proc_buf_num = 0;
		isoinreq->process_buffer = usbd_verify_iso_in_complete;
		isoinreq->context = vdev;

		vdev->iso_in_req = isoinreq;

		iso_ep_start(vdev->iso_in_ep, vdev->iso_in_req, 1);
	}
	
	return;
	
exit:
	for (i = 0; i < 2; i++) {
		if(vdev->iso_in_req_buf[i])
			rtw_free(vdev->iso_in_req_buf[i]);
	}
	if(vdev->iso_in_ep && vdev->iso_in_req)
		free_iso_request(vdev->iso_in_ep, vdev->iso_in_req);
}

void UsbdVerifyIsoOut(void)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	struct usb_iso_request  *isoinreq;
	struct usb_iso_request  *isooutreq;
	int status = 0;
	int i;

	if (vdev->iso_out_ep != NULL) {
		GoldenData  = rtw_zmalloc(vdev->iso_buf_size);
		if (!GoldenData) {
			DBG_8195A("Fail to allocate golden data buffer\n");
			goto exit;
		}
		UsbdDataGenerate(GoldenData, vdev->iso_buf_size, USBD_DATA_SEQ);
		
		for (i = 0; i < 2; i++) {
			vdev->iso_out_req_buf[i] = (u8 *)rtw_zmalloc(vdev->iso_buf_size);
			if (!vdev->iso_out_req_buf[i]) {
				DBG_8195A("Fail to allocate iso out request buffer\n");
				goto exit;
			}
		}
		
		if (vdev->iso_out_ep->driver_data != NULL) {
			iso_ep_stop(vdev->iso_out_ep, vdev->iso_out_req);	
			usb_ep_disable(vdev->iso_out_ep);
			vdev->iso_out_ep->driver_data = NULL;
		}

		if (vdev->iso_out_req != NULL) {
			free_iso_request(vdev->iso_out_ep, vdev->iso_out_req);
			vdev->iso_out_req = NULL;
		}

		vdev->iso_out_ep->desc = usb_get_descriptor(vdev->gadget, &verify_iso_out_ep_HS, &verify_iso_out_ep_FS);

		status = usb_ep_enable(vdev->iso_out_ep, vdev->iso_out_ep->desc);
		if (status < 0) {
			DBG_8195A("Fail to enable iso out endpoint: %d\n", status);
			goto exit;
		}

		vdev->iso_out_ep->driver_data = vdev;

		isooutreq = alloc_iso_request(vdev->iso_out_ep, 1, 1);
		if (!isooutreq) {
			DBG_8195A("Fail to allocate iso out request\n");
			goto exit;
		}

		isooutreq->buf0 = vdev->iso_out_req_buf[0];
		isooutreq->buf1 = vdev->iso_out_req_buf[1];
		isooutreq->dma0 = (dma_addr_t)isooutreq->buf0;
		isooutreq->dma1 = (dma_addr_t)isooutreq->buf1;
		isooutreq->buf_proc_intrvl = (1 << (vdev->iso_out_ep->desc->bInterval - 1));
		isooutreq->zero = 0;
		isooutreq->sync_frame = 0;
		isooutreq->data_pattern_frame = 0;
		isooutreq->data_per_frame = vdev->iso_buf_size;
		isooutreq->data_per_frame1 = vdev->iso_buf_size;
		isooutreq->start_frame = 0;
		isooutreq->flags |= USB_REQ_ISO_ASAP;
		isooutreq->proc_buf_num = 0;
		isooutreq->process_buffer = usbd_verify_iso_out_complete;
		isooutreq->context = vdev;

		vdev->iso_out_req = isooutreq;

		iso_ep_start(vdev->iso_out_ep, vdev->iso_out_req, 1);
	}
	
	return;
	
exit:
	for (i = 0; i < 2; i++) {
		if(vdev->iso_out_req_buf[i])
			rtw_free(vdev->iso_out_req_buf[i]);
	}
	if(vdev->iso_out_ep && vdev->iso_out_req)
		free_iso_request(vdev->iso_out_ep, vdev->iso_out_req);
}

static void usbd_verify_int_in_complete(struct usb_ep *ep, struct usb_request *req)
{
	int status = req->status;
	int ret = 0;
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	
        /*check request status*/
	switch (status) {
		case USB_ESUCCESS: 			/* tx successfuly*/
			if((vdev->test_mode == 1) && vdev->long_run_flag) {
				ret = usb_ep_queue(ep, req, 1);
				if (ret) {
					DBG_8195A("Fail to enqueue interrupt in request\n");
				}
			}
			break;
		/* FALLTHROUGH */
		case -USB_ECONNRESET:		/* unlink */
			DBG_8195A("ECONNRESET status = %d\n", status);
		case -USB_ESHUTDOWN:		/* disconnect etc */
			DBG_8195A("ESHUTDOWN status = %d\n", status);
			break;
		default:
			DBG_8195A("in_complete ERROR(%d)\n", status);
	}
}

static void usbd_verify_int_out_complete(struct usb_ep *ep, struct usb_request *req)
{
	int ret;
	int status = req->status;
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	UNUSED(ep);

	switch (status) {
		case USB_ESUCCESS:
			if(vdev->test_mode == 3) {	//loopback
				rtw_memcpy(vdev->int_in_buf, req->buf, req->actual);
				vdev->int_in_req->length = req->actual;
				ret = usb_ep_queue(vdev->int_in_ep, vdev->int_in_req, 1);
				if (ret < 0) {
					DBG_8195A("Fail to queue interrupt in request\n");
				}
			} else {		//only receive
				if(UsbdDataCompare(GoldenData, (u8 *)req->buf, req->length)) {
					if(vdev->long_run_flag) {
						if(data_count == 5000) {
							data_count = 0;
							DBG_8195A("Success\n");
						}
						data_count ++;
					} else {
						DBG_8195A("Success\n");
						break;
					}
				} else {
					DBG_8195A("Interrupt out data fail\n");
					break;
				}
			}

			rtw_memset(vdev->int_out_buf, 0, vdev->int_buf_size);
			ret = usb_ep_queue(ep, req, 1);
			if (ret){
				DBG_8195A("Fail to queue interrupt out request\n");
			}

			break;

		case -USB_ESHUTDOWN:
			DBG_8195A("Interrupt out shutdown\n");
			break;

		default:
			DBG_8195A("Interrupt out failed: %d\n", status);
			break;
		}
}

void UsbdVerifyInt(void)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	struct usb_request  *req;
	int status = 0;

	if((vdev->test_mode & 0x2) == 2) {
		// INT OUT
		GoldenData  = rtw_zmalloc(vdev->int_buf_size);
		if (!GoldenData) {
			DBG_8195A("Fail to allocate golden data buffer\n");
			goto exit;
		}
		UsbdDataGenerate(GoldenData, vdev->int_buf_size, USBD_DATA_SEQ);
		
		if (vdev->int_out_ep->driver_data != NULL) {
			usb_ep_disable(vdev->int_out_ep);
			vdev->int_out_ep->driver_data = NULL;
		}

		if (vdev->int_out_req != NULL) {
			UsbdVerifyFreeRequest(vdev->int_out_ep, vdev->int_out_req);
			vdev->int_out_req = NULL;
		}

		vdev->int_out_ep->desc = usb_get_descriptor(vdev->gadget, &verify_int_out_ep_HS, &verify_int_out_ep_FS);

		status = usb_ep_enable(vdev->int_out_ep, vdev->int_out_ep->desc);
		if (status < 0) {
			DBG_8195A("Fail to enable interrupt out endpoint: %d\n", status);
			goto exit;
		}

		vdev->int_out_ep->driver_data = vdev;

		req = usb_ep_alloc_request(vdev->int_out_ep, 1);
		if (!req) {
			DBG_8195A("Fail to allocate interrupt out request\n");
			goto exit;
		}

		vdev->int_out_buf = rtw_zmalloc(vdev->int_buf_size);
		if (vdev->int_out_buf == NULL) {
			DBG_8195A("Fail to allocate interrupt out data buffer\n");
			goto exit;
		}

		vdev->int_out_req= req;
		req->buf = vdev->int_out_buf;
		req->dma = (dma_addr_t)req->buf;
		req->length = vdev->int_buf_size;
		req->complete = usbd_verify_int_out_complete;
		req->context = vdev;

		status = usb_ep_queue(vdev->int_out_ep, req, 1);
		if (status) {
			DBG_8195A("Fail to enqueue interrupt out request\n");
			goto exit;
		}
	}

	if((vdev->test_mode & 0x1) == 1) {
		// Int IN
		if (vdev->int_in_ep != NULL) {
			if (vdev->int_in_ep->driver_data != NULL) {
				usb_ep_disable(vdev->int_in_ep);
				vdev->int_in_ep->driver_data = NULL;
			}

			if (vdev->int_in_req != NULL) {
				UsbdVerifyFreeRequest(vdev->int_in_ep, vdev->int_in_req);
				vdev->int_in_req = NULL;
			}

			vdev->int_in_ep->desc = usb_get_descriptor(vdev->gadget, &verify_int_in_ep_HS, &verify_int_in_ep_FS);

			status = usb_ep_enable(vdev->int_in_ep, vdev->int_in_ep->desc);
			if (status < 0) {
				DBG_8195A("Fail to enable interrupt in endpoint: %d\n", status);
				goto exit;
			}

			vdev->int_in_ep->driver_data = vdev;

			req = usb_ep_alloc_request(vdev->int_in_ep, 1);
			if (!req) {
				DBG_8195A("Fail to allocate interrupt in request\n");
				goto exit;
			}

			vdev->int_in_buf = rtw_zmalloc(vdev->int_buf_size);
			if (vdev->int_in_buf == NULL) {
				DBG_8195A("Fail to allocate interrupt in data buffer\n");
				goto exit;
			}

			 UsbdDataGenerate(vdev->int_in_buf , vdev->int_buf_size, USBD_DATA_SEQ);

			vdev->int_in_req= req;
			req->buf = vdev->int_in_buf;
			req->length = vdev->int_buf_size;
			req->dma = (dma_addr_t)req->buf;
			req->complete = usbd_verify_int_in_complete;
			req->context = vdev;
		}

		if(vdev->test_mode == 1) {
			rtw_up_sema(&wait_equeue_sema);	
		}
	}
	return;

exit:
	if(vdev->int_out_buf)
		rtw_free(vdev->int_out_buf);
	if(vdev->int_out_ep && vdev->int_out_req)
		usb_ep_free_request(vdev->int_out_ep, vdev->int_out_req);
	if(vdev->int_in_buf)
		rtw_free(vdev->int_in_buf);
	if(vdev->int_out_ep && vdev->int_in_req)
		usb_ep_free_request(vdev->int_in_ep, vdev->int_in_req);
}

static int UsbdVerifySetAlt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;

	UNUSED(f);
	UNUSED(intf);
	UNUSED(alt);

	if(vdev->alt_cb)
		vdev->alt_cb();
}

static int UsbdVerifyBind(struct usb_configuration *c, struct usb_function *f)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	struct usb_ep *ep;
	int status = -USB_ENODEV;
	int id;

	/* allocate instance-specific interface IDs, and patch descriptors */
	id = usb_interface_id(c, f); // this will return the allocated interface id
	if (id < 0) {
		status = id;
		goto verify_fun_bind_exit;
	}

	verify_intf_desc.bInterfaceNumber = id;

	ep = usb_ep_autoconfig(c->cdev->gadget, &verify_bulk_in_ep_FS);
	if (!ep) {
		goto verify_fun_bind_exit;
	}

	ep->driver_data = vdev;
	vdev->bulk_in_ep = ep;

	ep = usb_ep_autoconfig(c->cdev->gadget, &verify_bulk_out_ep_FS);
	if (!ep) {
		goto verify_fun_bind_exit;
	}

	ep->driver_data = vdev;
	vdev->bulk_out_ep = ep;

	verify_bulk_in_ep_HS.bEndpointAddress = verify_bulk_in_ep_FS.bEndpointAddress;
	verify_bulk_out_ep_HS.bEndpointAddress = verify_bulk_out_ep_FS.bEndpointAddress;
	
	DBG_8195A("BULK EP address in=0x%02x out=0x%02x\n", verify_bulk_in_ep_HS.bEndpointAddress,
	verify_bulk_out_ep_HS.bEndpointAddress);
	
#if USBD_ISO_VERIFY
	ep = usb_ep_autoconfig(c->cdev->gadget, &verify_iso_in_ep_FS);
	if (!ep) {
		goto verify_fun_bind_exit;
	}

	ep->driver_data = vdev;
	vdev->iso_in_ep = ep;

	ep = usb_ep_autoconfig(c->cdev->gadget, &verify_iso_out_ep_FS);
	if (!ep) {
		goto verify_fun_bind_exit;
	}

	ep->driver_data = vdev;
	vdev->iso_out_ep = ep;

	verify_iso_in_ep_HS.bEndpointAddress = verify_iso_in_ep_FS.bEndpointAddress;
	verify_iso_out_ep_HS.bEndpointAddress = verify_iso_out_ep_FS.bEndpointAddress;

	DBG_8195A("ISO EP address in=0x%02x out=0x%02x\n", verify_iso_in_ep_HS.bEndpointAddress,
	verify_iso_out_ep_HS.bEndpointAddress);
#else
	ep = usb_ep_autoconfig(c->cdev->gadget, &verify_int_in_ep_FS);
	if (!ep) {
		goto verify_fun_bind_exit;
	}

	ep->driver_data = vdev;
	vdev->int_in_ep = ep;

	ep = usb_ep_autoconfig(c->cdev->gadget, &verify_int_out_ep_FS);
	if (!ep) {
		goto verify_fun_bind_exit;
	}

	ep->driver_data = vdev;
	vdev->int_out_ep = ep;

	verify_int_in_ep_HS.bEndpointAddress = verify_int_in_ep_FS.bEndpointAddress;
	verify_int_out_ep_HS.bEndpointAddress = verify_int_out_ep_FS.bEndpointAddress;

	DBG_8195A("INT EP address in=0x%02x out=0x%02x\n", verify_int_in_ep_HS.bEndpointAddress,
	verify_int_out_ep_HS.bEndpointAddress);
#endif

	status = usb_assign_descriptors(f, verify_descriptors_FS, verify_descriptors_HS, NULL);
	if (status) {
		DBG_8195A("Fail to assign descriptors: %d\n", status);
		usb_free_all_descriptors(f);
		goto verify_fun_bind_exit;
	}

verify_fun_bind_exit:
	return status;
}

int UsbdVerifySetup(struct usb_function *f, const struct usb_control_request *ctrl)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;

	UNUSED(f);

	DBG_8195A("Setup request type=0x%02x request=0x%02x value=0x%04x index=0x%04x length=0x%04x\n",
	ctrl->bmRequestType, ctrl->bRequest, ctrl->wValue, ctrl->wIndex, ctrl->wLength);

	if(vdev->ctrl_cb)
		vdev->ctrl_cb(ctrl);
}

void UsbdVerifyDisable(struct usb_function *f)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	UNUSED(f);

	if (vdev->bulk_out_ep != NULL) {
		if (vdev->bulk_out_ep->driver_data != NULL) {
			usb_ep_disable(vdev->bulk_out_ep);
			vdev->bulk_out_ep->driver_data = NULL;
		}
	}

	if (vdev->bulk_in_ep != NULL) {
		if (vdev->bulk_in_ep->driver_data != NULL) {
			usb_ep_disable(vdev->bulk_in_ep);
			vdev->bulk_in_ep->driver_data = NULL;
		}
	}
	
	if (vdev->iso_out_ep != NULL) {
		if (vdev->iso_out_ep->driver_data != NULL) {
			iso_ep_stop(vdev->iso_out_ep, vdev->iso_out_req);
			usb_ep_disable(vdev->iso_out_ep);
			vdev->iso_out_ep->driver_data = NULL;
		}
	}

	if (vdev->iso_in_ep != NULL) {
		if (vdev->iso_in_ep->driver_data != NULL) {
			iso_ep_stop(vdev->iso_in_ep, vdev->iso_in_req);	
			usb_ep_disable(vdev->iso_in_ep);
			vdev->iso_in_ep->driver_data = NULL;
		}
	}

	if (vdev->int_out_ep != NULL) {
		if (vdev->int_out_ep->driver_data != NULL) {
			usb_ep_disable(vdev->int_out_ep);
			vdev->int_out_ep->driver_data = NULL;
		}
	}

	if (vdev->int_in_ep != NULL) {
		if (vdev->int_in_ep->driver_data != NULL) {
			usb_ep_disable(vdev->int_in_ep);
			vdev->int_in_ep->driver_data = NULL;
		}
	}
}

void UsbdVerifyUnbind(struct usb_configuration *c, struct usb_function *f)
{
	UNUSED(c);
	usb_free_all_descriptors(f);
}

static void UsbdVerifyFree(struct usb_function *f)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	int i;
	UNUSED(f);

	if (vdev->bulk_out_req != NULL) {
		UsbdVerifyFreeRequest(vdev->bulk_out_ep, vdev->bulk_out_req);
		vdev->bulk_out_req = NULL;
	}

	if (vdev->bulk_in_req != NULL) {
		UsbdVerifyFreeRequest(vdev->bulk_in_ep, vdev->bulk_in_req);
		vdev->bulk_in_req = NULL;
	}

	if (vdev->iso_out_req != NULL) {
		free_iso_request(vdev->iso_out_ep, vdev->iso_out_req);
		vdev->iso_out_req = NULL;
	}

	if (vdev->iso_in_req != NULL) {
		free_iso_request(vdev->iso_in_ep, vdev->iso_in_req);
		vdev->iso_in_req = NULL;
	}

	if (vdev->int_out_req != NULL) {
		UsbdVerifyFreeRequest(vdev->int_out_ep, vdev->int_out_req);
		vdev->int_out_req = NULL;
	}

	if (vdev->int_in_req != NULL) {
		UsbdVerifyFreeRequest(vdev->int_in_ep, vdev->int_in_req);
		vdev->int_in_req = NULL;
	}

	for (i = 0; i < 2; i++) {
		if(vdev->iso_in_req_buf[i]) {
			rtw_free(vdev->iso_in_req_buf[i]);
			vdev->iso_in_req_buf[i] = NULL;
		}
		
		if(vdev->iso_out_req_buf[i]) {
			rtw_free(vdev->iso_out_req_buf[i]);
			vdev->iso_out_req_buf[i] = NULL;
		}
	}

	usb_free_all_descriptors(f);   
}

static int UsbdVerifyConfig(struct usb_configuration *c)
{
	struct usb_verify_device_t *vdev = &usbd_test_dev;

	vdev->gadget = c->cdev->gadget;
	vdev->ep0 = c->cdev->gadget->ep0;
	vdev->req0 = c->cdev->req;

	return USB_ESUCCESS;
}

static struct usb_function verify_funcions = {
	.bind      = UsbdVerifyBind,
	.unbind    = UsbdVerifyUnbind,
	.setup     = UsbdVerifySetup,
	.set_alt   = UsbdVerifySetAlt,
	.disable   = UsbdVerifyDisable,
	.free_func = UsbdVerifyFree,
};

static struct usb_composite_driver verify_driver = {
	.dev_desc    = &verify_device_desc,
	.strings     = verify_gadget_strings,
	.config_desc = &verify_config_desc,
	.functions   = &verify_funcions,
	.driver_data = &usbd_test_dev,
	.config      = UsbdVerifyConfig,
};

int UsbdVerifyInit(void)
{
	int status = -USB_EINVAL;

	rtw_init_sema(&wait_equeue_sema, 0);

	status = usb_composite_register(&verify_driver);
	if (status != 0) {
		DBG_8195A("Fail to register composite driver");
		usb_composite_unregister(&verify_driver);
		goto usbd_verify_init_fail;
	}

	return USB_ESUCCESS;

usbd_verify_init_fail:  
	rtw_free_sema(&wait_equeue_sema);
	return status;
}

void UsbdVerifyDeinit(void)
{
	rtw_free_sema(&wait_equeue_sema);
	usb_composite_unregister(&verify_driver);
}

static void usbd_wait_equeue_thread(void *param)
{  
	int status;
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	UNUSED(param);

	rtw_down_sema(&wait_equeue_sema);
	rtw_mdelay_os(50);
	
	status = usb_ep_queue(vdev->int_in_ep, vdev->int_in_req, 1);
	if (status) {
		DBG_8195A("Fail to enqueue interrupt in request\n");
	}
exit:
	rtw_thread_exit();
}

/*
	USBD   full/high   ctrl
	USBD   full/high   bulk  in/out/inout  transfer_size  long_run_flag
	USBD   full/high   iso  in/out  buf_size  long_run_flag
	USBD   full/high   int  in/out/inout  transfer_size  long_run_flag
*/
u32
CmdUsbdTest(
    IN  u16 argc,
    IN  u8  *argv[]
)
{
	int status;
	int speed;
	struct usb_verify_device_t *vdev = &usbd_test_dev;
	struct task_struct task;

	rtw_memset(vdev, 0, sizeof(struct usb_verify_device_t));

	if (strcmp(argv[0], "full") == 0) {
		speed = USB_SPEED_FULL;
	} else {
		speed = USB_SPEED_HIGH;
	}
	
	status = usb_init(speed);
	if (status != USB_INIT_OK) {
		DBG_8195A("\nFail to init USB device: %d\n", status);
		return _FALSE;
	}

	status = UsbdVerifyInit();
	if (status < 0) {
		DBG_8195A("\nFail to init USB device verify driver: %d\n", status);
		usb_deinit();
		return _FALSE;
	}
	
	if (strcmp(argv[1], "ctrl") == 0) {
		DBG_8195A("usb device control transfer test\n");
		vdev->ctrl_cb= UsbdVerifyCtrl;
	} else if (strcmp(argv[1], "bulk") == 0) {
		vdev->bulk_buf_size = _strtoul((const u8*)(argv[3]), (u8 **)NULL, 10);
		vdev->long_run_flag = _strtoul((const u8*)(argv[4]), (u8 **)NULL, 10);
		if(strcmp(argv[2], "in") == 0) {
			DBG_8195A("usb device bulk in transfer test\n");
			vdev->test_mode = 1;
		} else if(strcmp(argv[2], "out") == 0) {
			DBG_8195A("usb device bulk out transfer test\n");
			vdev->test_mode = 2;
		} else {
			DBG_8195A("usb device bulk inout transfer test\n");
			vdev->test_mode = 3;
		}
		vdev->alt_cb = UsbdVerifyBulk;
	} else if (strcmp(argv[1], "iso") == 0) {
	// macro USBD_ISO_VERIFY should set to 1
		vdev->iso_buf_size = _strtoul((const u8*)(argv[3]), (u8 **)NULL, 10);
		vdev->long_run_flag = _strtoul((const u8*)(argv[4]), (u8 **)NULL, 10);
		if(strcmp(argv[2], "in") == 0) {
			DBG_8195A("usb device iso in transfer test\n");
			vdev->alt_cb = UsbdVerifyIsoIn;
		} else {
			DBG_8195A("usb device iso out transfer test\n");
			vdev->alt_cb = UsbdVerifyIsoOut;
		}
	} else if (strcmp(argv[1], "int") == 0) {
	// macro USBD_ISO_VERIFY should set to 0
		vdev->int_buf_size = _strtoul((const u8*)(argv[3]), (u8 **)NULL, 10);
		vdev->long_run_flag = _strtoul((const u8*)(argv[4]), (u8 **)NULL, 10);
		if(strcmp(argv[2], "in") == 0) {
			DBG_8195A("usb device interrupt in transfer test\n");
			status = rtw_create_task(&task, "usbd_wait_equeue_thread", 1024, tskIDLE_PRIORITY + 2, usbd_wait_equeue_thread, NULL);
			if (status != pdPASS) {
				printf("\nFail to create USBD wait equeue thread\n");
				usb_deinit();
				return _FALSE;
			}
			vdev->test_mode = 1;
		} else if(strcmp(argv[2], "out") == 0) {
			DBG_8195A("usb device interrupt out transfer test\n");
			vdev->test_mode = 2;
		}  else {
			DBG_8195A("usb device interrupt inout transfer test\n");
			vdev->test_mode = 3;
		}
		vdev->alt_cb = UsbdVerifyInt;
	} else {
		DBG_8195A("%s: wrong cmd!!!\n", __FUNCTION__);
		return _FALSE;
	}

	return _TRUE;
}

CMD_TABLE_DATA_SECTION
const COMMAND_TABLE   usbd_test_cmd_table[] = {
	{(const u8*)"USBD",  1, CmdUsbdTest,      (const u8*)"\tUsb device \n"
	                                              "\t\t usb device test, input verification item \n"},
};
