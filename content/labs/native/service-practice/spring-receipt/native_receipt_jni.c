/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/service-practice/spring-receipt/native_receipt_jni.c
 *
 * PURPOSE:
 *   Convert one JNI call to the existing C23 training rule.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "org_umicom_training_NativeReceiptRule.h"
#include "receipt_rule.h"

JNIEXPORT jint JNICALL Java_org_umicom_training_NativeReceiptRule_decide(
    JNIEnv *environment, jclass declaring_class, jint cents, jint ceiling)
{
    /* The signature carries two signed 32-bit values and owns no JNI objects. */
    (void)environment;
    (void)declaring_class;
    return (jint)receipt_decision((int32_t)cents, (int32_t)ceiling);
}
