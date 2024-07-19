//
// jni调用java代码
//
#ifndef NDKDEMO_JCLAZZUTIL_H
#define NDKDEMO_JCLAZZUTIL_H
#include <jni.h>

jobject callMethod(JNIEnv* env, jobject jobj, const char* methodName, const char* sign){
    jclass obj_clazz = env->GetObjectClass(jobj);
    jmethodID  obj_method_id = env->GetMethodID(obj_clazz, methodName, sign);
    return env->CallObjectMethod(jobj, obj_method_id);
}
#endif

