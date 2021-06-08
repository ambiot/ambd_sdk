ENTRY(Reset_Handler)

INCLUDE "rlx8721d_layout_tz.ld"

SECTIONS
{
	.rom.text : { } > IROM
	.rom.rodata : { } > DROM
	.hal.rom.bss : { } > ROMBSS_RAM_COM
	.hal.s_rom.bss : { } > ROMBSS_RAM_S

	/* image1: boot image start */
	/* image1 entry, this section should in RAM and fixed address for ROM */
	.ram_image1.entry :
	{
		__ram_image1_text_start__ = .;
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.image1.entry.data*)))
		KEEP(*(.image1.validate.rodata*))
		*(.image1.export.symb)
	} > BOOTLOADER_RAM_S

	/*  Add . to assign the start address of the section */ 
	/*  to prevent the change of the start address by ld doing section alignment */  
	.ram_image1.text . :
	{
		/* image1 text */
		*(.boot.ram.text*)    
		*(.boot.rodata*)
	} > BOOTLOADER_RAM_S

	.ram_image1.data . :
	{
		__ram_image1_data_start__ = .;
		KEEP(*(.boot.ram.data*))
		__ram_image1_data_end__ = .;
	
		__ram_image1_text_end__ = .;
	} > BOOTLOADER_RAM_S

	.ram_image1.bss . :
	{
		__image1_bss_start__ = .;
		KEEP(*(.boot.ram.bss*))
		KEEP(*(.boot.ram.end.bss*))
		*(.bss*)
		__image1_bss_end__ = .;
	} > BOOTLOADER_RAM_S

	.xip_image1.text :
	{
		__flash_boot_text_start__ = .;

		*(.flashboot.text*)

		__flash_boot_text_end__ = .;

		. = ALIGN(16);
	} > KM4_BOOT

	/* image2: normal image start */
	.ram_image2.entry :
	{
		__ram_image2_text_start__ = .;
		__image2_entry_func__ = .;
		KEEP(*(SORT(.image2.entry.data*)))

	} > BD_RAM_NS

	.ram_image3.text :
	{
		__ram_image3_start__ = .;
		__ram_image3_end__ = __ram_image3_start__ + LENGTH(BD_RAM_S);
	} > BD_RAM_S

	.psram_image3.text :
	{
		__psram_image3_start__ = .;
		__psram_image3_end__ = __psram_image3_start__ + LENGTH(PSRAM_S);
	} > PSRAM_S

	.xip_image2.text : 
	{
		__flash_text_start__ = .;
		__flash_img2_end__ = __flash_text_start__ + LENGTH(KM4_IMG2);
	} > KM4_IMG2
}
