/*
 *  xModem protocol
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */


#include "xmodem.h"
#if defined(CONFIG_PLATFORM_8711B)
#include "rtl8710b.h"
#elif defined(CONFIG_PLATFORM_8721D)
#include "rtl8721d.h"
#else
#include "rtl8195a.h"
#endif
//---------------------------------

#if defined(CONFIG_PLATFORM_8711B)||defined(CONFIG_PLATFORM_8721D)
#define  FWU_TEXT_SECTION
#define  DBG_MISC_WARN		DBG_8195A
#define  DBG_MISC_ERR		DBG_8195A
#define  COMMPORT_GET_T		_COMMPORT_GET_T 
#define  COMMPORT_CLEAN_RX	_COMMPORT_CLEAN_RX
#define  xModemInquiry	        _xModemInquiry
#define  xModemGetFirst	        _xModemGetFirst
#define  xModemGetOthers        _xModemGetOthers
#define  xModemRxFrame	        _xModemRxFrame
#define  xModemRxBuffer         _xModemRxBuffer
#endif
extern void xDelayUs(u32 us);

s16 xModemStart(XMODEM_CTRL *pXMCtrl, char *FrameBuf, RxFrameHandler_t RxFrameHdl);
s16 xModemEnd(XMODEM_CTRL *pXMCtrl);
s16 xModemInquiry(XMODEM_CTRL *pXMCtrl, u8 code);
s16 xModemCancel(XMODEM_CTRL *pXMCtrl);
void xModemGetFirst(XMODEM_CTRL *pXMCtrl);
void xModemGetOthers(XMODEM_CTRL *pXMCtrl);
s16 xModemRxBlock(XMODEM_CTRL *pXMCtrl);
s16 xModemTxBlock(XMODEM_CTRL *pXMCtrl, u8 *ptr, u16 count);
s16 xModemEOT(XMODEM_CTRL *pXMCtrl);
s16 xModemRxFrame(XMODEM_CTRL *pXMCtrl);
s32	xModemRxBuffer(XMODEM_CTRL *pXMCtrl, s32 MaxSize);

static __inline char 
COMMPORT_POLL(XMODEM_COM_PORT *pXComPort)
{
    return (pXComPort->poll());
}

static __inline char
COMMPORT_GET(XMODEM_COM_PORT *pXComPort)
{
    return (pXComPort->get());
}

static __inline void
COMMPORT_PUT(XMODEM_COM_PORT *pXComPort, char c)
{
    pXComPort->put(c);
}

FWU_TEXT_SECTION
char COMMPORT_GET_T(XMODEM_COM_PORT *pXComPort, char *pch, u32 timeout)
{
    do {
        if (COMMPORT_POLL(pXComPort)) {
            *pch = COMMPORT_GET(pXComPort);
            return 0;
        }
        xDelayUs(10);
        timeout--;
    } while (timeout != 0);

    DBG_MISC_ERR("xModem: Wait Next Char Timeout\r\n");
    return 1;
}

FWU_TEXT_SECTION
void COMMPORT_CLEAN_RX(XMODEM_COM_PORT *pXComPort)
{
    
    while (COMMPORT_POLL(pXComPort)) {
        COMMPORT_GET(pXComPort);
    }
}

//---------------------------
FWU_TEXT_SECTION
s16 xModemStart(XMODEM_CTRL *pXMCtrl, char *FrameBuf, RxFrameHandler_t RxFrameHdl)
{
	/* check PHY Driver */

	/* check X-Modem status */
	if (pXMCtrl->xMUsing == TRUE) {
		return XMODEM_NO_SESSION;
    }        

    pXMCtrl->pXFrameBuf = FrameBuf;
    pXMCtrl->RxFrameHandler = RxFrameHdl;
	/* initial COM port & buffer */

	/* mark X-Modem startup */
	pXMCtrl->xMUsing = TRUE;

	return XMODEM_OK;
}

FWU_TEXT_SECTION
s16 xModemEnd(XMODEM_CTRL *pXMCtrl)
{
	/* check X-Modem status */
	if (pXMCtrl->xMUsing == FALSE) {
		return XMODEM_NO_SESSION;
    }
	/* Stop COM port */
    
	/* mark X-Modem Stop */
	pXMCtrl->xMUsing = FALSE;

	return XMODEM_OK;
}


FWU_TEXT_SECTION
s16 xModemInquiry(XMODEM_CTRL *pXMCtrl, u8 code)
{
	if (code != ACK) {
        xDelayUs(1000);
    }

//	if (code == CAN) {
//		return TRUE;	/* MUST clear buffer */
//    }

	COMMPORT_PUT(&(pXMCtrl->ComPort), code);
	return TRUE;
}

FWU_TEXT_SECTION
s16 xModemCancel(XMODEM_CTRL *pXMCtrl)
{
    if (pXMCtrl->xMUsing == FALSE) {
    	return (XMODEM_NO_SESSION);
    }

	if (xModemInquiry(pXMCtrl, CAN) == -1) {
		return	XMODEM_NAK;
    } else {
		return XMODEM_OK;
    }
}

FWU_TEXT_SECTION
void xModemGetFirst(XMODEM_CTRL *pXMCtrl)
{
    char ch = 0;
    char tmp;

	if (COMMPORT_GET_T(&pXMCtrl->ComPort, &ch, WAIT_FRAME_TIME)) {
		pXMCtrl->rFinish = TRUE;
		pXMCtrl->rStatus =  XMODEM_TIMEOUT;
        DBG_MISC_WARN("xModem: Wait Next Frame Start Timeout\r\n");
		return ;
	}

	ch = ch & 0xff;
	switch(ch)
	{
		case CAN :
            DBG_MISC_WARN("xModem: Get Cancel\r\n");
    		pXMCtrl->rFinish = TRUE;
    		pXMCtrl->rStatus = XMODEM_CANCEL;
    		break;
		case EOT :
			pXMCtrl->rFinish = TRUE;
			xModemInquiry(pXMCtrl, ACK);
			pXMCtrl->rStatus = XMODEM_COMPLETE;
            DBG_MISC_WARN("xModem: End of Transmit\r\n");
			break;
		case SOH :
			pXMCtrl->expected =  FRAME_SIZE - 4;
			break;
		case STX :
			pXMCtrl->expected =  FRAME_SIZE_1K - 4;
			break;			
		case ESC :
            DBG_MISC_WARN("xModem: Aborted!\r\n");
			pXMCtrl->rFinish = TRUE;
			pXMCtrl->rStatus = XMODEM_ABORT;
			break;
		default :
            while (COMMPORT_GET_T(&pXMCtrl->ComPort, &tmp, WAIT_CHAR_TIME) == 0);
			xModemInquiry(pXMCtrl, NAK);
			break;
	}
	
}

FWU_TEXT_SECTION
void xModemGetOthers(XMODEM_CTRL *pXMCtrl)
{
    char *ptr = pXMCtrl->pXFrameBuf;
    XMODEM_COM_PORT *pComPort = &(pXMCtrl->ComPort);
    u8 frame_no;
    u8 frame_no_bar;
    u8 is_duplicate;
    char uch = 0;
    char uchk;
    u16	summation;
    u32	j;

	if (COMMPORT_GET_T(pComPort, (char *)(&frame_no), WAIT_CHAR_TIME)) {
		pXMCtrl->rFinish = TRUE;
		pXMCtrl->rStatus = XMODEM_TIMEOUT;
//        DBG_MISC_WARN("xModemGetOthers Timeout #1\r\n");
		return ;
	}

    /* check invert number */
    if (COMMPORT_GET_T(pComPort, (char *)(&frame_no_bar), WAIT_CHAR_TIME)) {
        pXMCtrl->rFinish = TRUE;
        pXMCtrl->rStatus = XMODEM_TIMEOUT;
//        DBG_MISC_WARN("xModemGetOthers Timeout #2\r\n");
        return ;
    }

    pXMCtrl->rStatus = XMODEM_OK;

    if ((((~frame_no)&0xff)^frame_no_bar) != 0) {
        DBG_MISC_WARN("Incorrect FrameNo %x %x\r\n", frame_no, frame_no_bar);
        pXMCtrl->rStatus = XMODEM_NAK;
    }

    is_duplicate = 0;
    if (frame_no == pXMCtrl->previousFrame) {
        // re-transmit packets, just send ACK and ignore it        
        is_duplicate = 1;
    } 
    else if (frame_no != pXMCtrl->currentFrame) {
        pXMCtrl->rStatus = XMODEM_NAK;
        DBG_MISC_WARN("Wrong FrameNo: expect for 0x%x but got 0x%x\r\n", pXMCtrl->currentFrame, frame_no);    
    }

	/* get data */
	summation = 0;
    for (j=0; j<pXMCtrl->expected; j++) {
		if (COMMPORT_GET_T(pComPort, (char*)(ptr+j), WAIT_CHAR_TIME)) {
			pXMCtrl->rFinish = TRUE;
			pXMCtrl->rStatus = XMODEM_TIMEOUT;
//                DBG_MISC_WARN("xModemGetOthers Timeout #3\r\n");
			return ;
		}
		summation += *(ptr+j);
	}

	/* CRC check */
	if (COMMPORT_GET_T(pComPort, &uch, WAIT_CHAR_TIME)) {
		pXMCtrl->rFinish = TRUE;
		pXMCtrl->rStatus = XMODEM_TIMEOUT;
//            DBG_MISC_WARN("xModemGetOthers Timeout #4\r\n");
		return ;
	}

	uchk = summation & 0xff;
	if (uchk != uch) {
		pXMCtrl->rStatus = XMODEM_NAK;
        DBG_MISC_WARN("Check-Sum Err(%x %x)!\r\n", uch, uchk);
    } else {
        if (!is_duplicate) {
            pXMCtrl->total_frame++;
//            pXMCtrl->rx_len += pXMCtrl->RxFrameHandler((char*)ptr, pXMCtrl->total_frame, pXMCtrl->expected);
        }

        // somehow the xmodem sender "TeraTerm" will send extra junk bytes if we start the xmodem
        // receiver before the xmodem sender start. So, we need to drop those extra data
        COMMPORT_CLEAN_RX(pComPort);
    }

	if (pXMCtrl->rStatus == XMODEM_OK) {
		pXMCtrl->rFinish = TRUE;
		xModemInquiry(pXMCtrl, ACK);
       		if (is_duplicate) {
			// duplicated frame
			pXMCtrl->rStatus = XMODEM_NAK;
		} else {
			pXMCtrl->rx_len += pXMCtrl->RxFrameHandler((char*)ptr, pXMCtrl->total_frame, pXMCtrl->expected);
		}
	} else {
		xModemInquiry(pXMCtrl, NAK);
	}
}

FWU_TEXT_SECTION
s16 xModemRxBlock(XMODEM_CTRL *pXMCtrl)
{
	pXMCtrl->expected = 1;
	pXMCtrl->rFinish = FALSE;
	while (pXMCtrl->rFinish == FALSE) {
		if (pXMCtrl->expected == 1) {
			xModemGetFirst(pXMCtrl);
		} else {
			xModemGetOthers(pXMCtrl);
		}
	}
	return pXMCtrl->rStatus;
}

s16 xModemTxBlock(XMODEM_CTRL *pXMCtrl, u8 *ptr, u16 count)
{
    u16	i,_count;

	for (i=0;i<RETRY_COUNT;i++) {
		_count = count;
		while (_count > 0) {
			COMMPORT_PUT(&(pXMCtrl->ComPort), *ptr);
			_count--;
			ptr++;
		}		
	}
	return TRUE;
}

s16 xModemEOT(XMODEM_CTRL *pXMCtrl)
{
    u8 buffer;

	buffer = EOT;
	
	/* clean Input & Output Port */

	return (xModemTxBlock(pXMCtrl, &buffer,1));
}


FWU_TEXT_SECTION
s16 xModemRxFrame(XMODEM_CTRL *pXMCtrl)
{
    s16 status;

	status = xModemRxBlock(pXMCtrl);
	if (status == XMODEM_OK) {
		pXMCtrl->previousFrame = pXMCtrl->currentFrame;
		pXMCtrl->currentFrame = (pXMCtrl->currentFrame+1) & 0xff;
	}

	return status;
}

//#define _HAVE_TIMEOUT

FWU_TEXT_SECTION
s32	xModemRxBuffer(XMODEM_CTRL *pXMCtrl, s32 MaxSize)
{
    u16 retry;
    s16 status;
    u32	rxlen;
    u32	_timeout;
    u8	finished,tooLarge;


RxB_again:
	/* MUST clear PHY buffer .... */
	pXMCtrl->currentFrame = 1;
	pXMCtrl->previousFrame = 0;	/* previous frame number */
    pXMCtrl->total_frame = 0;
    pXMCtrl->rx_len = 0;
	tooLarge = FALSE;
	rxlen = 0;
	/* send NAK to client */
	retry = 0;

#ifdef	_HAVE_TIMEOUT
	while (retry < RETRY_COUNT)
#else
	while (1)
#endif
	{
        COMMPORT_CLEAN_RX(&(pXMCtrl->ComPort));
		xModemInquiry(pXMCtrl, NAK); // initial the transfer with check-sum checking

		/* delay time */
		_timeout =  100000;
		while (_timeout > 0) {
			_timeout--;
			if (COMMPORT_POLL(&(pXMCtrl->ComPort))) {
			    break;
            }
            xDelayUs(10);
		}

		if (_timeout > 0) {
			break;
		}
	
		retry++;
	}

#ifdef	_HAVE_TIMEOUT

	/* TimeOut or not */
	if (retry == RETRY_COUNT) {
		return 0;
	}

#endif

	finished = FALSE;
    retry = 0;

	while (finished == FALSE) {
		status = xModemRxFrame(pXMCtrl);
		
		// If rx any non-SOH character
		if ((status == XMODEM_TIMEOUT) && (rxlen == 0)) {
			goto RxB_again;
		}
	
		switch (status)	{
			case XMODEM_OK :
                retry = 0;
				rxlen += pXMCtrl->expected;
				if (rxlen > MaxSize)
				{
				    // Received length Over the maximum available transfer length
				    // cancel(stop) the transfer
					rxlen -= pXMCtrl->expected;
					tooLarge = TRUE;
					finished = TRUE;
					xModemInquiry(pXMCtrl, CAN);
				}
				break;

			case XMODEM_TIMEOUT :
                retry++;
                if (retry >= 10) {
                    // Continuous 10 times RX Frame timeout 
                    // Cancel the transfer
                    xModemCancel(pXMCtrl);
                    finished = TRUE;
                    rxlen = 0;
                } else {
                    // Try again
                    COMMPORT_CLEAN_RX(&(pXMCtrl->ComPort));
                    xModemInquiry(pXMCtrl, NAK);
                }
                break;
                
			case XMODEM_COMPLETE :
				status = XMODEM_OK;
				finished = TRUE;
				break;
                
			case XMODEM_ABORT :
				status = XMODEM_ABORT;
				rxlen = 0;
                
			default :
    			xModemCancel(pXMCtrl);
    			finished = TRUE;
    			rxlen = 0;
    			break;
		}
	} 

	if (tooLarge == TRUE) {
		return MaxSize+1;
	} else {
//		return rxlen;
        return pXMCtrl->rx_len;
	}
}

