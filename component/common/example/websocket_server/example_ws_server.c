#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include <websocket/wsserver_api.h>
#include "wifi_conf.h"
#include "wifi_ind.h"
#include "websocket/ws_server_msg.h"

#define USE_WSS    0

#if USE_WSS
// use test_srv_crt, test_srv_key, test_ca_list in PolarSSL certs.c
#if (WS_SERVER_USE_TLS == WS_SERVER_TLS_POLARSSL)
#include <polarssl/certs.h>
#elif (WS_SERVER_USE_TLS == WS_SERVER_TLS_MBEDTLS)
#include <mbedtls/certs.h>
#endif
#endif

void echo_data(ws_conn *conn, int data_len, enum opcode_type opcode)
{
	printf("\r\n>>>>>> Receiving: %s with length: %d from %d\n", conn->receivedData, data_len, conn->sock);
	if(opcode == TEXT_FRAME)
		ws_server_sendText((char*)conn->receivedData, data_len, 1, conn);
	else if(opcode == BINARY_FRAME)
		ws_server_sendBinary(conn->receivedData, data_len, 1, conn);
}

static void example_wsserver_thread(void *param)
{
  	printf("\r\n\r\n\r\n>>>>>>>>>>>>>>>websocket server example<<<<<<<<<<<<<<<<<\r\n\r\n\r\n");
	vTaskDelay(10000);
	while(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS){ 
		printf("\r\n\r\n\r\n>>>>>>>>>>>>>>Wifi is disconnected!!Please connect!!<<<<<<<<<<<<<<<<<\r\n\r\n\r\n");
		vTaskDelay(10000);
	}
#if USE_WSS
#if (WS_SERVER_USE_TLS == WS_SERVER_TLS_POLARSSL)
	if(ws_server_setup_cert(test_srv_crt, test_srv_key, test_ca_crt) != 0) {
#elif (WS_SERVER_USE_TLS == WS_SERVER_TLS_MBEDTLS)
	if(ws_server_setup_cert(mbedtls_test_srv_crt, mbedtls_test_srv_key, mbedtls_test_ca_crt) != 0) {
#endif
		printf("\nERROR: ws_server_setup_cert\n");
		goto exit;
	}
#endif
	ws_server_dispatch(echo_data);

#if USE_WSS
	if(ws_server_start(443, 5, 4096, WS_SERVER_SECURE_TLS) != 0) {
#else
	if(ws_server_start(80, 5, 4096, WS_SERVER_SECURE_NONE) != 0) {
#endif
		printf("ERROR: ws_server_start");
	}
#if USE_WSS
exit:
#endif
	vTaskDelete(NULL);
}

void example_wsserver(void)
{
	if(xTaskCreate(example_wsserver_thread, ((const char*)"example_wsserver_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_wsserver_thread) failed", __FUNCTION__);
}

