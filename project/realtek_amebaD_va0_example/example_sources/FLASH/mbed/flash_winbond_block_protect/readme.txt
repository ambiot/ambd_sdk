Example Description

This example demonstrates how to configure the status register of Winbond to protect certain blocks, which is upper 512KB (0x180000h~0x1FFFFFh). Note that the status register should be reset
if users want to reload code. 

Be cautious!!
The definition of store array is different for Micron flash.
Size        Micron       MXIC       
4KB         Subsector    Sector
64KB        Sector       Block


