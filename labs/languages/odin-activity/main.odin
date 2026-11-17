/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/odin-activity/main.odin
 *
 * PURPOSE:
 *   Call the shared C activity archive through an explicit library collection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package main
import "core:c"
import "core:fmt"
import "core:os"
// Supply -collection:activity=<archive directory>. This is an explicit build
// input, not a search of another application or the current working directory.
foreign import activity "activity:libbtb-activity-adapters.a"
foreign activity {
    BtbActivityNext :: proc "c" (current: c.int) -> c.int ---
}
main :: proc() {
    inputs := [5]c.int{-1, 0, 41, 999, 1000}
    expected := [5]c.int{-1, 1, 42, 1000, -1}
    for current, index in inputs {
        next := BtbActivityNext(current)
        if next != expected[index] { os.exit(1) }
        fmt.printf("%d -> %d\n", current, next)
    }
}
