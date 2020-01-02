package com.rtk.btconfig;

import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import static com.rtk.btconfig.DevicesMainActivity.DB_BROADCAST_DEVICES_TAG;


public class BTListBaseAdapter extends BaseAdapter {
    private static final String TAG = "BTListBaseAdapter";

    private LayoutInflater mInflater;
    private List<Map<String, Object>> mData;
    public static Map<Integer, Boolean> isSelected;

    private Context mContext;
    public static List<HashMap<String, Object>> BroadcastDevInfo = null;

    public BTListBaseAdapter(Context context) {
        mContext= context;
        mInflater = LayoutInflater.from(context);
        init();
    }


    public void init() {
        mData = new ArrayList<Map<String, Object>>();
        SharedPreferences db = PreferenceManager.getDefaultSharedPreferences(mContext);
        Gson gson = new Gson();
        String retBDevInfoStr = db.getString(DB_BROADCAST_DEVICES_TAG, null);
//        Log.e(TAG,"popAwindow BTListBaseAdapter retBDevInfoStr "+retBDevInfoStr);
        Type type = new TypeToken<ArrayList<HashMap<String, Object>>>() {}.getType();
        BroadcastDevInfo = gson.fromJson(retBDevInfoStr, type);

        if (!retBDevInfoStr.contains("null")) {
            Iterator<HashMap<String, Object>> it = BroadcastDevInfo.iterator();
            HashMap<String, Object> map = null;
            for (; it.hasNext(); ) {
                map = it.next();
                if(map.get("Type").toString().contains("Device") == true && !map.get("MESH_ADDR").toString().isEmpty() && map.get("GROUP_ADDR").toString().contains("000")) {
                    map.put("img", R.drawable.ic_bluetooth);
                    map.put("title",map.get("Name"));
                    mData.add(map);
                }

            }

        }

        isSelected = new HashMap<Integer, Boolean>();
        for (int i = 0; i < mData.size(); i++) {
            isSelected.put(i, false);
        }
    }

    @Override
    public int getCount() {
        return mData.size();
    }

    @Override
    public Object getItem(int position) {
        return null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder holder = null;

        if (convertView == null) {
            holder = new ViewHolder();
            convertView = mInflater.inflate(R.layout.bt_device_group_select_list, null);
            holder.img = (ImageView) convertView.findViewById(R.id.img);
            holder.title = (TextView) convertView.findViewById(R.id.title);
            holder.cBox = (CheckBox) convertView.findViewById(R.id.cb);
            convertView.setTag(holder);
        } else {
            holder = (ViewHolder) convertView.getTag();
        }
        holder.img.setBackgroundResource((Integer) mData.get(position).get(
                "img"));
        holder.title.setText(mData.get(position).get("title").toString());
        holder.cBox.setChecked(isSelected.get(position));
        return convertView;
    }

    public final class ViewHolder {
        public ImageView img;
        public TextView title;
        public CheckBox cBox;
    }
}

