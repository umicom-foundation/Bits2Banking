/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/umicom_lessons/checked_product.d
 *
 * PURPOSE:
 *   Own a checked uint product for a multi-module D learning example.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module umicom_lessons.checked_product;

@safe pure nothrow @nogc
bool tryMultiply(uint left, uint right, ref uint result)
{
    if (right != 0 && left > uint.max / right) return false;
    result = left * right;
    return true;
}

unittest
{
    uint result = 71;
    assert(tryMultiply(0, uint.max, result) && result == 0);
    assert(tryMultiply(uint.max, 1, result) && result == uint.max);
    result = 71;
    assert(!tryMultiply(uint.max, 2, result) && result == 71);
}
