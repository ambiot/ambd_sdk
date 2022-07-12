/*
 * Wifi Connecter
 *
 * Copyright (c) 20101 Kevin Yuan (farproc@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **/

package com.wifi.connection;

import com.rtk.simpleconfig_wizard.FileOps;
import com.rtk.simpleconfig_wizard.R;
import com.rtk.simpleconfig_wizard.SCCtlOps;
import com.rtk.simpleconfig_wizard.MainActivity;

import android.app.ProgressDialog;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
//import android.util.Log;
import android.view.ContextMenu;
import android.view.MenuItem;
import android.view.View;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.View.OnClickListener;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;



public class NewNetworkContent extends BaseContent {
//	private static final String TAG = "NewNetworkContent";

	private boolean mIsOpenNetwork = false;

	public NewNetworkContent(final Floating floating, final WifiManager wifiManager, ScanResult scanResult) {
		super(floating, wifiManager, scanResult);

		mView.findViewById(R.id.Status).setVisibility(View.GONE);
		mView.findViewById(R.id.Speed).setVisibility(View.GONE);
		mView.findViewById(R.id.IPAddress).setVisibility(View.GONE);
		if(Wifi.ConfigSec.isOpenNetwork(mScanResultSecurity)) {
			mIsOpenNetwork = true;
			mView.findViewById(R.id.Password).setVisibility(View.GONE);
		} else {
			((TextView)mView.findViewById(R.id.Password_TextView)).setText(R.string.please_type_passphrase);
			((EditText)mView.findViewById(R.id.Password_EditText)).setText(SCCtlOps.StoredPasswd); //The last password hint
		}
	}

	private OnClickListener mConnectOnClick = new OnClickListener() {

		@Override
		public void onClick(View v) {
			
			
			
			SCCtlOps.ConnectedSSID = mScanResult.SSID; // Store SSID
//	        Log.d(TAG, "SSID��" + mScanResult.SSID);

			boolean connResult = false;
			if(mIsOpenNetwork) {
				SCCtlOps.IsOpenNetwork = true;
				connResult = Wifi.connectToNewNetwork(mFloating, mWifiManager, mScanResult, null, mNumOpenNetworksKept);
			} else {
				SCCtlOps.IsOpenNetwork = false;
				String passwd = ((EditText)mView.findViewById(R.id.Password_EditText)).getText().toString();
				connResult = Wifi.connectToNewNetwork(mFloating, mWifiManager, mScanResult
						, passwd
						, mNumOpenNetworksKept);

				if(connResult) {
					SCCtlOps.ConnectedPasswd = new String(passwd); // Store password
//	    	        Log.d(TAG, "Password��" + passwd);
				}
			}

//			if(!connResult) {
//				Toast.makeText(mFloating, R.string.toastFailed, Toast.LENGTH_LONG).show();
//			}

			mFloating.finish();

//			/** Update SSID and password */
//			if(connResult) {
//		    	FileOps fileOps = new FileOps();
//		    	fileOps.UpdateSsidPasswdFile(mIsOpenNetwork);
//			}
			
		}
	};

	private OnClickListener mOnClickListeners[] = {mConnectOnClick, mCancelOnClick};

	@Override
	public int getButtonCount() {
		return 2;
	}

	@Override
	public OnClickListener getButtonOnClickListener(int index) {
		return mOnClickListeners[index];
	}


	@Override
	public CharSequence getButtonText(int index) {
		switch(index) {
		case 0:
			return mFloating.getText(R.string.connect);
		case 1:
			return mFloating.getText(R.string.cancel);
//			return getCancelString();
		default:
			return null;
		}
	}

	@Override
	public CharSequence getTitle() {
		return mFloating.getString(R.string.wifi_connect_to, mScanResult.SSID);
	}

	@Override
	public boolean onContextItemSelected(MenuItem item) {
		return false;
	}

	@Override
	public void onCreateContextMenu(ContextMenu menu, View v,
			ContextMenuInfo menuInfo) {

	}
}
