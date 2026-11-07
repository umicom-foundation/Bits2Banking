/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/kotlin-first-program/Progress.kt
 *
 * PURPOSE:
 *   Teach immutable values, input validation and checks in a console program.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
fun remainingLessons(total: Int, completed: Int): Int {
    require(total >= 0) { "Total must not be negative" }
    require(completed in 0..total) { "Completed must be between zero and total" }
    return total - completed
}

fun main() {
    val total = 4
    val completed = 1
    println("Remaining lessons: ${remainingLessons(total, completed)}")
    check(remainingLessons(4, 1) == 3)
    check(remainingLessons(0, 0) == 0)
    check(remainingLessons(4, 4) == 0)
    check(runCatching { remainingLessons(4, 5) }.isFailure)
    check(runCatching { remainingLessons(-1, 0) }.isFailure)
    check(runCatching { remainingLessons(4, -1) }.isFailure)
    println("All progress checks passed.")
}
