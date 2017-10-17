//
// Created by 刘会华 on 2017/9/7.
//
#include <stdio.h>
#include <jni.h>
#include <malloc.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include "gif_lib.h"
#include <android/bitmap.h>
#include <fcntl.h>
#include <stdint.h>
#include <android/log.h>
#include<sys/file.h>
#define LOG_TAG "System.out.c"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#ifndef JNIPROCESS_NATIVE_LIB_H
#define JNIPROCESS_NATIVE_LIB_H
#define  argb(a,r,g,b) ( ((a) & 0xff) << 24 ) | ( ((b) & 0xff) << 16 ) | ( ((g) & 0xff) << 8 ) | ((r) & 0xff)
#endif //JNIPROCESS_NATIVE_LIB_H
void create_child();
void child_do_work();
void child_listen_msg();
int child_create_channel();
