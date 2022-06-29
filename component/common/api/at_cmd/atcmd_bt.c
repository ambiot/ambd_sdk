#include "log_service.h"
#include "atcmd_bt.h"
#include <platform/platform_stdlib.h>
#include <platform_opts.h>
#if defined(CONFIG_PLATFORM_8710C)
#include <platform_opts_bt.h>
#endif

#if defined(CONFIG_BT) && CONFIG_BT
#include "os_msg.h"
#include "app_msg.h"
#include "gap_le.h"
#include "gap_msg.h"
#include "gap_customer.h"

#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
#include "app_flags.h"
#include "ble_peripheral_at_cmd.h"
extern void *evt_queue_handle;
extern void *io_queue_handle;
#endif

#if defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL
#include "ble_central_app_flags.h"
#include "ble_central_at_cmd.h"
extern void *ble_central_evt_queue_handle;
extern void *ble_central_io_queue_handle;
#endif

#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
#include "ble_scatternet_app_flags.h"
extern void *ble_scatternet_evt_queue_handle;
extern void *ble_scatternet_io_queue_handle;
#endif

#if defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE
#include "bt_mesh_provisioner_multiple_profile_app_flags.h"
#if (defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL)
#include "ble_peripheral_at_cmd.h"
#elif (defined(CONFIG_BT_MESH_CENTRAL) && CONFIG_BT_MESH_CENTRAL)
#include "ble_central_at_cmd.h"
#elif (defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET)
#include "ble_peripheral_at_cmd.h"
#include "ble_central_at_cmd.h"
#endif
extern void *bt_mesh_provisioner_multiple_profile_evt_queue_handle;
extern void *bt_mesh_provisioner_multiple_profile_io_queue_handle;
#endif

#if defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE
#include "bt_mesh_device_multiple_profile_app_flags.h"
#if (defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL)
#include "ble_peripheral_at_cmd.h"
#elif (defined(CONFIG_BT_MESH_CENTRAL) && CONFIG_BT_MESH_CENTRAL)
#include "ble_central_at_cmd.h"
#elif (defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET)
#include "ble_peripheral_at_cmd.h"
#include "ble_central_at_cmd.h"
#endif
extern void *bt_mesh_device_multiple_profile_evt_queue_handle;
extern void *bt_mesh_device_multiple_profile_io_queue_handle;
#endif

#if defined(CONFIG_BT_BREEZE) && CONFIG_BT_BREEZE
#include "breeze_hal_ble.h"
#endif

uint8_t bt_cmd_type = 0x00;

void set_bt_cmd_type(uint8_t cmd_type)
{
	bt_cmd_type = cmd_type;
}

uint8_t bt_command_type(uint16_t command_type)
{
	switch (command_type) {
	case BT_COMMAND_CENTRAL: {
			if (!((bt_cmd_type & CENTRAL_BIT) >> 7)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_PERIPHERAL: {
			if (!((bt_cmd_type & PERIPHERAL_BIT) >> 6)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_SCATTERNET: {
			if (!((bt_cmd_type & SCATTERNET_BIT) >> 5)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_BEACON: {
			if (!((bt_cmd_type & BEACON_BIT) >> 4)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_CONFIG: {
			if (!((bt_cmd_type & CONFIG_BIT) >> 3)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_AIRSYNC_CONFIG: {
			if (!((bt_cmd_type & AIRSYNC_CONFIG_BIT) >> 2)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_MESH: {
			if (!((bt_cmd_type & MESH_BIT) >> 1)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_STACK: {
			if (!(bt_cmd_type & STACK_BIT)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_SCAN:
	case BT_COMMAND_CONNECT:
	case BT_COMMAND_DISCONNECT:
	case BT_COMMAND_GET:
	case BT_COMMAND_GET_CONN_INFO:
	case BT_COMMAND_READ:
	case BT_COMMAND_WRITE:
	case BT_COMMAND_MODIFY_WHITELIST:
	case BT_COMMAND_SET_SCAN_PARAM:
	case BT_COMMAND_SET_PHY: {
			if (!((bt_cmd_type & CENTRAL_BIT) >> 7) && !((bt_cmd_type & SCATTERNET_BIT) >> 5) && !((bt_cmd_type & MESH_BIT) >> 1)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_SEND_INDI_NOTI:
	case BT_COMMAND_MODIFY_ADV_INTERVAL: {
			if (!((bt_cmd_type & PERIPHERAL_BIT) >> 6) && !((bt_cmd_type & SCATTERNET_BIT) >> 5) && !((bt_cmd_type & MESH_BIT) >> 1)) {
				return 0;
			}
		}
		break;
	case BT_COMMAND_AUTH:
	case BT_COMMAND_SEND_USERCONF:
	case BT_COMMAND_UPDATE_CONN_REQUEST:
	case BT_COMMAND_BOND_INFORMATION: {
			if (!((bt_cmd_type & CENTRAL_BIT) >> 7) && !((bt_cmd_type & PERIPHERAL_BIT) >> 6) && !((bt_cmd_type & SCATTERNET_BIT) >> 5) &&
				!((bt_cmd_type & MESH_BIT) >> 1)) {
				return 0;
			}
		}
		break;
	default:
		break;
	}
	return 1;
}

#if ((defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL) || \
	(defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL) || \
	(defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET) || \
	(defined(CONFIG_BT_MESH_CENTRAL) && CONFIG_BT_MESH_CENTRAL) || \
	(defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
char bt_at_cmd_buf[256] = {0};
void bt_at_cmd_send_msg(uint16_t subtype, void *arg)
{
	uint8_t event = EVENT_IO_TO_APP;

	T_IO_MSG io_msg;

	io_msg.type = IO_MSG_TYPE_AT_CMD;
	io_msg.subtype = subtype;
	io_msg.u.buf = arg;

#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
	if (evt_queue_handle != NULL && io_queue_handle != NULL) {
		if (os_msg_send(io_queue_handle, &io_msg, 0) == false) {
			AT_PRINTK("bt at cmd send msg fail: subtype 0x%x", io_msg.subtype);
		} else if (os_msg_send(evt_queue_handle, &event, 0) == false) {
			AT_PRINTK("bt at cmd send event fail: subtype 0x%x", io_msg.subtype);
		}
	}
#endif
#if defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL
	if (ble_central_evt_queue_handle != NULL && ble_central_io_queue_handle != NULL) {
		if (os_msg_send(ble_central_io_queue_handle, &io_msg, 0) == false) {
			AT_PRINTK("bt at cmd send msg fail: subtype 0x%x", io_msg.subtype);
		} else if (os_msg_send(ble_central_evt_queue_handle, &event, 0) == false) {
			AT_PRINTK("bt at cmd send event fail: subtype 0x%x", io_msg.subtype);
		}
	}
#endif
#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
	if (ble_scatternet_evt_queue_handle != NULL && ble_scatternet_io_queue_handle != NULL) {
		if (os_msg_send(ble_scatternet_io_queue_handle, &io_msg, 0) == false) {
			AT_PRINTK("bt at cmd send msg fail: subtype 0x%x", io_msg.subtype);
		} else if (os_msg_send(ble_scatternet_evt_queue_handle, &event, 0) == false) {
			AT_PRINTK("bt at cmd send event fail: subtype 0x%x", io_msg.subtype);
		}
	}
#endif
#if defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE
	if (bt_mesh_device_multiple_profile_evt_queue_handle != NULL && bt_mesh_device_multiple_profile_io_queue_handle != NULL) {
		if (os_msg_send(bt_mesh_device_multiple_profile_io_queue_handle, &io_msg, 0) == false) {
			AT_PRINTK("bt at cmd send msg fail: subtype 0x%x", io_msg.subtype);
		} else if (os_msg_send(bt_mesh_device_multiple_profile_evt_queue_handle, &event, 0) == false) {
			AT_PRINTK("bt at cmd send event fail: subtype 0x%x", io_msg.subtype);
		}
	}
#endif
#if defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE
	if (bt_mesh_provisioner_multiple_profile_evt_queue_handle != NULL && bt_mesh_provisioner_multiple_profile_io_queue_handle != NULL) {
		if (os_msg_send(bt_mesh_provisioner_multiple_profile_io_queue_handle, &io_msg, 0) == false) {
			AT_PRINTK("bt at cmd send msg fail: subtype 0x%x", io_msg.subtype);
		} else if (os_msg_send(bt_mesh_provisioner_multiple_profile_evt_queue_handle, &event, 0) == false) {
			AT_PRINTK("bt at cmd send event fail: subtype 0x%x", io_msg.subtype);
		}
	}
#endif
}
#endif

#if ((defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL) || \
	(defined(CONFIG_BT_MESH_CENTRAL) && CONFIG_BT_MESH_CENTRAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
#if defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL
extern int ble_central_app_init(void);
extern void ble_central_app_deinit(void);
void fATBc(void *arg)
{
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);
	if (param == 1) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBc]:_AT_BLE_CENTRAL_[ON]\n\r");
		ble_central_app_init();
		set_bt_cmd_type(CENTRAL_BIT | STACK_BIT);
	} else if (param == 0) {
		if (!bt_command_type(BT_COMMAND_CENTRAL)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBc]:_AT_BLE_CENTRAL_[OFF]\n\r");
		ble_central_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBc] Start BLE Central: ATBc=1");
	AT_PRINTK("[ATBc] Stop  BLE Central: ATBc=0");
}
#endif

void fATBC(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if (argc != 3) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_CONNECT)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_CONNECT, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBC] Connect to remote device: ATBC=P/R,BLE_BD_ADDR");
	AT_PRINTK("[ATBC] P=public, R=random");
	AT_PRINTK("[ATBC] eg:ATBC=P,001122334455");
}

void fATBD(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_DISCONNECT)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_DISCONNECT, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBD] Disconnect to remote device: ATBD=connect_id");
	AT_PRINTK("[ATBD] eg:ATBD=0");
}

void fATBI(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	}

	if (argc != 0) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_GET_CONN_INFO)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_GET_COON_INFO, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBI] Get all connected device information: ATBI");
	AT_PRINTK("[ATBI] eg:ATBI");
}

void fATBG(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if ((argc != 3) && (argc != 5) && (argc != 7)) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_GET)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_GET, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBG] Get all services: ATBG=ALL,connect_id");
	AT_PRINTK("[ATBG] Discover services by uuid: ATBG=SRV,connect_id,uuid_type,uuid");
	AT_PRINTK("[ATBG] Discover characteristic: ATBG=CHARDIS,connect_id,start_handle,end_handle");
	AT_PRINTK("[ATBG] Discover characteristic by uuid: ATBG=CHARUUID,connect_id,start_handle,end_handle,type,uuid");
	AT_PRINTK("[ATBG] Discover characteristic descriptor: ATBG=CHARDDIS,connect_id,start_handle,end_handle");
	AT_PRINTK("[ATBG] eg:ATBG=ALL,0");
	AT_PRINTK("[ATBG] eg(uuid16):ATBG=SRV,0,0,1803");
	AT_PRINTK("[ATBG] eg(uuid128):ATBG=SRV,0,1,00112233445566778899aabbccddeeff");
	AT_PRINTK("[ATBG] eg:ATBG=CHARDIS,0,0x8,0xFF");
	AT_PRINTK("[ATBG] eg(uuid16):ATBG=CHARUUID,0,0x1,0xFFFF,0,B001");
	AT_PRINTK("[ATBG] eg(uuid128):ATBG=CHARUUID,0,0x1,0xFFFF,1,00112233445566778899aabbccddeeff");
	AT_PRINTK("[ATBG] eg:ATBG=CHARDDIS,0,0xe,0x10");
}

void fATBS(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if ((argc != 2) && (argc != 3) && (argc != 4)) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_SCAN)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	ble_central_at_cmd_scan(argc, argv);
	return;

exit:
	AT_PRINTK("[ATBS] Scan:ATBS=scan_enable,filter_policy,filter_duplicate");
	AT_PRINTK("[ATBS] [scan_enable]:0-(stop scan), 1(start scan)");
	AT_PRINTK("[ATBS] [filter_policy]: 0-(any), 1-(whitelist), 2-(any RPA), 3-(whitelist RPA)");
	AT_PRINTK("[ATBS] [filter_duplicate]: 0-(disable), 1-(enable)");
	AT_PRINTK("[ATBS] eg:ATBS=1");
	AT_PRINTK("[ATBS] eg:ATBS=1,0");
	AT_PRINTK("[ATBS] eg:ATBS=1,0,1");
	AT_PRINTK("[ATBS] eg:ATBS=0");
}

void fATBR(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if ((argc != 3) && (argc != 6)) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_READ)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_READ, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBR] Read characteristic: ATBR=conn_id,handle");
	AT_PRINTK("[ATBR] Read characterristic value by uuid: ATBR=conn_id,start_handle,end_handle,uuid_type,uuid");
	AT_PRINTK("[ATBR] eg:ATBR=0,0xa");
	AT_PRINTK("[ATBR] eg(uuid16):ATBR=0,0x1,0xFFFF,0,B001");
	AT_PRINTK("[ATBR] eg(uuid128):ATBR=0,0x1,0xFFFF,1,00112233445566778899aabbccddeeff");
}

void fATBW(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if (argc < 5) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_WRITE)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_WRITE, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBW] Write data to service: ATBW=conn_id,type,handle,length,value");
	AT_PRINTK("[ATBW] [type]: write type: 1-(write request), 2-(write command)");
	AT_PRINTK("[ATBW] [handle]: attribute handle");
	AT_PRINTK("[ATBW] [length]: value length");
	AT_PRINTK("[ATBW] [lvalue]: overwrite the value");
	AT_PRINTK("[ATBW] eg:ATBW=0,1,0xc,0x1,0x02");
	AT_PRINTK("[ATBW] eg:ATBW=0,2,0x19,0x2,0x10,0x20");
}

void fATBn(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if ((argc != 2) && (argc != 4)) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_MODIFY_WHITELIST)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_MODIFY_WHITELIST, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBn] Clear white list: ATBn=0");
	AT_PRINTK("[ATBn] Add a device to the white list: ATBn=1,P/R,addr");
	AT_PRINTK("[ATBn] Remove a device from the white list: ATBn=2,P/R,addr");
}

void fATBa(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if (argc != 3) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_SET_SCAN_PARAM)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_SET_SCAN_PARAM, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBa] Modify scan interval:ATBa=1,scan_interval");
	AT_PRINTK("[ATBa] Modify scan window:ATBa=2,scan_window");
	AT_PRINTK("[ATBa] Modify scan interval:ATBa=1,0x190");
	AT_PRINTK("[ATBa] Modify scan window:ATBa=2,0xC8");
}

void fATBg(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if (argc != 3) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_SET_PHY)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_SET_PHY, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBg] Set BLE PHY(2M): ATBg=conn_id,phy");
	AT_PRINTK("[ATBg] Set BLE PHY(2M): ATBg=0,1");
}
#endif

#if ((defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
extern int ble_app_init(void);
extern void ble_app_deinit(void);
void fATBp(void *arg)
{
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);
	if (param == 1) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBp]:_AT_BLE_PERIPHERAL_[ON]\n\r");
		ble_app_init();
		set_bt_cmd_type(PERIPHERAL_BIT | STACK_BIT);
	} else if (param == 0) {
		if (!bt_command_type(BT_COMMAND_PERIPHERAL)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBp]:_AT_BLE_PERIPHERAL_[OFF]\n\r");
		ble_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBp] Start BLE Peripheral: ATBp=1");
	AT_PRINTK("[ATBp] Stop  BLE Peripheral: ATBp=0");
}

#if (LEGACY_ADV_CONCURRENT == 1)
extern void legacy_adv_concurrent_init(uint32_t adv_interval_0, uint32_t adv_interval_1);
extern void legacy_adv_concurrent_start(void);
extern void legacy_adv_concurrent_stop(void);
extern void legacy_adv_concurrent_deinit(void);
#endif
void fATBP(void *arg)
{
#if (LEGACY_ADV_CONCURRENT == 1)
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if ((argc != 2) && (argc != 4)) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);
	if (param == 1 && argc == 4) {
		uint32_t adv_int_0 = atoi(argv[2]);
		uint32_t adv_int_1 = atoi(argv[3]);
		legacy_adv_concurrent_init(adv_int_0, adv_int_1);
	} else if (param == 0) {
		legacy_adv_concurrent_deinit();
	} else if (param == 2) {
		legacy_adv_concurrent_start();
	} else if (param == 3) {
		legacy_adv_concurrent_stop();
	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBP] Init   legacy adv concurrent: ATBP=1,adv_int_0(ms),adv_int_1(ms)");
	AT_PRINTK("[ATBP] Deinit legacy adv concurrent: ATBP=0");
	AT_PRINTK("[ATBP] Start  legacy adv concurrent: ATBP=2");
	AT_PRINTK("[ATBP] Stop   legacy adv concurrent: ATBP=3");
#endif
}
#endif

void fATBA(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 3) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_MODIFY_ADV_INTERVAL)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	ble_peripheral_at_cmd_set_adv_int(argc, argv);
	return;

exit:
	AT_PRINTK("[ATBA] Modify adv interval:ATBA=adv_interval_max,adv_interval_min");
	AT_PRINTK("[ATBA] Modify adv interval:ATBA=1600,1600");
}

void fATBe(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if (argc < 6) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_SEND_INDI_NOTI)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_SEND_INDI_NOTI, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBe] server send indication or notification");
	AT_PRINTK("[ATBe] ATBe=conn_id,service_id,attribute_index,type,length,p_value");
	AT_PRINTK("[ATBe] simple ble service send indication:ATBe=0,1,0xa,2,0x1,0x1");
	AT_PRINTK("[ATBe] simple ble service send notification:ATBe=0,1,0x7,1,0x2,0x1,0x2");
	AT_PRINTK("[ATBe] bas service send notification:ATBe=0,2,0x2,1,0x1,0x1");
}
#endif

#if ((defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL) || \
	(defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_CENTRAL) && CONFIG_BT_MESH_CENTRAL) || \
	(defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
void fATBK(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if ((argc != 3) && (argc != 4) && (argc != 6)) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_AUTH)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_AUTH, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBK] Config and Set authentication information");
	AT_PRINTK("[ATBK] ATBK=SEND,conn_id");
	AT_PRINTK("[ATBK] ATBK=KEY,conn_id,passcode");
	AT_PRINTK("[ATBK] ATBK=MODE,auth_flags,io_cap,sec_enable,oob_enable");
	AT_PRINTK("[ATBK] eg:ATBK=SEND,0");
	AT_PRINTK("[ATBK] eg:ATBK=KEY,0,123456");
	AT_PRINTK("[ATBK] eg:ATBK=MODE,0x5,2,1,0");
}

void fATBY(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if (argc != 3) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_SEND_USERCONF)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_SEND_USERCONF, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBY] Send user confirmation when show GAP_MSG_LE_BOND_USER_CONFIRMATION");
	AT_PRINTK("[ATBY] ATBY=[conn_id],[conf]");
	AT_PRINTK("[ATBY] [conf]=0-(Reject),1(Accept)");
	AT_PRINTK("[ATBY] eg:ATBY=0,1");
}

void fATBU(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if (argc != 6) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_UPDATE_CONN_REQUEST)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_UPDATE_CONN_REQUEST, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBU] Connection param update request: ATBU=conn_id,interval_min,interval_max,latency,supervision_timeout");
	AT_PRINTK("[ATBU] eg:ATBU=0,0x30,0x40,0x0,0x1F4");
}

void fATBO(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	memset(bt_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(bt_at_cmd_buf, arg, sizeof(bt_at_cmd_buf));
		argc = parse_param(bt_at_cmd_buf, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	if (!bt_command_type(BT_COMMAND_BOND_INFORMATION)) {
		AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
		goto exit;
	}

	bt_at_cmd_send_msg(BT_ATCMD_BOND_INFORMATION, bt_at_cmd_buf);
	return;

exit:
	AT_PRINTK("[ATBO] Clear bond information: ATBO=CLEAR");
	AT_PRINTK("[ATBO] Get bond information: ATBO=INFO");
}
#endif

#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
extern int ble_scatternet_app_init(void);
extern void ble_scatternet_app_deinit(void);
void fATBf(void *arg)
{
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);
	if (param == 1) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBf]:_AT_BLE_SCATTERNET_[ON]\n\r");
		ble_scatternet_app_init();
		set_bt_cmd_type(SCATTERNET_BIT | STACK_BIT);
	} else if (param == 0) {
		if (!bt_command_type(BT_COMMAND_SCATTERNET)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBf]:_AT_BLE_SCATTERNET_[OFF]\n\r");
		ble_scatternet_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBf] Start BLE Scatternet: ATBf=1");
	AT_PRINTK("[ATBf] Stop  BLE Scatternet: ATBf=0");
}
#endif

#if defined(CONFIG_BT_BEACON) && CONFIG_BT_BEACON
extern int bt_beacon_app_init(int type);
extern void bt_beacon_app_deinit(void);
void fATBJ(void *arg)
{
	int argc = 0;
	int param = 0;
	int type = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if ((argc != 2) && (argc != 3)) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);
	if (param == 1 && argc == 3) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		type = atoi(argv[2]);
		if (type == 1) {
			AT_PRINTK("[ATBJ]:_AT_BT_I_BEACON_[ON]\n\r");
		} else if (type == 2) {
			AT_PRINTK("[ATBJ]:_AT_BT_ALT_BEACON_[ON]\n\r");
		} else {
			goto exit;
		}
		bt_beacon_app_init(type);
		set_bt_cmd_type(BEACON_BIT | STACK_BIT);
	} else if (param == 0 && argc == 2) {
		if (!bt_command_type(BT_COMMAND_BEACON)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBJ]:_AT_BT_BEACON_[OFF]\n\r");
		bt_beacon_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBJ] Start BT I_Beacon: ATBJ=1,1");
	AT_PRINTK("[ATBJ] Start BT Alt_Beacon: ATBJ=1,2");
	AT_PRINTK("[ATBJ] Stop  BT Beacon: ATBJ=0");
}
#endif

#if defined(CONFIG_BT_CONFIG) && CONFIG_BT_CONFIG
extern int bt_config_app_init(void);
extern void bt_config_app_deinit(void);
void fATBB(void *arg)
{
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);
	if (param == 1) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBB]:_AT_BT_CONFIG_[ON]\n\r");
		bt_config_app_init();
		set_bt_cmd_type(CONFIG_BIT | STACK_BIT);
	} else if (param == 0) {
		if (!bt_command_type(BT_COMMAND_CONFIG)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBB]:_AT_BT_CONFIG_[OFF]\n\r");
		bt_config_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBB] Start BT Config: ATBB=1");
	AT_PRINTK("[ATBB] Stop  BT Config: ATBB=0");
}
#endif

#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
extern int bt_airsync_config_app_init(void);
extern void bt_airsync_config_app_deinit(void);
void fATBb(void *arg)
{
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);
	if (param == 1) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBb]:_AT_BT_AIRSYNC_CONFIG_[ON]\n\r");
		bt_airsync_config_app_init();
		set_bt_cmd_type(AIRSYNC_CONFIG_BIT | STACK_BIT);
	} else if (param == 0) {
		if (!bt_command_type(BT_COMMAND_AIRSYNC_CONFIG)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBb]:_AT_BT_AIRSYNC_CONFIG_[OFF]\n\r");
		bt_airsync_config_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBb] Start BT Airsync Config: ATBb=1");
	AT_PRINTK("[ATBb] Stop  BT Airsync Config: ATBb=0");
}
#endif

#if defined(CONFIG_BT_BREEZE) && CONFIG_BT_BREEZE
static ais_adv_init_t adv_data = {
	.flag = AIS_AD_GENERAL | AIS_AD_NO_BREDR,
	.name = { .ntype = AIS_ADV_NAME_FULL, .name = "AZ" },
};

static void init_done_cb(uint8_t res)
{
	if (!res) {
		printf("\r\nBreeze has initialized\r\n");
	}
}

static void connect_cb(void)
{
	printf("\r\nBreeze has connected\r\n");
}

static void disconnect_cb(void)
{
	printf("\r\nBreeze has disconnected\r\n");
}

static ais_bt_init_t attr_info = {
	/* service */
	AIS_UUID_DECLARE_16(BLE_UUID_AIS_SERVICE),
	/* rc */
	{
		.uuid          = AIS_UUID_DECLARE_16(BLE_UUID_AIS_RC),
		.prop          = AIS_GATT_CHRC_READ,
		.perm          = AIS_GATT_PERM_READ | AIS_GATT_PERM_READ_AUTHEN,
		.on_read       = NULL,
		.on_write      = NULL,
		.on_ccc_change = NULL
	},
	/* wc */
	{
		.uuid          = AIS_UUID_DECLARE_16(BLE_UUID_AIS_WC),
		.prop          = AIS_GATT_CHRC_READ | AIS_GATT_CHRC_WRITE,
		.perm          = AIS_GATT_PERM_READ | AIS_GATT_PERM_WRITE,
		.on_read       = NULL,
		.on_write      = NULL,//wc_write_handler,
		.on_ccc_change = NULL
	},
	/* ic */
	{
		.uuid          = AIS_UUID_DECLARE_16(BLE_UUID_AIS_IC),
		.prop          = AIS_GATT_CHRC_READ | AIS_GATT_CHRC_INDICATE,
		.perm          = AIS_GATT_PERM_READ,
		.on_read       = NULL,
		.on_write      = NULL,
		.on_ccc_change = NULL
	},//ic_ccc_handler },
	/* wwnrc */
	{
		.uuid          = AIS_UUID_DECLARE_16(BLE_UUID_AIS_WWNRC),
		.prop          = AIS_GATT_CHRC_READ | AIS_GATT_CHRC_WRITE_WITHOUT_RESP,
		.perm          = AIS_GATT_PERM_READ | AIS_GATT_PERM_WRITE,
		.on_read       = NULL,
		.on_write      = NULL,//wwnrc_write_handler,
		.on_ccc_change = NULL
	},
	/* nc */
	{
		.uuid          = AIS_UUID_DECLARE_16(BLE_UUID_AIS_NC),
		.prop          = AIS_GATT_CHRC_READ | AIS_GATT_CHRC_NOTIFY,
		.perm          = AIS_GATT_PERM_READ,
		.on_read       = NULL,
		.on_write      = NULL,
		.on_ccc_change = NULL
	},//nc_ccc_handler },
	connect_cb,//connected,
	disconnect_cb//disconnected
};

void fATBi(void *arg)
{
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);
	if (param == 1) {
		AT_PRINTK("[ATBi]:_AT_BT_BREEZE_[ON]\n\r");
		ble_stack_init(&attr_info, init_done_cb);
	} else if (param == 0) {
		AT_PRINTK("[ATBi]:_AT_BT_BREEZE_[OFF]\n\r");
		ble_stack_deinit();
	} else if (param == 2) {
		AT_PRINTK("[ATBi]:_AT_BT_BREEZE_ADV_[ON]\n\r");
		ble_advertising_start(&adv_data);
	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBi] Start BT Breeze:  ATBi=1");
	AT_PRINTK("[ATBi] Stop  BT Breeze:  ATBi=0");
	AT_PRINTK("[ATBi] Start Breeze ADV: ATBi=2");
}
#endif

#if defined(CONFIG_BT_TAG_SCANNER) && CONFIG_BT_TAG_SCANNER
extern int bt_tag_scanner_app_init(void);
extern void bt_tag_scanner_app_deinit(void);
extern void *bt_tag_scanner_evt_queue_handle;  //!< Event queue handle
extern void *bt_tag_scanner_io_queue_handle;   //!< IO queue handle

void fATBt(void *arg)
{
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);

	if (param == 1) {
		AT_PRINTK("[ATBt]:_AT_BT_TAG_SCANNER_[ON]\n\r");
		bt_tag_scanner_app_init();
	
	} else if (param == 0) {
		AT_PRINTK("[ATBt]:_AT_BT_TAG_SCANNER_[OFF]\n\r");
		bt_tag_scanner_app_deinit();

	} else if (param == 2){
		uint8_t event = EVENT_IO_TO_APP;
		T_IO_MSG io_msg;
		io_msg.type = IO_MSG_TYPE_QDECODE;

		if (bt_tag_scanner_evt_queue_handle != NULL && bt_tag_scanner_io_queue_handle != NULL) {
			if (os_msg_send(bt_tag_scanner_io_queue_handle, &io_msg, 0) == false) {
				AT_PRINTK("bt at cmd send msg fail");
			} else if (os_msg_send(bt_tag_scanner_evt_queue_handle, &event, 0) == false) {
				AT_PRINTK("bt at cmd send event fail");
			}
		}

	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBt] Start BT Tag Scanner: ATBt=1");
	AT_PRINTK("[ATBt] Clear records: ATBt=2");
	AT_PRINTK("[ATBt] Stop  BT Tag Scanner: ATBt=0");
}
#endif

#if defined(CONFIG_BT_ANCS) && CONFIG_BT_ANCS
extern int bt_ancs_app_init(void);
extern void bt_ancs_app_deinit(void);
void fATBN(void *arg)
{
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);

	if (param == 1) {
		AT_PRINTK("[ATBN]:_AT_BT_ANCS_[ON]\n\r");
		bt_ancs_app_init();

	} else if (param == 0) {
		AT_PRINTK("[ATBN]:_AT_BT_ANCS_[OFF]\n\r");
		bt_ancs_app_deinit();

	} else {
		goto exit;
	}

	return;

exit:
	AT_PRINTK("[ATBN] Start BT ANCS: ATBN=1");
	AT_PRINTK("[ATBN] Stop	BT ANCS: ATBN=0");
}
#endif

#if defined(CONFIG_BT_DISTANCE_DETECTOR) && CONFIG_BT_DISTANCE_DETECTOR
extern int bt_distance_detector_app_init(void);
extern void bt_distance_detector_app_deinit(void);
extern bool bt_distance_detector_send_msg_to_apptask(uint16_t subtype);
extern void *bt_distance_detector_evt_queue_handle;  //!< Event queue handle
extern void *bt_distance_detector_io_queue_handle;   //!< IO queue handle
void fATBd(void *arg)
{
	int argc = 0;
	int param = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg)
		argc = parse_param(arg, argv);
	else
		goto exit;

	if (argc != 2) {
		AT_PRINTK("[AT_PRINTK] ERROR: input parameter error!\n\r");
		goto exit;
	}

	param = atoi(argv[1]);
	if (param == 1) {
		AT_PRINTK("[ATBd]:_AT_BT_DISTANCE_DETECTOR_[ON]\n\r");
		bt_distance_detector_app_init();
	} else if (param == 0) {
		AT_PRINTK("[ATBd]:_AT_BT_DISTANCE_DETECTOR_[OFF]\n\r");
		bt_distance_detector_app_deinit();
	} else if (param == 2) {
		bt_distance_detector_send_msg_to_apptask(4); //subtype=4 for clearing all records
	} else
		goto exit;

	return;

exit:
	AT_PRINTK("[ATBd] Start BT DISTANCE DETECTOR: ATBd=1");
	AT_PRINTK("[ATBd] Stop	BT DISTANCE DETECTOR: ATBd=0");
	AT_PRINTK("[ATBd] Clear	all records: ATBd=2");

}
#endif

#if ((defined(CONFIG_BT_MESH_PROVISIONER) && CONFIG_BT_MESH_PROVISIONER) || \
	(defined(CONFIG_BT_MESH_DEVICE) && CONFIG_BT_MESH_DEVICE) || \
	(defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) || \
	(defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) || \
	(defined(CONFIG_EXAMPLE_BT_MESH_DEMO) && CONFIG_EXAMPLE_BT_MESH_DEMO))
extern void app_send_uart_msg(uint8_t data);
extern void bt_mesh_param_user_cmd(unsigned int argc, char **argv);
static void bt_mesh_set_cmd(unsigned int argc, char *argv[])
{
	unsigned int i = 0, j = 0;
	for (i = 0; i < argc; i++) {
		for (j = 0; j < (strlen(argv[i])); j++) {
			app_send_uart_msg(argv[i][j]);
		}
		if ((i + 1) == argc) {
			app_send_uart_msg('\r');
		} else {
			app_send_uart_msg(' ');
		}
	}
}

void fATBM(void *arg)
{
	unsigned int argc = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	}

	if ((argc == 2) && (strcmp(argv[1], "?") == 0)) {
		AT_PRINTK("provision cmd example: ATBM=pro,cmd,parameter \n");
		AT_PRINTK("device cmd example: ATBM=dev,cmd,parameter \n");
		goto exit;
	}

	if (argc < 3) {
		AT_PRINTK("[ATBM]:not enough number of parameter, please use ATBM=? for help \n");
		goto exit;
	}

	if (strcmp(argv[1], "dbg") == 0) {
		if (strcmp(argv[2], "pro") == 0) {
			AT_PRINTK("[ATBM]:DBG Provisioner Cmd \n");
		} else if (strcmp(argv[2], "dev") == 0) {
			AT_PRINTK("[ATBM]:DBG Device Cmd \n");
		} else {
			AT_PRINTK("[ATBM]:It must be dev or pro\n");
			goto exit;
		}
		bt_mesh_set_cmd((argc - 3), &argv[3]);
		return;
	}
#if defined(CONFIG_BT_MESH_USER_API) && CONFIG_BT_MESH_USER_API
#if ((defined(CONFIG_BT_MESH_PROVISIONER) && CONFIG_BT_MESH_PROVISIONER) || \
	(defined(CONFIG_BT_MESH_DEVICE) && CONFIG_BT_MESH_DEVICE) || \
	(defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) || \
	(defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE))
	else if (strcmp(argv[1], "pro") == 0) {
		AT_PRINTK("[ATBM]:Provisioner Cmd \n");
	} else if (strcmp(argv[1], "dev") == 0) {
		AT_PRINTK("[ATBM]:Device Cmd \n");
	} else {
		AT_PRINTK("[ATBM]:It must be dev or pro, please use ATBM=? to help \n");
		goto exit;
	}

	bt_mesh_param_user_cmd((argc - 1), &argv[1]);
#endif
#endif

exit:
	return;
}

extern int bt_mesh_provisioner_app_init(void);
extern void bt_mesh_provisioner_app_deinit(void);
extern int bt_mesh_device_app_init(void);
extern void bt_mesh_device_app_deinit(void);
extern int bt_mesh_device_multiple_profile_app_init(void);
extern int bt_mesh_device_multiple_profile_app_deinit(void);
extern int bt_mesh_provisioner_multiple_profile_app_init(void);
extern int bt_mesh_provisioner_multiple_profile_app_deinit(void);

void fATBm(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	if (!arg) {
		goto exit;
	}

	argc = parse_param(arg, argv);

	if (argc < 2) {
		goto exit;
	}

#if defined(CONFIG_BT_MESH_PROVISIONER) && CONFIG_BT_MESH_PROVISIONER
	if (strcmp(argv[1], "1") == 0) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBm]:_AT_BT_MESH_PROVISIONER_[ON]\n\r");
		if (bt_mesh_provisioner_app_init()) {
			AT_PRINTK("[ATBm]:_AT_BT_MESH_PROVISIONER_[ON] FAIL !!! \n\r");
		} else {
			set_bt_cmd_type(MESH_BIT | STACK_BIT);
		}
	} else if (strcmp(argv[1], "0") == 0) {
		if (!bt_command_type(BT_COMMAND_MESH)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBm]:_AT_BT_MESH_PROVISIONER_[OFF]\n\r");
		bt_mesh_provisioner_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}
#elif defined(CONFIG_BT_MESH_DEVICE) && CONFIG_BT_MESH_DEVICE
	if (strcmp(argv[1], "1") == 0) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBm]:_AT_BT_MESH_DEVICE_[ON]\n\r");
		if (bt_mesh_device_app_init()) {
			AT_PRINTK("[ATBm]:_AT_BT_MESH_DEVICE_[ON] FAIL !!! \n\r");
		} else {
			set_bt_cmd_type(MESH_BIT | STACK_BIT);
		}
	} else if (strcmp(argv[1], "0") == 0) {
		if (!bt_command_type(BT_COMMAND_MESH)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBm]:_AT_BT_MESH_DEVICE_[OFF]\n\r");
		bt_mesh_device_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}
#elif defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE
	if (strcmp(argv[1], "1") == 0) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBm]:_AT_BT_MESH_DEVICE_MULTIPLE_PROFILE_[ON]\n\r");
		if (bt_mesh_device_multiple_profile_app_init()) {
			AT_PRINTK("[ATBm]:_AT_BT_MESH_DEVICE_MULTIPLE_PROFILE_[ON] FAIL !!! \n\r");
		} else {
			set_bt_cmd_type(MESH_BIT | STACK_BIT);
		}
	} else if (strcmp(argv[1], "0") == 0) {
		if (!bt_command_type(BT_COMMAND_MESH)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBm]:_AT_BT_MESH_DEVICE_MULTIPLE_PROFILE_[OFF]\n\r");
		bt_mesh_device_multiple_profile_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}
#elif defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE
	if (strcmp(argv[1], "1") == 0) {
		if (bt_command_type(BT_COMMAND_STACK)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBm]:_AT_BT_MESH_PROVISIONER_MULTIPLE_PROFILE_[ON]\n\r");
		if (bt_mesh_provisioner_multiple_profile_app_init()) {
			AT_PRINTK("[ATBm]:_AT_BT_MESH_PROVISIONER_MULTIPLE_PROFILE_[ON] FAIL !!! \n\r");
		} else {
			set_bt_cmd_type(MESH_BIT | STACK_BIT);
		}
	} else if (strcmp(argv[1], "0") == 0) {
		if (!bt_command_type(BT_COMMAND_MESH)) {
			AT_PRINTK("[AT_PRINTK] ERROR: command type error!\n\r");
			goto exit;
		}
		AT_PRINTK("[ATBm]:_AT_BT_MESH_PROVISIONER_MULTIPLE_PROFILE_[OFF]\n\r");
		bt_mesh_provisioner_multiple_profile_app_deinit();
		set_bt_cmd_type(0);
	} else {
		goto exit;
	}
#endif
	return;
exit:
#if ((defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) || \
	(defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE))
	AT_PRINTK("[ATBm] Start BT Mesh Mulitple Profile: ATBm=1");
	AT_PRINTK("[ATBm] Stop  BT Mesh Mulitple Profile: ATBm=0");
#else
	AT_PRINTK("[ATBm] Start BT Mesh Mulitple Profile: ATBm=1");
	AT_PRINTK("[ATBm] Stop  BT Mesh Mulitple Profile: ATBm=0");
#endif
}
#endif

void fATBV(void *arg)
{
	bool ret;
	T_GAP_DEV_STATE state;
	T_BT_VERSION_INFO bt_version;

	le_get_gap_param(GAP_PARAM_DEV_STATE, &state);
	if (state.gap_init_state != GAP_INIT_STATE_STACK_READY) {
		AT_PRINTK("[ATBV] BT stack version can be got after BT init!\r\n");
		return;
	}

	ret = gap_get_bt_version_info(&bt_version);
	if (ret == false) {
		AT_PRINTK("[ATBV] gap_get_bt_version_info fail!\r\n");
		return;
	}

	AT_PRINTK("[ATBV] hci_version = 0x%x", bt_version.hci_revision);
	AT_PRINTK("[ATBV] lmp_subversion = 0x%x", bt_version.lmp_subversion);
	AT_PRINTK("[ATBV] btgap_revision = %d", bt_version.btgap_revision);
	AT_PRINTK("[ATBV] btgap_buildnum = %d", bt_version.btgap_buildnum);
}

log_item_t at_bt_items[ ] = {
#if ((defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL) || \
	(defined(CONFIG_BT_MESH_CENTRAL) && CONFIG_BT_MESH_CENTRAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
#if defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL
	{"ATBc", fATBc, {NULL, NULL}}, // Start/stop BLE central
#endif
	{"ATBC", fATBC, {NULL, NULL}}, // Create a GATT connection
	{"ATBD", fATBD, {NULL, NULL}}, // Disconnect GATT Connection
	{"ATBG", fATBG, {NULL, NULL}}, // Get peripheral information
	{"ATBI", fATBI, {NULL, NULL}}, // Get information of connected device
	{"ATBS", fATBS, {NULL, NULL}}, // Scan BT device
	{"ATBR", fATBR, {NULL, NULL}}, // GATT client read
	{"ATBW", fATBW, {NULL, NULL}}, // GATT client write
	{"ATBn", fATBn, {NULL, NULL}}, // Modify whitelist
	{"ATBa", fATBa, {NULL, NULL}}, // Modify scan interval/scan window
	{"ATBg", fATBg, {NULL, NULL}}, // Set PHY 2M
#endif
#if ((defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
	{"ATBp", fATBp, {NULL, NULL}}, // Start/stop BLE peripheral
	{"ATBP", fATBP, {NULL, NULL}}, // Legacy ADV concurrent test
#endif
	{"ATBA", fATBA, {NULL, NULL}}, // Modify adv interval
	{"ATBe", fATBe, {NULL, NULL}}, // BLE send indiaction/notification
#endif
#if ((defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL) || \
	(defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_CENTRAL) && CONFIG_BT_MESH_CENTRAL) || \
	(defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
	{"ATBK", fATBK, {NULL, NULL}}, // Reply GAP passkey
	{"ATBY", fATBY, {NULL, NULL}}, // Reply GAP user confirm
	{"ATBU", fATBU, {NULL, NULL}}, // Update connection request
	{"ATBO", fATBO, {NULL, NULL}}, // Get/clear bond information
#endif
#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
	{"ATBf", fATBf, {NULL, NULL}}, // Start/stop BLE scatternet
#endif
#if defined(CONFIG_BT_BEACON) && CONFIG_BT_BEACON
	{"ATBJ", fATBJ, {NULL, NULL}}, // Start/stop BT beacon
#endif
#if defined(CONFIG_BT_CONFIG) && CONFIG_BT_CONFIG
	{"ATBB", fATBB, {NULL, NULL}}, // Start/stop BT config
#endif
#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
	{"ATBb", fATBb, {NULL, NULL}}, // Start/stop BT airsync config
#endif
#if defined(CONFIG_BT_BREEZE) && CONFIG_BT_BREEZE
	{"ATBi", fATBi, {NULL, NULL}}, // BT breeze
#endif
#if defined(CONFIG_BT_TAG_SCANNER) && CONFIG_BT_TAG_SCANNER
	{"ATBt", fATBt, {NULL, NULL}}, // Start/stop BT tag scanner
#endif
#if defined(CONFIG_BT_ANCS) && CONFIG_BT_ANCS
	{"ATBN", fATBN, {NULL, NULL}}, // Start/stop BT ancs
#endif
#if defined(CONFIG_BT_DISTANCE_DETECTOR) && CONFIG_BT_DISTANCE_DETECTOR
	{"ATBd", fATBd, {NULL, NULL}}, // Start/stop BT distance detector
#endif
#if ((defined(CONFIG_BT_MESH_PROVISIONER) && CONFIG_BT_MESH_PROVISIONER) || \
	(defined(CONFIG_BT_MESH_DEVICE) && CONFIG_BT_MESH_DEVICE) || \
	(defined(CONFIG_EXAMPLE_BT_MESH_DEMO) && CONFIG_EXAMPLE_BT_MESH_DEMO) || \
	(defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) || \
	(defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE))
	{"ATBM", fATBM, {NULL, NULL}},
	{"ATBm", fATBm, {NULL, NULL}}, // Start/stop BLE mesh
#endif
	{"ATBV", fATBV, {NULL, NULL}}, // Get BT stack version
};

void at_bt_init(void)
{
	log_service_add_table(at_bt_items, sizeof(at_bt_items) / sizeof(at_bt_items[0]));
}

#if SUPPORT_LOG_SERVICE
log_module_init(at_bt_init);
#endif

#endif
