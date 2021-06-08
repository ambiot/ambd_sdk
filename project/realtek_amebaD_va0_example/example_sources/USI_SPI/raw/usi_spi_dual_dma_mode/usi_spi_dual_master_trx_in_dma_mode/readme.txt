Example Description

This example describes how to use USI SPI read/write as Master.

The USI SPI Interface provides a "Universal Serial Interface" SPI Master.

This interface can be used for communication with USI SPI slave devices.

So we connect them as below:
    master's MOSI (PA_25) connect to slave's MOSI (PA_25)
    master's MISO (PA_26) connect to slave's MISO (PA_26)
    master's SCLK (PA_30) connect to slave's SCLK (PA_30)
    master's CS   (PA_28) connect to slave's CS  (PA_28) 

After boot up, the master will send data to slave and receive date from slave. Results will be displayed on LOG_OUT.

Note:
1. for dma mode, both CPU and dma have access to usi spi buffer. Start address of usi spi buffer should be 32-byte aligned and size of usi spi buffer should be multiple of 32 byte.