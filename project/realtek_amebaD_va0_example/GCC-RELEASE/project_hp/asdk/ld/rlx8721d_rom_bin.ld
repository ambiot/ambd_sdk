ENTRY(Reset_Handler)

INCLUDE "rlx8721d_layout.ld"

SECTIONS
{
	.rom.text : { } > IROM
	.rom.rodata : { } > DROM
	.hal.rom.bss : { } > ROMBSS_RAM_COM
	.hal.s_rom.bss : { } > ROMBSS_RAM_S

	/* image1 entry, this section should in RAM and fixed address for ROM */
	.ram_image1.entry :
	{
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.image1.entry.data*)))
		KEEP(*(.image1.validate.rodata*))
	} > BOOTLOADER_RAM_S

	/* NS func entry, this section should in NS_ROM and fixed address for S_ROM */
	.ns_rom.rodata :
	{
		__rom_entry_ns_start__ = ABSOLUTE(.);
	} > DROM_NS

	/* data & bss should have not any content */
	.ram.data : 
	{
		KEEP(*(.data*))
	} > BD_RAM_S
 	.ram.bss :
	{
    		KEEP(*(.bss*))
	} > BD_RAM_S
	.rom.text.libgcc : 
	{
		KEEP(*(.text*))
	} > IROM
}
