/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/android-framework-profile/NativeProfile.kt
 *
 * PURPOSE:
 *   Expose the shared C name policy as a nullable Android native method.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package org.umicom.learning.profile

object NativeProfile {
    init { System.loadLibrary("btb_profile") }
    // Null is a refused name. VM/link/allocation exceptions are not converted
    // into successful validation or caught as ordinary form feedback.
    external fun canonical(input: String?): String?
}
