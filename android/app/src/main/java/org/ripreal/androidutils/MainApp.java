
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

package org.ripreal.androidutils;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

// SAMPLE 3

public class MainApp implements Runnable {

  // in C/C++ code the function will have name Java__org_ripreal_androidutils_LockState_OnLockChanged
  static native void OnLockChanged(long pObject);

  private long m_V8Object; // 1C application context
  private Activity m_Activity; // custom activity of 1C:Enterprise
  private BroadcastReceiver m_Receiver;

  public MainApp(Activity activity, long v8Object)
  {
    m_Activity = activity;
    m_V8Object = v8Object;
  }

  public void run()
  {
    System.loadLibrary("org_ripreal_androidutils");
  }

  public void show()
  {
    m_Activity.runOnUiThread(this);
  }

  public void startScreenWatch()
  {
    if (m_Receiver==null)
    {
      m_Receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
          switch (intent.getAction())
          {
            case Intent.ACTION_SCREEN_ON:
              OnLockChanged(m_V8Object);
              break;
          }
        }
      };

      IntentFilter filter = new IntentFilter(Intent.ACTION_SCREEN_ON);
      m_Activity.registerReceiver(m_Receiver, filter);
    }
  }

  public void stopScreenWatch()
  {
    if (m_Receiver != null)
    {
      m_Activity.unregisterReceiver(m_Receiver);
      m_Receiver = null;
    }
  }

  public native void testScreenActions();

  public native void testSleep();
}
