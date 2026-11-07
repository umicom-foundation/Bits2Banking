/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/message-retry/test_retry.c
 *
 * PURPOSE:
 *   Check that rejected retry reads and lease renewals preserve caller state.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include "umicom/messaging/idempotency.h"
#include "umicom/messaging/delivery_lease.h"
#define CHECK(condition) do { if (!(condition)) { fprintf(stderr, "Check failed at line %d\n", __LINE__); goto finished; } } while (0)
int main(void)
{
    UmiIdempotencyStore *records = NULL;
    UmiDeliveryLeaseStore *leases = NULL;
    UmiStatus outcome = UMI_STATUS_BUSY;
    char result[2] = {'Q', 'Q'};
    int exit_code = 1;
    CHECK(umi_idempotency_store_create(1, &records) == UMI_STATUS_OK);
    CHECK(umi_delivery_lease_store_create(1, &leases) == UMI_STATUS_OK);
    CHECK(umi_idempotency_store_record(records, "one", UMI_STATUS_OK, "complete") == UMI_STATUS_OK);
    CHECK(umi_idempotency_store_lookup(records, "one", &outcome, result, sizeof result) == UMI_STATUS_CAPACITY_EXCEEDED);
    CHECK(result[0] == 'Q' && result[1] == 'Q' && outcome == UMI_STATUS_BUSY);
    CHECK(umi_idempotency_store_count(records) == 1);
    CHECK(umi_delivery_lease_acquire(leases, 9, "worker", 10, 20) == UMI_STATUS_OK);
    CHECK(umi_delivery_lease_renew(leases, 9, "worker", 15, UINT64_MAX) == UMI_STATUS_INVALID_ARGUMENT);
    CHECK(umi_delivery_lease_is_owned(leases, 9, "worker", 29));
    CHECK(!umi_delivery_lease_is_owned(leases, 9, "worker", 30));
    exit_code = 0;
finished:
    umi_delivery_lease_store_destroy(leases);
    umi_idempotency_store_destroy(records);
    return exit_code;
}
