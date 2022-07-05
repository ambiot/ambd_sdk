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

#ifndef AMEBA_HARDWARE_AUDIO_V2_0_CIRCULARBUFFER_H
#define AMEBA_HARDWARE_AUDIO_V2_0_CIRCULARBUFFER_H

struct CircularBuffer {
	size_t read_ptr;
	size_t write_ptr;
	size_t size_remain;
	size_t capacity;
	char *raw_data;
};

struct CircularBuffer *create_circular_buffer(void);
void release_circular_buffer(struct CircularBuffer *buffer);
void circular_alloc_buffer(struct CircularBuffer *buffer, size_t capacity);
size_t get_buffer_remain_data_size(struct CircularBuffer *buffer);
size_t get_buffer_capacity(struct CircularBuffer *buffer);
size_t circular_buffer_write(struct CircularBuffer *buffer, const void *data, size_t bytes);
size_t update_rx_writeptr_after_gdma_transfer(struct CircularBuffer *buffer, size_t bytes);
size_t circular_buffer_read(struct CircularBuffer *buffer, void *data, size_t bytes);
void update_tx_readptr_after_gdma_transfer(struct CircularBuffer *buffer, size_t bytes);
size_t get_tx_readptr(struct CircularBuffer *buffer);
size_t get_rx_writeptr(struct CircularBuffer *buffer);
size_t get_available_buffer_size(struct CircularBuffer *buffer);

#endif


