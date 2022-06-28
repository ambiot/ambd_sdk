Example Description

This example describes how to use IR receive and learn the received waveform frequency or data format.

/*IRs pin location:
 * |  IR_TX  |  _PA_25  | _PB_23 | _PB_29 |
 * |  IR_RX  |  _PA_26  | _PB_22 | _PB_31 |
*/
In this example, IR as receiver, defualt using _PB_22.
CAUTION:
when used with IR receiver, please set rx pin no-pull.

NOTE:
* IR rx learning demo default works at
* @ sample frequency = 10MHz
* @ receive carrier symbol data when IR_RX_FIFO_LEVEL_INT interrupt happens(default ir receive 5 data into FIFO).
* @ IR receiving data stops at IR_RX_CNT_THR_INT interrupt.
* @ IR_RX_CNT_THR_INT, rx stop threshold, is controlled by received IR_RxCntThrType(default Low level) count > IR_RxCntThr(default 0xa1644, that is about 66ms)
* @LOOP_QUEUE_MAX_SIZE is 4096. default maxium queue length to store data before decoding.


IR learn data Flow:
1. enable IR RX mode
2. IR recieve data at IR_RX_FIFO_LEVEL_INT and store data to queue.
3. when IR_RX_CNT_THR_INT happens, IR stop receiving data and start decodeing received data.
4. IR decode packet will count all carrier symbol (data between TIME_LOWEST_VALUE and TIME_HIGHEST_VALUE regard as carrier symbol) together; and record non-carrier symbol value (data larger than TIME_LOW_VOLTAGE_VALUE).
5. IR decode frequncy is caculated from the IR sample frequency and received carrier symbol number.
	NOTE: there may be some accuarcy when rx learning from the received data.
6. display the carrier symbol data to space symbol data.
	NOTE: when the non-carrier symbol is large enough, there may bring caculation overflow. when this happens, force (uint64_t)detect_time or (uint64_t)frequency data type to uint64_t.


Reference:
	UM0400 Ameba-D User Manual.pdf

