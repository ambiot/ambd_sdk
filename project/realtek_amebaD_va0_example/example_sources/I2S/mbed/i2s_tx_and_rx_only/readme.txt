Example Description

This example describes how to use i2s by using mbed extend api

Using TX only and RX only mode.
RX will fill buffer until full then switching to TX only mode to play buffer content.

Procedure:
  1.Plug ALC5651 shield to Ameba HDK
   
  2.Run the main function.

  3.Plug earphone to Green phone jack

  4.Plug audio source to Red phone jack
  
In this example, you can hear the Intermittent audio source from the earphone. 

Tips: To compile this example, you need to copy main.c and alc5651.c to "project\realtek_amebaD_va0_example\src\src_hp".