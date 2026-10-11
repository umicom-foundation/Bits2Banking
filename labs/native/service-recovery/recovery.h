/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Service-Recovery Laboratory
 * File: labs/native/service-recovery/recovery.h
 * PURPOSE: Compose the existing interrupt ownership model with a volatile
 *          service checkpoint. This is not persistent storage or kernel code.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_LAB_SERVICE_RECOVERY_H
#define BTB_LAB_SERVICE_RECOVERY_H
#include "owner.h"
#include <stdint.h>
typedef struct BtbService {
    BtbIrqDomain sourceDomain;
    BtbIrqLease lease;
    uint32_t committed;
    uint32_t inFlight;
    uint32_t started;
    uint32_t stopped;
} BtbService;
BtbIrqStatus BtbServiceStart(BtbService *service, uint32_t owner);
BtbIrqStatus BtbServiceBegin(BtbService *service, uint32_t revision);
BtbIrqStatus BtbServiceCommit(BtbService *service);
BtbIrqStatus BtbServiceFault(BtbService *service);
BtbIrqStatus BtbServiceRecover(BtbService *service);
BtbIrqStatus BtbServiceStop(BtbService *service);
#endif
