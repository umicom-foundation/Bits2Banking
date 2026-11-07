/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/delivery-tickets/main.c
 *
 * PURPOSE:
 *   Demonstrate generation-bound local delivery ownership using the Framework messaging SDK.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include "umicom/messaging/delivery_lease.h"

static int report(const char *step, UmiStatus actual, UmiStatus expected)
{
    if (actual == expected) return 1;
    fprintf(stderr, "%s returned status %d; expected %d.\n",
            step, (int)actual, (int)expected);
    return 0;
}

int main(void)
{
    UmiDeliveryLeaseStore *store = NULL;
    UmiDeliveryLeaseTicket first = {0U, 0U}, replacement = {0U, 0U};
    int result = 1;

    if (!report("create", umi_delivery_lease_store_create(1U, &store), UMI_STATUS_OK))
        return result;

    /* Each asynchronous work item would retain its own ticket value.
     * Fixed times make this example deterministic without waiting or threads. */
    if (!report("first acquisition",
                umi_delivery_lease_acquire_ticket(store, 42U, "preview-worker",
                                                  100U, 20U, &first), UMI_STATUS_OK))
        goto finished;
    if (!umi_delivery_lease_ticket_is_owned(store, first, "preview-worker", 119U) ||
        umi_delivery_lease_ticket_is_owned(store, first, "preview-worker", 120U)) {
        fputs("Unexpected exclusive deadline.\n", stderr);
        goto finished;
    }
    puts("First acquisition is owned at 119 and expired at 120.");
    if (!report("replacement acquisition",
                umi_delivery_lease_acquire_ticket(store, 42U, "preview-worker",
                                                  120U, 30U, &replacement), UMI_STATUS_OK))
        goto finished;
    if (!report("delayed release",
                umi_delivery_lease_release_ticket(store, first, "preview-worker"),
                UMI_STATUS_PERMISSION_DENIED))
        goto finished;
    if (!umi_delivery_lease_ticket_is_owned(store, replacement, "preview-worker", 121U)) {
        fputs("Replacement ownership was lost.\n", stderr);
        goto finished;
    }
    puts("Stale release rejected; replacement remains owned.");
    if (!report("replacement release",
                umi_delivery_lease_release_ticket(store, replacement, "preview-worker"),
                UMI_STATUS_OK))
        goto finished;
    puts("Replacement released.");
    result = 0;
finished:
    umi_delivery_lease_store_destroy(store);
    return result;
}
