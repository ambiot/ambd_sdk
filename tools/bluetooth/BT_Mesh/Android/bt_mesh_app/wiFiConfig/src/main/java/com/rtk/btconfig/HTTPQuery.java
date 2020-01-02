package com.rtk.btconfig;

import android.util.Log;

import com.rtk.btconfigbluetooth.BTConfig.BTConfig;
import com.rtk.btconfigbluetooth.BTConfig.BTConfigState;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;

/**	The thread for connecting to repeater **/
public class HTTPQuery {
	private String TAG = "HTTPQueryThread";
	
	private boolean mIsPause = false;

	String mServer_addr;
	String http_response;
	String mQueryStr;

	public HTTPQuery(String address, String queryStr){
        mServer_addr = new String(address);
        mQueryStr = new String(queryStr);
    }

	public synchronized void setHTTPQueryString(String query){
        mQueryStr = query;
	}

	public synchronized void setServerAddress(String address){
		mServer_addr = address;
	}

	/** interrupt the thread **/
	public synchronized void onThreadPause(){
		mIsPause = true;
		 try {
			this.wait();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}  
	}
	
	/** make the thread go-on **/
	public synchronized void onThreadResume() {  
        mIsPause = false;  
        this.notify();  
    }

//    public String getQueryResult(){
//
//    }

	 /**  receive message from repeater **/

	public String run() {
//		while(!mIsPause && !isInterrupted())
        try {
            StringBuilder stringBuilder = new StringBuilder("http://" + mServer_addr + "/");
            stringBuilder.append("test_get?");
            String[] array = mQueryStr.split("=");
            stringBuilder.append(array[0] + "=");
            stringBuilder.append(URLEncoder.encode(array[1], "UTF-8"));

            Log.e(TAG,"whlole length: "+ stringBuilder.length());

            URL obj = new URL(stringBuilder.toString());

            HttpURLConnection con = (HttpURLConnection) obj.openConnection();
            con.setRequestMethod("GET");
            con.setRequestProperty("User-Agent", "Mozilla/5.0");
            con.setRequestProperty("Accept-Charset", "UTF-8");
            con.setUseCaches(false);



            Log.e(TAG, "\nSending request to URL : " + obj.toString());
            Log.e(TAG, "Response Code : " + con.getResponseCode());
            Log.e(TAG, "Response Message : " + con.getResponseMessage());

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
        }
        return null;
	}

}
