/*-----------------------------------------------------------------------------
 * Bits to Banking — Umicom Foundation
 * File: labs/native/round-robin-scheduler/round_robin.h
 * PURPOSE: Model an owned FIFO ready queue, task generations and waiting.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_ROUND_ROBIN_H
#define BTB_ROUND_ROBIN_H
#include <stddef.h>
#include <stdint.h>

#define BTB_RR_TASK_LIMIT 8U

typedef uint64_t BtbTaskHandle;
typedef enum BtbSchedResult {
    BTB_SCHED_OK = 0,
    BTB_SCHED_INVALID = 1,
    BTB_SCHED_CAPACITY = 2,
    BTB_SCHED_EMPTY = 3,
    BTB_SCHED_BUSY = 4,
    BTB_SCHED_BAD_STATE = 5,
    BTB_SCHED_STALE = 6,
    BTB_SCHED_RETIRED = 7
} BtbSchedResult;
typedef enum BtbTaskState {
    BTB_TASK_UNUSED = 0,
    BTB_TASK_READY = 1,
    BTB_TASK_RUNNING = 2,
    BTB_TASK_WAITING = 3,
    BTB_TASK_STOPPED = 4
} BtbTaskState;
typedef struct BtbSlot {
    uint32_t generation;
    uint32_t waitKey;
    BtbTaskState state;
} BtbSlot;
typedef struct BtbRoundRobin {
    BtbSlot tasks[BTB_RR_TASK_LIMIT];
    uint32_t ready[BTB_RR_TASK_LIMIT];
    size_t head;
    size_t readyCount;
    size_t waitingCount;
    uint32_t runningSlot; /* UINT32_MAX denotes an idle teaching processor. */
} BtbRoundRobin;
typedef struct BtbSchedSnapshot {
    size_t ready;
    size_t waiting;
    size_t running;
    size_t live;
    BtbTaskHandle runningTask;
} BtbSchedSnapshot;

/* Hosted, single-threaded teaching model. No real processes or task stacks.
 * These functions are not interrupt-safe and are not the Umicom Kernel ABI.
 * No pointer into a live scheduler may be retained by a client. */
void BtbRoundRobinInit(BtbRoundRobin *scheduler);
BtbSchedResult BtbRoundRobinAdmit(BtbRoundRobin *scheduler, BtbTaskHandle *outHandle);
BtbSchedResult BtbRoundRobinNext(BtbRoundRobin *scheduler, BtbTaskHandle *outHandle);
BtbSchedResult BtbRoundRobinYield(BtbRoundRobin *scheduler, BtbTaskHandle handle);
BtbSchedResult BtbRoundRobinWait(BtbRoundRobin *scheduler, BtbTaskHandle handle, uint32_t key);
BtbSchedResult BtbRoundRobinWake(BtbRoundRobin *scheduler, BtbTaskHandle handle, uint32_t key);
BtbSchedResult BtbRoundRobinExit(BtbRoundRobin *scheduler, BtbTaskHandle handle);
BtbSchedResult BtbRoundRobinCancelWait(BtbRoundRobin *scheduler, BtbTaskHandle handle, uint32_t key);
BtbSchedResult BtbRoundRobinSnapshotRead(const BtbRoundRobin *scheduler, BtbSchedSnapshot *out);
#endif
