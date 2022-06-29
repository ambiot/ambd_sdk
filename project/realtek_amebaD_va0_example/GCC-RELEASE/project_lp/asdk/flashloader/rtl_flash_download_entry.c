/******************************************************************************
 * Copyright (c) 2013-2016 Realtek Semiconductor Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
 
#include "rtl8721d.h"
#include "build_info.h"
#include "rtl8721d_flash.h"

void RtlFlashProgram(VOID);

IMAGE1_ENTRY_SECTION
RAM_FUNCTION_START_TABLE RamStartTable = {
	.RamStartFun = RtlFlashProgram,
	.RamWakeupFun = RtlFlashProgram,
	.RamPatchFun0 = RtlFlashProgram,
	.RamPatchFun1 = RtlFlashProgram,
	.RamPatchFun2 = RtlFlashProgram
};
