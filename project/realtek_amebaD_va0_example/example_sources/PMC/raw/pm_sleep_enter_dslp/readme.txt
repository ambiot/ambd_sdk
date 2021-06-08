Example Description

This example describes how to enter dslp mode from sleep mode when nothing need to do.

Procedure
(1) copy this main.c to project\realtek_amebaD_va0_example\src\src_lp\main.c
(2) register a suspend function to get km4 sleep time and if enter dslp, the file use test_suspend as the example
(3) Change the time in line 215 to choose the time you want to enter dslp mode after entering sleep mode. unit is ms.
(4) If want to wakeup from dslp for test, uncomment line 219 and line 220.

