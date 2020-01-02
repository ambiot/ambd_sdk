Websocket Client Example

Description:
A simple websocket client example which send "hello" and "world" to server.
The server will reply the message it received.
Once the client received "world", it will disconnect with server.

The SSL websocket server:
	wss://echo.websocket.org
	wss://sandbox.kaazing.net/echo
The websocket server without SSL:
	ws://echo.websocket.org
	ws://sandbox.kaazing.net/echo
	

Configuration:

[platform_opts.h]
	#define CONFIG_EXAMPLE_WEBSOCKET_CLIENT 	1


    If using the WSS server:

	[wsclient_api.h]
		#define USING_SSL

	[config_rsa.h]
		if connecting to wss://sandbox.kaazing.net
		#define SSL_MAX_CONTENT_LEN	5120
		or
		if connecting to wss://echo.websocket.org
		#define SSL_MAX_CONTENT_LEN	7680

	[example_wsclient.c]
		wsclient_context *wsclient = create_wsclient("wss://sandbox.kaazing.net", 0, "echo", NULL, 1500);
		or
		wsclient_context *wsclient = create_wsclient("wss://echo.websocket.org", 0, NULL, NULL, 1500);


    If using the WS server:

	[example_wsclient.c]
		wsclient_context *wsclient = create_wsclient("ws://sandbox.kaazing.net", 0, "echo", NULL, 1500);
		or
		wsclient_context *wsclient = create_wsclient("ws://echo.websocket.org", 0, NULL, NULL, 1500);


Execution:
Can make automatical Wi-Fi connection when booting by using wlan fast connect example.
A websocket client example thread will be started automatically when booting.
If using other websocekt server, modify the create_wsclient() API and the handle_message() function depending on the condition of the server.


Note : 
AmebaPro and AmebaZ2 don't support polarssl, only support mbedtls.

[Supported List]
	Supported :
	    Ameba-1, Ameba-z, Ameba-pro, Ameba-z2