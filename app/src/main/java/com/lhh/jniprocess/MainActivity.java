package com.lhh.jniprocess;

import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.util.LruCache;
import android.view.View;

import java.io.File;
import java.security.MessageDigest;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
   LruCache<String,Bitmap> lruCache;
    MessageDigest messageDigest;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Intent intent=new Intent(this,ProcessService.class);
        startService(intent);
        Log.i("tag", "onCreate: ");
        File file;
//        File.separator;Hash
        HashMap hashMap=new HashMap();
        hashMap.put(1,2);
        hashMap.put(1,3);
        Bitmap bitmap=null;
        lruCache.put("str",bitmap);
        int maxmemorySize=(int ) (Runtime.getRuntime().maxMemory()/1024);
        int cacheMemory=maxmemorySize/8;
            lruCache=new LruCache<String, Bitmap>(cacheMemory){
                @Override
                public void resize(int maxSize) {
                    super.resize(maxSize);
                }

                @Override
                protected void entryRemoved(boolean evicted, String key, Bitmap oldValue, Bitmap newValue) {
                    super.entryRemoved(evicted, key, oldValue, newValue);
                }

                @Override
                protected Bitmap create(String key) {
                    return super.create(key);
                }

                @Override
                protected int sizeOf(String key, Bitmap bitmap) {
                    return bitmap.getRowBytes()*bitmap.getHeight()/1024;
                }
            };
    }

    public void load(View view) {
//        init(Build.VERSION.SDK_INT);
//        load(Build.VERSION.SDK_INT,"/data/data/com.lhh.jniprocess");
    }

//    public native void init(int sdk);
public native void load(int sdk,String path);
    Handler han=new Handler(){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            int a=2;
            han.sendEmptyMessageDelayed(1,a);
        }
    };

}

