#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "audio_play.h"

file_hdl fdst_amr;

/**
 * @brief  Open a file
 * @note   
 * @param  pFile_hdl: file object
 * @param  pFile:  file pointer
 * @param  size: file size
 * @retval 
 */
int mf_open(file_hdl* pFile_hdl, const void* pFile, int size)
{
	pFile_hdl->pFile = pFile;
	pFile_hdl->size = size;
	pFile_hdl->pos = 0;
	pFile_hdl->isOpen = TRUE;

	printf("[%s]open size=%d\r\n",__func__,pFile_hdl->size);

	return pFile_hdl->size;
}

/**
 * @brief  close a file
 * @note   
 * @param  pFile_hdl: the object needs to be closed
 * @retval 
 */
int mf_close(file_hdl* pFile_hdl)
{
	pFile_hdl->pFile = NULL;
	pFile_hdl->size = 0;
	pFile_hdl->pos = 0;
	pFile_hdl->isOpen = FALSE;

	printf("[%s]!!!!\r\n",__func__);
	return 0;
}

/**
 * @brief  check we are at the end of a file or not 
 * @note   
 * @param  pFile_hdl: file object
 * @retval -1: file isn't opened, 0: not the end of a file other:end of a file
 */
int mf_eof(file_hdl* pFile_hdl)
{
	printf("[%s]file pos=%d\r\n",__func__,pFile_hdl->pos);
	if (pFile_hdl->isOpen != TRUE)
		return -1;

	if (pFile_hdl->pos >= pFile_hdl->size)
		return pFile_hdl->pos;
	else
		return  0;
}
/**
 * @brief  read a file
 * @note   
 * @param  pFile_hdl: file object
 * @param  *pvBuffer: buffer pointer
 * @param  lSize: length needs to be read
 * @param  *len_read: real length it reads
 * @retval 
 */
int mf_read(file_hdl* pFile_hdl, void *pvBuffer, int lSize, int *len_read)
{
	if (pFile_hdl->isOpen != TRUE)
		return -1;
	
	// 1. calculate the length left
	int remain_size = pFile_hdl->size - pFile_hdl->pos;


	// 2. length to be read is less then the length left
	if (lSize <= remain_size)     
	{
		memcpy(pvBuffer , (const unsigned char*)pFile_hdl->pFile+pFile_hdl->pos, lSize);
		pFile_hdl->pos += lSize;
		*len_read = lSize;

	}
	else
	{
		memcpy(pvBuffer, (const unsigned char*)pFile_hdl->pFile + pFile_hdl->pos, remain_size);
		pFile_hdl->pos += remain_size;
		*len_read = remain_size;
	}

	return 0;
}
