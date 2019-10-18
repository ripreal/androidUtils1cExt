
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

#include <wchar.h>
#include <thread>
#include "MainApp.h"
#include "ConversionWchar.h"

MainApp::MainApp() : cc(nullptr), obj(nullptr)
{
}

MainApp::~MainApp()
{
	if (obj)
	{
		stopScreenWatch(); // call to unregister broadcast receiver
		JNIEnv *env = getJniEnv();
		env->DeleteGlobalRef(obj);
		env->DeleteGlobalRef(cc);
	}
}

void MainApp::Initialize(IAddInDefBaseEx* cnn)
{
	if (!obj)
	{
		IAndroidComponentHelper* helper = (IAndroidComponentHelper*)cnn->GetInterface(eIAndroidComponentHelper);
		if (helper)
		{
			WCHAR_T* className = nullptr;
			convToShortWchar(&className, L"org.ripreal.androidutils.MainApp");
			jclass ccloc = helper->FindClass(className);
			delete[] className;
			className = nullptr;
			if (ccloc)
			{
				JNIEnv* env = getJniEnv();
				cc = static_cast<jclass>(env->NewGlobalRef(ccloc));
				env->DeleteLocalRef(ccloc);
				jobject activity = helper->GetActivity();
				// call of constructor for java class
				jmethodID methID = env->GetMethodID(cc, "<init>", "(Landroid/app/Activity;J)V");
				jobject objloc = env->NewObject(cc, methID, activity, (jlong)cnn);
				obj = static_cast<jobject>(env->NewGlobalRef(objloc));
				env->DeleteLocalRef(objloc);
				methID = env->GetMethodID(cc, "show", "()V");
				env->CallVoidMethod(obj, methID);
				env->DeleteLocalRef(activity);
			}
		}
	}
}

void MainApp::sleep(long delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void MainApp::startScreenWatch() const
{
	if (obj)
	{
		JNIEnv* env = getJniEnv();
		jmethodID methID = env->GetMethodID(cc, "startScreenWatch", "()V");
		env->CallVoidMethod(obj, methID);
	}
}

void MainApp::stopScreenWatch() const
{
	if (obj)
	{
		JNIEnv* env = getJniEnv();
		jmethodID methID = env->GetMethodID(cc, "stopScreenWatch", "()V");
		env->CallVoidMethod(obj, methID);
	}
}

static const wchar_t g_EventSource[] = L"org.ripreal.androidutils";
static const wchar_t g_EventName[] = L"LockChanged";
static WcharWrapper s_EventSource(g_EventSource);
static WcharWrapper s_EventName(g_EventName);

// name of function built according to Java native call
//
extern "C" JNIEXPORT void JNICALL Java_org_ripreal_androidutils_MainApp_OnLockChanged(JNIEnv* env, jclass jClass, jlong pObject) {
	IAddInDefBaseEx *pAddIn = (IAddInDefBaseEx *) pObject;
	if (pAddIn != nullptr) {
		pAddIn->ExternalEvent(s_EventSource, s_EventName, nullptr);
	}
}

std::wstring MainApp::jstring2wstring(JNIEnv* jenv, jstring aStr)
{
	std::wstring result;

	if (aStr)
	{
		const jchar* pCh = jenv->GetStringChars(aStr, 0);
		jsize len = jenv->GetStringLength(aStr);
		const jchar* temp = pCh;
		while (len > 0)
		{
			result += *(temp++);
			--len;
		}
		jenv->ReleaseStringChars(aStr, pCh);
	}
	return result;
}

void MainApp::setCC(jclass _cc) {
    cc = _cc;
}

void MainApp::setOBJ(jobject _obj) {
    obj= _obj;
}
