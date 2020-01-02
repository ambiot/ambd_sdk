ENTRY(Reset_Handler)

INCLUDE "rlx8721d_layout_tz.ld"

SECTIONS
{
	.rom.text : { } > IROM
	.rom.rodata : { } > DROM
	.hal.rom.bss : { } > ROMBSS_RAM_COM
	.hal.s_rom.bss : { } > ROMBSS_RAM_S

	/* image3: security image start */
	.gnu.sgstubs :
	{
		__ram_image3_nsc_start__ = .;
		. = ALIGN(16);
	} > BD_RAM_NSC

	.ram_image3.text :
	{
		__ram_image3_text_start__ = .;
		KEEP(*(.image3.nsc_entry.text*))
		*(.text*)
		*(.rodata*)
		. = ALIGN(16);
	} > BD_RAM_S

	.ram_image3.data :
	{
		__ram_image3_data_start__ = .;
		*(.data*)
		__ram_image3_data_end__ = .;
	
		. = ALIGN(16);
		__ram_image3_text_end__ = .;
	} > BD_RAM_S

	.ram_image3.bss :
	{
		__image3_bss_start__ = .;
		*(.bss*)
		*(COMMON)
		__image3_bss_end__ = .;
	} > BD_RAM_S

	/* PSRAM_S image start */
	.psram_image3.text :
	{
		__psram_image3_text_start__ = .;
		*(.psram.text*)
	} > PSRAM_S

	.psram_image3.data : 
	{
		*(.psram.data*)
		*(.psram.rodata*)
		. = ALIGN(16);
	} > PSRAM_S
  
	.psram_image3.bss :
	{
		__psram_bss_start__ = .;
		*(.psram.bss*)
		__psram_bss_end__ = .;
	} > PSRAM_S

	.psram_heap.data : 
	{
		*(.psram.heap*)
	} > PSRAM_S
}
