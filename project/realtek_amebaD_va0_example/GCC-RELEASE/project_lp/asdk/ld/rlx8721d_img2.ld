ENTRY(Reset_Handler)

INCLUDE "rlx8721d_layout.ld"

SECTIONS
{
	.rom.text : { } > IROM
	.rom.rodata : { } > DROM
	.hal.rom.bss : { } > ROMBSS_RAM

	.ram_image2.entry :
	{
		__ram_image2_text_start__ = .;
		__image2_entry_func__ = .;
		KEEP(*(SORT(.image2.entry.data*)))

		__image2_validate_code__ = .;
		KEEP(*(.image2.validate.rodata*)) 

	} > BD_RAM

	.ram_image2.text :
	{
		*(.image2.ram.text*)
	} > BD_RAM

	.ram_image2.data : 
	{
		__data_start__ = .;
		*(.data*)
		__data_end__ = .;
		__ram_image2_text_end__ = .;
		. = ALIGN(16);	
	} > BD_RAM
  
	.ram_image2.bss :
	{
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		*(.FW.ram.bss*)
		__bss_end__ = .;
	} > BD_RAM

	.ram_image2.nocache.data :
	{
		. = ALIGN (32);
		__ram_nocache_start__ = .;
		*(.bdsram.data*)
		. = ALIGN (32);
		__ram_nocache_end__ = .;
	} > BD_RAM

	.ram_heap.data : 
	{
		*(.bfsram.data*)
		*(.heap.stdlib*)
	
	} > BD_RAM

	.heap (COPY):
	{
		__HeapBase = .;
		__end__ = .;
		end = __end__;
		KEEP(*(.heap*))
		__HeapLimit = .;
	} > BD_RAM

	.xip_image2.text : 
	{
		__flash_text_start__ = .;

		*(.img2_custom_signature*)

		*(.text*)    
		*(.rodata*)

		. = ALIGN (4);
		__cmd_table_start__ = .;
		KEEP(*(.cmd.table.data*))
		__cmd_table_end__ = .;

		__flash_text_end__ = .;
	
		. = ALIGN (16);
	} > KM0_IMG2

	.ram_retention.entry : 
	{
		__retention_entry_func__ = .;
		KEEP(*(SORT(.retention.entry.data*)))
	} > RETENTION_RAM

	.ram_retention.text : 
	{
		__retention_text_start__ = .;
		KEEP(*(.retention.ram.text*))
		KEEP(*(.retention.ram.data*))
	} > RETENTION_RAM
}
