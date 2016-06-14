//
//  NativeLauncher.cpp
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/06/14.
//
//

#include "NativeLauncher.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#define CLASS_NAME "org/cocos2dx/cpp/AppActivity"

extern "C" {

    void NativeLauncher::returnHome()
    {
        // JNIを使ってJAVAのメソッドを呼び出す
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "returnHome", "()V")) {
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
}
