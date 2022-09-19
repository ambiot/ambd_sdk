#include <FreeRTOS.h>
#include <task.h>
#include <platform/platform_stdlib.h>
#include <basic_types.h>
#include <platform_opts.h>
#include <dct/example_dct.h>
#if defined(CONFIG_PLATFORM_8721D)
#include <dct.h>
#else
#include <dct/dct.h>
#endif

#if CONFIG_EXAMPLE_DCT

#define DCT_BEGIN_ADDR          0x100000    // DCT begin address of flash, ex: 0x100000 = 1M
#define MODULE_NUM              6           // max number of module

#if defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8721D)
#if MODULE_NUM > 6
#error "defult max DCT size is 24k(change DCT_BEGIN_ADDR in platform_opts.h), module size is 4k, max module number is 6; if backup enabled, the total module number is 6 + 1*6 = 12, the size is 48k; if wear leveling enabled, the total module number is 6 + 2*6 + 3*6 = 36, the size is 144k"
#endif
#endif

#define VARIABLE_NAME_SIZE      32       // max size of the variable name
#define VARIABLE_VALUE_SIZE     128 + 4  // max size of the variable value
#define ENABLE_BACKUP           1        // enable backup function to backup module, it need double module size
#define ENABLE_WEAR_LEVELING    0        // enable wear leveling function, it need sextuple module size
                                         // max value number in each moudle = 4024 / (32 + 128+4) = 24

static char example_dct_module[]  = "dct_test_module";
static char example_dct_string[]  = "string";
static char example_dct_u32[]     = "u32";
static char example_dct_bool[]    = "bool";
static char example_dct_binary[]  = "binary";
static char example_dct_string0[] = "aaabbbccc";

void example_dct_thread(void* param){
	int32_t			ret = -1;
	dct_handle_t	dct_handle;
	char			value[16];
	char			variable_name_array[VARIABLE_NAME_SIZE];

	// initial DCT
	ret = dct_init(DCT_BEGIN_ADDR, MODULE_NUM, VARIABLE_NAME_SIZE, VARIABLE_VALUE_SIZE, ENABLE_BACKUP, ENABLE_WEAR_LEVELING);

	// register module
	ret = dct_register_module(example_dct_module);

	// open module
	ret = dct_open_module(&dct_handle, example_dct_module);

	if(ret == DCT_SUCCESS){

		ret = dct_remain_variable(&dct_handle);
		if(ret > 0)
			printf("Remaining variable amount:%d\n", ret);

		// set test variable 0
		ret = dct_set_variable(&dct_handle, example_dct_string, example_dct_string0);
		if(ret == DCT_SUCCESS)
			printf("dct_set_variable: %s = %s\n", example_dct_string, example_dct_string0);

		// get value of test variable 0
		memset(value, 0, sizeof(value));
		ret = dct_get_variable(&dct_handle, example_dct_string, value, sizeof(value));
		if(ret == DCT_SUCCESS)
			printf("dct_get_variable: %s = %s\n", example_dct_string, value);

		// delete test variable 0
		ret = dct_delete_variable(&dct_handle, example_dct_string);

		// get value of test variable 0
		memset(value, 0, sizeof(value));
		ret = dct_get_variable(&dct_handle, example_dct_string, value, sizeof(value));
		if(ret == DCT_ERR_NOT_FIND)
			printf("Delete %s success.\n", example_dct_string);

		// get variable remaining amount
		ret = dct_remain_variable(&dct_handle);
		if(ret > 0)
			printf("Remaining variable amount:%d\n", ret);

		// u32
		uint32_t i = 65535,j=0;
		uint16_t len = sizeof(i);

		ret = dct_set_variable_new(&dct_handle, example_dct_u32, (char*)&i, len);
		if(ret == DCT_SUCCESS)
			printf("dct_set_variable_new: %s = %d\n", example_dct_u32, i);

		ret = dct_get_variable_new(&dct_handle, example_dct_u32, (char*)&j, &len);
		if(ret == DCT_SUCCESS)
			printf("dct_get_variable_new: %s = %d\n", example_dct_u32, j);

		printf("dct_remain_variable = %d\n", dct_remain_variable(&dct_handle));

		ret = dct_delete_variable(&dct_handle, example_dct_u32);
		if(ret == DCT_SUCCESS)
			printf("dct_delete_variable: %s\n", example_dct_u32);

		ret = dct_remain_variable(&dct_handle);
		if(ret > 0)
			printf("Remaining variable amount:%d\n", ret);

		// bool
		bool a=1,b=0;
		len = sizeof(a);
		ret = dct_set_variable_new(&dct_handle, example_dct_bool, (char*)&a, len);
		if(ret == DCT_SUCCESS)
			printf("dct_set_variable_new: %s = %d\n", example_dct_bool, a);

		ret = dct_get_variable_new(&dct_handle, example_dct_bool, (char*)&b, &len);
		if(ret == DCT_SUCCESS)
			printf("dct_get_variable_new: %s = %d\n", example_dct_bool, b);

		ret = dct_remain_variable(&dct_handle);
		if(ret > 0)
			printf("Remaining variable amount:%d\n", ret);

		ret = dct_delete_variable(&dct_handle, example_dct_bool);
		if(ret == DCT_SUCCESS)
			printf("dct_delete_variable: %s\n", example_dct_bool);

		ret = dct_remain_variable(&dct_handle);
		if(ret > 0)
			printf("Remaining variable amount:%d\n", ret);

		// binary
		uint8_t bb[VARIABLE_VALUE_SIZE-4],cc[VARIABLE_VALUE_SIZE-4];

		for(i=0; i<(VARIABLE_VALUE_SIZE-4); i++){
			bb[i] = i%256;
			cc[0] = 0;
		}

		printf("bb = ");
		for(i=0; i<(VARIABLE_VALUE_SIZE-4); i++)
		{
		  printf("%d ",bb[i]);
		  if(i%255==0)
			 printf("\n");
		}
		printf("\n\n\n");

		len = sizeof(bb);
		ret = dct_set_variable_new(&dct_handle, example_dct_binary, (char*)&bb, len);
		if(ret == DCT_SUCCESS)
			printf("dct_set_variable_new: %s\n", example_dct_binary);

		ret = dct_get_variable_new(&dct_handle, example_dct_binary, (char*)&cc, &len);
		if(ret == DCT_SUCCESS)
			printf("dct_get_variable_new: %s\n", example_dct_binary);

		printf("cc = ");
		for(i=0; i<(VARIABLE_VALUE_SIZE-4); i++)
		{
		  printf("%d ",cc[i]);
		  if(i%255==0)
			 printf("\n");
		}
		printf("\n\n\n");

		// dump variable_number, variable_name in module
		int x = 0;
		uint16_t item_num = 0;
		item_num = dct_get_variable_num(&dct_handle);
		for(x=0; x < item_num; x++)
		{
			memset(variable_name_array, 0 , VARIABLE_NAME_SIZE + 1);
			dct_get_variable_name(&dct_handle, x, variable_name_array);
            printf("dct_dump_variable[%d] = %s\n", x, variable_name_array);
		}

		// close module
		ret = dct_close_module(&dct_handle);
	}

	vTaskDelete(NULL);
}


void example_dct(void)
{
	if(xTaskCreate(example_dct_thread, ((const char*)"example_dct_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_dct_thread) failed", __FUNCTION__);
}

#endif // #if CONFIG_DCT
