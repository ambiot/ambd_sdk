// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include <azure/core/az_platform.h>
#include <azure/core/internal/az_precondition_internal.h>

#include <azure/core/_az_cfg.h>

#include "FreeRTOS.h"
#include "task.h"

AZ_NODISCARD az_result az_platform_clock_msec(int64_t* out_clock_msec)
{
	*out_clock_msec = (int64_t)xTaskGetTickCount/portTICK_PERIOD_MS;
	return AZ_OK;
}


AZ_NODISCARD az_result az_platform_sleep_msec(int32_t milliseconds)
{
	vTaskDelay(milliseconds/portTICK_RATE_MS);
	return AZ_OK;
}
