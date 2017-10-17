package com.lhh.jniprocess;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.Process;
import android.support.annotation.Nullable;
import android.util.Log;

import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by david on 2017/9/6.
 */

public class ProcessService extends Service {

    private static final String TAG = "tuch";
    int i=0;
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Manger wathcer=new Manger();
        wathcer.createWatcher(String.valueOf(Process.myUid()));
        wathcer.connectToMonitor();
        Timer timer = new Timer();
        //定时器
        timer.scheduleAtFixedRate(
                new TimerTask() {
                    public void run() {
                        Log.i(TAG, "服务  "+i);
                        i++;
                    }
                }, 0, 1000 * 3);
    }
}
