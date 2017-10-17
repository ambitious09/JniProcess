package com.lhh.jniprocess.gifdemo;

import android.graphics.Bitmap;
import android.util.Log;

/**
 * Created by 刘会华 on 2017/9/13.
 */

public class GifHandler {
    private long gifAddr;

    public GifHandler(String path) {
        Log.i("tag", "GifHandler: "+path);
        this.gifAddr = loadPath(path);
    }

    static {
        System.loadLibrary("native-lib");
    }

    private native long loadPath(String path);
    public native int getWidth(long ndkGif);
    public native int getHeight(long ndkGif);
    public native int updateFrame(long ndkGif, Bitmap bitmap);

    public int getWidth() {
        return getWidth(gifAddr);
    }
    public int getHeight() {
        return getHeight(gifAddr);
    }

    public int updateFrame(Bitmap bitmap) {
        return updateFrame(gifAddr,bitmap);
    }
}
