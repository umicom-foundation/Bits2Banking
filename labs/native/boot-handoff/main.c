/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/boot-handoff/main.c
 *
 * PURPOSE:
 *   Construct a small boot record and call the actual Umicom Kernel reader without accessing physical memory.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/kernel/boot_handoff.h"
#include <stdio.h>
#include <string.h>

static void Put(unsigned char *where, UmicomU64 value, size_t bytes)
{
    for (size_t i = 0U; i < bytes; ++i)
        where[i] = (unsigned char)(value >> (8U * i));
}
int main(void)
{
    /* These numbers describe a synthetic machine. They are never pointers. */
    unsigned char record[144] = {0};
    memcpy(record, "UMIBOOT", 7U);
    Put(record + 8U, 1U, 2U);       /* Version. */
    Put(record + 10U, 64U, 2U);     /* Header bytes. */
    Put(record + 12U, sizeof record, 4U);
    Put(record + 16U, UMICOM_BOOT_RISCV64, 4U);
    Put(record + 32U, 0x80001000ULL, 8U);
    Put(record + 40U, 4096U, 8U);
    Put(record + 48U, 1U, 2U);      /* One RAM span. */
    Put(record + 50U, 1U, 2U);      /* One reservation. */
    Put(record + 64U, 0x80000000ULL, 8U);
    Put(record + 72U, 0x100000U, 8U);
    Put(record + 80U, 0x80000000ULL, 8U);
    Put(record + 88U, 8192U, 8U);
    /* Bytes 96..143 describe absent firmware and framebuffer information. */
    UmicomKernelBootHandoff result;
    if (UmicomKernelBootHandoffRead(record, sizeof record, &result) != UMICOM_BOOT_HANDOFF_OK)
        return 1;
    /* UmicomSize is an unsigned long long, independently of the host size_t.
     * Keep the former diagnostic for review; explicit casts match its replacement. */
#if 0
    printf("Accepted: %zu RAM range, %zu reservation\n", result.ramCount, result.reservedCount);
#endif
    printf("Accepted: %llu RAM range, %llu reservation\n",
        (unsigned long long)result.ramCount, (unsigned long long)result.reservedCount);
    unsigned char snapshot[sizeof result];
    memcpy(snapshot, &result, sizeof result);
    Put(record + 88U, 4096U, 8U); /* Now the reservation ends before the kernel. */
    if (UmicomKernelBootHandoffRead(record, sizeof record, &result) != UMICOM_BOOT_HANDOFF_MEMORY ||
        memcmp(snapshot, &result, sizeof result)) return 2;
    puts("Refused: kernel not reserved; previous observation preserved");
    return 0;
}
