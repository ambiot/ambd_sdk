/**
*********************************************************************************************************
*               Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file
* @brief
* @details
* @author
* @date      2017-12-25
* @version   v0.1
* *********************************************************************************************************
*/
#include <platform_opts_bt.h>
#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
#include "app_msg.h"
#include "wechat_airsync_protocol.h"
#include "airsync_ble_service.h"
#include "trace_app.h"
#include "gap.h"
#include "epb_MmBp.h"
#include "epb_WristBand.h"
#include "stdlib.h"
#include "check_endian.h"
#include "string.h"
#include "os_mem.h"

#include "bt_config_wifi.h"

#define AIRSYNC_DEBUG    0

static uint8_t gAirSyncSendBuf[REQUEST_BUFFER_SIZE] = {0};
static uint8_t gAirSyncRevBuf[RECEIVE_BUFFER_SIZE];
static PacketContent gAirSyncSendContent = {0, NULL, false};
static PacketContent gAirSyncReceiveContent = {0, NULL, false};
static uint32_t airsync_sequence_id = 1;

extern uint8_t bt_airsync_config_conn_id;
extern T_SERVER_ID bt_airsync_config_srv_id;

void set_data_complete_callback(uint16_t length, uint8_t *current_pointer)
{
    gAirSyncSendContent.content = current_pointer;
    gAirSyncSendContent.length = length;
}
void airsync_tx_complete(void)
{
    if (gAirSyncSendContent.length > 0)
    {
        airsync_send_stream(gAirSyncSendContent.content, gAirSyncSendContent.length);
    }
}

void airsync_send_stream(uint8_t *buf, uint16_t length)
{
    uint16_t send_len;
    uint8_t *current_pointer = buf;
    APP_PRINT_INFO1("airsync send length: %d", length);

    send_len = (length > AIRSYNC_MTU_SIZE) ? AIRSYNC_MTU_SIZE : length;

#if AIRSYNC_DEBUG
    printf("%s = ", __FUNCTION__);
    for(int i = 0; i < send_len; i++)
        printf("%02X ", buf[i]);
    printf("\r\n");
#endif

    server_send_data(bt_airsync_config_conn_id, bt_airsync_config_srv_id, GATT_UUID_AIRSYNC_CHAR_INDICATION_INDEX, \
                     current_pointer, send_len, GATT_PDU_TYPE_INDICATION);
    length = length - send_len;
    current_pointer += send_len;

    if (length > 0)
    {
        set_data_complete_callback(length, current_pointer);
    }
    else
    {
        set_data_complete_callback(0, NULL);
    }
}



void airsync_auth_request(void)
{
    APP_PRINT_INFO0("Airsync Auth request...");
    printf("Airsync Auth request...\r\n");

    BaseRequest basReq = {NULL};
    AirSync_Header header_data = {0xFE, 1, 0, htons(ECI_req_auth), htons(airsync_sequence_id++)};
    if (airsync_sequence_id == 0)
    {
        airsync_sequence_id = 1;
    }

    /* encrytion with mac address */
    uint8_t mac_address[MAC_ADDRESS_LENGTH];
    gap_get_param(GAP_PARAM_BD_ADDR, mac_address);
    uint8_t address[MAC_ADDRESS_LENGTH];
    for (int i = 0; i < 6; i++)
    {
        address[i] = mac_address[5 - i];
    }
    AuthRequest authReq = {&basReq, \
                           false, \
    {NULL, 0}, \
    PROTO_VERSION, \
    AUTH_PROTO, \
    (EmAuthMethod)AUTH_METHOD, \
    false, \
    {NULL, 0}, \
    true, \
    {address, MAC_ADDRESS_LENGTH}, \
    false, \
    {NULL, 0}, \
    false, \
    {NULL, 0}, \
    true, \
    {DEVICE_ID, sizeof(DEVICE_ID)} \
                          };

    /* create protobuff Byte stream */
    uint16_t data_len = epb_auth_request_pack_size(&authReq) + HEADER_LENGTH;
    if (epb_pack_auth_request(&authReq, gAirSyncSendBuf + HEADER_LENGTH, data_len - HEADER_LENGTH) < 0)
    {
        return;
    }
    header_data.nLength = htons(data_len);
    memcpy(gAirSyncSendBuf, &header_data, HEADER_LENGTH);
    airsync_send_stream(gAirSyncSendBuf, data_len);
}


void airsync_init_request(void)
{
    APP_PRINT_INFO0("Airsync Init request...");
    printf("Airsync Init request...\r\n");

    static uint8_t challeange[4] = {0x11, 0x22, 0x33, 0x44};
    BaseRequest basReq = {NULL};
    InitRequest init_rsq = {&basReq, false, {NULL, 0}, true, {challeange, 4}};
    AirSync_Header header_data = {0xFE, 1, 0, htons(ECI_req_init), htons(airsync_sequence_id++)};
    if (airsync_sequence_id == 0)
    {
        airsync_sequence_id = 1;
    }
    /* calculate totoal packet length*/
    uint16_t data_len = epb_init_request_pack_size(&init_rsq) + HEADER_LENGTH;
    /* handle packet use protobuff protocol*/
    if (epb_pack_init_request(&init_rsq, gAirSyncSendBuf + HEADER_LENGTH, data_len - HEADER_LENGTH) < 0)
    {
        return;
    }
    header_data.nLength = htons(data_len);
    memcpy(gAirSyncSendBuf, &header_data, HEADER_LENGTH);
    airsync_send_stream(gAirSyncSendBuf, data_len);
}


void airsync_wristband_request(void)
{
    APP_PRINT_INFO0("AirSync_Wristband request...");
    printf("AirSync_Wristband request...\r\n");

    BaseRequest basReq = {NULL};
    AirSync_Header header_data = {0xFE, 1, 0, htons(ECI_req_sendData), htons(airsync_sequence_id++)};
    if (airsync_sequence_id == 0)
    {
        airsync_sequence_id = 1;
    }

    MMOpen_WristbandRequest *request = (MMOpen_WristbandRequest *)os_mem_alloc(RAM_TYPE_DATA_ON,
                                                                               sizeof(MMOpen_WristbandRequest));
    memset(request, 0, sizeof(MMOpen_WristbandRequest));
    request->step_data_count = 1;
    request->step_data = (MMOpen_StepDataItem *)os_mem_alloc(RAM_TYPE_DATA_ON,
                                                             sizeof(MMOpen_StepDataItem));
    memset(request->step_data, 0, sizeof(MMOpen_StepDataItem));

    MMOpen_StepDataItem *item = request->step_data;

    item->step = 10000;
    item->has_rtc_year = true;
    item->has_rtc_month = true;
    item->has_rtc_day = true;
    item->has_rtc_hour = true;
    item->has_rtc_minute = true;
    item->has_rtc_second = true;

    item->rtc_year = 2000;
    item->rtc_month = 1;
    item->rtc_day = 1;
    item->rtc_hour = 1;
    item->rtc_minute = 1;
    item->rtc_second = 1;

    request->has_ext_data = false;

    int len = epb_mmopen_wristband_request_pack_size(request);

    uint8_t *WristbandRequestBuf = (uint8_t *)os_mem_alloc(RAM_TYPE_DATA_ON, len);
    epb_mmopen_pack_wristband_request(request, WristbandRequestBuf, len);
    APP_PRINT_INFO1("epb_mmopen_pack_wristband_request len = %d", len);

    SendDataRequest sendDatReq = { \
                                   &basReq, \
    {WristbandRequestBuf, len}, \
    true, \
    (EmDeviceDataType)MPT_wristband_proto \
                                 };

    uint16_t data_len = epb_send_data_request_pack_size(&sendDatReq) + HEADER_LENGTH;

    APP_PRINT_INFO1("epb_send_data_request_pack_size data_len = %d", data_len);

    if (epb_pack_send_data_request(&sendDatReq, gAirSyncSendBuf + HEADER_LENGTH,
                                   data_len - HEADER_LENGTH) < 0)
    {
        os_mem_free(request->step_data);
        os_mem_free(request);
        os_mem_free(WristbandRequestBuf);
        return;
    }
    header_data.nLength = htons(data_len);
    memcpy(gAirSyncSendBuf, &header_data, HEADER_LENGTH);
    airsync_send_stream(gAirSyncSendBuf, data_len);

    os_mem_free(request->step_data);
    os_mem_free(request);
    os_mem_free(WristbandRequestBuf);
}


void airsync_send_data(uint8_t *buf, uint16_t length)
{
    APP_PRINT_INFO0("Airsync Senddata >>>>>");
#if AIRSYNC_DEBUG
    printf("Airsync Senddata >>>>>\r\n");
    printf("%s(): length = %d\r\n", __FUNCTION__, length);
    printf("%s = ", __FUNCTION__);
    for(int i = 0; i < length; i++)
        printf("%02X ", buf[i]);
    printf("\r\n");
#endif

    BaseRequest basReq = {NULL};
    AirSync_Header header_data = {0xFE, 1, 0, htons(ECI_req_sendData), htons(airsync_sequence_id++)};
    if (airsync_sequence_id == 0)
    {
        airsync_sequence_id = 1;
    }

    SendDataRequest sendDatReq = { \
                                   &basReq, \
    {buf, length}, \
    true, \
    (EmDeviceDataType)EDDT_manufatureSvr \
                                 };

    uint16_t data_len = epb_send_data_request_pack_size(&sendDatReq) + HEADER_LENGTH;
    
    APP_PRINT_INFO1("epb_send_data_request_pack_size data_len = %d", data_len);

    if (epb_pack_send_data_request(&sendDatReq, gAirSyncSendBuf + HEADER_LENGTH,
                                   data_len - HEADER_LENGTH) < 0)
    {
        return;
    }
    header_data.nLength = htons(data_len);
    memcpy(gAirSyncSendBuf, &header_data, HEADER_LENGTH);
    airsync_send_stream(gAirSyncSendBuf, data_len);
}

#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
void airsync_send_cmd_to_bt_config(uint8_t *cmd, uint8_t len)
{
    uint8_t send_cmd_flag = 0;

    if (cmd[0] == 0x00 && cmd[1] == 0x07 && cmd[2] == 0x00 && cmd[3] == 0x01 && cmd[4] == 0x00 && len == 5) {
#if AIRSYNC_DEBUG
        printf("[Airsync CMD] Get band cmd!\r\n");
#endif
        send_cmd_flag = 1;
    }
    else if (cmd[0] == 0x00 && cmd[1] == 0x01 && cmd[2] == 0x00 && cmd[3] == 0x01 && len == 5) {
#if AIRSYNC_DEBUG
        if (cmd[4] == 0x00)
            printf("[Airsync CMD] Scan 2.4g AP cmd!\r\n");
        else if (cmd[4] == 0x01)
            printf("[Airsync CMD] Scan 5g AP cmd!\r\n");
#endif
        send_cmd_flag = 1;
    }
    else if (cmd[0] == 0x00 && cmd[1] == 0x03 && cmd[2] == 0x00 && cmd[3] == 0x68 && len == 108) {
#if AIRSYNC_DEBUG
        printf("[Airsync CMD] Connect to AP cmd!\r\n");
#endif
        send_cmd_flag = 1;
    }
    else if (cmd[0] == 0x00 && cmd[1] == 0x05 && cmd[2] == 0x00 && cmd[3] == 0x01 && cmd[4] == 0x01 && len == 5) {
#if AIRSYNC_DEBUG
        printf("[Airsync CMD] Check connection status cmd!\r\n");
#endif
        send_cmd_flag = 1;
    }
    else {
#if AIRSYNC_DEBUG
        printf("[Airsync CMD] Error cmd!\r\n");
#endif
    }

    if (send_cmd_flag)
        BC_send_cmd(cmd, len);
}
#endif

int airsync_receive_data_handle(uint8_t *pBuffer, uint16_t length)
{
    uint16_t comd_id = (pBuffer[4] << 8 | pBuffer[5]);

    switch (comd_id)
    {
    case ECI_none:
        break;
    case ECI_resp_auth:
        {
            APP_PRINT_INFO0("Airsync Auth Response <<<<<");
            printf("Airsync Auth Response <<<<<\r\n");
            AuthResponse *auth_resp;
            auth_resp = epb_unpack_auth_response(pBuffer + HEADER_LENGTH, length - HEADER_LENGTH);
            if (!auth_resp)
            {
                return errorCodeUnpackAuthResp;
            }
            if (auth_resp->base_response->err_code == 0)
            {
                /* Auth request sucessfull */
                APP_PRINT_INFO0("Airsync Auth Successfull <<<<<");
                printf("Airsync Auth Successfull <<<<<\r\n");
                airsync_send_data_event(AIRSYNC_INIT_EVENT);
            }
            else
            {
                /* Auth request failed */
                APP_PRINT_INFO1("Airsync Auth failed, error code: %d", auth_resp->base_response->err_code);
                printf("Airsync Auth failed, error code: %d\r\n", auth_resp->base_response->err_code);
                if (auth_resp->base_response->has_err_msg)
                {
                    APP_PRINT_INFO0("Airsync Auth failed, error message");
                }
                /* free protobuff memory */
                epb_unpack_auth_response_free(auth_resp);
                return auth_resp->base_response->err_code;
            }
            epb_unpack_auth_response_free(auth_resp);
        }
        break;
    case ECI_resp_init:
        {
            APP_PRINT_INFO0("Airsync Init Response <<<<<");
            printf("Airsync Init Response <<<<<\r\n");
            InitResponse *init_resp = epb_unpack_init_response(pBuffer + HEADER_LENGTH, length - HEADER_LENGTH);
            if (!init_resp)
            {
                epb_unpack_init_response_free(init_resp);
                return errorCodeUnpackInitResp;
            }
            if (init_resp->base_response)
            {
                if (init_resp->base_response->err_code == 0)
                {
                    APP_PRINT_INFO0("Airsync Init Successfull <<<<<");
                    printf("Airsync Init Successfull <<<<<\r\n");
#if !defined(CONFIG_BT_AIRSYNC_CONFIG)
                    airsync_send_data_event(AIRSYNC_SENDDATA_TEST_EVENT);
#endif
                }
                else
                {
                    /* Init request failed */
                    APP_PRINT_INFO1("Airsync Init failed, error code: %d", init_resp->base_response->err_code);
                    printf("Airsync Init failed, error code: %d\r\n", init_resp->base_response->err_code);
                    epb_unpack_init_response_free(init_resp);
                    return init_resp->base_response->err_code;
                }
            }
            epb_unpack_init_response_free(init_resp);
        }
        break;
    case ECI_resp_sendData:
        {
            APP_PRINT_INFO0("SendDataResp <<<<<");
#if AIRSYNC_DEBUG
            printf("SendDataResp <<<<<\r\n");
#endif
            SendDataResponse *sendDataResp;
            sendDataResp = epb_unpack_send_data_response(pBuffer + HEADER_LENGTH, length - HEADER_LENGTH);
            epb_unpack_send_data_response_free(sendDataResp);
        }
        break;
    case ECI_push_recvData:
        {
            APP_PRINT_INFO0("Push_RecvData <<<<<");
#if AIRSYNC_DEBUG
            printf("Push_RecvData <<<<<\r\n");
#endif
            RecvDataPush *recvDatPush;
            recvDatPush = epb_unpack_recv_data_push(pBuffer + HEADER_LENGTH, length - HEADER_LENGTH);
            if (!recvDatPush)
            {
                APP_PRINT_INFO0("ECI_push_recvData unpack Fail!");
#if AIRSYNC_DEBUG
                printf("ECI_push_recvData unpack Fail!\r\n");
#endif
                return errorCodeUnpackRecvDataPush;
            }
            APP_PRINT_INFO1("payload length = %d", recvDatPush->data.len);
#if AIRSYNC_DEBUG
            printf("payload length = %d\r\n", recvDatPush->data.len);
            printf("payload data = ");
            for(int i = 0; i < recvDatPush->data.len; i++)
                printf("%02X ", recvDatPush->data.data[i]);
            printf("\r\n");
#endif
#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
            airsync_send_cmd_to_bt_config((uint8_t *)recvDatPush->data.data, recvDatPush->data.len);
#endif
            epb_unpack_recv_data_push_free(recvDatPush);
        }
        break;
    case ECI_push_switchView:
        {
        }
        break;
    case ECI_push_switchBackgroud:
        {
        }
        break;
    case ECI_err_decode:
        break;
    default:
        {
        }
        break;
    }
    return 0;
}

void airsync_receive_data(uint8_t *pBuffer, uint8_t length)
{
#if AIRSYNC_DEBUG
    printf("%s = ", __FUNCTION__);
    for(int i = 0; i < length; i++)
        printf("%02X ", pBuffer[i]);
    printf("\r\n");
#endif

    if (gAirSyncReceiveContent.SendingORReceiving == false)
    {
        if ((pBuffer[0] == 0xFE) && (pBuffer[1] == 0x01))
        {
            /* new package, do init */
            gAirSyncReceiveContent.SendingORReceiving = true;
            gAirSyncReceiveContent.length = pBuffer[2] << 8 | pBuffer[3];
            gAirSyncReceiveContent.content = gAirSyncRevBuf;
        }
        else
        {
            /* error package, do init */
            gAirSyncReceiveContent.SendingORReceiving = false;
            gAirSyncReceiveContent.length = 0;
            gAirSyncReceiveContent.content = gAirSyncRevBuf;
            return;
        }
    }
    memcpy(gAirSyncReceiveContent.content, pBuffer, length);
    gAirSyncReceiveContent.length -= length;
    gAirSyncReceiveContent.content += length;
    if (gAirSyncReceiveContent.length == 0)
    {
        /* all data are received done,start to upack pakcet */
        uint16_t length = gAirSyncRevBuf[2] << 8 | gAirSyncRevBuf[3];
        airsync_receive_data_handle(gAirSyncRevBuf, length);
        gAirSyncReceiveContent.SendingORReceiving = false;
        gAirSyncReceiveContent.length = 0;
        gAirSyncReceiveContent.content = gAirSyncRevBuf;
    }
    else if (gAirSyncReceiveContent.length > 0)
    {
        APP_PRINT_INFO1(" more data for AirSync ReceiveData length = %d", gAirSyncReceiveContent.length);
    }
    else
    {
        /* error package, do init */
        gAirSyncReceiveContent.SendingORReceiving = false;
        gAirSyncReceiveContent.length = 0;
        gAirSyncReceiveContent.content = gAirSyncRevBuf;
        APP_PRINT_INFO0(" error data for AirSync ReceiveData");
#if AIRSYNC_DEBUG
        printf(" error data for AirSync ReceiveData\r\n");
#endif
        return;
    }
}
void airsync_send_data_event(uint8_t Event)
{
    switch (Event)
    {
    case AIRSYNC_SENDDATA_TEST_EVENT:
        {
            airsync_wristband_request();
            break;
        }
    case AIRSYNC_AUTH_EVENT:
        {
            airsync_auth_request();
            break;
        }
    case AIRSYNC_INIT_EVENT:
        {
            airsync_init_request();
            break;
        }
    default:
        break;
    }
}

#endif
