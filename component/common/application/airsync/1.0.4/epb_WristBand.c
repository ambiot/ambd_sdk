//  epb_WristBand.h
//  MicroMessenger
//
//  Created by harlliu@tencent.com on 14-04-24.
//  Copyright 2014 Tencent. All rights reserved.
//

//  Version : 1.0.2

#include <platform_opts_bt.h>
#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "epb_WristBand.h"
#include "os_mem.h"

#define TAG_MMOpen_BaseResponse_ErrCode                                 0x08
#define TAG_MMOpen_BaseResponse_ErrMsg                                  0x12

#define TAG_MMOpen_StepDataItem_Step                                    0x08
#define TAG_MMOpen_StepDataItem_Timestamp                               0x10
#define TAG_MMOpen_StepDataItem_RTCYear                                 0x18
#define TAG_MMOpen_StepDataItem_RTCMonth                                0x20
#define TAG_MMOpen_StepDataItem_RTCDay                                  0x28
#define TAG_MMOpen_StepDataItem_RTCHour                                 0x30
#define TAG_MMOpen_StepDataItem_RTCMinute                               0x38
#define TAG_MMOpen_StepDataItem_RTCSecond                               0x40

#define TAG_MMOpen_WristbandRequest_StepData                            0x0a
#define TAG_MMOpen_WristbandRequest_ExtData                             0x12

#define TAG_MMOpen_WristbandResponse_BaseResponse                       0x0a


static int epb_mmopen_unpack_base_response(MMOpen_BaseResponse *base_response, const uint8_t *buf,
                                           int buf_len)
{
    Epb epb;
    epb_unpack_init(&epb, buf, buf_len);

    if (!epb_has_tag(&epb, TAG_MMOpen_BaseResponse_ErrCode))
    {
        return -1;
    }

    if (epb_has_tag(&epb, TAG_MMOpen_BaseResponse_ErrCode))
    {
        base_response->has_err_code = true;
        base_response->err_code = (int)epb_get_enum(&epb, TAG_MMOpen_BaseResponse_ErrCode);
    }

    if (epb_has_tag(&epb, TAG_MMOpen_BaseResponse_ErrMsg))
    {
        base_response->err_msg.str = epb_get_string(&epb, TAG_MMOpen_BaseResponse_ErrMsg,
                                                    &base_response->err_msg.len);
        base_response->has_err_msg = true;
    }

    return 0;
}

int epb_mmopen_step_data_item_pack_size(MMOpen_StepDataItem *item)
{
    int pack_size = epb_varint32_pack_size(TAG_MMOpen_StepDataItem_Step, item->step, false);
    if (item->has_timestamp)
    {
        pack_size += epb_varint32_pack_size(TAG_MMOpen_StepDataItem_Timestamp, item->timestamp, false);
    }

    if (item->has_rtc_year)
    {
        pack_size += epb_varint32_pack_size(TAG_MMOpen_StepDataItem_RTCYear, item->rtc_year, false);
    }
    if (item->has_rtc_month)
    {
        pack_size += epb_varint32_pack_size(TAG_MMOpen_StepDataItem_RTCMonth, item->rtc_month, false);
    }
    if (item->has_rtc_day)
    {
        pack_size += epb_varint32_pack_size(TAG_MMOpen_StepDataItem_RTCDay, item->rtc_day, false);
    }
    if (item->has_rtc_hour)
    {
        pack_size += epb_varint32_pack_size(TAG_MMOpen_StepDataItem_RTCHour, item->rtc_hour, false);
    }
    if (item->has_rtc_minute)
    {
        pack_size += epb_varint32_pack_size(TAG_MMOpen_StepDataItem_RTCMinute, item->rtc_minute, false);
    }
    if (item->has_rtc_second)
    {
        pack_size += epb_varint32_pack_size(TAG_MMOpen_StepDataItem_RTCSecond, item->rtc_second, false);
    }
    return pack_size;
}

int epb_mmopen_pack_step_data_item(MMOpen_StepDataItem *item, uint8_t *buf, int buf_len)
{
    Epb epb;
    epb_pack_init(&epb, buf, buf_len);

    int ret = epb_set_uint32(&epb, TAG_MMOpen_StepDataItem_Step, item->step);
    if (ret < 0) { return ret; }

    if (item->has_timestamp)
    {
        ret = epb_set_uint32(&epb, TAG_MMOpen_StepDataItem_Timestamp, item->timestamp);
        if (ret < 0) { return ret; }
    }

    if (item->has_rtc_year)
    {
        ret = epb_set_uint32(&epb, TAG_MMOpen_StepDataItem_RTCYear, item->rtc_year);
        if (ret < 0) { return ret; }
    }
    if (item->has_rtc_month)
    {
        ret = epb_set_uint32(&epb, TAG_MMOpen_StepDataItem_RTCMonth, item->rtc_month);
        if (ret < 0) { return ret; }
    }
    if (item->has_rtc_day)
    {
        ret = epb_set_uint32(&epb, TAG_MMOpen_StepDataItem_RTCDay, item->rtc_day);
        if (ret < 0) { return ret; }
    }
    if (item->has_rtc_hour)
    {
        ret = epb_set_uint32(&epb, TAG_MMOpen_StepDataItem_RTCHour, item->rtc_hour);
        if (ret < 0) { return ret; }
    }
    if (item->has_rtc_minute)
    {
        ret = epb_set_uint32(&epb, TAG_MMOpen_StepDataItem_RTCMinute, item->rtc_minute);
        if (ret < 0) { return ret; }
    }
    if (item->has_rtc_second)
    {
        ret = epb_set_uint32(&epb, TAG_MMOpen_StepDataItem_RTCSecond, item->rtc_second);
        if (ret < 0) { return ret; }
    }

    return epb_get_packed_size(&epb);
}

int epb_mmopen_wristband_request_pack_size(MMOpen_WristbandRequest *request)
{
    int pack_size = 0;
    for (int i = 0; i < request->step_data_count; i++)
    {
        int len = epb_mmopen_step_data_item_pack_size(request->step_data + i);
        pack_size += epb_length_delimited_pack_size(TAG_MMOpen_WristbandRequest_StepData, len);
    }
    if (request->has_ext_data)
    {
        pack_size += epb_length_delimited_pack_size(TAG_MMOpen_WristbandRequest_ExtData,
                                                    request->ext_data.len);
    }

    return pack_size;
}

int epb_mmopen_pack_wristband_request(MMOpen_WristbandRequest *request, uint8_t *buf, int buf_len)
{
    Epb epb;
    epb_pack_init(&epb, buf, buf_len);

    int ret;
    for (int i = 0; i < request->step_data_count; i++)
    {
        MMOpen_StepDataItem *item = request->step_data + i;
        int item_len = epb_mmopen_step_data_item_pack_size(item);
        uint8_t *item_buf = (uint8_t *)os_mem_alloc(RAM_TYPE_DATA_ON, item_len);
        ret = epb_mmopen_pack_step_data_item(item, item_buf, item_len);
        if (ret < 0)
        {
            os_mem_free(item_buf);
            return ret;
        }
        ret = epb_set_message(&epb, TAG_MMOpen_WristbandRequest_StepData, item_buf, item_len);
        if (ret < 0)
        {
            os_mem_free(item_buf);
            return ret;
        }
        os_mem_free(item_buf);
    }

    if (request->has_ext_data)
    {
        ret = epb_set_bytes(&epb, TAG_MMOpen_WristbandRequest_ExtData, request->ext_data.data,
                            request->ext_data.len);
        if (ret < 0) { return ret; }
    }

    return epb_get_packed_size(&epb);
}

MMOpen_WristbandResponse *epb_mmopen_unpack_wristband_response(const uint8_t *buf, int buf_len)
{
    Epb epb;
    epb_unpack_init(&epb, buf, buf_len);

    if (!epb_has_tag(&epb, TAG_MMOpen_WristbandResponse_BaseResponse))
    {
        return NULL;
    }

    MMOpen_WristbandResponse *response = (MMOpen_WristbandResponse *)os_mem_alloc(RAM_TYPE_DATA_ON,
                                                                                  sizeof(MMOpen_WristbandResponse));
    memset(response, 0, sizeof(MMOpen_WristbandResponse));
    int base_response_len = 0;
    const Message *base_response = epb_get_message(&epb, TAG_MMOpen_WristbandResponse_BaseResponse,
                                                   &base_response_len);
    int ret = epb_mmopen_unpack_base_response(&response->base_response, base_response,
                                              base_response_len);
    if (ret < 0)
    {
        os_mem_free(response);
        return NULL;
    }

    return response;
}
#endif
