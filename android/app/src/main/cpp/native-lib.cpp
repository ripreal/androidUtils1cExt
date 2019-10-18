#include <jni.h>
#include <string>
#include "../../../../../Inf18/MainApp.h"


extern "C"
JNIEXPORT jstring JNICALL
Java_org_ripreal_androidutils_MainActivity_hello(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from androidutils++";
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT void JNICALL
Java_org_ripreal_androidutils_MainApp_testScreenActions(JNIEnv *env, jobject objloc) {
    jclass ccLoc = env ->GetObjectClass(objloc);
    jclass cc = static_cast<jclass>(env->NewGlobalRef(ccLoc));
    jobject obj = static_cast<jobject>(env->NewGlobalRef(objloc));

    MainApp mainApp{};
    mainApp.setCC(cc);
    mainApp.setOBJ(obj);
    mainApp.startScreenWatch();
}


extern "C"
JNIEXPORT void JNICALL
Java_org_ripreal_androidutils_MainApp_testSleep(JNIEnv *env, jobject objloc) {
    jclass ccLoc = env ->GetObjectClass(objloc);
    jclass cc = static_cast<jclass>(env->NewGlobalRef(ccLoc));
    jobject obj = static_cast<jobject>(env->NewGlobalRef(objloc));

    MainApp mainApp{};
    mainApp.setCC(cc);
    mainApp.setOBJ(obj);
    mainApp.sleep(2000);
}