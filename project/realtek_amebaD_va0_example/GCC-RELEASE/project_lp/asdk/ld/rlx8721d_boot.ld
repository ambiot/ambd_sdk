ENTRY(Reset_Handler)

INCLUDE "rlx8721d_layout.ld"

SECTIONS
{
	.rom.text : { } > IROM
	.rom.rodata : { } > DROM
	.hal.rom.bss : { } > ROMBSS_RAM

	/* image1 entry, this section should in RAM and fixed address for ROM */
	.ram_image1.entry :
	{
		__ram_image1_text_start__ = .;
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.image1.entry.data*)))
		KEEP(*(.image1.validate.rodata*))
		KEEP(*(.image1.rodata*))
	} > BOOTLOADER_RAM

	/*  Add . to assign the start address of the section */ 
	/*  to prevent the change of the start address by ld doing section alignment */  
	.ram_image1.text . :
	{
		/* image1 text */
		*(.boot.ram.text*)    
		*(.boot.rodata*)
	} > BOOTLOADER_RAM

	.ram_image1.data . :
	{
		__ram_image1_data_start__ = .;
		KEEP(*(.boot.ram.data*))
		__ram_image1_data_end__ = .;
	
		__ram_image1_text_end__ = .;
	} > BOOTLOADER_RAM

	.ram_image1.bss . :
	{
		__image1_bss_start__ = .;
		KEEP(*(.boot.ram.bss*))
		KEEP(*(.boot.ram.end.bss*))
		*(.bss*)
		__image1_bss_end__ = .;
	} > BOOTLOADER_RAM

	.xip_image1.text :
	{
		__flash_boot_text_start__ = .;

		*(.flashboot.text*)
		*(.text*)

		__flash_boot_text_end__ = .;

		. = ALIGN(16);
	} > KM0_BOOT

	.ram_image2.entry :
	{
		__ram_image2_text_start__ = .;
		__image2_entry_func__ = .;

	} > BD_RAM

	__ls_flash_text_start__ = ORIGIN(KM0_IMG2);
	__hs_flash_text_start__ = ORIGIN(KM4_IMG2);
}
