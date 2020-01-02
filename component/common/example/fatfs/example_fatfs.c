#include "FreeRTOS.h"
#include "task.h"
#include <platform/platform_stdlib.h>
#include "basic_types.h"
#include "platform_opts.h"
#include "section_config.h"

#if CONFIG_EXAMPLE_FATFS

#if CONFIG_FATFS_EN
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>

/* Config for Ameba-1 */
#if defined(CONFIG_PLATFORM_8195A) || defined(CONFIG_PLATFORM_8710C)
#if FATFS_DISK_USB
    #include "usb.h"
    #include <disk_if/inc/usbdisk.h>
    #define STACK_SIZE		2048
#elif FATFS_DISK_SD
    #include "sdio_combine.h"
    #include "sdio_host.h"
    #include <disk_if/inc/sdcard.h>
    #define STACK_SIZE		2048

//#if (_USE_MKFS != 1)
//	#error define _USE_MKFS MACRO to 1 in ffconf.h to enable f_mkfs() which creates FATFS volume on Flash.
//#endif

#elif FATFS_DISK_FLASH
#if (_MAX_SS != 4096)
	#error set _MAX_SS to 4096 in ffconf.h to define maximum supported range of sector size for flash memory. See the description below the MACRO for details.
#endif
#if (_USE_MKFS != 1)
	#error define _USE_MKFS MACRO to 1 in ffconf.h for on-board flash memory to enable f_mkfs() which creates FATFS volume on Flash.
#endif
#include "flash_api.h"
#include <disk_if/inc/flash_fatfs.h>
#define STACK_SIZE		4096
#endif

#define TEST_SIZE       512

#if defined(CONFIG_PLATFORM_8195A)
SRAM_BF_DATA_SECTION u8 WRBuf[TEST_SIZE];
SRAM_BF_DATA_SECTION u8 RDBuf[TEST_SIZE];
#else
u8 WRBuf[TEST_SIZE];
u8 RDBuf[TEST_SIZE];
#endif
#endif // defined(CONFIG_PLATFORM_8195A)

/* Config for Ameba-Pro */
#if defined(CONFIG_PLATFORM_8195BHP)
#define STACK_SIZE		4096
#if FATFS_DISK_SD

#include "sdio_combine.h"
#include "sdio_host.h"
#include <disk_if/inc/sdcard.h>
#include "fatfs_sdcard_api.h"
#endif

#if FATFS_DISK_FLASH
#if (_MAX_SS != 4096)
	#error set _MAX_SS to 4096 in ffconf.h to define maximum supported range of sector size for flash memory. See the description below the MACRO for details.
#endif
#if (_USE_MKFS != 1)
	#error define _USE_MKFS MACRO to 1 in ffconf.h for on-board flash memory to enable f_mkfs() which creates FATFS volume on Flash.
#endif
#include "flash_api.h"
#include <disk_if/inc/flash_fatfs.h>
#include "fatfs_flash_api.h"
#endif

#if FATFS_DISK_SD && FATFS_DISK_FLASH
#if (_VOLUMES != 2)
	#error set _VOLUMES to 2 in ffconf.h to support dual file system.
#endif
#endif
#endif // defined(CONFIG_PLATFORM_8195BHP)

#if defined(CONFIG_PLATFORM_8721D)
#if FATFS_DISK_SD
#include <disk_if/inc/sdcard.h>
#elif FATFS_DISK_USB
#include "usb.h"
#include <disk_if/inc/usbdisk.h>
_Sema       us_sto_rdy_sema;
#elif FATFS_DISK_FLASH
#if (_MAX_SS != 4096)
	#error set _MAX_SS to 4096 in ffconf.h to define maximum supported range of sector size for flash memory. See the description below the MACRO for details.
#endif
#if (_USE_MKFS != 1)
	#error define _USE_MKFS MACRO to 1 in ffconf.h for on-board flash memory to enable f_mkfs() which creates FATFS volume on Flash.
#endif
#include "flash_api.h"
#include <disk_if/inc/flash_fatfs.h>
#endif

#if FATFS_DISK_FLASH
#define STACK_SIZE		4096
#else
#define STACK_SIZE		2048
#endif
#define TEST_SIZE		(512)

u8 WRBuf[TEST_SIZE];
u8 RDBuf[TEST_SIZE];
#endif // defined(CONFIG_PLATFORM_8721D)


FRESULT list_files(char *);
FRESULT del_dir(const TCHAR *path, int del_self);  
FATFS 	fs_sd;
FIL     m_file;
/*
SECTION(".lpddr.rodata")
u8 WRBuf[TEST_SIZE]__attribute__((aligned(32)));
SECTION(".lpddr.rodata")
u8 RDBuf[TEST_SIZE]__attribute__((aligned(32)));
*/
#if defined(CONFIG_PLATFORM_8195BHP)
#define TEST_BUF_SIZE	(512)

#if FATFS_DISK_SD
fatfs_sd_params_t fatfs_sd;
#endif
#if FATFS_DISK_FLASH
fatfs_flash_params_t fatfs_flash;
#endif

#if 0
static char cBuffer[512];

#define FATFS_BUF_SIZE (1024*1024/2)
SECTION(".lpddr.rodata")
u8 fatfs_buf[FATFS_BUF_SIZE]__attribute__((aligned(32)));
u32 fatfs_buf_pos = 0;

int fatfs_buffer_write(char* data, u32 len)
{
        int res = 0;
        int bw;
        int offset = 0;
        
        printf("frame_size %d\n\r",len);
        
        while (len >0) {
                if (fatfs_buf_pos + len >= FATFS_BUF_SIZE) {
                        memcpy(fatfs_buf + fatfs_buf_pos, data+offset, FATFS_BUF_SIZE-fatfs_buf_pos);
                        
                        res = f_write(&m_file, fatfs_buf, FATFS_BUF_SIZE, (u32*)&bw);
                        if(res){
                                printf("res = %d\n\r",res);
                                f_lseek(&m_file, 0); 
                                printf("Write error.\n\r");
                        }
                        //printf("Write %d bytes.\n\r", bw);
                        
                        offset += FATFS_BUF_SIZE-fatfs_buf_pos;
                        len -= FATFS_BUF_SIZE-fatfs_buf_pos;
                        fatfs_buf_pos = 0;
                }
                else {
                        memcpy(fatfs_buf + fatfs_buf_pos, data+offset, len);
                        fatfs_buf_pos = fatfs_buf_pos + len;
                        len = 0;
                }
        }
        
        return 0;
}
#endif

void example_fatfs_thread(void* param){

	int Fatfs_ok = 1;
    int ret_flash_mount, ret_flash_test;
	int sd_drv_num, flash_drv_num;

	//root diretory
	char	sd_drv[4]; 	
	char	flash_drv[4];

    u8 WRBuf[TEST_BUF_SIZE];
    u8 RDBuf[TEST_BUF_SIZE];

	u8 test_info[]="\"Ameba test dual fatfs sd card ~~~~\"";
	u8 test_info2[]="\"Ameba test dual fatfs flash ~~~~\"";
        
	FRESULT res; 
	DIR		m_dir;

	char path[64];
	char path_dir[64];
	char sd_fn[64] = "sd_file.txt";
	char sd_dir[64] = "sd_dir";
	char flash_fn[64] = "flash_file.txt";
    char flash_test_fn[64] = "flash_drive_test.txt";
	char flash_dir[64] = "flash_dir";
	int br,bw;
	int ret = 0;
                
	printf("=== FATFS Example ===\n\r");

#if FATFS_DISK_SD
	res = fatfs_sd_init();
	if(res < 0){
		printf("fatfs_sd_init fail (%d)\n", res);
		Fatfs_ok = 0;
		goto fail;
	}
	fatfs_sd_get_param(&fatfs_sd);
#endif
#if FATFS_DISK_FLASH
	res = fatfs_flash_init();
	if(res < 0){
		printf("fatfs_flash_init fail (%d)\n", res);
		Fatfs_ok = 0;
		goto fail;
	}
	fatfs_flash_get_param(&fatfs_flash);
#endif	

	if(Fatfs_ok){
		
		//printf("FatFS Write/Read test begin......\n\n");

		printf("\n\r=== Clear files ===\n\r");
#if FATFS_DISK_SD
		del_dir(fatfs_sd.drv, 0);
		printf("List files in SD card: %s\n\r", fatfs_sd.drv);
		res = list_files(fatfs_sd.drv);
		if(res){
			printf("list all files in SD card fail (%d)\n\r", res);
		}
		printf("\n\r");
#endif
#if FATFS_DISK_FLASH
		del_dir(fatfs_flash.drv, 0);
		printf("List files in flash: %s\n\r", fatfs_flash.drv);
		res = list_files(fatfs_flash.drv);
		if(res){
			printf("list all files in flash fail (%d)\n\r", res);
		}
		printf("\n\r");
#endif

#if FATFS_DISK_SD
// SD test
		printf("\n\r=== SD card FS Read/Write test ===\n\r");
		// file write & read test
		strcpy(path, fatfs_sd.drv);
		sprintf(&path[strlen(path)],"%s",sd_fn);
		
		res = f_open(&m_file, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
		if(res){
			printf("open file (%s) fail.\n", sd_fn);
			goto exit;
		}

		printf("Test file name: %s\n\n",sd_fn);

		memset(&WRBuf[0], 0x00, TEST_BUF_SIZE);
		memset(&RDBuf[0], 0x00, TEST_BUF_SIZE);
		
		strcpy(&WRBuf[0], &test_info[0]);
		
		do{
			res = f_write(&m_file, WRBuf, strlen(WRBuf), (u32*)&bw);
			if(res){
				f_lseek(&m_file, 0); 
				printf("Write error.\n");
			}
			printf("Write %d bytes.\n", bw);
		} while (bw < strlen(WRBuf));

		printf("Write content:\n%s\n", WRBuf);
		printf("\n");
		
		/* move the file pointer to the file head*/
		res = f_lseek(&m_file, 0); 

		do{
			res = f_read(&m_file, RDBuf, strlen(WRBuf), (u32*)&br);
			if(res){
				f_lseek(&m_file, 0);
				printf("Read error.\n");
			}
			printf("Read %d bytes.\n", br);
		}while(br < strlen(WRBuf));
	
		printf("Read content:\n%s\n", RDBuf);

		// close source file
		res = f_close(&m_file);
		if(res){
			printf("close file (%s) fail.\n", sd_fn);
		}
		printf("\n");

		// mkdir test
		memset(path_dir, 0, sizeof(path_dir)); 
		snprintf(path_dir, sizeof(path_dir), "%s%s", fatfs_sd.drv, sd_dir);		
		printf("Create directory: %s \n\r", path_dir);
		f_mkdir(path_dir);		
#endif
#if FATFS_DISK_FLASH
// Flash test
		printf("\n\r=== Flash FS Read/Write test ===\n\r");
		// file write & read test
		strcpy(path, fatfs_flash.drv);
		sprintf(&path[strlen(path)],"%s",flash_fn);
				
		res = f_open(&m_file, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
		if(res){
			printf("open file (%s) fail.\n", flash_fn);
			goto exit;
		}
		
		printf("Test file name: %s\n\n",flash_fn);

		memset(&WRBuf[0], 0x00, TEST_BUF_SIZE);
		memset(&RDBuf[0], 0x00, TEST_BUF_SIZE);
				
		strcpy(&WRBuf[0], &test_info2[0]);
				
		do{
			res = f_write(&m_file, WRBuf, strlen(WRBuf), (u32*)&bw);
			if(res){
				f_lseek(&m_file, 0); 
				printf("Write error.\n");
			}
			printf("Write %d bytes.\n", bw);
		} while (bw < strlen(WRBuf));
		
		printf("Write content:\n%s\n", WRBuf);
		printf("\n");
				
		/* move the file pointer to the file head*/
		res = f_lseek(&m_file, 0); 

		do{
			res = f_read(&m_file, RDBuf, strlen(WRBuf), (u32*)&br);
			if(res){
				f_lseek(&m_file, 0);
				printf("Read error.\n");
			}
				printf("Read %d bytes.\n", br);
		}while(br < strlen(WRBuf));
			
		printf("Read content:\n%s\n", RDBuf);
		
		// close source file
		res = f_close(&m_file);
		if(res){
			printf("close file (%s) fail.\n", flash_fn);
		}
		printf("\n");
		
		// mkdir test
		memset(path_dir, 0, sizeof(path_dir)); 
		snprintf(path_dir, sizeof(path_dir), "%s%s", fatfs_flash.drv, flash_dir);		
		printf("Create directory: %s \n\r", path_dir);
		f_mkdir(path_dir);
#endif		

		// List all files
		printf("\n\r=== List files ===\n\r");
#if FATFS_DISK_SD
		printf("List files in SD card: %s\n\r", fatfs_sd.drv);
		res = list_files(fatfs_sd.drv);
		if(res){
			printf("list all files in SD card fail (%d)\n\r", res);
		}
		printf("\n\r");
#endif
#if FATFS_DISK_FLASH
		printf("List files in flash: %s\n\r", fatfs_flash.drv);
		res = list_files(fatfs_flash.drv);
		if(res){
			printf("list all files in flash fail (%d)\n\r", res);
		}
		printf("\n\r");
#endif	
	
	}
	
fail:
#if FATFS_DISK_SD
	fatfs_sd_close();
#endif
#if FATFS_DISK_FLASH
	fatfs_flash_close();
#endif	

exit:
	vTaskDelete(NULL);
}
#endif

#if defined(CONFIG_PLATFORM_8195A) || defined(CONFIG_PLATFORM_8710C)
void example_fatfs_thread(void* param){
   
	int a = 0;
	int drv_num = 0;
	int Fatfs_ok = 0;

	FRESULT res; 
	FATFS 	m_fs;
	FIL		m_file;	
#ifdef FATFS_R_13C
	const size_t workbuf_size = 4096;
	void *workbuf = NULL;
#endif
	char	logical_drv[4]; /* root diretor */
	char path[64], path_list[64];
	char filename[64] = "TEST.TXT";
	int br,bw;
	int test_result = 1;
	int ret = 0;
	int flash = 0;

	//1 init disk drive
	printf("Init Disk driver.\n");
#if FATFS_DISK_SD
	sdio_driver_init();
#endif
#if FATFS_DISK_USB	
	_usb_init();
	ret = wait_usb_ready();
	if(ret != USB_INIT_OK){
		if(ret == USB_NOT_ATTACHED)
			printf("\r\n NO USB device attached\n");
		else
			printf("\r\n USB init fail\n");
		goto exit;
	}

#elif FATFS_DISK_SD
	// Set sdio debug level
	DBG_INFO_MSG_OFF(_DBG_SDIO_);  
	DBG_WARN_MSG_OFF(_DBG_SDIO_);
	DBG_ERR_MSG_ON(_DBG_SDIO_);
	
	//if(sdio_init_host()!=0){
        hal_sdio_host_adapter_t *psdioh_adapter;
        sdioh_pin_sel_t pin_sel;
        if(sdio_sd_host_init_combine(psdioh_adapter,pin_sel)!=0){

		printf("SDIO host init fail.\n");
		goto exit;
	}
#endif

	//1 register disk driver to fatfs
	printf("Register disk driver to Fatfs.\n");
#if FATFS_DISK_USB	
	drv_num = FATFS_RegisterDiskDriver(&USB_disk_Driver);
#elif FATFS_DISK_SD
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
	u8 test_info[]="\"Ameba test fatfs sd card ~~~~\"";
#elif FATFS_DISK_FLASH
	drv_num = FATFS_RegisterDiskDriver(&FLASH_disk_Driver);
	u8 test_info[]="\"Ameba test fatfs flash~~~~\"";
	flash = 1;
#endif

	if(drv_num < 0){
		printf("Register disk driver to FATFS fail.\n");
	}else{
		Fatfs_ok = 1;

		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}
	//1 Fatfs write and read test 
	if(Fatfs_ok){

		printf("FatFS Write/Read test begin......\n\n");
		
		res = f_mount(&m_fs, logical_drv, 1);
		if(res && flash){
#ifdef FATFS_R_13C
			workbuf = malloc(workbuf_size);
			if (workbuf == NULL) {
				printf("Error no memory for working buffer.\n");
				goto fail;
			}
			if(f_mkfs(logical_drv, FM_FAT32, 4096, workbuf, workbuf_size)!= FR_OK){
#else
			if(f_mkfs(logical_drv, 1, 4096)!= FR_OK){
#endif
				printf("Create FAT volume on Flash fail.\n");
				goto fail;
			}
			if(f_mount(&m_fs, logical_drv, 0)!= FR_OK){
				printf("FATFS mount logical drive on Flash fail.\n");
				goto fail;
 			}
		}
		else {
			if(res) {
				printf("FATFS mount logical drive fail.\n");
				goto fail;
 			}
		}

		// write and read test
		strcpy(path, logical_drv);

		sprintf(&path[strlen(path)],"%s",filename);

		//Open source file
		res = f_open(&m_file, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
		if(res){
			printf("open file (%s) fail.\n", filename);
			goto fail;
		}

		printf("Test file name:%s\n\n",filename);

		// clean write and read buffer
		memset(&WRBuf[0], 0x00, TEST_SIZE);
		memset(&RDBuf[0], 0x00, TEST_SIZE);
		
		strcpy(&WRBuf[0], &test_info[0]);
		
		do{
			res = f_write(&m_file, WRBuf, strlen(WRBuf), (u32*)&bw);
			if(res){
				f_lseek(&m_file, 0); 
				printf("Write error.\n");
			}
			printf("Write %d bytes.\n", bw);
		} while (bw < strlen(WRBuf));

		printf("Write content:\n%s\n", WRBuf);
		printf("\n");
		
		/* move the file pointer to the file head*/
		res = f_lseek(&m_file, 0); 

		do{
			res = f_read(&m_file, RDBuf, strlen(WRBuf), (u32*)&br);
			if(res){
				f_lseek(&m_file, 0);
				printf("Read error.\n");
			}
			printf("Read %d bytes.\n", br);
		}while(br < strlen(WRBuf));
	
		printf("Read content:\n%s\n", RDBuf);

		// close source file
		res = f_close(&m_file);
		if(res){
			printf("close file (%s) fail.\n", filename);
		}

		// List all files
		memset(path_list, 0x00, 64);
		strcpy(path_list, logical_drv);
		printf("List all files\n");
		res = list_files(path_list);
		if(res){
			printf("list all files fail");
		}

		//
#ifdef FATFS_R_13C
		if(f_mount(NULL, logical_drv, 0) != FR_OK){
#else
		if(f_mount(NULL, logical_drv, 1) != FR_OK){
#endif
			printf("FATFS unmount logical drive fail.\n");
		}
		
		if(FATFS_UnRegisterDiskDriver(drv_num))	
			printf("Unregister disk driver from FATFS fail.\n");
	}

fail:
#ifdef FATFS_R_13C
    if(flash && (workbuf != NULL))
		free(workbuf);	
#endif
#if FATFS_DISK_USB	
	// deinit usb driver
#elif FATFS_DISK_SD
	//sdio_deinit_host();
	deinit_combine(psdioh_adapter);
#endif
exit:
	vTaskDelete(NULL);
}
#endif

#if defined(CONFIG_PLATFORM_8721D)
void example_fatfs_thread(void* param){
   
	int a = 0;
	int drv_num = 0;
	int Fatfs_ok = 0;

	FRESULT res; 
	FATFS	m_fs;
	FIL 	m_file;

	char	logical_drv[4]; /* root diretor */
	char path[64];
	char filename[64] = "TEST.TXT";
	int br,bw;
	int test_result = 1;
	int ret = 0;
	int flash = 0;
	u8 test_info[]="\"Ameba test fatfs sd card ~~~~\"";

#if FATFS_DISK_USB
	_usb_init();
	ret = wait_usb_ready();
	if(ret != USB_INIT_OK){
		if(ret == USB_NOT_ATTACHED)
			printf("\r\n NO USB device attached\n");
		else
			printf("\r\n USB init fail\n");
		goto exit;
	}
	usb_hcd_post_init();
	rtw_init_sema(&us_sto_rdy_sema, 0);
#elif FATFS_DISK_SD
	ConfigDebug[LEVEL_ERROR] |= BIT(MODULE_SDIO);
	ConfigDebug[LEVEL_WARN] |= BIT(MODULE_SDIO);
#endif
	//1 register disk driver to fatfs
	printf("Register disk driver to Fatfs.\n");
#if FATFS_DISK_USB
	drv_num = FATFS_RegisterDiskDriver(&USB_disk_Driver);
#elif FATFS_DISK_SD
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
#elif FATFS_DISK_FLASH
	drv_num = FATFS_RegisterDiskDriver(&FLASH_disk_Driver);
#endif

	if(drv_num < 0){
		printf("Rigester disk driver to FATFS fail.\n");
	}else{
		Fatfs_ok = 1;

		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}
	//1 Fatfs write and read test 
	if(Fatfs_ok){

		printf("FatFS Write/Read test begin......\n\n");
		
		res = f_mount(&m_fs, logical_drv, 1);
		if(res) {
 #if FATFS_DISK_FLASH
			if(f_mkfs(logical_drv, 1, 4096)!= FR_OK){
				printf("Create FAT volume on Flash fail.\n");
				goto exit;
			}
			if(f_mount(&m_fs, logical_drv, 0)!= FR_OK){
				printf("FATFS mount logical drive on Flash fail.\n");
				goto exit;
 			}
#elif FATFS_DISK_SD
			/*check  if there is a file system. if not, it take about 15 seconds to f_mkfs.*/
			if(res == FR_NO_FILESYSTEM ){
				res = f_mount(&m_fs, logical_drv, 0);
				if(res) {
					printf("FATFS mount logical drive fail.\n");
					goto exit;
				}

				res = f_mkfs(logical_drv, 0, 4096);
				if(res!= FR_OK){	
					printf("Create FAT volume fail.\n");				
					goto exit;
				}

				res = f_mount(&m_fs, logical_drv, 1);
				if(res) {
					printf("FATFS mount logical drive fail.\n");
					goto exit;
				}
	
			}else{
				printf("FATFS mount logical drive fail.\n");
				goto exit;
			}
#else
			printf("FATFS mount logical drive fail.\n");
			goto exit;
#endif
		}

		// write and read test
		strcpy(path, logical_drv);

		sprintf(&path[strlen(path)],"%s",filename);

		//Open source file
		res = f_open(&m_file, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
		if(res){
			printf("open file (%s) fail.\n", filename);
			goto exit;
		}

		printf("Test file name:%s\n\n",filename);

		// clean write and read buffer
		memset(&WRBuf[0], 0x00, TEST_SIZE);
		memset(&RDBuf[0], 0x00, TEST_SIZE);

		strcpy(&WRBuf[0], &test_info[0]);
		
		do{
			res = f_write(&m_file, WRBuf, strlen(WRBuf), (u32*)&bw);
			if(res){
				f_lseek(&m_file, 0); 
				printf("Write error.\n");
			}
			printf("Write %d bytes.\n", bw);
		} while (bw < strlen(WRBuf));

		printf("Write content:\n%s\n", WRBuf);
		printf("\n");
		
		/* move the file pointer to the file head*/
		res = f_lseek(&m_file, 0); 

		do{
			res = f_read(&m_file, RDBuf, strlen(WRBuf), (u32*)&br);
			if(res){
				f_lseek(&m_file, 0);
				printf("Read error.\n");
			}
			printf("Read %d bytes.\n", br);
		}while(br < strlen(WRBuf));
	
		printf("Read content:\n%s\n", RDBuf);

		// close source file
		res = f_close(&m_file);
		if(res){
			printf("close file (%s) fail.\n", filename);
		}

		//
		if(f_mount(NULL, logical_drv, 1) != FR_OK){
			printf("FATFS unmount logical drive fail.\n");
		}
		
		if(FATFS_UnRegisterDiskDriver(drv_num)) 
			printf("Unregister disk driver from FATFS fail.\n");
	}

exit:
	vTaskDelete(NULL);
}
#endif


char *print_file_info(FILINFO fileinfo, char *fn, char* path)
{
	char info[256];
	char fname[64];
	memset(fname, 0, sizeof(fname));
	snprintf(fname, sizeof(fname), "%s", fn);	
	
	snprintf(info, sizeof(info), 
		"%c%c%c%c%c  %u/%02u/%02u  %02u:%02u  %9u  %30s  %30s", 
		(fileinfo.fattrib & AM_DIR) ? 'D' : '-',
		(fileinfo.fattrib & AM_RDO) ? 'R' : '-',
		(fileinfo.fattrib & AM_HID) ? 'H' : '-',
		(fileinfo.fattrib & AM_SYS) ? 'S' : '-',
		(fileinfo.fattrib & AM_ARC) ? 'A' : '-',
		(fileinfo.fdate >> 9) + 1980,
		(fileinfo.fdate >> 5) & 15,
		fileinfo.fdate & 31,
		(fileinfo.ftime >> 11),
		(fileinfo.ftime >> 5) & 63,
		fileinfo.fsize,
		fn,
		path);
	printf("%s\n\r", info);
	return info;
}

FRESULT list_files(char* list_path)
{
	DIR m_dir;
	FILINFO m_fileinfo;
	FRESULT res;
	char *filename;
#if _USE_LFN && !defined(FATFS_R_13C)
	char fname_lfn[_MAX_LFN + 1];
	m_fileinfo.lfname = fname_lfn;
	m_fileinfo.lfsize = sizeof(fname_lfn);
#endif
	char cur_path[64];
	//strcpy(cur_path, list_path);

	// open directory
	res = f_opendir(&m_dir, list_path);

	if(res == FR_OK)
	{
		for (;;) {
			strcpy(cur_path, list_path);
			// read directory and store it in file info object
			res = f_readdir(&m_dir, &m_fileinfo);
			if (res != FR_OK || m_fileinfo.fname[0] == 0) {
				break;
			}

#if _USE_LFN && !defined(FATFS_R_13C)
			filename = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
			filename = m_fileinfo.fname;
#endif
			if (*filename == '.' || *filename == '..') 
			{
				continue;
			}

			// check if the object is directory
			if(m_fileinfo.fattrib & AM_DIR)
			{
				print_file_info(m_fileinfo, filename, cur_path);
				sprintf(&cur_path[strlen(list_path)], "/%s", filename);
				res = list_files(cur_path);
				//strcpy(list_path, cur_path);
				if (res != FR_OK) 
				{
					break;
				}
				//list_path[strlen(list_path)] = 0;
			}
			else {
				print_file_info(m_fileinfo, filename, cur_path);
			}

		}
	}

	// close directory
	res = f_closedir(&m_dir);
	if(res){
		printf("close directory fail: %d\n", res);
	}
	return res;
}

FRESULT del_dir(const TCHAR *path, int del_self)  
{  
    FRESULT res;  
    DIR   m_dir;    
    FILINFO m_fileinfo;     
    char *filename;
    char file[_MAX_LFN + 1];  
#if _USE_LFN && !defined(FATFS_R_13C)
		char fname_lfn[_MAX_LFN + 1];
		m_fileinfo.lfname = fname_lfn;
		m_fileinfo.lfsize = sizeof(fname_lfn);
#endif

    res = f_opendir(&m_dir, path);  

	if(res == FR_OK) {
		for (;;) {
			// read directory and store it in file info object
			res = f_readdir(&m_dir, &m_fileinfo);
			if (res != FR_OK || m_fileinfo.fname[0] == 0) {
				break;
			}

#if _USE_LFN && !defined(FATFS_R_13C)
			filename = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
			filename = m_fileinfo.fname;
#endif
			if (*filename == '.' || *filename == '..') 
			{
				continue;
			}

			printf("del: %s\n\r", filename);
			sprintf((char*)file, "%s/%s", path, filename);  

			if (m_fileinfo.fattrib & AM_DIR) {  
            	res = del_dir(file, 1);  
        	}  
        	else { 
            	res = f_unlink(file);  
        	}  	

		}

	}
	
    // close directory
	res = f_closedir(&m_dir);

	// delete self? 
    if(res == FR_OK) {
		if(del_self == 1)
			res = f_unlink(path);  
    }

	return res;  
}  

void example_fatfs(void)
{
	if(xTaskCreate(example_fatfs_thread, ((const char*)"example_fatfs_thread"), STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_fatfs_thread) failed", __FUNCTION__);
}
#endif
#endif /* CONFIG_EXAMPLE_FATFS */
