/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/admission_queue.h
 * PURPOSE: Bounded, single-owner model of request admission and backpressure.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_ADMISSION_QUEUE_H
#define BTB_ADMISSION_QUEUE_H
#include <stddef.h>
#include <stdint.h>
#define BTB_ADMISSION_CAPACITY 4U

typedef enum BtbAdmissionStatus {
    BTB_ADMISSION_OK = 0,
    BTB_ADMISSION_INVALID,
    BTB_ADMISSION_FULL,
    BTB_ADMISSION_EMPTY,
    BTB_ADMISSION_BUSY,
    BTB_ADMISSION_STALE,
    BTB_ADMISSION_EXHAUSTED
} BtbAdmissionStatus;
typedef enum BtbAdmissionPhase {
    BTB_ADMISSION_QUEUED = 1,
    BTB_ADMISSION_ACTIVE = 2
} BtbAdmissionPhase;
typedef struct BtbAdmissionItem {
    uint64_t ticket;
    uint64_t requestId;
    BtbAdmissionPhase phase;
    unsigned cancellationRequested;
} BtbAdmissionItem;
typedef struct BtbAdmissionQueue {
    const struct BtbAdmissionQueue *self;
    BtbAdmissionItem items[BTB_ADMISSION_CAPACITY];
    size_t count;
    size_t active;
    size_t maxActive;
    uint64_t nextTicket;
    uint64_t admitted;
    uint64_t completed;
    uint64_t removed;
} BtbAdmissionQueue;

/* This is a deterministic model, NOT a threadsafe or kernel-backed executor.
 * Simulating two in-flight operations does not start two OS threads. */
BtbAdmissionStatus BtbAdmissionInit(BtbAdmissionQueue *queue, size_t maxActive);
BtbAdmissionStatus BtbAdmissionSubmit(BtbAdmissionQueue *queue,
                                      uint64_t requestId, uint64_t *outTicket);
BtbAdmissionStatus BtbAdmissionStart(BtbAdmissionQueue *queue,
                                     uint64_t *outTicket, uint64_t *outRequestId);
BtbAdmissionStatus BtbAdmissionCancel(BtbAdmissionQueue *queue, uint64_t ticket);
BtbAdmissionStatus BtbAdmissionComplete(BtbAdmissionQueue *queue, uint64_t ticket);
int BtbAdmissionValidate(const BtbAdmissionQueue *queue);
#endif
