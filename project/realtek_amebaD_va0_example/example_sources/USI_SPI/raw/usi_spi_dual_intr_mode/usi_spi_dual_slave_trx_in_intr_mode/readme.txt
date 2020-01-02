Example Description

This example describes how to use USI SPI read/write as Slave.

The USI SPI Interface provides a "Universal Serial Interface" SPI Slave.

This interface can be used for communication with USI SPI master devices.

So we connect them as below:
    master's MOSI (PA_25) connect to slave's MOSI (PA_25)
    master's MISO (PA_26) connect to slave's MISO (PA_26)
    master's SCLK (PA_30) connect to slave's SCLK (PA_30)
    master's CS   (PA_28) connect to slave's CS  (PA_28) 

After boot up, the slave will send data to slave and receive date from slave. Results will be displayed on LOG_OUT.