package com.lhh.jniprocess.gifdemo

import android.Manifest
import android.graphics.Bitmap
import android.os.*
import android.support.v4.app.ActivityCompat
import android.support.v7.app.AppCompatActivity
import android.view.View
import com.lhh.jniprocess.R
import kotlinx.android.synthetic.main.activity_gif.*
import java.io.File


class GifActivity : AppCompatActivity() {
    var gifHandler:GifHandler? = null;
    var bitmap:Bitmap?=null;
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_gif)
        if (Build.VERSION.SDK_INT >= 23) {
            val mPermissionList = arrayOf<String>(Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.CALL_PHONE, Manifest.permission.READ_LOGS, Manifest.permission.READ_PHONE_STATE, Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.SET_DEBUG_APP, Manifest.permission.SYSTEM_ALERT_WINDOW, Manifest.permission.GET_ACCOUNTS, Manifest.permission.WRITE_APN_SETTINGS)

            ActivityCompat.requestPermissions(this, mPermissionList, 123)
        }
    }
     fun ndkLoadGif(view: View) {
        var file=File(Environment.getExternalStorageDirectory(),"demo.gif");
         gifHandler=GifHandler(file.absolutePath);
         var width= gifHandler!!.getWidth()
         var height= gifHandler!!.getHeight();
         bitmap= Bitmap.createBitmap(width,height,Bitmap.Config.ARGB_8888);
         var nextTime=gifHandler!!.updateFrame(bitmap);
         handler.sendEmptyMessageDelayed(1, nextTime.toLong());

    }
 var handler= object : Handler() {
    override fun handleMessage(msg: Message?) {
        var nextTime=gifHandler!!.updateFrame(bitmap);
        this.sendEmptyMessageDelayed(1, nextTime.toLong());
        image.setImageBitmap(bitmap);

    }
}
}
