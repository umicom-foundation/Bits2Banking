/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * A deterministic mock of a bank-report request pipeline; no bank connected. */
#include "dispatch.h"
#include <inttypes.h>
#include <stdio.h>

int main(void)
{
    BtbDispatch dispatcher;
    if (BtbDispatchInit(&dispatcher) != BTB_DISPATCH_OK) return 1;
    const char *requests[] = {
        "CASH|GBP|ACCOUNT-A", "CASH|USD|ACCOUNT-B", "AUDIT|TMS|BOOK-C"
    };
    for (size_t i = 0U; i < sizeof(requests) / sizeof(requests[0]); ++i) {
        BtbDispatchIdentity identity;
        size_t length = 0U;
        while (requests[i][length] != '\0') ++length;
        if (BtbDispatchSubmit(&dispatcher, (uint64_t)i + 1001U,
                              requests[i], length, &identity) != BTB_DISPATCH_OK)
            return 2;
        printf("accepted request=%" PRIu32 " slot=%" PRIu32 "\n",
               identity.requestId, identity.token.slot);
    }
    if (BtbDispatchStep(&dispatcher) != BTB_DISPATCH_OK) return 3;
    if (BtbDispatchQuiesce(&dispatcher) != BTB_DISPATCH_OK) return 4;
    BtbDispatchIdentity forbidden;
    if (BtbDispatchSubmit(&dispatcher, 123U, "X", 1U, &forbidden) !=
        BTB_DISPATCH_QUIESCING) return 5;
    size_t executed = 0U;
    if (BtbDispatchRun(&dispatcher, 3U, &executed) != BTB_DISPATCH_OK ||
        executed != 2U) return 6;
    BtbDispatchReceipt receipt;
    while (BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_OK) {
        printf("delivered request=%" PRIu32 " connection=%" PRIu64
               " bytes=%zu digest=%016" PRIx64 "\n",
               receipt.identity.requestId, receipt.connectionId,
               receipt.requestLength, receipt.diagnosticDigest);
    }
    if (!BtbDispatchDrained(&dispatcher)) return 7;
    puts("Bits2Banking C23 composed dispatcher: PASS (3/3 delivered)");
    return 0;
}
