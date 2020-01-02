#include "example_audio_m4a_selfparse.h"
#include "wifi_conf.h"
#include "lwip/arch.h"
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>
#include <disk_if/inc/sdcard.h>
#include "section_config.h"
#include "libAACdec/include/aacdecoder_lib.h"
#include "rl6548.h"
#ifdef CONFIG_EXAMPLE_AUDIO_M4A_SELFPARSE
#define BITS_PER_CHANNEL	WL_16
#define FILE_NAME "AudioSDTest.m4a"    //Specify the file name you wish to play that is present in the SDCARD

//***global variables start***//
#define BUF_LEN 128000
#define MAX_STSC_NUM 1024
#define MAX_SAMPLE_NUM 102400
#define MAX_CHUNK_NUM 10240

typedef struct {
    int first_trunk;
    int samples_per_trunk;
    int sample_description_id;
} stsc_t;
stsc_t stsc_tab[MAX_STSC_NUM];
int stsc_num;

int m4a_len = 0;
//char m4a_buf[BUF_LEN];
//char *m4a_buf = (char *)(0x02000000);
char *m4a_buf = NULL;

int sample_freq_index;
int sample_channel;
int sample_object_type;

unsigned char asc_buf[64]; // AudioSpecificConfig
int asc_len = 0;

//int sample_size_tab[MAX_SAMPLE_NUM];
//int *sample_size_tab = (int *)(0x02100000);
int *sample_size_tab = NULL;

int sample_num;

//int chunk_offset_tab[MAX_CHUNK_NUM];
//int *chunk_offset_tab = (int *)(0x02180000);
int *chunk_offset_tab = NULL;

int chunk_num;

HANDLE_AACDECODER handle;
void *wav = NULL;
AAC_DECODER_ERROR err;

__attribute__((aligned(4))) uint8_t input_buf[1600];
__attribute__((aligned(4))) int16_t decode_buf[4096];
int frame_size = 0;
CStreamInfo *m4ainfo;
int first_frame = 1;
int pcm_size = 0;

SAL_PSRAM_MNGT_ADPT  PSRAMTestMngtAdpt[1];

static SP_InitTypeDef SP_InitStruct;
static SP_GDMA_STRUCT SPGdmaStruct;
static SP_OBJ sp_obj;
static SP_TX_INFO sp_tx_info;

static u8 sp_tx_buf[SP_DMA_PAGE_SIZE*SP_DMA_PAGE_NUM];
static u8 sp_zero_buf[SP_ZERO_BUF_SIZE];
//****global variables end****//

typedef void (*sample_cb_t)(int offset, int len, FIL m_file);

/*
 * The memmem() function finds the start of the first occurrence of the
 * substring 'needle' of length 'nlen' in the memory area 'haystack' of
 * length 'hlen'.
 *
 * The return value is a pointer to the beginning of the sub-string, or
 * NULL if the substring is not found.
 */
void *memmem(const char *haystack, size_t hlen, const void *needle, size_t nlen)
{
    int needle_first;
    const char *p = haystack;
    size_t plen = hlen;

    if (!nlen)
        return NULL;

    needle_first = *(unsigned char *)needle;

    while (plen >= nlen && (p = memchr(p, needle_first, plen - nlen + 1)))
    {
        if (!memcmp(p, needle, nlen))
            return (void *)p;

        p++;
        plen = hlen - (p - haystack);
    }

    return NULL;
}

VOID
PSRAMISRHandle(
    IN  VOID *Data
)
{
         u32 intr_status_cal_fail = 0; 
         u32 intr_status_timeout = 0; 
         
         intr_status_cal_fail = (PSRAM_PHY_REG_Read(0x0) & BIT16) >> 16;
         PSRAM_PHY_REG_Write(0x0, PSRAM_PHY_REG_Read(0x0)) ;
         intr_status_timeout = (PSRAM_PHY_REG_Read(0x1C) & BIT31) >> 31;
         PSRAM_PHY_REG_Write(0x1C, PSRAM_PHY_REG_Read(0x1C)) ;
         DBG_8195A("cal_fail = %x timeout = %x\n",intr_status_cal_fail, intr_status_timeout);
}


void PSRAMInit(void){
         u32 temp;
         PSAL_PSRAM_MNGT_ADPT  pSalPSRAMMngtAdpt = NULL;
         pSalPSRAMMngtAdpt = &PSRAMTestMngtAdpt[0];
         InterruptRegister((IRQ_FUN) PSRAMISRHandle, PSRAMC_IRQ, (u32) (pSalPSRAMMngtAdpt), 3);
         InterruptEn(PSRAMC_IRQ, 3);

         /*set rwds pull down*/
         temp = HAL_READ32(PINMUX_REG_BASE, 0x104);
         temp &= ~(PAD_BIT_PULL_UP_RESISTOR_EN | PAD_BIT_PULL_DOWN_RESISTOR_EN);
         temp |= PAD_BIT_PULL_DOWN_RESISTOR_EN;
         HAL_WRITE32(PINMUX_REG_BASE, 0x104, temp);

         PSRAM_CTRL_StructInit(&pSalPSRAMMngtAdpt->PCTL_InitStruct);
         PSRAM_CTRL_Init(&pSalPSRAMMngtAdpt->PCTL_InitStruct); 
         
         PSRAM_PHY_REG_Write(0x0, (PSRAM_PHY_REG_Read(0x0)& (~0x1)));
         
         /*set N/J initial value HW calibration*/
         PSRAM_PHY_REG_Write(0x4, 0x2030316);

         /*start HW calibration*/
         PSRAM_PHY_REG_Write(0x0, 0x111);
}


void check_m4a_file(FIL	*file)
{
	FIL m_file = *file;
	int bytes_left = 0;
	int file_size = 0;
	FRESULT res;
	file_size = (&m_file)->fsize;
	bytes_left = file_size;
	do{
		/* Read a block */
		if(bytes_left >= BUF_LEN)
                {
                  res = f_read(&m_file, m4a_buf, BUF_LEN,(UINT*)&m4a_len);	
                  bytes_left = bytes_left - m4a_len;
                }
		else
		{
                  res = f_read(&m_file, m4a_buf, bytes_left,(UINT*)&m4a_len);	
				  bytes_left = bytes_left - m4a_len;
		}
		if((res != FR_OK))
		{
			printf("file Break!\n");
			break;
		}
		
		char* pos = (char*)memmem(m4a_buf, m4a_len, "stsd", 4);
		if (pos)
		{
			pos += 16;
			if (memcmp(pos, "mp4a", 4) != 0)
			{
				printf("only support m4a file, not found mp4a type\n");
                		return;
			}
			else
			{
				printf("find file success\n");
				return;
			}
		}
	}while(bytes_left>0);
	printf("only support m4a file, not found stsd box\n");
	return;
}

// this field is variable length, param vl return the real length 
int calc_desc_len(char* pos, int* vl)
{
    int len = 0;
    int i;
    for (i=0; i<4; i++)
    { 
        int c = pos[i];
        len = (len << 7) | (c & 0x7f);
        if (!(c & 0x80))
            break;
    }
    *vl = i + 1;
    return len;    
}

void parse_esds(FIL	*file)
{
	FIL m_file = *file;
	int bytes_left = 0;
	int file_size = 0;
    FRESULT res;
	file_size = (&m_file)->fsize;
	bytes_left = file_size;
	do
	{
		/* Read a block */
		if(bytes_left >= BUF_LEN)
                {
                  res = f_read(&m_file, m4a_buf, BUF_LEN,(UINT*)&m4a_len);	
                  bytes_left = bytes_left - m4a_len;
                }
		else
		{
                  res = f_read(&m_file, m4a_buf, bytes_left,(UINT*)&m4a_len);	
				  bytes_left = bytes_left - m4a_len;
		}	
		if((res != FR_OK))
		{
			printf("file Break!\n");
			break;
		}
		
		char* pos = memmem(m4a_buf, m4a_len, "esds", 4);
		if (pos)
		{
			int len, vl;
			pos += 8; // MP4ESDescrTag
			if (*pos != 0x03)
			{
				printf("not found MP4ESDescrTag\n");
				exit(1);
			}
			pos++;
			len = calc_desc_len(pos, &vl);
			pos += (vl + 3); // MP4DecConfigDescrTag
			if (*pos != 0x04)
			{   
				printf("not found MP4DecConfigDescrTag\n");
				exit(1);
			}
			pos++;
			len = calc_desc_len(pos, &vl);
			pos += (vl + 13); // MP4DecSpecificDescrTag
			if (*pos != 0x05)
			{
				printf("not found MP4DecSpecificDescrTag\n");
				exit(1);
			}
			pos++;
			len = calc_desc_len(pos, &vl);
			pos += vl;
			memcpy(asc_buf, pos, len);
			asc_len = len;
			sample_object_type = (asc_buf[0] & 0xf8) >> 3;
			sample_freq_index = ((asc_buf[0] & 0x7) << 1) | (asc_buf[1] >> 7);
			sample_channel = (asc_buf[1] >> 3) & 0x0f;
			printf("sample_object_type: %d\n", sample_object_type);
			printf("sample_freq_index: %d\n", sample_freq_index);
			printf("sample_channel: %d\n", sample_channel);
		}
	}while(bytes_left>0);
}

void parse_stsc(FIL	*file)
{
	FIL m_file = *file;
	int bytes_left = 0;
	int file_size = 0;
    FRESULT res;
	file_size = (&m_file)->fsize;
	bytes_left = file_size;
	do
	{
		//Read a block
		if(bytes_left >= BUF_LEN)
                {
                  res = f_read(&m_file, m4a_buf, BUF_LEN,(UINT*)&m4a_len);	
                  bytes_left = bytes_left - m4a_len;
                }
		else
		{
                  res = f_read(&m_file, m4a_buf, bytes_left,(UINT*)&m4a_len);	
				  bytes_left = bytes_left - m4a_len;
		}	
		if((res != FR_OK))
		{
			printf("file Break!\n");
			break;
		}
		
		char* pos = memmem(m4a_buf, m4a_len, "stsc", 4);
		int i;
		if (pos)
		{
			pos += 8; //number of entry
			stsc_num = _htonl(*(int*)pos);
			for (i=0; i<stsc_num; i++)
			{
				pos += 4; //first chunk
				stsc_tab[i].first_trunk = _htonl(*(int*)pos);
				pos += 4; //samples per chunk 
				stsc_tab[i].samples_per_trunk = _htonl(*(int*)pos);
				pos += 4; //sample description ID
				stsc_tab[i].sample_description_id = _htonl(*(int*)pos);
			}
			printf("stsc table len: %d\n", stsc_num);
		}
	}while(bytes_left>0);
	return;
}

void parse_stsz(FIL	*file)
{
	FIL m_file = *file;
	int bytes_left = 0;
	int file_size = 0;
    FRESULT res;
	file_size = (&m_file)->fsize;
	bytes_left = file_size;
	do
	{
		//Read a block
		if(bytes_left >= BUF_LEN)
                {
                  res = f_read(&m_file, m4a_buf, BUF_LEN,(UINT*)&m4a_len);	
                  bytes_left = bytes_left - m4a_len;
                }
		else
		{
                  res = f_read(&m_file, m4a_buf, bytes_left,(UINT*)&m4a_len);	
				  bytes_left = bytes_left - m4a_len;
		}	
		if((res != FR_OK))
		{
			printf("file Break!\n");
			break;
		}
		
		char* pos = memmem(m4a_buf, m4a_len, "stsz", 4);
		int sample_size = 0;
		int table_size = 0;
		int i;
		if (pos)
		{
			pos += 8; //sample size
			sample_size = _htonl(*(int*)pos);
			printf("sample size: %d\n", sample_size);
			if (sample_size == 0)
			{
				pos += 4; //table size
				table_size = _htonl(*(int*)pos);
				printf("table size: %d\n", table_size);
				for (i=0; i<table_size; i++)
				{
					pos += 4; //each sample size
					sample_size_tab[i] = _htonl(*(int*)pos);
					//printf("sample %d size: %d\n", i, sample_size_tab[i]);
				}
				sample_num = i;
			}
		}
	}while(bytes_left>0);
	return;
}

void parse_stco(FIL	*file)
{
	FIL m_file = *file;
	int bytes_left = 0;
	int file_size = 0;
	FRESULT res;
	file_size = (&m_file)->fsize;
	bytes_left = file_size;
	do
	{
		//Read a block
		if(bytes_left >= BUF_LEN)
                {
                  res = f_read(&m_file, m4a_buf, BUF_LEN,(UINT*)&m4a_len);	
                  bytes_left = bytes_left - m4a_len;
                }
		else
		{
                  res = f_read(&m_file, m4a_buf, bytes_left,(UINT*)&m4a_len);	
				  bytes_left = bytes_left - m4a_len;
		}	
		if((res != FR_OK))
		{
			printf("file Break!\n");
			break;
		}
		char* pos = memmem(m4a_buf, m4a_len, "stco", 4);
		int i;
		if (pos)
		{
			pos += 8; //number of entry
			chunk_num = _htonl(*(int*)pos);
			for (i=0; i<chunk_num; i++)
			{
				pos += 4; //chunk offset
				chunk_offset_tab[i] = _htonl(*(int*)pos);
			}
			printf("chunk num: %d\n", chunk_num);
		}
	}while(bytes_left>0);
	return;
}


void get_adts_head(char head[7], int len)
{
    head[0]  = 0xff;
    head[1]  = 0xf1;
    head[2]  = (unsigned char)((sample_object_type-1)<<6) | (unsigned char)(sample_freq_index<<2);
    head[3]  = (unsigned char)(sample_channel<<6) | (unsigned char)(((len+7)>>11)&0x3); 
    head[4]  = (unsigned char)(((len+7)>>3)&0xff);
    head[5]  = 0x1f | (unsigned char)(((len+7)<<5)&0xe0);
    head[6]  = 0xfc;
}

void iterate_samples_from_stsc(sample_cb_t sample_cb, FIL m_file)
{
    int chunk_index = 0;
    int sample_index = 0;
    int i, j, k;

    for (i=0; i<stsc_num; i++) // stsc
    {
        int n_chunk;
        int n_sample;
        if (i == stsc_num - 1) // last stsc
            n_chunk = chunk_num - stsc_tab[i].first_trunk + 1;
        else
            n_chunk = stsc_tab[i+1].first_trunk - stsc_tab[i].first_trunk;
        n_sample = stsc_tab[i].samples_per_trunk;
        for (j=0; j<n_chunk; j++) // chunk
        {
            int chunk_offset = chunk_offset_tab[chunk_index++];
            int sample_size_total = 0;
            for (k=0; k<n_sample; k++) // sample
            {
                int size = sample_size_tab[sample_index];
                sample_cb(chunk_offset + sample_size_total, size, m_file);
                sample_size_total += size;
                sample_index++;
            }
        }
    }
}

u8 *sp_get_free_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
	
	if (ptx_block->tx_gdma_own)
		return NULL;
	else{
		return ptx_block->tx_addr;
	}	
}

void sp_write_tx_page(u8 *src, u32 length)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
	
	memcpy(ptx_block->tx_addr, src, length);
	ptx_block->tx_length = length;	
	ptx_block->tx_gdma_own = 1;
	sp_tx_info.tx_usr_cnt++;
	if (sp_tx_info.tx_usr_cnt == SP_DMA_PAGE_NUM){
		sp_tx_info.tx_usr_cnt = 0;
	}
}

void sp_release_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);
	
	if (sp_tx_info.tx_empty_flag){
	}
	else{
		ptx_block->tx_gdma_own = 0;
		sp_tx_info.tx_gdma_cnt++;
		if (sp_tx_info.tx_gdma_cnt == SP_DMA_PAGE_NUM){
			sp_tx_info.tx_gdma_cnt = 0;
		}
	}
}

u8 *sp_get_ready_tx_page(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);
	
	if (ptx_block->tx_gdma_own){
		sp_tx_info.tx_empty_flag = 0;
		return ptx_block->tx_addr;
	}
	else{
		sp_tx_info.tx_empty_flag = 1;
		return sp_tx_info.tx_zero_block.tx_addr;	//for audio buffer empty case
	}
}

u32 sp_get_ready_tx_length(void)
{
	pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);

	if (sp_tx_info.tx_empty_flag){
		return sp_tx_info.tx_zero_block.tx_length;
	}
	else{
		return ptx_block->tx_length;
	}
}

void sp_tx_complete(void *Data)
{
	SP_GDMA_STRUCT *gs = (SP_GDMA_STRUCT *) Data;
	PGDMA_InitTypeDef GDMA_InitStruct;
	u32 tx_addr;
	u32 tx_length;
	
	GDMA_InitStruct = &(gs->SpTxGdmaInitStruct);

	/* Clear Pending ISR */
	GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
	
	sp_release_tx_page();
	tx_addr = (u32)sp_get_ready_tx_page();
	tx_length = sp_get_ready_tx_length();
	GDMA_SetSrcAddr(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_addr);
	GDMA_SetBlkSize(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_length>>2);
	
	GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, ENABLE);
}

void sp_rx_complete(void *data, char* pbuf)
{
	//
}

static void sp_init_hal(pSP_OBJ psp_obj)
{
	u32 div;

	PLL_Sel(PLL_PCM);
	
	//PLL_I2S_Set(ENABLE);		//enable 98.304MHz PLL. needed if fs=8k/16k/32k/48k/96k
	PLL_PCM_Set(ENABLE);		//enable 45.1584MHz PLL. needed if fs=44.1k/88.2k

	RCC_PeriphClockCmd(APBPeriph_AUDIOC, APBPeriph_AUDIOC_CLOCK, ENABLE);
	RCC_PeriphClockCmd(APBPeriph_SPORT, APBPeriph_SPORT_CLOCK, ENABLE);	

	//set clock divider to gen clock sample_rate*256 from 98.304M.
	switch(psp_obj->sample_rate){
		case SR_48K:
			div = 8;
			break;
		case SR_96K:
			div = 4;
			break;
		case SR_32K:
			div = 12;
			break;
		case SR_16K:
			div = 24;
			break;
		case SR_8K:
			div = 48;
			break;
		case SR_44P1K:
			div = 4;
			break;
		case SR_88P2K:
			div = 2;
			break;
		default:
			DBG_8195A("sample rate not supported!!\n");
			break;
	}
	PLL_Div(div);

	/*codec init*/
	CODEC_Init(psp_obj->sample_rate, psp_obj->word_len, psp_obj->mono_stereo, psp_obj->direction);
}

static void sp_init_tx_variables(void)
{
	int i;

	for(i=0; i<SP_ZERO_BUF_SIZE; i++){
		sp_zero_buf[i] = 0;
	}
	sp_tx_info.tx_zero_block.tx_addr = (u32)sp_zero_buf;
	sp_tx_info.tx_zero_block.tx_length = (u32)SP_ZERO_BUF_SIZE;
	
	sp_tx_info.tx_gdma_cnt = 0;
	sp_tx_info.tx_usr_cnt = 0;
	sp_tx_info.tx_empty_flag = 0;
	
	for(i=0; i<SP_DMA_PAGE_NUM; i++){
		sp_tx_info.tx_block[i].tx_gdma_own = 0;
		sp_tx_info.tx_block[i].tx_addr = sp_tx_buf+i*SP_DMA_PAGE_SIZE;
		sp_tx_info.tx_block[i].tx_length = SP_DMA_PAGE_SIZE;
	}
}

static void initialize_audio(uint8_t ch_num, int sample_rate)
{
    printf("ch:%d sr:%d\r\n", ch_num, sample_rate);

	uint8_t smpl_rate_idx = SR_16K;
	uint8_t ch_num_idx = CH_STEREO;
	pSP_OBJ psp_obj = &sp_obj;
	u32 tx_addr;
	u32 tx_length;

	switch(ch_num){
    	case 1: ch_num_idx = CH_MONO;   break;
    	case 2: ch_num_idx = CH_STEREO; break;
    	default: break;
	}
	
	switch(sample_rate){
    	case 8000:  smpl_rate_idx = SR_8K;     break;
    	case 16000: smpl_rate_idx = SR_16K;    break;
    	//case 22050: smpl_rate_idx = SR_22p05K; break;
    	//case 24000: smpl_rate_idx = SR_24K;    break;		
    	case 32000: smpl_rate_idx = SR_32K;    break;
    	case 44100: smpl_rate_idx = SR_44P1K;  break;
    	case 48000: smpl_rate_idx = SR_48K;    break;
    	default: break;
	}

	psp_obj->mono_stereo= ch_num_idx;
	psp_obj->sample_rate = smpl_rate_idx;
	psp_obj->word_len = WL_16;
	psp_obj->direction = APP_LINE_OUT;	 
	sp_init_hal(psp_obj);
	
	sp_init_tx_variables();

	/*configure Sport according to the parameters*/
	AUDIO_SP_StructInit(&SP_InitStruct);
	SP_InitStruct.SP_MonoStereo= psp_obj->mono_stereo;
	SP_InitStruct.SP_WordLen = psp_obj->word_len;

	AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);
	
	AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
	AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);

	tx_addr = (u32)sp_get_ready_tx_page();
	tx_length = sp_get_ready_tx_length();
	AUDIO_SP_TXGDMA_Init(0, &SPGdmaStruct.SpTxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_tx_complete, tx_addr, tx_length);

}

static void audio_play_pcm(char *buf, uint32_t len)
{
	u32 offset = 0;
	u32 tx_len;
	while(len){
		if (sp_get_free_tx_page()){
			tx_len = (len >= SP_DMA_PAGE_SIZE)?SP_DMA_PAGE_SIZE:len;
			sp_write_tx_page(((u8 *)buf+offset), tx_len);
			offset += tx_len;
			len -= tx_len;
		}
		else{
			vTaskDelay(1);
		}
	}
}
void adts_cb(int offset, int len, FIL m_file)
{
	int packet_size = 0;
	UINT valid;
	uint8_t *ptr = input_buf;
	int i = 0;
	u32 read_length = 0;
	char head[7];
	int ret;

	get_adts_head(head, len);
	memcpy(input_buf, head, 7);
	f_lseek(&m_file, offset);
	f_read(&m_file, m4a_buf, len,(UINT*)&read_length);
	memcpy(input_buf+7, m4a_buf, len);
	
	packet_size = len+7;
	valid = packet_size;	
	err = aacDecoder_Fill(handle, &ptr, &packet_size, &valid);
	if (err != AAC_DEC_OK) {
		printf("Fill failed: %x\n", err);
		exit(1);
	}
	err = aacDecoder_DecodeFrame(handle, decode_buf, 4096, 0);
	if (err == AAC_DEC_NOT_ENOUGH_BITS)
		printf("Not enough bits\n");
	if (err != AAC_DEC_OK) {
		printf("Decode failed: %x\n", err);
	}
	if (!m4ainfo) {
		m4ainfo = aacDecoder_GetStreamInfo(handle);
		if (!m4ainfo || m4ainfo->sampleRate <= 0) {
			printf("No stream info\n");
			exit(1);
		}
		frame_size = m4ainfo->frameSize * m4ainfo->numChannels;
		printf("sampleRate: %d, frameSize: %d, numChannels: %d\n", m4ainfo->sampleRate, m4ainfo->frameSize, m4ainfo->numChannels);
		pcm_size = m4ainfo->frameSize * m4ainfo->numChannels * ((BITS_PER_CHANNEL == WL_16)?2:3);
	}
	if(first_frame){
		initialize_audio(m4ainfo->numChannels, m4ainfo->sampleRate);
		first_frame = 0;
	}
	audio_play_pcm(decode_buf, pcm_size);
	
    //ret = fwrite(decode_buf, 1, frame_size*2, fp);
}

void play_raw_adts(FIL m_file)
{
	u32 start_heap = 0;
	start_heap = xPortGetFreeHeapSize();
	handle = aacDecoder_Open(TT_MP4_ADTS, 1);
	iterate_samples_from_stsc(adts_cb, m_file);
	printf("decoding finished (Heap used: 0x%x)\n", start_heap - xPortGetFreeHeapSize());
	aacDecoder_Close(handle);
}

void audio_play_sd_m4a_selfparse(u8* filename)
{
	int drv_num = 0;
	FRESULT res; 
	FATFS 	m_fs;
	FIL		m_file;  
	char	logical_drv[4]; //root diretor
	char abs_path[32]; //Path to input file
	DWORD bytes_left;
	DWORD file_size;
	u32 start_time = 0;

	//PSRAMInit();
	m4a_buf = Psram_reserve_malloc(BUF_LEN);
	sample_size_tab = Psram_reserve_malloc(MAX_SAMPLE_NUM);
	chunk_offset_tab = Psram_reserve_malloc(MAX_CHUNK_NUM);	
	drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
	if(drv_num < 0){
		printf("Rigester disk driver to FATFS fail.\n");
		return;
	}else{
		logical_drv[0] = drv_num + '0';
		logical_drv[1] = ':';
		logical_drv[2] = '/';
		logical_drv[3] = 0;
	}

	if(f_mount(&m_fs, logical_drv, 1)!= FR_OK){
		printf("FATFS mount logical drive fail, please format DISK to FAT16/32.\n");
		goto unreg;
	}
	memset(abs_path, 0x00, sizeof(abs_path));
	strcpy(abs_path, logical_drv);
	sprintf(&abs_path[strlen(abs_path)],"%s", filename);

	//Open source file
	res = f_open(&m_file, abs_path, FA_OPEN_EXISTING | FA_READ); // open read only file
	if(res != FR_OK){
		printf("Open source file %s fail.\n", filename);
		goto umount;
	}
	
	file_size = (&m_file)->fsize;
	bytes_left = file_size;
	printf("File size is %d\n",file_size);
        
	check_m4a_file(&m_file);
	parse_esds(&m_file);
	parse_stsc(&m_file);
	parse_stsz(&m_file);
	parse_stco(&m_file);
	start_time = rtw_get_current_time();
	play_raw_adts(m_file);
	printf("decoding finished (Time passed: %dms)\n", rtw_get_current_time() - start_time);
	exit:	
	// close source file
	res = f_close(&m_file);
	if(res){
		printf("close file (%s) fail.\n", filename);
	}
	
umount:
	if(f_mount(NULL, logical_drv, 1) != FR_OK){
		printf("FATFS unmount logical drive fail.\n");
	}
	Psram_reserve_free(m4a_buf);
	Psram_reserve_free(sample_size_tab);
	Psram_reserve_free(chunk_offset_tab);
unreg:	
	if(FATFS_UnRegisterDiskDriver(drv_num))	
	printf("Unregister disk driver from FATFS fail.\n");
}

void example_audio_m4a_selfparse_thread(void)
{

	printf("Audio codec m4a selfparse demo begin......\n");
	audio_play_sd_m4a_selfparse(FILE_NAME);
exit:
	vTaskDelete(NULL);
}

void example_audio_m4a_selfparse(void)
{
	if(xTaskCreate(example_audio_m4a_selfparse_thread, ((const char*)"example_audio_m4a_selfparse_thread"), 4000, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_audio_m4a_selfparse_thread) failed", __FUNCTION__);
}
#endif
