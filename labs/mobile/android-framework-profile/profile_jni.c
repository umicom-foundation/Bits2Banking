/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/android-framework-profile/profile_jni.c
 *
 * PURPOSE:
 *   Bind the teaching Java method to the reusable Framework JNI adapter.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/ui/android/profile_name.h"

/* Java package, object and method identity belong to this application. Text
 * conversion and validation stay in Framework so other apps can reuse them. */
JNIEXPORT jstring JNICALL
Java_org_umicom_learning_profile_NativeProfile_canonical(JNIEnv *env, jobject object, jstring input)
{
    (void)object;
    return UmiAndroidProfileNameCanonical(env, input);
}
