/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Learning Laboratory
 * File: labs/native/interrupt-ownership/owner.h
 * PURPOSE: Explore explicit ownership of fictional interrupt sources.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_LAB_INTERRUPT_OWNER_H
#define BTB_LAB_INTERRUPT_OWNER_H
#include <stdint.h>

#define BTB_IRQ_SOURCE_COUNT 4U

typedef enum BtbIrqStatus {
    BTB_IRQ_OK = 0,
    BTB_IRQ_INVALID_ARGUMENT,
    BTB_IRQ_NOT_INITIALISED,
    BTB_IRQ_WRONG_OWNER,
    BTB_IRQ_STALE_LEASE,
    BTB_IRQ_WRONG_STAGE
} BtbIrqStatus;

typedef enum BtbIrqStage {
    BTB_IRQ_FREE = 0,
    BTB_IRQ_LEASED,
    BTB_IRQ_ARMED,
    BTB_IRQ_SERVICING,
    BTB_IRQ_ACKED,
    BTB_IRQ_FAULTED
} BtbIrqStage;

typedef struct BtbIrqLease {
    uint32_t source;
    uint32_t owner;
    uint32_t generation;
} BtbIrqLease;

typedef struct BtbIrqSource {
    uint32_t owner;
    uint32_t generation;
    uint32_t lastGeneration;
    BtbIrqStage stage;
} BtbIrqSource;

typedef struct BtbIrqDomain {
    const struct BtbIrqDomain *self; /* A live domain must not be copied. */
    uint32_t initialised;
    BtbIrqSource sources[BTB_IRQ_SOURCE_COUNT];
} BtbIrqDomain;

/* Provide a zero-initialised, address-stable domain. Do not copy or reset an
 * active domain; the last generation must survive source release. */
BtbIrqStatus BtbIrqInitialize(BtbIrqDomain *domain);
BtbIrqStatus BtbIrqClaim(BtbIrqDomain *domain, uint32_t source,
                          uint32_t owner, uint32_t generation,
                          BtbIrqLease *outLease);
BtbIrqStatus BtbIrqArm(BtbIrqDomain *domain, BtbIrqLease lease);
BtbIrqStatus BtbIrqEnter(BtbIrqDomain *domain, BtbIrqLease lease);
BtbIrqStatus BtbIrqAcknowledge(BtbIrqDomain *domain, BtbIrqLease lease);
BtbIrqStatus BtbIrqReturn(BtbIrqDomain *domain, BtbIrqLease lease);
BtbIrqStatus BtbIrqCancel(BtbIrqDomain *domain, BtbIrqLease lease);
BtbIrqStatus BtbIrqFault(BtbIrqDomain *domain, BtbIrqLease lease);
BtbIrqStatus BtbIrqRecover(BtbIrqDomain *domain, BtbIrqLease lease);
BtbIrqStatus BtbIrqRelease(BtbIrqDomain *domain, BtbIrqLease lease);
BtbIrqStatus BtbIrqReadStage(const BtbIrqDomain *domain,
                              BtbIrqLease lease, BtbIrqStage *outStage);
#endif
