#include <jni.h>
#include <string>
#include "src/agorammap.h"
#include "src/LogUtils.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_agora_loging_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    test_mmap();
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_agora_loging_MainActivity_setSdcardPath(JNIEnv *env, jobject thiz, jstring path) {
    std::string sdcard_path = env->GetStringUTFChars(path, nullptr);
    setSdcardPath(sdcard_path);
    LOGD("path = %s", sdcard_path.c_str())
}