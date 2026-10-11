/*-----------------------------------------------------------------------------
 * Bits to Banking — Umicom Foundation
 * File: labs/native/round-robin-scheduler/round_robin.c
 * PURPOSE: Follow FIFO dispatch, wait registration, wake-up and handle lifetime.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "round_robin.h"

static BtbTaskHandle Token(uint32_t slot, uint32_t generation)
{
    return ((uint64_t)generation << 32U) | (uint64_t)(slot + 1U);
}
static BtbSchedResult Lookup(BtbRoundRobin *scheduler, BtbTaskHandle handle,
                             BtbSlot **outSlot, uint32_t *outIndex)
{
    if (scheduler == NULL || outSlot == NULL || outIndex == NULL || handle == 0U)
        return BTB_SCHED_INVALID;
    const uint32_t word = (uint32_t)handle;
    const uint32_t generation = (uint32_t)(handle >> 32U);
    if (word == 0U || word > BTB_RR_TASK_LIMIT || generation == 0U)
        return BTB_SCHED_STALE;
    const uint32_t index = word - 1U;
    BtbSlot *slot = &scheduler->tasks[index];
    if (slot->generation != generation || slot->state == BTB_TASK_UNUSED ||
        slot->state == BTB_TASK_STOPPED)
        return BTB_SCHED_STALE;
    *outSlot = slot;
    *outIndex = index;
    return BTB_SCHED_OK;
}
static BtbSchedResult Queue(BtbRoundRobin *scheduler, uint32_t slot)
{
    if (scheduler->readyCount >= BTB_RR_TASK_LIMIT) return BTB_SCHED_CAPACITY;
    const size_t end = (scheduler->head + scheduler->readyCount) % BTB_RR_TASK_LIMIT;
    scheduler->ready[end] = slot;
    ++scheduler->readyCount;
    return BTB_SCHED_OK;
}
void BtbRoundRobinInit(BtbRoundRobin *scheduler)
{
    if (scheduler != NULL) {
        *scheduler = (BtbRoundRobin){0};
        scheduler->runningSlot = UINT32_MAX;
    }
}
BtbSchedResult BtbRoundRobinAdmit(BtbRoundRobin *scheduler, BtbTaskHandle *outHandle)
{
    if (scheduler == NULL || outHandle == NULL) return BTB_SCHED_INVALID;
    for (uint32_t index = 0U; index < BTB_RR_TASK_LIMIT; ++index) {
        BtbSlot *slot = &scheduler->tasks[index];
        if (slot->state != BTB_TASK_UNUSED && slot->state != BTB_TASK_STOPPED)
            continue;
        if (slot->generation == UINT32_MAX) continue;
        if (Queue(scheduler, index) != BTB_SCHED_OK) return BTB_SCHED_CAPACITY;
        ++slot->generation; /* Reusing this slot must invalidate earlier tokens. */
        slot->state = BTB_TASK_READY;
        slot->waitKey = 0U;
        *outHandle = Token(index, slot->generation);
        return BTB_SCHED_OK;
    }
    return BTB_SCHED_CAPACITY;
}
BtbSchedResult BtbRoundRobinNext(BtbRoundRobin *scheduler, BtbTaskHandle *outHandle)
{
    if (scheduler == NULL || outHandle == NULL) return BTB_SCHED_INVALID;
    if (scheduler->runningSlot != UINT32_MAX) return BTB_SCHED_BUSY;
    if (scheduler->readyCount == 0U) return BTB_SCHED_EMPTY;
    const uint32_t index = scheduler->ready[scheduler->head];
    if (index >= BTB_RR_TASK_LIMIT || scheduler->tasks[index].state != BTB_TASK_READY)
        return BTB_SCHED_BAD_STATE;
    scheduler->head = (scheduler->head + 1U) % BTB_RR_TASK_LIMIT;
    --scheduler->readyCount;
    scheduler->runningSlot = index;
    scheduler->tasks[index].state = BTB_TASK_RUNNING;
    *outHandle = Token(index, scheduler->tasks[index].generation);
    return BTB_SCHED_OK;
}
BtbSchedResult BtbRoundRobinYield(BtbRoundRobin *scheduler, BtbTaskHandle handle)
{
    BtbSlot *slot = NULL; uint32_t index = 0U;
    BtbSchedResult status = Lookup(scheduler, handle, &slot, &index);
    if (status != BTB_SCHED_OK) return status;
    if (scheduler->runningSlot != index || slot->state != BTB_TASK_RUNNING)
        return BTB_SCHED_BAD_STATE;
    status = Queue(scheduler, index);
    if (status != BTB_SCHED_OK) return status;
    scheduler->runningSlot = UINT32_MAX;
    slot->state = BTB_TASK_READY;
    return BTB_SCHED_OK;
}
BtbSchedResult BtbRoundRobinWait(BtbRoundRobin *scheduler, BtbTaskHandle handle, uint32_t key)
{
    if (key == 0U) return BTB_SCHED_INVALID;
    BtbSlot *slot = NULL; uint32_t index = 0U;
    BtbSchedResult status = Lookup(scheduler, handle, &slot, &index);
    if (status != BTB_SCHED_OK) return status;
    if (scheduler->runningSlot != index || slot->state != BTB_TASK_RUNNING)
        return BTB_SCHED_BAD_STATE;
    slot->state = BTB_TASK_WAITING;
    slot->waitKey = key;
    scheduler->runningSlot = UINT32_MAX;
    ++scheduler->waitingCount;
    return BTB_SCHED_OK;
}
BtbSchedResult BtbRoundRobinWake(BtbRoundRobin *scheduler, BtbTaskHandle handle, uint32_t key)
{
    if (key == 0U) return BTB_SCHED_INVALID;
    BtbSlot *slot = NULL; uint32_t index = 0U;
    BtbSchedResult status = Lookup(scheduler, handle, &slot, &index);
    if (status != BTB_SCHED_OK) return status;
    if (slot->state != BTB_TASK_WAITING || slot->waitKey != key)
        return BTB_SCHED_BAD_STATE;
    status = Queue(scheduler, index);
    if (status != BTB_SCHED_OK) return status;
    slot->state = BTB_TASK_READY;
    slot->waitKey = 0U;
    --scheduler->waitingCount;
    return BTB_SCHED_OK;
}
BtbSchedResult BtbRoundRobinExit(BtbRoundRobin *scheduler, BtbTaskHandle handle)
{
    BtbSlot *slot = NULL; uint32_t index = 0U;
    BtbSchedResult status = Lookup(scheduler, handle, &slot, &index);
    if (status != BTB_SCHED_OK) return status;
    if (scheduler->runningSlot != index || slot->state != BTB_TASK_RUNNING)
        return BTB_SCHED_BAD_STATE;
    scheduler->runningSlot = UINT32_MAX;
    slot->state = BTB_TASK_STOPPED;
    slot->waitKey = 0U;
    return BTB_SCHED_OK;
}
BtbSchedResult BtbRoundRobinCancelWait(BtbRoundRobin *scheduler, BtbTaskHandle handle, uint32_t key)
{
    if (key == 0U) return BTB_SCHED_INVALID;
    BtbSlot *slot = NULL; uint32_t index = 0U;
    BtbSchedResult status = Lookup(scheduler, handle, &slot, &index);
    if (status != BTB_SCHED_OK) return status;
    if (slot->state != BTB_TASK_WAITING || slot->waitKey != key)
        return BTB_SCHED_BAD_STATE;
    slot->state = BTB_TASK_STOPPED;
    slot->waitKey = 0U;
    --scheduler->waitingCount;
    return BTB_SCHED_OK;
}
BtbSchedResult BtbRoundRobinSnapshotRead(const BtbRoundRobin *scheduler, BtbSchedSnapshot *out)
{
    if (scheduler == NULL || out == NULL) return BTB_SCHED_INVALID;
    BtbSchedSnapshot next = {0};
    next.ready = scheduler->readyCount;
    next.waiting = scheduler->waitingCount;
    next.running = scheduler->runningSlot == UINT32_MAX ? 0U : 1U;
    if (next.running != 0U) {
        const uint32_t index = scheduler->runningSlot;
        if (index >= BTB_RR_TASK_LIMIT || scheduler->tasks[index].state != BTB_TASK_RUNNING)
            return BTB_SCHED_BAD_STATE;
        next.runningTask = Token(index, scheduler->tasks[index].generation);
    }
    for (size_t index = 0U; index < BTB_RR_TASK_LIMIT; ++index)
        if (scheduler->tasks[index].state == BTB_TASK_READY ||
            scheduler->tasks[index].state == BTB_TASK_RUNNING ||
            scheduler->tasks[index].state == BTB_TASK_WAITING)
            ++next.live;
    if (next.live != next.ready + next.waiting + next.running)
        return BTB_SCHED_BAD_STATE;
    *out = next;
    return BTB_SCHED_OK;
}
