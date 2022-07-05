/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#define LOG_TAG "CircularBuffer"
//#define LOG_NDEBUG 0

#include "hal_audio_debug.h"
#include "platform_stdlib.h"
#include "circular_buffer.h"

struct CircularBuffer *create_circular_buffer(void)
{
	struct CircularBuffer *buffer;
	buffer = calloc(1, sizeof(struct CircularBuffer));
	if (!buffer) {
		HAL_AUDIO_ERROR("calloc CircularBuffer fail");
		return NULL;
	}
	buffer->read_ptr = 0;
	buffer->write_ptr = 0;
	buffer->size_remain = 0;
	buffer->capacity = 0;
	buffer->raw_data = NULL;
	return buffer;
}

void release_circular_buffer(struct CircularBuffer *buffer)
{
	if (buffer->raw_data != NULL) {
		free(buffer->raw_data);
		buffer->raw_data = NULL;
	}

	if (buffer) {
		free(buffer);
		buffer = NULL;
	}
}


void circular_alloc_buffer(struct CircularBuffer *buffer, size_t capacity)
{
	//HAL_AUDIO_INFO("alloc buf,capacity = %u", capacity);
	buffer->raw_data  = calloc(capacity, sizeof(char));
	if (!buffer) {
		HAL_AUDIO_ERROR("calloc raw_data fail");
		return;
	}

	buffer->capacity = capacity;
}

size_t get_buffer_capacity(struct CircularBuffer *buffer)
{
	return buffer->capacity;
}

/*buffer bytes remain in buffer to be consumed*/
size_t get_buffer_remain_data_size(struct CircularBuffer *buffer)
{
	return buffer->size_remain;
}

/*buffer bytes available in buffer to be written*/
size_t get_available_buffer_size(struct CircularBuffer *buffer)
{
	if (buffer->size_remain == buffer->capacity || buffer->capacity == 0) {
		return 0;
	}

	//HAL_AUDIO_INFO("get avail,rp:%u,wp:%u", buffer->read_ptr, buffer->write_ptr);
	return (buffer->write_ptr < buffer->read_ptr) ? (buffer->read_ptr - buffer->write_ptr) : (buffer->capacity - (buffer->write_ptr - buffer->read_ptr));
}

/*write to buffer by hal*/
size_t circular_buffer_write(struct CircularBuffer *buffer, const void *data, size_t bytes)
{
	//HAL_AUDIO_INFO("[TX]write bytes = %u", bytes);

	if (bytes == 0 || buffer->size_remain >= buffer->capacity || buffer->capacity == 0) {
		return 0;
	}

	size_t capacity = buffer->capacity;
	size_t bytes_to_write = (bytes <= (capacity - buffer->size_remain)) ? bytes : (capacity - buffer->size_remain);

	if (bytes_to_write <= capacity - buffer->write_ptr) {
		memcpy(buffer->raw_data + buffer->write_ptr, (u8 *)data, bytes_to_write);
		buffer->write_ptr += bytes_to_write;
		if (buffer->write_ptr == capacity) {
			buffer->write_ptr = 0;
		}
	} else {
		size_t size_1 = capacity - buffer->write_ptr;
		memcpy(buffer->raw_data + buffer->write_ptr, (u8 *)data, size_1);
		size_t size_2 = bytes_to_write - size_1;
		memcpy(buffer->raw_data, (u8 *)data + size_1, size_2);
		buffer->write_ptr = size_2;
	}

	buffer->size_remain += bytes_to_write;
	//HAL_AUDIO_INFO("[TX]after write,rp:%u,wp:%u,bytes_to_write:%d,size_remain:%d", buffer->read_ptr, buffer->write_ptr, bytes_to_write, buffer->size_remain);
	return bytes_to_write;
}

/*read buffer by gdma, update readptr here*/
void update_tx_readptr_after_gdma_transfer(struct CircularBuffer *buffer, size_t bytes)
{
	//HAL_AUDIO_INFO("[TX]gdma up rd bytes = %u,size_ = %u", bytes, buffer->size_remain);
	if (bytes == 0) {
		return;
	}

	size_t capacity = buffer->capacity;
	size_t bytes_to_read = (bytes <= buffer->size_remain) ? bytes : buffer->size_remain;

	if (bytes_to_read <= capacity - buffer->read_ptr) {
		buffer->read_ptr += bytes_to_read;
		if (buffer->read_ptr == capacity) {
			buffer->read_ptr = 0;
		}
	} else {
		size_t size_1 = capacity - buffer->read_ptr;
		size_t size_2 = bytes_to_read - size_1;
		buffer->read_ptr = size_2;
	}
	//HAL_AUDIO_INFO("[TX]gdma up rd done,rp:%u,wp:%u", buffer->read_ptr, buffer->write_ptr);
	buffer->size_remain -= bytes_to_read;
}

size_t get_tx_readptr(struct CircularBuffer *buffer)
{
	return buffer->read_ptr;
}

/*write to buffer by gdma, update writeptr here*/
size_t update_rx_writeptr_after_gdma_transfer(struct CircularBuffer *buffer, size_t bytes)
{
	//HAL_AUDIO_INFO("[RX]gdma up wr bytes = %u, buffer->size_remain:%d", bytes, buffer->size_remain);
	if (bytes == 0 || buffer->size_remain >= buffer->capacity || buffer->capacity == 0) {
		return 0;
	}

	if ((buffer->write_ptr + bytes) > buffer->capacity) {
		HAL_AUDIO_ERROR("[RX]write ptr out of range!");
		buffer->write_ptr = 0;
	}

	if ((buffer->write_ptr + bytes) == buffer->capacity) {
		//HAL_AUDIO_INFO("[RX]write_ptr reset to 0");
		buffer->write_ptr = 0;
	} else {
		buffer->write_ptr += bytes;
	}

	buffer->size_remain += bytes;
	//HAL_AUDIO_INFO("[RX]gdma up wr done,rp:%u,wp:%u, buffer->size_remain:%u", buffer->read_ptr, buffer->write_ptr, buffer->size_remain);
	return bytes;
}

/*read buffer by hal*/
size_t circular_buffer_read(struct CircularBuffer *buffer, void *data, size_t bytes)
{
	//HAL_AUDIO_INFO("[RX]read bytes = %u,size_ = %u", bytes, buffer->size_remain);
	if (bytes == 0 || bytes > buffer->size_remain) {
		return 0;
	}

	size_t capacity = buffer->capacity;
	size_t bytes_to_read = (bytes <= buffer->size_remain) ? bytes : buffer->size_remain;

	if (bytes_to_read <= capacity - buffer->read_ptr) {
		memcpy(data, buffer->raw_data + buffer->read_ptr, bytes_to_read);
		buffer->read_ptr += bytes_to_read;
		if (buffer->read_ptr == capacity) {
			buffer->read_ptr = 0;
		}
	} else {
		size_t size_1 = capacity - buffer->read_ptr;
		memcpy((u8 *)data, buffer->raw_data + buffer->read_ptr, size_1);
		size_t size_2 = bytes_to_read - size_1;
		memcpy((u8 *)data + size_1, buffer->raw_data, size_2);
		buffer->read_ptr = size_2;
	}

	buffer->size_remain -= bytes_to_read;
	//HAL_AUDIO_INFO("[RX]after read,rp:%u,wp:%u, buffer->size_remain:%u", buffer->read_ptr, buffer->write_ptr, buffer->size_remain);
	return bytes_to_read;
}

size_t get_rx_writeptr(struct CircularBuffer *buffer)
{
	return buffer->write_ptr;
}

