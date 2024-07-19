//
// 文件管理
//

#ifndef NDKDEMO_FILEUTIL_H
#define NDKDEMO_FILEUTIL_H

#include <jni.h>
#include "JClazzUtil.h"
#include <iostream>
#include <fstream>

using namespace std;
//获取文件夹缓存
string fileCachePath(JNIEnv* env, jobject context){
    jobject file = callMethod(env, context, "getCacheDir", "()Ljava/io/File;");
    jstring path = (jstring)callMethod(env, file,"getAbsolutePath", "()Ljava/lang/String;");
    if (path != NULL){
        return jstring2string(env, path);
    }
    return NULL;
}

bool write_in_file(const char* file_path, const char* content){
    if (file_path == NULL || content == NULL){
        return false;
    }

    ofstream file;
    try {
        file.open(file_path, ios::app|ios::out);//追加/写入方式打开
        if (file.is_open()){
            //打开文件
            file << content;
            file.close();
        }
    } catch (exception& e){
        return false;
    }
    return true;
}

//读取内容失效后要清除
const char* read_in_file(const char* file_path){
    if (file_path == NULL){
        return NULL;
    }

    fstream file;
    try {
        file.open(file_path, ios::in|ios::binary);
        file.seekg(0, ios::end);
        char *buffer;
        long size;
        size = file.tellg();
        file.seekg(0, ios::beg);
        if (size == NULL){
            return NULL;
        }
        //以二进制形式读书数据
        buffer = new char[size];
        file.read(buffer, 1024);
        file.close();
        return buffer;
    } catch (exception e){
        //todo 处理异常
    }
    return NULL;
}

#endif //NDKDEMO_FILEUTIL_H
