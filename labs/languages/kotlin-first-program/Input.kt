/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/kotlin-first-program/Input.kt
 *
 * PURPOSE:
 *   Convert command-line text into checked lesson-progress inputs.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


import kotlin.system.exitProcess

/* Text conversion belongs to the caller. The existing remainingLessons
 * function remains the one place that defines the allowed progress range. */
fun remainingFromArguments(arguments: Array<String>): Int? {
    if (arguments.size != 2) return null
    val total = arguments[0].toIntOrNull() ?: return null
    val completed = arguments[1].toIntOrNull() ?: return null
    return try {
        remainingLessons(total, completed)
    } catch (_: IllegalArgumentException) {
        null
    }
}

fun main(arguments: Array<String>) {
    val remaining = remainingFromArguments(arguments)
    if (remaining == null) {
        System.err.println("Usage: InputKt TOTAL COMPLETED; require 0 <= COMPLETED <= TOTAL")
        exitProcess(2)
    }
    println("Remaining lessons: $remaining")
}
