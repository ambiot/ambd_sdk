ENTRY(Reset_Handler)

INCLUDE "rlx8721d_layout.ld"

SECTIONS
{
	/* addr fixed */
	.rom.text :
	{
		KEEP(*(.vectors_table))
		KEEP(*(.vectors_table_text))
		KEEP(*(.hal.rom.text*))
		KEEP(*(.libc.rom.text*))
		KEEP(*(.apple.rom.text*))
		KEEP(*(.ssl.rom.text*))
		KEEP(*(.FW.rom.text*))
	} > IROM
	
	.rom.rodata :
	{
		. = (. + 7)&(0xFFFFFFF8);
	
		KEEP(*(.sim.rom.rodata*))
		KEEP(*(.hal.rom.rodata*))
		KEEP(*(.libc.rom.rodata*))
		KEEP(*(.apple.rom.rodata*))
		KEEP(*(.ssl.rom.rodata*))
		KEEP(*(.FW.rom.rodata*))

		/* to compatiable with IAR compiler, the rom.rodata (especial the text string) must be located at the bottom of ROM */
		KEEP(*(.rom.rodata*))

		KEEP(*(.rodata*))
	} > DROM

	/* addr fixed */
	.hal.rom.bss :
	{
		__rom_bss_start__ = .;
		KEEP(*(.ram_vector_table1))
		KEEP(*(.ram_vector_table2))
		KEEP(*(.ram_vector_table3))

		KEEP(*(.hal.rom.bss*))
		KEEP(*(.hal.rom.bank.bss*))
		KEEP(*(.libc.ram.bss*))
		KEEP(*(.ssl_ram_map*))

		/* FW BSS */
		KEEP(*(.FW.rom.bss*))
		__rom_bss_end__ = .;

	} >  ROMBSS_RAM

	/* image1 entry, this section should in RAM and fixed address for ROM */
	.ram_image1.entry :
	{
		__ram_image1_text_start__ = .;
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.image1.entry.data*)))
		KEEP(*(.image1.validate.rodata*))
		KEEP(*(.image1.export.symb*))
	} > BOOTLOADER_RAM

	/* addr not fixed, addr will change when link with RAM code */
	.ram_image1.text :
	{
		KEEP(*(.hal.ram.data*))
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
	} > BD_RAM
 	.ram.bss :
	{
    		KEEP(*(.bss*))
	} > BD_RAM
	.rom.text.libgcc : 
	{
		KEEP(*(.text*))
	} > IROM

}
