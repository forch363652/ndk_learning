//
//  基本工具
//

#ifndef NDKDEMO_JNIUTIL_H
#define NDKDEMO_JNIUTIL_H

#include <jni.h>
#include <string>
#include "JClazzUtil.h"

using namespace std;

//char to jstring
jstring char2jstring(JNIEnv *env, char *str) {
    //将对象弄成byte, 通过构造函数，生成jstring对象
    jbyteArray byte_array = env->NewByteArray(strlen(str));//创建数组
    jstring jstring_encode = env->NewStringUTF("utf-8");//utf-8
    jclass str_clazz = (jclass) env->NewGlobalRef(env->FindClass("java/lang/String"));//获取类
    jmethodID create_id = env->GetMethodID(str_clazz, "<init>", "([BLjava/lang/String;)V");
    return (jstring) env->NewObject(str_clazz, create_id, byte_array, jstring_encode);
}

//string to jstring
jstring string2jstring(JNIEnv *env, std::string str) {
    //将对象弄成byte, 通过构造函数，生成jstring对象
    const char *str_char = str.c_str();
    jbyteArray byte_array = env->NewByteArray(strlen(str_char));//创建数组
    jstring jstring_encode = env->NewStringUTF("utf-8");//utf-8
    jclass str_clazz = (jclass) env->NewGlobalRef(env->FindClass("java/lang/String"));//获取类
    jmethodID create_id = env->GetMethodID(str_clazz, "<init>", "([BLjava/lang/String;)V");
    return (jstring) env->NewObject(str_clazz, create_id, byte_array, jstring_encode);
}

//jstring to string
string jstring2string(JNIEnv *env, jstring jstr) {
    //生成byte， 在生成string
    jboolean is_get_success = false;
    const char *c_str = env->GetStringUTFChars(jstr, &is_get_success);
    if (!is_get_success) {
        return NULL;
    }
    string out_put(c_str);
    env->ReleaseStringUTFChars(jstr, c_str);
    return out_put;
}

//jstring to char*
const char *jstring2char(JNIEnv *env, jstring jstr) {
    string str = jstring2string(env, jstr);
    return str.c_str();
}

#endif //NDKDEMO_JNIUTIL_H
