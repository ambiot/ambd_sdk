/**
  ******************************************************************************
  * @file    rtl8721dlp_sleepcfg.c
  * @author
  * @version V1.0.0
  * @date    2016-05-17
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of pin control:
  *           - sleep wakeup event
  *           - sleep power management
  ******************************************************************************
  * @attention
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2015, Realtek Semiconductor Corporation. All rights reserved.
  ****************************************************************************** 
  */

#include "ameba_soc.h"

#ifdef CONFIG_SOC_PS_MODULE
/* wifi 32k mode user sdm */
PWRCFG_TypeDef km0_pwrmgt_config[]=
{
//  	Module								Status
	{BIT_LSYS_PST_SLEP_EACK,			OFF},	//BIT1: 1 Enable ANA4M CLK when PMC enter into sleep mode
	{BIT_LSYS_PST_SLEP_EBUS,			OFF},	//BIT2: 1 Enable platform clock when PMC entro into sleep mode
	{BIT_LSYS_PST_SLEP_EMPM,			OFF},	//BIT3: 1 means RAM can not enter low power mode, 0 can enter, based on 0xD8 (see sleep_lsram_config)
	{BIT_LSYS_PST_SLEP_LDLM,			OFF},	//BIT4 0 LPSDO enter sleep mode
	{BIT_LSYS_PST_SLEP_ERCK,			OFF},	//BIT5 0 gate ls system clock 
	{BIT_LSYS_PST_SLEP_DPSW,			ON},	//BIT6: 1: disable power switch and use SWR mode, 0: enable power switch from SWR to LPLDO (1.1v->0.9v, dont suggect to use it option when wifi open)
	{BIT_LSYS_PST_SLEP_EPWM,			OFF},	//BIT7: 1 LDO mode: 1.1V or SWR PWM mode, 0 LDO mode 0.9v or SWR PFM mode 0.9v (0.9v can be tuned by 0x4800_0330 stage4)
	{BIT_LSYS_PST_SLEP_ESWR,			ON},	//BIT8: 0 is disable SWR when enter sleep
	{BIT_LSYS_PST_SLEP_EXTL,			OFF},	//BIT9 0 disable XTAL when sleep, should conflict with  BIT_LSYS_PST_SLEP_XACT
	{BIT_LSYS_PST_SLEP_XACT,			ON},	//BIT10 based on BIT_LSYS_PST_SLEP_EXTL
	
	{0xFFFFFFFF,							OFF},	/* Table end */
};


/* light-sleep: out-circut=on, out-val=keep, mem-arry=on */
/* deep-sleep: out-circut=off, out-val=not keep, mem-arry=on, suggest to use this */

/* KM4 RAM control flow: */
/* 1)	Shut down some RAMs if not used  */
/* 		HS_SYSON registers has two address mapping that can be accessed by KM4:  */
/* 		0x4000_0000~0x4000_03FF (Note: this address space can only be accessed by KM0 when KM4 is active)  */
/*		0x4800_0800~0x4800_0BFF (Note: this address space can only be accessed by KM0 when KM4 is disable)  */
/* 		KM0 should shut down unused RAMs before enable KM4, KM4 RAM are divided into 3 groups, the corresponding shut-down control registers are :  */
/* 		Group0 RAM shut down: 0x4800_0B08[8]  */
/* 		Group1 RAM shut down: 0x4800_0B08[12]  */
/* 		Group2 RAM shut down: 0x4800_0B08[16]  */
/* 2)	KM4 RAMs low power mode setting  */
/* 		KM0 should setting KM4's RAM low power mode register when KM4 is disabled  */
/*		Group0 RAM low power mode : 0x4800_0B08[9]/ 0x4800_0B08[10]  */
/*		Group1 RAM low power mode : 0x4800_0B08[13]/ 0x4800_0B08[14]  */
/*		Group2 RAM low power mode : 0x4800_0B08[17]/ 0x4800_0B08[18]  */
/* 3)	control register  */
/* 		REG_HS_MEM_CTRL2 0x4000_0308 or 4800_0B08 */
/* 		4800_0B08 can always be accessed, but 0x4000_0308 can only be access when KM4 on */
/* 4)	KM0 should clear all these bit before KM4 resume, PMC not control it automaticly */
PWRCFG_TypeDef sleep_hsram_config[]=
{
//  	Module								Status
	{BIT_HSYS_RFC_MEM_LS,				OFF},	/* BIT31 R/W	0		1: Enable RFC memory enter into light-sleep mode 0: Disable  */
	{BIT_HSYS_RFC_MEM_DS,				OFF},	/* BIT30 R/W	0		1: Enable RFC memory enter into deep-sleep mode 0: Disable  */
	{BIT_HSYS_RFC_MEM_SD,				OFF},	/* BIT29 R/W	0		1: Shut-down RFC memory 0: Power on RFC memory   */
	
	{BIT_HSYS_IDCACHE_LS,				ON},	/* BIT28 R/W	0		1: Enable ICACHE/DCACHE enter light-sleep mode 0: Disable  */

	{BIT_HSYS_WL_SHARE_MEM_LS,			OFF},	/* BIT26 R/W	0		1: Enable WL shared memory enter into light-sleep mode, only valid when WL memory shared as KM4 RAM 0: Disable  */
	{BIT_HSYS_WL_SHARE_MEM_DS,			OFF},	/* BIT25 R/W	0		1: Enable WL shared memory enter into deep-sleep mode, only valid when WL memory shared as KM4 RAM 0: Disable  */
	{BIT_HSYS_WL_SHARE_MEM_SD,			OFF},	/* BIT24 R/W	0		1: Shut-down WL shared memory, only valid when WL memory shared as KM4 RAM 0: Power on  WL shared memory, only valid when WL memory shared as KM4 RAM  */
	{BIT_HSYS_BT_SHARE_MEM_LS,			OFF},	/* BIT22 R/W	0		1: Enable BT shared memory enter into light-sleep mode, only valid when BT memory shared as KM4 RAM 0: Disable  */
	{BIT_HSYS_BT_SHARE_MEM_DS,			OFF},	/* BIT21 R/W	0		1: Enable BT shared memory enter into deep-sleep mode, only valid when BT memory shared as KM4 RAM 0: Disable  */
	{BIT_HSYS_BT_SHARE_MEM_SD,			OFF},	/* BIT20 R/W	0		1: Shut-down BT shared memory, only valid when BT memory shared as KM4 RAM 0: Power on  BT shared memory, only valid when BT memory shared as KM4 RAM  */

	/* SRAM */
	{BIT_HSYS_K4RAM2_LS,				OFF},	/* BIT18 R/W	0		1: Enable KM4 RAM2 enter into light-sleep mode 0: Disable  */
	{BIT_HSYS_K4RAM2_DS,				ON},	/* BIT17 R/W	0		1: Enable KM4 RAM2 enter into deep-sleep mode 0: Disable  */
	{BIT_HSYS_K4RMA2_SD,				OFF},	/* BIT16 R/W	0		1: Shut-down KM4 RAM2 0: Power on  KM4 RAM2  */
	{BIT_HSYS_K4RAM1_LS,				OFF},	/* BIT14 R/W	0		1: Enable KM4 RAM1 enter into light-sleep mode 0: Disable  */
	{BIT_HSYS_K4RAM1_DS,				ON},	/* BIT13 R/W	0		1: Enable KM4 RAM1 enter into deep-sleep mode 0: Disable  */
	{BIT_HSYS_K4RMA1_SD,				OFF},	/* BIT12 R/W	0		1: Shut-down KM4 RAM1 0: Power on  KM4 RAM1  */
	{BIT_HSYS_K4RAM0_LS,				OFF},	/* BIT10 R/W	0		1: Enable KM4 RAM0 enter into light-sleep mode 0: Disable  */
	{BIT_HSYS_K4RAM0_DS,				ON},	/* BIT9 R/W	0		1: Enable KM4 RAM0 enter into deep-sleep mode 0: Disable  */
	{BIT_HSYS_K4RMA0_SD,				OFF},	/* BIT8 R/W	0		1: Shut-down KM4 RAM0 0: Power on  KM4 RAM0  */

	{BIT_HSYS_PERI_MEM_LS,				OFF},	/* BIT6 R/W	0		1: Enable Peripheral memory enter into light-sleep mode 0: Disable  */
	{BIT_HSYS_PERI_MEM_DS,				OFF},	/* BIT5 R/W	0		1: Enable Peripheral memory enter into deep-sleep mode 0: Disable  */
	{BIT_HSYS_PERI_MEM_SD,				OFF},	/* BIT4 R/W	0		1: Shut-down Peripheral memory 0: Power on Peripheral memory  */
	{BIT_HSYS_USB_MEM_LS,				OFF},	/* BIT2 R/W	0		1: Enable USB memory enter into light-sleep mode 0: Disable  */
	{BIT_HSYS_USB_MEM_DS,				OFF},	/* BIT1 R/W	0		1: Enable USB memory enter into deep-sleep mode 0: Disable  */
	{BIT_HSYS_USB_MEM_SD,				OFF},	/* BIT0 R/W	0		1: Shut-down USB memory 0: Power on USB memory  */
	
	{0xFFFFFFFF,							OFF},	/* Table end */
};

/* LS memory control  */
/* 1)	Two sets of parameter for memory,  one set for 0.9v,  the other for 1.1v,  switch between these two sets of parameter is handled by HW PMC,  SW don't need to care.  */
/* 2)	KM0 RAM low power mode control  */
/* 		Two sets of registers are used to control the KM0's RAM low power mode.  */
/* 		When KM0 is in active mode, the first set (0x4800_02D8[2:0]) will be selected  */
/* 		When KM0 is in sleep mode, if 0x4800_0320[3] =0 (see sleep_pwrmgt_config.BIT_LSYS_PST_SLEP_EMPM), Then the second set (0x4800_02D8[18:16]) will be selected. */
/* 3)	Retention RAM low power mode control  */
/* 		Three sets of registers are used to control the retention RAM low power mode.  */
/* 		When KM0 is in active mode, the first set (0x4800_02D8[6:4]) will be selected  */
/* 		When KM0 is in sleep mode, if 0x4800_0320[3] =0, then the second set(0x4800_02D8[22:20]) will be selected. */
/*		When PMC enter into deep-sleep mode, the third set(REG_MEM_PMCTRL_DSLP 0x4800_001C[2:0]) will be selected. (see dsleep_lsram_config)  */
/* 4)	control register  */
/* 		REG_MEM_CTRL2 4800_02D8 */
PWRCFG_TypeDef sleep_lsram_config[]=
{
//  	Module								Status
	/* REG_MEM_CTRL2 4800_02D8 */
	{BIT_LSYS_SLEP_RET_RAM_LS,			OFF},	/* BIT22 R/W	0		"1: Enable Retention RAM light-sleep when KM0 in sleep state0: Disable" */
	{BIT_LSYS_SLEP_RET_RAM_DS,			ON},	/* BIT21 R/W	0		"1: Enable Retention RAM deep-sleep when KM0 in sleep state0: Disable"  */
	{BIT_LSYS_SLEP_RET_RAM_SD,			OFF},	/* BIT20 R/W	0		"1: Shut-down Retention RAM when KM0 in sleep state0: Power on Retention RAM when KM0 in sleep state"  */
	{BIT_LSYS_SLEP_IDCACHE_LS,			ON},	/* BIT19 R/W	0		"1: Enable ICACHE/DCACHE light-sleep when KM0 in sleep state0: Disable"  */

	{BIT_LSYS_SLEP_KM0_RAM_LS,			ON},	/* BIT18 R/W	0		"1: Enable CPU RAM light-sleep when KM0 in sleep state0: Disable"  */
	{BIT_LSYS_SLEP_KM0_RAM_DS,			OFF},	/* BIT17 R/W	0		"1: Enable CPU RAM deep-sleep when KM0 in sleep state0: Disable"  */
	{BIT_LSYS_SLEP_KM0_RAM_SD,			OFF},	/* BIT16 R/W	0		"1: Shut-down CPU RAM when KM0 in sleep state0: Power on CPU RAM when KM0 in sleep state"  */

	{BIT_LSYS_NORM_RET_RAM_LS,			OFF},	/* BIT6 R/W	0		"1: Enable Retention RAM light-sleep when KM0 in active state0: Disable"  */
	{BIT_LSYS_NORM_RET_RAM_DS,			OFF},	/* BIT5 R/W	0		"1: Enable Retention RAM deep-sleep when KM0 in active state0: Disable"  */
	{BIT_LSYS_NORM_RET_RAM_SD,			OFF},	/* BIT4 R/W	0		"1: Shut-down Retention RAM when KM0 in active state0: Power on Retention RAM when KM0 in active state"  */
	{BIT_LSYS_NORM_IDCACHE_LS,			OFF},	/* BIT3 R/W	0		"1: Enable ICACHE/DCACHE light-sleep when KM0 in active state0: Disable"  */

	{BIT_LSYS_NORM_KM0_RAM_LS,			OFF},	/* BIT2 R/W	0		"1: Enable CPU RAM light-sleep when KM0 in active state0: Disable"  */
	{BIT_LSYS_NORM_KM0_RAM_DS,			OFF},	/* BIT1 R/W	0		"1: Enable CPU RAM deep-sleep when KM0 in active state0: Disable"  */
	{BIT_LSYS_NORM_KM0_RAM_SD,			OFF},	/* BIT0 R/W	0		"1: Shut-down CPU RAM when KM0 in active state0: Power on CPU RAM when KM0 in active state" */

	{0xFFFFFFFF,							OFF},	/* Table end */
};


PWRCFG_TypeDef dsleep_lsram_config[]=
{
//  	Module								Status
	{BIT_AON_DLSP_RETRAM_SD,		OFF},	/* BIT2 R/W	0		Retension RAM SD control under Deep-sleep mode  */
	{BIT_AON_DLSP_RETRAM_DS,		ON},	/* BIT1 R/W	0		Retension RAM DS control under Deep-sleep mode  */
	{BIT_AON_DLSP_RETRAM_LS,		OFF},	/* BIT0 R/W	0		Retension RAM LS control under Deep-sleep mode  */

	{0xFFFFFFFF,						OFF},	/* Table end */
};

#endif
/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
