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
	} > IROM_NS
	
	.rom.rodata :
	{
		__rom_entry_ns_start__ = .;
		KEEP(*(.hal.rom.entryns.rodata*))
		__rom_entry_ns_end__ = .;

		KEEP(*(.hal.rom.rodata*))
		KEEP(*(.libc.rom.rodata*))
		KEEP(*(.apple.rom.rodata*))
		KEEP(*(.ssl.rom.rodata*))

		/* to compatiable with IAR compiler, the rom.rodata (especial the text string) must be located at the bottom of ROM */
		KEEP(*(.rom.rodata*))

		KEEP(*(.rodata*))
	} > DROM_NS

	/* addr fixed */
	.hal.rom.bss :
	{
		__rom_bss_start__ = .;

		KEEP(*(.hal.rom.bss*))
		__rom_bss_end__ = .;

	} >  ROMBSS_RAM_COM

	/* addr fixed */
	.hal.ns_rom.bss :
	{
		__rom_bss_start_ns__ = .;
		KEEP(*(.ram_vector_table1))
		KEEP(*(.ram_vector_table2))
		KEEP(*(.ram_vector_table3))
		KEEP(*(.hal.rom.bank.bss*))

		KEEP(*(.ssl_ram_map*))
		__rom_bss_end_ns__ = .;

	} >  ROMBSS_RAM_NS

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
