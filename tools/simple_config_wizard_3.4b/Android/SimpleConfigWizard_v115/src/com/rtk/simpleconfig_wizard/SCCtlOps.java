package com.rtk.simpleconfig_wizard;

import java.io.UnsupportedEncodingException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Random;

import android.net.wifi.ScanResult;
import android.util.Log;

public class SCCtlOps {
	private static final String TAG = "SCCtlOps";

	public static boolean IsOpenNetwork = false; // Default has password, not open network
	public static String  ConnectedSSID;         // Connected WIFI's SSID
	public static String  ConnectedPasswd;       // Connected WIFI's Password
	public static String  StoredPasswd;
	
	public static boolean isHiddenSSID;
	public static boolean addNewNetwork;
	public static ScanResult reBuiltScanResult;

	public static final int MAX_CLIENTS_NUM = 32;
	public static boolean DiscoveredNew;
	public static boolean SetAble = true;

	/** For UDP Data Receive */
//	public static byte[]     	 RecvBuf = new byte[512];

	/** UDP Payload Format Flag */
	public static class Flag{

		private Flag(){
		}

		/** Flag */
		public static final int Version = (0x00<<6); // 2 bits
		public static final int RequestFlag = (0<<5); // 1 bit
		public static final int ResponseFlag = (1<<5);
		/** Request */
		public static final int Discover = 0x00;  	// 5 bits
		public static final int SaveProf = 0x01;
		public static final int DelProf = 0x02;
		public static final int RenameDev = 0x03;
		public static final int ReturnACK = 0x04;
		/** Response */
		public static final int CfgSuccessACK = 0x00;  // 5 bits
		public static final int DiscoverACK = 0x01;
		public static final int SaveProfACK = 0x02;
		public static final int DelProfACK = 0x03;
		public static final int RenameDevACK = 0x04;
		public static final int CfgSuccessACKSendBack = 0x05;
	}

	/** UDP Payload Format ACK to Scan */
	public static class ScanACK{

		private ScanACK(){
		}

		/** MAC */
		public static int				MaxDevNum = 0;
		public static byte[][] 			Mac = new byte[MAX_CLIENTS_NUM][6]; // Record the connected STA
		/** Status */
		public static byte[] 			Status = new byte[MAX_CLIENTS_NUM];
		/** Device Type */
		public static byte[][] 			Type = new byte[MAX_CLIENTS_NUM][2];
		/** Device IP */
		public static byte[][] 			IPBuf = new byte[MAX_CLIENTS_NUM][4];
		public static String[]			IP = new String[MAX_CLIENTS_NUM];
		/** Device Name */
		public static byte[][] 			NameBuf = new byte[MAX_CLIENTS_NUM][64];
		public static String[]			Name = new String[MAX_CLIENTS_NUM];
	}

	public static byte[] rtk_sc_gen_digest(byte[] inputData)
	{
		try {
			return AESCrypt.MD5(inputData);
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}

	public static void rtk_sc_control_reset()
	{
		ScanACK.MaxDevNum = 0;
		Arrays.fill(ScanACK.Status, (byte)0);
		for(int i=0; i<MAX_CLIENTS_NUM; i++) {
			Arrays.fill(ScanACK.Mac[i], (byte)0);
			Arrays.fill(ScanACK.Type[i], (byte)0);
			Arrays.fill(ScanACK.IPBuf[i], (byte)0);
			Arrays.fill(ScanACK.NameBuf[i], (byte)0);
		}
		ScanACK.IP = new String[MAX_CLIENTS_NUM];
		ScanACK.Name = new String[MAX_CLIENTS_NUM];
	}

	public static byte[] rtk_sc_gen_discover_packet(String defaultPIN)
	{
		byte[] CmdBuf = new byte[92];
		short PayloadLen = 0;

		Arrays.fill(CmdBuf, (byte)0);
		/** Flag */
		CmdBuf[0] += Flag.Version;
		CmdBuf[0] += Flag.RequestFlag;
		CmdBuf[0] += Flag.Discover;

		/** Encrypt Flag */
		CmdBuf[3] = 0x01;
    	PayloadLen += 1;

		/** Nonce */
    	if(CmdBuf[3] == 0x01) {
    		for(int i=0; i<64; i++) {
        		Random r = new Random();
        		CmdBuf[4+i] = (byte) (r.nextInt(256) + 1);
    		}
    	}
    	PayloadLen += 64;

		/** Default PIN Digest */
    	byte[] inputData = new byte[64 + defaultPIN.length()];
    	System.arraycopy(CmdBuf, 4, inputData, 0, 64);
    	System.arraycopy(defaultPIN.getBytes(), 0, inputData, 64, defaultPIN.length());
    	byte[] digest = rtk_sc_gen_digest(inputData);
    	System.arraycopy(digest, 0, CmdBuf, PayloadLen+3, 16);
    	PayloadLen += 16;

		/** MAC Address */
    	PayloadLen += 6;

		/** Device Type */
    	PayloadLen += 2;

		/** Length */
    	byte[] buf = new byte[2];
    	buf[0] = (byte)((PayloadLen >> 8) & 0xff);
    	buf[1] = (byte)(PayloadLen & 0xff);
    	System.arraycopy(buf, 0, CmdBuf, 1, 2);

		/*String dbgStr = new String();
		for(int i=0; i<92; i++)
			dbgStr += String.format("%02x ", CmdBuf[i]);
		Log.d(TAG, "Client Discover Packet: " + dbgStr);*/

		return CmdBuf;
	}

	public static byte[] rtk_sc_gen_control_packet(int flag, String defaultPIN, String inputPIN, String nameStr)
	{
		byte[] CmdBuf;
		short PayloadLen = 0;
		byte[] digest;
		byte[] inputData;
		byte[] nameBuf = null;

    	if(flag == Flag.RenameDev) {
//			Log.d(TAG, "nameStr: " + nameStr);
    		try {
    			nameBuf = nameStr.getBytes("UTF-8");
			} catch (UnsupportedEncodingException e) {
				Log.e(TAG, "Get name bytes error");
				e.printStackTrace();
				return null;
			}
			CmdBuf = new byte[100+nameBuf.length];
    	} else {
    		CmdBuf = new byte[100];
    	}

		Arrays.fill(CmdBuf, (byte)0);
		/** Flag */
		CmdBuf[0] += Flag.Version;
		CmdBuf[0] += Flag.RequestFlag;
		CmdBuf[0] += flag;

		/** Encrypt Flag */
		CmdBuf[3] = 0x01;
    	PayloadLen += 1;

		/** Nonce */
    	if(CmdBuf[3] == 0x01) {
    		for(int i=0; i<64; i++) {
        		Random r = new Random();
        		CmdBuf[4+i] = (byte) (r.nextInt(256) + 1);
    		}
    	}
    	PayloadLen += 64;

		/** Default PIN Digest */
//		Log.d(TAG, "defaultPIN: " + defaultPIN);
    	inputData = new byte[64 + defaultPIN.length()];
    	System.arraycopy(CmdBuf, 4, inputData, 0, 64);
    	System.arraycopy(defaultPIN.getBytes(), 0, inputData, 64, defaultPIN.length());
    	digest = rtk_sc_gen_digest(inputData);
    	System.arraycopy(digest, 0, CmdBuf, PayloadLen+3, 16);
    	PayloadLen += 16;

		/** User Input PIN Digest */
//		Log.d(TAG, "inputPIN: " + inputPIN);
    	inputData = new byte[64 + inputPIN.length()];
    	System.arraycopy(CmdBuf, 4, inputData, 0, 64);
    	System.arraycopy(inputPIN.getBytes(), 0, inputData, 64, inputPIN.length());
    	digest = rtk_sc_gen_digest(inputData);
    	System.arraycopy(digest, 0, CmdBuf, PayloadLen+3, 16);
    	PayloadLen += 16;

		/** Device Name */
    	if(flag == Flag.RenameDev) {
//    		String tmp = new String();
//    	    for(int i=0; i<nameBuf.length; i++) {
//    	    	tmp += String.format("%02x ", nameBuf[i]);
//    	    }
//			Log.d(TAG, "nameBuf: " + tmp);

        	System.arraycopy(nameBuf, 0, CmdBuf, PayloadLen+3, nameBuf.length);
        	PayloadLen += nameBuf.length;
    	}

		/** Length */
    	byte[] buf = new byte[2];
    	buf[0] = (byte)((PayloadLen >> 8) & 0xff);
    	buf[1] = (byte)(PayloadLen & 0xff);
    	System.arraycopy(buf, 0, CmdBuf, 1, 2);

		return CmdBuf;
	}

	public static byte[] rtk_sc_gen_control_confirm_packet(int flag, String defaultPIN, String inputPIN)
	{
		byte[] CmdBuf;
		short PayloadLen = 0;
		byte[] digest;
		byte[] inputData;

    	CmdBuf = new byte[101];
		Arrays.fill(CmdBuf, (byte)0);
		/** Flag */
		CmdBuf[0] += Flag.Version;
		CmdBuf[0] += Flag.RequestFlag;
		CmdBuf[0] += Flag.ReturnACK;

		/** Encrypt Flag */
		CmdBuf[3] = 0x01;
    	PayloadLen += 1;

		/** Nonce */
    	if(CmdBuf[3] == 0x01) {
    		for(int i=0; i<64; i++) {
        		Random r = new Random();
        		CmdBuf[4+i] = (byte) (r.nextInt(256) + 1);
    		}
    	}
    	PayloadLen += 64;

		/** Default PIN Digest */
//		Log.d(TAG, "defaultPIN: " + defaultPIN);
    	inputData = new byte[64 + defaultPIN.length()];
    	System.arraycopy(CmdBuf, 4, inputData, 0, 64);
    	System.arraycopy(defaultPIN.getBytes(), 0, inputData, 64, defaultPIN.length());
    	digest = rtk_sc_gen_digest(inputData);
    	System.arraycopy(digest, 0, CmdBuf, PayloadLen+3, 16);
    	PayloadLen += 16;

		/** User Input PIN Digest */
//		Log.d(TAG, "inputPIN: " + inputPIN);
    	inputData = new byte[64 + inputPIN.length()];
    	System.arraycopy(CmdBuf, 4, inputData, 0, 64);
    	System.arraycopy(inputPIN.getBytes(), 0, inputData, 64, inputPIN.length());
    	digest = rtk_sc_gen_digest(inputData);
    	System.arraycopy(digest, 0, CmdBuf, PayloadLen+3, 16);
    	PayloadLen += 16;

		/** Encrypt Flag */
		CmdBuf[PayloadLen+3] += flag;
    	PayloadLen += 1;

		/** Length */
    	byte[] buf = new byte[2];
    	buf[0] = (byte)((PayloadLen >> 8) & 0xff);
    	buf[1] = (byte)(PayloadLen & 0xff);
    	System.arraycopy(buf, 0, CmdBuf, 1, 2);

		return CmdBuf;
	}


	public static int handle_discover_ack(byte[] recv_buf)
	{
		int length, equalCnt=0;
		String dbgStr;

		if(SetAble==false)
			return -1;

		DiscoveredNew = false;
//		System.arraycopy(recv_buf, 0, RecvBuf, 0, recv_buf.length);

		length = (recv_buf[1]<<8)&0xFF00 | (recv_buf[2])&0xFF;
//		Log.d(TAG, String.format("length: 0x%02x", length));
		if(length < 6) {
			Log.e(TAG, "At least a mac\n");
			return -1;
		}

		if(ScanACK.MaxDevNum > MAX_CLIENTS_NUM) {
			Log.e(TAG, "The receive buf is full\n");
			return -1;
		}

		/** Judge if it is the same MAC */
//		Log.d(TAG, "Max Device Number: " + ScanACK.MaxDevNum);
		if(ScanACK.MaxDevNum > 0) {/* Not the first time */
			for(int j=0; j<ScanACK.MaxDevNum; j++) {
				for(int i=0; i<6; i++) {
					if(recv_buf[3+i] == ScanACK.Mac[j][i])
						equalCnt++;
				}
				if(equalCnt == 6)
					return -1; //find the same MAC
				equalCnt = 0; //for the second judge(if has)
			}
		}

		/** Not the same MAC */
		System.arraycopy(recv_buf, 3, ScanACK.Mac[ScanACK.MaxDevNum], 0, 6);
		dbgStr = new String();
		for(int i=0; i<6; i++) {
			dbgStr += String.format("%02x", ScanACK.Mac[ScanACK.MaxDevNum][i]);
			if(i<5)
				dbgStr += ":";
		}
		Log.i(TAG, "Discovered MAC: " + dbgStr);

		/** Status */
		if(length > 7) {
			ScanACK.Status[ScanACK.MaxDevNum] = recv_buf[9];
//			Log.d(TAG, String.format("Status: %02x", ScanACK.Status[ScanACK.MaxDevNum]));
		}

		/** Device Type */
		if(length > 9) {
			System.arraycopy(recv_buf, 10, ScanACK.Type[ScanACK.MaxDevNum], 0, 2);
//			Log.d(TAG, String.format("Device Type: %02x %02x", ScanACK.DevType[ScanACK.MaxDevNum][0],
//					ScanACK.DevType[ScanACK.MaxDevNum][1]));
		}

		/** Device IP */
		if(length > 13) {
			System.arraycopy(recv_buf, 12, ScanACK.IPBuf[ScanACK.MaxDevNum], 0, 4);
			ScanACK.IP[ScanACK.MaxDevNum] = String.format("%d.%d.%d.%d",
					ScanACK.IPBuf[ScanACK.MaxDevNum][0]&0xff,
					ScanACK.IPBuf[ScanACK.MaxDevNum][1]&0xff,
					ScanACK.IPBuf[ScanACK.MaxDevNum][2]&0xff,
					ScanACK.IPBuf[ScanACK.MaxDevNum][3]&0xff);
			Log.i(TAG, "Device IP: " + ScanACK.IP[ScanACK.MaxDevNum]);
		}

		/** Device Name */
		if(length > 14) {
			System.arraycopy(recv_buf, 16, ScanACK.NameBuf[ScanACK.MaxDevNum], 0, 64);
			String name = null;
			try {
				name = new String(ScanACK.NameBuf[ScanACK.MaxDevNum], "UTF-8").trim();
			} catch (UnsupportedEncodingException e) {
				Log.e(TAG, "Get device name error");
				e.printStackTrace();
			}
			if(name.length()>0)
				ScanACK.Name[ScanACK.MaxDevNum] = name;
			else
				ScanACK.Name[ScanACK.MaxDevNum] = null;
			Log.i(TAG, "Device Name: " + ScanACK.Name[ScanACK.MaxDevNum]);
		}

		ScanACK.MaxDevNum++;
		DiscoveredNew = true;

		return 0;
	}

	public static int rtk_sc_get_discovered_dev_num()
	{
		return ScanACK.MaxDevNum;
	}

//	public static void rtk_get_connected_dev_test1()
//	{
//		/** For test */
//		byte[] tmp = {0x21,
//				00,0x2c,
//				00,0x18,(byte)0x95,0x61,(byte)0x89,0x75,
//				0x01,
//				00,0x01,
//				(byte)0xc0,(byte)0xa8,0x01,(byte)0xdd,00,
//				(byte)0xe7,(byte)0xa9,(byte)0xba,(byte)0xe8,(byte)0xb0,
//				(byte)0x83,00,00,00,00,
//				00,00,00,00,00,
//				00,00,00,00,00,
//				00,00,00,00,00,
//				00,00};
//		System.arraycopy(tmp, 0, RecvBuf, 0, tmp.length);
//		handle_discover_ack();
//	}
//
//	public static void rtk_get_connected_dev_test2()
//	{
//		byte[] tmp = {0x21,
//				00,0x2c,
//				00,0x44,0x46,0x66,0x66,0x76,
//				0x02,
//				00,0x02,
//				(byte)0xc0,(byte)0xa8,0x01,(byte)0xde,00,
//				0x54,0x56,00,00,00,
//				00,00,00,00,00,
//				00,00,00,00,00,
//				00,00,00,00,00,
//				00,00,00,00,00,
//				00,00};
//		System.arraycopy(tmp, 0, RecvBuf, 0, tmp.length);
//		handle_discover_ack();
//	}

	public static int rtk_sc_get_discovered_dev_info(List<HashMap<String, Object>> DevInfo)
	{
		int i;
		String buf;
		HashMap<String, Object> hmap;

		SetAble = false;
//		Log.d(TAG, "ScanACK.MaxDevNum: " + ScanACK.MaxDevNum);
		for(int index=0; index<ScanACK.MaxDevNum; index++) {
			buf = new String();
			hmap = new HashMap<String, Object>();
			for(i=0; i<6; i++) {
				buf += String.format("%02x", ScanACK.Mac[index][i]);
				if(i<5)
					buf += ":";
			}
//			Log.d(TAG, "Mac: " + buf);
			hmap.put("MAC", buf);

			buf = new String();
			switch(ScanACK.Status[index]) {
            case 0x01:
            	buf = "Connected";
				break;
            case 0x02:
            	buf = "Profile saved";
				break;
			default:
            	buf = "Unkown status";
				break;
			}
//			Log.d(TAG, "Status: " + buf);
			hmap.put("Status", buf);

			buf = new String();
			short type =  (short)((ScanACK.Type[index][0]&0xff<<8) + (ScanACK.Type[index][1]&0xff) );
			switch(type) {
            case 0x0000:
            	buf = "Any type";
				break;
            case 0x0001:
            	buf = "TV";
				break;
            case 0x0002:
            	buf = "Air conditioner";
				break;
			default:
            	buf = "Unkown type";
				break;
			}
//			Log.d(TAG, "DevType: " + buf);
			hmap.put("Type", buf);

//			Log.d(TAG, "IP: " + ScanACK.DevIP[index]);
			hmap.put("IP", ScanACK.IP[index]);

//			Log.d(TAG, "Name: " + ScanACK.DevName[index]);
			hmap.put("Name", ScanACK.Name[index]);

			DevInfo.add(hmap);
		}

		SetAble = true;

		return 0;
	}
}
