#include "platform_opts_bt.h"
#if ((defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) || \
	(defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE))
#include "log_service.h"
#include "atcmd_bt.h"
#include <platform/platform_stdlib.h>
#include "gap.h"
#include "gap_adv.h"
#include "gap_bond_le.h"
#include "gap_conn_le.h"
#include "app_msg.h"
#include "app_flags.h"
#include "os_msg.h"
#include "os_sched.h"
#include "os_mem.h"
#include "profile_server.h"

#define BLE_PRINT	printf

#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
extern void *evt_queue_handle;
extern void *io_queue_handle;
#endif

#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
extern void *ble_scatternet_evt_queue_handle;
extern void *ble_scatternet_io_queue_handle;
#endif

#if ((defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
#if defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE
extern T_GAP_DEV_STATE bt_mesh_provisioner_multiple_profile_gap_dev_state;
#elif defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFIL
extern T_GAP_DEV_STATE bt_mesh_device_multiple_profile_gap_dev_state;
#endif
extern uint16_t bt_mesh_peripheral_adv_interval;
#endif

static u8 ctoi(char c)
{
	if((c >= 'A') && (c <= 'F')) {
		return (c - 'A' + 0x0A);
	}

	if((c >= 'a') && (c <= 'f')) {
		return (c - 'a' + 0x0A);
	}

	if((c >= '0') && (c <= '9')) {
		return (c - '0' + 0x00);
	}

	return 0xFF;
}

static int hex_str_to_int(u32 str_len, s8*str)
{
	int result = 0;
	unsigned int n = 2;
	if((str_len < 3) || (str[0] != '0') || ((str[1] != 'x') && (str[1] != 'X'))){
		return -1;
	}
	while(n < str_len){
		result = (result << 4) | (ctoi(str[n++]));
	}
	return result;
}

void ble_peripheral_at_cmd_send_msg(uint16_t sub_type)
{
	uint8_t event = EVENT_IO_TO_APP;

	T_IO_MSG io_msg;

	io_msg.type = IO_MSG_TYPE_QDECODE;
	io_msg.subtype = sub_type;

#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
	if (evt_queue_handle != NULL && io_queue_handle != NULL) {
		if (os_msg_send(io_queue_handle, &io_msg, 0) == false) {
			BLE_PRINT("ble peripheral at cmd send msg fail: subtype 0x%x", io_msg.subtype);
		} else if (os_msg_send(evt_queue_handle, &event, 0) == false) {
			BLE_PRINT("ble peripheral at cmd send event fail: subtype 0x%x", io_msg.subtype);
		}
	}
#endif
#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
	if (ble_scatternet_evt_queue_handle != NULL && ble_scatternet_io_queue_handle != NULL) {
		if (os_msg_send(ble_scatternet_io_queue_handle, &io_msg, 0) == false) {
			BLE_PRINT("ble peripheral at cmd send msg fail: subtype 0x%x", io_msg.subtype);
		} else if (os_msg_send(ble_scatternet_evt_queue_handle, &event, 0) == false) {
			BLE_PRINT("ble peripheral at cmd send event fail: subtype 0x%x", io_msg.subtype);
		}
	}
#endif
}

int ble_peripheral_at_cmd_set_adv_int(int argc, char **argv)
{
	u16 adv_int_max = atoi(argv[1]);
	u16 adv_int_min = atoi(argv[2]);
	T_GAP_DEV_STATE new_state = {0};

#if ((defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
#if defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE
	new_state = bt_mesh_provisioner_multiple_profile_gap_dev_state;
#elif defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFIL
	new_state = bt_mesh_device_multiple_profile_gap_dev_state;
#endif
	if (new_state.gap_init_state) {
		bt_mesh_peripheral_adv_interval = adv_int_min;
		return 0;
	}
#endif

#if ((defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL) || \
	(defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET))
	ble_peripheral_at_cmd_send_msg(0);
	do {
		os_delay(1);
		le_get_gap_param(GAP_PARAM_DEV_STATE , &new_state);
	} while (new_state.gap_adv_state != GAP_ADV_STATE_IDLE);

	le_adv_set_param(GAP_PARAM_ADV_INTERVAL_MAX, sizeof(adv_int_max), &adv_int_max);
	le_adv_set_param(GAP_PARAM_ADV_INTERVAL_MIN, sizeof(adv_int_min), &adv_int_min);

	ble_peripheral_at_cmd_send_msg(1);
	do {
		os_delay(1);
		le_get_gap_param(GAP_PARAM_DEV_STATE , &new_state);
	} while (new_state.gap_adv_state != GAP_ADV_STATE_ADVERTISING);
#endif

	return 0;
}

int ble_peripheral_at_cmd_auth(int argc, char **argv)
{
	u8 conn_id;
	u32 passcode;
	T_GAP_CFM_CAUSE confirm;
	int ret;

	if(strcmp(argv[1],"SEND") == 0) {
		if(argc != 3){
			BLE_PRINT("ERROR:input parameter error!\n\r");
			return -1;
		}
		conn_id = atoi(argv[2]);
		le_bond_pair(conn_id);
	}else if(strcmp(argv[1], "KEY") == 0){
		if(argc !=4){
			BLE_PRINT("ERROR:input parameter error!\n\r");
			return -1;
		}
		conn_id = atoi(argv[2]);
		if(strlen(argv[3]) > 6){
			confirm = GAP_CFM_CAUSE_REJECT;
		}else{
			confirm = GAP_CFM_CAUSE_ACCEPT;
		}
		s8* str = (s8 *)argv[3];
		for(unsigned int i = 0; i < strlen(argv[3]); i ++){
			if((str[i ++] < '0') || (str[i ++] > '9')){
				BLE_PRINT("ERROR:input parameter error!\n\r");
				return -1;
				}
		}
		//passcode = dec_str_to_int(strlen(argv[3]), argv[3]);
		passcode = atoi(argv[3]);
		if (passcode > GAP_PASSCODE_MAX)
		{
			BLE_PRINT("ERROR:passcode is out of range[0-999999] !\n\r");
			confirm = GAP_CFM_CAUSE_REJECT;
		}
		le_bond_passkey_input_confirm(conn_id, passcode, confirm);
	}else if(strcmp(argv[1], "MODE") == 0){
		u8	auth_pair_mode = GAP_PAIRING_MODE_PAIRABLE;
		u16 auth_flags = GAP_AUTHEN_BIT_BONDING_FLAG;
		u8	auth_io_cap = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
#if F_BT_LE_SMP_OOB_SUPPORT
		u8	oob_enable = false;
#endif
		u8	auth_sec_req_enable = false;
		u16 auth_sec_req_flags = GAP_AUTHEN_BIT_BONDING_FLAG;

		if (argc >= 3) {
			auth_flags = hex_str_to_int(strlen(argv[2]), ( s8 *)argv[2]);
			auth_sec_req_flags =  auth_flags;
		}
		if (argc >= 4) {
			auth_io_cap = atoi(argv[3]);
		}
		if (argc >= 5) {
			auth_sec_req_enable = atoi(argv[4]);
		}
#if F_BT_LE_SMP_OOB_SUPPORT
//		if (argc >= 6) {
//			oob_enable = atoi(argv[5]);
//		}
#endif

		gap_set_param(GAP_PARAM_BOND_PAIRING_MODE, sizeof(auth_pair_mode), &auth_pair_mode);
		gap_set_param(GAP_PARAM_BOND_AUTHEN_REQUIREMENTS_FLAGS, sizeof(auth_flags), &auth_flags);
		gap_set_param(GAP_PARAM_BOND_IO_CAPABILITIES, sizeof(auth_io_cap), &auth_io_cap);
#if F_BT_LE_SMP_OOB_SUPPORT
		gap_set_param(GAP_PARAM_BOND_OOB_ENABLED, sizeof(uint8_t), &oob_enable);
#endif
		le_bond_set_param(GAP_PARAM_BOND_SEC_REQ_ENABLE, sizeof(auth_sec_req_enable), &auth_sec_req_enable);
		le_bond_set_param(GAP_PARAM_BOND_SEC_REQ_REQUIREMENT, sizeof(auth_sec_req_flags),
					  &auth_sec_req_flags);
		ret = gap_set_pairable_mode();

		if(ret == GAP_CAUSE_SUCCESS)
			BLE_PRINT("\n\rSet pairable mode success!\r\n");
		else
			BLE_PRINT("\n\rSet pairable mode fail!\r\n");
	}else{
		BLE_PRINT("ERROR:input parameter error!\n\r");
		return -1;
	}

	return ret;
}

int ble_peripheral_at_cmd_send_userconf(int argc, char **argv)
{
	(void) argc;
	u8 conn_id;
	u8 conf;
	int ret;
	T_GAP_CFM_CAUSE confirm;

	conn_id = atoi(argv[1]);
	conf = atoi(argv[2]);
	if (conf == 0){
		confirm = GAP_CFM_CAUSE_REJECT;
	}else{
		confirm = GAP_CFM_CAUSE_ACCEPT;
	}

	ret = le_bond_user_confirm(conn_id, confirm);
	return ret;
}

int ble_peripheral_at_cmd_update_conn_request(int argc, char **argv)
{
	(void) argc;
	int ret;
	u8 conn_id = atoi(argv[1]);
	u16 conn_interval_min = hex_str_to_int(strlen(argv[2]),(s8 *) argv[2]);
	u16 conn_interval_max = hex_str_to_int(strlen(argv[3]), (s8 *)argv[3]);
	u16 conn_latency = hex_str_to_int(strlen(argv[4]), (s8 *)argv[4]);
	u16 supervision_timeout = hex_str_to_int(strlen(argv[5]), (s8 *)argv[5]);

	ret = le_update_conn_param(conn_id,
							   conn_interval_min,
							   conn_interval_max,
							   conn_latency,
							   supervision_timeout,
							   2 * (conn_interval_min - 1),
							   2 * (conn_interval_max - 1));
	return ret;

}

int ble_peripheral_at_cmd_bond_information(int argc, char **argv)
{
	(void) argc;
	//int ret = 0;
	if(strcmp(argv[1],"CLEAR") == 0) {
		le_bond_clear_all_keys();
	}else if(strcmp(argv[1], "INFO") == 0){
		u8 i;
		T_LE_KEY_ENTRY *p_entry;
		for (i = 0; i < bond_storage_num; i++) {
			p_entry = le_find_key_entry_by_idx(i);
			if (p_entry != NULL) {
			BLE_PRINT("bond_dev[%d]: bd 0x%02x%02x%02x%02x%02x%02x, addr_type %d, flags 0x%x\r\n",
							p_entry->idx,
							p_entry->remote_bd.addr[5],
							p_entry->remote_bd.addr[4],
							p_entry->remote_bd.addr[3],
							p_entry->remote_bd.addr[2],
							p_entry->remote_bd.addr[1],
							p_entry->remote_bd.addr[0],
							p_entry->remote_bd.remote_bd_type,
							p_entry->flags);
			}
		}
	}else{
		return -1;
	}

	return 0;
}

int ble_peripheral_send_indi_notification(int argc, char **argv)
{
	(void) argc;

	u8 conn_id = atoi(argv[1]);
	u8 service_id = atoi(argv[2]);
	u16 attrib_index = hex_str_to_int(strlen(argv[3]), (s8 *) argv[3]);
	u8 type = atoi(argv[4]);
	int length = hex_str_to_int(strlen(argv[5]), (s8 *) argv[5]);

	if(length == -1){
		printf("\n\rError:value length should be hexadecimal and start with '0X' or '0x'\r\n");
		return -1;
	}
	u8 *data = (u8 *)os_mem_alloc(0,length * sizeof(u8));

	for(u8 i = 0; i < length; ++ i){
		data[i] = hex_str_to_int(strlen(argv[i + 6]), (s8 *)argv[i + 6]);
	}

	server_send_data(conn_id, service_id, attrib_index, data,length, (T_GATT_PDU_TYPE)type);
	
	if(data != NULL)
		os_mem_free(data);

	return 0;
}

int ble_peripheral_app_handle_at_cmd(uint16_t subtype, void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	}

	switch (subtype) {
		case BT_ATCMD_AUTH:
			ble_peripheral_at_cmd_auth(argc, argv);
			break;
		case BT_ATCMD_SEND_USERCONF:
			ble_peripheral_at_cmd_send_userconf(argc, argv);
			break;
		case BT_ATCMD_UPDATE_CONN_REQUEST:
			ble_peripheral_at_cmd_update_conn_request(argc, argv);
			break;
		case BT_ATCMD_BOND_INFORMATION:
			ble_peripheral_at_cmd_bond_information(argc, argv);
			break;
		case BT_ATCMD_SEND_INDI_NOTI:
			ble_peripheral_send_indi_notification(argc, argv);
			break;
		default:
			break;
	}

	return 0;
}
#endif
