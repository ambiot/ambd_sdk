#include "audio_amr/example_audio_amr.h"
#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "i2s_api.h"
#include "analogin_api.h"
#include <stdlib.h>
#include "platform_opts.h"
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>
#include <disk_if/inc/sdcard.h>
#include "section_config.h"

#define CONFIG_EXAMPLE_AMR_STREAM_SGTL5000 0

#if CONFIG_EXAMPLE_AMR_STREAM_SGTL5000
#include "sgtl5000.h"
#else
#include "alc5651.h"
#endif
#define WRITE_RAW_DATA_SD 1
//-----------------Frequency Mapping Table--------------------//
/*+-------------+-------------------------+--------------------+
| Frequency(hz) | Number of Channels      | Decoded Bytes      |
                |(CH_MONO:1 CH_STEREO:2)  |(I2S_DMA_PAGE_SIZE) |
+---------------+-------------------------+--------------------+
|          8000 |                       1 |               1152 |
|          8000 |                       2 |               2304 |
|         16000 |                       1 |               1152 |
|         16000 |                       2 |               2304 |
|         22050 |                       1 |               1152 |
|         22050 |                       2 |               2304 |
|         24000 |                       1 |               1152 |
|         24000 |                       2 |               2304 |
|         32000 |                       1 |               2304 |
|         32000 |                       2 |               4608 |
|         44100 |                       1 |               2304 |
|         44100 |                       2 |               4608 |
|         48000 |                       1 |               2304 |
|         48000 |                       2 |               4608 |
+---------------+-------------------------+------------------+*/


//------------------------------------- ---CONFIG Parameters-----------------------------------------------//
#define NB_I2S_DMA_PAGE_SIZE 320   //Use frequency mapping table and set this value to number of decoded bytes 
                                 //Options:- 1152, 2304, 4608
#define WB_I2S_DMA_PAGE_SIZE 640

#define NUM_CHANNELS CH_MONO   //Use mp3 file properties to determine number of channels
                                 //Options:- CH_MONO, CH_STEREO

#define NB_SAMPLING_FREQ SR_8KHZ   //Use mp3 file properties to identify frequency and use appropriate macro
#define WB_SAMPLING_FREQ SR_16KHZ

                                 //Options:- SR_8KHZ     =>8000hz  - PASS       
                                 //          SR_16KHZ    =>16000hz - PASS

#define AMRNB_FILE_NAME "sound.amr"    //Specify the file name you wish to play that is present in the SDCARD
#define AMRWB_FILE_NAME "sound-wb.amr"
#define WAV_FILE_NAME "sound.wav"
#define WAV_WB_FILE_NAME "sound-wb.wav"

//------------------------------------- ---CONFIG Parameters-----------------------------------------------//

#define I2S_DMA_PAGE_NUM    2   // Vaild number is 2~4

//static u8 i2s_tx_buf[I2S_DMA_PAGE_SIZE*I2S_DMA_PAGE_NUM];
//static u8 i2s_rx_buf[I2S_DMA_PAGE_SIZE*I2S_DMA_PAGE_NUM];
static u8 *i2s_tx_buf = NULL;
static u8 *i2s_rx_buf = NULL;

#define I2S_SCLK_PIN            PC_1
#define I2S_WS_PIN              PC_0
#define I2S_SD_PIN              PC_2

static i2s_t i2s_obj;
static int audio_inited = 0;

static void i2s_tx_complete(void *data, char *pbuf)
{   
	//
}

static void i2s_rx_complete(void *data, char* pbuf)
{
	//
}
/* From WmfDecBytesPerFrame in dec_input_format_tab.cpp */
const int sizes_nb[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };

/* From pvamrwbdecoder_api.h, by dividing by 8 and rounding up */
const int sizes_wb[] = { 17, 23, 32, 36, 40, 46, 50, 58, 60, 5, -1, -1, -1, -1, -1, 0 };

enum AMR_TYPE {
	AMR_INVALID = -1,
	AMR_NB = 0,
	AMR_WB
};

/* Copied from enc/src/gsmamr_enc.h */
enum Mode {
	MR475 = 0,/* 4.75 kbps */
	MR515,    /* 5.15 kbps */
	MR59,     /* 5.90 kbps */
	MR67,     /* 6.70 kbps */
	MR74,     /* 7.40 kbps */
	MR795,    /* 7.95 kbps */
	MR102,    /* 10.2 kbps */
	MR122,    /* 12.2 kbps */
	MRDTX,    /* DTX       */
	N_MODES   /* Not Used  */
};

void audio_play_sd_amr(u8* filename){
	int drv_num = 0;
	int frame_size = 0;
	u32 read_length = 0;
	FRESULT res; 
	FATFS 	m_fs;
	FIL		m_file[2];  
	char	logical_drv[4]; //root diretor
	char abs_path[32]; //Path to input file
	DWORD bytes_left;
	DWORD file_size;
	int i = 0;
	int bw = 0;
	volatile u32 tim1 = 0;
	volatile u32 tim2 = 0;
	u32 start_heap;
	int *ptx_buf;
	char header[9];
	void *amr = NULL;
	enum AMR_TYPE amr_type = AMR_INVALID;
#if WRITE_RAW_DATA_SD
	char abs_path_op[16]; //Path to output file
	const char *outfile = "sound_amr.pcm";
#endif
	
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
	if(drv_num < 0){
		printf("Rigester disk driver to FATFS fail.\n");
		return;
	}else{
		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}

	if(f_mount(&m_fs, logical_drv, 1)!= FR_OK){
		printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
		goto unreg;
	}
	memset(abs_path, 0x00, sizeof(abs_path));
	strcpy(abs_path, logical_drv);
	sprintf(&abs_path[strlen(abs_path)],"%s", filename);

	//Open source file
	res = f_open(&m_file[0], abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file
	if(res != FR_OK){
		printf("Open source file %s fail.\n", filename);
		goto umount;
	}
	
	file_size = (&m_file[0])->fsize;
	bytes_left = file_size;
	printf("File size of %s is %d\n", filename, file_size);

	memset(header, 0, 9);
	res = f_read(&m_file[0], header, 6, (UINT*)&read_length);
	if (res == FR_OK && read_length == 6 && memcmp(header, "#!AMR\n", 6) == 0) {
		printf("It's an AMRNB audio file\n");
		amr_type = AMR_NB;
		i2s_tx_buf = malloc(NB_I2S_DMA_PAGE_SIZE * I2S_DMA_PAGE_NUM);
		i2s_rx_buf = malloc(NB_I2S_DMA_PAGE_SIZE * I2S_DMA_PAGE_NUM);
		if(!i2s_tx_buf || !i2s_rx_buf){
			printf("malloc failed for i2s buffer\n");
			goto exit;
		}
		i2s_obj.channel_num = NUM_CHANNELS;
		i2s_obj.sampling_rate = NB_SAMPLING_FREQ;
		i2s_obj.word_length = WL_16b;
		i2s_obj.direction = I2S_DIR_TXRX;	 
		i2s_init(&i2s_obj, I2S_SCLK_PIN, I2S_WS_PIN, I2S_SD_PIN);
		i2s_set_dma_buffer(&i2s_obj, (char*)i2s_tx_buf, (char*)i2s_rx_buf, \
			I2S_DMA_PAGE_NUM, NB_I2S_DMA_PAGE_SIZE);
		i2s_tx_irq_handler(&i2s_obj, (i2s_irq_handler)i2s_tx_complete, (uint32_t)&i2s_obj);
		i2s_rx_irq_handler(&i2s_obj, (i2s_irq_handler)i2s_rx_complete, (uint32_t)&i2s_obj);
	}else{
		memset(header, 0, 9);
		f_lseek(&m_file[0], 0);
		res = f_read(&m_file[0], header, 9, (UINT*)&read_length);
		if (res == FR_OK && read_length == 9 && memcmp(header, "#!AMR-WB\n", 9) == 0) {
			printf("It's an AMRWB audio file\n");
			amr_type = AMR_WB;
			i2s_tx_buf = malloc(WB_I2S_DMA_PAGE_SIZE * I2S_DMA_PAGE_NUM);
			i2s_rx_buf = malloc(WB_I2S_DMA_PAGE_SIZE * I2S_DMA_PAGE_NUM);
			if(!i2s_tx_buf || !i2s_rx_buf){
				printf("malloc failed for i2s buffer\n");
				goto exit;
			}
			i2s_obj.channel_num = NUM_CHANNELS;
			i2s_obj.sampling_rate = WB_SAMPLING_FREQ;
			i2s_obj.word_length = WL_16b;
			i2s_obj.direction = I2S_DIR_TXRX;	 
			i2s_init(&i2s_obj, I2S_SCLK_PIN, I2S_WS_PIN, I2S_SD_PIN);
			i2s_set_dma_buffer(&i2s_obj, (char*)i2s_tx_buf, (char*)i2s_rx_buf, \
				I2S_DMA_PAGE_NUM, WB_I2S_DMA_PAGE_SIZE);
			i2s_tx_irq_handler(&i2s_obj, (i2s_irq_handler)i2s_tx_complete, (uint32_t)&i2s_obj);
			i2s_rx_irq_handler(&i2s_obj, (i2s_irq_handler)i2s_rx_complete, (uint32_t)&i2s_obj);
		}
	}
	if(amr_type == AMR_INVALID){
		printf("Bad header\n");
		goto exit;
	}

	if(!audio_inited){
#if CONFIG_EXAMPLE_AMR_STREAM_SGTL5000
			sgtl5000_enable();
			sgtl5000_setVolume(0.5);
#else
			alc5651_init();
			alc5651_init_interface2();	  
#endif
		audio_inited = 1;
	}

#if WRITE_RAW_DATA_SD
	if(amr_type == AMR_WB)
		outfile = "sound-amrwb.pcm";
	memset(abs_path_op, 0x00, sizeof(abs_path_op));
	strcpy(abs_path_op, logical_drv);
	sprintf(&abs_path_op[strlen(abs_path_op)],"%s", outfile);
	res = f_open(&m_file[1], abs_path_op, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);  // open read only file
	if(res != FR_OK){
		printf("Open source file %(s) fail.\n", outfile);
		goto exit;
	}
#endif
	start_heap = xPortGetFreeHeapSize();
	if(amr_type == AMR_NB){
		frame_size = NB_I2S_DMA_PAGE_SIZE/2;
		amr = (void *)Decoder_Interface_init();
	}
	else if(amr_type == AMR_WB){
		frame_size = WB_I2S_DMA_PAGE_SIZE/2;
		amr = (void *)D_IF_init();
	}
	if(!amr){
		printf("decoder interface init failed\r\n");
		goto exit;
	}
	tim1 = rtw_get_current_time();
	do{
		/* Read a block */
		uint8_t buffer[500], littleendian[WB_I2S_DMA_PAGE_SIZE], *ptr;
		int size, i;
		int16_t outbuffer[WB_I2S_DMA_PAGE_SIZE/2];
		/* Read the mode byte */
		res = f_read(&m_file[0], buffer, 1, (UINT*)&read_length);
		if (res != FR_OK || read_length != 1){
			if(read_length == 0)
				printf("read done\r\n");
			else
				printf("read the mode byte failed\r\n");
			break;
		}
		/* Find the packet size */
		if(amr_type == AMR_NB)
			size = sizes_nb[(buffer[0] >> 3) & 0x0f];
		else if(amr_type == AMR_WB)
			size = sizes_wb[(buffer[0] >> 3) & 0x0f];
		if(size < 0)
			break;

		res = f_read(&m_file[0], buffer + 1, size, (UINT*)&read_length);
		if(res != FR_OK){
			printf("read failed\r\n");
			break;
		}

		/* Decode the packet */
		if(amr_type == AMR_NB)
			Decoder_Interface_Decode(amr, buffer, outbuffer, 0);
		else if(amr_type == AMR_WB)
			D_IF_decode(amr, buffer, outbuffer, 0);

		/* Convert to little endian and write to wav */
		ptr = littleendian;
		for (i = 0; i < frame_size; i++) {
			*ptr++ = (outbuffer[i] >> 0) & 0xff;
			*ptr++ = (outbuffer[i] >> 8) & 0xff;
		}

#if WRITE_RAW_DATA_SD
		do{
			res = f_write(&m_file[1], littleendian, frame_size*2, (u32*)&bw);
			if(res){
				f_lseek(&m_file[1], 0); 
				printf("Write error.\n");
			}
			//printf("Write %d bytes.\n", bw);
		}while(bw < frame_size*2);
		bw = 0;
#endif
#if 1
		retry:
			ptx_buf = i2s_get_tx_page(&i2s_obj);
			if(ptx_buf){
				memcpy((void*)ptx_buf, (void*)littleendian, frame_size*2);
				i2s_send_page(&i2s_obj, (uint32_t*)ptx_buf);
			}else{
				vTaskDelay(1);
				goto retry;
			}
#endif
	}while(1);

	tim2 = rtw_get_current_time();
	printf("decoding finished (Heap used: 0x%x, Time passed: %dms)\n", start_heap - xPortGetFreeHeapSize(), (tim2-tim1));
	printf("PCM done\n");

	if(amr_type == AMR_NB)
		Decoder_Interface_exit(amr);
	else if(amr_type == AMR_WB)
		D_IF_exit(amr);

exit:
	i2s_deinit(&i2s_obj);
	if(i2s_rx_buf)
		free(i2s_rx_buf);
	if(i2s_tx_buf)
		free(i2s_tx_buf);
	// close source file
	res = f_close(&m_file[0]);
	if(res){
		printf("close file (%s) fail.\n", filename);
	}
#if WRITE_RAW_DATA_SD
	res = f_close(&m_file[1]);
	if(res){
		printf("close file (%s) fail.\n", outfile);
	}
#endif

umount:
	if(f_mount(NULL, logical_drv, 1) != FR_OK){
		printf("FATFS unmount logical drive fail.\n");
	}

unreg:	
	if(FATFS_UnRegisterDiskDriver(drv_num))	
		printf("Unregister disk driver from FATFS fail.\n");
	
}

void amrnb_enc_sd_wav(u8* filename){
	int drv_num = 0;
	int frame_size = 0;
	u32 read_length = 0;
	FRESULT res; 
	FATFS 	m_fs;
	FIL		m_file[2];  
	char	logical_drv[4]; //root diretor
	char abs_path[32]; //Path to input file
	DWORD bytes_left;
	DWORD file_size;
	int i = 0;
	int bw = 0;
	volatile u32 tim1 = 0;
	volatile u32 tim2 = 0;
	u32 start_heap;
	void *amr = NULL;
	int dtx = 1; // TBD
	int channels = 1;
	enum Mode mode = MR122;
	char abs_path_op[16]; //Path to output file
	const char *outfile = "sound_amrnb_enc.amr";
	
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
	if(drv_num < 0){
		printf("Rigester disk driver to FATFS fail.\n");
		return;
	}else{
		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}

	if(f_mount(&m_fs, logical_drv, 1)!= FR_OK){
		printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
		goto unreg;
	}
	memset(abs_path, 0x00, sizeof(abs_path));
	strcpy(abs_path, logical_drv);
	sprintf(&abs_path[strlen(abs_path)],"%s", filename);

	//Open source file
	res = f_open(&m_file[0], abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file
	if(res != FR_OK){
		printf("Open source file %s fail.\n", filename);
		goto umount;
	}
	
	file_size = (&m_file[0])->fsize;
	bytes_left = file_size;
	printf("File size of %s is %d\n", filename, file_size);
	f_lseek(&m_file[0], 44); // skip the wav header

	memset(abs_path_op, 0x00, sizeof(abs_path_op));
	strcpy(abs_path_op, logical_drv);
	sprintf(&abs_path_op[strlen(abs_path_op)],"%s", outfile);
	res = f_open(&m_file[1], abs_path_op, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);  // open read only file
	if(res != FR_OK){
		printf("Open source file %(s) fail.\n", outfile);
		goto exit;
	}

	start_heap = xPortGetFreeHeapSize();
	amr = (void *)Encoder_Interface_init(dtx);
	if(!amr){
		printf("decoder interface init failed\r\n");
		goto exit;
	}
	tim1 = rtw_get_current_time();
	res = f_write(&m_file[1], "#!AMR\n", 6, (u32*)&bw);
	if(res != FR_OK){
		printf("Write header to file %(s) fail.\n", outfile);
		goto exit;
	}
	do{
		/* Read a block */
		u8 inputBuf[1*2*160]; //channel*2*160, only encode one channel
		u16 buf[160];
		u8 outbuf[500];
		int read, n;
		/* Read the mode byte */
		res = f_read(&m_file[0], inputBuf, sizeof(inputBuf), (UINT*)&read_length);
		read_length /= channels;
		read_length /= 2;
		if (res != FR_OK || read_length < 160){
			if(read_length == 0)
				printf("read done\r\n");
			else
				printf("read the mode byte failed\r\n");
			break;
		}

		for (i = 0; i < 160; i++) {
			const uint8_t* in = &inputBuf[2*1*i];
			buf[i] = in[0] | (in[1] << 8);
		}

		n = Encoder_Interface_Encode(amr, mode, buf, outbuf, 0);

		do{
			res = f_write(&m_file[1], outbuf, n, (u32*)&bw);
			if(res){
				f_lseek(&m_file[1], 0); 
				printf("Write error.\n");
			}
			//printf("Write %d bytes.\n", bw);
		}while(bw < n);
		bw = 0;
	}while(1);

	tim2 = rtw_get_current_time();
	printf("encoding finished (Heap used: 0x%x, Time passed: %dms)\n", start_heap - xPortGetFreeHeapSize(), (tim2-tim1));

	Encoder_Interface_exit(amr);

exit:
	// close source file
	res = f_close(&m_file[0]);
	if(res){
		printf("close file (%s) fail.\n", filename);
	}
	res = f_close(&m_file[1]);
	if(res){
		printf("close file (%s) fail.\n", outfile);
	}

umount:
	if(f_mount(NULL, logical_drv, 1) != FR_OK){
		printf("FATFS unmount logical drive fail.\n");
	}

unreg:	
	if(FATFS_UnRegisterDiskDriver(drv_num))	
		printf("Unregister disk driver from FATFS fail.\n");
	
}

void amrwb_enc_sd_wav(u8* filename){
	int drv_num = 0;
	int frame_size = 0;
	u32 read_length = 0;
	FRESULT res; 
	FATFS 	m_fs;
	FIL		m_file[2];  
	char	logical_drv[4]; //root diretor
	char abs_path[32]; //Path to input file
	DWORD bytes_left;
	DWORD file_size;
	int i = 0;
	int bw = 0;
	volatile u32 tim1 = 0;
	volatile u32 tim2 = 0;
	u32 start_heap;
	void *amr = NULL;
	int dtx = 0; // TBD
	int channels = 1, inputSize;
    u8 *inputBuf;
	int mode = 8;
	char abs_path_op[16]; //Path to output file
	const char *outfile = "sound_amrwb_enc.amr";
	
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
	if(drv_num < 0){
		printf("Rigester disk driver to FATFS fail.\n");
		return;
	}else{
		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}

	if(f_mount(&m_fs, logical_drv, 1)!= FR_OK){
		printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
		goto unreg;
	}
	memset(abs_path, 0x00, sizeof(abs_path));
	strcpy(abs_path, logical_drv);
	sprintf(&abs_path[strlen(abs_path)],"%s", filename);

	//Open source file
	res = f_open(&m_file[0], abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file
	if(res != FR_OK){
		printf("Open source file %s fail.\n", filename);
		goto umount;
	}
	
	file_size = (&m_file[0])->fsize;
	bytes_left = file_size;
	printf("File size of %s is %d\n", filename, file_size);
	f_lseek(&m_file[0], 44); // skip the wav header

	memset(abs_path_op, 0x00, sizeof(abs_path_op));
	strcpy(abs_path_op, logical_drv);
	sprintf(&abs_path_op[strlen(abs_path_op)],"%s", outfile);
	res = f_open(&m_file[1], abs_path_op, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);  // open read only file
	if(res != FR_OK){
		printf("Open source file %(s) fail.\n", outfile);
		goto exit;
	}
	inputSize = channels*2*320;
	inputBuf = (uint8_t*) malloc(inputSize);

	start_heap = xPortGetFreeHeapSize();
	amr = (void *)E_IF_init();
	if(!amr){
		printf("decoder interface init failed\r\n");
		goto exit;
	}
	tim1 = rtw_get_current_time();
	res = f_write(&m_file[1], "#!AMR-WB\n", 9, (u32*)&bw);
	if(res != FR_OK){
		printf("Write header to file %(s) fail.\n", outfile);
		goto exit;
	}
	do{
		int read, i, n;
		short buf[320];
		uint8_t outbuf[500];
		/* Read the mode byte */
		res = f_read(&m_file[0], inputBuf, inputSize, (UINT*)&read_length);
		read_length /= channels;
		read_length /= 2;
		if (res != FR_OK || read_length < 320){
			if(read_length == 0)
				printf("read done\r\n");
			else
				printf("read the mode byte failed\r\n");
			break;
		}

		for (i = 0; i < 320; i++) {
			const uint8_t* in = &inputBuf[2*channels*i];
			buf[i] = in[0] | (in[1] << 8);
		}
		n = E_IF_encode(amr, mode, buf, outbuf, dtx);
		do{
			res = f_write(&m_file[1], outbuf, n, (u32*)&bw);
			if(res){
				f_lseek(&m_file[1], 0); 
				printf("Write error.\n");
			}
			//printf("Write %d bytes.\n", bw);
		}while(bw < n);
		bw = 0;
	}while(1);

	tim2 = rtw_get_current_time();
	printf("encoding finished (Heap used: 0x%x, Time passed: %dms)\n", start_heap - xPortGetFreeHeapSize(), (tim2-tim1));

	E_IF_exit(amr);

exit:
	// close source file
	res = f_close(&m_file[0]);
	if(res){
		printf("close file (%s) fail.\n", filename);
	}
	res = f_close(&m_file[1]);
	if(res){
		printf("close file (%s) fail.\n", outfile);
	}

umount:
	if(f_mount(NULL, logical_drv, 1) != FR_OK){
		printf("FATFS unmount logical drive fail.\n");
	}

unreg:	
	if(FATFS_UnRegisterDiskDriver(drv_num))	
		printf("Unregister disk driver from FATFS fail.\n");

    if(inputBuf)
        free(inputBuf);
}

void example_audio_amr_thread(void* param){
	printf("Audio codec demo begin......\n"); 
	audio_play_sd_amr(AMRNB_FILE_NAME);
	vTaskDelay(1000);
	audio_play_sd_amr(AMRWB_FILE_NAME);
	vTaskDelay(1000);
	amrnb_enc_sd_wav(WAV_FILE_NAME);
	vTaskDelay(1000);
	amrwb_enc_sd_wav(WAV_WB_FILE_NAME);

exit:
	vTaskDelete(NULL);
}

void example_audio_amr(void)
{
	if(xTaskCreate(example_audio_amr_thread, ((const char*)"example_audio_amr_thread"), 4096, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_audio_amr_thread) failed", __FUNCTION__);
}

