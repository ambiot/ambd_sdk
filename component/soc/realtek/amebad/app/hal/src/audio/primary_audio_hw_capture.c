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
#define LOG_TAG "PrimaryAudioHwCapture"
//#define LOG_NDEBUG 0

#include "hal_audio_debug.h"
#include "osdep_service.h"

#include "hardware/audio/audio_hw_types.h"
#include "hardware/audio/audio_hw_utils.h"
#include "hardware/audio/audio_hw_capture.h"
#include "hardware/audio/audio_hw_adapter.h"

#include "ameba_audio_driver.h"
#include "params_handle.h"
#include "primary_audio_hw_adapter.h"

#define CAPTURE_PERIOD_SIZE 2048
#define CAPTURE_PERIOD_COUNT 4

#define AUDIO_ADC0_CHOSE_AMIC         "adc0_sel_amic_num"
#define AUDIO_ADC1_CHOSE_AMIC         "adc1_sel_amic_num"
#define AUDIO_ADC2_CHOSE_AMIC         "adc2_sel_amic_num"
#define AUDIO_ADC3_CHOSE_AMIC         "adc3_sel_amic_num"
#define AUDIO_ADC4_CHOSE_AMIC         "adc4_sel_amic_num"
#define AUDIO_ADC5_CHOSE_AMIC         "adc5_sel_amic_num"
#define AUDIO_ADC6_CHOSE_AMIC         "adc6_sel_amic_num"
#define AUDIO_ADC7_CHOSE_AMIC         "adc7_sel_amic_num"

struct stream_config pcm_config_capture = {
	.channels = 2,
	.rate = 44100,
	.period_size = CAPTURE_PERIOD_SIZE,
	.period_count = CAPTURE_PERIOD_COUNT,
	.format = AUDIO_HW_FORMAT_PCM_16_BIT,
};

struct PrimaryAudioHwCapture {
	struct AudioHwCapture stream;

	struct PrimaryAudioHwAdapter *adap;
	struct AudioHwDeviceDescriptor desc;
	_mutex lock;
	struct stream_config config;
	struct stream *in_pcm;
	void *stream_buf;
	int standby;
	uint64_t rframe;
	uint32_t requested_channels;
};

static inline size_t PrimaryAudioHwCaptureFrameSize(const struct AudioHwCapture *s)
{
	size_t chan_samp_sz;
	AudioHwFormat format = s->common.GetFormat(&s->common);

	if (AudioIsLinearPCM(format)) {
		chan_samp_sz = GetAudioBytesPerSample(format);
		return s->common.GetChannels(&s->common) * chan_samp_sz;
	}

	return sizeof(int8_t);
}

/** audio_stream_in implementation **/
static uint32_t PrimaryGetCaptureSampleRate(const struct AudioHwStream *stream)
{
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;

	return cap->config.rate;
}

static int PrimarySetCaptureSampleRate(struct AudioHwStream *stream, uint32_t rate)
{
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;

	if (rate < 4000 || rate > 192000) {
		return - EINVAL;
	}

	cap->config.rate = rate;
	return 0;
}

static size_t PrimaryGetCaptureBufferSize(const struct AudioHwStream *stream)
{
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;

	return cap->config.period_size * PrimaryAudioHwCaptureFrameSize((const struct AudioHwCapture *)stream);
}

static uint32_t PrimaryGetCaptureChannels(const struct AudioHwStream *stream)
{
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;

	return (uint32_t)cap->requested_channels;
}

static int PrimarySetCaptureChannels(const struct AudioHwStream *stream, uint32_t channel)
{
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;

	cap->config.channels = channel;
	return 0;
}

static AudioHwFormat PrimaryGetCaptureFormat(const struct AudioHwStream *stream)
{
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;
	if (!cap->config.format) {
		return AUDIO_HW_FORMAT_PCM_16_BIT;
	}
	return cap->config.format;
}

static int PrimarySetCaptureFormat(struct AudioHwStream *stream, AudioHwFormat format)
{
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;
	cap->config.format = format;
	return 0;
}

static int DoInputStandby(struct PrimaryAudioHwCapture *cap)
{
	if (!cap->standby) {
		stream_rx_close(cap->in_pcm);
		cap->in_pcm = NULL;
		cap->standby = 1;
	}
	return 0;
}

static int PrimaryStandbyCapture(struct AudioHwStream *stream)
{
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;
	int status;

	rtw_mutex_get(&cap->adap->lock);
	rtw_mutex_get(&cap->lock);
	status = DoInputStandby(cap);
	rtw_mutex_put(&cap->lock);
	rtw_mutex_put(&cap->adap->lock);

	return status;
}

static int PrimaryDumpCapture(const struct AudioHwStream *stream, int fd)
{
	(void) stream;
	(void) fd;
	return 0;
}

static int PrimarySetCaptureParameters(struct AudioHwStream *stream, const char *str_pairs)
{
	HAL_AUDIO_VERBOSE("%s, keys = %s", __FUNCTION__, str_pairs);
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;
	struct string_cell *cells;
	cells = string_cells_create_from_str(str_pairs);
	int value;

	if (string_cells_has_key(cells, AUDIO_ADC0_CHOSE_AMIC)) {
		string_cells_get_int(cells, AUDIO_ADC0_CHOSE_AMIC, &value);
		stream_rx_sel_sdm_num_for_ad_channel(cap->in_pcm, 0, value);
	}

	if (string_cells_has_key(cells, AUDIO_ADC1_CHOSE_AMIC)) {
		string_cells_get_int(cells, AUDIO_ADC1_CHOSE_AMIC, &value);
		stream_rx_sel_sdm_num_for_ad_channel(cap->in_pcm, 1, value);
	}

	if (string_cells_has_key(cells, AUDIO_ADC2_CHOSE_AMIC)) {
		string_cells_get_int(cells, AUDIO_ADC2_CHOSE_AMIC, &value);
		stream_rx_sel_sdm_num_for_ad_channel(cap->in_pcm, 2, value);
	}

	if (string_cells_has_key(cells, AUDIO_ADC3_CHOSE_AMIC)) {
		string_cells_get_int(cells, AUDIO_ADC3_CHOSE_AMIC, &value);
		stream_rx_sel_sdm_num_for_ad_channel(cap->in_pcm, 3, value);
	}

	string_cells_destroy(cells);
	return 0;
}

static char *PrimaryGetCaptureParameters(const struct AudioHwStream *stream,
		const char *keys)
{
	(void) stream;
	(void) keys;
	return strdup("");
}

static uint32_t PrimaryGetCaptureLatency(const struct AudioHwCapture *stream)
{
	(void) stream;
	return 15;
}

static int PrimaryGetCapturePosition(const struct AudioHwCapture *stream, uint32_t *frames, struct timespec *timestamp)
{
	(void) stream;
	(void) frames;
	(void) timestamp;
	return 0;
}

static int StartAudioHwCapture(struct PrimaryAudioHwCapture *cap)
{
	stream_rx_start(cap->in_pcm);
	return 0;
}

static ssize_t PrimaryCaptureRead(struct AudioHwCapture *stream, void *buffer, size_t bytes)
{
	int ret = 0;
	unsigned int i = 0;
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)stream;
	struct PrimaryAudioHwAdapter *adap = cap->adap;

	size_t frame_size = PrimaryAudioHwCaptureFrameSize((const struct AudioHwCapture *)stream) * cap->config.channels / cap->requested_channels;
	HAL_AUDIO_VERBOSE("primaryCaptureRead: bytes %u, frame_size:%d", bytes, frame_size);

	rtw_mutex_get(&adap->lock);
	rtw_mutex_get(&cap->lock);
	if (cap->standby) {
		ret = StartAudioHwCapture(cap);
		if (ret == 0) {
			cap->standby = 0;
		} else {
			rtw_mutex_put(&adap->lock);
			rtw_mutex_put(&cap->lock);
			return -1;
		}
	}
	rtw_mutex_put(&adap->lock);
	if (ret < 0) {
		goto exit;
	}

	if (cap->requested_channels == 3) {
		unsigned int stream_buf_bytes = bytes * cap->config.channels / cap->requested_channels;   // *4chan/3chan
		HAL_AUDIO_INFO("read bytes:%d, stream_buf_bytes:%d", bytes, stream_buf_bytes);
		stream_rx_read(cap->in_pcm, cap->stream_buf, stream_buf_bytes);
		for (i = 0; i < stream_buf_bytes / frame_size; i++) {
			*((u16 *)buffer + cap->requested_channels * i) = *((u16 *)cap->stream_buf + cap->config.channels * i);
			*((u16 *)buffer + cap->requested_channels * i + 1) = *((u16 *)cap->stream_buf + cap->config.channels * i + 1);
			*((u16 *)buffer + cap->requested_channels * i + 2) = *((u16 *)cap->stream_buf + cap->config.channels * i + 2);
		}
	} /*else if (cap->requested_channels == 1) {
		unsigned int stream_buf_bytes = bytes * cap->config.channels / cap->requested_channels;   // *2chan/1chan
		stream_rx_read(cap->in_pcm, cap->stream_buf, stream_buf_bytes);
		for (i = 0; i < stream_buf_bytes / frame_size; i++) {
			*((u16 *)buffer + cap->requested_channels * i) = *((u16 *)cap->stream_buf + cap->config.channels * i);
		}
	}*/ else {
		stream_rx_read(cap->in_pcm, buffer, bytes);
	}

exit:
	//DelayUs((int64_t)bytes * 1000000 / PrimaryAudioHwCaptureFrameSize(stream) / PrimaryGetCaptureSampleRate(&stream->common));
	//memset(buffer, 0, bytes);
	rtw_mutex_put(&cap->lock);

	return bytes;
}

static int CheckInputParameters(uint32_t sample_rate, AudioHwFormat format, uint32_t channel_count)
{
	if (format != AUDIO_HW_FORMAT_PCM_16_BIT) {
		return HAL_OSAL_ERR_INVALID_PARAM;
	}

	if ((channel_count < 1) || (channel_count > 4)) {
		return HAL_OSAL_ERR_INVALID_PARAM;
	}

	switch (sample_rate) {
	case 8000:
	case 11025:
	case 16000:
	case 22050:
	case 24000:
	case 32000:
	case 44100:
	case 48000:
	case 88200:
	case 96000:
	case 174000:
	case 192000:
		break;
	default:
		return HAL_OSAL_ERR_INVALID_PARAM;
	}

	return 0;
}

size_t GetHwInputBufferSize(uint32_t sample_rate, AudioHwFormat format, uint32_t channel_count)
{
	size_t size;

	if (CheckInputParameters(sample_rate, format, channel_count) != 0) {
		return 0;
	}

	size = (pcm_config_capture.period_size * sample_rate) / pcm_config_capture.rate;

	size = ((size + 15) / 16) * 16;

	return size * channel_count * sizeof(short);
}

void CloseAudioHwCapture(struct AudioHwCapture *capture)
{
	struct PrimaryAudioHwCapture *cap = (struct PrimaryAudioHwCapture *)capture;

	PrimaryStandbyCapture(&capture->common);

	if (cap->stream_buf) {
		free(cap->stream_buf);
		cap->stream_buf = NULL;
	}

	rtw_mutex_free(&cap->lock);

	rtw_free(capture);
	capture = NULL;

}

struct AudioHwCapture *GetAudioHwCaptureFuncs(struct AudioHwAdapter *adapter, const struct AudioHwDeviceDescriptor *desc, const struct AudioHwSampleAttributes *attrs)
{
	struct PrimaryAudioHwAdapter *ladap = (struct PrimaryAudioHwAdapter *)adapter;
	struct PrimaryAudioHwCapture *in;

	HAL_AUDIO_INFO("primaryCreateCapture() with format:%d, sample_rate:%ld channel_count:0x%lx", attrs->format, attrs->sample_rate, attrs->channel_count);
	if (CheckInputParameters(attrs->sample_rate, attrs->format, attrs->channel_count) != 0) {
		HAL_AUDIO_ERROR("primaryCreateCapture: invalid config");
		return NULL;
	}

	in = (struct PrimaryAudioHwCapture *)rtw_zmalloc(sizeof(struct PrimaryAudioHwCapture));
	if (!in) {
		return NULL;
	}

	in->adap = ladap;
	in->desc = *desc;

	in->stream.common.GetSampleRate = PrimaryGetCaptureSampleRate;
	in->stream.common.SetSampleRate = PrimarySetCaptureSampleRate;
	in->stream.common.GetBufferSize = PrimaryGetCaptureBufferSize;
	in->stream.common.GetChannels = PrimaryGetCaptureChannels;
	in->stream.common.SetChannels = PrimarySetCaptureChannels;
	in->stream.common.GetFormat = PrimaryGetCaptureFormat;
	in->stream.common.SetFormat = PrimarySetCaptureFormat;
	in->stream.common.Standby = PrimaryStandbyCapture;
	in->stream.common.Dump = PrimaryDumpCapture;
	in->stream.common.SetParameters = PrimarySetCaptureParameters;
	in->stream.common.GetParameters = PrimaryGetCaptureParameters;
	in->stream.GetLatency = PrimaryGetCaptureLatency;
	in->stream.GetCapturePosition = PrimaryGetCapturePosition;
	in->stream.Read = PrimaryCaptureRead;

	in->config = pcm_config_capture;
	in->in_pcm = NULL;
	in->stream_buf = NULL;

	if (attrs->sample_rate != 0) {
		in->config.rate = attrs->sample_rate;
	}

	if (attrs->channel_count != 0) {
		in->requested_channels = attrs->channel_count;
		if (attrs->channel_count == 3) {
			in->config.channels = 4;   //no 3 channels tdm in driver
			unsigned int stream_buf_bytes = PrimaryGetCaptureBufferSize((struct AudioHwStream *)&in->stream) * in->config.channels /
											in->requested_channels * 10;   // *4chan/3chan
			HAL_AUDIO_VERBOSE("malloc stream_buf:%d in->config.channels:%ld, in->requested_channels:%ld", stream_buf_bytes, in->config.channels, in->requested_channels);
			in->stream_buf = (char *) malloc(stream_buf_bytes);
		} /*else if (attrs->channel_count == 1) {
			in->config.channels = 2;   //no 1 channels tdm in driver
			unsigned int stream_buf_bytes = PrimaryGetCaptureBufferSize((struct AudioHwStream *)&in->stream) * in->config.channels /
											in->requested_channels * 10;   // *4chan/3chan
			in->stream_buf = (char *) malloc(stream_buf_bytes);
		} */else {
			in->config.channels = attrs->channel_count;
		}
	}

	in->standby = 1;

	in->rframe = 0;

	rtw_mutex_init(&in->lock);

	ladap->input = in;

	in->config.frame_size = PrimaryAudioHwCaptureFrameSize(&in->stream) * in->config.channels / in->requested_channels;
	HAL_AUDIO_VERBOSE("rate = %ld , channels = %ld, format = %ld, period_size = %d, period_count = %d, frame_size = %ld",
		  in->config.rate, in->config.channels, in->config.format, in->config.period_size, in->config.period_count, in->config.frame_size);

	if (in->in_pcm == NULL) {
		in->in_pcm = stream_rx_init(in->config);
	}

	return &in->stream;
}
