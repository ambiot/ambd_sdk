ENTRY(Reset_Handler)

INCLUDE "rlx8721d_layout.ld"

SECTIONS
{
	.rom.text : { } > IROM_NS
	.rom.rodata : { } > DROM_NS
	.hal.rom.bss : { } > ROMBSS_RAM_COM
	.hal.ns_rom.bss : { } > ROMBSS_RAM_NS

	/* secure ROM BSS, this section should in secure RAM, add this to link 
	 * symbols to avoid compile error */
	.hal.s_rom.bss :
	{
		__rom_bss_start_s__ = ABSOLUTE(.);
		__rom_bss_end_s__ = __rom_bss_start_s__ + LENGTH(ROMBSS_RAM_S);
	} >  ROMBSS_RAM_S

	/* image1 entry, this section should in RAM and fixed address for ROM */
	.ram_image1.entry :
	{
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.image1.entry.data*)))
		KEEP(*(.image1.validate.rodata*))
	} > BOOTLOADER_RAM_S

	/* data & bss should have not any content */
	.ram.data : 
	{
		KEEP(*(.data*))
	} > BD_RAM_NS
 	.ram.bss :
	{
    		KEEP(*(.bss*))
	} > BD_RAM_NS
	.rom.text.libgcc : 
	{
		KEEP(*(.text*))
	} > IROM_NS
}
