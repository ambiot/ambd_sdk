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

#define LOG_TAG "CaptureTest"
//#define LOG_NDEBUG 0

#include "platform_stdlib.h"
#include "ameba_soc.h"
#include "hardware/audio/audio_hw_manager.h"

static unsigned int Capture_Sample(unsigned int channels, unsigned int rate, unsigned int record_bytes_one_time);

void AudioHwCaptureTestApp(u8  *argv[])
{
	unsigned int channels = 2;
	unsigned int rate = 16000;
	unsigned int frames;
	unsigned int record_bytes_one_time = 4096;

	/* parse command line arguments */
	while (*argv) {
		if (strcmp(*argv, "-c") == 0) {
			argv++;
			if (*argv) {
				channels = atoi(*argv);
			}
		} else if (strcmp(*argv, "-r") == 0) {
			argv++;
			if (*argv) {
				rate = atoi(*argv);
			}
		} else if (strcmp(*argv, "-b") == 0) {
			argv++;
			if (*argv) {
				record_bytes_one_time = atoi(*argv);
			}
		}
		if (*argv) {
			argv++;
		}
	}

	frames = Capture_Sample(channels, rate, record_bytes_one_time);

	printf("Captured %d frames \n", frames);

	return;
}

/*in order to test capture data, directly play it out through spk*/
static unsigned int Capture_Sample(unsigned int channels, unsigned int rate, unsigned int record_bytes_one_time)
{
	char *buffer;
	unsigned int size;
	unsigned int bytes_read = 0;
	unsigned int frames = 0;
	int32_t ret;
	unsigned int record_size = rate * 5 * 4; //5s data, 4 bytes per frame

	struct AudioHwManager *audio_manager;
	struct AudioHwAdapter *cap_audio_adapter;
	struct AudioHwCapture *audio_capture;
	struct AudioHwAdapterDescriptor *cap_adapter_desc;
	struct AudioHwPort capture_port;
	struct AudioHwRender *audio_render;
	struct AudioHwAdapter *out_audio_adapter;
	struct AudioHwAdapterDescriptor *out_adapter_desc;
	struct AudioHwPort render_port;

	/*init audio manager*/
	audio_manager = GetAudioHwManagerFuncs();
	if (audio_manager == NULL) {
		printf("Get AudioHwManager failed \n");
		return -1;
	}

	/*get all adapters*/
	int32_t adapters_size = -1;
	struct AudioHwAdapterDescriptor *descs = NULL;
	audio_manager->GetAllAdapters(audio_manager, &descs, &adapters_size);
	if (adapters_size < 0) {
		printf("No adapter in AudioHwManager \n");
		return -1;
	}

	/*create param for both cap & playback*/
	struct AudioHwSampleAttributes param;
	param.sample_rate = rate;
	param.channel_count = channels;
	param.format = AUDIO_HW_FORMAT_PCM_16_BIT;  // TODO: add format
	param.interleaved = false;

	/**************************************************************************************************
	 * **************************************playback init*********************************************
	 * ************************************************************************************************/
	/*init cap AudioHwPort*/
	capture_port.dir = AUDIO_HW_PORT_IN;
	capture_port.port_id = 0;
	capture_port.port_name = NULL;

	/*get audio adapter for cap*/
	for (int index = 0; index < adapters_size; index++) {
		struct AudioHwAdapterDescriptor *desc = &descs[index];
		for (unsigned int port = 0; (desc != NULL && port < desc->port_num); port++) {
			if (desc->ports[port].dir == AUDIO_HW_PORT_IN &&
				(audio_manager->LoadAdapter(audio_manager, desc, &cap_audio_adapter)) == 0) {
				// TODO: actually we should GetPortCapability to confirm support
				capture_port = desc->ports[port];
				cap_adapter_desc = desc;
				break;
			}
		}
	}

	if (cap_audio_adapter == NULL) {
		printf("Load audio adapter failed \n");
		return -1;
	}

	/*create audio capture*/
	struct AudioHwDeviceDescriptor cap_device_desc;
	cap_device_desc.port_id = capture_port.port_id;
	cap_device_desc.pins = AUDIO_HW_PIN_IN_MIC;
	cap_device_desc.desc = NULL;
	ret = cap_audio_adapter->CreateCapture(cap_audio_adapter, &cap_device_desc, &param, &audio_capture);
	if (ret != 0 || audio_capture == NULL) {
		printf("Create audio Capture failed \n");
		return -1;
	}

	/**************************************************************************************************
	 * **************************************capture init**********************************************
	 * ************************************************************************************************/
	/*init render_port*/
	render_port.dir = AUDIO_HW_PORT_OUT;
	render_port.port_id = 0;
	render_port.port_name = NULL;

	/*get out adapter*/
	for (int index = 0; index < adapters_size; index++) {
		struct AudioHwAdapterDescriptor *desc = &descs[index];
		for (unsigned int port = 0; (desc != NULL && port < desc->port_num); port++) {
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
		return -1;
	}

	/*create Render*/
	struct AudioHwDeviceDescriptor device_desc;
	device_desc.port_id = render_port.port_id;
	device_desc.pins = AUDIO_HW_PIN_OUT_SPEAKER;
	device_desc.desc = NULL;
	ret = out_audio_adapter->CreateRender(out_audio_adapter, &device_desc, &param, &audio_render);
	if (ret != 0 || audio_render == NULL) {
		printf("Create audio render failed \n");
		return -1;
	}

	/**************************************************************************************************
	 * ************************************cap=>playback test******************************************
	 * ************************************************************************************************/
	size = record_bytes_one_time;
	/*	size = ((struct AudioHwStream *)audio_capture)->GetBufferSize((struct AudioHwStream *)audio_capture);

		if (size != ((struct AudioHwStream *)audio_render)->GetBufferSize((struct AudioHwStream *)audio_render)) {
			printf("cap size != play size,error \n");
			goto end;
		}
	*/

	buffer = (char *) malloc(size);
	if (!buffer) {
		free(buffer);
		return 0;
	}

	printf("Capturing sample: %d ch, %d hz\n", channels, rate);
	do {
		audio_capture->Read(audio_capture, buffer, size);
		audio_render->Write(audio_render, buffer, size);
		bytes_read += size;
	} while (bytes_read < record_size);

	frames = bytes_read / 4;

end:
	free(buffer);

	if (audio_capture != NULL) {
		cap_audio_adapter->DestroyCapture(cap_audio_adapter, audio_capture);
		audio_capture = NULL;
	}

	if (audio_render != NULL) {
		out_audio_adapter->DestroyRender(out_audio_adapter, audio_render);
		audio_render = NULL;
	}

	if (audio_manager != NULL) {
		audio_manager->UnloadAdapter(audio_manager, cap_adapter_desc, &cap_audio_adapter);
		cap_adapter_desc = NULL;
		audio_manager->UnloadAdapter(audio_manager, out_adapter_desc, &out_audio_adapter);
		out_adapter_desc = NULL;
		DestoryAudioHwManager(&audio_manager);
	}

	return frames;
}

u32
CmdAudioHalCaptureTest(
	IN	u16 argc,
	IN	u8	*argv[]
)

{
	(void) argc;
	AudioHwCaptureTestApp(argv);
	return _TRUE;
}

CMD_TABLE_DATA_SECTION
const COMMAND_TABLE  audio_capture_test_cmd_table[] = {
	{
		(const u8 *)"AudioHwCapture",  1, CmdAudioHalCaptureTest, (const u8 *)"\tAudioHwCapture \n"
		"\t\t AudioHwCapture -r 16000 -c 2 -b 8192\n"
	},
};