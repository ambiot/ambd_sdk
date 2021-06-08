#include <basic_types.h>
#include <section_config.h>

/* const is read only, it will build into flash */
const u32 xip_test_read_only_data = 0;

/* non read only data will build into SRAM */
u32 xip_test_data = 0;

/* code in in SRAM */
IMAGE2_RAM_TEXT_SECTION
void test_critical_code(void)
{

}

/* code in in Flash */
void test_non_critical_code(void)
{

}
