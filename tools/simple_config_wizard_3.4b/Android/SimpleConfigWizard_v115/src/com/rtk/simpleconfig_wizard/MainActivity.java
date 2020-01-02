package com.rtk.simpleconfig_wizard;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.rtk.simpleconfig_wizard.ConfigurationDevice.DeviceInfo;
import com.realtek.simpleconfiglib.SCLibrary;
import com.wifi.connection.ConfigurationSecuritiesV8;
import com.wifi.connection.Wifi;
import com.zxing.activity.CaptureActivity;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
//import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.Process;
import android.os.SystemClock;
import android.provider.Settings;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.text.InputType;
//import android.text.format.Time;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.RadioGroup;
import android.widget.SimpleAdapter;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	public enum SECURITY_TYPE {
		SECURITY_NONE,
		SECURITY_WEP,
		SECURITY_PSK,
		SECURITY_EAP
	}
	
	private static final String pwfileName 		= "preAPInfoFile";
	private static final String pinfileName 	= "prePINFile";
	private static final String TAG 			= "<simple config wizard>";
	private static final String defaultPINcode 	= "";
	private static final String backdoor_PINCODE= "00000000";
	private static final String aboutMsg 		= "uncheck device if any unwanted";
	
	private static final int discoveryTimeout 	= 3000; //3s
	private static final int configTimeout 		= 120000;//120s
	private static final int deviceNumber 		= 32;
	private static final int APNumber 			= 100;
	
	private int CurrentItem;
	private String CurrentControlIP;
	private String QRCodeScanResult;
	
	//global
	TextView textConfigDeviceTitle;
	ListView listView;
	EditText edittxt_PINcode;
	View wifiPW_EntryView;
	LayoutInflater factory;
	
	String pinCodeText = "";
	String presave_pinCode = "";//pre file saved
	String ssid_name = "";
	String AP_password = "";
	String[] delConfirmIP;
	
	boolean ConnectAPProFlag = false;//user need to connect ap
	boolean ConfigureAPProFlag = false;//user need to connect ap
	boolean isWiFiEnable = false;
	boolean DiscovEnable = false;
	boolean isDeletedDevice = false;
	boolean isControlSingleDevice = false;
	boolean TimesupFlag_cfg = true;
	boolean TimesupFlag_rename = false;
	boolean TimesupFlag_remove = false;
	boolean ShowCfgSteptwo = false;

	private int mSingleChoiceID  = -1;
	private String PINGet = null;
	private String PINSet = null;
	private SimpleAdapter adapter_deviceInfo;
	private ProgressDialog pd;
	
	private List<HashMap<String, Object>> DevInfo;
	private List<HashMap<String, Object>> wifiArrayList = new ArrayList<HashMap<String, Object>>();
	private ScanResult mScanResult;
	private List<ScanResult> mScanResults;
	
	private boolean WifiConnected = false;
	protected WifiManager mWifiManager;
	
	AlertDialog 		APList_alert;
	AlertDialog.Builder APList_builder;
	DeviceInfo [] configuredDevices;
	DeviceInfo [] APInfo;
	DeviceInfo SelectedAPInfo;
	DeviceInfo[] deviceList;

	Thread connectAPThread = null;
	Thread backgroundThread = null;
	
	// handler for the background updating
    Handler progressHandler = new Handler() {
        public void handleMessage(Message msg) {
            pd.incrementProgressBy(1);
        }
    };
	
	Handler handler_pd = new Handler(){
    	@Override
    	public void handleMessage(Message msg) {
    		//Log.d(TAG,"handleMessage msg.what: " + String.valueOf(msg.what));
    		switch(msg.what) {
    		case 0:
				pd.dismiss();
    			break;
    		case 1:
    			int timeout = 10;
    			int coutDown = timeout;
    			
    			while( coutDown>0 ) {

        			try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
        			coutDown--;
        			if(coutDown==0){
        				pd.dismiss();
        			}
    			}
    			
    			break;
    			
    		default:
    				break;
    		}
    	}

    };
	
    private SCLibrary SCLib = new SCLibrary();
    private FileOps fileOps = new FileOps();

    static {
        System.loadLibrary("simpleconfiglib");
    }
    
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, 
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		setContentView(R.layout.activity_main);
		
		//Log.i(TAG,"system bit: " + System.getProperty("os.arch"));
		
		//simple config lib init
		SCLib.rtk_sc_init();
		SCLib.TreadMsgHandler = new MsgHandler();
		
		//wifi manager init
		SCLib.WifiInit(this);
		fileOps.SetKey(SCLib.WifiGetMacStr());
		
		initData();
		initComponent();
		
		initComponentAction();
		
		mWifiManager = (WifiManager)getSystemService(WIFI_SERVICE);
		
	}

	protected void onStart()
	{
		super.onStart();
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		SCLib.rtk_sc_exit();
		SCCtlOps.ConnectedSSID = null;
		SCCtlOps.ConnectedPasswd = null;
		DiscovEnable = false;
	}
	
	private void initData() 
	{
		configuredDevices = new DeviceInfo[deviceNumber];
		for(int i=0;i<deviceNumber;i++)
        {        	
			configuredDevices[i] = new DeviceInfo();
			configuredDevices[i].setaliveFlag(1);
			configuredDevices[i].setName("");
			configuredDevices[i].setIP("");
			configuredDevices[i].setmacAdrress("");
			configuredDevices[i].setimg(null);
			configuredDevices[i].setconnectedflag(false);
        }
		
		APInfo = new DeviceInfo[APNumber];
		for(int i=0;i<APNumber;i++){
			APInfo[i] = new DeviceInfo();
		}
		
		SelectedAPInfo = new DeviceInfo();
		APList_Clear();
		
		
		SCCtlOps.ConnectedSSID = null;
		SCCtlOps.ConnectedPasswd = null;
	}
	
	private void initComponent() 
	{
		
		
		DisplayMetrics metrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(metrics);
		//int s_height = metrics.heightPixels;
		//int s_width = metrics.widthPixels;
		//Log.d(TAG, "initComponent: " + String.valueOf(s_height));
		//Log.d(TAG, "initComponent: " + String.valueOf(s_width));
		
		textConfigDeviceTitle = (TextView)findViewById(R.id.textDeviceTitle);
		listView              = (ListView)findViewById(R.id.listView1);
		listView.setBackgroundColor(0xFFE6E6E2);
	}

	@SuppressLint("SdCardPath")
	private void initComponentAction()
	{
		//scan configured devices
		SCCtlOps.rtk_sc_control_reset();
		
		ConnectivityManager connManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
		if(mWifi.isConnected())
		{
			DiscovEnable = true;	
			DiscoveryDevice(discoveryTimeout);
			show_discoverDevice();
		}
		
	}
	
	private void DiscoveryDevice(final int counts) 
	{

		pd = new ProgressDialog(MainActivity.this);
		
		pd.setTitle("Scan Configured Devices by " + SCLib.getConnectedWifiSSID());
		
		pd.setMessage("Discovering devices ...");
		pd.setProgressStyle(ProgressDialog.STYLE_SPINNER);
		pd.setIndeterminate(true);
		pd.setCancelable(false);
		pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel", new DialogInterface.OnClickListener() {
		    @Override
		    public void onClick(DialogInterface dialog, int which) {
		        dialog.dismiss();
		        DiscovEnable = false;
		    }
		});
		pd.show();
		
		new Thread(new Runnable(){
    		public void run() {
    			Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
    			byte[] DiscovCmdBuf = SCCtlOps.rtk_sc_gen_discover_packet(SCLib.rtk_sc_get_default_pin());
    			long startTime = System.currentTimeMillis();
    			long endTime = System.currentTimeMillis();
    			while(DiscovEnable && (endTime-startTime)<counts) {
    				
    				try {
						Thread.sleep(200);
						SCLib.rtk_sc_send_discover_packet(DiscovCmdBuf, "255.255.255.255");
						//Log.d(TAG,"scan-discovery: 255.255.255.255");
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
        		 	
        			endTime = System.currentTimeMillis();
    			}
    			handler_pd.sendEmptyMessage(0);
    			Log.i(TAG, "Discover Time Elapsed: " + (endTime-startTime) + "ms");

				// Update Status
				Message msg = Message.obtain();
				msg.obj = null;
				msg.what = ~SCCtlOps.Flag.DiscoverACK; //timeout
				SCLib.TreadMsgHandler.sendMessage(msg);
    		}
    	}).start();
	}

	private void APList_Clear()
	{
		for(int i=0;i<APNumber;i++)
		{
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
	
	//<func>
	private boolean show_discoverDevice()
	{
		adapter_deviceInfo = new SimpleAdapter(this, getData_Device(),
				R.layout.device_list, new String[] { "title", "info" },
				new int[] { R.id.title, R.id.info });
		listView.setAdapter(adapter_deviceInfo);
		if (adapter_deviceInfo.getCount() > 0)
			setListViewHeightBasedOnChildren(listView);
		else if (adapter_deviceInfo.getCount() == 0) {
			listView.setAdapter(null);
		}
		
		listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> parent, View view, int itemId,
					long arg3) {
				
				ListView listView_parent = (ListView) parent;
				listView_parent.setTag(view);
				
				String []tmp = listView_parent.getItemAtPosition(itemId).toString().split("title=");
				String tmp1 = tmp[1];
				String []deviceName = tmp1.split(",");
				
				tmp = listView_parent.getItemAtPosition(itemId).toString().split("info=");
				String macAddress = tmp[1];
				macAddress = macAddress.replaceFirst("\\}","");
				
				CurrentItem = itemId;
		    	CurrentControlIP = (String)DevInfo.get(CurrentItem).get("IP");
		    	ControlPINcode(deviceName[0],(String)DevInfo.get(CurrentItem).get("MAC"));

			}
		});
		return true;
	}

	public void ScanDevices_OnClick(View view)
	{
		SCCtlOps.rtk_sc_control_reset();
		
		ConnectivityManager connManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
		if(mWifi.isConnected())
		{
			DiscovEnable = true;		
			DiscoveryDevice(discoveryTimeout);
			show_discoverDevice();
		}else{
			Toast toast = Toast.makeText(MainActivity.this, 
					"Please connect the home AP"
					,Toast.LENGTH_LONG);
			toast.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM, 0, 100);
			LinearLayout toastLayout = (LinearLayout) toast.getView();
			TextView toastTV = (TextView) toastLayout.getChildAt(0);
			toastTV.setTextSize(15);
			toast.show();
		}

	}
	
	//<func>
	public void configNewDevice_OnClick(View view)
	{

		int i = 0,j = 0;
		int itmeNum = 0;
		
		mSingleChoiceID = -1;
		WifiManager wifi = (WifiManager)getSystemService(Context.WIFI_SERVICE);
		
		//check wifi is disable
		if(!wifi.isWifiEnabled()) {
			//OpenWifiPopUp();
			SCLib.WifiOpen();
			
			do{
 				SystemClock.sleep(1000);
 				wifi = (WifiManager)getSystemService(Context.WIFI_SERVICE);
				//Log.d(TAG, "Turn on Wi-Fi wait");
 			}while(!wifi.isWifiEnabled()); //check again if it is disable
			SystemClock.sleep(2500);
		}
		
		//Log.d(TAG, "Turn on Wi-Fi ok");
		
		Toast toast = Toast.makeText(MainActivity.this, 
				"Choose the AP in order to add new devicess in wireless network"
				,Toast.LENGTH_LONG);
		toast.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM, 0, 100);
		LinearLayout toastLayout = (LinearLayout) toast.getView();
		TextView toastTV = (TextView) toastLayout.getChildAt(0);
		toastTV.setTextSize(15);
		toast.show();
		
		SCLib.WifiStartScan();
		try {
			Thread.sleep(800);
		} catch (InterruptedException e1) {
			e1.printStackTrace();
		}
		
		GetAllWifiList();
		
		fileOps.SetKey(SCLib.WifiGetMacStr());
		
		APList_builder=new AlertDialog.Builder(MainActivity.this);
		
		LayoutInflater inflater=LayoutInflater.from(getApplicationContext());
		View customTitle=inflater.inflate(R.layout.customtitlebar, null);
		APList_builder.setCustomTitle(customTitle);
		
		APList_builder.setCancelable(false);

		itmeNum = 0;
		for(int num=0;num<mScanResults.size();num++){
			if(num>=APNumber)
				break;
			if(APInfo[num].getaliveFlag()==1)
				itmeNum++;
		}
    	deviceList = new DeviceInfo[itmeNum];
    	//Log.d(TAG, "configNewDevice_OnClick itmeNum:" + String.valueOf(itmeNum));
    	for (i=0; i<itmeNum; i++) {
    		if(i<APNumber){
    			if(APInfo[i].getaliveFlag()==1 && APInfo[i]!=null){
        			deviceList[i] = new DeviceInfo();
        			deviceList[i] = APInfo[i];
        	    	//Log.d(TAG, "configNewDevice_OnClick" + String.valueOf(i));
        		}
    		}
    	}

    	//sort by name
    	DeviceInfo tmpDevice = new DeviceInfo();
    	for(i=0;i<itmeNum;i++)
    	{
    		tmpDevice = deviceList[i];
    		//Log.d(TAG, itmeNum + " ap ssid: " + tmpDevice.getName());
    		for(j=i-1 ; j>=0 && deviceList[j].getName().compareToIgnoreCase(tmpDevice.getName())>0 ; j--){
    			deviceList[j+1] = deviceList[j];
    		}
    		deviceList[j+1] = tmpDevice;
    		
    	}
    	/*for(i=0;i<itmeNum;i++)
        {
			 for(j=0;j<itmeNum-1;j++)
			 {
				 if(deviceList[j]!=null && deviceList[j+1]!=null){
					 if( deviceList[j].getName().compareToIgnoreCase( deviceList[j+1].getName() ) > 0)
				     {
					   tmpDevice = deviceList[j];
					   deviceList[j] = deviceList[j+1];
					   deviceList[j+1] = tmpDevice;
				     }
				 }
			 }
        }*/
    	
    	//set foucs connect item
    	int foucsIndex = 0;
    	if(WifiConnected==true){
     		
        	if(foucsIndex >= 0){

        		for(j=0;j<itmeNum;j++){

        			if( deviceList[j].getName().equals( SelectedAPInfo.getName() )){
        				foucsIndex = j;
        				//Log.d(TAG, "configNewDevice_OnClick() ===foucsIndex"+String.valueOf(foucsIndex));  
        				break;
        			}
        		}
        	}
    	}else{
    		foucsIndex = 0;
    	}
    	
    	SCCtlOps.isHiddenSSID = false;
    	
    	final ImageView addNetworkkBtn=(ImageView)customTitle.findViewById(R.id.addNewNetworkBtn);
    	addNetworkkBtn.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				SCCtlOps.addNewNetwork = true;

				addNetworkPopup();
			}
    		
    	});
    	SCCtlOps.addNewNetwork = false;
    	ListAdapter adapter = new DeviceAdapter(MainActivity.this,deviceList);
    	
    	APList_builder.setSingleChoiceItems( adapter, foucsIndex,new OnClickListener(){

			@Override
			public void onClick(DialogInterface dialog, int which) {
				// no use "which" due to sort name
				
				//convert to origin index
				mSingleChoiceID = which;
				
				fileOps.ParseSsidPasswdFile(deviceList[which].getName());
				dialog.dismiss();
				
				SCCtlOps.ConnectedSSID = deviceList[which].getName();
				
				//check password of the APInfo[mSingleChoiceID]
				//boolean isPasswordExist = false;
				String content="";
	    		byte[] buff = new byte[256]; //input stream buffer
	    		try {
	    			FileInputStream reader = openFileInput(pwfileName);
	    			while((reader.read(buff))!=-1){
	    				content+=new String(buff).trim();
	    			}
	    			reader.close();
	    		} catch (FileNotFoundException e) {
	    			e.printStackTrace();
	    			Log.e("deviceinfo FileNotFoundException", content);
	    		} catch (IOException e) {
	    			Log.e("deviceinfo IOException", content);
	    		}
	    		//Log.d(TAG, "APinfo:" + content);
	    		SCCtlOps.ConnectedPasswd = "";
	    		AP_password = "";
	    		if(content.length()>0){
	    			String[] APitem = content.split(";");
	    			for (String splitString:APitem){
	    				String[] array = splitString.split(",");
	    				if( deviceList[which].getName().equals(array[0]) == true){//ssid is the same
	    					
	    					if(array.length>1)
	    						AP_password	= array[1];
	    					else
	    						AP_password	= "";
	    					
	    					SCCtlOps.StoredPasswd = AP_password;
	    					SCCtlOps.ConnectedPasswd = SCCtlOps.StoredPasswd;
	   						
	    					//isPasswordExist = true;
	    					break;
	    				}
	    			}
	    		}
	    		
	    		//check it if it need password

				if(deviceList[which].getsecurityType()==0){//connect directly
					//do connect ap action
					AP_password = "";
					ConnectAPProFlag = true;
					
					pd = new ProgressDialog(MainActivity.this);
					pd.setTitle("Connecting");
					pd.setMessage("Please wait...");
					pd.setIndeterminate(true);
					pd.setCancelable(false);
					pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel", new DialogInterface.OnClickListener() {
					    @Override
					    public void onClick(DialogInterface dialog, int which) {
					        dialog.dismiss();
					        ConnectAPProFlag = false;
					    }
					});
					pd.show();
					
					connectAPThread = new Thread() {
			    		@Override
						public void run() {

				    			try {
									if( connect_action(mSingleChoiceID) == true){

										handler_pd.sendEmptyMessage(0);
										//Log.d(TAG, "connect AP: "+ APInfo[mSingleChoiceID].getName()+ "success");
										runOnUiThread(new Runnable() {
											@Override
											public void run() {

												if(ConnectAPProFlag == true){
													//show "start to configure"
													ConfigPINcode();
													ConnectAPProFlag = false;
												}
											}
										});
									}else{
										if(ConnectAPProFlag != false){
											Log.e(TAG, "connect AP:" + SelectedAPInfo.getName() + "fail");
											
											runOnUiThread(new Runnable() {
												@Override
												public void run() {
													AlertDialog.Builder errorAlert=new AlertDialog.Builder(MainActivity.this);

													errorAlert.setTitle("Connect the AP Fail");
													errorAlert.setMessage("Please check the password or other problem.\nYou can go to System Settings/Wi-Fi, select the Wi-Fi network!");
													errorAlert.setPositiveButton("OK",new DialogInterface.OnClickListener() {

														@Override
														public void onClick(DialogInterface arg0,int arg1) {
															startActivityForResult(new Intent(android.provider.Settings.ACTION_WIFI_SETTINGS), 0);
															
														}});
													errorAlert.show();
												}
											});
										}
										handler_pd.sendEmptyMessage(0);
									}
								} catch (InterruptedException e) {
									e.printStackTrace();
								}
				    	}
			    	};
			    	connectAPThread.start();
					
				}else{//ask user to key in password
					LayoutInflater factory = LayoutInflater.from(MainActivity.this);
					final View wifiPW_EntryView = factory.inflate(R.layout.wifi_password_entry, null);
					final EditText edittxt_apPassword = (EditText) wifiPW_EntryView.findViewById(R.id.id_ap_password);
					CheckBox password_checkbox;
					password_checkbox = (CheckBox)wifiPW_EntryView.findViewById(R.id.checkBox_password);
					
					if(AP_password.length()>0)
						edittxt_apPassword.setText(AP_password, TextView.BufferType.EDITABLE);
					else
						edittxt_apPassword.setText("", TextView.BufferType.EDITABLE);
					
					password_checkbox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()  {

						@Override
						public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

							if(isChecked)
								edittxt_apPassword.setInputType(InputType.TYPE_TEXT_VARIATION_PASSWORD);
							else
								edittxt_apPassword.setInputType(129);
						}
						
					});
					
					AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
					alert.setCancelable(false);
					//switch password input type
						alert.setTitle("Enter the AP password:");
					    alert.setCancelable(false);
					    alert.setView(wifiPW_EntryView);
					    alert.setPositiveButton("Cancel", 
					        new DialogInterface.OnClickListener() {
				            public void onClick(DialogInterface dialog, int whichButton) {

				            }
				        });
					    alert.setNegativeButton("Connect",
	    			    		new DialogInterface.OnClickListener() {

	    						@Override
	    						public void onClick(DialogInterface arg0, int arg1) {

	    							//Log.d(TAG, "AP Password:" + edittxt_apPassword.getText().toString());
	    							
	    							//AP_password;
	    							if(edittxt_apPassword.getText().toString().length() > 0){
	    								AP_password = edittxt_apPassword.getText().toString();
	    							}else{
	    								AlertDialog.Builder msgAlert=new AlertDialog.Builder(MainActivity.this);
	    								msgAlert.setTitle("Error");
	    								msgAlert.setMessage("Please check the password!\n");
	    								msgAlert.setPositiveButton("OK", null);
	    								msgAlert.show();
	    								return;
	    							}
	    							
	    							//do connect ap action
	    							ConnectAPProFlag = true;
	    							
	    							pd = new ProgressDialog(MainActivity.this);
	    							pd.setTitle("Connecting");
	    							pd.setMessage("Please wait...");
	    							pd.setIndeterminate(true);
	    							pd.setCancelable(false);
	    							pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel", new DialogInterface.OnClickListener() {
	    							    @Override
	    							    public void onClick(DialogInterface dialog, int which) {
	    							        dialog.dismiss();
	    							        ConnectAPProFlag = false;
	    							    }
	    							});
	    							pd.show();
	    							
	    							connectAPThread = new Thread() {
	    					    		@Override
	    								public void run() {

	    						    			try {
													if( connect_action(mSingleChoiceID) == true){

														//Log.d(TAG, "connect AP: " + APInfo[mSingleChoiceID].getName()+ "sucess");
														runOnUiThread(new Runnable() {
															@Override
															public void run() {

																if(ConnectAPProFlag == true){
																	//show "start to configure"
																	ConfigPINcode();
																	ConnectAPProFlag = false;
																}
															}
														});
														
													}else{
														if(ConnectAPProFlag != false){
															//Log.e(TAG, "connect AP: "+APInfo[mSingleChoiceID].getName()+ "fail");
															
															runOnUiThread(new Runnable() {
																@Override
																public void run() {
																	AlertDialog.Builder errorAlert=new AlertDialog.Builder(MainActivity.this);

																	errorAlert.setTitle("Connect the AP Fail");
																	errorAlert.setMessage("Please check the password or other problem.\nYou can go to System Settings/Wi-Fi, select the Wi-Fi network!");
																	errorAlert.setPositiveButton("OK",new DialogInterface.OnClickListener() {

																		@Override
																		public void onClick(DialogInterface arg0,int arg1) {
																			startActivityForResult(new Intent(android.provider.Settings.ACTION_WIFI_SETTINGS), 0);
																			
																		}});
																	errorAlert.show();
																}
															});
														}
														handler_pd.sendEmptyMessage(0);
													}
												} catch (InterruptedException e) {
													e.printStackTrace();
												}
	    						    	}
	    					    	};
	    					    	connectAPThread.start();
	    						}
	    				    	
	    				    });
	    				    
	    				    alert.show();
				}
				
				
			}
    		
    	});

    	APList_builder.setPositiveButton("Cancel", null);
    	
    	APList_alert = APList_builder.create();
    	APList_alert.show();
	}
	
	private void addNetworkPopup()
	{
		if(APList_alert!=null){
			APList_alert.cancel();
		}

		
		LayoutInflater inflater = getLayoutInflater();
		View addNetworkView = inflater.inflate(R.layout.add_network_content,
		     (ViewGroup)findViewById(R.id.add_network_dialog));

		final EditText network_name_edit;
		final EditText network_pw_edit;
		final Spinner  encrypt_type_spinner;
		final ArrayAdapter<String> encrypt_adapter;
		final String[] encryption_types = {"NONE", "WEP", "WAPI", "WPA-PSK", "WPA2-PSK", "WPA_EAP"};
		CheckBox password_checkbox;
		

		network_name_edit = (EditText)addNetworkView.findViewById(R.id.network_name_edit);
		network_pw_edit   = (EditText)addNetworkView.findViewById(R.id.id_ap_password);
		password_checkbox = (CheckBox)addNetworkView.findViewById(R.id.checkBox_password);

		encrypt_type_spinner = (Spinner)addNetworkView.findViewById(R.id.encrypt_type);
		encrypt_adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, encryption_types);
		encrypt_adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		encrypt_type_spinner.setAdapter(encrypt_adapter);
		encrypt_type_spinner.setOnItemSelectedListener(null);
		encrypt_type_spinner.setVisibility(View.VISIBLE);

		password_checkbox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()  {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

				if(isChecked)
					network_pw_edit.setInputType(InputType.TYPE_TEXT_VARIATION_PASSWORD);
				else
					network_pw_edit.setInputType(129);
			}
			
		});

	 	AlertDialog.Builder builder = new AlertDialog.Builder(this);
	 	builder.setTitle("Add new network:")
	 	.setIcon(R.drawable.ic_dialog_icon)
	 	.setView(addNetworkView)
	 	.setNegativeButton("OK", new DialogInterface.OnClickListener() {
	 		@Override
	 		public void onClick(DialogInterface dialog, int id) {
	 			ssid_name = network_name_edit.getText().toString();
	 			AP_password      = network_pw_edit.getText().toString();
	 			final String encrypt_type = encrypt_type_spinner.getSelectedItem().toString();
	 			SCCtlOps.isHiddenSSID = true;
//	 			Log.d(TAG, "network_name_edit: " + ssid_name);
//	 			Log.d(TAG, "encrypt_type: " + encrypt_type);
//	 			Log.d(TAG, "is_hidden_ssid: " + SCCtlOps.isHiddenSSID);
	 			
	 			/*if(encrypt_type.equals("NONE")) {
	 				encrypt_type = "";
	 			} else {
	 				encrypt_type = "[" + encrypt_type + "]";
	 			}
	 			Log.d(TAG, "encrypt_type: " + encrypt_type);*/
	 			ConnectAPProFlag = true;
	 			pd = new ProgressDialog(MainActivity.this);
				pd.setTitle("Connecting");
				pd.setMessage("Please wait...");
				pd.setIndeterminate(true);
				pd.setCancelable(false);
				pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel", new DialogInterface.OnClickListener() {
				    @Override
				    public void onClick(DialogInterface dialog, int which) {
				        dialog.dismiss();
				        ConnectAPProFlag = false;
				    }
				});
				pd.show();
	 			
				connectAPThread = new Thread(){
	 				public void run(){
	 					
	 					String jsonSsidStr = "{" +
	 		 					"\"SSID\":\"" + ssid_name + "\"" +
	 		 					",\"BSSID\":\"" + "\"" +
	 		 					",\"capabilities\":\"" + encrypt_type + "[ESS]\"" +
	 		 			    	",\"level\":" + 0 +
	 		 			    	",\"frequency\":" + 0 +
	 		 			    	"}";
	 		 			
	 		   	 		Log.d(TAG, "jsonSsidStr: " + jsonSsidStr + " pw:"+AP_password);
	 		 			Gson gson = new Gson();
	 		 			SCCtlOps.reBuiltScanResult = gson.fromJson(jsonSsidStr,
	 		 									new TypeToken<ScanResult>(){}.getType());

//	 		 			Log.i(TAG, "reBuiltScanResult: " + SCCtlOps.reBuiltScanResult);
//	 		 			Log.d(TAG, "reBuiltScanResult.SSID: " + SCCtlOps.reBuiltScanResult.SSID);
//	 		 			Log.d(TAG, "reBuiltScanResult.BSSID: " + SCCtlOps.reBuiltScanResult.BSSID);
//	 		 			Log.d(TAG, "reBuiltScanResult.capabilities: " + SCCtlOps.reBuiltScanResult.capabilities);
//	 		 			Log.d(TAG, "reBuiltScanResult.level: " + SCCtlOps.reBuiltScanResult.level);
//	 		 			Log.d(TAG, "reBuiltScanResult.frequency: " + SCCtlOps.reBuiltScanResult.frequency);

	 					//launchWifiConnecter(MainActivity.this,SCCtlOps.reBuiltScanResult);
	 					
	 					//String security = Wifi.ConfigSec.getScanResultSecurity(SCCtlOps.reBuiltScanResult);
	 					@SuppressWarnings("deprecation")
						int mNumOpenNetworksKept =  Settings.Secure.getInt(MainActivity.this.getContentResolver(),
	 				            Settings.Secure.WIFI_NUM_OPEN_NETWORKS_KEPT, 10);
	 					boolean connResult = false;
	 					connResult = Wifi.connectToNewNetwork(MainActivity.this, mWifiManager
	 							, SCCtlOps.reBuiltScanResult
	 							, AP_password
	 							, mNumOpenNetworksKept);
	 					
	 					Log.d(TAG, "connResult: " + String.valueOf(connResult));
	 					
	 					//check wifi connected
	 					WifiManager wifiManager = (WifiManager) MainActivity.this.getSystemService(Context.WIFI_SERVICE);
	 					WifiInfo wifiInfo = wifiManager.getConnectionInfo();
	 					ConnectivityManager connManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
	 					NetworkInfo mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
	 					String connected_ssid = "";
	 					int retry = 60;
	 					do{
	 						
	 						try {
	 							Thread.sleep(500);
	 							wifiInfo = wifiManager.getConnectionInfo();
	 							mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
	 							if (WifiInfo.getDetailedStateOf(wifiInfo.getSupplicantState()) == NetworkInfo.DetailedState.CONNECTED || mWifi.isConnected()) {
	 								connected_ssid = wifiInfo.getSSID();
	 								if(connected_ssid.indexOf("\"")==0)
	 									connected_ssid = connected_ssid.substring(1, connected_ssid.length()-1);
	 							}
	 						} catch (InterruptedException e) {
	 							e.printStackTrace();
	 						}
	 						Log.d(TAG,"wifi connect :"+connected_ssid);
	 					}while(!ssid_name.equals(connected_ssid) && retry-- > 0 );
	 					
	 					//wait for android system 
	 					try {
							Thread.sleep(2000);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
	 					
	 					if(ConnectAPProFlag == true)
	 					{
	 						handler_pd.sendEmptyMessage(0);
	 						ConnectAPProFlag = false;
	 					}

	 					if(retry>0){
	 						runOnUiThread(new Runnable() {
								@Override
								public void run() {
									configNewDevice_OnClick(null);
								}
							});
	 					}else{
	 						runOnUiThread(new Runnable() {
								@Override
								public void run() {
									AlertDialog.Builder errorAlert=new AlertDialog.Builder(MainActivity.this);

									errorAlert.setTitle("Connect the AP Fail");
									errorAlert.setMessage("Please check the password or other problem.\nYou can go to System Settings/Wi-Fi, select the Wi-Fi network!");
									errorAlert.setPositiveButton("OK",new DialogInterface.OnClickListener() {

										@Override
										public void onClick(DialogInterface arg0,int arg1) {
											startActivityForResult(new Intent(android.provider.Settings.ACTION_WIFI_SETTINGS), 0);
											
										}});
									errorAlert.show();
								}
							});
	 					}
	 						
	 				};

	 			};
				connectAPThread.start();
				
            }
	 	})
	 	.setPositiveButton("Cancel", new DialogInterface.OnClickListener() {
	 		@Override
	 		public void onClick(DialogInterface dialog, int id) {
	 			dialog.cancel();
            }
	 	});
	 	builder.show();
	}
	
	/*protected boolean launchWifiConnecter(ScanResult scanResult) {
		WifiManager wifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
		
		ShowCfgSteptwo = true;

		if(!wifiManager.isWifiEnabled()){
			if(wifiManager.getWifiState() != WifiManager.WIFI_STATE_ENABLING)
				wifiManager.setWifiEnabled(true);
		}
		
		conf.setupSecurity(wifiConfig, conf.getScanResultSecurity(scanResult),AP_password);

		wifiConfig.SSID = "\"" + scanResult.SSID + "\"";
		wifiConfig.priority = getMaxPriority(wifiManager) + 1;

		//Log.d("=======connect AP=======","Security type: " +conf.getScanResultSecurity(scanResult));
		
		// Dependent on the security type of the selected network
	    // we set the security settings for the configuration
		int networkId = wifiManager.addNetwork(wifiConfig);

		if (networkId == -1)
			return false;

		if (!wifiManager.saveConfiguration())
			return false;

		wifiManager.disconnect();
		wifiManager.reconnect();
		
		boolean active = wifiManager.enableNetwork(networkId, true);
        
        
        //Log.d("=======connect AP=======","enableNetwork: " +String.valueOf(active));
        
        ConnectivityManager connManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo mWifi = null;

        int retry = 0;
        try {
	        do {
					Thread.sleep(500);
					mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
				
	        	retry++;
	        	Log.d("=======connect AP=======","wait"+ String.valueOf(retry));
	        	
	        }while(mWifi.isConnected() == false && retry<=60);
        
        } catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		
		return true;
	}*/

	private void GetAllWifiList() 
	{
		
		ConnectivityManager connManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
		
		String tmp = "";
		String connected_ssid = "";
		String connected_bssid = "";
		String connected_ip = "";
		WifiConnected = false;
		
		WifiManager wifiManager = (WifiManager) MainActivity.this.getSystemService(Context.WIFI_SERVICE);
		WifiInfo wifiInfo = wifiManager.getConnectionInfo();
		if (WifiInfo.getDetailedStateOf(wifiInfo.getSupplicantState()) == NetworkInfo.DetailedState.CONNECTED || mWifi.isConnected()) {
			
			connected_ssid = wifiInfo.getSSID();
			connected_bssid= wifiInfo.getBSSID();
			if(connected_ssid.indexOf("\"")==0)
				tmp = connected_ssid.substring(1, connected_ssid.length()-1);
			else
				tmp = connected_ssid;
			int myIp = wifiInfo.getIpAddress();     
			int intMyIp3 = myIp/0x1000000;
			int intMyIp3mod = myIp%0x1000000;

			int intMyIp2 = intMyIp3mod/0x10000;
			int intMyIp2mod = intMyIp3mod%0x10000;

			int intMyIp1 = intMyIp2mod/0x100;
			int intMyIp0 = intMyIp2mod%0x100;
			   
			connected_ip = String.valueOf(intMyIp0) 
					+ "." + String.valueOf(intMyIp1)
                    + "." + String.valueOf(intMyIp2)
                    + "." + String.valueOf(intMyIp3);
			
			WifiConnected = true;
			Log.i(TAG,"Connected AP:"+tmp);
		}
		
		mScanResults = SCLib.WifiGetScanResults();
		//Log.d(TAG, "mScanResults: "+ String.valueOf(mScanResults.size()) );
		
		APList_Clear();
		wifiArrayList.clear();
		
		if(mScanResults!=null){
			
			boolean checkSameSSID = false;
			
			int i = 0;
			
			for(int iScan=0; iScan<mScanResults.size() && i<APNumber; iScan++)
			{
				checkSameSSID = false;
				if(iScan<APNumber){
					mScanResult = mScanResults.get(iScan);
					//Log.d(TAG, "AP"+String.valueOf(i)  +" : " + mScanResult.SSID + "("+ mScanResult.capabilities+")" + String.valueOf(mScanResult.level));
				}else
					continue;

				if(mScanResult.SSID.length()==0)continue;
				
				for(int numAP=0;numAP<APNumber;numAP++){
					if(APInfo[numAP].getaliveFlag()==1){
						if(mScanResult.SSID.equals(APInfo[numAP].getName()))
							checkSameSSID = true;
					}
				}
				if(checkSameSSID){
					Log.d(TAG,"checkSameSSID");
					continue;
				}else
				{
					
					if((SCCtlOps.ConnectedSSID!=null) &&
		    				(SCCtlOps.ConnectedSSID.length()>0) &&
		    				(SCCtlOps.ConnectedSSID.equals(mScanResult.SSID)) &&
		    				SCLib.isWifiConnected(SCCtlOps.ConnectedSSID)){
						//Log.d(TAG, "AP"+String.valueOf(i)  +" : " + mScanResult.SSID );
					}
					
					//Log.d(TAG,"=====================");
					//Log.d(TAG,"mScanResult.SSID:" + mScanResult.SSID);
					//Log.d(TAG,"mScanResult.SSID len:" + mScanResult.SSID.getBytes().length);
					//Log.d(TAG,String.valueOf(getSecurity(mScanResult)));
					//Log.d(TAG,mScanResult.capabilities);
					
					//APInfo[i].setsecurityType(mScanResult.capabilities);
					APInfo[i].setsecurityType(getSecurity(mScanResult));
					APInfo[i].setaliveFlag(1);
					APInfo[i].setName(mScanResult.SSID);
					APInfo[i].setmacAdrress(mScanResult.BSSID);
					APInfo[i].setconnectedflag(false);
					APInfo[i].setIP("");
					
					if(mScanResult.level>-50)
						APInfo[i].setimg(getResources().getDrawable(R.drawable.signal5));
					else if(mScanResult.level>-60)
						APInfo[i].setimg(getResources().getDrawable(R.drawable.signal4));
					else if(mScanResult.level>-70)
						APInfo[i].setimg(getResources().getDrawable(R.drawable.signal3));
					else if(mScanResult.level>-80)
						APInfo[i].setimg(getResources().getDrawable(R.drawable.signal2));
					else
						APInfo[i].setimg(getResources().getDrawable(R.drawable.signal1));
					
					//tmp = "\"" + mScanResult.SSID + "\"";
					if(WifiConnected == true){
						if( connected_bssid.equals(APInfo[i].getmacAdrress()) &&
								APInfo[i].getName().length() > 0 ){
							APInfo[i].setIP(connected_ip);
							APInfo[i].setconnectedflag(true);
							
							SelectedAPInfo.setconnectedflag(true);
							SelectedAPInfo.setName(APInfo[i].getName());
							SelectedAPInfo.setaliveFlag(1);
							SelectedAPInfo.setimg(APInfo[i].getimg());
							SelectedAPInfo.setIP(APInfo[i].getIP());
							SelectedAPInfo.setmacAdrress(APInfo[i].getmacAdrress());
							SelectedAPInfo.setsecurityType(APInfo[i].getsecurityType());
							
							//Log.d(TAG,SelectedAPInfo.getName());
						}
					}
				}
				i++;
			}
		}

	}

	//<func>
	public void ConfigPINcode()
	{
		factory = LayoutInflater.from(MainActivity.this);
		wifiPW_EntryView = factory.inflate(R.layout.confirm_pincode_entry, null);
		edittxt_PINcode = (EditText) wifiPW_EntryView.findViewById(R.id.id_ap_password);
		
		edittxt_PINcode.setText("", TextView.BufferType.EDITABLE);
		edittxt_PINcode.setInputType(InputType.TYPE_CLASS_NUMBER);
		
		//get last pin code
		pinCodeText = edittxt_PINcode.getText().toString();
		PINGet = edittxt_PINcode.getText().toString();
		PINSet = null;

		AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
		alert.setCancelable(false);
		    alert.setTitle("Input Device PIN code:");
		    alert.setMessage("The PIN code will be display on device if the PIN code is exist.\nOtherwise, choose the skip option.");
		    alert.setCancelable(false);
		    alert.setView(wifiPW_EntryView);
		    alert.setPositiveButton("Skip", 
		        new DialogInterface.OnClickListener() {
	            public void onClick(DialogInterface dialog, int whichButton) {
	            	if(edittxt_PINcode.getText().toString().length() > 0){
						pinCodeText = edittxt_PINcode.getText().toString();
					}
	            	//Log.d(TAG,"pinCode_step1 "+edittxt_PINcode.getText().toString());
	            	startToConfigure();
	            }
	        });
		    alert.setNegativeButton("OK",
	    		new DialogInterface.OnClickListener() {
	
				@Override
				public void onClick(DialogInterface arg0, int arg1) {
				
					if(edittxt_PINcode.getText().toString().length() > 0){
						pinCodeText = edittxt_PINcode.getText().toString();
						presave_pinCode = pinCodeText;
					}
					//Log.d(TAG,"pinCode_step1: "+edittxt_PINcode.getText().toString());
					
					startToConfigure();
				}
		    	
		    });
		    alert.show();
		    handler_pd.sendEmptyMessage(0);
	}
	
	//<func>
	public void ControlPINcode(final String deviceName, final String macAddress)
	{
		
		factory = LayoutInflater.from(MainActivity.this);
		wifiPW_EntryView = factory.inflate(R.layout.confirm_pincode_entry, null);
		edittxt_PINcode = (EditText) wifiPW_EntryView.findViewById(R.id.id_ap_password);
		
		edittxt_PINcode.setText("", TextView.BufferType.EDITABLE);
		edittxt_PINcode.setInputType(InputType.TYPE_CLASS_NUMBER);
		edittxt_PINcode.setTextSize(20);
		
		//try to get success pin code by pinfilename
		String content="";
 		byte[] buff = new byte[256]; //input stream buffer
 		try {
 			FileInputStream reader = openFileInput(pinfileName);
 			while((reader.read(buff))!=-1){
 				content+=new String(buff).trim();
 			}
 			reader.close();
 		} catch (FileNotFoundException e) {
 			e.printStackTrace();
 			Log.e(TAG,"pin code FileNotFoundException: "+ content);
 		} catch (IOException e) {
 			Log.e(TAG,"pin code IOException: "+ content);
 		}
 		//Log.d(TAG,"PIN Code info: "+content);
 		
 		//read pin
 		if(content.length()>0){
 			String[] DeviceItem = content.split(";");
 			int itemNumber = DeviceItem.length;

 			for(int i=0;i<itemNumber;i++)
 			{
 				String[] array = DeviceItem[i].split(",");
 				if( macAddress.equals(array[0]) == true){//bssid is same
 					edittxt_PINcode.setText(array[1], TextView.BufferType.EDITABLE);
 					break;
 				}
 			}
 		}
		
		pinCodeText = edittxt_PINcode.getText().toString();
		PINGet = edittxt_PINcode.getText().toString();
		
		AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
		alert.setCancelable(false);
		    alert.setTitle("Key in "+ deviceName +" PIN code");
		    alert.setMessage("The PIN code will be display on device if the PIN code is exist.");
		    alert.setCancelable(false);
		    alert.setView(wifiPW_EntryView);
		    alert.setPositiveButton("Cancel",null);
		    alert.setNegativeButton("OK",
	    		new DialogInterface.OnClickListener() {
	
				@Override
				public void onClick(DialogInterface arg0, int arg1) {
					
					
					if(edittxt_PINcode.getText().toString().length() <= 0){
						Toast.makeText(MainActivity.this, "Warning: The PIN code is empty!", Toast.LENGTH_LONG).show();
						return;
					}
					
					//Log.d(TAG,"ControlPINcode: "+pinCodeText);
					
					if(edittxt_PINcode.getText().toString().length() > 0){
						pinCodeText = edittxt_PINcode.getText().toString();
						PINGet = edittxt_PINcode.getText().toString();
						
						byte[] pinget = PINGet.getBytes();
						byte[] pinset;
		 				if(pinget.length>0) {
		 					if(pinget.length<8) {
			 					pinset = new byte[8];
		 						System.arraycopy(pinget, 0, pinset, 0, pinget.length);
		 						for(int i=pinget.length; i<8; i++) {
		 							pinset[i] = '0';
		 						}
		 					} else if(pinget.length>=8 && pinget.length<=64){
			 					pinset = new byte[pinget.length];
		 						System.arraycopy(pinget, 0, pinset, 0, pinget.length);
		 					} else {
			 					pinset = new byte[64];
		 						System.arraycopy(pinget, 0, pinset, 0, 64);
		 					}
		 					PINSet = new String(pinset);
		 				} else {
		 					PINSet = new String(pinget);
		 				}
		 				fileOps.UpdateCfgPinFile((PINSet!=null && PINSet.length()>0) ? PINSet : "null");
					}
					
					AlertDialog.Builder dialogaction = new AlertDialog.Builder(MainActivity.this);
					// Get the layout inflater
					dialogaction.setCancelable(false);
					dialogaction.setTitle("Setting action");
					dialogaction.setIcon(R.drawable.settings);
					dialogaction.setPositiveButton("Exit",
				            new DialogInterface.OnClickListener() {
				                public void onClick(DialogInterface dialog, int id) {
				                    dialog.cancel();

				                }
				            });

					dialogaction.setNeutralButton("Remove device",
				            new DialogInterface.OnClickListener() {
				                public void onClick(DialogInterface dialog, int id) {

				                    //context.startActivity(new Intent(context, Setup.class));
				                	dialog.cancel();
				                	
				                	remove_OnClick();

				                }
				            });

					dialogaction.setNegativeButton("Rename device",
				            new DialogInterface.OnClickListener() {
				                public void onClick(DialogInterface dialog, int id) {
				                	dialog.cancel();
				                    rename_OnClick();
				                }
				            });
					dialogaction.show();
				}
		    	
		    });
		    alert.show();
	}
	
	//<func>
	public void startToConfigure()
	{
	
		ConfigureAPProFlag = true;
		
		pd = new ProgressDialog(MainActivity.this);
		pd.setCancelable(true);
		pd.setTitle("Configure New Device");
		pd.setCancelable(false);
		pd.setMessage("Configuring...");
		pd.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
		pd.setProgress(0);
        pd.setMax(100);
		pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel", new DialogInterface.OnClickListener() {
		    @Override
		    public void onClick(DialogInterface dialog, int which) {
		        dialog.dismiss();
		        ConfigureAPProFlag = false;
		        TimesupFlag_cfg = true;
		        SCLib.rtk_sc_stop();
		        backgroundThread.interrupt();
		    }
		});
		pd.show();
        // create a thread for updating the progress bar
        backgroundThread = new Thread (new Runnable() {
           public void run() {
               try {
            	   
	           	   //int c = 0;
	           	   
                   while (pd.getProgress()<= pd.getMax()) {
                	   
                	   /*if(c==0){
                		   runOnUiThread(new Runnable() {
	       						@Override
	       						public void run() {
	       							WifiManager wifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
	       				        	   WifiInfo wifiInfo = wifiManager.getConnectionInfo();
	       				        	   String bssid = wifiInfo.getBSSID();
	       				        	   String ssid = wifiInfo.getSSID();
	       							   Toast.makeText(MainActivity.this, "AP: "+ssid+" ("+bssid+")", Toast.LENGTH_LONG).show();
	       						}
       		           		});
                	   }
                	   
                	   if(c++>5)c=0;*/
                	   
                       Thread.sleep(1200);
                       progressHandler.sendMessage(progressHandler.obtainMessage());
                   }
               } catch (java.lang.InterruptedException e) {
               }
           }
        });
        backgroundThread.start();
		
		Thread ConfigDeviceThread = new Thread() {
    		@Override
			public void run() {
    			
	    		Configure_action();
	    		
	    		//wait dialog cancel
	    		if(ConnectAPProFlag == false){
	    			pd.setProgress(100);
	    			backgroundThread.interrupt();
	    			handler_pd.sendEmptyMessage(0);
	    		}
	    		
				runOnUiThread(new Runnable() {
					@Override
					public void run() {
						if(ConfigureAPProFlag == true){
							//show "start to configure"
							ConfigureAPProFlag = false;
							
							showConfiguredList();
						}
					}
				});
	    	}
    	};
    	ConfigDeviceThread.start();
	}
	
	//<func>
	private boolean connect_action(int choiceID) throws InterruptedException
	{
		WifiManager wifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
		List<WifiConfiguration> list = wifiManager.getConfiguredNetworks();
		ScanResult scanResult 			= null;
		WifiConfiguration wifiConfig 	= null;
		ConfigurationSecuritiesV8 conf 	= new ConfigurationSecuritiesV8();
		ConnectivityManager connManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo mWifi = null;
        
		boolean isConnectedConfig = false;
		boolean active = false;
		int networkId = -1;
		String s_SSID = "";
		
		if(!wifiManager.isWifiEnabled()){
			if(wifiManager.getWifiState() != WifiManager.WIFI_STATE_ENABLING)
				wifiManager.setWifiEnabled(true);
		}

		mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
		if(mWifi.isConnected()){
			
			for (int i=0; i<APNumber; i++) {
				scanResult = mScanResults.get(i);
				
				//Log.d("SC_CONNECTION","BSSID: " + deviceList[choiceID].getmacAdrress() + " vs " + scanResult.BSSID + "("+ scanResult.SSID +")");
				
				if(deviceList[choiceID].getmacAdrress().equals(scanResult.BSSID) && scanResult.SSID.length()>0){
					
					if(deviceList[choiceID].getName().endsWith(scanResult.SSID)){

						for( int i_conf=0;i_conf<list.size();i_conf++) {
							
							wifiConfig = list.get(i_conf);
							
							if(wifiConfig.SSID!= null)
								s_SSID = wifiConfig.SSID.indexOf("\"")==0 ? wifiConfig.SSID.substring(1, wifiConfig.SSID.length()-1) : wifiConfig.SSID;
								
							if(wifiConfig.BSSID==null || wifiConfig.BSSID.equalsIgnoreCase("any")){
								if	(s_SSID.length()>0 && s_SSID.equals(scanResult.SSID)){
									isConnectedConfig = true;
									break;
								}
							}else{
								if( wifiConfig.BSSID.equalsIgnoreCase(scanResult.BSSID) ){
									
									//Log.d("SC_CONNECTION","the same BSSID: " + s_SSID + " v.s. " + scanResult.SSID);
									
									if	(s_SSID.length()>0){
										
										if( s_SSID.equals(scanResult.SSID)){
											isConnectedConfig = true;
											break;
										}
										
									}else{
										isConnectedConfig = true;
										break;
									}
								}
							}
						}
						break;
					}
					
				}
	    	}
		}else{
			
			for (int i=0; i<APNumber; i++) {
				scanResult = mScanResults.get(i);
				
				//Log.d("SC_CONNECTION","BSSID: " + deviceList[choiceID].getmacAdrress() + " vs " + scanResult.BSSID + "("+ scanResult.SSID +")");
				
				if(deviceList[choiceID].getmacAdrress().equals(scanResult.BSSID) && scanResult.SSID.length()>0){
					
					if(deviceList[choiceID].getName().endsWith(scanResult.SSID)){
						break;
					}
				}
	    	}
		}
		
		ShowCfgSteptwo = true;
		
		if(isConnectedConfig==true && wifiConfig!=null){//check that it is already connected
			//Log.d("SC_CONNECTION","it is already connected");
			/*runOnUiThread(new Runnable() {
				@Override
				public void run() {

					Toast toast = Toast.makeText(MainActivity.this, 
							"take original"
							,Toast.LENGTH_LONG);
					toast.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM, 0, 100);
					LinearLayout toastLayout = (LinearLayout) toast.getView();
					TextView toastTV = (TextView) toastLayout.getChildAt(0);
					toastTV.setTextSize(15);
					toast.show();
				}
			});*/
			
			conf.setupSecurity(wifiConfig, conf.getScanResultSecurity(scanResult),AP_password);

			networkId = wifiConfig.networkId;
			
			if(Build.MANUFACTURER.equalsIgnoreCase("HUAWEI")){//for HUAWEI
				if (Build.MODEL.equalsIgnoreCase("HUAWEI G610-T00") ||
						Build.MODEL.indexOf("H60")>0 ){
					//Log.d(TAG,Build.MODEL + " connecting");
					
					if(!scanResult.BSSID.equals(wifiManager.getConnectionInfo().getBSSID())){
						networkId = wifiManager.addNetwork(wifiConfig);
						wifiManager.disconnect();
						active = wifiManager.enableNetwork(networkId, true);
					}
				}else{
					networkId = wifiManager.addNetwork(wifiConfig);
					wifiManager.disconnect();
					active = wifiManager.enableNetwork(networkId, true);
				}
			}else{
				
				if(networkId<=0){
					networkId = wifiManager.addNetwork(wifiConfig);
					wifiManager.disconnect();
					active = wifiManager.enableNetwork(networkId, true);
				}
			}
			
			active = wifiManager.reconnect();
			
		}else{						// new wifi config, and connect it, if networkId is invalid
			//Log.d("SC_CONNECTION","new wifi config");
			/*runOnUiThread(new Runnable() {
				@Override
				public void run() {

					Toast toast = Toast.makeText(MainActivity.this, 
							"new wifi_conf"
							,Toast.LENGTH_LONG);
					toast.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM, 0, 100);
					LinearLayout toastLayout = (LinearLayout) toast.getView();
					TextView toastTV = (TextView) toastLayout.getChildAt(0);
					toastTV.setTextSize(15);
					toast.show();
				}
			});*/
			
			conf = new ConfigurationSecuritiesV8();
			wifiConfig = new WifiConfiguration();
			conf.setupSecurity(wifiConfig, conf.getScanResultSecurity(scanResult),AP_password);

			wifiConfig.SSID = "\"" + scanResult.SSID + "\"";
			wifiConfig.priority = getMaxPriority(wifiManager) + 1;

			//Log.d(TAG,"=======connect AP======= Security type: " +conf.getScanResultSecurity(scanResult));
			
			// Dependent on the security type of the selected network
		    // we set the security settings for the configuration
			networkId = wifiManager.addNetwork(wifiConfig);

			if (networkId == -1)
				return false;

			wifiManager.disconnect();
			
			active = wifiManager.enableNetwork(networkId, true);
			active = wifiManager.reconnect();
		}
        
        //Log.d(TAG,"=======connect AP======= enableNetwork: " +String.valueOf(active) + " networkId:" + networkId);
		//Log.d("SC_CONNECTION","=======connect AP======= enableNetwork: " +String.valueOf(active) + " networkId:" + networkId);
        int retry = 0;
        try {
	        do {
					Thread.sleep(500);
					mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
				
	        	retry++;
	        	//Log.d(TAG,"=======connect AP======= wait"+ String.valueOf(retry));
	        	Log.d("SC_CONNECTION","=======connect AP======= wait"+ String.valueOf(retry) + " : " + mWifi.getDetailedState());
	        	
	        	if(ConnectAPProFlag == false)
	        		return false;
	        	
	        }while(mWifi.isConnected() == false && retry<=60);
        
        } catch (InterruptedException e) {
        	Log.e("SC_CONNECTION","=======connect AP======= wait"+ String.valueOf(retry));
			e.printStackTrace();
		}
        
        WifiConnected = false;
        
        //check connect AP correctly
        if(wifiManager.getConnectionInfo().getSSID()!= null){
        	s_SSID = wifiManager.getConnectionInfo().getSSID();
        	s_SSID = s_SSID.indexOf("\"")==0 ? s_SSID.substring(1, s_SSID.length()-1) : s_SSID;
        	
        	if(!scanResult.SSID.equals(s_SSID)){
        		active = false;
            	//Log.d("SC_CONNECTION","SSID is different!!!! " + scanResult.SSID + " vs " + wifiManager.getConnectionInfo().getSSID());
        	}
        	//Log.d("SC_CONNECTION","BSSID " + scanResult.BSSID + " vs " + wifiManager.getConnectionInfo().getBSSID());
        }
        
        //Log.d("SC_CONNECTION","Result: " + active);
        
        if(active==true && mWifi.isConnected()==true)
        {
        	WifiConnected = true;
        	
        	SelectedAPInfo.setconnectedflag(true);
        	SelectedAPInfo.setaliveFlag(1);
    		SelectedAPInfo.setName(deviceList[choiceID].getName());
    		SelectedAPInfo.setIP(deviceList[choiceID].getIP());
    		SelectedAPInfo.setmacAdrress(deviceList[choiceID].getmacAdrress());
    		SelectedAPInfo.setsecurityType(deviceList[choiceID].getsecurityType());
    		SelectedAPInfo.setimg(null);
    		
    		SCCtlOps.ConnectedSSID = scanResult.SSID;
    		SCCtlOps.ConnectedPasswd = AP_password;

        }else{
        	WifiConnected = false;
        	
        	SelectedAPInfo.setconnectedflag(false);
    		SelectedAPInfo.setaliveFlag(0);
    		SelectedAPInfo.setName("");
    		SelectedAPInfo.setIP("");
    		SelectedAPInfo.setmacAdrress("");
    		SelectedAPInfo.setsecurityType(0);
    		SelectedAPInfo.setimg(null);
    		
    		//writeLogtoSys("/sdcard/Log.txt","connection fail:" + "networkId("+networkId+") " + scanResult.SSID);
        }
        
        //check password if it is not exist
        //store the password
        //content: ssid,password;ssid,password;.....
        if(WifiConnected == true){
            
    		String content="";
    		byte[] buff = new byte[256]; //input stream buffer
    		try {
    			FileInputStream reader = openFileInput(pwfileName);
    			while((reader.read(buff))!=-1){
    				content+=new String(buff).trim();
    			}
    			reader.close();
    		} catch (FileNotFoundException e) {
    			e.printStackTrace();
    			Log.e(TAG,"deviceinfo FileNotFoundException "+ content);
    		} catch (IOException e) {
    			Log.e(TAG,"deviceinfo IOException "+ content);
    		}
    		//Log.d(TAG,"APinfo: "+content);
    		
    		if(content.length()>0){
    			String[] APitem = content.split(";");
    			int itemNumber = APitem.length;
    			int compareAPNumber = 0;
    			String[] array;
    			
    			for(int i=0;i<itemNumber;i++)
    			{
    				array = APitem[i].split(",");
    				if(array.length>0){
    					if( SelectedAPInfo.getName().equals(array[0]) == false){ //ssid is different , no store
        					compareAPNumber++;
        				}
    				}
    			}
    			
    			if(itemNumber==compareAPNumber) // add new password
    			{
					//store password into file
					String spilt = ",";
					String spiltEnd = ";";
					FileOutputStream writer;
					try {
						writer = openFileOutput(pwfileName, Context.MODE_APPEND);
						writer.write(SelectedAPInfo.getName().getBytes());
						writer.write(spilt.getBytes());
						if(SCCtlOps.ConnectedPasswd.length()>0)
							writer.write(SCCtlOps.ConnectedPasswd.getBytes());
						else
							writer.write("".getBytes());
						writer.write(spiltEnd.getBytes());
						writer.close();
					} catch (FileNotFoundException e) {
						e.printStackTrace();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}else{ //update password
					FileOutputStream writer;
					String tmpData = content;
					String newData = "";
					String[] tmpAPitem = tmpData.split(";");
					
					//refine data
					for(int i=0;i<tmpAPitem.length;i++){
						array = tmpAPitem[i].split(",");
						if( SelectedAPInfo.getName().equals(array[0]) == false){ //ssid is different
							newData = newData + tmpAPitem[i] +";";
	    				}else{
	    					tmpAPitem[i] = array[0] + "," + SCCtlOps.ConnectedPasswd;
	    					newData = newData + tmpAPitem[i] +";";
	    				}
					}
					
					
					try {
						writer = openFileOutput(pwfileName, Context.MODE_PRIVATE);
						writer.write(newData.getBytes());
						writer.close();
					} catch (FileNotFoundException e) {
						e.printStackTrace();
					} catch (IOException e) {
						e.printStackTrace();
					}
					
				}
    			
    		}else{
    			//store password into file directly if origin is empty
				String spilt = ",";
				String spiltEnd = ";";
				FileOutputStream writer;
				try {
					writer = openFileOutput(pwfileName, Context.MODE_APPEND);
					writer.write(SelectedAPInfo.getName().getBytes());
					writer.write(spilt.getBytes());
					writer.write(SCCtlOps.ConnectedPasswd.getBytes());
					writer.write(spiltEnd.getBytes());
					writer.close();
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				}
    		}
        }
        return WifiConnected;
	}

	//<func>
	private void Configure_action()
	{
		int stepOneTimeout = 30000;
		
		//check wifi connected
		if (SCCtlOps.ConnectedSSID == null) {
			return;
		}
		int connect_count = 200;
		
		//get wifi ip
		int wifiIP = SCLib.WifiGetIpInt();
		while(connect_count>0 && wifiIP==0){
			wifiIP = SCLib.WifiGetIpInt();
			connect_count--;
		}
		if(wifiIP == 0){
    	    Toast.makeText(MainActivity.this, "Allocating IP, please wait a moment", Toast.LENGTH_SHORT).show();
			return;
		}
		
		SCLib.rtk_sc_reset();
		if(PINSet == null){
			SCLib.rtk_sc_set_default_pin(defaultPINcode);
		}else if(PINSet.length()>0){
			SCLib.rtk_sc_set_default_pin(defaultPINcode);			
		}
			
		//Log.d("=== Configure_action ===","rtk_sc_set_pin: " + pinCodeText + "," + PINSet);
		if(pinCodeText.length()>0){
			//Log.d("=== Configure_action ===","pinCodeText: " + pinCodeText);
			SCLib.rtk_sc_set_pin(pinCodeText);
		}
		else
			SCLib.rtk_sc_set_pin(PINSet);
		
		//Log.d("=== Configure_action ===","rtk_sc_set_ssid"+ SCCtlOps.ConnectedSSID);
		SCLib.rtk_sc_set_ssid(SCCtlOps.ConnectedSSID);
		
		if(!SCCtlOps.IsOpenNetwork) {
        	/*if(SCCtlOps.ConnectedPasswd == null) {
    	        Log.e(TAG, "Please Enter Password");
        	    Toast.makeText(MainActivity.this, "Please Enter Password", Toast.LENGTH_SHORT).show();
        	    return;
        	}*/
        	SCLib.rtk_sc_set_password(SCCtlOps.ConnectedPasswd);
        	//if(SCCtlOps.ConnectedPasswd!=null)
        	//	Log.d("=== Configure_action ===",SCCtlOps.ConnectedPasswd);
    	}

		TimesupFlag_cfg = false;
		
		SCLib.rtk_sc_set_ip(wifiIP);
		SCLib.rtk_sc_build_profile();
		
		/* Profile(SSID+PASSWORD, contain many packets) sending total time(ms). */
		SCLibrary.ProfileSendTimeMillis = configTimeout;
		
		//==================== 1 ========================= 30s
		/* Time interval(ms) between sending two profiles. */
		SCLibrary.ProfileSendTimeIntervalMs = 50; //50ms
		/* Time interval(ms) between sending two packets. */
		SCLibrary.PacketSendTimeIntervalMs  = 5; //0ms
		/* Each packet sending counts. */
		SCLibrary.EachPacketSendCounts = 1;

		Log.d(TAG,"Build.MANUFACTURER "+Build.MANUFACTURER);
		Log.d(TAG,"Build.MODEL "+Build.MODEL);
		
		//exception action
		exception_action();
		
		SCLib.rtk_sc_start();
		int watchCount = 0;
		try {
			do{
				Thread.sleep(1000);
				watchCount+=1000;
			}while(TimesupFlag_cfg==false && watchCount<stepOneTimeout);
			
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		//==================== 2 =========================
		if(TimesupFlag_cfg==false)
		{
			int count = 0;
			/* Time interval(ms) between sending two profiles. */
			SCLibrary.ProfileSendTimeIntervalMs = 200; //200ms
			/* Time interval(ms) between sending two packets. */
			SCLibrary.PacketSendTimeIntervalMs  = 10; //10ms
			/* Each packet sending counts. */
			SCLibrary.EachPacketSendCounts = 1;
			
			//exception action
			//exception_action();
			
	    	try {
	    		do{
	    			Thread.sleep( 1000);
	    			count++;
	    			if( (((configTimeout-stepOneTimeout)/1000) - count)<0 )
	    				break;
	    		}while(TimesupFlag_cfg==false );
	    		
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
			TimesupFlag_cfg = true;

	    	//Log.d("=== Configure_action ===","rtk_sc_stop 2");
	    	SCLib.rtk_sc_stop();
		}

	}
	
	private void exception_action()
	{
		if(Build.MANUFACTURER.equalsIgnoreCase("Samsung")){
			//SCLibrary.PacketSendTimeIntervalMs  = 5;
			if (Build.MODEL.equalsIgnoreCase("G9008")){ //Samsung Galaxy S5 SM-G9008
				SCLibrary.PacketSendTimeIntervalMs  = 10; 
			}else if(Build.MODEL.contains("SM-G9208")){ //samsun Galaxy S6
				SCLibrary.PacketSendTimeIntervalMs  = 10; 
			}else if(Build.MODEL.contains("N900")){ //samsun Galaxy note 3
				SCLibrary.PacketSendTimeIntervalMs  = 5; 
			}else if(Build.MODEL.contains("SM-N910U")){ //samsun Galaxy note 4
				SCLibrary.PacketSendTimeIntervalMs  = 5; 
			}
		
		}else if(Build.MANUFACTURER.equalsIgnoreCase("Xiaomi")){//for MI
			if (Build.MODEL.equalsIgnoreCase("MI 4W")){
				SCLibrary.PacketSendTimeIntervalMs  = 5;	//MI 4
			}
		}else if(Build.MANUFACTURER.equalsIgnoreCase("Sony")){//for Sony
			if (Build.MODEL.indexOf("Xperia")>0){
				SCLibrary.PacketSendTimeIntervalMs  = 5;	//Z3
			}
		}else if(Build.MANUFACTURER.equalsIgnoreCase("HUAWEI")){//HUAWEI
			if (Build.MODEL.indexOf("GEM-702L")>0){
				SCLibrary.PacketSendTimeIntervalMs  = 10;	//GEM-702L
			}else{
				SCLibrary.PacketSendTimeIntervalMs  = 5;
			}
		}
		
		//check link rate
		WifiManager wifi_service = (WifiManager) getSystemService(WIFI_SERVICE);
		WifiInfo wifiinfo = wifi_service.getConnectionInfo();
		if( wifiinfo.getLinkSpeed() > 78 ){//MCS8 , 20MHZ , NOSGI
			SCLibrary.ProfileSendTimeIntervalMs = 100; //50ms
			SCLibrary.PacketSendTimeIntervalMs  = 15;
		}
	}
	
	//<func>
	private void showConfiguredList()
	{
		ShowCfgSteptwo = false;
		ConfigureAPProFlag = false;
		SCLib.rtk_sc_stop();
		handler_pd.sendEmptyMessage(0);
		
		final List<HashMap<String, Object>> InfoList = new ArrayList<HashMap<String, Object>>();
		String[] deviceList = null;
		
		final int itemNum = SCLib.rtk_sc_get_connected_sta_num();

		SCLib.rtk_sc_get_connected_sta_info(InfoList);
		
		final boolean[] isSelectedArray = new boolean[itemNum];
		Arrays.fill(isSelectedArray, Boolean.TRUE);
		
		//input data
		if(itemNum>0){
			deviceList = new String[itemNum];
			for (int i=0; i<itemNum; i++) {
				
				configuredDevices[i].setaliveFlag(1);
				
				if(InfoList.get(i).get("Name")==null)
					configuredDevices[i].setName( (String)InfoList.get(i).get("MAC") );
				else
					configuredDevices[i].setName( (String)InfoList.get(i).get("Name") );
					
				
				configuredDevices[i].setmacAdrress( (String)InfoList.get(i).get("MAC") );
				configuredDevices[i].setIP( (String)InfoList.get(i).get("IP") );
					
	    		deviceList[i] = configuredDevices[i].getName();
	    	}
		}else{
			    if(TimesupFlag_cfg == true)
			    {
					AlertDialog.Builder alert_timeout=new AlertDialog.Builder(MainActivity.this);
					alert_timeout.setCancelable(false);
					//switch password input type
					alert_timeout.setTitle("Configure Timeout");
					alert_timeout.setCancelable(false);
					alert_timeout.setPositiveButton("OK",null);
					alert_timeout.show();
			    }
				
				handler_pd.sendEmptyMessage(0);
			return;
		}
    	
		/** Refresh PIN of MAC and store in file */
		/*if(InfoList.size()>0) {
			fileOps.UpdateCtlPinFile(InfoList.get(0).get("MAC").toString(),
				(PINSet!=null && PINSet.length()>0) ? PINSet : "null");
		}*/
		
    	//selectedItemIndexList = new ArrayList();
    	
		AlertDialog.Builder builder=new AlertDialog.Builder(MainActivity.this);
		builder.setCancelable(false);
		
		Toast toast = Toast.makeText(MainActivity.this, aboutMsg,Toast.LENGTH_LONG);
		toast.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.TOP, 0, 100);
		LinearLayout toastLayout = (LinearLayout) toast.getView();
		TextView toastTV = (TextView) toastLayout.getChildAt(0);
		toastTV.setTextSize(20);
		toast.show();
		
    	builder.setTitle("Configured Device");
    	builder.setIcon(android.R.drawable.ic_dialog_info);

    	//Log.d(TAG,"show Configured itmeNum:"+itemNum);
    	
    	builder.setMultiChoiceItems(deviceList, isSelectedArray, 
    			new DialogInterface.OnMultiChoiceClickListener() {
					
					@Override
					public void onClick(DialogInterface dialog, int which, boolean isChecked) {
						
						/*if(isChecked){
							selectedItemIndexList.add(which);
						}else if(selectedItemIndexList.contains(which)){
							selectedItemIndexList.remove(Integer.valueOf(which));
						}*/
						isSelectedArray[which] = isChecked;
					}
				});
    	builder.setPositiveButton("Confirm", new DialogInterface.OnClickListener(){

			@Override
			public void onClick(DialogInterface dialog, int which) {
				
				//String selectedStr = "un-configured state:\n";
				int delDeviceNumber = 0;
				pinCodeText = backdoor_PINCODE;
				PINGet = backdoor_PINCODE;
				
				byte[] pinget = PINGet.getBytes();
				byte[] pinset;
 				if(pinget.length>0) {
 					if(pinget.length<8) {
	 					pinset = new byte[8];
 						System.arraycopy(pinget, 0, pinset, 0, pinget.length);
 						for(int i=pinget.length; i<8; i++) {
 							pinset[i] = '0';
 						}
 					} else if(pinget.length>=8 && pinget.length<=64){
	 					pinset = new byte[pinget.length];
 						System.arraycopy(pinget, 0, pinset, 0, pinget.length);
 					} else {
	 					pinset = new byte[64];
 						System.arraycopy(pinget, 0, pinset, 0, 64);
 					}
 					PINSet = new String(pinset);
 				} else {
 					PINSet = new String(pinget);
 				}
 				fileOps.UpdateCfgPinFile((PINSet!=null && PINSet.length()>0) ? PINSet : "null");
 				
 				//store the pin code
 		        //content: bssid,pin;bssid,pin;.....
 				if(presave_pinCode.length()>0)
 				{
 					String content="";
 		    		byte[] buff = new byte[256]; //input stream buffer
 		    		try {
 		    			FileInputStream reader = openFileInput(pinfileName);
 		    			while((reader.read(buff))!=-1){
 		    				content+=new String(buff).trim();
 		    			}
 		    			reader.close();
 		    		} catch (FileNotFoundException e) {
 		    			e.printStackTrace();
 		    			Log.e(TAG,"pin code FileNotFoundException "+ content);
 		    		} catch (IOException e) {
 		    			Log.e(TAG,"pin code IOException "+ content);
 		    		}
 		    		//Log.d(TAG,"PIN Code info: "+content);
 		    		
 		    		//Write pin into file
 		    		if(content.length()>0){
 		    			String[] DeviceItem = content.split(";");
 		    			boolean isDiffBSSID = false; //check all different SSID 
 		    			int itemNumber = DeviceItem.length;
 		    			int CompearNumber = 0;

 		    			for(int i=0;i<itemNumber;i++)
 		    			{
 		    				String[] array = DeviceItem[i].split(",");
 		    				if( configuredDevices[0].getmacAdrress().equals(array[0]) == false){//bssid is different , no store
 		    					CompearNumber++;
 		    				}
 		    			}
 		    			
 		    			if(itemNumber==CompearNumber)
 		    				isDiffBSSID=true;
 		    			
 		    			if(isDiffBSSID==true)
 		    			{// new bssid
 							//store password into file
 							String spilt = ",";
 							String spiltEnd = ";";
 							FileOutputStream writer;
 							try {
 								writer = openFileOutput(pinfileName, Context.MODE_APPEND);
 								writer.write(configuredDevices[0].getmacAdrress().getBytes());
 								writer.write(spilt.getBytes());
 								writer.write(presave_pinCode.getBytes());
 								writer.write(spiltEnd.getBytes());
 								writer.close();
 							} catch (FileNotFoundException e) {
 								e.printStackTrace();
 							} catch (IOException e) {
 								e.printStackTrace();
 							}
 						}else{ //update bssid
 							String tmpData = content;
 							String[] tmpDeviceItem = tmpData.split(";");
 							String newData = "";
 							String[] array;
 							for(int i=0;i<itemNumber;i++)
 	 		    			{
 								array = tmpDeviceItem[i].split(",");
 								if( configuredDevices[0].getmacAdrress().equals(array[0]) == true)
 								{
 									newData = array[0] +","+ presave_pinCode+";";
 								}else{
 									newData = array[0] +","+ array[1] +";";
 								}
 	 		    			}
 							
 							FileOutputStream writer;
 							try {
 								writer = openFileOutput(pinfileName, Context.MODE_PRIVATE);
 								writer.write(newData.getBytes());
 								writer.close();
 							} catch (FileNotFoundException e) {
 								e.printStackTrace();
 							} catch (IOException e) {
 								e.printStackTrace();
 							}
 							
 						}
 		    			
 		    		}else{
 		    			//store password into file directly if origin is empty
 						String spilt = ",";
 						String spiltEnd = ";";
 						FileOutputStream writer;
 						try {
 							writer = openFileOutput(pinfileName, Context.MODE_APPEND);
 							writer.write(configuredDevices[0].getmacAdrress().getBytes());
								writer.write(spilt.getBytes());
								writer.write(presave_pinCode.getBytes());
 							writer.write(spiltEnd.getBytes());
 							writer.close();
 						} catch (FileNotFoundException e) {
 							e.printStackTrace();
 						} catch (IOException e) {
 							e.printStackTrace();
 						}
 		    		}
 		    		
 		    		//check content
 		    		try {
 		    			FileInputStream reader = openFileInput(pinfileName);
 		    			while((reader.read(buff))!=-1){
 		    				content+=new String(buff).trim();
 		    			}
 		    			reader.close();
 		    		} catch (FileNotFoundException e) {
 		    			e.printStackTrace();
 		    			Log.e(TAG,"pin code FileNotFoundException: "+ content);
 		    		} catch (IOException e) {
 		    			Log.e(TAG,"pin code IOException: "+ content);
 		    		}
 		    		//Log.d(TAG,"PIN Code info: "+content);
 				}
 				
 				for(int _i=0;_i< itemNum;_i++)
			    {
					if(isSelectedArray[_i] == false){
						delDeviceNumber++;
					}
				}
 				if(delDeviceNumber>0){
 					delConfirmIP = new String[delDeviceNumber];
 					for(int _i=0;_i< delDeviceNumber;_i++)
 						delConfirmIP[_i] = "";
 				}
 				
 				int j = 0;
 				boolean isDelDevice = false;
				for(int _i=0;_i< itemNum;_i++)
			    {
					if(isSelectedArray[_i] == false){
						//selectedStr = selectedStr+"\n"+configuredDevices[_i];
						
						delConfirmIP[j++] = InfoList.get(_i).get("IP").toString();
						
						CurrentControlIP = InfoList.get(_i).get("IP").toString();
						//Log.d(TAG,"DelProf SendCtlDevPacket :"+CurrentControlIP);
						//confirm that uncheck device
						SendCtlDevPacket(SCCtlOps.Flag.DelProf, pinCodeText, CurrentControlIP, null);
						isDelDevice = true;
					}
			    }
				
				//Toast.makeText(MainActivity.this, selectedStr, 3000).show();
				if(isDelDevice==false){
					
					SCCtlOps.rtk_sc_control_reset();
					
					DiscovEnable = true;
					DiscoveryDevice(3000);
					show_discoverDevice();
				}
			}
    	});
    	builder.create();
    	builder.show();
	}
	
	public void rename_OnClick()
	{
		LayoutInflater factory = LayoutInflater.from(this);
		final View textEntryView = factory.inflate(R.layout.device_rename, null);
	    final EditText edit_device_name = (EditText) textEntryView.findViewById(R.id.id_device_name);
	    
	    edit_device_name.setText("", TextView.BufferType.EDITABLE);
	    edit_device_name.setTextSize(20);
	    
	    AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
	    alert.setTitle("Enter the Device Name:");
	    alert.setCancelable(false);
	    alert.setView(textEntryView);
	    alert.setPositiveButton("Cancel", 
	        new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
            	
            }
        });
	    alert.setNegativeButton("Save",
	    		new DialogInterface.OnClickListener() {

					@Override
					public void onClick(DialogInterface arg0, int arg1) {
						
		            	//Toast.makeText(	MainActivity.this,
		        		//		"rename device",
		        		//		Toast.LENGTH_LONG).show();
						String new_deviceName = edit_device_name.getText().toString();
						if(new_deviceName.length()>0){
							
							pd = new ProgressDialog(MainActivity.this);
							pd.setTitle("Device Renaming ");
							pd.setMessage("Please wait...");
							pd.setProgressStyle(ProgressDialog.STYLE_SPINNER);
							pd.setIndeterminate(true);
							pd.setCancelable(false);
							pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel", new DialogInterface.OnClickListener() {
							    @Override
							    public void onClick(DialogInterface dialog, int which) {
							        dialog.dismiss();
							        DiscovEnable = false;
							        TimesupFlag_rename = false;
							        AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
									alert.setCancelable(false);
									//switch password input type
										alert.setTitle("Rename Device Failed");
									    alert.setCancelable(false);
									    alert.setPositiveButton("OK",null);
									    alert.show();
							    }
							});
							pd.show();
							isControlSingleDevice = true;
							TimesupFlag_rename = false;
							SendCtlDevPacket(SCCtlOps.Flag.RenameDev, pinCodeText, CurrentControlIP, new_deviceName);
							
							new Thread(){
								public void run() {
									try {
										Thread.sleep(10000);
										isControlSingleDevice = false;
										if(TimesupFlag_rename == false){
											runOnUiThread(new Runnable() {

												@Override
												public void run() {
													
													handler_pd.sendEmptyMessage(0);
													
													AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
													alert.setCancelable(false);
													alert.setTitle("Rename Device Failed");
												    alert.setCancelable(false);
												    alert.setPositiveButton("OK",null);
												    /*alert.setPositiveButton("OK",new DialogInterface.OnClickListener() {
											            public void onClick(DialogInterface dialog, int whichButton) {
											            	SCCtlOps.rtk_sc_control_reset();
															DiscovEnable = true;
															Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
															byte[] DiscovCmdBuf = SCCtlOps.rtk_sc_gen_discover_packet(SCLib.rtk_sc_get_default_pin());
															
															for(int i=0;i<15;i++)
															{
																try {
																	Thread.sleep(200);
																} catch (InterruptedException e) {
																	e.printStackTrace();
																}
																SCLib.rtk_sc_send_discover_packet(DiscovCmdBuf, "255.255.255.255");
															}

											    			// Update Status
															Message msg = Message.obtain();
															msg.obj = null;
															msg.what = ~SCCtlOps.Flag.DiscoverACK; //timeout
															SCLib.TreadMsgHandler.sendMessage(msg);
															
															runOnUiThread(new Runnable() {

																@Override
																public void run() {
																	handler_pd.sendEmptyMessage(0);
																	show_discoverDevice();
															}});
											            }
											        });*/
												    alert.show();
												}});
										}else{
											
											SCCtlOps.rtk_sc_control_reset();
											DiscovEnable = true;
											Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
											byte[] DiscovCmdBuf = SCCtlOps.rtk_sc_gen_discover_packet(SCLib.rtk_sc_get_default_pin());
											
											for(int i=0;i<15;i++)
											{
												Thread.sleep(200);
												SCLib.rtk_sc_send_discover_packet(DiscovCmdBuf, "255.255.255.255");
											}

							    			// Update Status
											Message msg = Message.obtain();
											msg.obj = null;
											msg.what = ~SCCtlOps.Flag.DiscoverACK; //timeout
											SCLib.TreadMsgHandler.sendMessage(msg);
											
											runOnUiThread(new Runnable() {

												@Override
												public void run() {
													handler_pd.sendEmptyMessage(0);
													show_discoverDevice();
											}});
	
										}
										
									} catch (InterruptedException e) {
										e.printStackTrace();
									}
								};
							}.start();
							
							
						}else{
							Toast.makeText(MainActivity.this, "Warning: The device name is empty!", Toast.LENGTH_LONG).show();
						}
					}
	    	
	    });
	    alert.show();
	}
	
	public void remove_OnClick() 
	{
		pd = new ProgressDialog(MainActivity.this);
		pd.setTitle("Device Removing ");
		pd.setMessage("Please wait...");
		pd.setProgressStyle(ProgressDialog.STYLE_SPINNER);
		pd.setIndeterminate(true);
		pd.setCancelable(false);
		pd.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancel", new DialogInterface.OnClickListener() {
		    @Override
		    public void onClick(DialogInterface dialog, int which) {
		        dialog.dismiss();
		        DiscovEnable = false;
		        /*AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
				alert.setCancelable(false);
				//switch password input type
					alert.setTitle("Remove Device Failed");
				    alert.setCancelable(false);
				    alert.setPositiveButton("OK",null);
				    alert.show();*/
				    isDeletedDevice = false;
		    }
		});
		pd.show();
		TimesupFlag_remove = false;
		isControlSingleDevice = true;
		SendCtlDevPacket(SCCtlOps.Flag.DelProf, pinCodeText, CurrentControlIP, null);
		//Toast.makeText(MainActivity.this, "remove device", Toast.LENGTH_LONG).show();
		
		new Thread(){
			public void run() {
				try {
					Thread.sleep(20000);
					
					isControlSingleDevice = false;
					/*if(TimesupFlag_remove == false){
						runOnUiThread(new Runnable() {

							@Override
							public void run() {
								AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
								alert.setCancelable(false);
								alert.setTitle("Remove Device Failed");
							    alert.setCancelable(false);
							    alert.setPositiveButton("OK",null);
							    alert.show();
							}});
					}else{*/
						if(isDeletedDevice == true ){
							/*runOnUiThread(new Runnable() {

								@Override
								public void run() {
									
				 					AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
									alert.setCancelable(false);
									//switch password input type
										alert.setTitle("Remove Device Success");
									    alert.setCancelable(false);
									    alert.setPositiveButton("OK",null);
									    alert.show();
									    isDeletedDevice = false;
									handler_pd.sendEmptyMessage(0);
								}});*/
							SCCtlOps.rtk_sc_control_reset();
							DiscovEnable = true;
							Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
							byte[] DiscovCmdBuf = SCCtlOps.rtk_sc_gen_discover_packet(SCLib.rtk_sc_get_default_pin());
							
							for(int i=0;i<15;i++)
							{
								Thread.sleep(200);
								SCLib.rtk_sc_send_discover_packet(DiscovCmdBuf, "255.255.255.255");
							}

			    			// Update Status
							Message msg = Message.obtain();
							msg.obj = null;
							msg.what = ~SCCtlOps.Flag.DiscoverACK; //timeout
							SCLib.TreadMsgHandler.sendMessage(msg);
							
							runOnUiThread(new Runnable() {

								@Override
								public void run() {
									handler_pd.sendEmptyMessage(0);
									show_discoverDevice();
							}});
								
		 				} else {
		 					runOnUiThread(new Runnable() {

								@Override
								public void run() {
									handler_pd.sendEmptyMessage(0);
				 					AlertDialog.Builder alert=new AlertDialog.Builder(MainActivity.this);
									alert.setCancelable(false);
									//switch password input type
										alert.setTitle("Remove Device Failed");
									    alert.setCancelable(false);
									    alert.setPositiveButton("OK",null);
									    /*alert.setPositiveButton("OK",new DialogInterface.OnClickListener() {
								            public void onClick(DialogInterface dialog, int whichButton) {
								            	SCCtlOps.rtk_sc_control_reset();
												DiscovEnable = true;
												Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
												byte[] DiscovCmdBuf = SCCtlOps.rtk_sc_gen_discover_packet(SCLib.rtk_sc_get_default_pin());
												
												for(int i=0;i<15;i++)
												{
													try {
														Thread.sleep(200);
													} catch (InterruptedException e) {
														e.printStackTrace();
													}
													SCLib.rtk_sc_send_discover_packet(DiscovCmdBuf, "255.255.255.255");
												}

								    			// Update Status
												Message msg = Message.obtain();
												msg.obj = null;
												msg.what = ~SCCtlOps.Flag.DiscoverACK; //timeout
												SCLib.TreadMsgHandler.sendMessage(msg);
												
												runOnUiThread(new Runnable() {

													@Override
													public void run() {
														handler_pd.sendEmptyMessage(0);
														show_discoverDevice();
												}});
								            }
								        });*/
									    alert.show();
									    isDeletedDevice = false;
								}});
		 				}
					//}
						
						
					
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			};
		}.start();
		
		
	}
	
	private void rtk_sc_send_confirm_packet(final int flag)
	{
		new Thread(new Runnable(){
			String pin;
    		public void run() {
    			byte[] buf;
    			Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);

    				pin = PINSet;

//    			Log.d(TAG, "Comfirm PIN: " + pin);
//    			Log.d(TAG, "Comfirm IP: " + CurrentControlIP);
    			
    			//for confirm to delete
    			if(flag==SCCtlOps.Flag.DelProf && delConfirmIP!=null && isControlSingleDevice != true){
    				int DelArraySize = delConfirmIP.length;
    				
    				for(int i=0;i<DelArraySize;i++){
    					if(delConfirmIP[i].length()>0){
    						//Log.d(TAG,"DelProf rtk_sc_send_confirm_packet :"+delConfirmIP[i]);
    						buf = SCCtlOps.rtk_sc_gen_control_confirm_packet(flag,
                					SCLib.rtk_sc_get_default_pin(), pin);
            				if(delConfirmIP[i].equals("0.0.0.0")){
            					//Toast.makeText(MainActivity.this, "rtk_sc_send_confirm_packet1:"+CurrentControlIP, Toast.LENGTH_SHORT).show();
            					//Log.d(TAG,"rtk_sc_send_confirm_packet1: "+CurrentControlIP);
            					for(int retry=0;retry<5;retry++){
            						try {
										Thread.sleep(1);
										SCLib.rtk_sc_send_control_packet(buf, CurrentControlIP);
									} catch (InterruptedException e) {
										e.printStackTrace();
									}
            					}
            						
            				}else{
            					//Toast.makeText(MainActivity.this, "rtk_sc_send_confirm_packet2:"+delConfirmIP[i], Toast.LENGTH_SHORT).show();
            					//Log.d(TAG,"rtk_sc_send_confirm_packet2"+delConfirmIP[i]);
            					for(int retry=0;retry<5;retry++){
            						try {
										Thread.sleep(1);
										
										SCLib.rtk_sc_send_control_packet(buf, delConfirmIP[i]);
									} catch (InterruptedException e) {
										e.printStackTrace();
									}
            					}
            				}
    					}
    				}
    			}else{
    				//Log.d(TAG,"rtk_sc_send_confirm_packet3"+CurrentControlIP);
    				//Toast.makeText(MainActivity.this, "rtk_sc_send_confirm_packet3:"+CurrentControlIP, Toast.LENGTH_SHORT).show();
    				buf = SCCtlOps.rtk_sc_gen_control_confirm_packet(flag,
        					SCLib.rtk_sc_get_default_pin(), pin);
    				for(int retry=0;retry<5;retry++){
    					try {
							Thread.sleep(1);
							SCLib.rtk_sc_send_control_packet(buf, CurrentControlIP);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
    					
    				}
    					
    			}
    			
    		}
    	}).start();
	}
	
	private List<? extends Map<String, ?>> getData_Device() 
	{
		
		List<Map<String, Object>> list = new ArrayList<Map<String, Object>>();
		Map<String, Object> map;
		String tmp = "";
		int i = 0;
		DevInfo = new ArrayList<HashMap<String, Object>>();
		SCCtlOps.rtk_sc_get_discovered_dev_info(DevInfo);
		for(i=0; i<SCCtlOps.rtk_sc_get_discovered_dev_num(); i++) {
			map = new HashMap<String, Object>();
			if(DevInfo.get(i).get("Name")==null) {

				map.put("title", DevInfo.get(i).get("MAC"));
				map.put("info", DevInfo.get(i).get("MAC")+ "   " + DevInfo.get(i).get("Status"));
				
			}else{
				//Log.d(TAG,"getData_Device "+(String) DevInfo.get(i).get("Name"));
				map.put("title", DevInfo.get(i).get("Name"));
				map.put("info", DevInfo.get(i).get("MAC")+ "   " + DevInfo.get(i).get("Status"));
			}

			tmp = (String) DevInfo.get(i).get("IP");
			if(DevInfo.get(i).get("IP")!=null && tmp.length()>0)
				list.add(map);
			
		}

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
	
    /**
     * Definition of the list adapter...uses the View Holder pattern to
     * optimize performance.
     */
 static class DeviceAdapter extends ArrayAdapter {

  private static final int RESOURCE = R.layout.wifiap_list;
  private LayoutInflater inflater;

     static class ViewHolder {
         TextView nameTxVw;
         TextView deviceInfo;
         ImageView deviceImg;
         RadioGroup selected;
     }

     @SuppressWarnings("unchecked")
	public DeviceAdapter(Context context, DeviceInfo[] objects)
	  {
	   super(context, RESOURCE, objects);
	   inflater = LayoutInflater.from(context);
	  }

	  @Override
	  public View getView(int position, View convertView, ViewGroup parent)
	  {
	   ViewHolder holder;
	
	   if ( convertView == null ) {
	    // inflate a new view and setup the view holder for future use
	    convertView = inflater.inflate( RESOURCE, null );
	
	    holder = new ViewHolder();
	    holder.nameTxVw = (TextView) convertView.findViewById(R.id.title_aplist);
	    holder.deviceInfo = (TextView) convertView.findViewById(R.id.info_aplist);
	    holder.deviceImg =(ImageView)convertView.findViewById(R.id.signalImg);
	    holder.selected = (RadioGroup)convertView.findViewById(R.id.radioButton1);
	    
	    convertView.setTag( holder );
	   }  else {
	    // view already defined, retrieve view holder
	    holder = (ViewHolder) convertView.getTag();
	   }
	
	   DeviceInfo cat = (DeviceInfo) getItem( position );
	   if ( cat == null ) {
	    //Log.e( TAG,"error_getView_neil "+ String.valueOf(position) );
	   }
	   
	   holder.nameTxVw.setText( cat.getName() );

	   if(cat.getconnectedflag() == true){
		   holder.deviceInfo.setText("connected");
	   }
	   else{
		   holder.deviceInfo.setText("");
	   }
		   
	   
	   //holder.nameTxVw.setCompoundDrawables( cat.getimg(), null, null, null );
	   holder.deviceImg.setImageDrawable(cat.getimg());
	
	   return convertView;
	  }
	 }
	
 	private Runnable Cfg_changeMessage = new Runnable() {
	    @Override
	    public void run() {
	        //Log.v(TAG, strCharacters);
	    	pd.setMessage("Waiting for the device");
	    }
	};
 
	/** Handler class to receive send/receive message */
	private class MsgHandler extends Handler{

		@Override
		public void handleMessage(Message msg){
			//Log.d(TAG, "msg.what: " + msg.what);
			switch(msg.what) {
			case ~SCCtlOps.Flag.CfgSuccessACK://Config Timeout
				//Log.d("MsgHandler","Config Timeout");
				SCLib.rtk_sc_stop();
				
				break;
			case SCCtlOps.Flag.CfgSuccessACK: //Not Showable
				//Log.d("MsgHandler","Config SuccessACK");
				//Toast.makeText(getApplication(), "Get CfgSuccessACK", Toast.LENGTH_SHORT).show();
				SCLib.rtk_sc_stop();
//				Log.d(TAG, "CurrentView: " + CurrentView);
				TimesupFlag_cfg = true;
				
				if(ShowCfgSteptwo == true)
					runOnUiThread(Cfg_changeMessage);
				
	 		 	List<HashMap<String, Object>> InfoList = new ArrayList<HashMap<String, Object>>();
	 			SCLib.rtk_sc_get_connected_sta_info(InfoList);
	 			String ip = InfoList.get(0).get("IP").toString();
	    		if(!ip.equals("0.0.0.0")) {// Client Got IP
					//Log.d(TAG, "Client Got IP");
	 				//SendCtlDevPacket(SCCtlOps.Flag.RenameDev, PINSet, ip, ReNameStr);
	 				//RenameOfConfig = false;
	    		}
				break;
			case SCCtlOps.Flag.DiscoverACK:
				//Log.d("MsgHandler","DiscoverACK");
				//DiscovEnable = false;
				SCCtlOps.handle_discover_ack((byte[])msg.obj);
				if(SCCtlOps.DiscoveredNew) {
					show_discoverDevice();
					//handler_pd.sendEmptyMessage(0);
				}
				
				break;
			case ~SCCtlOps.Flag.DiscoverACK:
				//Log.d("MsgHandler","Discovery timeout.");
				DiscovEnable = false;
				//handler_pd.sendEmptyMessage(0);
				break;
			case SCCtlOps.Flag.DelProfACK:
				
				//Toast.makeText(getApplication(), "Get DelProfACK", Toast.LENGTH_SHORT).show();
				
				//Log.d("MsgHandler","Del Profile ACK");
				rtk_sc_send_confirm_packet(SCCtlOps.Flag.DelProf);
				isDeletedDevice = true;
 				
				SCCtlOps.rtk_sc_control_reset();
 				
				DiscovEnable = true;	
				TimesupFlag_remove = true;
				
				new Thread(new Runnable(){
		    		public void run() {
		    			Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
		    			byte[] DiscovCmdBuf = SCCtlOps.rtk_sc_gen_discover_packet(SCLib.rtk_sc_get_default_pin());
		    			
		    			try {
							Thread.sleep(10000);
						} catch (InterruptedException e1) {
							e1.printStackTrace();
						}
		    			
		    			/*long startTime = System.currentTimeMillis();
		    			long endTime = System.currentTimeMillis();
		    			while(DiscovEnable && (endTime-startTime)<10000) {

		        			if((endTime-startTime)>7000){
		        				try {
									Thread.sleep(500);
									SCLib.rtk_sc_send_discover_packet(DiscovCmdBuf, "255.255.255.255");
									Log.d("scan-RemoveDevACK111111","255.255.255.255");
								} catch (InterruptedException e) {
									e.printStackTrace();
								}
		        				
		        			}
		        			endTime = System.currentTimeMillis();
		    			}
		    			
		    			Log.i(TAG, "Discover Time Elapsed: " + (endTime-startTime) + "ms");*/

		    			SCLib.rtk_sc_send_discover_packet(DiscovCmdBuf, "255.255.255.255");
						// Update Status
						Message msg = Message.obtain();
						msg.obj = null;
						msg.what = ~SCCtlOps.Flag.DiscoverACK; //timeout
						SCLib.TreadMsgHandler.sendMessage(msg);
						//handler_pd.sendEmptyMessage(0);
		    		}
		    	}).start();
				
				show_discoverDevice();
 				
				break;
			case SCCtlOps.Flag.RenameDevACK:
				
				//Toast.makeText(getApplication(), "Get RenameDevACK", Toast.LENGTH_SHORT).show();
				
				//Log.d("MsgHandler","Rename Device ACK");
				rtk_sc_send_confirm_packet(SCCtlOps.Flag.RenameDev);
				
				SCCtlOps.rtk_sc_control_reset();
				TimesupFlag_rename = true;
				/*
				
				new Thread(new Runnable(){
		    		public void run() {
		    			Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
		    			byte[] DiscovCmdBuf = SCCtlOps.rtk_sc_gen_discover_packet(SCLib.rtk_sc_get_default_pin());
		    			
		    			try {
							Thread.sleep(8000);
						} catch (InterruptedException e1) {
							e1.printStackTrace();
						}

		    			SCLib.rtk_sc_send_discover_packet(DiscovCmdBuf, "255.255.255.255");
		    			
						// Update Status
						Message msg = Message.obtain();
						msg.obj = null;
						msg.what = ~SCCtlOps.Flag.DiscoverACK; //timeout
						SCLib.TreadMsgHandler.sendMessage(msg);
						//handler_pd.sendEmptyMessage(0);
		    		}
		    	}).start();
				
				show_discoverDevice();*/
				
				break;
			default:
				//Log.d("MsgHandler","default");
				break;
			}
		}
	}

	public void SendCtlDevPacket(final int flag, final String pin, final String ip, final String new_name)
	{
//		Log.d(TAG, "ip: " + ip);
//		Log.d(TAG, "pin: " + pin);
//		Log.d(TAG, "name: " + new_name);

		new Thread(new Runnable(){
    		int count = 0;
    		public void run() {
    			Process.setThreadPriority(Process.THREAD_PRIORITY_DEFAULT);
				byte[] buf = SCCtlOps.rtk_sc_gen_control_packet(flag, SCLib.rtk_sc_get_default_pin(), pin, new_name);
				
				/*if(flag==SCCtlOps.Flag.DelProf){
					new Thread(){
						public void run() {
							runOnUiThread(new Runnable() {

								@Override
								public void run() {
									Toast.makeText(getApplication(), "DelProf: " +ip, Toast.LENGTH_LONG).show();
								}});
						};
					}.start();
				}else if(flag==SCCtlOps.Flag.RenameDev){
					new Thread(){
						public void run() {
							runOnUiThread(new Runnable() {

								@Override
								public void run() {
									Toast.makeText(getApplication(), "RenameDev: " +ip+"("+new_name+")", Toast.LENGTH_LONG).show();
								}});
						};
					}.start();
				}*/
				
    			while(count<6) {
    				try {
						Thread.sleep(1);
						SCLib.rtk_sc_send_control_packet(buf, ip);
						//Log.d("control packet","flag: " + String.valueOf(flag));
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
    			 	
    			 	count++;
    			}
    		}
    	}).start();
	}

	public void CtlDevStatPopUp(String title)
	{
	 	AlertDialog.Builder builder = new AlertDialog.Builder(this);
	 	builder.setTitle(title)
	 	.setIcon(android.R.drawable.ic_dialog_info)
		.setCancelable(false)
	 	.setPositiveButton("OK", new DialogInterface.OnClickListener(){
	        @Override
	        public void onClick(DialogInterface dialog, int which) {
            	SCCtlOps.rtk_sc_control_reset();
            	DiscovEnable = true;

	            dialog.cancel();
	        }
	    })
	 	.setNegativeButton(null, null);
	 	builder.show();
	}
	
	static int getSecurity(ScanResult result) {
	    if (result.capabilities.contains("WEP")) {
	        return SECURITY_TYPE.SECURITY_WEP.ordinal();
	    } else if (result.capabilities.contains("PSK")) {
	        return SECURITY_TYPE.SECURITY_PSK.ordinal();
	    } else if (result.capabilities.contains("EAP")) {
	        return SECURITY_TYPE.SECURITY_EAP.ordinal();
	    }
	    return SECURITY_TYPE.SECURITY_NONE.ordinal();
	}
	
	private static int getMaxPriority(final WifiManager wifiManager) {
		final List<WifiConfiguration> configurations = wifiManager.getConfiguredNetworks();
		int pri = 0;
		for(final WifiConfiguration config : configurations) {
			if(config.priority > pri) {
				pri = config.priority;
			}
		}
		return pri;
	}
	
	/*private boolean writeLogtoSys(String path, String ctx)
	{
		//path :"/sdcard/Log.txt"
		Time now = new Time();
        now.setToNow();
        String sTime = now.format("%m/%d %H:%M.%S");
        
		OutputStream output = null;
		try {
			output = new FileOutputStream(path,true);
		
		String hdr = "\n\n------  " +sTime+ " ssid connection ------\n";
		try {
			output.write(hdr.getBytes());
			output.write(ctx.getBytes());
			output.write("\n".getBytes());
			output.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		} catch (FileNotFoundException e2) {
			e2.printStackTrace();
		}
		
		return true;
	}
	
	private String byteArrayToHex(byte[] a) {
	   StringBuilder sb = new StringBuilder(a.length * 2);
	   for(byte b: a)
	      sb.append(String.format("%02x ", b & 0xff));
	   return sb.toString();
	}*/
	
	private void launchWifiConnecter(final Activity activity, final ScanResult hotspot) {
		final Intent openWifiItemIntent = new Intent("com.wifi.connecter.CONNECT_OR_EDIT");
		openWifiItemIntent.putExtra("com.wifi.connecter.HOTSPOT", hotspot);
		try {
			activity.startActivity(openWifiItemIntent);
		} catch(ActivityNotFoundException e) {
			Toast.makeText(activity, "Wifi Connecter is not installed.", Toast.LENGTH_LONG).show();
	        Log.e(TAG, "Wifi Connecter is not installed.");
		}
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		//getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	
	public void qrcode_onclick(View view)
	{
		Intent openCameraIntent = new Intent(MainActivity.this, CaptureActivity.class);
		startActivityForResult(openCameraIntent, 0);
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (resultCode == RESULT_OK) {
			Bundle bundle = data.getExtras();
			QRCodeScanResult = bundle.getString("result");
			Log.d(TAG, "QRCodeScanResult: " + QRCodeScanResult);

			if(QRCodeScanResult.length()>0 && QRCodeScanResult.length()<64) {
				//LayoutInflater factory = LayoutInflater.from(MainActivity.this);
				//View wifiPW_EntryView = factory.inflate(R.layout.wifi_pincode_entry, null);
				//EditText edittxt_PINcode = (EditText) wifiPW_EntryView.findViewById(R.id.id_ap_password);
				edittxt_PINcode.setText(QRCodeScanResult, TextView.BufferType.EDITABLE);
				
				pinCodeText = QRCodeScanResult;
				//Log.d("pin code:", pinCodeText);
				
			} else {
				Log.e(TAG, "Wrong QRCode!");
			}
		}
	}
}
