#ifndef AMEBA_HARDWARE_INTERFACES_HARDWARE_AMEBA_AUDIO_DRIVER_H
#define AMEBA_HARDWARE_INTERFACES_HARDWARE_AMEBA_AUDIO_DRIVER_H

#include "platform_stdlib.h"
//#include "ameba_rcc.h"
#include "ameba_soc.h"
//#include "ameba_sport.h"
//#include "ameba_audio.h"
#include "circular_buffer.h"
#include "hal_osal_errnos.h"
#include "osdep_service.h"

#define STREAM_OUT 0
#define STREAM_IN  1

struct stream_config {
	u32 channels;
	u32 format;
	u32 rate;
	u32 frame_size;
	unsigned int period_size;
	unsigned int period_count;
};

struct gdma_callback_data;

struct stream {
	struct CircularBuffer *stream_buffer;
	struct gdma_callback_data *SPGdmaStruct;
	SP_InitTypeDef SP_InitStruct;
	//CODEC_InitTypeDef CODEC_InitStruct;
	bool start_gdma;
	bool restart_by_write;
	bool restart_by_read;
	bool gdma_should_stop;
	u32 period_bytes;
	u32 sport_dev_num;
	u32 direction;
	u32 gdma_count;
	u32 gdma_irq_count;
	_mutex lock;
	_sema sem;
	bool sem_should_post;
};

struct gdma_callback_data {
	GDMA_InitTypeDef       	SpTxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
	GDMA_InitTypeDef       	SpRxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
	struct stream *own_stream;
};

struct stream *stream_tx_init(struct stream_config config);
void stream_tx_start(struct stream *stream_out);
int stream_tx_write(struct stream *stream_out, const void *data, unsigned int bytes);
void stream_tx_close(struct stream *stream_out);


struct stream *stream_rx_init(struct stream_config config);
void stream_rx_sel_sdm_num_for_ad_channel(struct stream *stream_in, u32 ad_channel, u32 sdm_num);
void stream_rx_start(struct stream *stream_in);
int stream_rx_read(struct stream *stream_in, void *data, unsigned int bytes);
void stream_rx_close(struct stream *stream_in);


#endif
