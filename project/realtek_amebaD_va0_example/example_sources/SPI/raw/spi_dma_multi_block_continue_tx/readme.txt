Example Description

This example describes how to use SPI GDMA multi-block continue TX.

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
	1) This example aims to demonstrate how the spi master continue TX use use multi GDMA blocks.
	2) Data array send times can be set through Macro define.
	3) For dma mode, both CPU and dma have access to spi buffer. Start address of spi buffer should be 32-byte aligned and size of spi buffer should be multiple of 32 byte.