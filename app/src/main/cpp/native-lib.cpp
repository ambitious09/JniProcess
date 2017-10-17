#include "native-lib.h"

typedef struct GifBean{
    int current_frame;
    int total_frame;
    int  *dealys;
} GifBean;

static const char APP_DIR[] = "/data/data/com.lhh.jniprocess";
static const char observerFile[] = "/data/data/com.lhh.jniprocess/observedFile";
const char *userId;
int m_child;
int m_parent = -1;
const char *PATH = "/data/data/com.lhh.jniprocess/my.sock";


void drawFrame(GifFileType *pType, GifBean *pBean, AndroidBitmapInfo info, void *pVoid);

extern "C" {
JNIEXPORT void JNICALL
Java_com_lhh_jniprocess_Manger_createWatcher(JNIEnv *env, jobject instance, jstring userId_) {
   userId = env->GetStringUTFChars(userId_, 0);

   create_child();

    env->ReleaseStringUTFChars(userId_, userId);
}

JNIEXPORT void JNICALL
Java_com_lhh_jniprocess_Manger_connectToMonitor(JNIEnv *env, jobject instance) {
//    子进程1    父进程2
    int sockfd;
    struct sockaddr_un  addr;
    while (1){
        LOGE("客户端  父进程开始连接");
        sockfd=socket(PF_LOCAL, SOCK_STREAM, 0);
//        sockfd=socket(AF_LOCAL, SOCK_STREAM, 0);
        if (sockfd < 0) {
            return;
        }
        memset(&addr, 0, sizeof(sockaddr_un));
        addr.sun_family = AF_LOCAL;
        strcpy(addr.sun_path, PATH);
        if (connect(sockfd, (const sockaddr *) &addr, sizeof(addr)) < 0) {
            LOGE("连接失败  休眠");
//            连接失败
            close(sockfd);
            sleep(1);
//            再来继续下一次尝试
            continue;
        }
//        连接成功
        m_parent = sockfd;
        LOGE("连接成功  父进程跳出循环");
        break;
    }

}


JNIEXPORT void JNICALL
Java_com_lhh_jniprocess_MainActivity_load__ILjava_lang_String_2(JNIEnv *env, jobject instance,
                                                                jint sdk, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);

    pid_t pid=fork();
    if (pid < 0) {
        LOGD("fork失败");
//        系统fork（）
    } else if (pid > 0) {
        LOGD("父进程");
    } else {
        LOGD("子进程");
        //    初始化  inotify
        int fileDescriple = inotify_init();
        int watch=inotify_add_watch(fileDescriple, path, IN_DELETE_SELF);
        void *p_buf=malloc(sizeof(struct inotify_event));
        //        阻塞式函数  anr
        size_t readBytes=read(fileDescriple,p_buf, sizeof(struct inotify_event));
        inotify_rm_watch(fileDescriple, watch);
        LOGD("跳转网页");
//        铁了心要删除app  sdk   17   am  设置到环境变量   多用户的操作
        if (sdk < 17) {
            execlp("am", "am", "start", "-a", "android.intent.action.VIEW", "-d",
                   "http://www.baidu.com",NULL);

        } else{
            execlp("am", "am", "start","--user","0","-a", "android.intent.action.VIEW", "-d",
                   "http://www.baidu.com",NULL);
        }
    }

    env->ReleaseStringUTFChars(path_, path);
}


JNIEXPORT void JNICALL
Java_com_lhh_jniprocess_MainActivity_init(JNIEnv *env, jobject instance, jint sdk) {
//创建一个进程  多个返回值
  pid_t pid=   fork();

    if(pid<0){
LOGD("进程失败");
    } else if (pid>0){
           LOGD("父进程");
    } else{
        LOGD("子进程");
   int observer=     open(observerFile,O_RDONLY);
        LOGD("父进程observer=");
        if (observer==-1) {
            observer=open(observerFile, O_CREAT);
        }
        int fileDescriple= inotify_init();
//        监听文件
        int watch=inotify_add_watch(fileDescriple,observerFile,IN_ALL_EVENTS);
        if (watch < 0) {
            exit(0);
        }
   void *p_bur =  malloc(sizeof(struct inotify_event));
     ssize_t read_bities=  read(fileDescriple,p_bur,sizeof(struct inotify_event));
        if (((struct  inotify_event *)p_bur)->mask==IN_DELETE_SELF){

       FILE  *app_file=   fopen(APP_DIR,"r");
            if (app_file==NULL){
                 inotify_rm_watch(fileDescriple,watch);
            } else{
                // 重新创建被监听文件，并重新监听
                fclose(app_file);
                FILE *p_observeleFile = fopen(observerFile, "w");
                int watchDescip = inotify_add_watch(fileDescriple, observerFile, IN_ALL_EVENTS);
            }
        }
              free(p_bur);
        if (sdk < 17) {
            execlp("am", "am", "start", "-a", "android.intent.action.VIEW", "-d",
                   "http://www.dongnaoedu.com", NULL);
        } else{
            execlp("am", "am", "start","--user","0","-a", "android.intent.action.VIEW", "-d",
                   "http://www.dongnaoedu.com", NULL);
        }

        exit(0);
    }

}


//gif
JNIEXPORT jlong JNICALL
Java_com_lhh_jniprocess_gifdemo_GifHandler_loadPath(JNIEnv *env, jobject instance, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);
    int err;
//用系统函数打开一个gif文件   返回一个结构体，这个结构体为句柄
    GifFileType  *gifFileType= DGifOpenFileName(path,&err);
    DGifSlurp(gifFileType);
           GifBean *gifBean= (GifBean *) malloc(sizeof(GifBean));
    //    清空内存地址
    memset(gifBean, 0, sizeof(GifBean));
    gifFileType->UserData=gifBean;
    gifBean->dealys= (int *) malloc(sizeof(int) * gifFileType->ImageCount);
    memset(gifBean->dealys, 0, sizeof(int) * gifFileType->ImageCount);
    gifBean->total_frame = gifFileType->ImageCount;
    ExtensionBlock *ext;
    for (int i = 0; i < gifFileType->ImageCount; ++i) {
        SavedImage frame = gifFileType->SavedImages[i];
        for (int j = 0; j < frame.ExtensionBlockCount; ++j) {
            if (frame.ExtensionBlocks[j].Function == GRAPHICS_EXT_FUNC_CODE) {
                ext = &frame.ExtensionBlocks[j];
                break;
            }
        }
        if (ext) {
            int frame_delay = 10 * (ext->Bytes[2] << 8 | ext->Bytes[1]);
            LOGE("时间  %d   ",frame_delay);
            gifBean->dealys[i] = frame_delay;

        }
    }
    LOGE("gif  长度大小    %d  ",gifFileType->ImageCount);
    env->ReleaseStringUTFChars(path_, path);
    return (jlong) gifFileType;
}

JNIEXPORT jint JNICALL
Java_com_lhh_jniprocess_gifdemo_GifHandler_getWidth__J(JNIEnv *env, jobject instance,
                                                        jlong ndkGif) {
          GifFileType *gifFileType = (GifFileType *) ndkGif;


    return gifFileType->SWidth;

}

JNIEXPORT jint JNICALL
Java_com_lhh_jniprocess_gifdemo_GifHandler_getHeight__J(JNIEnv *env, jobject instance,
                                                        jlong ndkGif) {
    GifFileType *gifFileType = (GifFileType *) ndkGif;

    return  gifFileType->SHeight;

}

JNIEXPORT jint JNICALL
Java_com_lhh_jniprocess_gifdemo_GifHandler_updateFrame__JLandroid_graphics_Bitmap_2(JNIEnv *env,
                                                                                    jobject instance,
                                                                                    jlong ndkGif,
                                                                                    jobject bitmap) {
    //强转代表gif图片的结构体
    GifFileType *gifFileType= (GifFileType *)ndkGif;
    GifBean * gifBean= (GifBean *) gifFileType->UserData;
    AndroidBitmapInfo info;
    //代表一幅图片的像素数组
    void *pixels;
    AndroidBitmap_getInfo(env,bitmap,&info);
    //锁定bitmap  一幅图片--》二维 数组   ===一个二维数组
    AndroidBitmap_lockPixels(env,bitmap,&pixels);
    // TODO
    drawFrame(gifFileType, gifBean, info, pixels);
    //播放完成之后   循环到下一帧
    gifBean->current_frame+=1;
    LOGE("当前帧  %d  ",gifBean->current_frame);
    if (gifBean->current_frame >= gifBean->total_frame-1) {
        gifBean->current_frame=0;
        LOGE("重新过来  %d  ",gifBean->current_frame);
    }
    AndroidBitmap_unlockPixels(env, bitmap);
    return gifBean->dealys[gifBean->current_frame];

}
}

void drawFrame(GifFileType *gifFileType, GifBean *gifBean, AndroidBitmapInfo info, void *pVoid) {
    //播放底层代码
//        拿到当前帧
    SavedImage savedImage = gifFileType->SavedImages[gifBean->current_frame];

    GifImageDesc frameInfo = savedImage.ImageDesc;
    //整幅图片的首地址
    int* px = (int *)pVoid;
//    每一行的首地址
    int *line;
    //   其中一个像素的位置  不是指针  在颜色表中的索引
    int pointPixel;
    GifByteType  gifByteType;
    GifColorType gifColorType;
  ColorMapObject * colorMapObject=     frameInfo.ColorMap;
    px = (int *) ((char*)px + info.stride * frameInfo.Top);
    for (int y =frameInfo.Top; y < frameInfo.Top+frameInfo.Height; ++y) {
        line=px;
        for (int x = frameInfo.Left; x< frameInfo.Left + frameInfo.Width; ++x) {
            pointPixel = (y - frameInfo.Top) * frameInfo.Width + (x - frameInfo.Left);
            gifByteType = savedImage.RasterBits[pointPixel];
            gifColorType = colorMapObject->Colors[gifByteType];
            line[x] = argb(255,gifColorType.Red, gifColorType.Green, gifColorType.Blue);
        }
        px = (int *) ((char*)px + info.stride);
    }
}

void create_child() {
    pid_t pid = fork();
//
    if (pid < 0) {

    } else if (pid > 0) {
//父进程
    } else if (pid == 0){
        LOGE("子进程开启 ");
//       守护进程
        child_do_work();
    }
}
void child_do_work(){
//    守护进程
//   1 建立socket服务
//    2读取消息
    if(child_create_channel()) {
        child_listen_msg();
    }


}

int child_create_channel() {
//    创建socket  listenfd 对象
  int listenid=socket(AF_LOCAL,SOCK_STREAM,0);
    //    取消之前进程文件连接
    unlink(PATH);
    struct sockaddr_un addr;
    //    清空内存
    memset(&addr, 0,sizeof(sockaddr_un));
    //void *memset(void *s,int c,size_t n)
//    总的作用：将已开辟内存空间 s 的首 n 个字节的值设为值 c。

    addr.sun_family=AF_LOCAL;
    strcpy(addr.sun_path,PATH);
    int connfd=0;
    LOGE("绑定端口号");
    if (bind(listenid, (const sockaddr *) &addr, sizeof(addr))<0){
        LOGE("绑定错误");
        return 0;
    }
    listen(listenid,5);
    while (1){
        LOGE("子进程循环等待连接  %d ",m_child);
//        不断接受客户端请求的数据
//        等待 客户端连接  accept阻塞式函数
        if ((connfd=accept(listenid,NULL,NULL))<0){
              if (errno==EINTR){
                  continue;
              } else{
                  LOGE("读取错误");
                  return 0;
              }
        }
        //        apk 进程连接上了
        m_child = connfd;
        LOGE("apk 父进程连接上了  %d ",m_child);
        break;
    }
    LOGE("返回成功");
    return 1;
}

void child_listen_msg() {
 fd_set  rfds;
    while (1){
        //清空端口号
        FD_ZERO(&rfds);
        FD_SET(m_child,&rfds);
        //        设置超时时间
        struct timeval timeout={3,0};
       int  r=   select(m_child+1,&rfds,NULL,NULL,&timeout);
        LOGE("读取消息前  %d  ",r);
        if (r>0){
            char pkg[256]={0};
            //            确保读到的内容是制定的端口号
            if (FD_ISSET(m_child,&rfds)){
                //                阻塞式函数  客户端写到内容  apk进程  没有进行任何写入    连接
                int result=  read(m_child,pkg, sizeof(pkg));
                //                读到内容的唯一方式 是客户端断开
                LOGE("重启父进程  %d ",result);
                LOGE("读到信息  %d    userid  %d ",result,userId);
                execlp("am", "am", "startservice", "--user",userId,
                       "com.lhh.jniprocess/com.lhh.jniprocess.ProcessService", (char*)NULL);
                break;
            }

        }
    }
}

