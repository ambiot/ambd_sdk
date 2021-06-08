/********************************************************************************
 * Copyright (c) 2014, Realtek Semiconductor Corp.
 * All rights reserved.
 *
 * This module is a confidential and proprietary property of RealTek and
 * possession or use of this module requires written permission of RealTek.
 *******************************************************************************
 */
#if defined(CONFIG_PLATFORM_8711B)

#include "xmodem.h"
#include <platform/platform_stdlib.h>
#include "flash_api.h"
#include "device_lock.h"

extern char xmodem_uart_readable(void);
extern char xmodem_uart_getc(void);
extern void xmodem_uart_putc(char c);

char xMFrameBuf[XM_BUFFER_SIZE];
XMODEM_CTRL _xMCtrl;

extern const update_file_img_id OtaImgId[2];
static update_ota_target_hdr OtaTargetHdr;
static u32 fw_img2_addr;
static u32 flash_wr_err_cnt;
static int SigCnt;
static u8 signature[9];
static update_dw_info DownloadInfo[2];
static int ImageCnt;
static u32 OtaFg;
static s32 RemainBytes;
static u32 i;
static u32 TempLen;
static s32 OtaImgSize;
static int size;

void xDelayUs(u32 us)
{
	DelayUs(us);
}

void xmodem_uart_func_hook(XMODEM_COM_PORT *pXComPort)
{
	pXComPort->poll = (char(*)(void))xmodem_uart_readable;
	pXComPort->put = xmodem_uart_putc;
	pXComPort->get = (char(*)(void))xmodem_uart_getc;
}

s32
xModem_Init_UART_Port(u8 uart_idx, u8 pin_mux, u32 baud_rate)
{
	xmodem_uart_init(uart_idx, pin_mux, baud_rate);
	xmodem_uart_func_hook(&(_xMCtrl.ComPort));
	return 0;
}

VOID
xModem_DeInit_UART_Port(u8 uart_idx)
{
	xmodem_uart_deinit();
}

int GetDownloadInfo(u32 addr, update_ota_target_hdr * pOtaTgtHdr)
{
	u32 ImageCnt;
	/*init download information buffer*/
	memset((u8 *)&DownloadInfo, 0, 2*sizeof(update_dw_info));

	/*arrange OTA/RDP image download information*/
	if(pOtaTgtHdr->RdpStatus == ENABLE) {
		ImageCnt = 2;
		if(pOtaTgtHdr->FileImgHdr.Offset < pOtaTgtHdr->FileRdpHdr.Offset) {
			DownloadInfo[0].ImgId = OTA_IMAG;
			/* get OTA image and Write New Image to flash, skip the signature, 
			not write signature first for power down protection*/
			DownloadInfo[0].FlashAddr = addr -SPI_FLASH_BASE + 8;
			DownloadInfo[0].ImageLen = pOtaTgtHdr->FileImgHdr.ImgLen - 8;/*skip the signature*/
			DownloadInfo[0].ImgOffset = pOtaTgtHdr->FileImgHdr.Offset;
			DownloadInfo[1].ImgId = RDP_IMAG;
			DownloadInfo[1].FlashAddr = RDP_FLASH_ADDR - SPI_FLASH_BASE;
			DownloadInfo[1].ImageLen = pOtaTgtHdr->FileRdpHdr.ImgLen;
			DownloadInfo[1].ImgOffset = pOtaTgtHdr->FileRdpHdr.Offset;
		} else {
			DownloadInfo[0].ImgId = RDP_IMAG;
			DownloadInfo[0].FlashAddr = RDP_FLASH_ADDR - SPI_FLASH_BASE;
			DownloadInfo[0].ImageLen = pOtaTgtHdr->FileRdpHdr.ImgLen;
			DownloadInfo[0].ImgOffset = pOtaTgtHdr->FileRdpHdr.Offset;	
			DownloadInfo[1].ImgId = OTA_IMAG;
			/* get OTA image and Write New Image to flash, skip the signature, 
			not write signature first for power down protection*/
			DownloadInfo[1].FlashAddr = addr -SPI_FLASH_BASE + 8;
			DownloadInfo[1].ImageLen = pOtaTgtHdr->FileImgHdr.ImgLen - 8;/*skip the signature*/
			DownloadInfo[1].ImgOffset = pOtaTgtHdr->FileImgHdr.Offset;
		}
	}else {
			ImageCnt = 1;
			DownloadInfo[0].ImgId = OTA_IMAG;
			/* get OTA image and Write New Image to flash, skip the signature, 
			not write signature first for power down protection*/
			DownloadInfo[0].FlashAddr = addr -SPI_FLASH_BASE + 8;
			DownloadInfo[0].ImageLen = pOtaTgtHdr->FileImgHdr.ImgLen - 8;/*skip the signature*/
			DownloadInfo[0].ImgOffset = pOtaTgtHdr->FileImgHdr.Offset;		
	}
	
	printf("\n\r OTA Image Address = %x\n", addr);
	if(pOtaTgtHdr->RdpStatus == ENABLE) {	
		printf("\n\r RDP Image Address = %x\n", RDP_FLASH_ADDR);
	}
	return ImageCnt;
}

u32 xModem_Frame_Img2(char *ptr,  unsigned int frame_num, unsigned int frame_size)
{
	uint32_t uart_ota_target_index = OTA_INDEX_2;
	u32 fw_img2_size;
	u8 *pImgId = NULL;
	u32 IncFg = 0;
	flash_t flash;
	int read_bytes;
	int read_bytes_buf;
	u32 TempCnt = 0;	
	u32 TailCnt = 0;	
	u8 * buf = NULL;
	
	printf("\rframe_num: %d frame_size: %d", frame_num, frame_size);
	if (flash_wr_err_cnt)
		return 0;

	if (frame_num == 1) {
		/* check OTA index we should update */
		if (ota_get_cur_index() == OTA_INDEX_1) {
			uart_ota_target_index = OTA_INDEX_2;
			printf("\n\rOTA2 address space will be upgraded\n");
		} else {
			uart_ota_target_index = OTA_INDEX_1;
			printf("\n\rOTA1 address space will be upgraded\n");
		}		
		pImgId = (u8 *)&OtaImgId[uart_ota_target_index];
		
		/* -----step3: parse firmware file header and get the target OTA image header-----*/
		/* parse firmware file header and get the target OTA image header-----*/
		if(!get_ota_tartget_header((u8*)ptr, frame_size, &OtaTargetHdr, pImgId)){
			printf("\n\rget OTA header failed\n");
			flash_wr_err_cnt++;
			return 0;
		}

		/*get new image addr and check new address validity*/
		if(!get_ota_address(uart_ota_target_index, &fw_img2_addr, &OtaTargetHdr)){
			printf("\n\rget OTA address failed\n");
			flash_wr_err_cnt++;
			return 0;
		}

		/*get new image length from the firmware header*/
		fw_img2_size = OtaTargetHdr.FileImgHdr.ImgLen;

		/*-------------------step4: erase flash space for new firmware--------------*/
		/*erase flash space new OTA image */
		erase_ota_target_flash(fw_img2_addr, fw_img2_size);
		/*erase flash space for new RDP image*/
		if(OtaTargetHdr.RdpStatus == ENABLE) {
			device_mutex_lock(RT_DEV_LOCK_FLASH);
			flash_erase_sector(&flash, RDP_FLASH_ADDR - SPI_FLASH_BASE);
			device_mutex_unlock(RT_DEV_LOCK_FLASH);
			printf("\n\r RDP image size: %d", OtaTargetHdr.FileRdpHdr.ImgLen);
		}
		
		/*arrange OTA/RDP image download information*/
		ImageCnt = GetDownloadInfo(fw_img2_addr, &OtaTargetHdr);

		/*initialize the reveiving counter*/
		RemainBytes = DownloadInfo[0].ImageLen;
	}

	/*downloading parse the OTA and RDP image from the data stream sent by server*/
	while(i < ImageCnt){
		/*download the new firmware from server*/
		if(RemainBytes > 0){
			buf = (u8*)ptr;
			if(IncFg == 1) {
				IncFg = 0;
				read_bytes = read_bytes_buf;
			} else {
				read_bytes = frame_size;
				if(read_bytes <= 0){
					return 0; // it may not happen			
				}
				read_bytes_buf = read_bytes;
				TempLen += frame_size;
			}
			
			if(TempLen > DownloadInfo[i].ImgOffset) {
				if(!OtaFg) {   				/*reach the desired image, the first packet process*/
					OtaFg = 1;
					TempCnt = TempLen -DownloadInfo[i].ImgOffset;
					if(DownloadInfo[i].ImgId == OTA_IMAG) {
						if(TempCnt < 8) {
							SigCnt = TempCnt;
						} else {
							SigCnt = 8;
						}

						_memcpy(signature, buf + read_bytes -TempCnt, SigCnt);

						if((SigCnt < 8) || (TempCnt -8 == 0)) {
							return 0;
						}

						buf = buf + (read_bytes -TempCnt + 8);
						read_bytes = TempCnt -8;
					} else {
						buf = buf + read_bytes -TempCnt;
						read_bytes = TempCnt;
					}
				} else {					/*normal packet process*/
					if(DownloadInfo[i].ImgId == OTA_IMAG) {
						if(SigCnt < 8) {
							if(read_bytes < (8 -SigCnt)) {
								_memcpy(signature + SigCnt, buf, read_bytes);
								SigCnt += read_bytes;
								return 0;
							} else {
								_memcpy(signature + SigCnt, buf, (8 -SigCnt));
								buf = buf + (8 - SigCnt);
								read_bytes -= (8 - SigCnt) ;
								SigCnt = 8;
								if(!read_bytes) {
									return 0;
								}
							}
						}
					}
				}
				
				RemainBytes -= read_bytes;
				if(RemainBytes < 0) {
					read_bytes = read_bytes -(-RemainBytes);
				}
				device_mutex_lock(RT_DEV_LOCK_FLASH);
				if(flash_stream_write(&flash, DownloadInfo[i].FlashAddr + size, read_bytes, buf) < 0){
					printf("\n\r[%s] Write sector failed", __FUNCTION__);
					device_mutex_unlock(RT_DEV_LOCK_FLASH);
					flash_wr_err_cnt++;
					return 0;
				}
				device_mutex_unlock(RT_DEV_LOCK_FLASH);
				size += read_bytes;
			}else{
				return 0 + TailCnt; /* not reach desired image */
			}

		}else{
			return 0; /* no desired image */
		}
		
		if(RemainBytes <= 0){		
			/*if complete downloading OTA image, acquire the image size*/
			if(DownloadInfo[i].ImgId == OTA_IMAG) {
				OtaImgSize = size;
			}
			TailCnt = read_bytes;
			/*update flag status*/
			size = 0;
			OtaFg = 0;
			IncFg = 1;
			/*the next image length*/
			if(++i < ImageCnt)
				RemainBytes = DownloadInfo[i].ImageLen;
		}else{
			return read_bytes + TailCnt;
		}
	}
	return 0 + TailCnt;/* no desired image */
}

int
WriteImg2Sign(
    u32 wr_len
)
{
	int ret = 1 ;
	uint32_t uart_ota_target_index = OTA_INDEX_2;
	flash_t flash;
	if(fw_img2_addr == OTA1_ADDR)
		uart_ota_target_index = OTA_INDEX_1;
	else
		uart_ota_target_index = OTA_INDEX_2;
	
	if((OtaImgSize <= 0) || (OtaImgSize != (OtaTargetHdr.FileImgHdr.ImgLen - 8))) {
		printf("\n\rdownload new firmware failed\n");
		return 1;
	}
	printf("\n\rwrite size = %d", OtaImgSize);
	printf("\n\rsignature = %s",signature);
	 /*-------------step6: verify checksum and update signature-----------------*/
	if(verify_ota_checksum(fw_img2_addr, OtaImgSize, signature, &OtaTargetHdr)){
		if(!change_ota_signature(fw_img2_addr, signature, uart_ota_target_index)) {
			printf("\n%s: change signature failed\n", __FUNCTION__);
			return 1;
		}
		ret = 0;
	} else {
		/*if checksum error, clear the signature zone which has been 
		written in flash in case of boot from the wrong firmware*/
		#if 1
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_erase_sector(&flash, fw_img2_addr - SPI_FLASH_BASE);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
		#endif
	}
	return ret;
}

void OTU_FW_Update(u8 uart_idx, u8 pin_mux, u32 baud_rate)
{
	u32 wr_len = 0;
	int ret = 1;
	memset(signature, 0, sizeof(signature));
	memset(&OtaTargetHdr, 0, sizeof(OtaTargetHdr));
	memset((u8 *)&DownloadInfo, 0, 2*sizeof(update_dw_info));
	fw_img2_addr = 0;
	flash_wr_err_cnt = 0;
	SigCnt = 0;
	ImageCnt = 0;
	OtaFg = 0;
	RemainBytes = 0;
	i = 0;
	TempLen = 0;
	OtaImgSize = 0;
	size = 0;

	printf("FW Update Over UART%d, PinMux=%d, Baud=%d\r\n", uart_idx, pin_mux, baud_rate);
    // Baud rate setting is used by UART_SetBaud,not serial_baud. Baud rate setting cannot be successful when LOW_POWER_RX_ENABLE
	if(uart_config[0].LOW_POWER_RX_ENABLE){
	  UART_LPRxpathSet(UART0_DEV, DISABLE);
	  UART_LPRxIPClockSet(UART0_DEV, UART_RX_CLK_XTAL_40M);
	}
	// Start to update the Image2 through xModem on peripheral device
	// We update the image via xModem on UART now, if we want to use other peripheral device
	// to update the image then we need to redefine the API
	if (xModem_Init_UART_Port(uart_idx, pin_mux, baud_rate) < 0) {
	    return;
	}
	xModemStart(&_xMCtrl, xMFrameBuf, xModem_Frame_Img2);
	wr_len = _xModemRxBuffer(&_xMCtrl, (2*1024*1024));
	xModemEnd(&_xMCtrl);
	xModem_DeInit_UART_Port(uart_idx);

	printf("FW Update Image2 @ 0x%x\r\n", fw_img2_addr);

	if ((wr_len > 0) && (flash_wr_err_cnt == 0)){
		ret = WriteImg2Sign(wr_len);
	}
	else
		printf("\n\rerror in writen to flash");

	if(!ret)
		printf("\n\rOTU_FW_Update Success");
	
	if(uart_config[0].LOW_POWER_RX_ENABLE){
	  UART_LPRxpathSet(UART0_DEV, ENABLE);
	  UART_LPRxIPClockSet(UART0_DEV, UART_RX_CLK_OSC_8M);
	}
	
	printf("\n\rOTU_FW_Update Done, Write Len=%d\n", wr_len);
}

#elif defined(CONFIG_PLATFORM_8721D)

#include "xmodem.h"
#include <platform/platform_stdlib.h>
#include "flash_api.h"
#include "device_lock.h"
#include "ameba_soc.h"
#include "xmodem_uart_rom.h"
#include "xmodem_rom.h"

UART_TypeDef* xmodem_uartx_patch;

char xMFrameBuf[XM_BUFFER_SIZE];
XMODEM_CTRL _xMCtrl;

static update_ota_target_hdr OtaTargetHdr;
static u32 fw_img2_addr;
static u32 flash_wr_err_cnt;
static int SigCnt;
static u8 signature[9];
static update_dw_info DownloadInfo[2];
static int ImageCnt;
static u32 OtaFg;
static s32 RemainBytes;
static u32 i;
static u32 TempLen;
static s32 OtaImgSize;
static int size;

static void xmodem_uart_init_patch(UNUSED_WARN_DIS u8 uart_idx, u32 baud_rate)
{
	//Baud rate setting cannot be successful when LOW_POWER
	RCC_PeriphClockSource_UART(xmodem_uartx_patch, UART_RX_CLK_XTAL_40M);
	
	UART_InitTypeDef UART_InitStruct;
	UART_StructInit(&UART_InitStruct);

	UART_InitStruct.DmaModeCtrl = DISABLE;
	UART_InitStruct.WordLen = RUART_WLS_8BITS;
	UART_InitStruct.StopBit = RUART_STOP_BIT_1;     // word length select: 0 -> no stop bit, 1 -> 1 stop bit
	UART_InitStruct.Parity = DISABLE;      // parity check enable
	UART_InitStruct.ParityType = RUART_ODD_PARITY;
	UART_InitStruct.StickParity = DISABLE;
	UART_InitStruct.FlowControl = DISABLE;
	UART_InitStruct.RxFifoTrigLevel = UART_RX_FIFOTRIG_LEVEL_1BYTES;
	UART_InitStruct.RxErReportCtrl = UART_RX_EEROR_REPORT_ENABLE;

	/* wait Log_UART tx done, otherwise redundant data will be tx when re-initialize Log_UART */
	UART_WaitBusy(xmodem_uartx_patch, 5);

	/* re-initialize Log_UART */
	UART_Init(xmodem_uartx_patch, &UART_InitStruct);
	UART_SetBaud(xmodem_uartx_patch, baud_rate);
	UART_INTConfig(xmodem_uartx_patch, RUART_IER_ERBI | RUART_IER_ELSI, DISABLE);
	UART_RxCmd(xmodem_uartx_patch, ENABLE);
}

static char xmodem_uart_readable_patch(void) 
{
	return UART_Readable(xmodem_uartx_patch);
}

static char xmodem_uart_getc_patch(void) 
{
	u8 Val = 0;
	UART_CharGet(xmodem_uartx_patch, &Val);
	
	return Val;
}

static void xmodem_uart_putc_patch(char c) 
{
	UART_CharPut(xmodem_uartx_patch, c);
}

static void  xmodem_uart_deinit_patch(void) 
{
	UART_DeInit(xmodem_uartx_patch);
}

void xDelayUs(u32 us)
{
	DelayUs(us);
}

void xmodem_uart_func_hook(XMODEM_COM_PORT *pXComPort)
{
	pXComPort->poll = (char(*)(void))xmodem_uart_readable_patch;
	pXComPort->put = xmodem_uart_putc_patch;
	pXComPort->get = (char(*)(void))xmodem_uart_getc_patch;
}

s32 xModem_Init_UART_Port(u8 uart_idx, u32 baud_rate)
{
	xmodem_uart_init_patch(uart_idx, baud_rate);
	xmodem_uart_func_hook(&(_xMCtrl.ComPort));
	return 0;
}

VOID xModem_DeInit_UART_Port(u8 uart_idx)
{
	xmodem_uart_deinit_patch();
}

int GetDownloadInfo(u32 addr, update_ota_target_hdr * pOtaTgtHdr)
{
	u32 ImageCnt;
	/*init download information buffer*/
	memset((u8 *)&DownloadInfo, 0, 2*sizeof(update_dw_info));

	/*arrange OTA image download information*/
	ImageCnt = 1;
	DownloadInfo[0].ImgId = OTA_IMAG;
	/* get OTA image and Write New Image to flash, skip the signature, 
	not write signature first for power down protection*/
	DownloadInfo[0].FlashAddr = addr -SPI_FLASH_BASE + 8;
	DownloadInfo[0].ImageLen = pOtaTgtHdr->FileImgHdr[0].ImgLen - 8;/*skip the signature*/
	DownloadInfo[0].ImgOffset = pOtaTgtHdr->FileImgHdr[0].Offset;		
	
	printf("\n\r OTA Image Address = %x\n", addr);

	return ImageCnt;
}

u32 xModem_Frame_Img2(char *ptr,  unsigned int frame_num, unsigned int frame_size)
{
	uint32_t uart_ota_target_index = OTA_INDEX_2;
	u32 fw_img2_size;
	u32 IncFg = 0;
	flash_t flash;
	int read_bytes;
	int read_bytes_buf;
	u32 TempCnt = 0;	
	u32 TailCnt = 0;	
	u8 * buf = NULL;
	
	printf("frame_num: %d frame_size: %d\n", frame_num, frame_size);
	if (flash_wr_err_cnt)
		return 0;

	if (frame_num == 1) {
		/* check OTA index we should update */
		if (ota_get_cur_index() == OTA_INDEX_1) {
			uart_ota_target_index = OTA_INDEX_2;
			printf("\n\rOTA2 address space will be upgraded\n");
		} else {
			uart_ota_target_index = OTA_INDEX_1;
			printf("\n\rOTA1 address space will be upgraded\n");
		}		
		
		/* -----step3: parse firmware file header and get the target OTA image header-----*/
		/* parse firmware file header and get the target OTA image header-----*/
		if(!get_ota_tartget_header((u8*)ptr, frame_size, &OtaTargetHdr, uart_ota_target_index)){
			printf("\n\rget OTA header failed\n");
			flash_wr_err_cnt++;
			return 0;
		}

		fw_img2_addr = OtaTargetHdr.FileImgHdr->FlashAddr;

		/*get new image length from the firmware header*/
		fw_img2_size = OtaTargetHdr.FileImgHdr[0].ImgLen;

		/*-------------------step4: erase flash space for new firmware--------------*/
		/*erase flash space new OTA image */
		erase_ota_target_flash(fw_img2_addr, fw_img2_size);
		
		/*arrange OTA/RDP image download information*/
		ImageCnt = GetDownloadInfo(fw_img2_addr, &OtaTargetHdr);

		/*initialize the reveiving counter*/
		RemainBytes = DownloadInfo[0].ImageLen;
	}

	/*downloading parse the OTA from the data stream sent by server*/
	while(i < ImageCnt){
		/*download the new firmware from server*/
		if(RemainBytes > 0){
			buf = (u8*)ptr;
			if(IncFg == 1) {
				IncFg = 0;
				read_bytes = read_bytes_buf;
			} else {
				read_bytes = frame_size;
				if(read_bytes <= 0){
					return 0; // it may not happen			
				}
				read_bytes_buf = read_bytes;
				TempLen += frame_size;
			}
			
			if(TempLen > DownloadInfo[i].ImgOffset) {
				if(!OtaFg) {   				/*reach the desired image, the first packet process*/
					OtaFg = 1;
					TempCnt = TempLen -DownloadInfo[i].ImgOffset;
					if(DownloadInfo[i].ImgId == OTA_IMAG) {
						if(TempCnt < 8) {
							SigCnt = TempCnt;
						} else {
							SigCnt = 8;
						}

						_memcpy(signature, buf + read_bytes -TempCnt, SigCnt);
						_memcpy(&OtaTargetHdr.Sign[i][0], buf + read_bytes -TempCnt, SigCnt);

						if((SigCnt < 8) || (TempCnt -8 == 0)) {
							return 0;
						}

						buf = buf + (read_bytes -TempCnt + 8);
						read_bytes = TempCnt -8;
					} else {
						buf = buf + read_bytes -TempCnt;
						read_bytes = TempCnt;
					}
				} else {					/*normal packet process*/
					if(DownloadInfo[i].ImgId == OTA_IMAG) {
						if(SigCnt < 8) {
							if(read_bytes < (8 -SigCnt)) {
								_memcpy(signature + SigCnt, buf, read_bytes);
								SigCnt += read_bytes;
								return 0;
							} else {
								_memcpy(signature + SigCnt, buf, (8 -SigCnt));
								buf = buf + (8 - SigCnt);
								read_bytes -= (8 - SigCnt) ;
								SigCnt = 8;
								if(!read_bytes) {
									return 0;
								}
							}
						}
					}
				}
				
				RemainBytes -= read_bytes;
				if(RemainBytes < 0) {
					read_bytes = read_bytes -(-RemainBytes);
				}
				device_mutex_lock(RT_DEV_LOCK_FLASH);
				if(flash_stream_write(&flash, DownloadInfo[i].FlashAddr + size, read_bytes, buf) < 0){
					printf("\n\r[%s] Write sector failed", __FUNCTION__);
					device_mutex_unlock(RT_DEV_LOCK_FLASH);
					flash_wr_err_cnt++;
					return 0;
				}
				device_mutex_unlock(RT_DEV_LOCK_FLASH);
				size += read_bytes;
			}else{
				return 0 + TailCnt; /* not reach desired image */
			}

		}else{
			return 0; /* no desired image */
		}
		
		if(RemainBytes <= 0){		
			/*if complete downloading OTA image, acquire the image size*/
			if(DownloadInfo[i].ImgId == OTA_IMAG) {
				OtaImgSize = size;
			}
			TailCnt = read_bytes;
			/*update flag status*/
			size = 0;
			OtaFg = 0;
			IncFg = 1;
			/*the next image length*/
			if(++i < ImageCnt)
				RemainBytes = DownloadInfo[i].ImageLen;
		}else{
			return read_bytes + TailCnt;
		}
	}
	return 0 + TailCnt;/* no desired image */
}

int
WriteImg2Sign(
    u32 wr_len
)
{
	int ret = 1 ;
	uint32_t uart_ota_target_index = OTA_INDEX_2;
	flash_t flash;
	if(ota_get_cur_index() == OTA_INDEX_1){
		uart_ota_target_index = OTA_INDEX_2;
		printf("\n\rOTA1 address space will be upgraded");
	}else{
		uart_ota_target_index = OTA_INDEX_1;
		printf("\n\rOTA2 address space will be upgraded");
	}
	
	if((OtaImgSize <= 0) || (OtaImgSize != (OtaTargetHdr.FileImgHdr[0].ImgLen - 8))) {
		printf("\n\rdownload new firmware failed\n");
		return 1;
	}
	printf("\n\rwrite size = %d", OtaImgSize);
	printf("\n\rsignature = %s",signature);
	 /*-------------step6: verify checksum and update signature-----------------*/
	if(verify_ota_checksum(&OtaTargetHdr)){
		if(!change_ota_signature(&OtaTargetHdr,uart_ota_target_index)) {
			printf("\n%s: change signature failed\n", __FUNCTION__);
			return 1;
		}
		ret = 0;
	} else {
		/*if checksum error, clear the signature zone which has been 
		written in flash in case of boot from the wrong firmware*/
		#if 1
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_erase_sector(&flash, fw_img2_addr - SPI_FLASH_BASE);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
		#endif
	}
	return ret;
}

void OTU_FW_Update(u8 uart_idx, u8 uart_tx, u8 uart_rx, u32 baud_rate)
{
	u32 wr_len = 0;
	int ret = 1;
	memset(signature, 0, sizeof(signature));
	memset(&OtaTargetHdr, 0, sizeof(OtaTargetHdr));
	memset((u8 *)&DownloadInfo, 0, 2*sizeof(update_dw_info));
	fw_img2_addr = 0;
	flash_wr_err_cnt = 0;
	SigCnt = 0;
	ImageCnt = 0;
	OtaFg = 0;
	RemainBytes = 0;
	i = 0;
	TempLen = 0;
	OtaImgSize = 0;
	size = 0;

	Pinmux_Config(uart_tx, PINMUX_FUNCTION_UART);
	Pinmux_Config(uart_rx, PINMUX_FUNCTION_UART);
	PAD_PullCtrl(uart_tx, GPIO_PuPd_UP);   
	PAD_PullCtrl(uart_rx, GPIO_PuPd_UP);

	if(uart_idx == 0){
		xmodem_uartx_patch = UART0_DEV;
	}else if(uart_idx == 3){
		xmodem_uartx_patch = UART3_DEV;
	}else{
		DBG_8195A("ERROR: ONLY SUPPORT UART_IDX = 0/3 NOW\n");
	}
	
	printf("FW Update Over UART%d, Baud=%d\r\n", uart_idx, baud_rate);

	// Start to update the Image2 through xModem on peripheral device
	// We update the image via xModem on UART now, if we want to use other peripheral device
	// to update the image then we need to redefine the API
	if (xModem_Init_UART_Port(uart_idx, baud_rate) < 0) {
	  	return;
	}
	xModemStart(&_xMCtrl, xMFrameBuf, xModem_Frame_Img2);
	wr_len = _xModemRxBuffer(&_xMCtrl, (2*1024*1024));
	xModemEnd(&_xMCtrl);
	xModem_DeInit_UART_Port(uart_idx);

	printf("FW Update Image2 @ 0x%x\r\n", fw_img2_addr);

	if ((wr_len > 0) && (flash_wr_err_cnt == 0)){
		ret = WriteImg2Sign(wr_len);
	}
	else
		printf("\n\rerror in writen to flash");

	if(!ret)
		printf("\n\rOTU_FW_Update Success");
	
	printf("\n\rOTU_FW_Update Done, Write Len=%d\n", wr_len);
}

#else

#include "xmport_uart.h"
#include "xmport_loguart.h"
#include "rtl8195a.h"
#include "xmodem.h"
#include "xmport_uart.h"
#include "hal_spi_flash.h"
#include "rtl8195a_spi_flash.h"
#include <platform/platform_stdlib.h>

enum {
  XMODEM_UART_0     = 0,   
  XMODEM_UART_1     = 1,   
  XMODEM_UART_2     = 2,   
  XMODEM_LOG_UART   = 3   
};

FWU_DATA_SECTION char xMFrameBuf[XM_BUFFER_SIZE];
FWU_DATA_SECTION XMODEM_CTRL xMCtrl;

FWU_DATA_SECTION static u32 fw_img1_size;
FWU_DATA_SECTION static u32 fw_img2_size;
FWU_DATA_SECTION static u32 fw_img2_addr;
FWU_DATA_SECTION static u32 fw_img3_size;
FWU_DATA_SECTION static u32 fw_img3_addr;
FWU_DATA_SECTION static u32 flash_wr_offset;
FWU_DATA_SECTION static u32 flash_erased_addr;
FWU_DATA_SECTION static u8  start_with_img1;
FWU_DATA_SECTION static u32 flash_wr_err_cnt;

FWU_DATA_SECTION HAL_RUART_ADAPTER xmodem_uart_adp; // we can dynamic allocate memory for this object to save memory
static union { uint32_t u; unsigned char c[4]; } file_checksum;
static u32 updated_img2_size = 0;
static u32 default_img2_addr = 0;

FWU_RODATA_SECTION const char Img2Signature[8]="81958711";
extern u32 SpicCalibrationPattern[4];
extern const u8 ROM_IMG1_VALID_PATTEN[];
extern HAL_RUART_ADAPTER *pxmodem_uart_adp;

#ifdef CONFIG_GPIO_EN
extern HAL_GPIO_ADAPTER gBoot_Gpio_Adapter;
extern PHAL_GPIO_ADAPTER _pHAL_Gpio_Adapter;
#endif

void xDelayUs(u32 us)
{
	HalDelayUs(us);
}

extern BOOLEAN SpicFlashInitRtl8195A(u8 SpicBitMode);
_LONG_CALL_
extern VOID SpicWaitBusyDoneRtl8195A(VOID);
extern VOID SpicWaitWipDoneRefinedRtl8195A(SPIC_INIT_PARA SpicInitPara);


FWU_TEXT_SECTION void FWU_WriteWord(u32 Addr, u32 FData)
{
    SPIC_INIT_PARA SpicInitPara;
    
    HAL_WRITE32(SPI_FLASH_BASE, Addr, FData);
    // Wait spic busy done
    SpicWaitBusyDoneRtl8195A();
    // Wait flash busy done (wip=0)
    SpicWaitWipDoneRefinedRtl8195A(SpicInitPara);
}

FWU_TEXT_SECTION u32 xModem_MemCmp(const u32 *av, const u32 *bv, u32 len)
{
    const u32 *a = av;
    const u32 *b = (u32*)((u8*)bv+SPI_FLASH_BASE);
    u32 len4b = len >> 2;
    u32 i;
    
    for (i=0; i<len4b; i++) {
        if (a[i] != b[i]) {
            DBG_MISC_ERR("OTU: Flash write check error @ 0x%08x\r\n", (u32)(&b[i]));
            return ((u32)(&b[i])); 
        }
    }
    return 0;
}

FWU_TEXT_SECTION
u32 xModem_Frame_Img2(char *ptr,  unsigned int frame_num, unsigned int frame_size)    
{
    u32 address;
    u32 ImageIndex=0;
    u32 rx_len=0;
    u32 *chk_sr;
    u32 *chk_dr;
    u32 err_addr;
    
    if (frame_num == 1) {
        // Parse Image2 header
        memset(&file_checksum, 0, sizeof(file_checksum));
        flash_wr_offset = fw_img2_addr;
        fw_img2_size = rtk_le32_to_cpu(*((u32*)ptr)) + 0x14;
        if ((fw_img2_size & 0x03) != 0) {
            DBG_MISC_ERR("xModem_Frame_ImgAll Err#2: fw_img2_addr=0x%x fw_img2_size(%d) isn't 4-bytes aligned\r\n", fw_img2_addr, fw_img2_size);
            fw_img1_size = 0;
            fw_img2_size = 0;
            return rx_len;
        }
        
        if (fw_img2_size > (2*1024*1024)) {
            DBG_MISC_ERR("xModem_Frame_ImgAll Image2 to Big: fw_img2_addr=0x%x fw_img2_size(%d) \r\n", fw_img2_addr, fw_img2_size);
            fw_img1_size = 0;
            fw_img2_size = 0;
            return rx_len;
        }
        fw_img3_addr = fw_img2_addr + fw_img2_size;
        updated_img2_size = fw_img2_size;
        
        // erase Flash first
        address = fw_img2_addr & (~0xfff);     // 4k aligned, 4k is the page size of flash memory
        while ((address) < (fw_img2_addr+fw_img2_size)) {
            SpicSectorEraseFlashRtl8195A(SPI_FLASH_BASE + address);
            address += 0x1000;
        }
        flash_erased_addr = address;
    }

    if (fw_img2_size > 0) {
        // writing image2
        chk_sr = (u32*)((u8*)ptr+ImageIndex);
        chk_dr = (u32*)flash_wr_offset;
        while (ImageIndex < frame_size) {
            FWU_WriteWord(flash_wr_offset, (*((u32*)(ptr+ImageIndex))));
            ImageIndex += 4;
            flash_wr_offset += 4;
            rx_len += 4;
            fw_img2_size -= 4;
            if (fw_img2_size == 0) {
                // Image2 write done,
                break;
            }
        }
					        
        err_addr = xModem_MemCmp(chk_sr, chk_dr, (flash_wr_offset - (u32)chk_dr));
        if (err_addr) {
            flash_wr_err_cnt++;
        }
    }

    // checksum attached at file end
	file_checksum.c[0] = ptr[rx_len - 4];      
	file_checksum.c[1] = ptr[rx_len - 3];
	file_checksum.c[2] = ptr[rx_len - 2];
	file_checksum.c[3] = ptr[rx_len - 1];
	
    return rx_len;
}

FWU_TEXT_SECTION
s32
xModem_Init_UART_Port(u8 uart_idx, u8 pin_mux, u32 baud_rate)
{
    if (uart_idx <= XMODEM_UART_2) {
        // update firmware via generic UART
        pxmodem_uart_adp = &xmodem_uart_adp;    // we can use dynamic allocate to save memory
        xmodem_uart_init(uart_idx, pin_mux, baud_rate);
        xmodem_uart_func_hook(&(xMCtrl.ComPort));
    } else if(uart_idx == XMODEM_LOG_UART) {
        // update firmware via Log UART
        xmodem_loguart_init(baud_rate);
        xmodem_loguart_func_hook(&(xMCtrl.ComPort));    
    } else {
        // invalid UART port
		DBG_MISC_ERR("xModem_Init_UART_Port: Invaild UART port(%d)\n", uart_idx);
        return -1;
    }

    return 0;
}

FWU_TEXT_SECTION
VOID
xModem_DeInit_UART_Port(u8 uart_idx)
{
    if (uart_idx <= XMODEM_UART_2) {    
        xmodem_uart_deinit();
    } else if (uart_idx == XMODEM_LOG_UART) {
        xmodem_loguart_deinit();
    }
}

FWU_TEXT_SECTION
__weak s32
UpdatedImg2AddrValidate(
    u32 Image2Addr,
    u32 DefImage2Addr,
    u32 DefImage2Size
)
{
    if (Image2Addr == 0xffffffff) {
        // Upgraded Image2 isn't exist
        return 0;   // invalid address
    }

    if ((Image2Addr & 0xfff) != 0) {
        // Not 4K aligned
        return 0;   // invalid address
    }

    if (Image2Addr <= DefImage2Addr) {
        // Updated image2 address must bigger than the addrss of default image2
        return 0;   // invalid address
    }

    if (Image2Addr < (DefImage2Addr+DefImage2Size)) {
        // Updated image2 overlap with the default image2
        return 0;   // invalid address
    }

    return 1;   // this address is valid    
}

FWU_TEXT_SECTION
VOID
WriteImg2Sign(
    u32 Image2Addr
)
{
    u32 img2_sig[2];
    
    _memcpy((void*)img2_sig, (void*)Img2Signature, 8);    
    FWU_WriteWord((Image2Addr + 8), img2_sig[0]);
    FWU_WriteWord((Image2Addr + 12), img2_sig[1]);
    
    // set the default imag2's signature to old
    if(default_img2_addr != Image2Addr)
    {
        printf("set the signature of default img2 to old\n");
        FWU_WriteWord((default_img2_addr + 8), 0x35393130);
        FWU_WriteWord((default_img2_addr + 12), 0x31313738);
    }    

}

static void xmodem_write_ota_addr_to_system_data(u32 newImg2Addr)
{
    FWU_WriteWord(FLASH_SYSTEM_DATA_ADDR, newImg2Addr);
	return;
}

FWU_TEXT_SECTION
u32
SelectImg2ToUpdate(
    u32 *OldImg2Addr
)
{
    u32 DefImage2Addr=0xFFFFFFFF;  // the default Image2 addr.
    u32 SecImage2Addr=0xFFFFFFFF;  // the 2nd image2 addr.
    u32 ATSCAddr=0xFFFFFFFF; 
    u32 UpdImage2Addr;  // the addr of the image2 to be updated
    u32 DefImage2Len;
    
    *OldImg2Addr = 0;
    DefImage2Addr = (HAL_READ32(SPI_FLASH_BASE, 0x18)&0xFFFF) * 1024;
    if ((DefImage2Addr != 0) && ((DefImage2Addr < (16*1024*1024)))) {
        // Valid Default Image2 Addr: != 0 & located in 16M
        DefImage2Len = HAL_READ32(SPI_FLASH_BASE, DefImage2Addr);
        default_img2_addr = DefImage2Addr;

        // Get the pointer of the upgraded Image2
        SecImage2Addr = HAL_READ32(SPI_FLASH_BASE, FLASH_SYSTEM_DATA_ADDR);

        if (UpdatedImg2AddrValidate(SecImage2Addr, DefImage2Addr, DefImage2Len)) {
            UpdImage2Addr = SecImage2Addr; // Update the 2nd image2
        } else {
            // The upgraded image2 isn't exist or invalid so we can just update the default image2
            //UpdImage2Addr = DefImage2Addr; // Update the default image2
            UpdImage2Addr = 0x80000; // Update to a predefined address
       }
    } else {
        UpdImage2Addr = 0;
    }
    xmodem_write_ota_addr_to_system_data(UpdImage2Addr);

    return UpdImage2Addr;
}

static uint32_t xmodem_get_flash_checksum()
{
    uint32_t flash_checksum = 0;
    
    if(updated_img2_size == 0)
    {
        printf("img2 size is wrong\n");
        return 0;
    }

    for(int i = 0; i < updated_img2_size - 4; i++)
        flash_checksum += HAL_READ8(SPI_FLASH_BASE, fw_img2_addr + i); 
    	 
    return flash_checksum; 
}

FWU_TEXT_SECTION
void OTU_FW_Update(u8 uart_idx, u8 pin_mux, u32 baud_rate)
{
    u32 wr_len;
    u32 OldImage2Addr=0;  // the addr of the image2 will become old one
    SPIC_INIT_PARA SpicInitPara;

    fw_img1_size = 0;
    fw_img2_size = 0;
    fw_img2_addr = 0;
    fw_img3_size = 0;
    fw_img3_addr = 0;
    flash_wr_offset = 0;
    flash_erased_addr = 0;
    start_with_img1 = 0;;
    flash_wr_err_cnt = 0;
    u32 flash_checksum = 0;

    // Get the address of the image2 to be updated
	SPI_FLASH_PIN_FCTRL(ON);
	if (!SpicFlashInitRtl8195A(SpicOneBitMode)){
        SPI_FLASH_PIN_FCTRL(OFF);    
		DBG_MISC_ERR("OTU_FW_Update: SPI Init Fail!!!!!!\n");
        return;
	}
	SpicWaitWipDoneRefinedRtl8195A(SpicInitPara);

    printf("FW Update Over UART%d, PinMux=%d, Baud=%d\r\n", uart_idx, pin_mux, baud_rate);
    fw_img2_addr = SelectImg2ToUpdate(&OldImage2Addr);
    // Start to update the Image2 through xModem on peripheral device
    printf("FW Update Image2 @ 0x%x\r\n", fw_img2_addr);
    // We update the image via xModem on UART now, if we want to uase other peripheral device
    // to update the image then we need to redefine the API
    if (xModem_Init_UART_Port(uart_idx, pin_mux, baud_rate) < 0) {
        return;
    }

    xModemStart(&xMCtrl, xMFrameBuf, xModem_Frame_Img2);    // Support Image format: Image2 only
    wr_len = xModemRxBuffer(&xMCtrl, (2*1024*1024));
    xModemEnd(&xMCtrl);

    xModem_DeInit_UART_Port(uart_idx);
    
    // add checksum check
    
    flash_checksum = xmodem_get_flash_checksum();
    printf("flash_checksum: %x file_checksum: %x\n", flash_checksum, file_checksum.u);
    
    if(flash_checksum != file_checksum.u)
        printf("checksum error, please retry to update\n");
    else 
    {
        if ((wr_len > 0) && (flash_wr_err_cnt == 0)) {
            // Firmware update OK, now write the signature to active this image
            WriteImg2Sign(fw_img2_addr);        
        }
        else
            printf("error in writen to flash");
    }
        
    printf("OTU_FW_Update Done, Write Len=%d\n", wr_len);
    SPI_FLASH_PIN_FCTRL(OFF);    
}

#endif
