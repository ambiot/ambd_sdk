package com.rtk.simpleconfig_wizard;

import java.security.MessageDigest;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

public class AESCrypt {

	public static String encrypt(String key, String cleartext) throws Exception {
		byte[] md5Key = MD5(key.getBytes());
		byte[] result = encrypt(md5Key, cleartext.getBytes());
		return toHex(result);
	}

	public static String decrypt(String key, String encrypted) throws Exception {
		byte[] md5Key = MD5(key.getBytes());
		byte[] result = decrypt(md5Key, toByte(encrypted));
		return new String(result);
	}

	public static byte[] MD5(byte[] key) throws Exception {
		byte[] md5_digest = new byte[16];
		MessageDigest mDigest;

		mDigest = MessageDigest.getInstance("MD5");
		mDigest.update(key, 0, key.length);
		md5_digest = mDigest.digest();

	    return md5_digest;
	}

	public static byte[] encrypt(byte[] raw, byte[] clear) throws Exception {
	    SecretKeySpec skeySpec = new SecretKeySpec(raw, "AES/ECB/PKCS5Padding");
		Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
	    cipher.init(Cipher.ENCRYPT_MODE, skeySpec);
	    byte[] encrypted = cipher.doFinal(clear);

	    return encrypted;
	}

	public static byte[] decrypt(byte[] raw, byte[] encrypted) throws Exception {
	    SecretKeySpec skeySpec = new SecretKeySpec(raw, "AES/ECB/PKCS5Padding");
		Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
	    cipher.init(Cipher.DECRYPT_MODE, skeySpec);
	    byte[] decrypted = cipher.doFinal(encrypted);
		return decrypted;
	}

	public static byte[] toByte(String hexString) {
		int len = hexString.length()/2;
		byte[] result = new byte[len];
		for (int i = 0; i < len; i++)
			result[i] = Integer.valueOf(hexString.substring(2*i, 2*i+2), 16).byteValue();
		return result;
	}

	public static String toHex(byte[] buf) {
		if (buf == null)
			return "";
		StringBuffer result = new StringBuffer(2*buf.length);
		for (int i = 0; i < buf.length; i++) {
			appendHex(result, buf[i]);
		}
		return result.toString();
	}

	private final static String HEX = "0123456789ABCDEF";
	private static void appendHex(StringBuffer sb, byte b) {
		sb.append(HEX.charAt((b>>4)&0x0f)).append(HEX.charAt(b&0x0f));
	}
}
