Example Description

This example describes how to use i2c interrupt mode by using mbed api

1.This test needs two demo board, one as master and the other as slave

2.The codes of Master and Slave are distinguished by the define of macro 'I2C_MASTER_DEVICE' in the code

3.The codes of Master send Slave read mode and Master read Slave send mode are distinguished by the define of macro 'MASTER_SEND' in the code

4.Connect LOG-UART connector to PC
  
5.Connect 
  - Master board I2C0 SDA (PA_26) to Slave board I2C0 SDA (PA_26) pin,
  - Master board I2C0 SCL (PA_25) to Slave board I2C0 SCL (PA_25) pin.
  
6.First run Slave and then Master.

7.Get the Master and Slave Data.

