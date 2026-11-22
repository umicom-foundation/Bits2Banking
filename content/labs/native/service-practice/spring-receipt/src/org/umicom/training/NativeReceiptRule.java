/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/service-practice/spring-receipt/src/org/umicom/training/NativeReceiptRule.java
 *
 * PURPOSE:
 *   Name the native receipt boundary that both Spring courses call.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
package org.umicom.training;

import java.nio.file.Path;

public final class NativeReceiptRule {
    public NativeReceiptRule(Path library) {
        // Resolve only an absolute path chosen by the local lab operator.
        if (!library.isAbsolute()) {
            throw new IllegalArgumentException("Use an absolute native library path");
        }
        System.load(library.toString());
    }

    // Java and JNI preserve signed 32-bit units at this boundary.
    private static native int decide(int cents, int ceiling);

    public int check(int cents, int ceiling) {
        return decide(cents, ceiling);
    }
}
