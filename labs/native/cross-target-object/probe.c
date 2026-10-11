/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/cross-target-object/probe.c
 * PURPOSE: Compile freestanding native object code without a host OS runtime.
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include <stdint.h>

/* This is a calculation over fictional boot values, not a complete kernel.
 * It can be compiled for the host or RISC-V64 without linking a process. */
uint64_t BtbBootFingerprint(uint64_t hartId, uint64_t deviceTreeAddress)
{
    uint64_t mixed = deviceTreeAddress ^ (hartId << 16U);
    return (mixed ^ UINT64_C(0x554D49434F4D0000)) + UINT64_C(0x10000);
}
