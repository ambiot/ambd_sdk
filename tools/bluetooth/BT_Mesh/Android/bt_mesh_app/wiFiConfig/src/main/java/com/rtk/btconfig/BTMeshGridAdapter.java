package com.rtk.btconfig;

import android.widget.BaseAdapter;
import android.content.Context;
import android.graphics.Bitmap;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import java.util.List;


public class BTMeshGridAdapter extends BaseAdapter
{
    private List<String> devicesList;
    private Context mContext;

    public BTMeshGridAdapter(List<String> devicesList, Context mContext) {
        this.devicesList = devicesList;
        this.mContext = mContext;
    }

    /**
     *
     *
     * @return
     */
    @Override
    public int getCount() {
        return devicesList.size();
    }

    @Override
    public Object getItem(int position) {
        return devicesList.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder holder;
        if (convertView == null) {
            convertView = LayoutInflater.from(mContext).inflate(R.layout.grid_pick, parent, false);
            holder = new ViewHolder();
            holder.img_item = (ImageView) convertView.findViewById(R.id.item_img);
            holder.txt_name = (TextView) convertView.findViewById(R.id.name);
            convertView.setTag(holder);
        } else {
            holder = (ViewHolder) convertView.getTag();
        }

        holder.txt_name.setText(devicesList.get(position).toString());


        holder.img_item.setImageResource(R.drawable.ic_bluetooth);
        holder.img_item.setScaleX(1.5f);
        holder.img_item.setScaleY(1.5f);
        return convertView;
    }


    static class ViewHolder {
        ImageView img_item;
        TextView txt_name;
    }

}


