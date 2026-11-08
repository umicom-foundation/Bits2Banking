/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: ForecastDemo.kt
 *
 * PURPOSE:
 *   Reuse the Java native boundary from Kotlin without duplicating treasury logic.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
import java.nio.file.Paths
fun main(args: Array<String>) {
    require(args.size == 1) { "Supply the absolute treasury-forecast path" }
    val net = NativeForecast.net(Paths.get(args[0]), 125000L, 140000L)
    check(net == -15000L) { "Unexpected funding gap" }
    println(net)
}
