#ifndef __USB_VERIFY_DEVICE_H
#define __USB_VERIFY_DEVICE_H
#include "usb_ch9.h"
#include "usb_gadget.h"

#define USBD_ISO_VERIFY					1

// String index
#define USBD_VERIFY_MANUFACTURER		1
#define USBD_VERIFY_PRODUCT				2
#define USBD_VERIFY_SERIALNUMBER			3
#define USBD_VERIFY_STRING_INTERFACE	4

// Endpoint address
#define USBD_VERIFY_BULK_IN_EP_ADDRESS		0x81
#define USBD_VERIFY_BULK_OUT_EP_ADDRESS	0x02
#define USBD_VERIFY_ISO_IN_EP_ADDRESS		0x83
#define USBD_VERIFY_ISO_OUT_EP_ADDRESS		0x04
#define USBD_VERIFY_INT_IN_EP_ADDRESS		0x83
#define USBD_VERIFY_INT_OUT_EP_ADDRESS		0x04

/** @defgroup USB_DESCRIPTORS
  * @{
  */
static struct usb_string verify_strings[] = {
	{
		.id = USBD_VERIFY_MANUFACTURER,
		.s  = "Realtek",
	},
	{
		.id = USBD_VERIFY_PRODUCT,
		.s  = "USB Verify Device",
	},
	{
		.id = USBD_VERIFY_SERIALNUMBER,
		.s  = "0123456789AB",
	},
	{
		.id = USBD_VERIFY_STRING_INTERFACE,
		.s  = "USB Verify Interface",
	}
};

static struct usb_gadget_strings verify_gadget_string_tab = {
	.language = 0x0409,
	.strings = verify_strings,
};
    
struct usb_gadget_strings *verify_gadget_strings[] = {
	&verify_gadget_string_tab,
	NULL
};

struct usb_device_descriptor verify_device_desc = {
	.bLength				= USB_DT_DEVICE_SIZE,
	.bDescriptorType		= USB_DT_DEVICE,
	.bcdUSB				= 0x0200,
	.bDeviceClass			= USB_CLASS_PER_INTERFACE,
	.bDeviceSubClass		= 0x00,
	.bDeviceProtocol		= 0x00,
	.bMaxPacketSize0		= 64,    // this will be set automatically depends on ep0 setting
	.idVendor				= REALTEK_USB_VID,
	.idProduct			= REALTEK_USB_PID,
	.bcdDevice			= 0x0100,
	.iManufacturer			= USBD_VERIFY_MANUFACTURER,
	.iProduct				= USBD_VERIFY_PRODUCT,
	.iSerialNumber		= USBD_VERIFY_SERIALNUMBER,
	.bNumConfigurations	= 0x01,
};

struct usb_config_descriptor verify_config_desc = {
	.bLength             = USB_DT_CONFIG_SIZE,
	.bDescriptorType     = USB_DT_CONFIG,
	.bNumInterfaces      = 1,                  // This will be assign automatically
	.bConfigurationValue = 1,
	.iConfiguration      = 0,
	.bmAttributes	     = USB_CONFIG_ATT_ONE, // | USB_CONFIG_ATT_SELFPOWER,
	.bMaxPower           = 50,
};

/* Vendor Interface, Alternate Setting 0*/
struct usb_interface_descriptor verify_intf_desc = {
	.bLength            = USB_DT_INTERFACE_SIZE,
	.bDescriptorType    = USB_DT_INTERFACE,
	.bInterfaceNumber   = 0x00, // this will be assign automatically
	.bAlternateSetting  = 0x00,
	.bNumEndpoints      = 0x04,
	.bInterfaceClass    = USB_CLASS_VENDOR_SPEC,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface         = USBD_VERIFY_STRING_INTERFACE,
};

/* Endpoint, EP Bulk IN, for Low-speed/Full-speed */
struct usb_endpoint_descriptor verify_bulk_in_ep_FS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_BULK_IN_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize   = 64,
	.bInterval        = 0x00,

};

/* Endpoint, EP Bulk OUT, for Low-speed/Full-speed */
struct usb_endpoint_descriptor verify_bulk_out_ep_FS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_BULK_OUT_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize   = 64,
	.bInterval        = 0x00,
};

/* Endpoint, EP Bulk IN, for High-speed */
struct usb_endpoint_descriptor verify_bulk_in_ep_HS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_BULK_IN_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize   = 512,
	.bInterval        = 0x00,
};

/* Endpoint, EP Bulk OUT, for High-speed */
struct usb_endpoint_descriptor verify_bulk_out_ep_HS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_BULK_OUT_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize   = 512,
	.bInterval        = 0x00,
};

/* Endpoint, EP ISO IN, for Low-speed/Full-speed */
struct usb_endpoint_descriptor verify_iso_in_ep_FS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_ISO_IN_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize   = 512,
	.bInterval        = 0x01,

};
/* Endpoint, EP ISO OUT, for Low-speed/Full-speed */
struct usb_endpoint_descriptor verify_iso_out_ep_FS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_ISO_OUT_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize   = 512,
	.bInterval        = 0x01,
};

/* Endpoint, EP ISO IN, for High-speed */
struct usb_endpoint_descriptor verify_iso_in_ep_HS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_ISO_IN_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize   = 512,
	.bInterval        = 0x01,
};

/* Endpoint, EP ISO OUT, for High-speed */
struct usb_endpoint_descriptor verify_iso_out_ep_HS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_ISO_OUT_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize   = 512,
	.bInterval        = 0x01,
};

/* Endpoint, EP INT IN, for Low-speed/Full-speed */
struct usb_endpoint_descriptor verify_int_in_ep_FS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_INT_IN_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize   = 64,
	.bInterval        = 0x01,

};
/* Endpoint, EP INT OUT, for Low-speed/Full-speed */
struct usb_endpoint_descriptor verify_int_out_ep_FS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_INT_OUT_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize   = 64,
	.bInterval        = 0x01,
};

/* Endpoint, EP INT IN, for High-speed */
struct usb_endpoint_descriptor verify_int_in_ep_HS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_INT_IN_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize   = 512,
	.bInterval        = 0x02,
};

/* Endpoint, EP INT OUT, for High-speed */
struct usb_endpoint_descriptor verify_int_out_ep_HS = {
	.bLength          = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType  = USB_DT_ENDPOINT,
	.bEndpointAddress = USBD_VERIFY_INT_OUT_EP_ADDRESS,
	.bmAttributes     = USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize   = 512,
	.bInterval        = 0x02,
};

/* HW only support 5 endpoints: 0-CTRL£¬1-IN, 2-OUT, 3-IN, 4-OUT and it only support one Periodic IN EP */
struct usb_descriptor_header *verify_descriptors_FS[] = {
	/* data interface has no altsetting */
	(struct usb_descriptor_header *) &verify_intf_desc,
	(struct usb_descriptor_header *) &verify_bulk_in_ep_FS,
	(struct usb_descriptor_header *) &verify_bulk_out_ep_FS,
#if USBD_ISO_VERIFY
	(struct usb_descriptor_header *) &verify_iso_in_ep_FS,
	(struct usb_descriptor_header *) &verify_iso_out_ep_FS,
#else
	(struct usb_descriptor_header *) &verify_int_in_ep_FS,
	(struct usb_descriptor_header *) &verify_int_out_ep_FS,
#endif
	NULL,
};

struct usb_descriptor_header *verify_descriptors_HS[] = {
	/* data interface has no altsetting */
	(struct usb_descriptor_header *) &verify_intf_desc,
	(struct usb_descriptor_header *) &verify_bulk_in_ep_HS,
	(struct usb_descriptor_header *) &verify_bulk_out_ep_HS,
#if USBD_ISO_VERIFY
	(struct usb_descriptor_header *) &verify_iso_in_ep_HS,
	(struct usb_descriptor_header *) &verify_iso_out_ep_HS,
#else
	(struct usb_descriptor_header *) &verify_int_in_ep_HS,
	(struct usb_descriptor_header *) &verify_int_out_ep_HS,
#endif
	NULL,
};
/**
  * @}
  */

typedef enum _USB_DATA_MODE_
{
	USBD_DATA_FIX = 0,
	USBD_DATA_SEQ = 1,
	USBD_DATA_RND = 2
} USB_DATA_MODE, *PUSB_DATA_MODE;

struct usb_verify_device_t {
	struct usb_gadget   *gadget;
	struct usb_ep       *ep0;
	struct usb_request  *req0;
	
	struct usb_ep       *bulk_in_ep;
	struct usb_ep       *bulk_out_ep;
	struct usb_request *bulk_in_req;
	struct usb_request *bulk_out_req;
	u8 *bulk_in_buf;
	u8 *bulk_out_buf;
	u32 bulk_buf_size;
	
	struct usb_ep       *iso_in_ep;
	struct usb_ep       *iso_out_ep;
	struct usb_iso_request *iso_in_req;
	struct usb_iso_request *iso_out_req;
	u8 *iso_in_req_buf[2];
	u8 *iso_out_req_buf[2];
	u32 iso_buf_size;

	struct usb_ep       *int_in_ep;
	struct usb_ep       *int_out_ep;
	struct usb_request *int_in_req;
	struct usb_request *int_out_req;
	u8 *int_in_buf;
	u8 *int_out_buf;
	u32 int_buf_size;

	u8 test_mode;
	u8 long_run_flag;
	void(* alt_cb)(void);
	void(* ctrl_cb)(const struct usb_control_request *ctrl);
};
#endif	//__USB_VERIFY_DEVICE_H