#include "example_audio_signal_generate.h"
#include <platform/platform_stdlib.h>
#include "rl6548.h"
#include "ameba_soc.h"
#include "arm_math.h"

#if (AUDIO_SIGNAL_GENERATE)
#define DMIC_LOC_PB1			1	//EVB v2 should set this macro to 0

#define SAMPLE_RATE				SR_48K
#define ABS_FREQ				48000


#define SP_DMA_PAGE_SIZE        512   // 2 ~ 4096
#define SP_DMA_PAGE_NUM         4
#define SP_ZERO_BUF_SIZE        128
#define SP_FULL_BUF_SIZE        128
#define RFFT_SIZE               (SP_DMA_PAGE_SIZE >> 1)

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


typedef struct {
    GDMA_InitTypeDef           SpTxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
    GDMA_InitTypeDef           SpRxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef    
}SP_GDMA_STRUCT, *pSP_GDMA_STRUCT;

typedef struct {
    u8 tx_gdma_own;
    u32 tx_addr;
    u32 tx_length;
}TX_BLOCK, *pTX_BLOCK;

typedef struct {
    TX_BLOCK tx_block[SP_DMA_PAGE_NUM];
    TX_BLOCK tx_zero_block;
    u8 tx_gdma_cnt;
    u8 tx_usr_cnt;
    u8 tx_empty_flag;
}SP_TX_INFO, *pSP_TX_INFO;

typedef struct {
    u8 rx_gdma_own;
    u32 rx_addr;
    u32 rx_length;
}RX_BLOCK, *pRX_BLOCK;

typedef struct {
    RX_BLOCK rx_block[SP_DMA_PAGE_NUM];
    RX_BLOCK rx_full_block;
    u8 rx_gdma_cnt;
    u8 rx_usr_cnt;
    u8 rx_full_flag;
}SP_RX_INFO, *pSP_RX_INFO;

typedef struct {
    u32 sample_rate;
    u32 word_len;
    u32 mono_stereo;
    u32 direction;
}SP_OBJ, *pSP_OBJ;

static SP_InitTypeDef SP_InitStruct;
static SP_GDMA_STRUCT SPGdmaStruct;
static SP_OBJ sp_obj;
static SP_TX_INFO sp_tx_info;
static SP_RX_INFO sp_rx_info;

static arm_rfft_fast_instance_f32 rfft;

static GPIO_InitTypeDef GPIO_InitStruct;

static int audio_fre;


static short sine_wave[48000] = {0};


static u8 sp_tx_buf[SP_DMA_PAGE_SIZE*SP_DMA_PAGE_NUM]__attribute__((aligned(32)));
static u8 sp_zero_buf[SP_ZERO_BUF_SIZE]__attribute__((aligned(32)));

SRAM_NOCACHE_DATA_SECTION static u8 sp_rx_buf[SP_DMA_PAGE_SIZE*SP_DMA_PAGE_NUM];
static u8 sp_full_buf[SP_FULL_BUF_SIZE];

static TaskHandle_t xAudioTaskHandle;
static u8 audio_source;
static u8 audio_sink;
enum {
    AUDIO_SOURCE_TONE = 0,
    AUDIO_SOURCE_DMIC,
    AUDIO_SOURCE_DAAD,
    AUDIO_SINK_SPKR,
    AUDIO_SINK_HP,
    AUDIO_SINK_FFT
};

static u8 *sp_get_free_tx_page(void) {
    pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
    
    if (ptx_block->tx_gdma_own)
        return NULL;
    else{
        return (u8*)ptx_block->tx_addr;
    }
}

static void sp_write_tx_page(u8 *src, u32 length) {
    pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_usr_cnt]);
    
    memcpy((void*)ptx_block->tx_addr, src, length);
    ptx_block->tx_gdma_own = 1;
    ptx_block->tx_length = length;
    sp_tx_info.tx_usr_cnt++;
    if (sp_tx_info.tx_usr_cnt == SP_DMA_PAGE_NUM) {
        sp_tx_info.tx_usr_cnt = 0;
    }
}

static void sp_release_tx_page(void) {
    pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);
    
    if (sp_tx_info.tx_empty_flag) {
    }
    else {
        ptx_block->tx_gdma_own = 0;
        sp_tx_info.tx_gdma_cnt++;
        if (sp_tx_info.tx_gdma_cnt == SP_DMA_PAGE_NUM){
            sp_tx_info.tx_gdma_cnt = 0;
        }
    }
}

static u8 *sp_get_ready_tx_page(void) {
    pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);
    
    if (ptx_block->tx_gdma_own) {
        sp_tx_info.tx_empty_flag = 0;
        return (u8*)ptx_block->tx_addr;
    } else {
        sp_tx_info.tx_empty_flag = 1;
        return (u8*)sp_tx_info.tx_zero_block.tx_addr;    //for audio buffer empty case
    }
}

static u32 sp_get_ready_tx_length(void) {
    pTX_BLOCK ptx_block = &(sp_tx_info.tx_block[sp_tx_info.tx_gdma_cnt]);

    if (sp_tx_info.tx_empty_flag) {
        return sp_tx_info.tx_zero_block.tx_length;
    } else {
		//printf("tx_size %d\n", ptx_block->tx_length);
        return ptx_block->tx_length;
    }
}

static u8 *sp_get_ready_rx_page(void)
{
    pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_usr_cnt]);
    
    if (prx_block->rx_gdma_own)
        return NULL;
    else
        return (u8*)prx_block->rx_addr;
}

static void sp_read_rx_page(u8 *dst, u32 length) {
    pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_usr_cnt]);
    
    memcpy(dst, (void const*)prx_block->rx_addr, length);
    prx_block->rx_gdma_own = 1;
    sp_rx_info.rx_usr_cnt++;
    if (sp_rx_info.rx_usr_cnt == SP_DMA_PAGE_NUM) {
        sp_rx_info.rx_usr_cnt = 0;
    }
}

static void sp_release_rx_page(void) {
    pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_gdma_cnt]);
    
    if (sp_rx_info.rx_full_flag) {
    } else {
        prx_block->rx_gdma_own = 0;
        sp_rx_info.rx_gdma_cnt++;
        if (sp_rx_info.rx_gdma_cnt == SP_DMA_PAGE_NUM) {
            sp_rx_info.rx_gdma_cnt = 0;
        }
    }
}

static u8 *sp_get_free_rx_page(void) {
    pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_gdma_cnt]);
    
    if (prx_block->rx_gdma_own) {
        sp_rx_info.rx_full_flag = 0;
        return (u8*)prx_block->rx_addr;
    } else {
        sp_rx_info.rx_full_flag = 1;
        return (u8*)sp_rx_info.rx_full_block.rx_addr;    //for audio buffer full case
    }
}

static u32 sp_get_free_rx_length(void) {
    pRX_BLOCK prx_block = &(sp_rx_info.rx_block[sp_rx_info.rx_gdma_cnt]);

    if (sp_rx_info.rx_full_flag) {
        return sp_rx_info.rx_full_block.rx_length;
    } else {
        return prx_block->rx_length;
    }
}

static void sp_tx_complete(void *Data) {
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
    //GDMA_SetSrcAddr(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_addr);
    //GDMA_SetBlkSize(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_length>>2);
    
    //GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, ENABLE);
	AUDIO_SP_TXGDMA_Restart(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, tx_addr, tx_length);    
}

static void sp_rx_complete(void *Data) {
    SP_GDMA_STRUCT *gs = (SP_GDMA_STRUCT *) Data;
    PGDMA_InitTypeDef GDMA_InitStruct;
    u32 rx_addr;
    u32 rx_length;
    
    GDMA_InitStruct = &(gs->SpRxGdmaInitStruct);
    DCache_Invalidate(GDMA_InitStruct->GDMA_DstAddr, GDMA_InitStruct->GDMA_BlockSize<<2);

    /* Clear Pending ISR */
    GDMA_ClearINT(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum);
    sp_release_rx_page();
    rx_addr = (u32)sp_get_free_rx_page();
    rx_length = sp_get_free_rx_length();
    //GDMA_SetDstAddr(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, rx_addr);
    //GDMA_SetBlkSize(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, rx_length>>2);    
    
    //GDMA_Cmd(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, ENABLE);
	AUDIO_SP_RXGDMA_Restart(GDMA_InitStruct->GDMA_Index, GDMA_InitStruct->GDMA_ChNum, rx_addr, rx_length);
}

static void sp_init_hal(pSP_OBJ psp_obj) {
    u32 div;
    
    PLL_I2S_Set(ENABLE);        //enable 98.304MHz PLL. needed if fs=8k/16k/32k/48k/96k
    PLL_PCM_Set(ENABLE);        //enable 45.1584MHz PLL. needed if fs=44.1k/88.2k
    PLL_Sel(PLL_I2S);

    RCC_PeriphClockCmd(APBPeriph_AUDIOC, APBPeriph_AUDIOC_CLOCK, ENABLE);
    RCC_PeriphClockCmd(APBPeriph_SPORT, APBPeriph_SPORT_CLOCK, ENABLE);    

    //set clock divider to gen clock sample_rate*256 from 98.304M.
    switch(psp_obj->sample_rate) {
        case SR_48K:
			printf("is 48K or not");
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
            PLL_Sel(PLL_PCM);
            break;
        case SR_88P2K:
            div = 2;
            PLL_Sel(PLL_PCM);
            break;
        default:
            DiagPrintf("sample rate not supported!!\n");
            break;
    }
    PLL_Div(div);

	#if DMIC_LOC_PB1
    PAD_CMD(_PB_1, DISABLE);
    PAD_CMD(_PB_2, DISABLE);
    Pinmux_Config(_PB_1, PINMUX_FUNCTION_DMIC);
    Pinmux_Config(_PB_2, PINMUX_FUNCTION_DMIC);    
	#else
    PAD_CMD(_PB_24, DISABLE);
    PAD_CMD(_PB_25, DISABLE);
    Pinmux_Config(_PB_24, PINMUX_FUNCTION_DMIC);
    Pinmux_Config(_PB_25, PINMUX_FUNCTION_DMIC);   	
	#endif

    PAD_CMD(_PB_28, DISABLE);
    PAD_CMD(_PB_29, DISABLE);
    PAD_CMD(_PB_30, DISABLE);
    PAD_CMD(_PB_31, DISABLE);

    /*codec init*/
    CODEC_Init(psp_obj->sample_rate, psp_obj->word_len, psp_obj->mono_stereo, psp_obj->direction);
    CODEC_SetVolume(0x90, 0x90);

    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;

    GPIO_InitStruct.GPIO_Pin = _PA_28;
    GPIO_Init(&GPIO_InitStruct);
    if(audio_sink == AUDIO_SINK_HP) {
        /* Route audio to headphone */
        DiagPrintf("\nRoute audio to headphone!!");
        GPIO_WriteBit(_PA_28, GPIO_PIN_LOW);
    } else if (audio_sink == AUDIO_SINK_SPKR) {
        /* Route audio to speaker */
        DiagPrintf("\nRoute audio to speaker!!");
        GPIO_WriteBit(_PA_28, GPIO_PIN_HIGH);
    }

    if(audio_source == AUDIO_SOURCE_DMIC) {
        /* Power on DMIC */
        GPIO_InitStruct.GPIO_Pin = _PB_6;
        GPIO_Init(&GPIO_InitStruct);
        GPIO_WriteBit(_PB_6, GPIO_PIN_HIGH);
    }
}

static void sp_deinit_hal(void) {
    /* Power off DMIC */
    GPIO_WriteBit(_PB_6, GPIO_PIN_LOW);

    /* Power off audio amplifier */
    GPIO_WriteBit(_PA_28, GPIO_PIN_LOW);
    
    CODEC_DeInit(APP_DMIC_IN|APP_LINE_OUT);
    
    RCC_PeriphClockCmd(APBPeriph_AUDIOC, APBPeriph_AUDIOC_CLOCK, DISABLE);
    RCC_PeriphClockCmd(APBPeriph_SPORT, APBPeriph_SPORT_CLOCK, DISABLE);   
    
    PLL_I2S_Set(DISABLE);
    PLL_PCM_Set(DISABLE);
}

static void sp_init_tx_variables(void) {
    int i;

    for(i=0; i<SP_ZERO_BUF_SIZE; i++) {
        sp_zero_buf[i] = 0;
    }
    sp_tx_info.tx_zero_block.tx_addr = (u32)sp_zero_buf;
    sp_tx_info.tx_zero_block.tx_length = (u32)SP_ZERO_BUF_SIZE;
    
    sp_tx_info.tx_gdma_cnt = 0;
    sp_tx_info.tx_usr_cnt = 0;
    sp_tx_info.tx_empty_flag = 0;
    
    for(i=0; i<SP_DMA_PAGE_NUM; i++) {
        sp_tx_info.tx_block[i].tx_gdma_own = 0;
        sp_tx_info.tx_block[i].tx_addr = (u32)(sp_tx_buf+i*SP_DMA_PAGE_SIZE);
        sp_tx_info.tx_block[i].tx_length = SP_DMA_PAGE_SIZE;
    }
}

static void sp_init_rx_variables(void) {
    int i;

    sp_rx_info.rx_full_block.rx_addr = (u32)sp_full_buf;
    sp_rx_info.rx_full_block.rx_length = (u32)SP_FULL_BUF_SIZE;
    
    sp_rx_info.rx_gdma_cnt = 0;
    sp_rx_info.rx_usr_cnt = 0;
    sp_rx_info.rx_full_flag = 0;
    
    for(i=0; i<SP_DMA_PAGE_NUM; i++) {
        sp_rx_info.rx_block[i].rx_gdma_own = 1;
        sp_rx_info.rx_block[i].rx_addr = (u32)(sp_rx_buf+i*SP_DMA_PAGE_SIZE);
        sp_rx_info.rx_block[i].rx_length = SP_DMA_PAGE_SIZE;
    }
}


void audio_test_sin_generator(void* param){
    u32 buf[SP_DMA_PAGE_SIZE>>2];
    u32 tx_addr;
    u32 tx_length;
    u32 rx_addr;
    u32 rx_length;
    pSP_OBJ psp_obj = (pSP_OBJ)param;
    u32 rx_cnt = 0, tx_cnt = 0;
    float frame[RFFT_SIZE];
    float buffer[RFFT_SIZE];
    float max_val = 0;
    u32 max_freq = 0;
    
    sp_init_hal(psp_obj);
    
    /* Configure Sport according to the parameters */
    AUDIO_SP_StructInit(&SP_InitStruct);
    SP_InitStruct.SP_MonoStereo= psp_obj->mono_stereo;
    SP_InitStruct.SP_WordLen = psp_obj->word_len;
	
    if(audio_source == AUDIO_SOURCE_TONE) {
	
    double delta = 0.0000208333333;
    double current_t = 0;
	
    for(int i = 0; i < 48000; i++){
        sine_wave[i] = (int)(sin(2 * M_PI  * audio_fre * current_t) *(pow(2,15)-1));
        current_t += delta;
    }
	
    DiagPrintf("...Playing sine wave\n");

    sp_init_tx_variables();
    AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);
    AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
    AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);

    tx_addr = (u32)sp_get_ready_tx_page();
    tx_length = sp_get_ready_tx_length();
    AUDIO_SP_TXGDMA_Init(0, &SPGdmaStruct.SpTxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_tx_complete, (u8*)tx_addr, tx_length);
		
    tx_cnt = 0;
    while(1) {
        u32 page_num = sizeof(sine_wave)/SP_DMA_PAGE_SIZE;
        if (sp_get_free_tx_page()) {
            if(tx_cnt < page_num){
                sp_write_tx_page((u8 *)sine_wave + tx_cnt*SP_DMA_PAGE_SIZE, SP_DMA_PAGE_SIZE);
                tx_cnt++;
			}
            else{
                sp_write_tx_page((u8 *)sine_wave + tx_cnt*SP_DMA_PAGE_SIZE, SP_DMA_PAGE_SIZE/2);
                tx_cnt = 0;
			}
        } else {
            vTaskDelay(1);
			} 
        }
    } else if (audio_source == AUDIO_SOURCE_DAAD) {		
        double delta = 0.0000208333333;
        double current_t = 0;
	
        for(int i = 0; i < 48000; i++){
            sine_wave[i] = (int)(sin(2 * M_PI  * audio_fre * current_t) *(pow(2,15)-1));
            current_t += delta;
        }
	
        arm_rfft_fast_init_f32(&rfft, RFFT_SIZE);

        sp_init_tx_variables();   
        sp_init_rx_variables();
        AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);

        AUDIO_SP_RdmaCmd(AUDIO_SPORT_DEV, ENABLE);
        AUDIO_SP_RxStart(AUDIO_SPORT_DEV, ENABLE);   
        AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, ENABLE);
        AUDIO_SP_TxStart(AUDIO_SPORT_DEV, ENABLE);
		
        tx_addr = (u32)sp_get_ready_tx_page();
        tx_length = sp_get_ready_tx_length();
        AUDIO_SP_TXGDMA_Init(0, &SPGdmaStruct.SpTxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_tx_complete, (u8*)tx_addr, tx_length);

        rx_addr = (u32)sp_get_free_rx_page();
        rx_length = sp_get_free_rx_length();
        AUDIO_SP_RXGDMA_Init(0, &SPGdmaStruct.SpRxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_rx_complete, (u8*)rx_addr, rx_length);   
		
        tx_cnt = 0;
        rx_cnt = 0;
        while(1) {
            if (sp_get_free_tx_page()) {
                sp_write_tx_page((u8 *)sine_wave+SP_DMA_PAGE_SIZE*tx_cnt, SP_DMA_PAGE_SIZE);
                tx_cnt++;
                if (tx_cnt >= sizeof(sine_wave)/SP_DMA_PAGE_SIZE) {
                    tx_cnt = 0;
                }
            }
			
            if (sp_get_ready_rx_page()) {
                sp_read_rx_page((u8 *)buf, SP_DMA_PAGE_SIZE);
                rx_cnt++;
                if (rx_cnt == ABS_FREQ/(4*RFFT_SIZE)) {
                    rx_cnt = 0;    
		
					//Compute FFT
                    for(int i=0; i<RFFT_SIZE; i++) {
                        frame[i] = ((float)(((s16 *)buf)[i]))/(1<<15);
                    }
                    arm_rfft_fast_f32(&rfft, frame, buffer, 0);
                    int32_t half_dim = RFFT_SIZE/2;
                    float first_energy = buffer[0] * buffer[0],
                    last_energy =  buffer[1] * buffer[1];  // handle this special case
                    for (int i=1; i<half_dim; i++) {
                        float real = buffer[i*2], im = buffer[i*2 + 1];
                        buffer[i] = real*real + im*im;
                    }
                    buffer[0] = first_energy;
                    buffer[half_dim] = last_energy;
		
                    for(int i=0; i<=half_dim; i++) {
                        if (max_val < buffer[i]) {
                            max_val = buffer[i];
                            max_freq = i;
                        }
                    }
					
                    DiagPrintf("%dHz,%d\n", max_freq*ABS_FREQ/RFFT_SIZE, (int)(20*(log10(sqrt(max_val)/(RFFT_SIZE/2)))));
                    max_val = 0;
                    max_freq = 0;
                }
            } 			
            else {
                vTaskDelay(1);
            }		 
        }
    } else if (audio_source == AUDIO_SOURCE_DMIC) {
        DiagPrintf("....analyzing audio picked up by DMIC\n");

        arm_rfft_fast_init_f32(&rfft, RFFT_SIZE);
        
        sp_init_rx_variables();
        AUDIO_SP_Init(AUDIO_SPORT_DEV, &SP_InitStruct);
        AUDIO_SP_RdmaCmd(AUDIO_SPORT_DEV, ENABLE);
        AUDIO_SP_RxStart(AUDIO_SPORT_DEV, ENABLE);   

        rx_addr = (u32)sp_get_free_rx_page();
        rx_length = sp_get_free_rx_length();
        AUDIO_SP_RXGDMA_Init(0, &SPGdmaStruct.SpRxGdmaInitStruct, &SPGdmaStruct, (IRQ_FUN)sp_rx_complete, (u8*)rx_addr, rx_length);   
        while(1) {
            if (sp_get_ready_rx_page()) {
                sp_read_rx_page((u8 *)buf, SP_DMA_PAGE_SIZE);
            
                rx_cnt++;
                if (rx_cnt == ABS_FREQ/(4*RFFT_SIZE)) {
                    rx_cnt = 0;          
                    //Compute FFT
                    for(int i=0; i<RFFT_SIZE; i++) {
                        frame[i] = ((float)(((s16 *)buf)[i]))/(1<<15);
                    }
                    arm_rfft_fast_f32(&rfft, frame, buffer, 0);
            
                    int32_t half_dim = RFFT_SIZE/2;
                    float first_energy = buffer[0] * buffer[0],
                    last_energy =  buffer[1] * buffer[1];  // handle this special case
                    for (int i=1; i<half_dim; i++) {
                        float real = buffer[i*2], im = buffer[i*2 + 1];
                        buffer[i] = real*real + im*im;
                    }
                    buffer[0] = first_energy;
                    buffer[half_dim] = last_energy;
            
                    for(int i=0; i<=half_dim; i++) {
                        if (max_val < buffer[i]) {
                            max_val = buffer[i];
                            max_freq = i;
                        }
                    }
                        
                    DiagPrintf("%d Hz, %d\n", max_freq*ABS_FREQ/RFFT_SIZE, (int)(20*(log10(sqrt(max_val)/(RFFT_SIZE/2)))));
                        
                    max_val = 0;
                    max_freq = 0;
                }
            } else {
                vTaskDelay(1);
            }        
        }
	}
	exit:
    vTaskDelete(NULL);
	
}


void audio_test_start(int argc, char *argv[]) {
    if(xAudioTaskHandle) {
        DiagPrintf("\nAn audio test is already running, stop it first by 'audio stop' command\n");
    }			
    else if(argc == 3){
        audio_source = (_strcmp(argv[0], "tone") == 0) ? AUDIO_SOURCE_TONE : ((_strcmp(argv[0], "dmic") == 0) ? AUDIO_SOURCE_DMIC : AUDIO_SOURCE_DAAD);        audio_sink = (_strcmp(argv[1], "spkr") == 0) ? AUDIO_SINK_SPKR : ((_strcmp(argv[1], "hp") == 0) ? AUDIO_SINK_HP : AUDIO_SINK_FFT);
        audio_sink = (_strcmp(argv[1], "spkr") == 0) ? AUDIO_SINK_SPKR : AUDIO_SINK_FFT;
        audio_fre = _strtoul((const u8*)(argv[2]), (u8 **)NULL, 10);
        printf("audio fre %d\n", audio_fre);
        sp_obj.sample_rate = SR_48K;
        sp_obj.mono_stereo = CH_MONO;
        sp_obj.word_len = WL_16;
		
        if (audio_source == AUDIO_SOURCE_DAAD) {
	        sp_obj.direction = APP_DAAD_LPBK;				
        }else if (audio_source == AUDIO_SOURCE_TONE) {
            sp_obj.direction = APP_LINE_OUT;
        }else if(audio_source == AUDIO_SOURCE_DMIC){
            sp_obj.direction = APP_DMIC_IN;
        }
        if(xTaskCreate(audio_test_sin_generator, ((const char*)"audio_test_sin_generator"), 2048, (void *)(&sp_obj), tskIDLE_PRIORITY + 1, &xAudioTaskHandle) != pdPASS) {
            DiagPrintf("\n\r%s xTaskCreate(audio_test_sin_generator) failed", __FUNCTION__);
        }
    } else {
        DiagPrintf("\nWrong params, Usage:  [tone|dmic|daad] [spkr|hp]\n");
    }
}


void audio_test_stop(void) {
    if(xAudioTaskHandle) {
        vTaskDelete(xAudioTaskHandle);
        xAudioTaskHandle = NULL;
        if ((audio_sink != AUDIO_SINK_FFT) || (audio_source == AUDIO_SOURCE_DAAD)) {
            /* Disable Tx path */
            AUDIO_SP_TxStart(AUDIO_SPORT_DEV, DISABLE);
            AUDIO_SP_TdmaCmd(AUDIO_SPORT_DEV, DISABLE);
            /* Disable Tx GDMA channel */
            GDMA_ClearINT(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum);
            GDMA_Cmd(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum, DISABLE);
            GDMA_ChnlFree(SPGdmaStruct.SpTxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpTxGdmaInitStruct.GDMA_ChNum);
        }

        if (audio_source != AUDIO_SOURCE_TONE) {
            /* Disable Rx path */
            AUDIO_SP_RxStart(AUDIO_SPORT_DEV, DISABLE);
            AUDIO_SP_RdmaCmd(AUDIO_SPORT_DEV, DISABLE);
            /* Disable Rx GDMA channel */
            GDMA_ClearINT(SPGdmaStruct.SpRxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpRxGdmaInitStruct.GDMA_ChNum);
            GDMA_Cmd(SPGdmaStruct.SpRxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpRxGdmaInitStruct.GDMA_ChNum, DISABLE);
            GDMA_ChnlFree(SPGdmaStruct.SpRxGdmaInitStruct.GDMA_Index, SPGdmaStruct.SpRxGdmaInitStruct.GDMA_ChNum);
        }

        sp_deinit_hal();
    }
}

u32 cmdAudio(u16 argc, u8 *argv[]) {
    if(argc == 3) {
        audio_test_start(argc, argv);
    } else if(argc == 1) {
        if (_strcmp(argv[0], "stop") == 0) {
            audio_test_stop();
        } else {
            DiagPrintf("\nUsage: audio stop\n");
            return 0;
        }
    } else {
        DiagPrintf("\nUsage: audio [tone|dmic] [spkr|hp|fft]\n");
        return 0;
    }
    return 1;
}

CMD_TABLE_DATA_SECTION
const COMMAND_TABLE roku_audio_test_cmd_table[] = {
	{(const u8*)"Audio_generate",  3, cmdAudio,(const u8*)"\audio_test_start \n"},
};
#endif
