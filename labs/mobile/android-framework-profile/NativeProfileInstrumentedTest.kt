/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/android-framework-profile/NativeProfileInstrumentedTest.kt
 *
 * PURPOSE:
 *   Exercise the real Android library load and JNI boundary on an emulator or device.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package org.umicom.learning.profile

import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Assert.assertEquals
import org.junit.Assert.assertNull
import org.junit.Test
import org.junit.runner.RunWith

@RunWith(AndroidJUnit4::class)
class NativeProfileInstrumentedTest {
    @Test fun canonicalisesAscii() {
        assertEquals("sam_007", NativeProfile.canonical("Sam_007"))
    }
    @Test fun minimumLength() {
        assertEquals("abc", NativeProfile.canonical("ABC"))
    }
    @Test fun maximumLength() {
        assertEquals("a".repeat(48), NativeProfile.canonical("A".repeat(48)))
    }
    @Test fun refusesNullAndShortValues() {
        for (value in listOf(null, "", "a", "ab")) assertNull(NativeProfile.canonical(value))
    }
    @Test fun refusesLongValues() {
        assertNull(NativeProfile.canonical("a".repeat(49)))
        assertNull(NativeProfile.canonical("a".repeat(4096)))
    }
    @Test fun refusesInvalidAscii() {
        for (value in listOf("1abc", "_abc", "-abc", "ab c", "a.b", "<b>"))
            assertNull(NativeProfile.canonical(value))
    }
    @Test fun refusesUnicodeOutsidePolicy() {
        for (value in listOf("caf\u00e9", "ab\uD83D\uDE00", "ab\uD800"))
            assertNull(NativeProfile.canonical(value))
    }
    @Test fun refusesEmbeddedNul() {
        assertNull(NativeProfile.canonical("abc\u0000tail"))
    }
    @Test fun acceptsPermittedSeparatorsAndDigits() {
        assertEquals("a-1_b", NativeProfile.canonical("A-1_B"))
    }
    @Test fun refusalDoesNotPoisonNextCall() {
        assertNull(NativeProfile.canonical("not allowed"))
        assertEquals("second", NativeProfile.canonical("SECOND"))
    }
}
