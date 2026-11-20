/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/boot-handoff/reservations.c
 *
 * PURPOSE:
 *   Teach how the RISC-V Kernel reports the page plan already owned by boot.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/kernel/riscv64/boot_handoff.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2 || (strcmp(argv[1], "review") != 0 && strcmp(argv[1], "unreserved") != 0)) {
        fputs("Usage: boot-handoff-reservations <review | unreserved>\n", stderr);
        return 2;
    }
    /* These are address observations in a hosted process. Kernel owns the
     * shared page calculation and the approved format. No address is followed. */
    const UmicomRiscvBootHandoffInput input = {0U, {0x80000000U, 0x1000000U},
        {0x80200000U, 0x9000U}, {0x80f0f000U, 0x80U}};
    const UmicomKernelDeviceTreeLayout tree = {.totalBytes = 0x80U, .reservationCount = 1U,
        .reservations = {{0x80300123U, 0x1000U}}};
    UmicomKernelBootReservationPlan plan;
    if (!UmicomKernelBootReservationsPlan((UmicomAddress)input.ram.address, input.ram.bytes,
        (UmicomAddress)(input.kernel.address + input.kernel.bytes), (UmicomAddress)input.deviceTree.address,
        &tree, &plan)) return 1;
    UmicomKernelBootHandoff observed;
    if (UmicomRiscvBootHandoffProject(&input, &plan, &observed) != UMICOM_BOOT_HANDOFF_OK ||
        observed.ramCount != 1U || observed.reservedCount != 3U ||
        observed.kernel.address != 0x80200000U || observed.kernel.bytes != 0x9000U ||
        observed.reserved[1].address != 0x80300000U || observed.reserved[1].bytes != 0x2000U) return 1;
    if (strcmp(argv[1], "review") == 0) {
        if (printf("RAM ranges %" PRIu64 ", reserved spans %" PRIu64 "\n", (uint64_t)observed.ramCount,
            (uint64_t)observed.reservedCount) < 0 ||
            printf("Kernel image 0x%" PRIx64 " for %" PRIu64 " bytes\n", (uint64_t)observed.kernel.address,
            (uint64_t)observed.kernel.bytes) < 0 ||
            printf("Rounded firmware reservation 0x%" PRIx64 " for %" PRIu64 " bytes\n",
            (uint64_t)observed.reserved[1].address, (uint64_t)observed.reserved[1].bytes) < 0) return 1;
        return 0;
    }

    /* Drop the last page range, which owns the FDT. The failed review must
     * leave an already accepted observation byte-for-byte intact. */
    unsigned char previous[sizeof observed];
    memcpy(previous, &observed, sizeof previous);
    --plan.count;
    if (UmicomRiscvBootHandoffProject(&input, &plan, &observed) != UMICOM_BOOT_HANDOFF_RANGE ||
        memcmp(previous, &observed, sizeof previous) != 0) return 1;
    return puts("Refused uncovered FDT, previous observation retained.") == EOF ? 1 : 0;
}
