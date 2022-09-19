ENTRY(Reset_Handler)

INCLUDE "rlx8721d_layout.ld"

SECTIONS
{
	.rom2.data : 
	{
		__rom2_data_start__ = .;
		*(.data*)
		__rom2_data_end__ = .;
		. = ALIGN(32);
	} > ROM2_RAM
	
	.rom2.bss :
	{
		__rom2_bss_start__ = .;
		*(.bss*)
		*(COMMON)
		__rom2_bss_end__ = .;
		. = ALIGN(32);
	} > ROM2_RAM

	.rom.heap : 
	{
		__rom2_heap_start__ = .;
		end = .;
	} > ROM2_RAM
	
	/*  Add . to assign the start address of the section */ 
	/*  to prevent the change of the start address by ld doing section alignment */  
	.rom2.text :
	{
		__rom2_text_start__ = .;

		/* rom2 text */
		KEEP(*(.hal.rom2.entry.text*))
		KEEP(*(.hal.rom2.text*))
		KEEP(*(.text*))
		KEEP(*(.hal.rom2.rodata*))
		KEEP(*(.rodata*))
		KEEP(*(.rom.rodata.str1.4*))
		. = ALIGN(32);
		__rom2_text_end__ = .;

	} > IROM2

	/* image1 entry, this section should in RAM and fixed address for ROM */
	.ram_image1.entry :
	{
		__ram_image1_text_start__ = .;
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.image1.entry.data*)))
		KEEP(*(.image1.validate.rodata*))
		KEEP(*(.image1.rodata*))
	} > BOOTLOADER_RAM

	/* retention RAM entry, this section should in RAM and fixed address for ROM */
	.ram_retention.entry : 
	{
		__retention_entry_func__ = ABSOLUTE(.);
	} > RETENTION_RAM
	
	/* data & bss should have not any content */
	.ram.data : 
	{
		KEEP(*(.data*))
	} > ROM2_RAM
	.ram.bss :
	{
		KEEP(*(.bss*))
	} > ROM2_RAM
}
