/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/android-framework-activity/activity_jni.c
 *
 * PURPOSE:
 *   Connect a Kotlin method to the existing shared C activity adapter.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <jni.h>
#include "../../native/activity-adapters/bridge.h"
/* The Java package and class are part of this exported JNI symbol. Keep the
 * Kotlin declaration and this name together when moving the example. */
JNIEXPORT jint JNICALL
Java_org_umicom_learning_activity_NativeActivity_next(JNIEnv *env, jobject object, jint current)
{
    (void)env;
    (void)object;
    if (current < 0 || current > 1000) return (jint)-1;
    return (jint)BtbActivityNext((int)current);
}

