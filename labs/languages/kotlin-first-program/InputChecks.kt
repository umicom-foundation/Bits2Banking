/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/kotlin-first-program/InputChecks.kt
 *
 * PURPOSE:
 *   Check conversion boundaries and reuse of the existing progress rule.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


fun main() {
    check(remainingFromArguments(arrayOf("4", "1")) == 3)
    check(remainingFromArguments(arrayOf("0", "0")) == 0)
    check(remainingFromArguments(arrayOf("4", "4")) == 0)
    check(remainingFromArguments(arrayOf("2147483647", "0")) == Int.MAX_VALUE)
    val invalid = listOf(
        emptyArray<String>(), arrayOf("4"), arrayOf("4", "1", "extra"),
        arrayOf("", "1"), arrayOf("four", "1"), arrayOf("4", "1x"),
        arrayOf("4.0", "1"), arrayOf(" 4", "1"),
        arrayOf("2147483648", "0"), arrayOf("-1", "0"),
        arrayOf("4", "-1"), arrayOf("4", "5")
    )
    for (arguments in invalid) {
        check(remainingFromArguments(arguments) == null) {
            "Expected rejection for ${arguments.joinToString()}"
        }
    }
    println("All argument checks passed.")
}
