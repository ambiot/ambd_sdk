#ifndef __USB_VERIFY_HOST_H
#define __USB_VERIFY_HOST_H
#include "usb.h"

typedef enum _USB_DATA_MODE_
{
	USB_DATA_FIX = 0,
	USB_DATA_SEQ = 1,
	USB_DATA_RND = 2
} USB_DATA_MODE, *PUSB_DATA_MODE;

struct usb_test {
	int in_bulk_addr;
	int out_bulk_addr;
	u32 bulk_buf_size;
	struct urb *bulk_in_urb;
	u8 *bulk_in_buf;
	struct urb *bulk_out_urb;
	u8 *bulk_out_buf;
	
	int in_iso_addr;
	int out_iso_addr;
	struct usb_endpoint_descriptor  *iso_in, *iso_out;
	u32 iso_pcnt;
	u32 iso_psize;
	struct urb *iso_in_urb;
	u8 *iso_in_buf;
	struct urb *iso_out_urb;
	u8 *iso_out_buf;
	
	int in_int_addr;
	int out_int_addr;
	u32 int_buf_size;
	struct usb_endpoint_descriptor  *int_in, *int_out;
	struct urb *int_in_urb;
	u8 *int_in_buf;
	struct urb *int_out_urb;
	u8 *int_out_buf;
	
	void(* probe_cb)(struct usb_device *udev);
	void(* disconnect_cb)(struct usb_device *udev, struct usb_interface *intf);
	u8 long_run_flag;
};
#endif	//__USB_VERIFY_HOST_H