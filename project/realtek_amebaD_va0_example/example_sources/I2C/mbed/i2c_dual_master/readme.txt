Example Description

This example describes how to use i2c by using mbed api

1.This test needs two demo board, one as master and the other as slave

2.The codes of Master and Slave are distinguished by the define of macro 'I2C_MASTER_DEVICE' in the code
3.Connect LOG-UART connector to PC
  
4.Connect 
  - Master board I2C0 SDA (PA_26) to Slave board I2C0 SDA (PA_26) pin,
  - Master board I2C0 SCL (PA_25) to Slave board I2C0 SCL (PA_25) pin.
  
5.First run Slave and then Master.

6.Get the Master and Slave Data.

