//
//  defines.h
//  SimpleConfig
//
//  Created by Realsil on 14/11/6.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#ifndef SimpleConfig_defines_h
#define SimpleConfig_defines_h

#define APP_DEBUG
#ifdef APP_DEBUG
#define NSLog(...) NSLog(__VA_ARGS__)
#else
#define NSLog(...) do {} while (0)
#endif

#define PATTERN_ONE                 0
#define PATTERN_TWO                 1
#define PATTERN_THREE               2
#define PATTERN_FOUR                3

#define PATTERN_DEF_PIN             @"57289961"

#define PATTERN_ONE_IDX             (PATTERN_ONE+1)
#define PATTERN_TWO_IDX             (PATTERN_TWO+1)
#define PATTERN_THREE_IDX           (PATTERN_THREE+1)
#define PATTERN_FOUR_IDX            (PATTERN_FOUR+1)

#define RTK_FAILED                  (-1)
#define RTK_SUCCEED                 (0)

#define RTK_SC_CONTROL_SAVE         (0)                         // deprecated
#define RTK_SC_CONTROL_RENAME       (1)
#define RTK_SC_CONTROL_DELETE       (2)

#define SC_RAND_MIN                 (48)
#define SC_RAND_MAX                 (255)
#define MCAST_ADDR_PREFIX           (239)

#define BIT(x)                      (1<<(x))
#define PATTERN_VALID               BIT(1)
#define PATTERN_HAS_END             BIT(2)
#define PATTERN_USING_UDP_SOCKET    BIT(3)
#define PATTERN_USING_PLAIN         BIT(4)

#define TLV_T_BYTES                 (1)
#define TLV_L_BYTES                 (1)
#define TLV_T_L_BYTES               (TLV_T_BYTES + TLV_L_BYTES)
#define TAG_SSID                    1
#define TAG_PSW                     2
#define TAG_IP                      3

#define MAX_AES_KEY_LEN             (32)
#define MAX_BUF_LEN                 (256)

#define SCAN_DATA_LEN               (1+1+2+64+16+6+2)
#define CONTROL_DATA_LEN            (1+1+2+64+16+16)
#define ACK_TO_CONTROL_DATA_LEN     (1+1+2+64+16+16+1)
#define RESP_MIN_LEN                (1+2+6+1+2+4)
#define CONTROL_ACK_ACK_LEN         (64+16+16+1)
#define SCAN_PACKET_SEND_TIME       (3)
#define CONTROL_PACKET_SEND_TIME    (50)

#define REQ_SCAN                    (0)
//#define REQ_SAVE_PROFILE          (BIT(0))
#define REQ_DEL_PROFILE             (BIT(1))
#define REQ_RENAME_DEV              (BIT(0) | BIT(1))
#define REQ_ACK                     (BIT(2))
#define REQ_NEW_AP                  (BIT(2) | BIT(1) | BIT(0))

#define RSP_CONFIG                  (BIT(5))
#define RSP_SCAN                    (BIT(5) | BIT(0))
//#define RSP_SAVE_PROFILE            (BIT(5) | BIT(1))
#define RSP_DEL_PROFILE             (BIT(5) | BIT(1) | BIT(0))
#define RSP_RENAME_DEV              (BIT(5) | BIT(2))
#define RSP_NEW_AP                  (BIT(5) | BIT(2) | BIT(1) | BIT(0))

#define RTK_SC_CONTROL_PKT_ROUND    100

#define LOCAL_PORT_NUM              (8864)
#define UNICAST_PORT_NUM            (8864)
#define MCAST_PORT_NUM              (18864)

#define MAC_ADDR_LEN                (6)
#define MAX_INFO_LEN                (64)

#define ACK_OFFSET_MAC              (3)
#define ACK_OFFSET_STATUS           (9)
#define ACK_OFFSET_DEV_TYPE         (10)
#define ACK_OFFSET_IP               (12)
#define ACK_OFFSET_DEV_NAME         (16)
#define ACK_OFFSET_REQUIRE_PIN      (ACK_OFFSET_DEV_NAME+MAX_INFO_LEN)

#define SC_USE_ENCRYPTION           1
#define SC_NO_ENCRYPTION            PATTERN_USING_PLAIN

#define SC_DBG_CONFIG_RECV          0

struct dev_info{
    unsigned char  status;                  //BIT(0):connected BIT(1):profile saved
    unsigned short dev_type;
    unsigned char  mac[MAC_ADDR_LEN];
    unsigned int   ip;
    unsigned char  extra_info[MAX_INFO_LEN];//name
    unsigned char  require_pin;             //1-require PIN, 0-no need for PIN
};

typedef enum{
    MODE_INIT = 0,
    MODE_CONFIG,
    MODE_WAIT_FOR_IP,
    MODE_DISCOVER,
    MODE_CONTROL,
    MODE_ALERT,
}PatternModes;

#endif
