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
#define LOG_TAG "PrimaryAudioHwRender"
//#define LOG_NDEBUG 0

#include "hal_audio_debug.h"
#include "osdep_service.h"

#include "hardware/audio/audio_hw_types.h"
#include "hardware/audio/audio_hw_utils.h"
#include "hardware/audio/audio_hw_render.h"
#include "hardware/audio/audio_hw_adapter.h"

#include "ameba_audio_driver.h"
#include "primary_audio_hw_adapter.h"

#define DEFAULT_OUT_SAMPLING_RATE 16000
#define SHORT_PERIOD_SIZE         2048
#define SHORT_PERIOD_COUNT        4

struct stream_config pcm_output_config = {
	.channels = 2,
	.rate = DEFAULT_OUT_SAMPLING_RATE,
	.format = AUDIO_HW_FORMAT_PCM_16_BIT,
	.period_size = SHORT_PERIOD_SIZE,
	.period_count = SHORT_PERIOD_COUNT,
};

struct PrimaryAudioHwRender {
	struct AudioHwRender stream;

	_mutex lock;
	struct stream_config config;
	struct stream *out_pcm;
	char *buffer;
	size_t buffer_frames;
	int standby;
	AudioHwFormat format;
	uint32_t channel_count;
	uint32_t sample_rate;
	uint32_t period_size;
	struct PrimaryAudioHwAdapter *adap;
	struct AudioHwDeviceDescriptor desc;

	uint64_t written;
};

static inline size_t PrimaryAudioHwRenderFrameSize(const struct AudioHwRender *s)
{
	int chan_samp_sz;
	AudioHwFormat format = s->common.GetFormat(&s->common);

	if (AudioIsLinearPCM(format)) {
		chan_samp_sz = GetAudioBytesPerSample(format);
		return s->common.GetChannels(&s->common) * chan_samp_sz;
	}

	return sizeof(int8_t);
}

static uint32_t PrimaryGetRenderSampleRate(const struct AudioHwStream *stream)
{
	struct PrimaryAudioHwRender *out = (struct PrimaryAudioHwRender *)stream;
	return out->sample_rate;
}

static int PrimarySetRenderSampleRate(struct AudioHwStream *stream, uint32_t rate)
{
	struct PrimaryAudioHwRender *out = (struct PrimaryAudioHwRender *)stream;
	out->sample_rate = rate;
	return 0;
}

static size_t PrimaryGetRenderBufferSize(const struct AudioHwStream *stream)
{
	size_t ret = 0;
	struct PrimaryAudioHwRender *out = (struct PrimaryAudioHwRender *)stream;
	size_t size = (out->period_size * out->sample_rate) / out->sample_rate;
	size = ((size + 15) / 16) * 16;
	ret = size * PrimaryAudioHwRenderFrameSize((const struct AudioHwRender *)stream);
	return ret;
}

static uint32_t PrimaryGetRenderChannels(const struct AudioHwStream *stream)
{
	struct PrimaryAudioHwRender *out = (struct PrimaryAudioHwRender *)stream;

	return out->channel_count;
}

static int PrimarySetRenderChannels(const struct AudioHwStream *stream, uint32_t channel)
{
	struct PrimaryAudioHwRender *out = (struct PrimaryAudioHwRender *)stream;

	out->channel_count = channel;
	return 0;
}

static AudioHwFormat PrimaryGetRenderFormat(const struct AudioHwStream *stream)
{
	struct PrimaryAudioHwRender *out = (struct PrimaryAudioHwRender *)stream;

	return out->format;
}

static int PrimarySetRenderFormat(struct AudioHwStream *stream, AudioHwFormat format)
{
	(void) stream;
	(void) format;
	return 0;
}

/* must be called with hw device and output stream mutexes locked */
static int DoStandbyOutput(struct PrimaryAudioHwRender *out)
{
	if (!out->standby) {
		out->standby = 1;
	}
	return 0;
}

static int PrimaryStandbyRender(struct AudioHwStream *stream)
{
	struct PrimaryAudioHwRender *out = (struct PrimaryAudioHwRender *)stream;
	int status;

	rtw_mutex_get(&out->adap->lock);
	rtw_mutex_get(&out->lock);
	status = DoStandbyOutput(out);
	rtw_mutex_put(&out->lock);
	rtw_mutex_put(&out->adap->lock);

	return status;
}

static int PrimaryDumpRender(const struct AudioHwStream *stream, int fd)
{
	(void) stream;
	(void) fd;
	return 0;
}

static int PrimarySetRenderParameters(struct AudioHwStream *stream, const char *kvpairs)
{
	(void) stream;
	(void) kvpairs;
	return 0;
}

static char *PrimaryGetRenderParameters(const struct AudioHwStream *stream, const char *keys)
{
	(void) stream;
	(void) keys;
	return strdup("");
}

static int PrimaryGetPresentationPosition(const struct AudioHwRender *stream, uint32_t *frames, struct timespec *timestamp)
{
	(void) stream;
	(void) frames;
	(void) timestamp;
	return 0;
}

static uint32_t PrimaryGetRenderLatency(const struct AudioHwRender *stream)
{
	(void) stream;
	return 15;
}

static int PrimarySetRenderVolume(struct AudioHwRender *stream, float left,
								  float right)
{
	(void) stream;
	(void) left;
	(void) right;
	return 0;
}

/* must be called with hw device and output stream mutexes locked */
static int StartAudioHwRender(struct PrimaryAudioHwRender *out)
{
	HAL_AUDIO_VERBOSE("start output stream enter");

	stream_tx_start(out->out_pcm);

	return OSAL_OK;
}

static ssize_t PrimaryRenderWrite(struct AudioHwRender *stream, const void *buffer,
								  size_t bytes)
{
	//HAL_AUDIO_INFO("primaryRenderWrite: bytes: %u", bytes);

	int ret = 0;
	struct PrimaryAudioHwRender *out = (struct PrimaryAudioHwRender *)stream;
	struct PrimaryAudioHwAdapter *adap = out->adap;

	size_t frame_size = PrimaryAudioHwRenderFrameSize((const struct AudioHwRender *)stream);
	size_t in_frames = bytes / frame_size;

	rtw_mutex_get(&adap->lock);
	rtw_mutex_get(&out->lock);
	if (out->standby) {
		ret = StartAudioHwRender(out);
		if (ret != 0) {
			HAL_AUDIO_ERROR("start render fail");
			rtw_mutex_put(&adap->lock);
			goto exit;
		}
		out->standby = 0;
	}
	rtw_mutex_put(&adap->lock);

	/* Write to all active PCMs */
	if (out->out_pcm) {
		ret = stream_tx_write(out->out_pcm, (void *)buffer, bytes);
	} else {
		HAL_AUDIO_ERROR("out pcm is NULL!!!");
	}

	//write successfully
	if (ret == 0) {
		out->written += in_frames;
	}

exit:
	rtw_mutex_put(&out->lock);
	//if (ret != 0) {
	//	HAL_AUDIO_ERROR("primaryRenderWrite failed");
		uint32_t msec = (int64_t)bytes * 1000 / PrimaryAudioHwRenderFrameSize(stream) /
				PrimaryGetRenderSampleRate(&stream->common);
		vTaskDelay(msec / 2 / portTICK_RATE_MS);
	//}

	return bytes;
}

void CloseAudioHwRender(struct AudioHwRender *render)
{
	struct PrimaryAudioHwRender *out = (struct PrimaryAudioHwRender *)render;

	PrimaryStandbyRender(&render->common);

	if (out->out_pcm) {
		stream_tx_close(out->out_pcm);
		out->out_pcm = NULL;
	}

	rtw_mutex_free(&out->lock);
	rtw_free(render);
	render = NULL;
}

struct AudioHwRender *GetAudioHwRenderFuncs(struct AudioHwAdapter *adapter, const struct AudioHwDeviceDescriptor *desc, const struct AudioHwSampleAttributes *attrs)
{
	struct PrimaryAudioHwAdapter *adap = (struct PrimaryAudioHwAdapter *)adapter;
	struct PrimaryAudioHwRender *out;

	out = (struct PrimaryAudioHwRender *)rtw_zmalloc(sizeof(struct PrimaryAudioHwRender));
	if (!out) {
		return NULL;
	}

	out->adap = adap;
	out->desc = *desc;

	out->stream.common.GetSampleRate = PrimaryGetRenderSampleRate;
	out->stream.common.SetSampleRate = PrimarySetRenderSampleRate;
	out->stream.common.GetBufferSize = PrimaryGetRenderBufferSize;
	out->stream.common.GetChannels = PrimaryGetRenderChannels;
	out->stream.common.SetChannels = PrimarySetRenderChannels;
	out->stream.common.GetFormat = PrimaryGetRenderFormat;
	out->stream.common.SetFormat = PrimarySetRenderFormat;
	out->stream.common.Standby = PrimaryStandbyRender;
	out->stream.common.Dump = PrimaryDumpRender;
	out->stream.common.SetParameters = PrimarySetRenderParameters;
	out->stream.common.GetParameters = PrimaryGetRenderParameters;
	out->stream.GetPresentationPosition = PrimaryGetPresentationPosition;
	out->stream.GetLatency = PrimaryGetRenderLatency;
	out->stream.SetVolume = PrimarySetRenderVolume;
	out->stream.Write = PrimaryRenderWrite;

	out->format = AUDIO_HW_FORMAT_PCM_16_BIT;
	out->channel_count = 2;
	out->sample_rate = DEFAULT_OUT_SAMPLING_RATE;
	out->period_size = SHORT_PERIOD_SIZE;
	out->adap = adap;
	out->standby = 1;
	out->written = 0;

	AudioHwFormat format = out->stream.common.GetFormat(&out->stream.common);
	uint32_t channel_count =  out->stream.common.GetChannels(&out->stream.common);
	uint32_t sample = out->stream.common.GetSampleRate(&out->stream.common);

	if (format != attrs->format) {
		out->format =  attrs->format;
	}
	if (channel_count != attrs->channel_count) {
		out->channel_count = attrs->channel_count;
	}
	if (sample != attrs->sample_rate) {
		out->sample_rate = attrs->sample_rate;
	}

	rtw_mutex_init(&out->lock);

	adap->output = out;

	out->config = pcm_output_config;

	out->config.rate = out->sample_rate; // update sample_rate according to top level player
	out->config.format = out->format;
	out->config.channels = out->channel_count;
	out->config.frame_size = PrimaryAudioHwRenderFrameSize(&out->stream);
	out->config.period_size = out->period_size;

	if (out->out_pcm == NULL) {
		HAL_AUDIO_VERBOSE("startAudioHwRender samplerate:%ld, format:%ld, channel:0x%lx, framesize:%ld, period_size:%d", out->config.rate, out->config.format, out->config.channels,
			  out->config.frame_size, out->config.period_size);
		out->out_pcm = stream_tx_init(out->config);

	} else {
		HAL_AUDIO_DEBUG("out pcm has been opened");
	}

	return &out->stream;
}
