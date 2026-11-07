/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/riscv-sequences/sequences.h
 *
 * PURPOSE:
 *   Define borrowed-array and fixed-width contracts for RV64 learning functions.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_RISCV_SEQUENCES_H
#define BTB_RISCV_SEQUENCES_H
#include <stddef.h>
#include <stdint.h>
/* RV64 interfaces use the standard integer calling convention.
   Sum permits NULL only when count is zero. Otherwise data addresses count
   readable, naturally aligned uint64_t elements for the duration of the call.
   Arithmetic is modulo 2^64; no allocation or input mutation occurs. */
uint64_t BtbSum64(const uint64_t *data, size_t count);
uint64_t BtbSumAndBias64(const uint64_t *data, size_t count, uint64_t bias);
int64_t BtbMinSigned64(int64_t left, int64_t right);
uint64_t BtbMinUnsigned64(uint64_t left, uint64_t right);
uint64_t BtbRotateLeft64(uint64_t value, uint64_t distance);
uint64_t BtbParity64(uint64_t value);
#endif
