Microsoft Azure IoT Examples based on Azure Embedded C SDK and MQTT stack


Introduction
-----------------------------------------------------------------------------------------------------------------------------------
The Azure examples here are designed to communicate with Azure IoT Hub and Azure IoT Provisioning Service and perform all required action
to interact with Azure IoT Service. These examples are based on Azure Embedded C SDK and utilize our own MQTT stack. We introduce all sorts 
of examples including Telemetry, Cloud-to-Device, Direct Methods, Device Twins, Device Provisioning and Plug and Play, and show X509 and 
SAS authentication supported by Azure IoT Service.


Prerequisites
-----------------------------------------------------------------------------------------------------------------------------------
1. Azure Account need to be created.
2. Azure IoT Hub need to be setup on your Azure Account and a x509/SAS iot device needs to be setup on your IoT Hub.
3. Azure IoT Hub Device Provisioning Service (DPS) need to be setup on your Azure Account if running iot provisioning examples.
4. Azure IoT Explorer need to be installed in order to interact with examples. 
	[https://github.com/Azure/azure-iot-explorer/releases]
5. A pair of X509 certificate and private key need to be prepared for examples using X509 authentication. You can refer to 
	"Create a Device Using X.509 Self-Signed Certificate Authentication" section on azure-sdk-for-c on github:
	[https://github.com/Azure/azure-sdk-for-c/blob/master/sdk/samples/iot/README.md]
6. Azure IoT Central is an integrated platform to simplify the IoT Service management and operation. You can also test AmebaD IoT Hub Plug and Play Examples with Azure IoT Central to easily get start with AmebaD Plug and Play service.


Getting Start
-----------------------------------------------------------------------------------------------------------------------------------
[GCC]
	To enable Azure IoT example in this sdk
		1. Use "make menuconfig" command to open menuconfig terminal and select "MQTT Config" -> "Enable MQTT" to enable MQTT Stack.
		2. Manually uncomment "@make -C azure_emb all" in [project_hp\asdk\make\application\Makefile] to include azure-sdk-for-c library for building.
		3. Manually uncomment below source file in [project_hp\asdk\make\utilities_example\Makefile] to include azure iot example for building.
			CSRC += $(DIR)/azure/example_azure_iot_common.c
			CSRC += $(DIR)/azure/example_azure_iot_entry.c
			CSRC += $(DIR)/azure/example_azure_iot_hub_c2d.c
			CSRC += $(DIR)/azure/example_azure_iot_hub_methods.c
			CSRC += $(DIR)/azure/example_azure_iot_hub_pnp.c
			CSRC += $(DIR)/azure/example_azure_iot_hub_pnp_component.c
			CSRC += $(DIR)/azure/example_azure_iot_hub_sas_telemetry.c
			CSRC += $(DIR)/azure/example_azure_iot_hub_telemetry.c
			CSRC += $(DIR)/azure/example_azure_iot_hub_twin.c
			CSRC += $(DIR)/azure/example_azure_iot_rtk_pnp_sas.c
			CSRC += $(DIR)/azure/example_azure_iot_rtk_pnp_x509.c
			CSRC += $(DIR)/azure/example_azure_iot_provisioning.c
			CSRC += $(DIR)/azure/example_azure_iot_provisioning_sas.c
			CSRC += $(DIR)/azure/pnp/pnp_mqtt_message.c
			CSRC += $(DIR)/azure/pnp/pnp_protocol.c
			CSRC += $(DIR)/azure/pnp/sample_component/pnp_device_info_component.c
			CSRC += $(DIR)/azure/pnp/sample_component/pnp_thermostat_component.c
			CSRC += $(DIR)/azure/pnp/rtk_message/pnp_common_message.c
			CSRC += $(DIR)/azure/pnp/rtk_component/pnp_audio.c
			CSRC += $(DIR)/azure/pnp/rtk_component/pnp_bluetooth.c
			CSRC += $(DIR)/azure/pnp/rtk_component/pnp_device_info.c
			CSRC += $(DIR)/azure/pnp/rtk_component/pnp_gpio.c
			CSRC += $(DIR)/azure/pnp/rtk_component/pnp_lcd.c
			CSRC += $(DIR)/azure/pnp/rtk_component/pnp_memory.c
			CSRC += $(DIR)/azure/pnp/rtk_component/pnp_system.c
			CSRC += $(DIR)/azure/pnp/rtk_component/pnp_video.c
			CSRC += $(DIR)/azure/pnp/rtk_component/pnp_wireless.c
		4. Enable CONFIG_EXAMPLE_AZURE in [inc_hp\platform_opts.h] to start the example.
		5. Select example in [example_azure_iot_entry.h] and configure your own setting in the example. Please refer to the "Azure Example Description" and "Realtek Pnp Example Description"section.
		6. If you are using X509 certificate encrypted with EC cryptography, please enable below define in [config_rsa.h]. (Default use MbedTLS-2.4.0)
			MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
			MBEDTLS_ASN1_WRITE_C
			MBEDTLS_ECDH_C
			MBEDTLS_ECDSA_C
			MBEDTLS_ECP_C

	Next, Build and flash your image to the EVB.
	When example start running
		1. Use AT command to connect to WiFi manually. Input the below command step by step on terminal. After WiFi connected the example will proceed.
			ATW0=[your AP ssid]
			ATW1=[your AP passphrase. Exclude this command if AP is OPEN mode]
			ATWC
		2. Check the example and interact with it.
		
Azure IoT Service Configuration
-----------------------------------------------------------------------------------------------------------------------------------
Here we introduce some required steps to prepare for your IoT Service. For Azure IoT Examples, it is recommended to set up Azure IoT Hub and DPS on your Azure Service Portal for testing. And for AmebaD IoT Hub Plug and Play Examples, you can either choose to connect to Azure IoT Hub/DPS or connect to Azure IoT Central for more simple deployment.

	Azure IoT Hub and DPS
	------------------------------------------------------------------------------------------------------------
	IoT Hub and DPS can be created on your Azure Portal. You can performed the following steps to setup your own IoT Service on Azure Portal and manage your resources.
	1. Create your IoT Hub on Azure Portal. Once created, you will be able to retrieve your IoT Hub hostname on your IoT Hub menu. This IoT Hub hostname is required for Azure examples in our SDK and will be filled in HUB_HOSTNAME in the example.
	2. Now you can add a device to your IoT Hub by either manually adding or by device provisioning. You have to specify the Device ID for your device and choose Symmetric key or X.509 for device connection if you add the device manually. If you use device provisioning, the Device ID will be assigned by DPS which will be same as the Registration ID of the device enrollment. Also, the registered device will keep the same authentication type as the DPS device enrollment.
	Once you have your device created, you can run the Azure example to connect your device to IoT Hub by giving HUB_HOSTNAME, device id as HUB_DEVICE_ID, connection authentication type either Symmetric key as HUB_SAS_KEY or X.509 certificate/private key as X509CERTIFICATE/ X509PRIVATEKEY.
	3. Create your Device Provisioning Services (DPS) on Azure Portal and have your device enrollment ready. The ID scope of the DPS and the Registration ID of device enrollment will be use in Azure Examples as ID_SCOPE and REGISTRATION_ID. Here we introduce individual enrollment only. When you add individual enrollment to your DPS, you can select Symmetric Key or X.509 mechanism.
	[SAS]
		For Symmetric Key (SAS), you have to specify the Registration ID, IoT Hub Device ID and IoT Hub hostname you want to assign to. The Primary key will be auto generated and will be used in the Azure examples as SAS_KEY. Once device provisioning is done, the device with name as your IoT Hub Device ID will be registered to your IoT hub. The registered device will use the same symmetric key for connection.
	[X509]
		For X.509, you have to specify the IoT Hub Device ID and IoT Hub hostname you want to assign to. Also, you need to select the X509 certificate file you have for provisioning.
		Please note that:
		i. Registration ID for X.509 individual enrollment is retrieved from the X.509 certificate Subject Name.
		ii. For the X509 certificate used for iot provisioning, please make sure your x509 certificate is create with x509 v3 extension.
			X509v3 Basic Constraints: CA:FALSE
			X509v3 Key Usage: Digital Signature, Non Repudiation, Key Encipherment
		To connect to DPS with X.509 enrollment, you will need to provide X509 certificate and private key as X509CERTIFICATE and X509PRIVATEKEY in your examples. Once device provisioning is done, the device with name as your IoT Hub Device ID will be registered to your IoT hub. The registered device will use the same X.509 certificate for connection.

	Azure IoT Central
	------------------------------------------------------------------------------------------------------------
	Azure IoT Central is an integrated platform for users to develop their Azure IoT Service. You can customize your IoT solution on this platform and manage your IoT resource easily and gracefully.
	First, you have to create an application on your Azure IoT Central and then select and publish AmebaD device on Device Template. Next, navigate to Devices and create a new device. For individual enrollment, follow the steps below to setup your device connection.
	1.	Click on you device.
	2.	Click on the Connect icon on your device page, you will see the Device connection window pops up.
	3.	Select Individual enrollment on the Authentication type.
	4.	Choose Shared access signature (SAS) or Certificate (X.509) on the Authentication method.
	5.	Enter the SAS Primary key or Upload the X.509 Certificate. There are some tips for creating the SAS key and X.509 Certificate in the below link.
		[https://docs.microsoft.com/en-us/azure/iot-central/core/concepts-get-connected#create-individual-enrollments]
	Now you can filled in the connection information to AmebaD IoT Hub Plug and Play examples where ID scope as ID_SCOPE, Device ID as REGISTRATION_ID, SAS key as SAS_KEY and X509 certificate/private key as X509CERTIFICATE/X509PRIVATEKEY.


Azure Example Description
-----------------------------------------------------------------------------------------------------------------------------------
Here we introduce how to run the examples on our sdk and a brief description on each example.
These examples work the same as the ones on Azure Embedded C SDK. So for the interaction of each example, please refer to azure-sdk-for-c on github:
[https://github.com/Azure/azure-sdk-for-c/blob/master/sdk/samples/iot/README.md]

	IoT Hub C2D Sample:
	------------------------------------------------------------------------------------------------------------
	This sample receives incoming cloud-to-device (C2D) messages sent from the Azure IoT Hub to the device.
	X509 Certificate is used to connect to iot hub.

		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_HUB_C2D to select the example.
		[example_azure_iot_hub_c2d.c]
			modify HUB_HOSTNAME to your own iot hub name
			modify HUB_DEVICE_ID to your own iot hub device id 
			modify X509CERTIFICATE to your own x509 certificate
			modify X509PRIVATEKEY to your own x509 private key


	IoT Hub Methods Sample:
	------------------------------------------------------------------------------------------------------------
	This sample receives incoming method commands invoked from the the Azure IoT Hub to the device.
	X509 Certificate is used to connect to iot hub.

		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_HUB_METHODS to select the example.
		[example_azure_iot_hub_methods.c]
			modify HUB_HOSTNAME to your own iot hub name
			modify HUB_DEVICE_ID to your own iot hub device id 
			modify X509CERTIFICATE to your own x509 certificate
			modify X509PRIVATEKEY to your own x509 private key


	IoT Hub Telemetry Sample:
	------------------------------------------------------------------------------------------------------------
	This sample sends five telemetry messages to the Azure IoT Hub.
	X509 Certificate is used to connect to iot hub.

		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_HUB_TELEMETRY to select the example.
		[example_azure_iot_hub_telemetry.c]
			modify HUB_HOSTNAME to your own iot hub name
			modify HUB_DEVICE_ID to your own iot hub device id 
			modify X509CERTIFICATE to your own x509 certificate
			modify X509PRIVATEKEY to your own x509 private key


	IoT Hub SAS Telemetry Sample:
	------------------------------------------------------------------------------------------------------------
	This sample sends five telemetry messages to the Azure IoT Hub
	SAS authentication is used to connect to iot hub.

		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_HUB_SAS_TELEMETRY to select the example.
		[example_azure_iot_hub_sas_telemetry.c]
			modify HUB_HOSTNAME to your own iot hub name
			modify HUB_DEVICE_ID to your own iot hub device id 
			modify HUB_SAS_KEY to your own SAS Key


	IoT Hub Twin Sample:
	------------------------------------------------------------------------------------------------------------
	This sample utilizes the Azure IoT Hub to get the device twin document, send a reported property message, 
	and receive up to 5 desired property messages.
	X509 Certificate is used to connect to iot hub.

		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_HUB_TWIN to select the example.
		[example_azure_iot_hub_twin.c]
			modify HUB_HOSTNAME to your own iot hub name
			modify HUB_DEVICE_ID to your own iot hub device id 
			modify X509CERTIFICATE to your own x509 certificate
			modify X509PRIVATEKEY to your own x509 private key


	IoT Hub Plug and Play Sample:
	------------------------------------------------------------------------------------------------------------
	This sample connects an IoT Plug and Play enabled device (a thermostat) with the Digital Twin Model ID (DTMI):
	[https://github.com/Azure/opendigitaltwins-dtdl/blob/master/DTDL/v2/samples/Thermostat.json]
	X509 Certificate is used to connect to iot hub.

		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_HUB_PNP to select the example.
		[example_azure_iot_hub_pnp.c]
			modify HUB_HOSTNAME to your own iot hub name
			modify HUB_DEVICE_ID to your own iot hub device id 
			modify X509CERTIFICATE to your own x509 certificate
			modify X509PRIVATEKEY to your own x509 private key


	IoT Hub Plug and Play Multiple Component Sample:
	------------------------------------------------------------------------------------------------------------
	This sample extends the IoT Hub Plug and Play Sample above to mimic a Temperature Controller and connects the 
	IoT Plug and Play enabled device (the Temperature Controller) with the Digital Twin Model ID (DTMI):
	[https://github.com/Azure/opendigitaltwins-dtdl/blob/master/DTDL/v2/samples/TemperatureController.json]
	X509 Certificate is used to connect to iot hub.

		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_HUB_PNP_COMPONENT to select the example.
		[example_azure_iot_hub_pnp_component.c]
			modify HUB_HOSTNAME to your own iot hub name
			modify HUB_DEVICE_ID to your own iot hub device id 
			modify X509CERTIFICATE to your own x509 certificate
			modify X509PRIVATEKEY to your own x509 private key


	IoT Provisioning Certificate Sample:
	------------------------------------------------------------------------------------------------------------
	This sample registers a device with the Azure IoT Device Provisioning Service.
	X509 Certificate is used to connect to device provisioning service.
	For the X509 certificate used for iot provisioning, please make sure it is create with x509 v3 extension:
		X509v3 Basic Constraints: CA:FALSE
		X509v3 Key Usage: Digital Signature, Non Repudiation, Key Encipherment


		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_PROVISIONING to select the example.
		[example_azure_iot_provisioning.c]
			modify HUB_HOSTNAME to your own iot hub name
			modify HUB_DEVICE_ID to your own iot hub device id 
			modify X509CERTIFICATE to your own x509 certificate
			modify X509PRIVATEKEY to your own x509 private key


	IoT Provisioning SAS Sample:
	------------------------------------------------------------------------------------------------------------
	This sample registers a device with the Azure IoT Device Provisioning Service.
	SAS authentication is used to connect to device provisioning service.

		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_PROVISIONING_SAS to select the example.
		[example_azure_iot_provisioning_sas.c]
			modify HUB_HOSTNAME to your own iot hub name
			modify HUB_DEVICE_ID to your own iot hub device id 
			modify HUB_SAS_KEY to your own SAS Key


Realtek Pnp Example Description
-----------------------------------------------------------------------------------------------------------------------------------
AmebaD IoT Hub Plug and Play examples are the application responsible for communication between AmebaD components and Azure IoT service. 
Basically there are two examples in our sdk, example_azure_iot_rtk_pnp_x509 and example_azure_iot_rtk_pnp_sas, who done the exactly same things except the authentication type of connection to DPS and IoT Hub.
After Wi-Fi is connected, the example will proceed. At the beginning of the example, it will connect to your DPS and register the device to your iothub. 
If succeed, you should see your device shown on Azure IoT Explorer. Next, the example will connect to your IoT Hub and start the plug and play process for AmebaD:

1.	MQTT Subscribe for command, device twins desired property and response.
2.	Initial all components. If there is some initial values or read only properties that you would like to initialize, you can do at this part.
3.	Update reported properties for all components for the first time and then send a twins document request to check the device status on IoT Hub.
4.	Start the telemetry thread. This thread is responsible for all component telemetry.
5.	Start receiving the messages that are subscribed from IoT Hub. AmebaD will then react to the incoming message, complete the proper operation to the corresponding component and response to IoT Hub.

To enable the examples in our AmebaD sdk:

	AmebaD IoT Hub Plug and PLay X509 Sample:
	------------------------------------------------------------------------------------------------------------
	AmebaD IoT Hub Plug and Play example with X509 certificate to provision device by DPS and start plug and play process.

		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_RTK_PNP_X509 to select the example.
		[example_azure_iot_rtk_pnp_x509.c]
			modify ID_SCOPE to your own DPS id scope.
			modify REGISTRATION_ID to your own DPS registration id. 
			modify X509CERTIFICATE to your own x509 certificate.
			modify X509PRIVATEKEY to your own x509 private key.
	Make sure the certificate has the x509 v3 extension. If you are going to connect to Azure IoT Central for device provisioning, you also have to make sure the issuer and subject CN set to the device ID in your x509 certificate.

	AmebaD IoT Hub Plug and PLay SAS Sample:
	------------------------------------------------------------------------------------------------------------
	AmebaD IoT Hub Plug and Play example with SAS authentication to provision device by DPS and start plug and play process.
		[example_azure_iot_entry.h]
			uncomment EXAMPLE_AZURE_IOT_RTK_PNP_SAS to select the example.
		[example_azure_iot_rtk_pnp_sas.c]
			modify ID_SCOPE to your own DPS id scope.
			modify REGISTRATION_ID to your own DPS registration id. 
			modify SAS_KEY to your own SAS key.

After AmebaD IoT Hub PnP examples are successfully executed, you can check your registered device on Azure IoT Explorer where its “IoT Plug and Play device” column shows dtmi:realtek:rtk_ameba_series;1.
Next, you can check all components on Azure IoT Explorer and interact with AmebaD.
There are four types of interfaces you can check on each component. Click in any component on the “IoT Plug and Play components” page, you will see the component details.

	[Property] The read-only property. You can check the properties in the “Properties (read-only)” tab.
	[Writable Property] The writable property. You can modified writable properties in the “Properties (writable)” tab.
	[Telemetry] The telemetry. You can see the telemetry messages received in the “Telemetry” tab.
	[Command] The commands. You can send commands in the “Commands” tab.

Realtek plug and play model files are placed on Realtek folder of Microsoft Public Repository, which are defined with Digital Twins Definition Language (DTDL):
	[https://github.com/Azure/iot-plugandplay-models/tree/main/dtmi/realtek]
The model files are divided into several components. Each component represents a feature of the device and details its telemetry, property and command to interact with Azure IoT service. 
Here we briefly introduce each component of AmebaD. 

	Ameba Series:
		Ameba Series is the AmebaD model file entry. It is the default component containing all the components of the device. 
		Our plug and play examples register the model id of this model file while connecting to DPS and IoT Hub. 
		You will see this component page once you click in your IoT Plug and Play components page on your registered device on Azure IoT Explorer.

	Audio:
		Audio Component defines the audio feature of the device. It only contains a support property and can be extended in the future.
			[Property] audio_support
				Audio support for device.

	Bluetooth: 
		Bluetooth Component defines the bluetooth feature of the device. It only contains a support property and can be extended in the future.
			[Property] bluetooth_support
				Bluetooth support for device.

	Device Information:
		Device Information Component records the information of the device containing several read-only properties. These properties should be configured by the firmware provider
			[Property] manufacturer
				Company name of the device manufacturer. 
			[Property] model
				Device model name.
			[Property] fw_version
				Version of the firmware on your device.

	GPIO:
		GPIO Component defined the GPIO feature of the device. In the examples, pinmux PA 12 and PB 5 are default enabled and can be directly used for gpio commands. 
		PB 5 is an output pin with PullNone mode and can be used as led pin. 
		PA 12 is an input pin with PullUp mode which can be used as a button pin. 
		You can test with these two gpio pins on AmebaD with the following commands.
		Pinmux is a combination of port number and pin number. There are 2 types of port number, PA and PB, and pin number with the range from 0 to 31.
			[Property] gpio_support
				GPIO support for device.
			[Command] gpio_set
				Given a pinmux with pin mode and direction, AmebaD will set the corresponding gpio pin. 
				If the pin number is out of range, you will get bad request response on your Azure IoT Explorer, otherwise you will get success response.
			[Command] gpio _read
				Read GPIO status from device. You will get 0 for pin low and 1 for pin high. 
				If GPIO pin is not initialized (by default or by gpio_set), you will get bad request response, otherwise you will get success response.
			[Command] gpio _write
				Sets value to the selected output port pin. You can select OFF to set pin low and ON to set pin high. 
				If GPIO pin is not initialized (by default or by gpio_set), you will get bad request response, otherwise you will get success response.

	LCD:
		LCD Component defines the lcd feature of the device. It only contains a support property and will be extended in the future.
			[Property] lcd_support
				LCD support for device.

	Memory:
		Memory Component defines the memory detail of the device.
			[Property] total_flash
				Size of flash on device. Represented with mebibyte.
			[Property] total_sram
				Size of sram on device. Represented with kibibyte.
			[Property] total_external_ram
				Size of external ram on device. Represented with mebibyte.
			[Telemetry] remain_heap
				Current available heap size on device. The value is represented with byte.
			[Writable Property] telemetry_enable_remain_heap
				Enable remain_heap option in telemetry. Set true to enable and false to disable.
			[Writable Property] telemetry_interval
				Interval for telemetry of Memory component. The number you set is represented with second.

	System:
		System Component defines the system detail of the device.
			[Property] build_info
				Build information of the firmware. It is represented as an object containing 4 information:
					fw_compile_time: the time that the firmware is generated.
					fw_compile_by: the name who builds the firmware.
					fw_compile_host: the host device for building firmware.
					fw_compiler: compiler information.
				These information is auto generated by AmebaD SDK.
			[Property] os_info
				OS information of the firmware.
			[Property] processor_architecture
				Processor architecture on device.
			[Telemetry] device_runtime
				Shows how long device has been running. Represented with seconds.
			[Telemetry] cpu_usage
				Shows CPU utilization of each running task. This information is directly retrieved from AmebaD OS and is represent as a single string.
				The message contain several task status where each task status is shown like “pnp_telem\t30772\t\t3%\r\n”.  
				“pnp_telem” is the task name, “30772” is the total run time allocated to the task so far and “3%” is the percentage of the total run time that the task has used. 
				Therefore the value is accumulated value of each task.
				To retrieve task status from OS, you need to enable configGENERATE_RUN_TIME_STATS in “inc_hp\FreeRTOSConfig.h”.
			[Writable Property] telemetry_enable_device_runtime
				Enable device_runtime option in telemetry. Set true to enable and false to disable.
			[Writable Property] telemetry_enable_cpu_usage
				Enable cpu_usage option in telemetry. Set true to enable and false to disable.
			[Writable Property] telemetry_interval
				Interval for telemetry of System component. The number you set is represented with second. The above two telemetry of System will be set to the same interval.
			[Command] reboot
				System reboot after given time. We will leave 5 seconds to reboot the device to make sure the command response is correctly reply from device. 
				If the time you set is less than 5 seconds from now or even you set a time that has already passed, the device will reboot in 5 seconds.
			[Command] switch_to_upgraded_image
				Switch to OTA upgraded firmware and reboot the device in 5 seconds. 
				OTA process should be done before switching firmware and make sure the OTA firmware can connected to IoT Hub and well function as well.
				To enable OTA features, you need to enable CONFIG_OTA_UPDATE in “inc_hp\platform_opts.h”.
			[Command] switch_to_default_image
				Switch back to default firmware and reboot the device in 5 seconds. 
				To enable OTA features, you need to enable CONFIG_OTA_UPDATE in “inc_hp\platform_opts.h”.

	Video: 
		Video Component defines the video feature of the device. It only contains a support property and will be extended in the future
			[Property] video_support
				Video support for device.

	Wireless:
		Wireless Component defines the Wi-Fi feature of the device.
			[Property] wireless_support
				Wireless support for device.
			[Property] specification
				Wireless specification.
			[Telemetry] wifi_info
				The telemetry message that shows current Wi-Fi connection information. 
				It is represent as an object containing the station mode connection information and station mode interface configuration.
				Station mode connection information:
					ssid: SSID of the connection AP
					channel: Connected channel to AP.
					security: Security type of connecting AP. Should be one of OPEN, WEP, TKIP, AES or UNLNOWN.
					password: Password of connecting AP. Show nothing if open mode.
				Station mode interface configuration:
					mac: mac address of device station mode interface.
					ip: assigned IP address.
					gw: gateway.
					msk: Network mask.
			[Writable Property] telemetry_enable_wifi_info
				Enable wifi_info option in telemetry. Set true to enable and false to disable.
			[Writable Property] telemetry_interval
				Interval for telemetry of Wireless component. The number you set is represented with second.
			[Command] wifi_connect
				Connect to specified AP with your given ssid and password. It will response success and start a wifi connection thread to connect to the specified AP after 5 seconds.
			[Command] wifi_scan 
				Scan for netowrk access point around the device. 
				You can specify the channels you would like to scan by providing the numbers of channels as an array elements. Leave blank to default scan for all channels.
				Note that it is possible to take longer time to search for the access points and cause response time out if you scan for all channels. 
				You can try more times or search for less channels.
				The response of Wi-Fi scan contain at most 5 objects where each object record the information of scanned access point.
					idx: index of scanned AP, starting from 1.
					bss_type: 2 bss types. “Adhoc” for ad-hoc mode and “Infra” for infrastructure mode.
					mac: Mac address of AP.
					signal_strength: signal strength of AP, represented with db. 
					channel: channel of AP. 
					wps_type: AP WPS types. One of DEFAULT, USER_SPECIFIED, MACHINE_SPECIFIED, REKEY, PUSHBUTTON, REGISTRAR_SPECIFIED, NONE, WSC or Unknown.
					security: AP Security type. One of Open, WEP, WPA TKIP, WPA AES, WPA2 AES, WPA2 TKIP, WPA2 Mixed, WPA/WPA2 AES, WPA2 Enterprise, WPA/WPA2 Enterprise, WP3-SAE AES or Unknown.
					ssid: SSID of scanned AP.
			[Command] ota
				Over-the-Air firmware update via Wi-Fi. The OTA image should be placed on local server and device will download upgraded image from the local server. 
				Therefore, for testing, you should have your OTA image ready and upload to local server. 
				Then you can send the ota command where “ip_address” as IP of local server and “port” as port of local server. 
				After OTA is done, you can use “switch_to_upgraded_image” and “switch_to_default_image” commands in System component to switch firmware.
				To enable OTA features, you need to enable CONFIG_OTA_UPDATE in “inc_hp\platform_opts.h”.
				For the detail of OTA process and the OTA image generation, please refer to document on AmebaD Website or contact Realtek for further information.
			[Command] ping
				Ping for specified host. AmebaD will ping for the host with your provided parameters. 
					host_address: You should provide a valid “host_address” for pinging with the format like 127.0.0.1. 
					number: The number for pinging is default 4 times, you can raise it to up to 20 times. It was concerned that too much ping times will cause response timeout, therefore we limited the number to lower than 20.
					buffer_size: Payload size to send while pinging. Default 32Byte.
				The ping response is represented with 3 parts.
					info: Ping info that you provided.
					content: The ping results will be placed as array elements in this part.
					result: The conclusion of this ping process.

Supported List
-----------------------------------------------------------------------------------------------------------------------------------
Ameba-D, Ameba-Z2