package com.rtk.btconfig;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceManager;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.GridView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;


import static com.rtk.btconfig.DevicesMainActivity.BroadcastDevInfo;
import static com.rtk.btconfig.DevicesMainActivity.DB_BROADCAST_DEVICES_TAG;
import static com.rtk.btconfig.DevicesMainActivity.DB_GROUP_DEVICES_TAG;
import static com.rtk.btconfig.DevicesMainActivity.DB_GROUP_NAMEADDR_MAP_TAG;
import static com.rtk.btconfig.DevicesMainActivity.DB_GROUP_NAME_TAG;
import static com.rtk.btconfig.DevicesMainActivity.HTTPQueryResultParse;
import static com.rtk.btconfig.DevicesMainActivity.currProvisionerIP;


public class TabBaseFragment extends BaseFragment {

	private static final String TAG = "TabBaseFragment";
	
	private static final String DATA_NAME = "name";
	private static final String DATA_DEVICES = "devices";
	
	private String title = "";
	private boolean isFABOpen = false;

	GridView bt_mesh_grid;
	BTMeshGridAdapter btMeshGrdiAdapter;
	List<String> mDevicesList;
	String mDevicesListStr;
	FloatingActionButton mFab;
	FloatingActionButton mFab_Del;
	FloatingActionButton mFab_LightOn;
	FloatingActionButton mFab_LightOff;
	Fragment mFragment;

	String db_group_name_addr_str;
	String db_group_name_str;
	String db_group_devices_str;

	List<HashMap<String, String>> group_name_addr_map;
	List<HashMap<String, String>> bt_group_devices_map;

	private ProgressDialog pd;



    private Handler handler_pd ;

    public static TabBaseFragment newInstance(String title, int indicatorColor, int dividerColor, int iconResId, String devicesList) {
		Log.e(TAG,"TabActivity - newInstance " + devicesList);
		TabBaseFragment f = new TabBaseFragment();
		f.setTitle(title);
		f.setIndicatorColor(indicatorColor);
		f.setDividerColor(dividerColor);
//		f.setIconResId(iconResId);



		
		//pass data
		Bundle args = new Bundle();
        args.putString(DATA_NAME, title);
		args.putString(DATA_DEVICES, devicesList);
        f.setArguments(args);

        return f;
    }
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
        mFragment = this;
		
		//get data
		title = getArguments().getString(DATA_NAME);
		mDevicesListStr = getArguments().getString(DATA_DEVICES);
		setMyTag(title);
		Log.e(TAG,"TabActivity - onCreate" + mDevicesListStr);

		SharedPreferences db = PreferenceManager.getDefaultSharedPreferences(getActivity().getApplicationContext());

		db_group_name_addr_str = db.getString(DB_GROUP_NAMEADDR_MAP_TAG, null);
		db_group_name_str = db.getString(DB_GROUP_NAME_TAG, null);
		db_group_devices_str = db.getString(DB_GROUP_DEVICES_TAG, null);
		Type typeToken = new TypeToken<ArrayList<HashMap<String, String>>>() {
		}.getType();
		Gson gson = new Gson();
		group_name_addr_map = gson.fromJson(db_group_name_addr_str, typeToken);
		bt_group_devices_map = gson.fromJson(db_group_devices_str, typeToken);

	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

		View view = inflater.inflate(R.layout.frg_common, container, false);
		bt_mesh_grid = view.findViewById(R.id.mesh_grid);
		mFab =  view.findViewById(R.id.fab);
		mFab_Del = view.findViewById(R.id.fab_del);
		mFab_LightOn = view.findViewById(R.id.fab_lighton);
		mFab_LightOff = view.findViewById(R.id.fab_lightoff);
		String tmpDeviceName[]  = mDevicesListStr.split(";");
		List<String>  bt_group_devices = new ArrayList<String>(Arrays.asList(tmpDeviceName));
        Log.e(TAG,"BookFragment - onCreateView "+ bt_group_devices.toString());
		btMeshGrdiAdapter = new BTMeshGridAdapter(bt_group_devices , getContext());
		bt_mesh_grid.setAdapter(btMeshGrdiAdapter);

        handler_pd = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                // Log.d(TAG,"handleMessage msg.what: " + String.valueOf(msg.what));
                switch (msg.what) {
                    case 0:
						stopPD();
                        break;

                    default:
                        break;
                }
            }
        };
		initFab();
		return view;
	}
	
	@Override
	public void onViewCreated(View view, Bundle savedInstanceState) {
		super.onViewCreated(view, savedInstanceState);
		Log.e(TAG,"BookFragment - onViewCreated");

//		TextView txtName = (TextView) view.findViewById(R.id.txtName);
//		txtName.setText(title);
	}

	@Override
	public void onActivityCreated(Bundle savedInstanceState) {
		super.onActivityCreated(savedInstanceState);
		Log.e(TAG,"BookFragment - onActivityCreated");
	}

	@Override
	public void onDestroy() {
		Log.e(TAG,"BookFragment - onDestroy");

		super.onDestroy();
	}



	@Override
	public void onDestroyView() {
		Log.e(TAG,"BookFragment - onDestroyView");
		super.onDestroyView();
	}

	private void showFABMenu(){
		isFABOpen = true;
		mFab_Del.animate().translationY(-getResources().getDimension(R.dimen.standard_60));
		mFab_LightOff.animate().translationY(-getResources().getDimension(R.dimen.standard_120));
		mFab_LightOn.animate().translationY(-getResources().getDimension(R.dimen.standard_180));
	}

	private void closeFABMenu(){
		isFABOpen = false;
		mFab_Del.animate().translationY(0);
		mFab_LightOff.animate().translationY(0);
		mFab_LightOn.animate().translationY(0);
	}

	private void light_control(final String value){
    	startPD("Connect Mesh devices ...");
		new Thread(new Runnable() {
			public void run() {
				SharedPreferences db = PreferenceManager.getDefaultSharedPreferences(getActivity().getApplicationContext());
				HashMap<String, String> map = null;
				HashMap<String, Object> message_map = new HashMap<String, Object>();
				Gson gson = new Gson();
				Type typeToken = new TypeToken<ArrayList<HashMap<String, String>>>() {
				}.getType();
				db_group_name_addr_str = db.getString(DB_GROUP_NAMEADDR_MAP_TAG, null);
				group_name_addr_map = gson.fromJson(db_group_name_addr_str, typeToken);

				Iterator<HashMap<String, String>> it = group_name_addr_map.iterator();
				for (; it.hasNext(); ) {
					map = it.next();
					if (map.toString().contains(title)) {
						message_map.put("GROUP_ADDR", map.keySet().toString().substring(1, map.keySet().toString().length() - 1));
						message_map.put("LIGHT", value);
						Log.e(TAG, "tab GROUP_ADDR " + map.keySet().toString().substring(1, map.keySet().toString().length() - 1));
						String queryStr = "01" + (String) message_map.get("GROUP_ADDR") + (String) message_map.get("LIGHT");

						HTTPQuery httpQuery = new HTTPQuery(currProvisionerIP, "bt_mesh=0106" + String.format("%04x", queryStr.length() + 8) + queryStr);
						String HTTPQueryResult = httpQuery.run();
						Log.e(TAG, "fuck HTTPQueryResult" + HTTPQueryResult);
						if (HTTPQueryResult != null) {
							HTTPQueryResultParse(HTTPQueryResult);
						}
						break;
					}
				}
                handler_pd.sendEmptyMessage(0);
			}
		}).start();

    }

	private void initFab(){

		mFab.setOnClickListener(new View.OnClickListener() {
			@Override public void onClick(View v) {
				if(!isFABOpen)
					showFABMenu();
				else
					closeFABMenu();
			}
		});

        mFab_LightOff.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {
                light_control("00");
            }
        });

        mFab_LightOn.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {

                light_control("01");

            }
        });


		mFab_Del.setOnClickListener(new View.OnClickListener() {
			@Override public void onClick(View v) {
				startPD("Deleting "+ title + " group...");
//				Toast.makeText(getContext(), "Group Removed", Toast.LENGTH_SHORT).show();
				new Thread(new Runnable() {
					public void run() {
				Gson gson = new Gson();

				Log.e(DB_GROUP_NAME_TAG, TAG +"1 " + db_group_name_str.toString());
				String tmpGroupName[]  = db_group_name_str.split(", ");
				List<String> bt_group_name = new ArrayList<String>(Arrays.asList(tmpGroupName));
				bt_group_name.remove(title);
				Log.e(DB_GROUP_NAME_TAG, TAG +"2 "  + bt_group_name.toString());
				Log.e(DB_GROUP_NAME_TAG, TAG +"3 "  + db_group_devices_str.toString());



				Iterator<HashMap<String, String>> it = bt_group_devices_map.iterator();
				HashMap<String, String> map = null;
				for (; it.hasNext(); ) {
					map = it.next();
					if(map.get(title) != null )
					{

						String[] deviceName = map.get(title).split(";");
						String queryStr = new String("");
						Log.e(TAG,"delete tab " + map.get(title));

						for(int i=0; i < deviceName.length;i++) {
							String defBDevInfoStr = gson.toJson(BroadcastDevInfo);
							if (!defBDevInfoStr.contains("null")) {
								Iterator<HashMap<String, Object>> it_BroadcastDevInfo = BroadcastDevInfo.iterator();
								HashMap<String, Object> BroadcastDevInfoMap = null;
								for (; it_BroadcastDevInfo.hasNext(); ) {
									BroadcastDevInfoMap = it_BroadcastDevInfo.next();
									if(BroadcastDevInfoMap.get("Name").toString().contains(deviceName[i]) == true) {
										BroadcastDevInfoMap.put("GROUP_ADDR","c000");
										String mesh_addr =(String) BroadcastDevInfoMap.get("MESH_ADDR");
										queryStr = queryStr + mesh_addr + "c000";
									}

								}

							}
						}
						queryStr = String.format("%02x", deviceName.length) + queryStr;
Log.e("TAG","re-group queryStr "+queryStr);
						HTTPQuery httpQuery = new HTTPQuery(currProvisionerIP, "bt_mesh=0107" + String.format("%04x", queryStr.length() + 8) + queryStr);
						String HTTPQueryResult = httpQuery.run();
						if (HTTPQueryResult != null) {
							HTTPQueryResultParse(HTTPQueryResult);
							Log.e("TAG","re-group queryStr "+queryStr);

						}
						bt_group_devices_map.remove(map);
						break;
					}
				}
				Log.e(DB_GROUP_NAME_TAG, TAG  + bt_group_devices_map.toString());

				it = group_name_addr_map.iterator();
				for (; it.hasNext(); ) {
					map = it.next();
					if(map.toString().contains(title) )
					{
						group_name_addr_map.remove(map);
						break;
					}
				}

				SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(getActivity().getApplicationContext());//this.getPreferences(MODE_PRIVATE);
				SharedPreferences.Editor editor = pref.edit();
				String BroadcastDevInfoStr = gson.toJson(BroadcastDevInfo);
				String bt_group_devices_map_str = gson.toJson(bt_group_devices_map);
				db_group_name_addr_str = gson.toJson(group_name_addr_map);
				editor.putString(DB_BROADCAST_DEVICES_TAG, BroadcastDevInfoStr);
				editor.putString(DB_GROUP_DEVICES_TAG, bt_group_devices_map_str);
				editor.putString(DB_GROUP_NAMEADDR_MAP_TAG, db_group_name_addr_str);
                Log.e(TAG,"0fuck bt_group_name " +bt_group_name.toString());
//				if(bt_group_name.size() > 0) {
					Log.e(TAG,"1.1fuck bt_group_name " +bt_group_name.toString());
                    editor.putString(DB_GROUP_NAME_TAG, bt_group_name.toString().substring(1, +bt_group_name.toString().length() - 1));


				editor.commit();

                pref = PreferenceManager.getDefaultSharedPreferences(getActivity().getApplicationContext());//this.getPreferences(MODE_PRIVATE);


Log.e(TAG,"2fuck bt_group_name " +pref.getString(DB_GROUP_NAME_TAG, null));
				getActivity().getSupportFragmentManager()
						.beginTransaction()
						.detach(mFragment)
////						.hide(mFragment)
						.remove(mFragment)
////						.attach(tabFragment)
//						.replace(R.id.content_fragment, null)
						.commit();
//				handler_pd.sendEmptyMessage(0);
				getActivity().finish();
				getActivity().startActivity(getActivity().getIntent().addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION));
					}
				}).start();

			}


		});
	}

    private void stopPD() {


				if (pd.isShowing()) {
					pd.dismiss();
				}


    }

    private void startPD(String title) {



    	pd = new ProgressDialog(getActivity());
        pd.setMessage(title);
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


    }

    }
