/******************************************************************************
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved. 
  *
******************************************************************************/

#ifndef _WIRELESS_H
#define _WIRELESS_H

/***************************** INCLUDES *****************************/


//#include <sockets.h>
#define IFNAMSIZ	16
#define	ARPHRD_ETHER	1	/* ethernet hardware format */


#define WIRELESS_EXT	22



/**************************** CONSTANTS ****************************/
typedef unsigned char __u8;
typedef char __s8;
typedef unsigned short __u16;
typedef short __s16;
typedef unsigned int __u32;
typedef int __s32;
typedef	unsigned long long __u64;
typedef	long long __i64;

#define	E2BIG		 7	/* Argument list too long */

#define ETH_ALEN	6		/* Octets in one ethernet addr	 */

/* Device private ioctl calls */

/*
 *	These 16 ioctls are available to devices via the do_ioctl() device
 *	vector. Each device should include this file and redefine these names
 *	as their own. Because these are device dependent it is a good idea
 *	_NOT_ to issue them to random objects and hope.
 *
 *	THESE IOCTLS ARE _DEPRECATED_ AND WILL DISAPPEAR IN 2.5.X -DaveM
 */
 
#define RTKIOCDEVPRIVATE	0x89F0	/* to 89FF */

/* -------------------------- IOCTL LIST -------------------------- */

/* Basic operations */

#define RTKIOCSIWFREQ	0x8B04		/* set channel/frequency (Hz) */
#define RTKIOCGIWFREQ	0x8B05		/* get channel/frequency (Hz) */
#define RTKIOCSIWMODE	0x8B06		/* set operation mode */
#define RTKIOCGIWMODE	0x8B07		/* get operation mode */
#define RTKIOCGIWSENS	0x8B09		/* get sensitivity (dBm) */


/* Access Point manipulation */
#define RTKIOCSIWAP		0x8B14		/* set access point MAC addresses */
#define RTKIOCGIWAP		0x8B15		/* get access point MAC addresses */
#define RTKIOCSIWSCAN	0x8B18		/* trigger scanning (list cells) */
#define RTKIOCGIWSCAN	0x8B19		/* get scanning results */

/* 802.11 specific support */
#define RTKIOCSIWESSID	0x8B1A		/* set ESSID (network name) */
#define RTKIOCGIWESSID	0x8B1B		/* get ESSID */
/* As the ESSID and NICKN are strings up to 32 bytes long, it doesn't fit
 * within the 'rtwreq' structure, so we need to use the 'data' member to
 * point to a string in user space, like it is done for RANGE... */


/* WPA : Generic IEEE 802.11 informatiom element (e.g., for WPA/RSN/WMM).
 * This ioctl uses struct rtw_point and data buffer that includes IE id and len
 * fields. More than one IE may be included in the request. Setting the generic
 * IE to empty buffer (len=0) removes the generic IE from the driver. Drivers
 * are allowed to generate their own WPA/RSN IEs, but in these cases, drivers
 * are required to report the used IE as a wireless event, e.g., when
 * associating with an AP. */
#define RTKIOCSIWGENIE		0x8B30		/* set generic IE */

/* WPA : Authentication mode parameters */
#define RTKIOCSIWAUTH		0x8B32		/* set authentication mode params */

/* WPA : Extended version of encoding configuration */
#define RTKIOCSIWENCODEEXT 	0x8B34		/* set encoding token & mode */
#define RTKIOCGIWENCODEEXT 	0x8B35		/* get encoding token & mode */

/* WPA2/WPA3 : Set PMKSA Cache Management Enable */
#define RTKIOCSIWPMKSA		0x8B36		/* PMKSA cache operation */

/* Send Mgnt Frame or Action Frame */
#define RTKIOCSIWMGNTSEND	0x8B37		/* Send Mgnt Frame or Action Frame */

/* Send WPS EAPOL Frame */
#define RTKIOCSIWEAPOLSEND	0x8B38		/* Send WPS EAPOL Frame */

/* Set MailBox Info */
#define RTKIOCSIMAILBOX		0x8B39		/* Set MailBox Info */

/* Set Management Frame Protection Support */
#define RTKIOCSIWMFP		0x8B3A		/* Set Management Frame Protection Support */

/* Set Finite cyclic groups id for SAE  */
#define RTKIOCSIWGRPID		0x8B3B		/* Set Finite cyclic groups id for SAE  */

/* Get rssiBCN */
#define RTKIOCGIWBCNSENS	0x8B40 		/* Get beacon average rssi */

/* -------------------- DEV PRIVATE IOCTL LIST -------------------- */

/* These 32 ioctl are wireless device private, for 16 commands.
 * Each driver is free to use them for whatever purpose it chooses,
 * however the driver *must* export the description of those ioctls
 * with SIOCGIWPRIV and *must* use arguments as defined below.
 * If you don't follow those rules, DaveM is going to hate you (reason :
 * it make mixed 32/64bit operation impossible).
 */
#define RTKIOCIWFIRSTPRIV	0x8BE0
#define RTKIOCIWLASTPRIV	0x8BFF

#define RTKIOCSIWPRIVADAPTIVITY		0x8BFB
#define RTKIOCGIWPRIVPASSPHRASE		0x8BFC
#define RTKIOCSIWPRIVCOUNTRY		0x8BFD
#define RTKIOCSIWPRIVAPESSID		0x8BFE
#define RTKIOCSIWPRIVPASSPHRASE		0x8BFF
/* Previously, we were using RTKIOCDEVPRIVATE, but we now have our
 * separate range because of collisions with other tools such as
 * 'mii-tool'.
 * We now have 32 commands, so a bit more space ;-).
 * Also, all 'even' commands are only usable by root and don't return the
 * content of ifr/iwr to user (but you are not obliged to use the set/get
 * convention, just use every other two command). More details in iwpriv.c.
 * And I repeat : you are not forced to use them with iwpriv, but you
 * must be compliant with it.
 */

/* ------------------------- IOCTL STUFF ------------------------- */

/* The first and the last (range) */
#define RTKIOCIWFIRST	0x8B00
#define RTKIOCIWLAST	RTKIOCIWLASTPRIV		/* 0x8BFF */

/* Odd : get (world access), even : set (root access) */
#define RTW_IS_SET(cmd)	(!((cmd) & 0x1))
#define RTW_IS_GET(cmd)	((cmd) & 0x1)

/* ----------------------- WIRELESS EVENTS ----------------------- */
/* Those are *NOT* ioctls, do not issue request on them !!! */
/* Most events use the same identifier as ioctl requests */

#define RTWEVCUSTOM		0x8C02		/* Driver specific ascii string */
#define RTWEVREGISTERED	0x8C03		/* Discovered a new node (AP mode) */
#define RTWEVEXPIRED	0x8C04		/* Expired a node (AP mode) */

/* Indicate Mgnt Frame and Action Frame to uplayer*/
#define RTWEVMGNTRECV	0x8C10		/* Indicate Mgnt Frame to uplayer */

/* ------------------------- PRIVATE INFO ------------------------- */
/*
 * The following is used with SIOCGIWPRIV. It allow a driver to define
 * the interface (name, type of data) for its private ioctl.
 * Privates ioctl are RTKIOCIWFIRSTPRIV -> RTKIOCIWLASTPRIV
 */
enum RTK_IW_PRIV_TYPE {
	RTW_PRIV_TYPE_NONE = 0x0000,		/* None type */
	RTW_PRIV_TYPE_BYTE = 0x1000,		/* Char as number */
	RTW_PRIV_TYPE_CHAR = 0x2000,		/* Char as character */
	RTW_PRIV_TYPE_INT  = 0x4000,		/* 32 bits int */
	RTW_PRIV_TYPE_FLOAT = 0x5000,		/* struct rtw_freq */
	RTW_PRIV_TYPE_ADDR = 0x6000,		/* struct sockaddr */
	RTW_PRIV_TYPE_MASK = 0x7000			/* Type of arguments */
};


#define RTW_PRIV_SIZE_FIXED	0x0800	/* Variable or fixed number of args */

#define RTW_PRIV_SIZE_MASK	0x07FF	/* Max number of those args */

/*
 * Note : if the number of args is fixed and the size < 16 octets,
 * instead of passing a pointer we will put args in the rtwreq struct...
 */

/* ----------------------- OTHER CONSTANTS ----------------------- */

/* Maximum size of the ESSID and NICKN strings */
#define RTW_ESSID_MAX_SIZE	32

/* Modes of operation */
enum RTK_IW_MODE {
	RTW_MODE_AUTO = 0,		/* Let the driver decides */
	RTW_MODE_ADHOC,			/* Single cell network */
	RTW_MODE_INFRA,			/* Multi cell network, roaming, ... */
	RTW_MODE_MASTER			/* Synchronisation master or Access Point */
};

/* Flags for encoding (along with the token) */
#define RTW_ENCODE_DISABLED	0x8000	/* Encoding disabled */
#define RTW_ENCODE_TEMP		0x0400  /* Temporary key */

/* Max number of char in custom event - use multiple of them if needed */
#define RTW_CUSTOM_MAX		256	/* In bytes */

/* RTKIOCSIWAUTH/RTKIOCGIWAUTH struct rtw_param flags */
#define RTW_AUTH_INDEX		0x0FFF

/* RTKIOCSIWAUTH/RTKIOCGIWAUTH parameters (0 .. 4095)
 * (RTW_AUTH_INDEX mask in struct rtw_param flags; this is the index of the
 * parameter that is being set/get to; value will be read/written to
 * struct rtw_param value field) */
enum RTK_IW_AUTH_PARAM {	
	RTW_AUTH_WPA_VERSION = 0,
	RTW_AUTH_CIPHER_PAIRWISE,
	RTW_AUTH_CIPHER_GROUP,
	RTW_AUTH_KEY_MGMT,
	RTW_AUTH_TKIP_COUNTERMEASURES,
	RTW_AUTH_DROP_UNENCRYPTED,
	RTW_AUTH_80211_AUTH_ALG,
	RTW_AUTH_WPA_ENABLED,
	RTW_AUTH_RX_UNENCRYPTED_EAPOL,
	RTW_AUTH_ROAMING_CONTROL,
	RTW_AUTH_PRIVACY_INVOKED
};


/* RTW_AUTH_80211_AUTH_ALG values (bit field) */
#define RTW_AUTH_ALG_OPEN_SYSTEM	0x00000001
#define RTW_AUTH_ALG_SHARED_KEY		0x00000002


/* RTKIOCSIWENCODEEXT definitions */
#define RTW_ENCODE_SEQ_MAX_SIZE	8
/* struct rtw_encode_ext ->alg */
enum RTW_IW_ENC_ALG {
	RTW_ENCODE_ALG_NONE = 0,
	RTW_ENCODE_ALG_WEP,
	RTW_ENCODE_ALG_TKIP,
	RTW_ENCODE_ALG_CCMP,
	RTW_ENCODE_ALG_PMK,
	RTW_ENCODE_ALG_AES_CMAC //IGTK
};


/* struct rtw_encode_ext ->ext_flags */
#define RTW_ENCODE_EXT_RX_SEQ_VALID	0x00000002
#define RTW_ENCODE_EXT_GROUP_KEY	0x00000004
#define RTW_ENCODE_EXT_SET_TX_KEY	0x00000008
			   

/****************************** TYPES ******************************/

/* --------------------------- SUBTYPES --------------------------- */

struct sockaddr_t {
  __u8 sa_len;
  __u8 sa_family;
  char sa_data[14];
};

/*
 *	Generic format for most parameters that fit in an int
 */
struct	rtw_param
{
  __s32		value;		/* The value of the parameter itself */
  __u8		fixed;		/* Hardware should not use auto select */
  __u8		disabled;	/* Disable the feature */
  __u16		flags;		/* Various specifc flags (if any) */
};

/*
 *	For all data larger than 16 octets, we need to use a
 *	pointer to memory allocated in user space.
 */
struct	rtw_point
{
  void		*pointer;	/* Pointer to the data  (in user space) */
  __u16		length;		/* number of fields or size in bytes */
  __u16		flags;		/* Optional params */
};

/*
 *	A frequency
 *	For numbers lower than 10^9, we encode the number in 'm' and
 *	set 'e' to 0
 *	For number greater than 10^9, we divide it by the lowest power
 *	of 10 to get 'm' lower than 10^9, with 'm'= f / (10^'e')...
 *	The power of 10 is in 'e', the result of the division is in 'm'.
 */
struct	rtw_freq
{
	__s32		m;		/* Mantissa */
	__s16		e;		/* Exponent */
	__u8		i;		/* List index (when in range struct) */
	__u8		flags;		/* Flags (fixed/auto) */
};

/* ------------------------- WPA SUPPORT ------------------------- */

/*
 *	Extended data structure for get/set encoding (this is used with
 *	RTKIOCSIWENCODEEXT/RTKIOCGIWENCODEEXT. struct rtw_point and IW_ENCODE_*
 *	flags are used in the same way as with SIOCSIWENCODE/SIOCGIWENCODE and
 *	only the data contents changes (key data -> this structure, including
 *	key data).
 *
 *	If the new key is the first group key, it will be set as the default
 *	TX key. Otherwise, default TX key index is only changed if
 *	RTW_ENCODE_EXT_SET_TX_KEY flag is set.
 *
 *	Key will be changed with RTKIOCSIWENCODEEXT in all cases except for
 *	special "change TX key index" operation which is indicated by setting
 *	key_len = 0 and ext_flags |= RTW_ENCODE_EXT_SET_TX_KEY.
 *
 *	tx_seq/rx_seq are only used when respective
 *	IW_ENCODE_EXT_{TX,RX}_SEQ_VALID flag is set in ext_flags. Normal
 *	TKIP/CCMP operation is to set RX seq with RTKIOCSIWENCODEEXT and start
 *	TX seq from zero whenever key is changed. RTKIOCGIWENCODEEXT is normally
 *	used only by an Authenticator (AP or an IBSS station) to get the
 *	current TX sequence number. Using TX_SEQ_VALID for RTKIOCSIWENCODEEXT and
 *	RX_SEQ_VALID for RTKIOCGIWENCODEEXT are optional, but can be useful for
 *	debugging/testing.
 */
struct	rtw_encode_ext
{
	__u32		ext_flags; /* IW_ENCODE_EXT_* */
	__u8		tx_seq[RTW_ENCODE_SEQ_MAX_SIZE]; /* LSB first */
	__u8		rx_seq[RTW_ENCODE_SEQ_MAX_SIZE]; /* LSB first */
	struct sockaddr_t	addr; /* ff:ff:ff:ff:ff:ff for broadcast/multicast
			       * (group) keys or unicast address for
			       * individual keys */
	__u16		alg; /* IW_ENCODE_ALG_* */
	__u16		key_len;
#ifdef __CC_ARM	//Fix Keil compile error, must modify sizeof rtw_encode_ext - Alex Fang
	__u8		key[1];
#else
	__u8		key[0];
#endif
};

/* ------------------------ IOCTL REQUEST ------------------------ */
/*
 * This structure defines the payload of an ioctl, and is used 
 * below.
 *
 * Note that this structure should fit on the memory footprint
 * of rtwreq (which is the same as ifreq), which mean a max size of
 * 16 octets = 128 bits. Warning, pointers might be 64 bits wide...
 * You should check this when increasing the structures defined
 * above in this file...
 */
union	rtwreq_data
{
	/* Config - generic */
	char		name[IFNAMSIZ];
	/* Name : used to verify the presence of  wireless extensions.
	 * Name of the protocol/provider... */

	struct rtw_point	essid;		/* Extended network name */
	struct rtw_param	nwid;		/* network id (or domain - the cell) */
	struct rtw_freq	freq;		/* frequency or channel :
					 * 0-1000 = channel
					 * > 1000 = frequency in Hz */

	struct rtw_param	sens;		/* signal level threshold */
	struct rtw_param	bcnsens;	/* signal level threshold */
	struct rtw_param	bitrate;	/* default bit rate */
	struct rtw_param	txpower;	/* default transmit power */
	struct rtw_param	rts;		/* RTS threshold threshold */
	struct rtw_param	frag;		/* Fragmentation threshold */
	__u32		mode;		/* Operation mode */
	struct rtw_param	retry;		/* Retry limits & lifetime */

	struct rtw_point	encoding;	/* Encoding stuff : tokens */
	struct rtw_param	power;		/* PM duration/timeout */

	struct sockaddr_t	ap_addr;	/* Access point address */
	struct sockaddr_t	addr;		/* Destination address (hw/mac) */

	struct rtw_param	param;		/* Other small parameters */
	struct rtw_point	data;		/* Other large parameters */
	struct rtw_point	passphrase;		/* Extended network name */
};

/*
 * The structure to exchange data for ioctl.
 * This structure is the same as 'struct ifreq', but (re)defined for
 * convenience...
 * Do I need to remind you about structure size (32 octets) ?
 */
struct	rtwreq 
{
#if 0
	union
	{
		char	ifrn_name[IFNAMSIZ];	/* if name, e.g. "eth0" */
	} ifr_ifrn;
#endif
	char	ifr_name[IFNAMSIZ];	/* if name, e.g. "eth0" */

	/* Data part (defined just above) */
	union	rtwreq_data	u;
};

/* -------------------------- IOCTL DATA -------------------------- */
/*
 *	For those ioctl which want to exchange mode data that what could
 *	fit in the above structure...
 */

/*
 * Private ioctl interface information
 */
 
struct	rtw_priv_args
{
	__u32		cmd;		/* Number of the ioctl to issue */
	__u16		set_args;	/* Type and number of args */
	__u16		get_args;	/* Type and number of args */
	char		name[IFNAMSIZ];	/* Name of the extension */
};

/* ----------------------- WIRELESS EVENTS ----------------------- */
/*
 * Wireless events are carried through the rtnetlink socket to user
 * space. They are encapsulated in the IFLA_WIRELESS field of
 * a RTM_NEWLINK message.
 */

#define IW_EXT_STR_FOURWAY_DONE  		"WPA/WPA2 handshake done"
#define IW_EXT_STR_RECONNECTION_FAIL  	"RECONNECTION FAILURE"
#define IW_EVT_STR_STA_ASSOC			"STA Assoc"
#define IW_EVT_STR_STA_DISASSOC		"STA Disassoc"
#define IW_EXT_STR_FOURWAY_DONE  "WPA/WPA2 handshake done"
#define IW_EXT_STR_RECONNECTION_FAIL  "RECONNECTION FAILURE"
#define IW_EVT_STR_STA_ASSOC	"STA Assoc"
#define IW_EVT_STR_STA_DISASSOC	"STA Disassoc"
#define IW_EVT_STR_SEND_ACTION_DONE	"Send Action Done"
#define IW_EVT_STR_NO_NETWORK "No Assoc Network After Scan Done"
#define IW_EVT_STR_ICV_ERROR "ICV Eror"
#define IW_EVT_STR_CHALLENGE_FAIL "Auth Challenge Fail"
#define IW_EVT_STR_SOFTAP_START "Softap Start"
#define IW_EVT_STR_SOFTAP_STOP "Softap Stop"
#endif	/* _WIRELESS_H */
