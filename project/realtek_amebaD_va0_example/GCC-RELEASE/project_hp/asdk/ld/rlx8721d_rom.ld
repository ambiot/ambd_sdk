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
		KEEP(*(.dsp.rom.text*))
	} > IROM
	
	.rom.rodata :
	{
	
		KEEP(*(.hal.rom.rodata*))
		KEEP(*(.libc.rom.rodata*))
		KEEP(*(.apple.rom.rodata*))
		KEEP(*(.ssl.rom.rodata*))

		/* to compatiable with IAR compiler, the rom.rodata (especial the text string) must be located at the bottom of ROM */
		KEEP(*(.rom.rodata*))

		KEEP(*(.rodata*))
	} > DROM

	/* addr fixed */
	.hal.rom.bss :
	{
		__rom_bss_start__ = .;

		KEEP(*(.hal.rom.bss*))
		__rom_bss_end__ = .;

	} >  ROMBSS_RAM_COM

	/* addr fixed */
	.hal.s_rom.bss :
	{
		__rom_bss_start_s__ = .;
		KEEP(*(.ram_vector_table1))
		KEEP(*(.ram_vector_table2))
		KEEP(*(.ram_vector_table3))
		KEEP(*(.hal.rom.bank.bss*))

		KEEP(*(.ssl_ram_map*))
		__rom_bss_end_s__ = .;

	} >  ROMBSS_RAM_S

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
