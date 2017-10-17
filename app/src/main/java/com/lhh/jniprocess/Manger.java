package com.lhh.jniprocess;

/**
 * Created by 刘会华 on 2017/9/12.
 */

public class Manger {
    static {
        System.loadLibrary("native-lib");
    }
    public native void createWatcher(String userId);
    public native void connectToMonitor();
}
