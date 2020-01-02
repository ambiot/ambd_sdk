Example Description

This example describes how to use Bod Brown-Out interrupt mode or reset mode.

Requirement Components:
    a USB to TTL Adapter

Operating process: 
   For BOD interrupt mode (#define BOD_INTR_MODE in line 13 of main.c)
 - Remove R43 on the demo board
 - Give 3.3V at pin that near the chip of J38 by power supply.
 - Boot up device, and you will see the log "Supply 2.50V voltage will cause bod interrupt!!!"
 - Change 3.3V to 1.85V-2.60V to trigger Bod Interrupt, and will call the registered "bor_intr_Handler"
 - Recover voltage to above 2.9V

   For BOD interrupt mode (#unfine BOD_INTR_MODE in line 13 of main.c)
 - Remove R43 on the demo board
 - Give 3.3V at pin that near the chip of J38 by power supply.
 - Boot up device, and you will see the log "Supply 2.1V voltage and then recover voltage to above 2.5V will cause bod reset!!!"
 - Change 3.3V to 1.85V-2.10V to trigger Bod Reset, and recover voltage to above 2.5V to reset chip
 - You can see reset log "BOOT_Reason:40000 200000", the first value "0x40000" means BOD reset

Note: 
 - Never give 3.3V at the other pin of J38


