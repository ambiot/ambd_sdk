MEMORY
{
	IROM (rx) : 			ORIGIN = 0x00000000, LENGTH = 0x18000	/* ROM: 96k */
	DROM (rx) : 			ORIGIN = 0x00020000, LENGTH = 0x4000	/* ROM: 16k */

	ROMBSS_RAM (rw)  : 		ORIGIN = 0x00080000, LENGTH = 0x00082000 - 0x00080000	/* ROM BSS RAM: 8K */
	BOOTLOADER_RAM (rwx)  : 	ORIGIN = 0x00082000, LENGTH = 0x00083000 - 0x00082000	/* BOOT Loader RAM: 4K */
	BD_RAM (rwx)  : 		ORIGIN = 0x00083000, LENGTH = 0x0008F000 - 0x00083000	/* MAIN RAM: 48K */
	MSP_RAM (wx)  : 		ORIGIN = 0x0008F000, LENGTH = 0x1000	/* MSP RAM: 4k */
	RETENTION_RAM (rwx)  : 		ORIGIN = 0x000C0000, LENGTH = 0x000C0400 - 0x000C0000	/* RETENTION SRAM: 1K */

	/* Flash */
	KM0_BOOT (rx)  :		ORIGIN = 0x08000000+0x20, LENGTH = 0x02000-0x20	/* XIPBOOT: 8k, 32 Bytes resvd for header*/
	DPK (r) :			ORIGIN = 0x08001000, LENGTH = 0x1000	/* DPK: 4K calibration data in flash */
	BACKUP (r) :			ORIGIN = 0x08002000, LENGTH = 0x1000	/* BACKUP: 4K system data in flash */
	XIPSYS (r) :			ORIGIN = 0x08003000, LENGTH = 0x1000	/* XIPSYS: 4K system data in flash */
	KM4_BOOT (rx)  :		ORIGIN = 0x08004000+0x20, LENGTH = 0x02000-0x20	/* XIPBOOT: 8k, 32 Bytes resvd for header*/
	KM0_IMG2 (rx)  : 		ORIGIN = 0x0C000000+0x20, LENGTH = 0x02000000 - 0x20	/* KM0_IMG2: 128k, 32 Bytes resvd for header, virtual address */
	KM4_IMG2 (rx)  : 		ORIGIN = 0x0E000000+0x20, LENGTH = 0x02000000 - 0x20	/* KM4_IMG2 OTA1: 868k, 32 Bytes resvd for header, virtual address */

	/* KM4 RAM */
	PRINT_RAM (rwx)  : 		ORIGIN = 0x1006F000, LENGTH = 0x10070000 - 0x1006F000	/* PRINTF BUFFER RAM: 4k */
}
