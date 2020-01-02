Example Description

This example describes how to use SPI GDMA single-block continue TX.

The SPI Interface provides a "Serial Peripheral Interface" Master.

This interface can be used for communication with SPI slave devices,
such as FLASH memory, LCD screens and other modules or integrated circuits.

In this example, SPI1 as master,and use pinmux S1.
So pinmux as below:
    SPI1_MOSI (PB_4)
    SPI1_MISO (PB_5)
    SPI1_SCLK (PB_6)
    SPI1_CS   (PB_7)

Note:
	1) This example aims to demonstrate how the spi master continue TX use use single GDMA blocks.
	2) Data array send times can be set through Macro define.