#include "usb.h"
#include "rand.h"
#include "rtl8721d_usbh_test.h"

struct usb_test *usbh_test_dev;
static u8 *GoldenData;
static int data_count = 0;

/*
*To Compare out and in data
*/
BOOL UsbhDataCompare(u8 *pSrc, u8 *pDst, u32 Length)
{
	int Index;
	
	for (Index = 0; Index < Length; ++Index){
		if(pSrc[Index] != pDst[Index]) {
			DBG_8195A("Src/Dst data[%d] = %x/%x\n", Index, pSrc[Index], pDst[Index]);
			return _FALSE;
		}
	}
	return _TRUE;
}

/*
*To Generate Tx Data
*Mode:
	USB_DATA_SEQ: fixed
	USB_DATA_SEQ: sequential 
	USB_DATA_RND: random
*/
void UsbhDataGenerate(u8 *pTxArray, u32 Length, u32 Mode)
{
	u32 i  = 0;
	_memset(pTxArray, 0x0, Length);

	switch (Mode)
	{
		case USB_DATA_FIX:
			for(i = 0; i < Length; i++)
				pTxArray[i] = 0x3E;
			break;
		case USB_DATA_SEQ:
			for(i = 0; i < Length; i++)
				pTxArray[i] = i & 0xFF;
			break;
		case USB_DATA_RND:
			for(i = 0; i < Length; i++)
				pTxArray[i] =  Rand() & 0xFF;
			break;
		default:
			break;
	}
}

static int UsbhVerifyEpnum(struct usb_test *dev, struct usb_interface *intf)
{
	unsigned int tmp = 0;
	unsigned int i = 0;
	struct usb_host_interface *alt;
	int ret = 0;

	for (tmp = 0; tmp < intf->num_altsetting; tmp++) {
		alt = intf->altsetting + tmp;

		for (i = 0; i < alt->desc.bNumEndpoints; i++) {
			struct usb_endpoint_descriptor *desc = &alt->endpoint[i].desc;
			int edi;
			edi = usb_endpoint_dir_in(desc);

			switch (usb_endpoint_type(desc)) {
				case USB_ENDPOINT_XFER_BULK:
					if (edi) {
						dev->in_bulk_addr = usb_endpoint_num(desc);
					} else {
						dev->out_bulk_addr = usb_endpoint_num(desc);
					}

					if (!dev->in_bulk_addr && !dev->out_bulk_addr) 
						ret = -USB_ENOENT;

					break;

				case USB_ENDPOINT_XFER_ISOC:
					if (edi) {
						dev->in_iso_addr = usb_endpoint_num(desc);
						dev->iso_in = desc;
					} else {
						dev->out_iso_addr = usb_endpoint_num(desc);
						dev->iso_out = desc;
					}

					if (!dev->in_iso_addr && !dev->out_iso_addr) 
						ret = -USB_ENOENT;

					break;

				case USB_ENDPOINT_XFER_INT:
					if (edi) {
						dev->in_int_addr = usb_endpoint_num(desc);
						dev->int_in = desc;
					} else {
						dev->out_int_addr = usb_endpoint_num(desc);
						dev->int_out = desc;
					}

					if (!dev->in_int_addr && !dev->out_int_addr) 
						ret = -USB_ENOENT;

					break;

				default:
					break;
			}
		}
	}

	if (ret) {
		DBG_8195A("Endpoint sanity check failed! Rejecting dev.\n");
		return ret;
	}

	return 0;
}

void UsbhVerifyCtrl(struct usb_device *udev)
{
	u8 ctrl_data_buf[2];
	struct usb_ctrlrequest *ctrl_setup_buf;
	int ctrl_ret;
	
	ctrl_setup_buf = rtw_zmalloc(sizeof(struct usb_ctrlrequest));
	if (!ctrl_setup_buf) {
		DBG_8195A("Fail to allocate control setup buffer\n");
		goto exit;
	}
	// Get device status
	ctrl_setup_buf->bRequestType = 0x80;
	ctrl_setup_buf->bRequest = USB_REQ_GET_STATUS;
	ctrl_setup_buf->wValue = 0;
	ctrl_setup_buf->wIndex = 0;
	ctrl_setup_buf->wLength = 0x0002;

	ctrl_data_buf[0] = 99; //this buf is used to receive the return value by device
	ctrl_ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), ctrl_setup_buf->bRequest, ctrl_setup_buf->bRequestType, ctrl_setup_buf->wValue, ctrl_setup_buf->wIndex, ctrl_data_buf, ctrl_setup_buf->wLength, 1000);
	if (ctrl_ret < 0) {
		DBG_8195A("Fail to commit get device status urb, ctrl_ret: %d\n", ctrl_ret);
	} else {
		DBG_8195A("Device status(self-power, remote-wakeup): %d, %d\n", ctrl_data_buf[0], ctrl_data_buf[1]);
	}
	
	// Set vendor request	modify endpoint 
	ctrl_setup_buf->bRequestType = 0x42;
	ctrl_setup_buf->bRequest = 0;
	ctrl_setup_buf->wValue = 0x0100;
	ctrl_setup_buf->wIndex = 0x0002;
	ctrl_setup_buf->wLength = 0x0002;
	//modify self power, wakeup
	ctrl_data_buf[0] = 1;
	ctrl_data_buf[1] = 1;
	
	ctrl_ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), ctrl_setup_buf->bRequest, ctrl_setup_buf->bRequestType, ctrl_setup_buf->wValue, ctrl_setup_buf->wIndex, ctrl_data_buf, ctrl_setup_buf->wLength, 5000);

	if (ctrl_ret < 0) {
		DBG_8195A("Fail to commit set device descriptor urb, ctrl_ret: %d\n", ctrl_ret);
	}

exit:
	if(ctrl_setup_buf)
		rtw_free(ctrl_setup_buf);
	if(ctrl_data_buf)
		rtw_free(ctrl_data_buf);
}

static void usbh_bulk_in_complete(struct urb *urb)
{
	int ret;

	if(!usbh_get_connect_status())
		return;
	
	if(UsbhDataCompare(GoldenData, urb->transfer_buffer, urb->transfer_buffer_length)) {
		if(usbh_test_dev->long_run_flag) {
			if(data_count == 5000) {
				data_count = 0;
				DBG_8195A("Success\n");
			}
			data_count ++;
		} else {
			DBG_8195A("usbh bulk in data success\n");
		}
	} else {
		DBG_8195A("usbh bulk in data fail\n");
		return;
	}

	if(usbh_test_dev->long_run_flag) {
		rtw_memset(urb->transfer_buffer, 0x00, urb->transfer_buffer_length);
		
		ret = usb_submit_urb(urb);
		if (ret < 0) {
			DBG_8195A("\nFail to resubmit bulk in urb: %d\n", ret);
		}
	}
}

static void usbh_bulk_out_complete(struct urb *urb)
{
	int ret;

	if(!usbh_get_connect_status())
		return;

	//DBG_8195A("test_bulk_out_complete\n");

	if(usbh_test_dev->long_run_flag) {
		ret = usb_submit_urb(urb);
		if (ret < 0) {
			DBG_8195A("\nFail to resubmit bulk out urb: %d\n", ret);
		}
	}
}

void UsbhVerifyBulkIn(struct usb_device *udev)
{
	int ret = -1;

	usbh_test_dev->bulk_in_urb = usb_alloc_urb(0);
	if (!usbh_test_dev->bulk_in_urb) {
		DBG_8195A("Fail to allocate bulk in urb\n");
		goto exit;
	}

	GoldenData  = rtw_zmalloc(usbh_test_dev->bulk_buf_size);
	if (!GoldenData) {
		DBG_8195A("Fail to allocate golden data buffer\n");
		goto exit;
	}
	UsbhDataGenerate(GoldenData, usbh_test_dev->bulk_buf_size, USB_DATA_SEQ);

	usbh_test_dev->bulk_in_buf= rtw_zmalloc(usbh_test_dev->bulk_buf_size);
	if (!usbh_test_dev->bulk_in_buf) {
		DBG_8195A("Fail to allocate bulk in buffer\n");
		goto exit;
	}
	// fill bulk in parameters
	usb_fill_bulk_urb(usbh_test_dev->bulk_in_urb, udev, usb_rcvbulkpipe(udev, usbh_test_dev->in_bulk_addr), usbh_test_dev->bulk_in_buf, usbh_test_dev->bulk_buf_size, usbh_bulk_in_complete, NULL);

	ret = usb_submit_urb(usbh_test_dev->bulk_in_urb);
	if (ret < 0) {
		DBG_8195A("Fail to commit bulk in urb: %d\n", ret);
		goto exit;
	}

	return;

exit:
	if(usbh_test_dev->bulk_in_urb)
		rtw_free(usbh_test_dev->bulk_in_urb);

	if(usbh_test_dev->bulk_in_buf)
		rtw_free(usbh_test_dev->bulk_in_buf);
	
	if(GoldenData)
		rtw_free(GoldenData);
}

void UsbhVerifyBulkOut(struct usb_device *udev)
{
	int ret;

	usbh_test_dev->bulk_out_urb = usb_alloc_urb(0);
	if (!usbh_test_dev->bulk_out_urb) {
		DBG_8195A("Fail to allocate bulk out urb\n");
		goto exit;
	}

	usbh_test_dev->bulk_out_buf = rtw_zmalloc(usbh_test_dev->bulk_buf_size);
	if (!usbh_test_dev->bulk_out_buf) {
		DBG_8195A("Fail to allocate bulk out buffer\n");
		goto exit;
	}
	UsbhDataGenerate(usbh_test_dev->bulk_out_buf, usbh_test_dev->bulk_buf_size, USB_DATA_SEQ);

	// fill bulk out parameters
	usb_fill_bulk_urb(usbh_test_dev->bulk_out_urb, udev, usb_sndbulkpipe(udev, usbh_test_dev->out_bulk_addr), usbh_test_dev->bulk_out_buf, usbh_test_dev->bulk_buf_size, usbh_bulk_out_complete, NULL);

	ret = usb_submit_urb(usbh_test_dev->bulk_out_urb);
	if (ret < 0) {
		DBG_8195A("Fail to commit bulk out urb: %d\n", ret);
		goto exit;
	}

	return;

exit:
	if(usbh_test_dev->bulk_out_urb)
		rtw_free(usbh_test_dev->bulk_out_urb);
	
	if(usbh_test_dev->bulk_out_buf)
		rtw_free(usbh_test_dev->bulk_out_buf);
}

void UsbhVerifyBulk(struct usb_device *udev)
{
	u8 *bufin;
	u8 *bufout;
	u32 i =0;
	u32 mode =0;
	u32 actual_length=0, actual_length1=0;
	int ret = -1;

	bufout  = rtw_zmalloc(usbh_test_dev->bulk_buf_size);
	if (!bufout) {
		DBG_8195A("Fail to allocate bulk out buffer\n");
		goto exit;
	}

	bufin = rtw_zmalloc(usbh_test_dev->bulk_buf_size);
	if (!bufin) {
		DBG_8195A("Fail to allocate bulk in buffer\n");
		goto exit;
	}

	while(1) {
		if(!usbh_get_connect_status())
			return;
		
		i++;
		mode = Rand() % 3;
		_memset(bufout, usbh_test_dev->bulk_buf_size, 0);
		UsbhDataGenerate(bufout, usbh_test_dev->bulk_buf_size, mode);
		_memset(bufin, usbh_test_dev->bulk_buf_size, 0);

		//bulk out
		ret = usb_bulk_msg(udev, usb_sndbulkpipe(udev, usbh_test_dev->out_bulk_addr), bufout, usbh_test_dev->bulk_buf_size, &actual_length, 1000);
		if (ret) {
			DBG_8195A("Fail to commit bulk out urb: %d\n", ret);
			break;
		}
		
		DelayMs(2);	//buffer size >=1024 need, or it will occur bulk in timeout
		
		//bulk in
		ret = usb_bulk_msg(udev, usb_rcvbulkpipe(udev, usbh_test_dev->in_bulk_addr), bufin, usbh_test_dev->bulk_buf_size, &actual_length1, 1000);
		if (ret) {
			DBG_8195A("Fail to commit bulk in urb: %d\n", ret);
			break;
		}
		
		if(UsbhDataCompare(bufout, bufin, usbh_test_dev->bulk_buf_size) == _FALSE) {
			DBG_8195A("loopback fail %d\n", i);
			break;
		} else {
			if(usbh_test_dev->long_run_flag) {	//long run
				if(i == 5000) {
					i = 0;
					DBG_8195A("success\n");
				}
			} else {	//run once
				DBG_8195A("success\n");
				break;
			}
		}
	}
exit:
	if(bufin)
		rtw_free(bufin);
	if(bufout)
		rtw_free(bufout);
}

static void usbh_iso_in_complete(struct urb *urb)
{
	int ret;

	if(!usbh_get_connect_status())
		return;
	if(UsbhDataCompare(GoldenData, urb->transfer_buffer, urb->transfer_buffer_length)) {
		data_count ++;
		if(!usbh_test_dev->long_run_flag)
			DBG_8195A("usbh iso in data success\n");
	} else {
		DBG_8195A("usbh iso in data fail\n");
	}

	if(usbh_test_dev->long_run_flag) {
		rtw_memset(urb->transfer_buffer, 0x00, urb->transfer_buffer_length);
		if(data_count == 5000) {
			data_count = 0;
			DBG_8195A("success\n");
		}
		
		ret = usb_submit_urb(urb);
		if (ret < 0) {
			DBG_8195A("\nFail to resubmit iso in urb: %d\n", ret);
		}
	}
}

static void usbh_iso_out_complete(struct urb *urb)
{
	int ret;
	
	if(!usbh_get_connect_status())
		return;

	//DBG_8195A("test_iso_out_complete\n");

	if(usbh_test_dev->long_run_flag) {
		ret = usb_submit_urb(urb);
		if (ret < 0) {
			DBG_8195A("\nFail to resubmit iso out urb: %d\n", ret);
		}
	}
}

void UsbhVerifyIsoIn(struct usb_device *udev)
{
	u32 i;
	int status;

	GoldenData  = rtw_zmalloc(usbh_test_dev->iso_pcnt * usbh_test_dev->iso_psize);
	if (!GoldenData) {
		DBG_8195A("Fail to allocate golden data buffer\n");
		goto iso_fail;
	}
	UsbhDataGenerate(GoldenData, usbh_test_dev->iso_pcnt * usbh_test_dev->iso_psize, USB_DATA_SEQ);

	usbh_test_dev->iso_in_buf = rtw_zmalloc(usbh_test_dev->iso_pcnt * usbh_test_dev->iso_psize);
	if (!usbh_test_dev->iso_in_buf) {
		DBG_8195A("Fail to allocate iso in buffer\n");
		goto iso_fail;
	}	
	rtw_memset((void *)usbh_test_dev->iso_in_buf, 0x00, usbh_test_dev->iso_pcnt * usbh_test_dev->iso_psize);

	usbh_test_dev->iso_in_urb = usb_alloc_urb(usbh_test_dev->iso_pcnt);
	if (!usbh_test_dev->iso_in_urb) {
		DBG_8195A("Fail to allocate iso in urb\n");
		goto iso_fail;
	}
	usbh_test_dev->iso_in_urb->dev = udev;
	usbh_test_dev->iso_in_urb->pipe = usb_rcvisocpipe(udev, usbh_test_dev->in_iso_addr);
	usbh_test_dev->iso_in_urb->transfer_flags = URB_ISO_ASAP;
	usbh_test_dev->iso_in_urb->interval = usbh_test_dev->iso_in->bInterval;
	usbh_test_dev->iso_in_urb->transfer_buffer = usbh_test_dev->iso_in_buf;
	usbh_test_dev->iso_in_urb->complete = usbh_iso_in_complete;
	usbh_test_dev->iso_in_urb->context = NULL;
	usbh_test_dev->iso_in_urb->number_of_packets = usbh_test_dev->iso_pcnt ;
	usbh_test_dev->iso_in_urb->transfer_buffer_length = usbh_test_dev->iso_pcnt * usbh_test_dev->iso_psize; 

	for (i = 0; i < usbh_test_dev->iso_pcnt; ++i) {
		usbh_test_dev->iso_in_urb->iso_frame_desc[i].offset = i * usbh_test_dev->iso_psize;
		usbh_test_dev->iso_in_urb->iso_frame_desc[i].length = usbh_test_dev->iso_psize;
	}
	status = usb_submit_urb(usbh_test_dev->iso_in_urb);
	if (status < 0) {
		DBG_8195A("Fail to commit iso in urb: %d\n", status);
		goto iso_fail;
	}
	
	return;

iso_fail:
	if (GoldenData) {
		rtw_free(GoldenData);
	}
	
	if (usbh_test_dev->iso_in_urb) {
		usb_free_urb(usbh_test_dev->iso_in_urb);
	}
		
	if (usbh_test_dev->iso_in_buf) {
		rtw_free(usbh_test_dev->iso_in_buf);
	}
}

void UsbhVerifyIsoOut(struct usb_device *udev)
{
	u32 i;
	int status;

	usbh_test_dev->iso_out_buf = rtw_zmalloc(usbh_test_dev->iso_pcnt * usbh_test_dev->iso_psize);
	if (!usbh_test_dev->iso_out_buf) {
		DBG_8195A("Fail to allocate iso out buffer\n");
		goto iso_fail;
	}
	UsbhDataGenerate(usbh_test_dev->iso_out_buf, usbh_test_dev->iso_pcnt * usbh_test_dev->iso_psize, USB_DATA_SEQ);

	usbh_test_dev->iso_out_urb = usb_alloc_urb(usbh_test_dev->iso_pcnt);
	if (!usbh_test_dev->iso_out_urb) {
		DBG_8195A("Fail to allocate iso out urb\n");
		goto iso_fail;
	}
	usbh_test_dev->iso_out_urb->dev = udev;
	usbh_test_dev->iso_out_urb->pipe = usb_sndisocpipe(udev, usbh_test_dev->out_iso_addr);
	usbh_test_dev->iso_out_urb->transfer_flags = URB_ISO_ASAP;
	usbh_test_dev->iso_out_urb->interval = usbh_test_dev->iso_out->bInterval;
	usbh_test_dev->iso_out_urb->transfer_buffer = usbh_test_dev->iso_out_buf;
	usbh_test_dev->iso_out_urb->complete = usbh_iso_out_complete;
	usbh_test_dev->iso_out_urb->context = NULL;
	usbh_test_dev->iso_out_urb->number_of_packets = usbh_test_dev->iso_pcnt;
	usbh_test_dev->iso_out_urb->transfer_buffer_length = usbh_test_dev->iso_pcnt * usbh_test_dev->iso_psize;

	for (i = 0; i < usbh_test_dev->iso_pcnt; ++i) {
		usbh_test_dev->iso_out_urb->iso_frame_desc[i].offset = i * usbh_test_dev->iso_psize;
		usbh_test_dev->iso_out_urb->iso_frame_desc[i].length = usbh_test_dev->iso_psize;
	}
	
	status = usb_submit_urb(usbh_test_dev->iso_out_urb);
	if (status < 0) {
		DBG_8195A("Fail to commit iso out urb: %d\n", status);
		goto iso_fail;
	}
	
	return;

iso_fail:
	if (usbh_test_dev->iso_out_urb) {
		usb_free_urb(usbh_test_dev->iso_out_urb);
	}
	
	if (usbh_test_dev->iso_out_buf) {
		rtw_free(usbh_test_dev->iso_out_buf);
	}
}

static void usbh_int_in_complete(struct urb *urb)
{
	int ret;

	if(!usbh_get_connect_status())
		return;
	
	if(UsbhDataCompare(GoldenData, urb->transfer_buffer, urb->transfer_buffer_length)) {
		if(usbh_test_dev->long_run_flag) {
			if(data_count == 5000) {
				data_count = 0;
				DBG_8195A("Success\n");
			}
			data_count ++;
		} else {
			DBG_8195A("usbh interrupt in data success\n");
		}
	} else {
		DBG_8195A("usbh interrupt in data fail\n");
		return;
	}

	if(usbh_test_dev->long_run_flag) {
		rtw_memset(urb->transfer_buffer, 0x00, urb->transfer_buffer_length);
		
		ret = usb_submit_urb(urb);
		if (ret < 0) {
			DBG_8195A("\nFail to resubmit interrupt in urb: %d\n", ret);
		}
	}
}

static void usbh_int_out_complete(struct urb *urb)
{
	int ret;

	if(!usbh_get_connect_status())
		return;

	//DBG_8195A("test_int_out_complete\n");

	if(usbh_test_dev->long_run_flag) {
		ret = usb_submit_urb(urb);
		if (ret < 0) {
			DBG_8195A("\nFail to resubmit interrupt out urb: %d\n", ret);
		}
	}
}

void UsbhVerifyIntIn(struct usb_device *udev)
{
	int ret = -1;

	usbh_test_dev->int_in_urb= usb_alloc_urb(0);
	if (!usbh_test_dev->int_in_urb) {
		DBG_8195A("Fail to allocate interrupt in urb\n");
		goto exit;
	}

	GoldenData  = rtw_zmalloc(usbh_test_dev->int_buf_size);
	if (!GoldenData) {
		DBG_8195A("Fail to allocate golden data buffer\n");
		goto exit;
	}
	UsbhDataGenerate(GoldenData, usbh_test_dev->int_buf_size, USB_DATA_SEQ);

	usbh_test_dev->int_in_buf = rtw_zmalloc(usbh_test_dev->int_buf_size);
	if (!usbh_test_dev->int_in_buf) {
		DBG_8195A("Fail to allocate interrupt in buffer\n");
		goto exit;
	}
	// fill interrupt in parameters
	usb_fill_int_urb(usbh_test_dev->int_in_urb, udev, usb_rcvintpipe(udev, usbh_test_dev->in_int_addr), usbh_test_dev->int_in_buf, usbh_test_dev->int_buf_size, usbh_int_in_complete, NULL, usbh_test_dev->int_in->bInterval);

	ret = usb_submit_urb(usbh_test_dev->int_in_urb);
	if (ret < 0) {
		DBG_8195A("Fail to commit interrupt in urb: %d\n", ret);
		goto exit;
	}

	return;

exit:
	if(usbh_test_dev->int_in_urb)
		rtw_free(usbh_test_dev->int_in_urb);

	if(usbh_test_dev->int_in_buf)
		rtw_free(usbh_test_dev->int_in_buf);
	
	if(GoldenData)
		rtw_free(GoldenData);
}

void UsbhVerifyIntOut(struct usb_device *udev)
{
	int ret;

	usbh_test_dev->int_out_urb = usb_alloc_urb(0);
	if (!usbh_test_dev->int_out_urb) {
		DBG_8195A("Fail to allocate interrupt out urb\n");
		goto exit;
	}

	usbh_test_dev->int_out_buf = rtw_zmalloc(usbh_test_dev->int_buf_size);
	if (!usbh_test_dev->int_out_buf) {
		DBG_8195A("Fail to allocate interrupt out buffer\n");
		goto exit;
	}
	UsbhDataGenerate(usbh_test_dev->int_out_buf, usbh_test_dev->int_buf_size, USB_DATA_SEQ);

	// fill interrupt out parameters
	usb_fill_int_urb(usbh_test_dev->int_out_urb, udev, usb_sndintpipe(udev, usbh_test_dev->out_int_addr), usbh_test_dev->int_out_buf, usbh_test_dev->int_buf_size, usbh_int_out_complete, NULL, usbh_test_dev->int_out->bInterval);

	ret = usb_submit_urb(usbh_test_dev->int_out_urb);
	if (ret < 0) {
		DBG_8195A("Fail to commit interrupt out urb: %d\n", ret);
		goto exit;
	}

	return;

exit:
	if(usbh_test_dev->int_out_urb)
		rtw_free(usbh_test_dev->int_out_urb);

	if(usbh_test_dev->int_out_buf)
		rtw_free(usbh_test_dev->int_out_buf);
}

void UsbhVerifyInt(struct usb_device *udev)
{
	u8 *bufin;
	u8 *bufout;
	u32 i =0;
	u32 mode =0;
	u32 actual_length=0, actual_length1=0;
	int ret = -1;

	bufout  = rtw_zmalloc(usbh_test_dev->int_buf_size);
	if (!bufout) {
		DBG_8195A("Fail to allocate interrupt out buffer\n");
		goto exit;
	}

	bufin = rtw_zmalloc(usbh_test_dev->int_buf_size);
	if (!bufin) {
		DBG_8195A("Fail to allocate interrupt in buffer\n");
		goto exit;
	}

	while(1) {
		if(!usbh_get_connect_status())
			return;
		
		i++;
		mode = Rand() % 3;
		_memset(bufout, usbh_test_dev->int_buf_size, 0);
		UsbhDataGenerate(bufout, usbh_test_dev->int_buf_size, mode);
		_memset(bufin, usbh_test_dev->int_buf_size, 0);

		//interrupt out
		ret = usb_bulk_msg(udev, usb_sndintpipe(udev, usbh_test_dev->out_int_addr), bufout, usbh_test_dev->int_buf_size, &actual_length, 1000);
		if (ret) {
			DBG_8195A("Fail to commit interrupt out urb: %d\n", ret);
			break;
		}
		//interrupt in
		ret = usb_bulk_msg(udev, usb_rcvintpipe(udev, usbh_test_dev->in_int_addr), bufin, usbh_test_dev->int_buf_size, &actual_length1, 1000);
		if (ret) {
			DBG_8195A("Fail to commit interrupt in urb: %d\n", ret);
			break;
		}
		
		if(UsbhDataCompare(bufout, bufin, usbh_test_dev->int_buf_size) == _FALSE) {
			DBG_8195A("loopback fail %d\n", i);
			break;
		} else {
			if(usbh_test_dev->long_run_flag) {	//long run
				if(i == 5000) {
					i = 0;
					DBG_8195A("success\n");
				}
			} else {	//run once
				DBG_8195A("success\n");
				break;
			}
		}
	}
exit:
	if(bufin)
		rtw_free(bufin);
	if(bufout)
		rtw_free(bufout);
}

void UsbhVerifyFree(struct usb_device *udev, struct usb_interface *intf)
{
	if(GoldenData)
		rtw_free(GoldenData);

	if(usbh_test_dev->bulk_in_urb)
		rtw_free(usbh_test_dev->bulk_in_urb);

	if(usbh_test_dev->bulk_in_buf)
		rtw_free(usbh_test_dev->bulk_in_buf);

	if(usbh_test_dev->bulk_out_urb)
		rtw_free(usbh_test_dev->bulk_out_urb);
	
	if(usbh_test_dev->bulk_out_buf)
		rtw_free(usbh_test_dev->bulk_out_buf);
	
	if (usbh_test_dev->iso_in_urb) {
		usb_free_urb(usbh_test_dev->iso_in_urb);
	}
		
	if (usbh_test_dev->iso_in_buf) {
		rtw_free(usbh_test_dev->iso_in_buf);
	}
	
	if (usbh_test_dev->iso_out_urb) {
		usb_free_urb(usbh_test_dev->iso_out_urb);
	}
	
	if (usbh_test_dev->iso_out_buf) {
		rtw_free(usbh_test_dev->iso_out_buf);
	}

	if(usbh_test_dev->int_in_urb)
		rtw_free(usbh_test_dev->int_in_urb);

	if(usbh_test_dev->int_in_buf)
		rtw_free(usbh_test_dev->int_in_buf);

	if(usbh_test_dev->int_out_urb)
		rtw_free(usbh_test_dev->int_out_urb);

	if(usbh_test_dev->int_out_buf)
		rtw_free(usbh_test_dev->int_out_buf);
	
	if(udev && intf) {
		usb_disable_interface(udev, intf, TRUE);
	}
}

static int UsbhVerifyProbe(struct usb_interface *intf)
{
	struct usb_device *udev = interface_to_usbdev(intf); 
	u32 ret;

	ret = UsbhVerifyEpnum(usbh_test_dev, intf);
	if(ret < 0) {
		DBG_8195A("Endpoint address get fail.\n");
		return -1;
	}

	if(usbh_test_dev->probe_cb)
		usbh_test_dev->probe_cb(udev);
		
	return 0;
}

static void UsbhVerifyDisconnect(struct usb_interface *intf)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	
	if(usbh_test_dev->disconnect_cb)
		usbh_test_dev->disconnect_cb(udev, intf);
}

static struct usb_driver usbh_verify_driver =
{
    .name = "usbh_verify",
    .probe = UsbhVerifyProbe,
    .disconnect = UsbhVerifyDisconnect,
};

int UsbhVerifyInit(void)
{
	usbh_test_dev = (struct usb_test *)rtw_zmalloc(sizeof * usbh_test_dev);
	if(!usbh_test_dev) {
		DBG_8195A("Dev malloc fail \n");
		return -USB_ENOMEM;
	}
	return usb_register_class_driver(&usbh_verify_driver);
}

int UsbhVerifyDeinit(void)
{
	if(usbh_test_dev) {
		rtw_free(usbh_test_dev);
	}
	return usb_unregister_class_driver(&usbh_verify_driver);
}

/*
	USBH   ctrl
	USBH   bulk  in/out/inout  transfer_size  long_run_flag
	USBH   iso  in/out  packet_number  packet_size(<=ep_max_packet_size)  long_run_flag
	USBH   int  in/out/inout  transfer_size  long_run_flag
*/
u32
CmdUsbhTest(
    IN  u16 argc,
    IN  u8  *argv[]
)
{
	int status;
	
	status = usb_init();
	if (status != USB_INIT_OK) {
		DBG_8195A("\nFail to init USB host controller: %d\n", status);
		return _FALSE;
	}

	status = UsbhVerifyInit();
	if (status < 0) {
		DBG_8195A("\nFail to init USB host verify driver: %d\n", status);
		usb_deinit();
		return _FALSE;
	}
	
	if (strcmp(argv[0], "ctrl") == 0) {
		DBG_8195A("usb host control transfer test\n");
		usbh_test_dev->probe_cb= UsbhVerifyCtrl;
	} else if (strcmp(argv[0], "bulk") == 0) {
		usbh_test_dev->bulk_buf_size = _strtoul((const u8*)(argv[2]), (u8 **)NULL, 10);
		usbh_test_dev->long_run_flag = _strtoul((const u8*)(argv[3]), (u8 **)NULL, 10);
		if(strcmp(argv[1], "in") == 0) {
			DBG_8195A("usb host bulk in transfer test\n");
			usbh_test_dev->probe_cb = UsbhVerifyBulkIn;
		} else if(strcmp(argv[1], "out") == 0) {
			DBG_8195A("usb host bulk out transfer test\n");
			usbh_test_dev->probe_cb = UsbhVerifyBulkOut;
		} else {
			DBG_8195A("usb host bulk inout transfer test\n");
			usbh_test_dev->probe_cb = UsbhVerifyBulk;
		}
	} else if (strcmp(argv[0], "iso") == 0) {
		usbh_test_dev->iso_pcnt = _strtoul((const u8*)(argv[2]), (u8 **)NULL, 10);
		usbh_test_dev->iso_psize = _strtoul((const u8*)(argv[3]), (u8 **)NULL, 10);		//can't exceed device ep max packet size
		usbh_test_dev->long_run_flag = _strtoul((const u8*)(argv[4]), (u8 **)NULL, 10);
		if(strcmp(argv[1], "in") == 0) {
			DBG_8195A("usb host iso in transfer test\n");
			usbh_test_dev->probe_cb = UsbhVerifyIsoIn;
		} else {
			DBG_8195A("usb host iso out transfer test\n");
			usbh_test_dev->probe_cb = UsbhVerifyIsoOut;
		}
	} else if (strcmp(argv[0], "int") == 0) {
		usbh_test_dev->int_buf_size = _strtoul((const u8*)(argv[2]), (u8 **)NULL, 10);
		usbh_test_dev->long_run_flag = _strtoul((const u8*)(argv[3]), (u8 **)NULL, 10);
		if(strcmp(argv[1], "in") == 0) {
			DBG_8195A("usb host interrupt in transfer test\n");
			usbh_test_dev->probe_cb = UsbhVerifyIntIn;
		} else if(strcmp(argv[1], "out") == 0) {
			DBG_8195A("usb host interrupt out transfer test\n");
			usbh_test_dev->probe_cb = UsbhVerifyIntOut;
		}  else {
			DBG_8195A("usb host interrupt inout transfer test\n");
			usbh_test_dev->probe_cb = UsbhVerifyInt;
		}
	} else {
		DBG_8195A("%s: wrong cmd!!!\n", __FUNCTION__);
		return _FALSE;
	}
	
	usbh_test_dev->disconnect_cb = UsbhVerifyFree;

	return _TRUE;
}

CMD_TABLE_DATA_SECTION
const COMMAND_TABLE   usbh_test_cmd_table[] = {
	{(const u8*)"USBH",  1, CmdUsbhTest,      (const u8*)"\tUsb host \n"
	                                              "\t\t usb host test, input verification item \n"},
};
