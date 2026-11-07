/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/message-retry/main.c
 *
 * PURPOSE:
 *   Observe retry identity and exclusive lease expiry through Framework messaging contracts.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "umicom/messaging/idempotency.h"
#include "umicom/messaging/delivery_lease.h"

int main(void)
{
    UmiIdempotencyStore *records = NULL;
    UmiDeliveryLeaseStore *leases = NULL;
    UmiStatus outcome = UMI_STATUS_BUSY;
    char result[UMI_IDEMPOTENCY_RESULT_CAPACITY] = {0};
    int exit_code = 1;
    /* Framework owns the algorithms; this client owns both store lifetimes. */
    if (umi_idempotency_store_create(2, &records) != UMI_STATUS_OK ||
        umi_delivery_lease_store_create(2, &leases) != UMI_STATUS_OK) goto finished;
    if (umi_delivery_lease_acquire(leases, 7, "lesson-worker", 100, 20) != UMI_STATUS_OK ||
        !umi_delivery_lease_is_owned(leases, 7, "lesson-worker", 119) ||
        umi_delivery_lease_is_owned(leases, 7, "lesson-worker", 120)) goto finished;
    if (umi_idempotency_store_record(records, "export-7", UMI_STATUS_OK, "report prepared") != UMI_STATUS_OK ||
        umi_idempotency_store_record(records, "export-7", UMI_STATUS_OK, "changed") != UMI_STATUS_ALREADY_EXISTS ||
        umi_idempotency_store_lookup(records, "export-7", &outcome, result, sizeof result) != UMI_STATUS_OK ||
        outcome != UMI_STATUS_OK || strcmp(result, "report prepared") != 0) goto finished;
    printf("Retry result: %s\n", result);
    puts("Lease owned at 119; expired at 120.");
    exit_code = 0;
finished:
    if (exit_code) fputs("A messaging contract check failed.\n", stderr);
    umi_delivery_lease_store_destroy(leases);
    umi_idempotency_store_destroy(records);
    return exit_code;
}
