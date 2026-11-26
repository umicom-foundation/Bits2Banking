/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/c23-type-and-value/bit_width.c
 *
 * PURPOSE:
 *   Check the value range of an unsigned nine-bit field without assuming its storage size.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <limits.h>

/* This describes numeric width. A compiler may allocate more storage bits. */
typedef unsigned _BitInt(9) ChannelBits;

int main(void)
{
    /* Convert deliberately at the field boundary. The 512th value wraps to
     * zero in this unsigned nine-bit type. Keep a wider next value for checks. */
    const ChannelBits lastChannel = 511;
    const unsigned int nextValue = (unsigned int)lastChannel + 1U;
    const ChannelBits wrapped = (ChannelBits)nextValue;

    /* Check the numeric contract independently of alignment and byte order. */
    static_assert(sizeof(ChannelBits) * CHAR_BIT >= 9U);
    return (unsigned int)lastChannel != 511U || nextValue != 512U || wrapped != 0U;
}
