#include "FreeRTOS.h"
#include "task.h"
#include <platform/platform_stdlib.h>
#include "wifi_conf.h"
#include "wifi_ind.h"
#include "websocket/libwsclient.h"
#include "websocket/wsclient_api.h"
#include <stdio.h>
#include "example_wsclient.h"

void handle_message(wsclient_context **wsclient, int data_len)
{
	wsclient_context *wsc = *wsclient;
	printf("\r\n>>>>>> Receiving: %s with length: %d\n", wsc->receivedData, data_len);

	if(strcmp((char const*)wsc->receivedData, "hello") == 0)
		ws_send("world", strlen("world"), 1, wsc);
	else if (strcmp((char const*)wsc->receivedData, "world") == 0){
		ws_close(wsclient);
    }
}

static void example_wsclient_thread(void *param)
{
	/* To avoid gcc warnings */
	( void ) param;
	
  	printf("\r\n\r\n\r\n>>>>>>>>>>>>>>>wsclient example<<<<<<<<<<<<<<<<<\r\n\r\n\r\n");
	vTaskDelay(10000);
	while(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS){ 
		printf("\r\n\r\n\r\n>>>>>>>>>>>>>>Wifi is disconnected!!Please connect!!<<<<<<<<<<<<<<<<<\r\n\r\n\r\n");
		vTaskDelay(10000);
	}

	int ret;
	
        //Please set SSL_MAX_CONTENT_LEN to 7680 for maximum input msglen 7067 Bytes
        wsclient_context *wsclient = create_wsclient("wss://echo.websocket.org", 0, NULL, NULL, 1500,3);
        
        //Please set SSL_MAX_CONTENT_LEN to 5120 for maximum input msglen 4849 Bytes
	//wsclient_context *wsclient = create_wsclient("wss://sandbox.kaazing.net", 0, "echo", NULL, 1500,3);
	if(wsclient != NULL){

		if(wsclient->use_ssl == 1){
#ifndef USING_SSL
			printf("\r\nNot Support the wss server!\r\n");
			vTaskDelete(NULL);       
#endif
          }
		ret = ws_connect_url(wsclient);
		if(ret >= 0){
			ws_send("hello", strlen("hello"), 1, wsclient);
			ws_dispatch(handle_message);
			while (wsclient->readyState != CLOSED){
				
				ws_poll(0, &wsclient);
			}
		}
		else
			printf("\r\nConnect to websocket server failed!\r\n");
                
		if(wsclient){
			ws_free(wsclient);
			wsclient = NULL;
		}
	}
	else
		printf("\r\nCreat websocket context failed!\r\n");
	
	vTaskDelete(NULL);
}

void example_wsclient(void)
{
	if(xTaskCreate(example_wsclient_thread, ((const char*)"example_wsclient_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(init_thread) failed", __FUNCTION__);
}
