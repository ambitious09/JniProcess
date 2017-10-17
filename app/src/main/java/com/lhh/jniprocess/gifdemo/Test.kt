package com.lhh.jniprocess.gifdemo

import android.os.Handler
import android.os.Message


/**
 * Created by 刘会华 on 2017/9/13.
 */
class Test {
    var handler: Handler = object : Handler() {
        override fun handleMessage(msg: Message) {
            this.sendEmptyMessageDelayed(1, 2)
        }
    }

}