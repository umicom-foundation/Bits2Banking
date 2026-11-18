/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/umicom_lessons/pixel_budget.d
 *
 * PURPOSE:
 *   Compose a nonempty four-byte pixel budget from a separately owned checked product.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module umicom_lessons.pixel_budget;
import umicom_lessons.checked_product : tryMultiply;

@safe pure nothrow @nogc
bool tryRgbaBytes(uint width, uint height, ref uint result)
{
    if (width == 0 || height == 0) return false;
    uint pixels, bytes;
    if (!tryMultiply(width, height, pixels) || !tryMultiply(pixels, 4, bytes))
        return false;
    result = bytes;
    return true;
}

unittest
{
    uint result = 71;
    assert(tryRgbaBytes(640, 360, result) && result == 921600);
    result = 71;
    assert(!tryRgbaBytes(0, 360, result) && result == 71);
    assert(!tryRgbaBytes(uint.max, 2, result) && result == 71);
    assert(!tryRgbaBytes(1073741824, 1, result) && result == 71);
}
