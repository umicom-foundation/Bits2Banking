/* Bits2Banking — C23 Service-Recovery Demo | Umicom Foundation | MIT */
#include "recovery.h"
#include <stdio.h>
int main(void)
{
    BtbService service = {0};
    if (BtbServiceStart(&service, 7U) != BTB_IRQ_OK ||
        BtbServiceBegin(&service, 1U) != BTB_IRQ_OK ||
        BtbServiceCommit(&service) != BTB_IRQ_OK ||
        BtbServiceBegin(&service, 2U) != BTB_IRQ_OK ||
        BtbServiceFault(&service) != BTB_IRQ_OK ||
        BtbServiceRecover(&service) != BTB_IRQ_OK ||
        service.committed != 1U ||
        BtbServiceBegin(&service, 2U) != BTB_IRQ_OK ||
        BtbServiceCommit(&service) != BTB_IRQ_OK ||
        BtbServiceStop(&service) != BTB_IRQ_OK) return 1;
    printf("Fictional Notes service: last accepted revision %u\n", (unsigned)service.committed);
    puts("No real interrupt or durable storage was used.");
    return 0;
}
