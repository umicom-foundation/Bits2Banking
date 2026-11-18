/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/module_client.d
 *
 * PURPOSE:
 *   Demonstrate qualified, aliased and selective imports with a bounded D pixel budget.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module module_client;
import sizes = umicom_lessons.pixel_budget;
import umicom_lessons.checked_product : tryMultiply;
static import std.stdio;

int main()
{
    uint bytes = 71;
    if (!sizes.tryRgbaBytes(640, 360, bytes) || bytes != 921600) return 1;
    std.stdio.writeln("640 x 360 RGBA bytes: ", bytes);
    bytes = 71;
    if (sizes.tryRgbaBytes(0, 360, bytes) || bytes != 71) return 2;
    if (sizes.tryRgbaBytes(1073741824, 1, bytes) || bytes != 71) return 3;
    std.stdio.writeln("Refused requests preserve: ", bytes);
    uint product = 99;
    if (!tryMultiply(0, uint.max, product) || product != 0) return 4;
    std.stdio.writeln("Generic zero product: ", product);
    return 0;
}
