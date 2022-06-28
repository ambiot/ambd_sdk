Example Description

This example describes how to use IR decode data by NEC protocol at interrupt mode.

/*IRs pin location:
 * |  IR_TX  |  _PA_25  | _PB_23 | _PB_29 |
 * |  IR_RX  |  _PA_26  | _PB_22 | _PB_31 |
*/
In this example, IR as receiver, defualt using _PB_22.
CAUTION:
when used with IR receiver, please set rx pin no-pull.

NOTE:
* NEC protocol works at
* @ sample frequency = 10MHz
* @ receive carrier symbol data when IR_RX_FIFO_LEVEL_INT interrupt happens.
* @ rx stop at IR_RX_CNT_THR_INT interrupt.
* @ rx stop threshold is controlled by received IR_RxCntThrType(default Low level) count > IR_RxCntThr(default 0xa1644, that is about 66ms)
* @ decoding tolerance is 30% by default.


Additional configurations: 
1. data waveform reverse
	1.1 to reverse lR output idle level:
		IR_InitStruct->IR_TxIdleLevel: 
		- IR_IDLE_OUTPUT_LOW
		- IR_IDLE_OUTPUT_HIGH
	1.2 to revsese IR carrier and non-carrier level:
		IR_InitStruct->IR_TxInverse : 
		- IR_TX_DATA_NORMAL: carrier symbol from high to low; non-carrier symbol default low.
		- IR_TX_DATA_INVERSE: carrier symbol from low to high; non-carrier symbol default high.
		- IR_TX_DATA_CARRIER_NORMAL: default carrier and non-carrier waveform
		- IR_TX_DATA_CARRIER_INVERSE: there is a pulse from carrier to non-carrier.

2. other IR protocol configuration
	refer to component\common\drivers\ir\protocol\ir_nec_protocol.c
	2.1 struct and macros:
	- IR_ProtocolTypeDef: the struct of IR protocol data format, which depends on the IR protocol custom choose.
	- IR_DataTypeDef: the struct used to store IR decoding/endcoding data
	- MAX_IR_BUF_SIZE: the maxium length of carrier symbol data to store in one data command and data format.
	- MAX_HEADDER_LEN: header length if there is header.
	- MAX_LOG_WAVFORM_SIZE: always be 2. to differ from space symbol high or low.
	- MAX_CODE_SIZE: the data length of DATA_CODE_WDTH
	- DATA_CODE_WDTH: NEC protocol is 8bits as default.
	2.2 IR encode and decode functions:
	- NEC_EncodePacket: encode the space symbol of IR waveform data with carrier symbol data.
	- NEC_DecodePacket: decode the received IR waveform with carrier symbol to space symbol.

Reference:
	UM0400 Ameba-D User Manual.pdf

