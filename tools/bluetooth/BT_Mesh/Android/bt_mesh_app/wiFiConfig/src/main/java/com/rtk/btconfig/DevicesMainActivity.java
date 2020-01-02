package com.rtk.btconfig;

import android.annotation.SuppressLint;
import android.app.ActionBar;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.location.LocationManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.Process;
import android.os.StrictMode;
import android.preference.PreferenceManager;
import android.support.design.widget.BottomNavigationView;
import android.text.InputType;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.PopupWindow;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.rtk.btconfig.ConfigurationDevice.DeviceInfo;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Type;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.HttpURLConnection;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.MalformedURLException;
import java.net.NetworkInterface;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.URI;
import java.net.URL;
import java.net.URLEncoder;
import java.net.UnknownHostException;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.ConcurrentModificationException;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import static java.lang.Integer.min;
import static java.lang.Integer.valueOf;


public class DevicesMainActivity extends BaseActivity {


	final String[] CtrlListStr = {"Rename","Remove Device","Connect to other AP"};

	public static final String EXTRA_MESSAGE = "com.realtek.amebacam.MESSAGE";

	private static final String pinfileName = "prePINFile";
	private static final String TAG = "DevicesMainActivity";


	private static final int discoveryTimeout = 3000; // 3s
	private static final int deviceNumber = 32;
	private static final int APNumber = 100;

	private static final int BROADCAST_RECV_SOCKET_PORT = 49151;
	private static final int BROADCAST_SEND_SOCKET_PORT = 49152;
	private static final int CONTROL_LED_SOCKET_PORT = 8080;


	private DatagramSocket ds,rs = null;
	private int CurrentItem;
	private String CurrentControlIP;
	private static boolean noPD = true;
	private ServerSocket serverSocket;
	private Socket LEDControlSocket;
	private BufferedWriter LEDControlBW;
	private String gMsg;


	private BottomNavigationView mNavigationView = null;
	private ListView deviceGroupingListView = null;

	ImageButton btn_setting;
	ImageButton btn_scan;
	TextView textConfigDeviceTitle;
	ListView listView;
	EditText edittxt_PINcode;
	View wifiPW_EntryView;
	LayoutInflater factory;
	LinearLayout parentLayout_bt_list_view;
	ListView mBTScanListView;
	ListView popup_bt_listview;
	LinearLayout layout_linear;
	PopupWindow window;
	Button popup_submit;
	Button popup_cancel;

	String pinCodeText = "";
	String data_exchange_IP = "";


	boolean DiscovEnable = false;
	boolean isDeletedDevice = false;
	boolean isControlSingleDevice = false;
	boolean TimesupFlag_rename = false;
	boolean is_getIP_finish = false;
	boolean isScanFinish = false;

	private String PINGet = null;
	private String PINSet = null;
	private SimpleAdapter adapter_deviceInfo;
	private ProgressDialog pd;

	public static List<HashMap<String, Object>> BroadcastDevInfo = null;
	private List<HashMap<String, Object>> DevInfo;

	protected WifiManager mWifiManager;
	private HashMap<String, Object> tmpMap = null;


	DeviceInfo[] configuredDevices;
	DeviceInfo[] APInfo;
	DeviceInfo SelectedAPInfo;

	public static Context context = null;

	int mPosition;
	ViewGroup mParent;
	EditText pop_groupname_edittext;
	public static final String DB_BROADCAST_DEVICES_TAG = "DB_BROADCAST_DEVICES";
	public static final String DB_GROUP_NAME_TAG = "DB_GROUP_NAME";
	public static final String DB_GROUP_DEVICES_TAG = "DB_GROUP_DEVICES";
	public static final String DB_GROUP_NAMEADDR_MAP_TAG = "DB_GROUP_NAMEADDR";


	public static List<String> bt_group_name;
	public static List<HashMap<String, String>> bt_group_devices_map;
	public static List<String> setting_menu;

	public static List<HashMap<String, String>> group_name_addr_map;
	String curUUID = null;
	String http_response = null;
	public static String currProvisionerIP =null;
	static BTListBaseAdapter popDeviceListAdapter;

	private final Lock _mutex = new ReentrantLock(true);
	Thread refreshDeviceStateThread = null;
	private int currItemID;
	Boolean isTimeToJoin = false;
	Thread httpQueryThread;

	Handler handler_pd = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			// Log.d(TAG,"handleMessage msg.what: " + String.valueOf(msg.what));
			switch (msg.what) {
			case 0:
				if(pd.isShowing()){
					pd.dismiss();
				}
				break;
			case 1:
				int timeout = 10;
				int coutDown = timeout;

				while (coutDown > 0) {

					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					coutDown--;
					if (coutDown == 0) {
						pd.dismiss();
					}
				}

				break;
				case 2:
					if(pd != null) {
						if (pd.isShowing()) {
							pd.dismiss();
						}
					}
					show_discoverDevice();
					break;
				case 3:
					show_discoverDevice();
					break;
				case 4:
					AlertDialog.Builder builder = new AlertDialog.Builder(DevicesMainActivity.this);
					builder.setTitle("Warning");
					builder.setMessage(gMsg);
					builder.setCancelable(true);
					final AlertDialog dlg = builder.create();
					dlg.show();
					final Timer t = new Timer();
					t.schedule(new TimerTask() {
						public void run() {
							dlg.dismiss();
							t.cancel();
							return;
						}
					}, 3000);
					break;
			default:
				break;
			}
		}
	};


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		if (android.os.Build.VERSION.SDK_INT > 9) {
			StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
			StrictMode.setThreadPolicy(policy);
		}

//
//		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
//				WindowManager.LayoutParams.FLAG_FULLSCREEN);

		initData();
		initComponent();
		initComponentAction();

		mWifiManager = (WifiManager) getApplicationContext().getSystemService(WIFI_SERVICE);

	}

	protected void onStart() {
		super.onStart();

		if(context==null)
			context = getApplicationContext();
	}

	@Override
	public void onPause() {

		Log.e(TAG,"onPause");
		isTimeToJoin = true;

		try{
			Log.e(TAG,"onPause isTimeToJoin");


			refreshDeviceStateThread.interrupt();
			refreshDeviceStateThread.join();
		}catch (InterruptedException e){e.printStackTrace();}
        Log.e(TAG,"onPause after join");
		SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(context);//this.getPreferences(MODE_PRIVATE);
		SharedPreferences.Editor editor = pref.edit();

		Gson gson = new Gson();
		String  group_name_addr_map_str =  gson.toJson(group_name_addr_map);
		String BDevInfoStr = gson.toJson(BroadcastDevInfo);
		String bt_group_devices_map_str = gson.toJson(bt_group_devices_map);
		editor.putString(DB_BROADCAST_DEVICES_TAG,BDevInfoStr);
		editor.putString(DB_GROUP_NAMEADDR_MAP_TAG, group_name_addr_map_str);
		editor.putString(DB_GROUP_DEVICES_TAG,bt_group_devices_map_str);
		Log.e(TAG,"onPause BroadcastDevInfo "+ BDevInfoStr);
		Log.e(DB_GROUP_NAMEADDR_MAP_TAG,"onPause group_name_addr_map_str "+ group_name_addr_map_str);
		Log.e(DB_GROUP_DEVICES_TAG ,"bt_group_devices_map " + bt_group_devices_map.toString());
		Log.e(DB_GROUP_NAME_TAG , "onPause " +bt_group_name.toString().substring(1,+bt_group_name.toString().length()-1) + " size " +bt_group_name.size() );
		if(bt_group_name.size() > 0)
			editor.putString(DB_GROUP_NAME_TAG, bt_group_name.toString().substring(1,+bt_group_name.toString().length()-1));
		editor.commit();

		super.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		Log.e(TAG,"onResume");
        refreshDeviceStateThread = new Thread(new Runnable() {
            public void run() {

					String HTTPQueryResult;
							while(isTimeToJoin == false) {

                                    try {
                                        Log.e(TAG, "refreshDeviceStateThread "+currProvisionerIP);
                                        refreshDeviceStateThread.sleep(2000);
                                        if(currProvisionerIP != null ) {
											ConnectMESHDevice(currProvisionerIP, "bt_mesh=01020008", false);
//											Log.e(TAG, "refreshDeviceStateThread get unprovisied ");
                                            refreshDeviceStateThread.sleep(2000);
                                            Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
                                            HashMap<String, Object> refreshObject = null;
//                                            Log.e(TAG, "refreshDeviceStateThread BroadcastDevInfo " + BroadcastDevInfo.toString() + " isInterrupted " + (refreshDeviceStateThread.isInterrupted()));
                                            try {
												for (; it.hasNext(); ) {
													refreshObject = it.next();
													if (refreshObject.get("MESH_ADDR") == null)
														continue;
													if (refreshObject.get("MESH_ADDR").toString().isEmpty() == false) {
														HTTPQueryResult = HTTPQuery(currProvisionerIP, "bt_mesh=01050008");
														if (HTTPQueryResult != null)
															HTTPQueryResultParse(HTTPQueryResult);
														if (popDeviceListAdapter != null)
															popDeviceListAdapter.init();
														handler_pd.sendEmptyMessage(3);
													}
//													Log.e(TAG, refreshObject.get("Name").toString() + "  MESH_ADDR " + refreshObject.get("MESH_ADDR").toString());
												}
											}catch (ConcurrentModificationException e){e.printStackTrace();}
                                        }

                                    } catch (InterruptedException e) {
                                        Log.e(TAG, "refreshDeviceStateThread  InterruptedException!!");
                                        break;
                                    }
                             }

				isTimeToJoin = false;
							Log.e(TAG,"refreshDeviceStateThread finish");
            }
        });
        refreshDeviceStateThread.start();
	}

	@Override
	protected void onStop() {
		super.onStop();

		Log.e(TAG,"onStop");
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		if (ds != null) {
			ds.close();
		}
		if (rs != null) {
			rs.close();
		}
		DiscovEnable = false;
	}


//
//	//Handling callback
//	@Override
//	public void onRequestPermissionsResult(int requestCode,
//                                           String permissions[], int[] grantResults) {
//		switch (requestCode) {
//			case 1: {
//				if (grantResults.length > 0
//						&& grantResults[0] == PackageManager.PERMISSION_GRANTED) {
//
//
//				} else {
//					Toast.makeText(this, "Permissions Denied to use MIC", Toast.LENGTH_LONG).show();
//				}
//				return;
//			}
//		}
//	}


	private void initData() {
		configuredDevices = new DeviceInfo[deviceNumber];
		for (int i = 0; i < deviceNumber; i++) {
			configuredDevices[i] = new DeviceInfo();
			configuredDevices[i].setaliveFlag(1);
			configuredDevices[i].setName("");
			configuredDevices[i].setIP("");
			configuredDevices[i].setmacAdrress("");
			configuredDevices[i].setimg(null);
			configuredDevices[i].setconnectedflag(false);
		}

		APInfo = new DeviceInfo[APNumber];
		for (int i = 0; i < APNumber; i++) {
			APInfo[i] = new DeviceInfo();
		}

		SelectedAPInfo = new DeviceInfo();
		APList_Clear();



	}

	private void resetData() {
		for (int i = 0; i < deviceNumber; i++) {
			configuredDevices[i] = new DeviceInfo();
			configuredDevices[i].setaliveFlag(0);
			configuredDevices[i].setName("");
			configuredDevices[i].setIP("");
			configuredDevices[i].setmacAdrress("");
			configuredDevices[i].setimg(null);
			configuredDevices[i].setconnectedflag(false);
		}
	}

	private void initComponent() {
//		View BTScanLayout = View.inflate(this, R.layout.wlan_scan_listview, null);

		DisplayMetrics metrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(metrics);
		btn_scan = (ImageButton) findViewById(R.id.btn_scanDevices);

		textConfigDeviceTitle = (TextView) findViewById(R.id.textDeviceTitle);
		listView = (ListView) findViewById(R.id.listView1);
		listView.setBackgroundColor(0xFFE6E6E2);
//		layout_linear = new LinearLayout(this);
		mNavigationView = (BottomNavigationView)findViewById(R.id.navigation);
		parentLayout_bt_list_view = (LinearLayout) findViewById(R.id.mainlayout);

//		parentLayout_bt_list_view.addView(BTScanLayout, layout_linear.getLayoutParams());
//		mNavigationView.setVisibility(View.GONE);
	}

	private void initComponentAction() {

		int androidBuildVersion = android.os.Build.VERSION.SDK_INT;// (Android 4.0:14, 5.0:22, 6.0:23)
		
		btn_scan.setOnTouchListener(new Button.OnTouchListener() {

			@Override
			public boolean onTouch(View arg0, MotionEvent event) {

				if (event.getAction() == MotionEvent.ACTION_DOWN) {
					btn_scan.getBackground().setAlpha(100);
				} else if (event.getAction() == MotionEvent.ACTION_UP) {
					btn_scan.getBackground().setAlpha(255);
				}

				return false;
			}
		});
			SharedPreferences db = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
			Gson gson = new Gson();
			String db_group_name_str = db.getString(DB_GROUP_NAME_TAG, null);
            Log.e(DB_GROUP_NAME_TAG, "db_group_name_str array " +db_group_name_str);
			if(db_group_name_str == null)
				bt_group_name = new ArrayList<String>();
			else {
			    String tmpGroupName[]  = db_group_name_str.split(", ");
                bt_group_name = new ArrayList<String>(Arrays.asList(tmpGroupName));
            }

		String group_name_addr_map_str = db.getString(DB_GROUP_NAMEADDR_MAP_TAG, null);
		if(group_name_addr_map_str == null)
			group_name_addr_map = new ArrayList<HashMap<String, String>>();
		else{
			Type typeToken = new TypeToken<ArrayList<HashMap<String, String>>>() {
			}.getType();
			Log.e(DB_GROUP_NAMEADDR_MAP_TAG, "DB_GROUP_NAMEADDR_MAP_TAG   array " +group_name_addr_map_str);
			group_name_addr_map = gson.fromJson(group_name_addr_map_str, typeToken);
		}

		Log.e(DB_GROUP_NAME_TAG, "after  array " +bt_group_name.toString());
		String db_group_devices_str = db.getString(DB_GROUP_DEVICES_TAG, null);
		if(db_group_devices_str == null)
			bt_group_devices_map = new ArrayList<HashMap<String, String>>();
		else {
			Type typeToken = new TypeToken<ArrayList<HashMap<String, String>>>() {
			}.getType();
			Log.e(DB_GROUP_NAME_TAG, "bt_group_name  array " +db_group_devices_str);
			bt_group_devices_map = gson.fromJson(db_group_devices_str, typeToken);
		}

			String retBDevInfoStr = db.getString(DB_BROADCAST_DEVICES_TAG, null);
Log.e(TAG,"initComponentAction " +retBDevInfoStr);
			Type type = new TypeToken<ArrayList<HashMap<String, Object>>>() {}.getType();
			BroadcastDevInfo = gson.fromJson(retBDevInfoStr, type);
			String defBDevInfoStr = gson.toJson(BroadcastDevInfo);
			if (!defBDevInfoStr.contains("null")) {
				Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
				HashMap<String, Object> map = null;
				for (; it.hasNext(); ) {
					map = it.next();
					if(map.get("Type").toString().contains("Provisioner") == true) {
					    currProvisionerIP = map.get("IP").toString();
                        map.put("Status", "");
                    }else if(map.get("Type").toString().contains("Device") == true) {
                        map.put("ACTIVE", "");
                    }
//					map.put("Type", "");
				}
				noPD = true; //no pogressdialog
				show_discoverDevice();
				DiscoveryDevice(3000);
			}

		if(androidBuildVersion >= 23 && !isLocationServiceEnabled()){
			runOnUiThread(new Runnable() {
				@Override
				public void run() {
					AlertDialog.Builder errorAlert = new AlertDialog.Builder(
							DevicesMainActivity.this);

					errorAlert.setTitle("Warning");
					errorAlert.setMessage("Please check the location service enabled if the WiFi scan failed.");
					errorAlert.setPositiveButton("OK",null);
					errorAlert.show();
				}
			});
		}
	}

	private boolean isLocationServiceEnabled()
	{
		final LocationManager manager = (LocationManager) getSystemService( Context.LOCATION_SERVICE );
		
		return manager.isProviderEnabled( LocationManager.GPS_PROVIDER );
	}

    public InetAddress getIpAddress() {
        InetAddress inetAddress = null;
        InetAddress myAddr = null;

        try {
            for (Enumeration<NetworkInterface> networkInterface = NetworkInterface
                    .getNetworkInterfaces(); networkInterface.hasMoreElements();) {

                NetworkInterface singleInterface = networkInterface.nextElement();

                for (Enumeration< InetAddress > IpAddresses = singleInterface.getInetAddresses(); IpAddresses
                        .hasMoreElements();) {
                    inetAddress = IpAddresses.nextElement();

                    if (!inetAddress.isLoopbackAddress() && (singleInterface.getDisplayName()
                            .contains("wlan0") ||
                            singleInterface.getDisplayName().contains("eth0") ||
                            singleInterface.getDisplayName().contains("ap0"))) {

                        myAddr = inetAddress;
                    }
                }
            }

        } catch (SocketException ex) {
            Log.e(TAG, ex.toString());
        }
        return myAddr;
    }

    public InetAddress getBroadcast(InetAddress inetAddr) {

        NetworkInterface temp;
        InetAddress iAddr = null;
        try {
            temp = NetworkInterface.getByInetAddress(inetAddr);
            List<InterfaceAddress> addresses = temp.getInterfaceAddresses();

            for (InterfaceAddress inetAddress: addresses)

                iAddr = inetAddress.getBroadcast();
            Log.d(TAG, "iAddr=" + iAddr);
            return iAddr;

        } catch (SocketException e) {

            e.printStackTrace();
            Log.d(TAG, "getBroadcast" + e.getMessage());
        }
        return null;
    }

	private void DiscoveryDevice(final int counts) 
	{
		if(!noPD) {
			runOnUiThread(new Runnable() {
				@Override
				public void run() {
					pd = new ProgressDialog(DevicesMainActivity.this);
					pd.setMessage("Discovering devices ...");
					pd.setProgressStyle(ProgressDialog.STYLE_SPINNER);
					pd.setIndeterminate(true);
					pd.setCancelable(false);
					pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel",
							new DialogInterface.OnClickListener() {
								@Override
								public void onClick(DialogInterface dialog, int which) {
									dialog.dismiss();
									DiscovEnable = false;
								}
							});
					pd.show();
				}
			});
		}
		new Thread(new Runnable() {
			public void run() {
				try {
					InetAddress broadCastAddress = InetAddress.getByName("255.255.255.255");


                	WifiManager wifi = (WifiManager) getApplicationContext().getSystemService(Context.WIFI_SERVICE);
                	Method[] wmMethods = wifi.getClass().getDeclaredMethods();
                	for (Method method: wmMethods) {
                    	if (method.getName().equals("isWifiApEnabled")) {

                        	try {
                            	if ((Boolean) method.invoke(wifi)) {
									broadCastAddress = getBroadcast(getIpAddress());
                               	 	Log.e(TAG, "WifiTether on");
                            	} else {

                                	Log.e(TAG, "WifiTether off");
                            	}
                        	} catch (IllegalArgumentException e) {
                            	e.printStackTrace();
                        	} catch (IllegalAccessException e) {
                            	e.printStackTrace();
                        	} catch (InvocationTargetException e) {
                            	e.printStackTrace();
                        	}

                    	}
                	}


					DatagramPacket sp;
					DatagramPacket rp;
					HashMap<String, Object> map = null;
					if(BroadcastDevInfo == null)
						BroadcastDevInfo = new ArrayList<HashMap<String, Object>>();
					else{
						Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
						HashMap<String, Object> Map = null;
						for(;it.hasNext();){
							Map = it.next();
							if(Map.get("Type").toString().contains("Provisioner") == true)
								Map.put("Status", "");
//							Map.put("Type", "");
						}
					}

					byte[] rcvmsg = new byte[64];

					byte[] testmsg = ("AMEBA:DISCOVER:"+ System.currentTimeMillis() +"\0").getBytes();
					sp = new DatagramPacket(testmsg, testmsg.length);
					rp = new DatagramPacket(rcvmsg, rcvmsg.length);

					try {
						sp.setAddress(broadCastAddress);
						sp.setPort(BROADCAST_SEND_SOCKET_PORT);
						ds = new DatagramSocket(BROADCAST_SEND_SOCKET_PORT);
						ds.setBroadcast(true);

						rp.setAddress(broadCastAddress);
						rp.setPort(BROADCAST_RECV_SOCKET_PORT);
						rs = new DatagramSocket(BROADCAST_RECV_SOCKET_PORT);
						rs.setBroadcast(true);
						rs.setSoTimeout(counts);
					} catch (SocketException e) {
						e.printStackTrace();
						String error = e.toString();
						Log.e(TAG, error);
					}  /*catch (UnknownHostException e) {
						e.printStackTrace();
						String error = e.toString();
						Log.e(TAG, error);
					}catch (IOException e) {
						e.printStackTrace();
						String error = e.toString();
						Log.e(TAG, error);
					}*/ catch (Exception e) {
						e.printStackTrace();
						String error = e.toString();
						Log.e(TAG, error);
					}

				for (int j = 0; j < counts/1000; j++) {
						try {
							ds.send(sp);
							rs.receive(rp);

							String rcvstr = new String(rcvmsg, "UTF-8").trim();
							Log.e(TAG,"rcvstr " +rcvstr.toString());
							String[] str = rcvstr.split(";");

							String buf = new String();
							for (int i = 0; i < 6; i++) {
								buf += String.format("%02x", (byte) Character.digit(str[0].charAt(i * 2), 16) * 16 + Character.digit(str[0].charAt((i * 2) + 1), 16));
								if (i < 5)
									buf += ":";
							}

							map = new HashMap<String, Object>();
							map.put("MAC", buf);
							map.put("Status", "LAN Access");
							map.put("Type", "Provisioner");
							map.put("IP", rp.getAddress().getHostAddress().toString());
							currProvisionerIP = map.get("IP").toString();
							map.put("PIN", false);
                            ConnectMESHDevice(map.get("IP").toString(), "bt_mesh=01010008", false);
							try {
								map.put("RELAYPORT", str[1]);
							}catch(ArrayIndexOutOfBoundsException e){
								map.put("RELAYPORT", "554");
								Log.e(TAG, "rcvstr.split RELAYPORT failed");
							}
							map.put("Name", "Provisioner_" + str[2]);
							map.put("RELAYSUFFIX", str[2]);
							try {
                                map.put("RESOLUTION", str[3]);
                                Log.e(TAG, "RESOLUTION "+ str[3]);
							}catch(ArrayIndexOutOfBoundsException e){
                                map.put("RESOLUTION", "720");
                                    Log.e(TAG, "rcvstr.split RESOLUTION failed");
							}
								try {
									map.put("VERSION", str[4]);
									Log.e(TAG, "VERSION "+ str[4]);
								}catch(ArrayIndexOutOfBoundsException e){
									map.put("VERSION", "unknown");
									Log.e(TAG, "rcvstr.split VERSION failed");
								}
								try {
									map.put("IRLED", str[5]);
									Log.e(TAG, "IRLED "+ str[5]);
								}catch(ArrayIndexOutOfBoundsException e){
									map.put("IRLED", "unknown");
									Log.e(TAG, "rcvstr.split IRLED failed");
								}

                                Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
                                boolean deviceExisted = false;
                                HashMap<String, Object> defMap = null;
                                for(;it.hasNext();){
                                    defMap = it.next();

                                    if(defMap.toString().contains(map.get("MAC").toString())){//compare MAC address to check if device existed

                                        deviceExisted = true;
                                        defMap.put("Status", "LAN Access");
                                        defMap.put("IP", rp.getAddress().getHostAddress().toString());
										currProvisionerIP = defMap.get("IP").toString();
										defMap.put("Type", "Provisioner");
                                        defMap.put("RELAYPORT", map.get("RELAYPORT"));
                                        defMap.put("RELAYSUFFIX",  map.get("RELAYSUFFIX"));
										try {
											defMap.put("RESOLUTION", str[3]);
											defMap.put("VERSION", str[4]);
											defMap.put("IRLED", str[5]);
										}catch(ArrayIndexOutOfBoundsException e){
											defMap.put("RESOLUTION", "720");
											defMap.put("VERSION", "unknown");
											defMap.put("IRLED", "unknown");
											Log.e(TAG, "rcvstr.split ArrayIndexOutOfBoundsException failed");
										}

                                        break;
                                    }
                                }
                                if (!deviceExisted) {
                                    BroadcastDevInfo.add(map);
                                }

                            } catch (IOException e) {
                                e.printStackTrace();
                            }catch (NullPointerException e) {
                                e.printStackTrace();
                            }
                    }

                    try {
                        if (ds != null) {
                            ds.close();
                        }
                        if (rs != null) {
                            rs.close();
                        }
                        SharedPreferences db = PreferenceManager.getDefaultSharedPreferences(context);
                        Gson gson = new Gson();
                        String retBDevInfoStr = db.getString(DB_BROADCAST_DEVICES_TAG, null);

                        Type type = new TypeToken<ArrayList<HashMap<String, Object>>>() {
                        }.getType();
                        ArrayList<HashMap<String, Object>> defBDevInfo = gson.fromJson(retBDevInfoStr, type);
                        String defBDevInfoStr = gson.toJson(defBDevInfo);
                        String BDevInfoStr = gson.toJson(BroadcastDevInfo);
//                        Log.e(TAG,"after DiscoveryDevice BroadcastDevInfo "+BDevInfoStr);
                        //if (defBDevInfoStr.contains("null"))
                        {
                            SharedPreferences.Editor defCollection = db.edit();
                            defCollection.putString(DB_BROADCAST_DEVICES_TAG, BDevInfoStr);
                            defCollection.commit();
                        }



				}catch(NullPointerException e)
				{
					e.printStackTrace();
				}
				if (noPD) {
					noPD = false;
					handler_pd.sendEmptyMessage(3);
				} else {
					handler_pd.sendEmptyMessage(2);
//					Log.e(TAG, "NOPD!!!!");
				}
//				    Log.e(TAG, " DiscoveryDevice finish");
				}catch (UnknownHostException e){
					e.printStackTrace();
				}
			}
		}).start();

	}


    private void ConnectMESHDevice(final String address, final String queryStr, boolean isNeedProgressDialog)
    {
        if( isNeedProgressDialog == true) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
					noPD = false;
                    pd = new ProgressDialog(DevicesMainActivity.this);
                    pd.setMessage("Connect Mesh devices ...");
                    pd.setProgressStyle(ProgressDialog.STYLE_SPINNER);
                    pd.setIndeterminate(true);
                    pd.setCancelable(false);
                    pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel",
                            new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    dialog.dismiss();
                                    DiscovEnable = false;
                                }
                            });
                    pd.show();
                }
            });
        }

		httpQueryThread = new Thread(new Runnable() {
            public void run() {

            	String HTTPQueryResult;
				HTTPQueryResult = HTTPQuery(address, queryStr);
				if(HTTPQueryResult != null)
					HTTPQueryResultParse(HTTPQueryResult);

                if (noPD) {
                    noPD = false;
                    handler_pd.sendEmptyMessage(3);
                } else {
                    handler_pd.sendEmptyMessage(2);
                    Log.e(TAG, "NOPD!!!!");
                }


            }
        });
		httpQueryThread.start();

    }

    public static boolean HTTPQueryResultParse(String queryResultStr){
		Iterator<HashMap<String, Object>> it;
		HashMap<String, Object> defMap = null;
		String UUIDStrs;
		String meshAddr;
		int count_devices;
		String mesh_event_str = queryResultStr.substring("bt_mesh= ".length(), queryResultStr.length());
		String event = mesh_event_str.substring(0,4);
		String count_devices_str = mesh_event_str.substring(8,10);

		if(count_devices_str.contains("ff")){
			Looper.prepare();
			Toast.makeText(context,
				"HTTP response error " + count_devices_str, Toast.LENGTH_LONG).show();
			Looper.loop();
        }


//		Log.e(TAG,"mesh_event_str "+mesh_event_str);


		switch(event){
			case "0201": //RTW_BT_EVENT_PROVISIONER_STATE
				String ret =  mesh_event_str.substring(mesh_event_str.length()-2,mesh_event_str.length());
				if(ret.contains("01"))  //success
				{
					//todo
				} else {
					//todo
				}
				break;
			case "0202": //RTW_BT_EVENT_UNPROVISIONED_DEVICE  0202 000a 00
				count_devices = Integer.valueOf(count_devices_str);
				UUIDStrs =  mesh_event_str.substring(10,mesh_event_str.length());
				Log.e(TAG,"count_devices "+count_devices +" UUIDStrs "+UUIDStrs);


				boolean deviceExisted;


				for(int i=0 ; i < count_devices; i++ ){
                    deviceExisted = false;
					HashMap<String, Object> map = new HashMap<String, Object>();
					map.put("UUID", UUIDStrs.substring(i*32, (i+1) *32 ) );
//					map.put("Name", "Device_"+ UUIDStrs.substring(0, 6));
					map.put("Name", "Device_"+ map.get("UUID").toString().substring(0, 6));
					Log.e(TAG,"map.get(\"UUID\") "+map.get("UUID").toString());
					map.put("Status", "Mesh Disconnect");
					map.put("Type", "Device");
					map.put("IP", "");
					map.put("VERSION", "");
					map.put("GROUP_ADDR", "");
					map.put("ACTIVE", " ");
					map.put("LIGHT", "");
					map.put("MESH_ADDR", "");

					it = BroadcastDevInfo.iterator();
					for(;it.hasNext();){
						defMap = it.next();
						Log.e(TAG,"1deviceExisted  "+deviceExisted + " defMap "+defMap.toString() + " map.get(\"UUID\") " + map.get("UUID") + " BroadcastDevInfo " +BroadcastDevInfo.toString());
						if(defMap.toString().contains(map.get("UUID").toString())){//compare UUID to check if device existed
							deviceExisted = true;
						}
					}
					Log.e(TAG,"2deviceExisted  "+deviceExisted + " map "+map.toString());
					if (deviceExisted == false) {
						BroadcastDevInfo.add(map);
					}
//					if (noPD) {
//						noPD = false;
//						handler_pd.sendEmptyMessage(3);
//					} else {
//						handler_pd.sendEmptyMessage(2);
//						Log.e(TAG, "NOPD!!!!");
//					}
					Log.e(TAG,"HTTPQueryResultParse  BroadcastDevInfo "+BroadcastDevInfo.toString());
				}
				break;
            case "0203":
                if(count_devices_str.contains("00"))
                    return false;
				UUIDStrs =  mesh_event_str.substring(10, 42);
				String connStatusStr = mesh_event_str.substring(42, 44);
				meshAddr = mesh_event_str.substring(44, 48);
				String lightState = mesh_event_str.substring(48, 50);
//				Log.e(TAG,"UUIDStrs "+UUIDStrs +" connStatusStr "+connStatusStr +" meshAddr " + meshAddr +" lightState "+lightState);
				if(connStatusStr.contains("01"))//success
				{
					it = BroadcastDevInfo.iterator();
					for (; it.hasNext(); ) {
						defMap = it.next();
						if (defMap.toString().contains(UUIDStrs))
						{
							defMap.put("Status", "Mesh Connected");
							defMap.put("MESH_ADDR", meshAddr);
							defMap.put("LIGHT", lightState);
						}
					}
					SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(context);//this.getPreferences(MODE_PRIVATE);
					SharedPreferences.Editor editor = pref.edit();
					Gson gson = new Gson();
					String BDevInfoStr = gson.toJson(BroadcastDevInfo);
					editor.putString(DB_BROADCAST_DEVICES_TAG,BDevInfoStr);
					editor.commit();
					if(popDeviceListAdapter != null)
						popDeviceListAdapter.init();
					Log.e(TAG,"popAwindow  retBDevInfoStr "+BDevInfoStr );
				}

				Log.e(TAG,"HTTPQueryResultParse BroadcastDevInfo "+BroadcastDevInfo.toString());
				break;
			case "0204"://0204 0010 01 0100 01
				String delStatusStr = mesh_event_str.substring(mesh_event_str.length()-2, mesh_event_str.length());
				meshAddr = mesh_event_str.substring(mesh_event_str.length()-6, mesh_event_str.length()-2);
				String deviceName = null;
Log.e(TAG,"delStatusStr "+delStatusStr +" meshAddr "+meshAddr);
				if(delStatusStr.contains("01"))//success
				{
					it = BroadcastDevInfo.iterator();
					for (; it.hasNext(); ) {
						defMap = it.next();
						Log.e(TAG,"fucking simen meshAddr " +  meshAddr + defMap.toString() + defMap.toString().contains(meshAddr) );
						if (defMap.toString().contains(meshAddr))
						{
							deviceName = defMap.get("Name").toString();
//							defMap.put("Status", "Mesh Disconnect");
//							defMap.put("MESH_ADDR", "");
//							defMap.put("GROUP_ADDR", "");
//							defMap.put("ACTIVE", "");
//							defMap.put("LIGHT", "");
							BroadcastDevInfo.remove(defMap);
							if(popDeviceListAdapter != null)
								popDeviceListAdapter.init();

Log.e(TAG,"fucking simen " + defMap.get("Name") );
							break;
						}
					}

					Log.e(TAG,"fucking the world " + deviceName );

					Iterator<HashMap<String, String>> it_bt_group_devices_map = bt_group_devices_map.iterator();
					for (; it_bt_group_devices_map.hasNext(); ) {
						HashMap<String, String> map = it_bt_group_devices_map.next();
						Log.e(TAG,"fucking simen  name " + deviceName +" map "+ map.toString() +" map.toString().contains(name) " + map.toString().contains(deviceName) );
						if (map.toString().contains(deviceName)   ) {
							String group_name = map.keySet().toString().substring(1,map.keySet().toString().length()-1);
							String devicesStr = map.get(group_name);
							Log.e(TAG,"fucking bt_group_devices_map "+devicesStr+" devicesStr.contains(name) "+devicesStr.contains(deviceName)+ " name "+deviceName);
							if(devicesStr.contains(deviceName+";"))
								devicesStr = devicesStr.replace(deviceName+";","");
							else if(devicesStr.contains(deviceName)) {
								devicesStr = devicesStr.replace(deviceName, "");
							}
							Log.e(TAG,"fucking bt_group_devices_map !"+devicesStr+"!");
							if(devicesStr.isEmpty()) {
								Iterator<HashMap<String, String>> it_group_name_addr_map = group_name_addr_map.iterator();
								for (; it_group_name_addr_map.hasNext(); ) {
									HashMap<String, String> tmpMap_it_group_name_addr_map = it_group_name_addr_map.next();
									if (tmpMap_it_group_name_addr_map.toString().contains(group_name)) {
										group_name_addr_map.remove(tmpMap_it_group_name_addr_map);
									}
								}

								bt_group_name.remove(group_name);

								bt_group_devices_map.remove(map);
							}else
								map.put(map.keySet().toString().substring(1,map.keySet().toString().length()-1),devicesStr);
						}
					}



					Log.e(TAG," bt_group_devices_map "+bt_group_devices_map);
					SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(context);//this.getPreferences(MODE_PRIVATE);
					SharedPreferences.Editor editor = pref.edit();
					Gson gson = new Gson();
					String group_name_addr_map_str = gson.toJson(group_name_addr_map);
					String bt_group_devices_map_str = gson.toJson(bt_group_devices_map);
					String BDevInfoStr = gson.toJson(BroadcastDevInfo);
					editor.putString(DB_BROADCAST_DEVICES_TAG, BDevInfoStr);
					editor.putString(DB_GROUP_NAMEADDR_MAP_TAG, group_name_addr_map_str);
					editor.putString(DB_GROUP_DEVICES_TAG,bt_group_devices_map_str);
					//		if(bt_group_name.size() > 0)
					editor.putString(DB_GROUP_NAME_TAG, bt_group_name.toString().substring(1,+bt_group_name.toString().length()-1));
					editor.commit();

				}else if(delStatusStr.contains("00")) {//success
					Looper.prepare();
                    Toast.makeText(context,
						"Delete device failed!", Toast.LENGTH_LONG).show();
					Looper.loop();
				    return false;

                }


                break;
			case "0205"://0205 0016 01 0104 0000 01 00
				count_devices = Integer.valueOf(count_devices_str);
				if(count_devices == 0)
					break;
				meshAddr = mesh_event_str.substring(10, 14);

				if(count_devices >= 1)//success
				{
					it = BroadcastDevInfo.iterator();
					for (; it.hasNext(); ) {
						defMap = it.next();
						if (defMap.toString().contains(meshAddr))
						{
							defMap.put("GROUP_ADDR", mesh_event_str.substring(14, 18));
							defMap.put("ACTIVE", mesh_event_str.substring(18, 20));
							defMap.put("LIGHT", mesh_event_str.substring(20, 22));
						}
					}
					SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(context);//this.getPreferences(MODE_PRIVATE);
					SharedPreferences.Editor editor = pref.edit();
					Gson gson = new Gson();
					String BDevInfoStr = gson.toJson(BroadcastDevInfo);
					editor.putString(DB_BROADCAST_DEVICES_TAG,BDevInfoStr);
					editor.commit();
//					if (noPD) {
//						noPD = false;
//						handler_pd.sendEmptyMessage(3);
//					} else {
//						handler_pd.sendEmptyMessage(2);
//						Log.e(TAG, "NOPD!!!!");
//					}
				}

				break;
			default:

		}


//		Log.e(TAG,"event str " + event);
		return true;
	}

    private String HTTPQuery(String address, String queryStr){

//		Log.e(TAG,"HTTPQuery lock");
        try {
            _mutex.lockInterruptibly();
            StringBuilder stringBuilder = new StringBuilder("http://" + address + "/");
            stringBuilder.append("test_get?");
            String[] array = queryStr.split("=");
            stringBuilder.append(array[0] + "=");
            stringBuilder.append(URLEncoder.encode(array[1], "UTF-8"));

//            Log.e(TAG,"whlole length: "+ stringBuilder.length());

            URL obj = new URL(stringBuilder.toString());

            HttpURLConnection con = (HttpURLConnection) obj.openConnection();
            con.setRequestMethod("GET");
            con.setRequestProperty("User-Agent", "Mozilla/5.0");
            con.setRequestProperty("Accept-Charset", "UTF-8");
            con.setUseCaches(false);



//            Log.e(TAG, "\nSending request to URL : " + obj.toString());
//            Log.e(TAG, "Response Code : " + con.getResponseCode());
//            Log.e(TAG, "Response Message : " + con.getResponseMessage());

            if(con.getResponseCode() == HttpURLConnection.HTTP_OK) {
				BufferedReader in = new BufferedReader(
						new InputStreamReader(con.getInputStream()));
				String line;
				StringBuffer response = new StringBuffer();

				while ((line = in.readLine()) != null) {
					response.append(line);
				}

				http_response = response.toString();
				Log.e(TAG, "http content: " + http_response);
				in.close();
				_mutex.unlock();
//				Log.e(TAG,"HTTPQuery unlock");
				return http_response;
//				Looper.prepare();
//				Toast.makeText(DevicesMainActivity.this,
//						http_response, Toast.LENGTH_LONG).show();
//				Looper.loop();

			}else{
				Log.e(TAG, "Response Code : " + con.getResponseCode() );
			}
//                    runOnUiThread(new Runnable() {
//                        @Override
//                        public void run() {
//                            responseTextView.setText(http_response);
//                        }
//                    });

        }catch (UnsupportedEncodingException e){
            Log.e(TAG, "UnsupportedEncodingException !! " );
        }catch (MalformedURLException e){
            Log.e(TAG, "MalformedURLException !! " );
        }catch (IOException e){
            Log.e(TAG, "IOException !! " );
        }catch (InterruptedException e){
            Log.e(TAG, "InterruptedException !! " );
        }
		Log.e(TAG,"HTTPQuery HTTPQuery unlock");

//		_mutex.unlock();
		return null;
    }

	private void APList_Clear() {
		for (int i = 0; i < APNumber; i++) {
			APInfo[i].setconnectedflag(false);
			APInfo[i].setaliveFlag(0);
			APInfo[i].setName("");
			APInfo[i].setIP("");
			APInfo[i].setmacAdrress("");
			APInfo[i].setsecurityType(0);
			APInfo[i].setimg(null);
		}

		SelectedAPInfo = new DeviceInfo();
		SelectedAPInfo.setconnectedflag(false);
		SelectedAPInfo.setaliveFlag(0);
		SelectedAPInfo.setName("");
		SelectedAPInfo.setIP("");
		SelectedAPInfo.setmacAdrress("");
		SelectedAPInfo.setsecurityType(0);
		SelectedAPInfo.setimg(null);

	}

	private boolean checkDeviceInformation(String macAddress) {
		boolean ret = false;
		int deviceNum = 0;
		String tmp_mac = "";

		if (macAddress.length() == 0 || macAddress == null)
			return ret;

		deviceNum = DevInfo.size();

		for (int i = 0; i < deviceNum; i++) {

			tmp_mac = (String) DevInfo.get(i).get("MAC");
			if (macAddress.equals(tmp_mac)) {
				CurrentControlIP = (String) DevInfo.get(i).get("IP");
				if (CurrentControlIP.length() == 0
						|| CurrentControlIP.equals("0.0.0.0"))
					continue;
				ret = true;
				break;
			}
		}

		return ret;
	}

	private void getkDeviceInformation(final String device,
			final String macAddress) {
		is_getIP_finish = false;

		pd = new ProgressDialog(DevicesMainActivity.this);

		pd.setTitle("Waiting");
		pd.setMessage("Getting " + device + " information...");
		pd.setProgressStyle(ProgressDialog.STYLE_SPINNER);
		pd.setIndeterminate(true);
		pd.setCancelable(false);
		pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel",
				new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
					}
				});
		pd.show();

		new Thread(new Runnable() {
			public void run() {
				Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);

				boolean isCtlPIN = false;
				int deviceNum = -1;
				int iDevice = -1;
				int i = -1;
				String tmp_mac = "";
				long startTime = System.currentTimeMillis();
				long endTime = System.currentTimeMillis();
				while (!is_getIP_finish && (endTime - startTime) < 30000) {

					try {
						Thread.sleep(500);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}

					endTime = System.currentTimeMillis();

					// check the ip of device
					if (checkDeviceInformation(macAddress)) {
						is_getIP_finish = true;
						break;
					}
				}
				handler_pd.sendEmptyMessage(0);

				// Update Status
				Message msg = Message.obtain();
				msg.obj = null;
				deviceNum = DevInfo.size();

				if (is_getIP_finish) {

					for (i = 0; i < deviceNum; i++) {
						tmp_mac = (String) DevInfo.get(i).get("MAC");
						if (macAddress.equals(tmp_mac)) {
							iDevice = i;
							break;
						}
					}

					if (iDevice >= 0) {

						if (DevInfo.get(iDevice).get("PIN") != null) {
							isCtlPIN = (Boolean) DevInfo.get(iDevice).get("PIN");
						}

						final boolean isDevicePIN = isCtlPIN;
						final String deviceName = (String) DevInfo.get(iDevice).get("Name");
						final String deviceMAC = (String) DevInfo.get(iDevice).get("MAC");
						final String deviceType = (String) DevInfo.get(CurrentItem).get("Type");

						runOnUiThread(new Runnable() {
							@Override
							public void run() {
								Log.d(TAG, "Setting: " + deviceName + " "+ deviceMAC + " " + isDevicePIN);

								if (!isDevicePIN)
									CtlDefaultPINcode(deviceName, deviceMAC, deviceType, -1);
								else
									ControlPINcode(deviceName, deviceMAC, deviceType);
							}
						});
					}

				}

			}
		}).start();
	}

	@Override
	public boolean dispatchTouchEvent(MotionEvent event){
		if(window != null && window.isShowing())
			return false;
		return super.dispatchTouchEvent(event);
	}

    private void closeWindow(){

        for (int j = 0; j < BTListBaseAdapter.isSelected.size(); j++) {
            BTListBaseAdapter.isSelected.put(j, false);
            BTListBaseAdapter.ViewHolder vHollder = (BTListBaseAdapter.ViewHolder) popup_bt_listview.getChildAt(j).getTag();
            vHollder.cBox.setChecked(false);
        }

        if (window != null) {
            window.dismiss();
        }
    }

	private void popAwindow(View parent) {
		if (window == null) {
			LayoutInflater lay = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			View v = lay.inflate(R.layout.bt_popup_window, null);
			TextView popup_title = v.findViewById(R.id.tip);
			popup_submit = (Button) v.findViewById(R.id.submit);
			popup_cancel = (Button) v.findViewById(R.id.cancel);
			popup_bt_listview = (ListView)v.findViewById(R.id.lv);


			popup_title.setText(pop_groupname_edittext.getText().toString() + " group devices list ");

			popDeviceListAdapter = new BTListBaseAdapter(getApplicationContext());
			popup_bt_listview.setAdapter(popDeviceListAdapter);
			popup_bt_listview.setItemsCanFocus(false);
			popup_bt_listview.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE);
			popup_bt_listview.setOnItemClickListener(listClickListener);

			window = new PopupWindow(v, LinearLayout.LayoutParams.WRAP_CONTENT,LinearLayout.LayoutParams.WRAP_CONTENT,true);
			window.setFocusable(false);
            window.setOutsideTouchable(false);

            Button.OnClickListener popup_submitListener=new Button.OnClickListener(){
                @Override
                public void onClick(View v){
					String group_member_name = new String();
                	for(int i=0;i<popup_bt_listview.getCount();i++){
						BTListBaseAdapter.ViewHolder vHollder = (BTListBaseAdapter.ViewHolder) popup_bt_listview.getChildAt(i).getTag();
						if(vHollder.cBox.isChecked()){
							group_member_name = group_member_name + vHollder.title.getText().toString()+";";
						}

						Log.e(TAG, "--onClick --"+vHollder.title.getText() + "  checked: " +vHollder.cBox.isChecked()+" group_member_name "+group_member_name);
					}

					HashMap<String, String> Map = null;
                    String group_addr = null;
                    Map = new HashMap<String, String>();
					bt_group_name.add(pop_groupname_edittext.getText().toString());
                    if(!group_member_name.isEmpty()) {
						Map.put(pop_groupname_edittext.getText().toString(), group_member_name.substring(0, group_member_name.length() - 1));
						bt_group_devices_map.add(Map);
						String[] deviceName = Map.get(pop_groupname_edittext.getText().toString()).split(";");
						int i = 1;
						boolean isScanFinished = false;
						Log.e(TAG, " popAwindow " + group_addr +" group_name_addr_map "+group_name_addr_map.toString() );
						do {
							isScanFinished = true;
							Iterator<HashMap<String, String>> it = group_name_addr_map.iterator();


							for (; it.hasNext(); ) {
								HashMap<String, String> map = it.next();
								if (map.containsKey((String.format("c%03x", i)))) {
									i++;
									isScanFinished = false;
									break;
								}
							}
							group_addr = String.format("c%03x", i);
						}while(!isScanFinished);
						HashMap<String, String> map = new HashMap<String, String>();
                        Log.e(TAG, "popAwindow " + group_addr +" group_name_addr_map "+group_name_addr_map.toString() );
						map.put(group_addr, pop_groupname_edittext.getText().toString() );
						group_name_addr_map.add(map);

						Gson gson = new Gson();
						String queryStr = new String();
						String mesh_addr = new String();
                        queryStr = String.format("%02x", deviceName.length);
						for(i=0; i<deviceName.length; i++){

							String defBDevInfoStr = gson.toJson(BroadcastDevInfo);
							if (!defBDevInfoStr.contains("null")) {
								Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
								HashMap<String, Object> BroadcastDevInfoMap = null;
								for (; it.hasNext(); ) {
									BroadcastDevInfoMap = it.next();
									if(BroadcastDevInfoMap.get("Name").toString().contains(deviceName[i]) == true) {
										mesh_addr =(String) BroadcastDevInfoMap.get("MESH_ADDR");
									}

								}

							}

							queryStr = queryStr + mesh_addr  + group_addr;
							Log.e(TAG, "1popAwindow " + queryStr );
						}
						queryStr = "0107" + String.format( "%04x", queryStr.length() + 8 ) + queryStr;
						Log.e(TAG, "2popAwindow " + queryStr );
						ConnectMESHDevice(currProvisionerIP, "bt_mesh="+queryStr, true );
						Log.e(TAG, "--groupName -- " + pop_groupname_edittext.getText().toString() + "  bt_group_devices_map: " + bt_group_devices_map.toString() + " group_name_addr_map:"+group_name_addr_map.toString());
					}else{
						Toast.makeText(DevicesMainActivity.this,
								"Error: Please select at least one device in list.", Toast.LENGTH_LONG).show();
					}
					closeWindow();
                }
            };
            popup_submit.setOnClickListener(popup_submitListener);

            Button.OnClickListener popup_cancelListener=new Button.OnClickListener(){
                @Override
                public void onClick(View v){
                    closeWindow();
                }
            };
			popup_cancel.setOnClickListener(popup_cancelListener);



		}

//		window.setFocusable(true);
		window.update();
		window.showAtLocation(parent, Gravity.CENTER_VERTICAL, 0, 0);


	}

	AdapterView.OnItemClickListener listClickListener = new AdapterView.OnItemClickListener() {
		@Override
		public void onItemClick(AdapterView<?> parent, View view, int position,
								long id) {
			BTListBaseAdapter.ViewHolder vHollder = (BTListBaseAdapter.ViewHolder) view.getTag();
			vHollder.cBox.toggle();

//			Log.e(TAG,"item: "+ vHollder.title.getText() + " checked: " + vHollder.cBox.isChecked());
			BTListBaseAdapter.isSelected.put(position, vHollder.cBox.isChecked());
		}
	};




	private boolean show_discoverDevice() {

		adapter_deviceInfo = new SimpleAdapter(this, getData_Device(),
				R.layout.device_main_list, new String[] { "title", "info", "status" },
				new int[] { R.id.title, R.id.info, R.id.status })
		{
			@Override
			public View getView(int position, View convertView, ViewGroup parent)
			{
				View v = super.getView(position, convertView, parent);
				btn_setting = (ImageButton) v.findViewById(R.id.img_btn_setting);
				mParent = parent;
				mPosition = position;

				HashMap<String, Object> map = null;
				String status = null, mac = null;
				int i=0;

				Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
				for(;it.hasNext();){
					map = it.next();
					status = (String) map.get("Status");
					if(i == position)
						break;
					i++;
				}

				btn_setting.setOnClickListener(new View.OnClickListener()  {
					@Override
					public void onClick(View view) {
						boolean isCtlPIN = false;
						String deviceType = "";
						ListView listView_parent = (ListView) mParent;
						listView_parent.setTag(view);
						mPosition = listView_parent.getPositionForView(view);

						String[] tmp = listView_parent.getItemAtPosition(mPosition)
								.toString().split("title=");
						String tmp1 = tmp[1];
						String[] deviceName = tmp1.split(",");

						tmp = listView_parent.getItemAtPosition(mPosition).toString().split("info=");
						String macAddress = tmp[1];
						macAddress = macAddress.replaceFirst("\\}", "");
						macAddress = macAddress.substring(0, 17);
						CurrentItem = mPosition;

						Log.d(TAG, "listView choose " + deviceName[0] + " "	+ macAddress);


						if (isScanFinish) {
							CurrentControlIP = (String) DevInfo.get(CurrentItem).get("IP");

							deviceType = (String) DevInfo.get(CurrentItem).get("Type");

							if (DevInfo.get(CurrentItem).get("PIN") != null) {
								isCtlPIN = (Boolean) DevInfo.get(CurrentItem).get("PIN");
							}

							if (!isCtlPIN) {
								CtlDefaultPINcode(deviceName[0], (String) DevInfo.get(CurrentItem).get("MAC"), deviceType, mPosition);
							}else {
								ControlPINcode(deviceName[0], (String) DevInfo.get(CurrentItem).get("MAC"), deviceType);
							}
						} else {
							// check list info after first confirm device
							getkDeviceInformation(deviceName[0], macAddress);
						}
					}
				});
				return v;
			}

		};
		listView.setAdapter(adapter_deviceInfo);
		if (adapter_deviceInfo.getCount() > 0) {
			setListViewHeightBasedOnChildren(listView);
		}
		else if (adapter_deviceInfo.getCount() == 0) {
			listView.setAdapter(null);

		}

		listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> parent, View view,
                                    int itemId, long arg3) {
				HashMap<String, Object> map = null;
				int i=0;

				Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
				for(;it.hasNext();){
					map = it.next();
					if(i == itemId)
						break;
					i++;
				}
				if(map.get("UUID") != null) {
					Log.e(TAG, "2.CONNECT DEVICE UUID:" + map.get("UUID").toString());
					ConnectMESHDevice(currProvisionerIP, "bt_mesh=0103002a01" + map.get("UUID").toString(), true);
				}

//waitting by modified by sean
//				Intent intent = new Intent(context,GroupTabActivity.class);
//				intent.putExtra(EXTRA_MESSAGE, map);
//				startActivity(intent);

			}
		});
		return true;
	}


	public void ScanDevices_OnClick(View view) {

		ConnectivityManager connManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);

			DiscovEnable = true;
			noPD = false;
			DiscoveryDevice(discoveryTimeout);
	
	}

    public void Group_Add_OnClick(final View view) {

		AlertDialog alertDialog_group;
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);
        pop_groupname_edittext = new EditText(this);

        alertDialogBuilder.setTitle("Enter the name for mesh group");
        alertDialogBuilder.setView(pop_groupname_edittext);
        alertDialogBuilder.setCancelable(true);
        alertDialogBuilder.setPositiveButton("Continue",new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog,int id) {
                InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                imm.hideSoftInputFromWindow(pop_groupname_edittext.getWindowToken(),0);
                if(bt_group_name.contains(  pop_groupname_edittext.getText().toString() ))
				{
                    Toast.makeText(DevicesMainActivity.this,
                            "Error: This group name is already being used!",
                            Toast.LENGTH_LONG).show();

					return;
				}else if(pop_groupname_edittext.getText().toString().isEmpty()){
					Toast.makeText(DevicesMainActivity.this,
							"Error: This group name can't be empty!",
							Toast.LENGTH_LONG).show();
					return;
				}

				popAwindow(view);
            }
        });
		alertDialogBuilder.setNegativeButton("cancel",new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog,int id) {
			}
		});
		alertDialog_group = alertDialogBuilder.create();
		alertDialog_group.show();
    }


	public void About_OnClick(View view) {
		String appVersion = "";
		PackageManager manager = this.getPackageManager();
		PackageInfo info = null;
		try {
			info = manager.getPackageInfo(this.getPackageName(), 0);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		appVersion = info.versionName;

		if (appVersion.length() == 0)
			appVersion = "1.0";

		new AlertDialog.Builder(DevicesMainActivity.this)
				.setIcon(android.R.drawable.ic_menu_info_details)
				.setTitle("About").setCancelable(false)
				.setMessage("Realtek BT MESH v" + appVersion)
				.setPositiveButton("OK", null).show();
	}

	// <func>
	public void ControlPINcode(final String deviceName, final String macAddress, final String deviceType) {

		factory = LayoutInflater.from(DevicesMainActivity.this);

		edittxt_PINcode.setText("", TextView.BufferType.EDITABLE);
		edittxt_PINcode.setInputType(InputType.TYPE_CLASS_NUMBER);
		edittxt_PINcode.setTextSize(20);

		// try to get success pin code by pinfilename
		String content = "";
		byte[] buff = new byte[256]; // input stream buffer
		try {
			FileInputStream reader = openFileInput(pinfileName);
			while ((reader.read(buff)) != -1) {
				content += new String(buff).trim();
			}
			reader.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			Log.e(TAG, "pin code FileNotFoundException: " + content);
		} catch (IOException e) {
			Log.e(TAG, "pin code IOException: " + content);
		}

		if (content.length() > 0) {
			String[] DeviceItem = content.split(";");
			int itemNumber = DeviceItem.length;

			for (int i = 0; i < itemNumber; i++) {
				String[] array = DeviceItem[i].split(",");
				if (macAddress.equals(array[0]) == true) {// bssid is same
					edittxt_PINcode.setText(array[1],
							TextView.BufferType.EDITABLE);
					break;
				}
			}
		}

		pinCodeText = edittxt_PINcode.getText().toString();
		PINGet = edittxt_PINcode.getText().toString();

		AlertDialog.Builder alert = new AlertDialog.Builder(DevicesMainActivity.this);
		alert.setCancelable(false);
		alert.setTitle("Key in " + deviceName + " PIN code");
		alert.setMessage("The PIN code will be display on device if the PIN code is exist.");
		alert.setCancelable(false);
		alert.setView(wifiPW_EntryView);
		alert.setPositiveButton("Cancel", null);
		alert.setNegativeButton("OK", new DialogInterface.OnClickListener() {

			@Override
			public void onClick(DialogInterface arg0, int arg1) {

				if (edittxt_PINcode.getText().toString().length() <= 0) {
					Toast.makeText(DevicesMainActivity.this,
							"Warning: The PIN code is empty!",
							Toast.LENGTH_LONG).show();
					return;
				}


				if (edittxt_PINcode.getText().toString().length() > 0) {
					pinCodeText = edittxt_PINcode.getText().toString();
					PINGet = edittxt_PINcode.getText().toString();

					byte[] pinget = PINGet.getBytes();
					byte[] pinset;
					if (pinget.length > 0) {
						if (pinget.length < 8) {
							pinset = new byte[8];
							System.arraycopy(pinget, 0, pinset, 0,
									pinget.length);
							for (int i = pinget.length; i < 8; i++) {
								pinset[i] = '0';
							}
						} else if (pinget.length >= 8 && pinget.length <= 64) {
							pinset = new byte[pinget.length];
							System.arraycopy(pinget, 0, pinset, 0,
									pinget.length);
						} else {
							pinset = new byte[64];
							System.arraycopy(pinget, 0, pinset, 0, 64);
						}
						PINSet = new String(pinset);
					} else {
						PINSet = new String(pinget);
					}
				}

				AlertDialog.Builder dialogaction = new AlertDialog.Builder(DevicesMainActivity.this);
				// Get the layout inflater
				dialogaction.setCancelable(false);
				dialogaction.setTitle("Setting action");
				dialogaction.setIcon(R.drawable.settings);

				
				if(deviceType.equals("Multi_Media")){
					dialogaction.setItems(CtrlListStr,new DialogInterface.OnClickListener(){

						@Override
						public void onClick(DialogInterface dialog, int which) {
							 if(which==0){
								 rename_OnClick(deviceName);
							 }else if(which==1){
								 remove_OnClick(-1);
							 }
						}
					});
				}else{
					dialogaction.setNeutralButton("Remove device",
							new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									dialog.cancel();
									remove_OnClick(-1);

								}
							});

					dialogaction.setNegativeButton("Rename",
							new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int id) {
									dialog.cancel();
									rename_OnClick(deviceName);
								}
							});
				}
				
				
				dialogaction.setPositiveButton("Exit", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int id) {
						dialog.cancel();
					}
				});
				dialogaction.show();
				
			}

		});
		alert.show();
	}


	
	public void CtlDefaultPINcode(final String deviceName, final String macAddress, final String deviceType, final int itemId) {

		AlertDialog.Builder dialogaction = new AlertDialog.Builder(
				DevicesMainActivity.this);
		// Get the layout inflater
		dialogaction.setCancelable(false);
		dialogaction.setTitle("Setting action\n");
		dialogaction.setIcon(R.drawable.settings);
		
		if(deviceType.equals("Multi_Media")){
		//do something
		}else{

			int i = 0;
			Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
			Log.e(TAG, "setting BroadcastDevInfo "+BroadcastDevInfo.toString());
			for(;it.hasNext();) {
				tmpMap = it.next();
				if (i == itemId )
					break;
				i++;
			}

			setting_menu = new ArrayList<String>();
			if( tmpMap.get("Type").toString().equals("Provisioner") ) {
//                setting_menu.add("START_PROVISIONER");
                setting_menu.add("GET UNPROVISIONED DEVICE");
				setting_menu.add("CVR:"+tmpMap.get("VERSION").toString());
				setting_menu.add(tmpMap.get("IP").toString());
				currProvisionerIP = tmpMap.get("IP").toString();

            }else if( tmpMap.get("Type").toString().equals("Device") ) {
				if(tmpMap.get("Status").toString().contains("Mesh Connected") ) {
					setting_menu.add("REMOVE MESH CONNECTION");
					setting_menu.add("REFRESH NODE STATUS");
					String lightStr = "";
					if(tmpMap.get("LIGHT").toString().contains("00"))
						 lightStr = "Turn ON";
					else if(tmpMap.get("LIGHT").toString().contains("01"))
						 lightStr = "Turn OFF";
					setting_menu.add("LIGHT CONTROL: "+lightStr);
				}else {
					setting_menu.add("CONNECT MESH DEVICE");
				}
				setting_menu.add("UUID:"+tmpMap.get("UUID").toString());
			}
			setting_menu.add("Remove This Device");


			final String[] SettingListStr = setting_menu.toArray(new String[0]);

//			dialogaction.setNeutralButton("Remove device",
//					new DialogInterface.OnClickListener() {
//						public void onClick(DialogInterface dialog, int id) {
//							dialog.cancel();
//							remove_OnClick(itemId);
//
//						}
//					});

			dialogaction.setItems(SettingListStr,new DialogInterface.OnClickListener(){

				@Override
				public void onClick(DialogInterface dialog, int which) {

//				    if(SettingListStr[which].toString().contains("START_PROVISIONER")) {
//						ConnectMESHDevice(currProvisionerIP, "bt_mesh=01010008", true);
//
//					}else
					if(SettingListStr[which].toString().contains("Remove This Device")){
						boolean isRemoveItem = true;
						dialog.cancel();
						remove_OnClick(itemId);

						if(tmpMap.get("Type").toString().equals("Provisioner"))
							return;

						if(tmpMap.get("MESH_ADDR").toString().isEmpty() == false)
							ConnectMESHDevice(currProvisionerIP, "bt_mesh=0104000e01" + tmpMap.get("MESH_ADDR").toString(), false);


//                        removeDeviceFromGROUPDevicesMap(tmpMap.get("Name").toString());


                    }else if(SettingListStr[which].toString().contains("GET UNPROVISIONED DEVICE")){
                        ConnectMESHDevice(currProvisionerIP, "bt_mesh=01020008", true);

                    }else if(SettingListStr[which].toString().contains("CONNECT MESH DEVICE")){
				    	Log.e(TAG, "1.CONNECT DEVICE UUID:" + tmpMap.get("UUID").toString());
				    	if(tmpMap.get("UUID") != null) {
                            Log.e(TAG, "2.CONNECT DEVICE UUID:" + tmpMap.get("UUID").toString());
							ConnectMESHDevice(currProvisionerIP, "bt_mesh=0103002a01" + tmpMap.get("UUID").toString(), true);
						}

					}else if(SettingListStr[which].toString().contains("REMOVE MESH CONNECTION")){
				    	Log.e(TAG,"REMOVE MESH CONNECTION!! MESH ADDR "+tmpMap.get("MESH_ADDR"));
						ConnectMESHDevice(currProvisionerIP, "bt_mesh=0104000e01" + tmpMap.get("MESH_ADDR").toString(), false);
						dialog.cancel();
						remove_OnClick(itemId);
//                        removeDeviceFromGROUPDevicesMap(tmpMap.get("Name").toString());
					}else if(SettingListStr[which].toString().contains("REFRESH NODE STATUS"))	{
						ConnectMESHDevice(currProvisionerIP, "bt_mesh=01050008" , true);

				    }else if(SettingListStr[which].toString().contains("LIGHT CONTROL")) {
						String lightStr = "";
						if(tmpMap.get("LIGHT").toString().contains("00"))
							lightStr = "01";
						else if(tmpMap.get("LIGHT").toString().contains("01"))
							lightStr = "00";
						ConnectMESHDevice(currProvisionerIP, "bt_mesh=0106001001" + tmpMap.get("MESH_ADDR").toString() + lightStr, true);
					}



				}
			});
		}
		
		
		dialogaction.setPositiveButton("Exit", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				dialog.cancel();
			}
		});

		dialogaction.show();
	}

    private void removeDeviceFromGROUPDevicesMap(String name){
        Iterator<HashMap<String, String>> it = bt_group_devices_map.iterator();
        for (; it.hasNext(); ) {
            HashMap<String, String> map = it.next();
Log.e(TAG,"fucking simen  name" + name +" map "+ map.toString() +" map.toString().contains(name) " + map.toString().contains(name) +  "  " +map.toString().contains(name));
            if (map.toString().contains(name)   ) {
            	String group_name = map.keySet().toString().substring(1,map.keySet().toString().length()-1);
                String devicesStr = map.get(group_name);
Log.e(TAG,"fucking bt_group_devices_map "+devicesStr+" devicesStr.contains(name) "+devicesStr.contains(name)+ " name "+name);
                if(devicesStr.contains(name+";"))
                    devicesStr = devicesStr.replace(name+";","");
                else if(devicesStr.contains(name)) {
                    devicesStr = devicesStr.replace(name, "");
                }
				Log.e(TAG,"fucking bt_group_devices_map !"+devicesStr+"!");
                if(devicesStr.isEmpty()) {
					Iterator<HashMap<String, String>> it_group_name_addr_map = group_name_addr_map.iterator();
					for (; it_group_name_addr_map.hasNext(); ) {
						HashMap<String, String> tmpMap_it_group_name_addr_map = it_group_name_addr_map.next();
						if (tmpMap_it_group_name_addr_map.toString().contains(group_name)) {
							group_name_addr_map.remove(tmpMap_it_group_name_addr_map);
						}
					}

					bt_group_name.remove(group_name);

					bt_group_devices_map.remove(map);
				}else
                	map.put(map.keySet().toString().substring(1,map.keySet().toString().length()-1),devicesStr);
            }
        }
Log.e(TAG," bt_group_devices_map "+bt_group_devices_map);
        SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(context);//this.getPreferences(MODE_PRIVATE);
        SharedPreferences.Editor editor = pref.edit();
        Gson gson = new Gson();
		String group_name_addr_map_str = gson.toJson(group_name_addr_map);
        String bt_group_devices_map_str = gson.toJson(bt_group_devices_map);

        editor.putString(DB_GROUP_NAMEADDR_MAP_TAG, group_name_addr_map_str);
        editor.putString(DB_GROUP_DEVICES_TAG,bt_group_devices_map_str);
//		if(bt_group_name.size() > 0)
			editor.putString(DB_GROUP_NAME_TAG, bt_group_name.toString().substring(1,+bt_group_name.toString().length()-1));
        editor.commit();
    }

	@SuppressLint("NewApi")
	public void rename_OnClick(String deviceName) {
		LayoutInflater factory = LayoutInflater.from(this);
		final View textEntryView = factory
				.inflate(R.layout.device_rename, null);
		final EditText edit_device_name = (EditText) textEntryView
				.findViewById(R.id.id_device_name);

		edit_device_name.setText(deviceName, TextView.BufferType.EDITABLE);
		edit_device_name.setTextSize(20);

		AlertDialog.Builder alert = new AlertDialog.Builder(DevicesMainActivity.this);
		alert.setTitle("Enter the Device Name:");
		alert.setCancelable(false);
		alert.setView(textEntryView);
		alert.setPositiveButton("Cancel",
				new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int whichButton) {

					}
				});
		alert.setNegativeButton("Save", new DialogInterface.OnClickListener() {

			@Override
			public void onClick(DialogInterface arg0, int arg1) {

				String new_deviceName = edit_device_name.getText().toString();
				if (new_deviceName.length() > 0) {

					pd = new ProgressDialog(DevicesMainActivity.this);
					pd.setTitle("Device Renaming ");
					pd.setMessage("Please wait...");
					pd.setProgressStyle(ProgressDialog.STYLE_SPINNER);
					pd.setIndeterminate(true);
					pd.setCancelable(false);
					pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel",
							new DialogInterface.OnClickListener() {
								@Override
								public void onClick(DialogInterface dialog,
										int which) {
									dialog.dismiss();
									DiscovEnable = false;
									TimesupFlag_rename = false;
									AlertDialog.Builder alert = new AlertDialog.Builder(DevicesMainActivity.this);
									alert.setCancelable(false);
									// switch password input type
									alert.setTitle("Rename Device Failed");
									alert.setCancelable(false);
									alert.setPositiveButton("OK", null);
									alert.show();
								}
							});
					pd.show();
					isControlSingleDevice = true;
					TimesupFlag_rename = false;
					new Thread() {
						public void run() {
							try {
								Thread.sleep(10000);
								isControlSingleDevice = false;
								if (TimesupFlag_rename == false) {
									runOnUiThread(new Runnable() {

										@Override
										public void run() {

											handler_pd.sendEmptyMessage(0);

											AlertDialog.Builder alert = new AlertDialog.Builder(
													DevicesMainActivity.this);
											alert.setCancelable(false);
											alert.setTitle("Rename Device Failed");
											alert.setCancelable(false);
											alert.setPositiveButton("OK", null);
											alert.show();
										}
									});
								} else {

									DiscovEnable = true;
									Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
									byte[] DiscovCmdBuf ;
									for (int i = 0; i < 15; i++) {
										Thread.sleep(200);
									}

									// Update Status
									Message msg = Message.obtain();
									msg.obj = null;

									runOnUiThread(new Runnable() {

										@Override
										public void run() {
											handler_pd.sendEmptyMessage(0);
											show_discoverDevice();
										}
									});

								}

							} catch (InterruptedException e) {
								e.printStackTrace();
							}
						};
					}.start();

				} else {
					Toast.makeText(DevicesMainActivity.this,
							"Warning: The device name is empty!",
							Toast.LENGTH_LONG).show();
				}
			}

		});
		alert.show();
	}

	public void remove_OnClick(final int itemId) {
		pd = new ProgressDialog(DevicesMainActivity.this);
		pd.setTitle("Device Removing ");
		pd.setMessage("Please wait...");
		pd.setProgressStyle(ProgressDialog.STYLE_SPINNER);
		pd.setIndeterminate(true);
		pd.setCancelable(false);
		pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel",
				new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
						DiscovEnable = false;
						isDeletedDevice = false;
					}
				});
		pd.show();

		isControlSingleDevice = true;

		new Thread() {
			public void run() {
				try {

					isControlSingleDevice = false;

					if (isDeletedDevice == true) {
						DiscovEnable = true;
						Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
						byte[] DiscovCmdBuf ;
						for (int i = 0; i < 15; i++) {
							Thread.sleep(200);
						}

						// Update Status
						Message msg = Message.obtain();
						msg.obj = null;

						runOnUiThread(new Runnable() {

							@Override
							public void run() {
								handler_pd.sendEmptyMessage(0);
								show_discoverDevice();
							}
						});

					} else {
						runOnUiThread(new Runnable() {

							@Override
							public void run() {
								String ret = "Failed";
								handler_pd.sendEmptyMessage(0);
								AlertDialog.Builder alert = new AlertDialog.Builder(
										DevicesMainActivity.this);
								alert.setCancelable(false);
								// switch password input type
								if(itemId != -1)
								{
									int i = 0;
									Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
									HashMap<String, Object> map = null;
									for (; it.hasNext(); ) {
										map = it.next();
										if(i == itemId){
											if(map.get("Type").toString().contains("Device"))
												break;
											Gson gson = new Gson();
											BroadcastDevInfo.remove(map);
											SharedPreferences db = PreferenceManager.getDefaultSharedPreferences(context);
											SharedPreferences.Editor defCollection = db.edit();
											String BDevInfoStr = gson.toJson(BroadcastDevInfo);
											defCollection.putString(DB_BROADCAST_DEVICES_TAG, BDevInfoStr);
											defCollection.commit();
//											Log.e(TAG,"popAwindow remove device "+BDevInfoStr);
											if(popDeviceListAdapter != null)
												popDeviceListAdapter.init();
											break;
										}
										i++;
									}
									show_discoverDevice();
									ret = "Successful";
									isDeletedDevice = false;
									return;
								}
								alert.setTitle("Remove Device " + ret);
								alert.setCancelable(false);
								alert.setPositiveButton("OK", null);
								alert.show();
								isDeletedDevice = false;
							}
						});
					}

				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			};
		}.start();

	}


	private List<? extends Map<String, ?>> getData_Device() {

		List<Map<String, Object>> list = new ArrayList<Map<String, Object>>();
		Map<String, Object> map;
		String tmp = "";
		int i = 0;
		if(BroadcastDevInfo.size()>0){
			DevInfo = BroadcastDevInfo;
		}else {
			DevInfo = new ArrayList<HashMap<String, Object>>();
		}
//Log.e(TAG,"getData_Device DevInfo " + DevInfo.toString());
		for (i = 0; i < DevInfo.size(); i++)
		{
			map = new HashMap<String, Object>();

			if (DevInfo.get(i).get("Name") == null) {
				map.put("title", DevInfo.get(i).get("MAC"));
				if(!DevInfo.get(i).get("Type").toString().equals("Provisioner"))
					map.put("info", DevInfo.get(i).get("MAC") + "   "
							+ DevInfo.get(i).get("Type"));
				else
					map.put("info", DevInfo.get(i).get("MAC") + "   "
							+ DevInfo.get(i).get("Status"));
			} else {

				if(!DevInfo.get(i).get("Type").toString().equals("Provisioner")) {
					map.put("info", DevInfo.get(i).get("Status"));
					String activeStr = "INACTIVE";
					if(DevInfo.get(i).get("ACTIVE").toString().contains("01"))
                        activeStr = "ONLINE";
					else
                        activeStr = "OFFLINE";
					String lightStatus="";
					if(DevInfo.get(i).get("LIGHT").toString().contains("00"))
						lightStatus = "OFF";
					else if(DevInfo.get(i).get("LIGHT").toString().contains("01"))
						lightStatus = "ON";
                    map.put("status", "MA:" + DevInfo.get(i).get("MESH_ADDR") + "  "
                            + "GA:" + DevInfo.get(i).get("GROUP_ADDR") + "  " + activeStr + "  " + "  LIGHT " + lightStatus);
                } else {
					map.put("info", DevInfo.get(i).get("MAC") + "   "
							+ DevInfo.get(i).get("Status"));
				}
				map.put("title", DevInfo.get(i).get("Name"));
			}

			if (DevInfo.get(i).get("VERSION") != null)
				map.put("VERSION", DevInfo.get(i).get("VERSION"));


//			tmp = (String) DevInfo.get(i).get("IP");
//			if (DevInfo.get(i).get("IP") != null && tmp.length() > 0)
			list.add(map);

		}

		isScanFinish = true;

		return list;
	}

	private void setListViewHeightBasedOnChildren(ListView adjuestlistView) {

		ListAdapter listAdapter = adjuestlistView.getAdapter();
		if (listAdapter == null) {
			return;
		}
		View listItem = null;
		int totalHeight = 0;

		listItem = listAdapter.getView(0, null, adjuestlistView);
		listItem.measure(0, 0);
		totalHeight = listItem.getMeasuredHeight() * listAdapter.getCount();

		ViewGroup.LayoutParams params = adjuestlistView.getLayoutParams();
		params.height = totalHeight
				+ (adjuestlistView.getDividerHeight() * (listAdapter.getCount() - 1));
		adjuestlistView.setLayoutParams(params);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		// getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}


	@Override
	int getContentViewId() {
		return R.layout.activity_devices;
	}

	@Override
	int getNavigationMenuItemId() {
		return R.id.navigation_dashboard;
	}
}
