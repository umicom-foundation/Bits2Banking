/*-----------------------------------------------------------------------------
 * Bits to Banking — native systems programming
 * File: src/add_portable.c
 * PURPOSE: Fallback for architectures without a matching Assembly exercise.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include <stdint.h>
/* The checked C contract rejects overflow before this function is called. */
uint32_t BtbAssemblyAddU32(uint32_t left, uint32_t right)
{
    return left + right;
}
