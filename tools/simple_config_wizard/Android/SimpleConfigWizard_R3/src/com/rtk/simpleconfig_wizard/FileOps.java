package com.rtk.simpleconfig_wizard;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;

import android.os.Environment;
import android.util.Log;

public class FileOps {
	private static final String TAG = "FileOps";

	private String SDPATH = Environment.getExternalStorageDirectory()+"/";
	private String CFGFOLDER = "rtk_sc_wizard/";
	public static String SsidPasswdFile = "wizard1";
	public static String CfgPinFile = "wizard2";
	public static String CtlPinFile = "wizard3";
	public static String PASSWD;

	private boolean checkFileExists(String path) {
	    File file = new File(path);
	    return file.exists();
	}

	private boolean createDir(String dir) {
  		File dfile = new File(dir);
  		if(dfile.exists())
  			return true;
  		return dfile.mkdir();
    }

	private boolean createFile(String file) throws Exception
	{
        File ffile = new File(file);
    	return ffile.createNewFile();
	}

//	private boolean deleteFile(String file) throws Exception
//	{
//        File ffile = new File(file);
//		Log.d(TAG, "createFile: " + ffile);
//    	return ffile.delete();
//	}

	public void SetKey(String key)
	{
		PASSWD = key;
//		Log.d(TAG, "PASSWD: " + PASSWD);
	}


    public RandomAccessFile openFile(String filename) throws Exception
    {
        RandomAccessFile rf = null;
		String dir = SDPATH + CFGFOLDER;
		String file = dir + filename;
//		Log.d(TAG, "openFile: " + file);

		if(!checkFileExists(file)) {
			if(!createDir(dir)) {
				//Log.e(TAG, "Create Dir Error");
				return null;
			}
			if(!createFile(file)) {
				Log.e(TAG, "Create File Error");
				return null;
			}
		}

        rf = new RandomAccessFile(file, "rw");

        return rf;
    }

    public void writeFile(RandomAccessFile rf, String str) throws Exception
    {
    	if(rf==null) {
    		return;
    	}

    	String estr = AESCrypt.encrypt(PASSWD, str);
//		Log.d(TAG, "estr: " + estr);
        rf.writeBytes(estr);
    }

    public String readFile(RandomAccessFile rf) throws Exception
    {
        String str = null;
        byte[] strbuf = null;
        int len = 0 ;

    	if(rf==null) {
    		return null;
    	}

        len = (int)rf.length();
		if(len==0) {
			return null;
		}

        strbuf = new byte[len];
        rf.read(strbuf, 0, len);
//        for(int i=0; i<strbuf.length; i++)
//    		Log.d(TAG, "" + strbuf[i]);
        str = new String(strbuf);
//		Log.d(TAG, "read str: " + str);

    	String dstr = AESCrypt.decrypt(PASSWD, str);
//		Log.d(TAG, "decrypt str: " + dstr);

        return dstr;
    }

    public void closeFile(RandomAccessFile rf) throws Exception
    {
    	if(rf==null)
    		return;

        rf.close();
    }


	public void ParseSsidPasswdFile(String ssid)
	{
    	RandomAccessFile rf = null;
    	String str = null;

		try {
			rf = openFile(FileOps.SsidPasswdFile);
		} catch (Exception e1) {
			e1.printStackTrace();
			Log.e(TAG, "Open File Error");
			return;
		}

		try {
			str = readFile(rf);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Read File Error");
			try {
				rf.setLength(0);
			} catch (IOException e1) {
				e1.printStackTrace();
				Log.e(TAG, "Set Length Error");
				return;
			}
			return;
		}
//		Log.d(TAG, "Read: " + str);

    	SCCtlOps.StoredPasswd = new String();
		if(str==null) {
			//Log.e(TAG, "Null File");
		} else {
		    String[] items = str.split("\\|");
		    for(int i=0; i<items.length; i++) {
//				System.out.printf("items[%d]: %s\n", i, items[i]);
			    String[] subitems = items[i].split("\\:");
//			    for(int j=0; j<subitems.length; j++) {
//					Log.d(TAG, String.format("subitems[%d]: %s\n", j, subitems[j]));
//			    }
//				Log.d(TAG, String.format("Selected SSID: %s\n", ssid));
			    if(ssid.equals(subitems[0]) && !subitems[1].equals("null")) {
			    	SCCtlOps.StoredPasswd += subitems[1];
//					Log.d(TAG, "Find already existed SSID");
			    	break;
			    }
		    }
		}

    	try {
    		closeFile(rf);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Close File Error");
		}
	}

	public void UpdateSsidPasswdFile(boolean isOpenNetwork)
	{
    	RandomAccessFile rf;
		try {
			rf = openFile(FileOps.SsidPasswdFile);
		} catch (Exception e2) {
			e2.printStackTrace();
			Log.e(TAG, "Open File Error");
    		return;
		}

    	long len=0;
    	boolean isOld = false;
		String getstr = new String();
		String setstr = new String();
    	try {
			len = rf.length();
		} catch (IOException e1) {
			e1.printStackTrace();
			Log.e(TAG, "Get Length Error");
    		return;
		}
		if(len>0) {
			try {
				getstr = readFile(rf);
			} catch (Exception e) {
				e.printStackTrace();
				Log.e(TAG, "Read File Error");
	    		return;
			}
//			Log.d(TAG, "getstr: " + getstr);

		    String[] items = getstr.split("\\|");
		    for(int i=0; i<items.length; i++) {
//				System.out.printf("items[%d]: %s\n", i, items[i]);
			    String[] subitems = items[i].split("\\:");
//			    for(int j=0; j<subitems.length; j++) {
//					System.out.printf("subitems[%d]: %s\n", j, subitems[j]);
//			    }
			    if(SCCtlOps.ConnectedSSID.equals(subitems[0])) {
			    	isOld = true;
//					Log.d(TAG, "Refresh old");
			    	if(isOpenNetwork)
			    		setstr += SCCtlOps.ConnectedSSID + ":null|";
			    	else
			    		setstr += SCCtlOps.ConnectedSSID + ":" + SCCtlOps.ConnectedPasswd + "|";
			    } else {
//					Log.d(TAG, "Re-Add existed");
				    setstr += subitems[0] + ":" + subitems[1] + "|";
			    }
		    }
		}
		if(!isOld) {
//			Log.d(TAG, "Add new");
	    	if(isOpenNetwork)
	    		setstr += SCCtlOps.ConnectedSSID + ":null|";
	    	else
	    		setstr += SCCtlOps.ConnectedSSID + ":" + SCCtlOps.ConnectedPasswd + "|";
		}

		try {
			rf.seek(0); //re-write all info
		} catch (IOException e) {
			e.printStackTrace();
			Log.e(TAG, "Re-Seek Error");
    		return;
		}
    	try {
    		writeFile(rf, setstr);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Write File Error");
    		return;
		}

    	try {
    		closeFile(rf);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Close File Error");
    		return;
		}
	}

	public String ParseCfgPinFile()
	{
    	RandomAccessFile rf = null;
    	String getstr = null;

		try {
			rf = openFile(FileOps.CfgPinFile);
		} catch (Exception e1) {
			e1.printStackTrace();
			Log.e(TAG, "Open File Error");
			return null;
		}

		try {
			getstr = readFile(rf);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Read File Error");
			try {
				rf.setLength(0);
			} catch (IOException e1) {
				e1.printStackTrace();
				Log.e(TAG, "Set Length Error");
				return null;
			}
			return null;
		}
//		Log.d(TAG, "Read: " + getstr);

    	try {
    		closeFile(rf);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Close File Error");
		}

		return getstr;
	}

	public void UpdateCfgPinFile(String pin)
	{
    	RandomAccessFile rf;
		try {
			rf = openFile(FileOps.CfgPinFile);
		} catch (Exception e2) {
			e2.printStackTrace();
			Log.e(TAG, "Open File Error");
    		return;
		}

    	try {
    		writeFile(rf, pin);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Write File Error");
    		return;
		}

    	try {
    		closeFile(rf);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Close File Error");
    		return;
		}
	}

	public String ParseCtlPinFile(String mac)
	{
    	RandomAccessFile rf = null;
    	String getstr = null;
    	String pin = null;

		try {
			rf = openFile(FileOps.CtlPinFile);
		} catch (Exception e1) {
			e1.printStackTrace();
			Log.e(TAG, "Open File Error");
			return null;
		}

		try {
			getstr = readFile(rf);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Read File Error");
			try {
				rf.setLength(0);
			} catch (IOException e1) {
				e1.printStackTrace();
				Log.e(TAG, "Set Length Error");
				return null;
			}
			return null;
		}
//		Log.d(TAG, "Read: " + getstr);

		if(getstr==null) {
			//Log.e(TAG, "Null File");
		} else {
		    String[] items = getstr.split("\\;");
		    for(int i=0; i<items.length; i++) {
//				System.out.printf("items[%d]: %s\n", i, items[i]);
			    String[] subitems = items[i].split("\\|");
//			    for(int j=0; j<subitems.length; j++) {
//					Log.d(TAG, String.format("subitems[%d]: %s\n", j, subitems[j]));
//			    }
//				Log.d(TAG, String.format("Selected MAC: %s\n", mac));
			    if(mac.equals(subitems[0]) && !subitems[1].equals("null")) {
			    	pin = subitems[1];
//					Log.d(TAG, "Find PIN");
			    	break;
			    }
		    }
		}

    	try {
    		closeFile(rf);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Close File Error");
		}

		return pin;
	}

	public void UpdateCtlPinFile(String mac, String pin)
	{
    	RandomAccessFile rf;
		try {
			rf = openFile(FileOps.CtlPinFile);
		} catch (Exception e2) {
			e2.printStackTrace();
			Log.e(TAG, "Open File Error");
    		return;
		}

    	long len=0;
    	boolean isOld = false;
		String getstr = new String();
		String setstr = new String();
    	try {
			len = rf.length();
		} catch (IOException e1) {
			e1.printStackTrace();
			Log.e(TAG, "Get Length Error");
    		return;
		}
		if(len>0) {
			try {
				getstr = readFile(rf);
			} catch (Exception e) {
				e.printStackTrace();
				Log.e(TAG, "Read File Error");
	    		return;
			}
//			Log.d(TAG, "getstr: " + getstr);

		    String[] items = getstr.split("\\;");
		    for(int i=0; i<items.length; i++) {
//				System.out.printf("items[%d]: %s\n", i, items[i]);
			    String[] subitems = items[i].split("\\|");
//			    for(int j=0; j<subitems.length; j++) {
//					System.out.printf("subitems[%d]: %s\n", j, subitems[j]);
//			    }
			    if(mac.equals(subitems[0])) {
			    	isOld = true;
//					Log.d(TAG, "Refresh old");
				    setstr += subitems[0] + "|" + pin + ";";
			    } else {
//					Log.d(TAG, "Re-Add existed");
				    setstr += subitems[0] + "|" + subitems[1] + ";";
			    }
		    }
		}
		if(!isOld) {
//			Log.d(TAG, "Add new");
	    	setstr += mac + "|" + pin + ";";
		}

//		Log.d(TAG, "setstr: " + setstr);
		try {
			rf.seek(0); //re-write all info
		} catch (IOException e) {
			e.printStackTrace();
			Log.e(TAG, "Re-Seek Error");
    		return;
		}
    	try {
    		writeFile(rf, setstr);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Write File Error");
    		return;
		}

    	try {
    		closeFile(rf);
		} catch (Exception e) {
			e.printStackTrace();
			Log.e(TAG, "Close File Error");
    		return;
		}
	}
}
