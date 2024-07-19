#include <jni.h>
#include <string>
#include "include/JniUtil.h"
#include "include/android_log_print.h"
#include "include/FileUtil.h"
#include "pthread.h"
#include "web_task.h"


//线程处理
void * thread_t1(void * arg){
    LOGD("thread_t1  running");
    return NULL;
}

void test_request(){
    string url = "http://www.weather.com.cn/data/sk/101280601.html";
    WebTask task;
    task.SetUrl(url.c_str());
    task.SetConnectTimeout(5);
    task.DoGetString();
    if (task.WaitTaskDone() == 0){
        string result = task.GetResultString();
        LOGD("网络请求成功,结果：%s", result.c_str());
    } else {
        LOGD("网络请求失败,状态码：%d", task.WaitTaskDone());
    }
}


extern "C" JNIEXPORT jstring JNICALL
Java_cn_ndk_demo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_cn_ndk_demo_MainActivity_input(JNIEnv *env, jobject thiz, jstring input_) {
    // TODO: implement input()
    const char *input = env->GetStringUTFChars(input_, 0);
//    env->ReleaseStringUTFChars(input_, input);
    LOGD("hello world++");
    LOGD("this is jni log msg");
    return env->NewStringUTF(input);
}
extern "C"
JNIEXPORT jstring JNICALL
Java_cn_ndk_demo_MainActivity_test(JNIEnv *env, jobject thiz, jobject context) {
    // TODO: implement test()
    //jni 调用java对象参数
    jstring pkg_name = (jstring)callMethod(env, context, "getPackageName", "()Ljava/lang/String;");
    string cache_path = fileCachePath(env, context);
    LOGD("file_path:%s", cache_path.c_str());

    //文件读写操作
    string test_path = cache_path + "/" +"demo.txt";
    bool res = write_in_file(test_path.c_str(), "hello world");
    if (res) {
        LOGD("写入成功");
    } else {
        LOGD("写入失败");
    }
    const char* file_content = read_in_file(test_path.c_str());
    LOGD("文件内容:%s",file_content);
    delete[] file_content;

    //线程操作
    pthread_t thread1;
    pthread_create(&thread1, NULL, thread_t1, NULL);
    pthread_detach(thread1);

    test_request();

    return pkg_name;
}


