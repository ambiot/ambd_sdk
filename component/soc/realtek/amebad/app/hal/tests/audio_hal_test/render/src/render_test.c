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

//#define LOG_NDEBUG 0
#define LOG_TAG "RenderTest"

#include "platform_stdlib.h"
#include "hardware/audio/audio_hw_manager.h"

#define TEST_PLAYBACK 1
#define TEST_16000 0
#define TEST_48000 0
#define TEST_SINE 1

#if TEST_PLAYBACK
#if TEST_16000
#include "16000_2ch_16b.c"
#endif
#if TEST_48000
#include "48000_2ch_16b.c"
#endif
#endif

u32 sine32_48k[96] = {
	0X00000000,	0X00000000, 0X10B50000, 0X10B50000, 0X21200000, 0X21200000, 0X30FB0000, 0X30FB0000, 0X3FFF0000, 0X3FFF0000, 0X4DEB0000, 0X4DEB0000,
	0X5A820000,	0X5A820000, 0X658C0000, 0X658C0000, 0X6ED90000, 0X6ED90000, 0X76410000, 0X76410000, 0X7BA30000,	0X7BA30000, 0X7EE70000, 0X7EE70000,
	0X7FFF0000, 0X7FFF0000, 0X7EE70000, 0X7EE70000, 0X7BA30000, 0X7BA30000, 0X76410000, 0X76410000,	0X6ED90000,	0X6ED90000, 0X658C0000, 0X658C0000,
	0X5A820000,	0X5A820000, 0X4DEB0000, 0X4DEB0000, 0X3FFF0000, 0X3FFF0000, 0X30FB0000, 0X30FB0000, 0X21200000, 0X21200000, 0X10B50000, 0X10B50000,
	0X00000000,	0X00000000, 0XEF4A0000, 0XEF4A0000, 0XDEDF0000, 0XDEDF0000, 0XCF040000, 0XCF040000, 0XC0000000, 0XC0000000,	0XB2140000,	0XB2140000,
	0XA57D0000,	0XA57D0000, 0X9A730000, 0X9A730000,	0X91260000,	0X91260000, 0X89BE0000, 0X89BE0000,	0X845C0000,	0X845C0000, 0X81180000, 0X81180000,
	0X80000000,	0X80000000,	0X81180000,	0X81180000,	0X845C0000,	0X845C0000, 0X89BE0000, 0X89BE0000, 0X91260000, 0X91260000, 0X9A730000, 0X9A730000,
	0XA57D0000, 0XA57D0000, 0XB2140000,	0XB2140000,	0XC0000000, 0XC0000000,	0XCF040000, 0XCF040000, 0XDEDF0000, 0XDEDF0000, 0XEF4A0000,	0XEF4A0000
};

u16 sine_48k[96] = {
	0X0000,	0X0000, 0X10B5, 0X10B5, 0X2120, 0X2120, 0X30FB, 0X30FB, 0X3FFF, 0X3FFF, 0X4DEB, 0X4DEB,
	0X5A82,	0X5A82, 0X658C, 0X658C, 0X6ED9, 0X6ED9, 0X7641, 0X7641, 0X7BA3,	0X7BA3, 0X7EE7, 0X7EE7,
	0X7FFF, 0X7FFF, 0X7EE7, 0X7EE7, 0X7BA3, 0X7BA3, 0X7641, 0X7641,	0X6ED9,	0X6ED9, 0X658C, 0X658C,
	0X5A82,	0X5A82, 0X4DEB, 0X4DEB, 0X3FFF, 0X3FFF, 0X30FB, 0X30FB, 0X2120, 0X2120, 0X10B5, 0X10B5,
	0X0000,	0X0000, 0XEF4A, 0XEF4A, 0XDEDF, 0XDEDF, 0XCF04, 0XCF04, 0XC000, 0XC000,	0XB214,	0XB214,
	0XA57D,	0XA57D, 0X9A73, 0X9A73,	0X9126,	0X9126, 0X89BE, 0X89BE,	0X845C,	0X845C, 0X8118, 0X8118,
	0X8000,	0X8000,	0X8118,	0X8118,	0X845C,	0X845C, 0X89BE, 0X89BE, 0X9126, 0X9126, 0X9A73, 0X9A73,
	0XA57D, 0XA57D, 0XB214,	0XB214,	0XC000, 0XC000,	0XCF04, 0XCF04, 0XDEDF, 0XDEDF, 0XEF4A,	0XEF4A
};

static void PlaySample(unsigned int channels, unsigned int rate, unsigned int bits);

void AudioHwRenderTestApp(u8  *argv[])
{
	unsigned int rate = 16000;
	unsigned int num_channels = 2;
	unsigned int bits_per_sample = 16;

	/* parse command line arguments */
	while (*argv) {
		if (_strcmp(*argv, "-c") == 0) {
			argv++;
			if (*argv) {
				num_channels = atoi(*argv);
			}
		}
		if (_strcmp(*argv, "-r") == 0) {
			argv++;
			if (*argv) {
				rate = atoi(*argv);
			}
		}
		if (_strcmp(*argv, "-b") == 0) {
			argv++;
			if (*argv) {
				bits_per_sample = atoi(*argv);
			}
		}
		if (*argv) {
			argv++;
		}
	}

	PlaySample(num_channels, rate, bits_per_sample);
}

static void PlaySample(unsigned int channels, unsigned int rate, unsigned int bits)
{

	struct AudioHwManager *audio_manager;
	struct AudioHwAdapter *out_audio_adapter;
	struct AudioHwRender *audio_render;
	struct AudioHwAdapterDescriptor *out_adapter_desc;
	struct AudioHwPort render_port;
	AudioHwFormat format;
	unsigned int frames_played = 0;
	unsigned int play_frame_size = rate * 5; //5s data
#if (TEST_PLAYBACK && (TEST_16000 || TEST_48000))
	int i;
#endif
	printf("play sample channels:%u, rate:%u, bits=%u \n", channels, rate, bits);

	switch (bits) {
	case 16:
		format = AUDIO_HW_FORMAT_PCM_16_BIT;
		break;
	case 32:
		format = AUDIO_HW_FORMAT_PCM_32_BIT;
		break;
	default:
		break;
	}

	/*init render_port*/
	render_port.dir = AUDIO_HW_PORT_OUT;
	render_port.port_id = 0;
	render_port.port_name = NULL;

	/*init audio_manager*/
	audio_manager = GetAudioHwManagerFuncs();
	if (audio_manager == NULL) {
		printf("Get AudioHwManager failed \n");
		return;
	}

	/*get descs and size*/
	int32_t adapters_size = -1;
	struct AudioHwAdapterDescriptor *descs = NULL;
	audio_manager->GetAllAdapters(audio_manager, &descs, &adapters_size);
	if (adapters_size < 0) {
		printf("No adapter in AudioHwManager \n");
		return;
	}

	/*load adapters*/
	for (int index = 0; index < adapters_size; index++) {
		struct AudioHwAdapterDescriptor *desc = &descs[index];
		for (uint32_t port = 0; (desc != NULL && port < desc->port_num); port++) {
			printf("check for audio port \n");
			if (desc->ports[port].dir == AUDIO_HW_PORT_OUT &&
				(audio_manager->LoadAdapter(audio_manager, desc, &out_audio_adapter)) == 0) {
				// TODO: actually we should GetPortCapability to confirm support
				render_port = desc->ports[port];
				out_adapter_desc = desc;
				break;
			}
		}
	}
	if (out_audio_adapter == NULL) {
		printf("Load audio adapter failed \n");
		return;
	}

	/*create Render*/
	struct AudioHwSampleAttributes param;
	param.sample_rate = rate;
	param.channel_count = channels;
	param.format = format;
	param.interleaved = false;
	struct AudioHwDeviceDescriptor device_desc;
	device_desc.port_id = render_port.port_id;
	device_desc.pins = AUDIO_HW_PIN_OUT_SPEAKER;
	device_desc.desc = NULL;
	int32_t ret = out_audio_adapter->CreateRender(out_audio_adapter, &device_desc, &param, &audio_render);
	if (ret != 0 || audio_render == NULL) {
		printf("Create audio render failed \n");
		return;
	}

#if TEST_PLAYBACK
	/*get buf size from audio hal, getbuffersize returns period bytes*/
	ssize_t size = ((struct AudioHwStream *)audio_render)->GetBufferSize((struct AudioHwStream *)audio_render);

	//printf("test get size = %ld \n", size);
	/*write data to render*/

#if TEST_16000
	i = 0;
	if (rate == 16000) {
		i = 0;
		while (1) {
			audio_render->Write(audio_render, ((u8 *)birds_sing + i * size), size);
			frames_played += size / 4;
			if (frames_played >= play_frame_size) {
				break;
			}
			i++;
			if ((i + 2)*size > birds_sing_size * 4) {
				i = 0;
			}
		}
	}
#endif

#if TEST_48000
	if (rate == 48000) {
		while (1) {
			audio_render->Write(audio_render, ((u8 *)sample + i * size), size);
			frames_played += size / 4;
			if (frames_played >= play_frame_size) {
				break;
			}
			i++;
			if ((i + 2)*size > sample_size * 4) {
				i = 0;
			}
		}
	}
#endif

#if TEST_SINE
	if (rate == 48000) {
		while (1) {
			if (format == AUDIO_HW_FORMAT_PCM_32_BIT) {
				size = 96 * 4;
				audio_render->Write(audio_render, (u8 *)sine32_48k, size);
				frames_played += size / 8;
			} else if (format == AUDIO_HW_FORMAT_PCM_16_BIT) {
				size = 96 * 2;
				audio_render->Write(audio_render, (u8 *)sine_48k, size);
				frames_played += size / 4;
			}
			if (frames_played >= play_frame_size) {
				break;
			}
		}
	}
#endif
#endif

	out_audio_adapter->DestroyRender(out_audio_adapter, audio_render);
	/*play end, release*/
	if (audio_manager != NULL) {
		audio_manager->UnloadAdapter(audio_manager, out_adapter_desc, &out_audio_adapter);
		DestoryAudioHwManager(&audio_manager);
		out_adapter_desc = NULL;
	}
}

u32
CmdAudioHalRenderTest(
	IN	u16 argc,
	IN	u8	*argv[]
)

{
	(void) argc;
	AudioHwRenderTestApp(argv);
	return _TRUE;
}

CMD_TABLE_DATA_SECTION
const COMMAND_TABLE  audio_render_test_cmd_table[] = {
	{
		(const u8 *)"AudioHwRender",  1, CmdAudioHalRenderTest, (const u8 *)"\tAudioHwRender \n"
		"\t\t AudioHwRender -r 48000\n"
	},
};
