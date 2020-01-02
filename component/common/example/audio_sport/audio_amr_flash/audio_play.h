#ifndef __AUDIO_PLAY_
#define __AUDIO_PLAY_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"


#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif


typedef struct
{
	const void*   pFile;        //file pointer
	int     size;               //file size
}audio_file_t;

typedef struct
{
	const void*   pFile;        //file pointer
	int     size;               //file size
	int     pos;                //current position, used for loop read
	int     isOpen;             //true: already open, false: not open
}file_hdl;

extern file_hdl fdst_amr;


extern SemaphoreHandle_t Semaphore_audio;

int mf_open(file_hdl* pFile_hdl, const void* pFile, int size);
int mf_close(file_hdl* pFile_hdl);
int mf_eof(file_hdl* pFile_hdl);
int mf_read(file_hdl* pFile_hdl, void *pvBuffer, int lSize, int *len_read);


#endif


