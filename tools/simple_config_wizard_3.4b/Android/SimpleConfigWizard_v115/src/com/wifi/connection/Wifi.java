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

import java.util.Comparator;
import java.util.List;

import com.rtk.simpleconfig_wizard.SCCtlOps;
import android.content.Context;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.text.TextUtils;
import android.util.Log;

public class Wifi {

	public static final ConfigurationSecurities ConfigSec = ConfigurationSecurities.newInstance();

	private static final String TAG = "Wifi Connecter";

	/**
	 * Change the password of an existing configured network and connect to it
	 * @param wifiMgr
	 * @param config
	 * @param newPassword
	 * @return
	 */
	public static boolean changePasswordAndConnect(final Context ctx, final WifiManager wifiMgr, final WifiConfiguration config, final String newPassword, final int numOpenNetworksKept) {
		ConfigSec.setupSecurity(config, ConfigSec.getWifiConfigurationSecurity(config), newPassword);
		final int networkId = wifiMgr.updateNetwork(config);
		if(networkId == -1) {
			// Update failed.
			return false;
		}
		// Force the change to apply.
		wifiMgr.disconnect();
		return connectToConfiguredNetwork(ctx, wifiMgr, config, true);
	}

	/**
	 * Configure a network, and connect to it.
	 * @param wifiMgr
	 * @param scanResult
	 * @param password Password for secure network or is ignored.
	 * @return
	 */
	public static boolean connectToNewNetwork(final Context ctx, final WifiManager wifiMgr, final ScanResult scanResult, final String password, final int numOpenNetworksKept) {
		final String security = ConfigSec.getScanResultSecurity(scanResult);

		if(ConfigSec.isOpenNetwork(security)) {
			checkForExcessOpenNetworkAndSave(wifiMgr, numOpenNetworksKept);
		}

		WifiConfiguration config = new WifiConfiguration();
		if(SCCtlOps.isHiddenSSID)
			config.hiddenSSID = true;
		config.SSID = convertToQuotedString(scanResult.SSID);
		if(!SCCtlOps.isHiddenSSID)
			config.BSSID = scanResult.BSSID;
		ConfigSec.setupSecurity(config, security, password);

		int id = -1;
		try {
			id = wifiMgr.addNetwork(config);
		} catch(NullPointerException e) {
			Log.e(TAG, "Weird!! Really!! What's wrong??", e);
			// Weird!! Really!!
			// This exception is reported by user to Android Developer Console(https://market.android.com/publish/Home)
		}
		if(id == -1) {
			return false;
		}

		if(!wifiMgr.saveConfiguration()) {
			return false;
		}

		config = getWifiConfiguration(wifiMgr, config, security);
		if(config == null) {
			return false;
		}

		return connectToConfiguredNetwork(ctx, wifiMgr, config, true);
	}

	/**
	 * Connect to a configured network.
	 * @param wifiManager
	 * @param config
	 * @param numOpenNetworksKept Settings.Secure.WIFI_NUM_OPEN_NETWORKS_KEPT
	 * @return
	 */
	public static boolean connectToConfiguredNetwork(final Context ctx, final WifiManager wifiMgr, WifiConfiguration config, boolean reassociate) {
		final String security = ConfigSec.getWifiConfigurationSecurity(config);

		int oldPri = config.priority;
		// Make it the highest priority.
		int newPri = getMaxPriority(wifiMgr) + 1;
		if(newPri > MAX_PRIORITY) {
			newPri = shiftPriorityAndSave(wifiMgr);
			config = getWifiConfiguration(wifiMgr, config, security);
			if(config == null) {
				return false;
			}
		}

		// Set highest priority to this configured network
		config.priority = newPri;
		int networkId = wifiMgr.updateNetwork(config);
		if(networkId == -1) {
			return false;
		}

		// Do not disable others
		if(!wifiMgr.enableNetwork(networkId, false)) {
			config.priority = oldPri;
			return false;
		}

		if(!wifiMgr.saveConfiguration()) {
			config.priority = oldPri;
			return false;
		}

		// We have to retrieve the WifiConfiguration after save.
		config = getWifiConfiguration(wifiMgr, config, security);
		if(config == null) {
			return false;
		}

		ReenableAllApsWhenNetworkStateChanged.schedule(ctx);

		// Disable others, but do not save.
		// Just to force the WifiManager to connect to it.
		if(!wifiMgr.enableNetwork(config.networkId, true)) {
			return false;
		}

		final boolean connect = reassociate ? wifiMgr.reassociate() : wifiMgr.reconnect();
		if(!connect) {
			return false;
		}

		return true;
	}

	private static void sortByPriority(final List<WifiConfiguration> configurations) {
		java.util.Collections.sort(configurations, new Comparator<WifiConfiguration>() {

			@Override
			public int compare(WifiConfiguration object1,
					WifiConfiguration object2) {
				return object1.priority - object2.priority;
			}
		});
	}

	/**
	 * Ensure no more than numOpenNetworksKept open networks in configuration list.
	 * @param wifiMgr
	 * @param numOpenNetworksKept
	 * @return Operation succeed or not.
	 */
	private static boolean checkForExcessOpenNetworkAndSave(final WifiManager wifiMgr, final int numOpenNetworksKept) {
		final List<WifiConfiguration> configurations = wifiMgr.getConfiguredNetworks();
		sortByPriority(configurations);

		boolean modified = false;
		int tempCount = 0;
		for(int i = configurations.size() - 1; i >= 0; i--) {
			final WifiConfiguration config = configurations.get(i);
			if(ConfigSec.isOpenNetwork(ConfigSec.getWifiConfigurationSecurity(config))) {
				tempCount++;
				if(tempCount >= numOpenNetworksKept) {
					modified = true;
					wifiMgr.removeNetwork(config.networkId);
				}
			}
		}
		if(modified) {
			return wifiMgr.saveConfiguration();
		}

		return true;
	}

	private static final int MAX_PRIORITY = 99999;

	private static int shiftPriorityAndSave(final WifiManager wifiMgr) {
		final List<WifiConfiguration> configurations = wifiMgr.getConfiguredNetworks();
		sortByPriority(configurations);
		final int size = configurations.size();
		for(int i = 0; i < size; i++) {
			final WifiConfiguration config = configurations.get(i);
			config.priority = i;
			wifiMgr.updateNetwork(config);
		}
		wifiMgr.saveConfiguration();
		return size;
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

	public static WifiConfiguration getWifiConfiguration(final WifiManager wifiMgr, final ScanResult hotsopt, String hotspotSecurity) {
		final String ssid = convertToQuotedString(hotsopt.SSID);
		if(ssid.length() == 0) {
			return null;
		}

		final String bssid = hotsopt.BSSID;
		if(bssid == null) {
			return null;
		}

		if(hotspotSecurity == null) {
			hotspotSecurity = ConfigSec.getScanResultSecurity(hotsopt);
		}

		final List<WifiConfiguration> configurations = wifiMgr.getConfiguredNetworks();
		if(configurations == null) {
			return null;
		}

		for(final WifiConfiguration config : configurations) {
			if(config.SSID == null || !ssid.equals(config.SSID)) {
				continue;
			}
			if(config.BSSID == null || bssid.equals(config.BSSID)) {
				final String configSecurity = ConfigSec.getWifiConfigurationSecurity(config);
				if(hotspotSecurity.equals(configSecurity)) {
					return config;
				}
			}
		}
		return null;
	}

	public static WifiConfiguration getWifiConfiguration(final WifiManager wifiMgr, final WifiConfiguration configToFind, String security) {
		final String ssid = configToFind.SSID;
		if(ssid.length() == 0) {
			return null;
		}

		final String bssid = configToFind.BSSID;


		if(security == null) {
			security = ConfigSec.getWifiConfigurationSecurity(configToFind);
		}

		final List<WifiConfiguration> configurations = wifiMgr.getConfiguredNetworks();

		for(final WifiConfiguration config : configurations) {
			if(config.SSID == null || !ssid.equals(config.SSID)) {
				continue;
			}
			if(config.BSSID == null || bssid == null || bssid.equals(config.BSSID)) {
				final String configSecurity = ConfigSec.getWifiConfigurationSecurity(config);
				if(security.equals(configSecurity)) {
					return config;
				}
			}
		}
		return null;
	}

	public static String convertToQuotedString(String string) {
        if (TextUtils.isEmpty(string)) {
            return "";
        }

        final int lastPos = string.length() - 1;
        if(lastPos > 0 && (string.charAt(0) == '"' && string.charAt(lastPos) == '"')) {
            return string;
        }

        return "\"" + string + "\"";
    }

}
