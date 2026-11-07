/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/framework/order-lifecycle/main.c
 *
 * PURPOSE:
 *   Follow a local simulated order through validation, acceptance and cancellation.
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
#include "umicom/trading/trading.h"

#define REQUIRE(test) do { if (!(test)) { \
    fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #test); return 1; \
} } while (0)

int main(void)
{
    UmiSimulatedBrokerStorage storage = {0};
    UmiBroker broker = {0};
    UmiOrderRequest request = {0};
    UmiOrder *stored = NULL;
    /* Literal sizes are known and include the terminating byte. Applications
     * accepting input must validate its length before filling these fields. */
    memcpy(request.client_order_id.value, "LESSON-ORDER-1", sizeof "LESSON-ORDER-1");
    memcpy(request.account_id.value, "LESSON-ACCOUNT", sizeof "LESSON-ACCOUNT");
    memcpy(request.instrument.instrument_id.value, "LESSON.ASSET", sizeof "LESSON.ASSET");
    memcpy(request.instrument.symbol, "LESSON", sizeof "LESSON");
    memcpy(request.instrument.venue, "LOCAL", sizeof "LOCAL");
    memcpy(request.instrument.currency.code, "GBP", sizeof "GBP");
    request.instrument.multiplier = 1.0;
    request.side = UMI_SIDE_BUY;
    request.type = UMI_ORDER_LIMIT;
    request.tif = UMI_TIF_DAY;
    request.quantity = 2.0;
    request.limit_price = 10.0;
    request.environment = UMI_TRADING_SIMULATION;

    REQUIRE(umi_simulated_broker_create(&storage, &broker) == UMI_STATUS_OK);
    REQUIRE(broker.connect(broker.instance, UMI_TRADING_SIMULATION) == UMI_STATUS_OK);
    REQUIRE(broker.submit_order(broker.instance, &request) == UMI_STATUS_OK);
    REQUIRE(umi_order_store_find(&storage.orders, request.client_order_id.value, &stored) == UMI_STATUS_OK);
    REQUIRE(stored != NULL && stored->status == UMI_ORDER_ACCEPTED && stored->version == 1U);
    puts("Accepted local request; revision 1. No fill has occurred.");
    REQUIRE(broker.submit_order(broker.instance, &request) == UMI_STATUS_ALREADY_EXISTS);
    REQUIRE(storage.orders.count == 1U && stored->version == 1U);
    puts("Duplicate identifier refused; one order remains.");
    REQUIRE(broker.cancel_order(broker.instance, &request.client_order_id) == UMI_STATUS_OK);
    REQUIRE(stored->status == UMI_ORDER_CANCELLED && stored->version == 2U);
    REQUIRE(broker.cancel_order(broker.instance, &request.client_order_id) == UMI_STATUS_OK);
    REQUIRE(stored->version == 2U);
    puts("Cancelled local request; revision 2. Repeated cancellation changes nothing.");
    /* The pointer borrows storage owned by this function. Stop using it when
     * destruction resets the book; it must not outlive the storage itself. */
    stored = NULL;
    broker.destroy(broker.instance);
    REQUIRE(storage.orders.count == 0U && !storage.connected);
    puts("Local session reset. No broker account or network was used.");
    return 0;
}
