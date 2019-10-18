
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Examples for the report "Making external components for 1C mobile platform for Android""
// at the conference INFOSTART 2018 EVENT EDUCATION https://event.infostart.ru/2018/
//
// Sample 1: Delay in code
// Sample 2: Getting device information
// Sample 3: Device blocking: receiving external event about changing of sceen
//
// Copyright: Igor Kisil 2018
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../include/AddInDefBase.h"
#include "../include/IAndroidComponentHelper.h"
#include "../jni/jnienv.h"
#include "../include/IMemoryManager.h"
#include <string>

/* Wrapper calling class LockState from java build org.ripreal.androidutils */

class MainApp
{
private:

	jclass cc;
	jobject obj;
	std::wstring jstring2wstring(JNIEnv* jenv, jstring aStr);

public:

	MainApp();
	~MainApp();

	void setCC(jclass _cc);
	void setOBJ(jobject _obj);

	void Initialize(IAddInDefBaseEx*);

	void startScreenWatch() const; // Start monitoring lock state
	void stopScreenWatch() const; // End of monitoring
};