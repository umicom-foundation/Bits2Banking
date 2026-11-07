/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/android-framework-activity/NativeActivity.kt
 *
 * PURPOSE:
 *   Load the C boundary without duplicating the activity rule.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package org.umicom.learning.activity

object NativeActivity {
    init { System.loadLibrary("btb_activity") }
    external fun next(current: Int): Int
}

