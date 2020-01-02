//#include <stdio.h>
#include "opusenc.h"
#include <fatfs_ext/inc/ff_driver.h>
#include <disk_if/inc/sdcard.h>
#include "ff.h"
#include "platform_opts.h"
#include <platform_stdlib.h>
#define READ_SIZE 256
#ifdef CONFIG_EXAMPLE_AUDIO_OPUS_ENCODE
int drv_num;
char logical_drv[4];

void opus_audio_opus_encode(u8* source_file, u8* dest_file, opus_int32 sample_rate, int channels, int complexity, int bitrate) {
    printf("enter opus encode\n");
    FIL m_file;
    char abs_path[32];
    OggOpusEnc *enc;
    OggOpusComments *comments;
    int error;
    FRESULT res; 
    FATFS m_fs;
    drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
    
    if(drv_num < 0){
        printf("Rigester disk driver to FATFS fail.\n");
        return ;
    }else{
        logical_drv[0] = drv_num + '0';
        logical_drv[1] = ':';
        logical_drv[2] = '/';
        logical_drv[3] = 0;
    }
    
    if(f_mount(&m_fs, logical_drv, 1)!= FR_OK){
         printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
    }
    memset(abs_path, 0x00, sizeof(abs_path));
    strcpy(abs_path, logical_drv);
    sprintf(&abs_path[strlen(abs_path)],"%s", source_file);
	
    //Open source file
    res = f_open(&m_file, abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file
    comments = ope_comments_create();
    //add artist name and title name to the converted opus file
    ope_comments_add(comments, "ARTIST", "Someone");
    ope_comments_add(comments, "TITLE", "Some track");
    //specify the sampling rate and channels of source file 
    
    enc = ope_encoder_create_file(dest_file, comments, sample_rate, channels, 0, &error);
    //configure the complexity and bitrate of encoded file
    ope_encoder_ctl(enc, OPUS_SET_COMPLEXITY_REQUEST, complexity);
    ope_encoder_ctl(enc, OPUS_SET_BITRATE_REQUEST, bitrate);
    u32 tim_total1 = 0;
  
    //change data transfer strategy according to channel number
    if(channels == 2){
    while (1) {
        short buf[2*READ_SIZE];
        int byte_count;
        u32 tim1, tim2;
        FRESULT read_res;
        read_res= f_read(&m_file, (void*)buf, 2*sizeof(short)*READ_SIZE, &byte_count);
        if(byte_count < 2*sizeof(short)*READ_SIZE){
		    break;
	    }
        if (read_res == FR_OK) {
            tim1 = RTIM_GetCount(TIM0); 
            ope_encoder_write(enc, buf, byte_count/(2*sizeof(short)));
            tim2 = RTIM_GetCount(TIM0);
                tim_total1 += (tim2-tim1)*32;
	    } else break;
	}
    }

    else{
    while(1){
        short buf[READ_SIZE];
        int byte_count;
        u32 tim1, tim2;
        FRESULT read_res;
        read_res= f_read(&m_file, (void*)buf, sizeof(short)*READ_SIZE, &byte_count);
        if(byte_count < sizeof(short)*READ_SIZE){
		    break;
	    }
        if (read_res == FR_OK) {
            tim1 = RTIM_GetCount(TIM0); 
          ope_encoder_write(enc, buf, byte_count/(sizeof(short)));
            tim2 = RTIM_GetCount(TIM0);
            tim_total1 += (tim2-tim1)*32;
	    } else break;
	}
    }
    
    printf("conversion finished\n");
    printf("tim_total is %d\n", tim_total1);
    ope_encoder_drain(enc);
    ope_encoder_destroy(enc);
    ope_comments_destroy(comments);
    f_close(&m_file);
    f_mount(NULL, logical_drv, 1);
    FATFS_UnRegisterDiskDriver(drv_num);
}

void opus_audio_opus_encode_thread(void* param){
    //source_file is stored in SD card, dest_file is the one converted from source_file
    u8* source_file[] = {"1000Hz_48k_stereo.wav", "1000Hz_48k_mono.wav", "1000Hz_16k_mono.wav", "arashi_mono_48k.wav"};
    u8* dest_file[] = {"48_stereo_256_10.opus", "48_stereo_256_3.opus","48_stereo_256_0.opus","48_mono_256_3.opus","16_mono_48_3.opus","16_mono_20_3.opus"};
    opus_audio_opus_encode(source_file[0], dest_file[0], 48000, 2, 10, 256000);
    opus_audio_opus_encode(source_file[0], dest_file[1], 48000, 2, 3, 256000);
    opus_audio_opus_encode(source_file[0], dest_file[2], 48000, 2, 0, 256000);
    opus_audio_opus_encode(source_file[1], dest_file[3], 48000, 1, 3, 256000);
    opus_audio_opus_encode(source_file[2], dest_file[4], 16000, 1, 3, 48000);
    opus_audio_opus_encode(source_file[2], dest_file[5], 16000, 1, 3, 20000);
    vTaskDelete(NULL);
}

void example_audio_opus_encode(void)
{
    RTIM_Cmd(TIM0, ENABLE);
	xTaskCreate(opus_audio_opus_encode_thread, ((const char*)"opus_audio_opus_encode_thread"), 20000, NULL, tskIDLE_PRIORITY + 1, NULL);
	//printf("\n\r%s xTaskCreate(opus_audio_opus_encode_thread) failed", __FUNCTION__);
}

#endif