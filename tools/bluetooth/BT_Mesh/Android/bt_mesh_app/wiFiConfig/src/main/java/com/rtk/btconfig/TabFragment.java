package com.rtk.btconfig;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import static com.rtk.btconfig.DevicesMainActivity.DB_GROUP_DEVICES_TAG;
import static com.rtk.btconfig.DevicesMainActivity.DB_GROUP_NAME_TAG;
import static com.rtk.btconfig.DevicesMainActivity.bt_group_name;
import static com.rtk.btconfig.DevicesMainActivity.bt_group_devices_map;


public class TabFragment extends Fragment {
    private static final String TAG = "TabFragment";
	private static SlidingTabLayout tabs;
	private static ViewPager pager;
	public static FragmentPagerAdapter adapter;
	static LinkedList<BaseFragment> fragments;


	
	public static Fragment newInstance(){
		TabFragment f = new TabFragment();
		return f;
	}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		return inflater.inflate(R.layout.frg_tab, container, false);
	}
	
	@Override
	public void onViewCreated(View view, Bundle savedInstanceState) {
		//adapter


		LinkedList<BaseFragment> aFragments = getFragments();
		adapter = new TabFragmentPagerAdapter(getFragmentManager(), aFragments);

		//pager
		pager = (ViewPager) view.findViewById(R.id.pager);

		pager.setAdapter(adapter);
		//tabs
		tabs = (SlidingTabLayout) view.findViewById(R.id.tabs);

		tabs.setCustomTabColorizer(new SlidingTabLayout.TabColorizer() {

			@Override
			public int getIndicatorColor(int position) {
				return fragments.get(position).getIndicatorColor();
			}

			@Override
			public int getDividerColor(int position) {
				return fragments.get(position).getDividerColor();
			}
		});
		tabs.setBackgroundResource(R.color.white);
		tabs.setCustomTabView(R.layout.tab_title, R.id.txtTabTitle, R.id.imgTabIcon);
		tabs.setViewPager(pager);

	}


	public static int getPosition(){
		return tabs.getPosition();
	}

	private LinkedList<BaseFragment> getFragments(){
		int indicatorColor = Color.BLUE;
		int dividerColor = Color.TRANSPARENT;
		Gson gson = new Gson();

		fragments = new LinkedList<BaseFragment>();

		SharedPreferences db = PreferenceManager.getDefaultSharedPreferences(getActivity().getApplicationContext());
		String db_group_name_str = db.getString(DB_GROUP_NAME_TAG, null);
		String bt_group_devices_map_str = db.getString(DB_GROUP_DEVICES_TAG, null);
		Type type = new TypeToken<ArrayList<HashMap<String, Object>>>() {}.getType();
		bt_group_devices_map = gson.fromJson(bt_group_devices_map_str, type);
//		Log.e(DB_GROUP_NAME_TAG, " array " +db_group_name_str+ " bt_group_devices_map "+ bt_group_devices_map.toString());
		if(db_group_name_str != null) {
			String tmpGroupName[]  = db_group_name_str.split(", ");
			bt_group_name = new ArrayList<String>(Arrays.asList(tmpGroupName));

			for (int i = 0; i < bt_group_name.size(); i++) {
				Log.e(TAG, "bt_group_name.get(i) " + bt_group_name.get(i) + " " + i);
				HashMap<String, String> map = null;
				Iterator<HashMap<String, String>> it = bt_group_devices_map.iterator();
				for(;it.hasNext();)
				{
					map = it.next();
					String devices_list =  map.get(bt_group_name.get(i));
					Log.e(TAG,i +" bt_group_name.get(i) " + bt_group_name.get(i) + " devices_list " + devices_list + " map "+map.toString());
					if(devices_list != null) {
						fragments.add(TabBaseFragment.newInstance(bt_group_name.get(i), indicatorColor, dividerColor, android.R.drawable.ic_dialog_info, devices_list));
						break;
					}

				}


			}
		}
//		TabBaseFragment newTabPage = TabBaseFragment.newInstance(bt_group_name.get(i), indicatorColor, dividerColor, android.R.drawable.ic_dialog_info);
//		fragments.add(newTabPage);
//		fragments.add( TabBaseFragment.newInstance("cook", indicatorColor, dividerColor, android.R.drawable.ic_dialog_info));

//		fragments.remove(newTabPage);
//		fragments.add(CookFragment.newInstance("Cook", indicatorColor, dividerColor, android.R.drawable.ic_dialog_map));
//		fragments.add(FoodFragment.newInstance("Food", indicatorColor, dividerColor, android.R.drawable.ic_dialog_email));
//		fragments.add(GoodFragment.newInstance("Good", Color.BLUE, dividerColor, android.R.drawable.ic_lock_power_off));
//		fragments.add(LookFragment.newInstance("Look", Color.CYAN, dividerColor, android.R.drawable.ic_dialog_dialer));
//		fragments.add(WoodFragment.newInstance("Wood", Color.MAGENTA, dividerColor, android.R.drawable.ic_media_play));
		return fragments;
	}
	
}
