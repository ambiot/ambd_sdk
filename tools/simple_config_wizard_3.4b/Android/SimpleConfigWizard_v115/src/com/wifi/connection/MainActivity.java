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

import com.rtk.simpleconfig_wizard.R;
import com.rtk.simpleconfig_wizard.SCCtlOps;

import android.content.Intent;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
//import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
//import android.util.Log;
import android.widget.Toast;

public class MainActivity extends Floating {
//	private static final String TAG = "WifiMainActivity";

	public static final String EXTRA_HOTSPOT = "com.wifi.connection.HOTSPOT";

	private ScanResult mScanResult;
	private Floating.Content mContent;
	private WifiManager mWifiManager;

	@Override
	protected void onNewIntent (Intent intent) {
		setIntent(intent);
		// This activity has "singleInstance" launch mode.
		// Update content to reflect the newest intent.
		doNewIntent(intent);
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		mWifiManager = (WifiManager)getSystemService(WIFI_SERVICE);

		doNewIntent(getIntent());
	}

	private boolean isAdHoc(final ScanResult scanResule) {
		return scanResule.capabilities.indexOf("IBSS") != -1;
	}

	private void doNewIntent(final Intent intent) {
		if(SCCtlOps.addNewNetwork)
			mScanResult = SCCtlOps.reBuiltScanResult;
		else
			mScanResult = intent.getParcelableExtra(EXTRA_HOTSPOT);
//		Log.i(TAG, "mScanResult: " + mScanResult);
//		Log.d(TAG, "mScanResult.SSID: " + mScanResult.SSID);
//		Log.d(TAG, "mScanResult.BSSID: " + mScanResult.BSSID);
//		Log.d(TAG, "mScanResult.capabilities: " + mScanResult.capabilities);
//		Log.d(TAG, "mScanResult.level: " + mScanResult.level);
//		Log.d(TAG, "mScanResult.frequency: " + mScanResult.frequency);

		if(mScanResult == null) {
			Toast.makeText(this, "No data in Intent!", Toast.LENGTH_LONG).show();
			finish();
			return;
		}

		if(isAdHoc(mScanResult)) {
			Toast.makeText(this, R.string.adhoc_not_supported_yet, Toast.LENGTH_LONG).show();
			finish();
			return;
		}

		final String security = Wifi.ConfigSec.getScanResultSecurity(mScanResult);
		final WifiConfiguration config = Wifi.getWifiConfiguration(mWifiManager, mScanResult, security);

		if(config != null) {
//	        Log.d(TAG, "Remove already configured network\n");
			mWifiManager.removeNetwork(config.networkId);
		}
//        Log.d(TAG, "NewNetworkContent\n");
		mContent = new NewNetworkContent(this, mWifiManager, mScanResult);

//		if(config == null) {
//        Log.d(TAG, "NewNetworkContent\n");
//			mContent = new NewNetworkContent(this, mWifiManager, mScanResult);
//		} else {
//			final boolean isCurrentNetwork_ConfigurationStatus = config.status == WifiConfiguration.Status.CURRENT;
//			final WifiInfo info = mWifiManager.getConnectionInfo();
//			final boolean isCurrentNetwork_WifiInfo = info != null
//				&& android.text.TextUtils.equals(info.getSSID(), mScanResult.SSID)
//				&& android.text.TextUtils.equals(info.getBSSID(), mScanResult.BSSID);
//			if(isCurrentNetwork_ConfigurationStatus || isCurrentNetwork_WifiInfo) {
//		        Log.d(TAG, "CurrentNetworkContent\n");
//				mContent = new CurrentNetworkContent(this, mWifiManager, mScanResult);
//			} else {
//		        Log.d(TAG, "ConfiguredNetworkContent\n");
//				mContent = new ConfiguredNetworkContent(this, mWifiManager, mScanResult);
//			}
//		}

		setContent(mContent);
	}
}
