/*-----------------------------------------------------------------------------
 * Bits2Banking · Umicom Foundation
 * File: labs/native/process-lifecycle/process.c
 * PURPOSE: Preserve prior state on unsupported lifecycle transitions.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "process.h"
#include <limits.h>
#include <stddef.h>

BtbProcessResult BtbProcessInit(BtbProcess *process, uint32_t identifier)
{
    if (process == NULL || identifier == 0U) return BTB_PROCESS_INVALID_ARGUMENT;
    *process = (BtbProcess){.identifier = identifier, .revision = 1U,
                            .state = BTB_PROCESS_NEW, .exitCode = 0};
    return BTB_PROCESS_OK;
}

BtbProcessResult BtbProcessApply(BtbProcess *process,
                                 BtbProcessEvent event, int exitCode)
{
    if (process == NULL || process->identifier == 0U ||
        process->state < BTB_PROCESS_NEW || process->state > BTB_PROCESS_TERMINATED ||
        event < BTB_EVENT_ADMIT || event > BTB_EVENT_EXIT ||
        (event != BTB_EVENT_EXIT && exitCode != 0))
        return BTB_PROCESS_INVALID_ARGUMENT;
    BtbProcessState next;
    switch (process->state) {
    case BTB_PROCESS_NEW:
        if (event != BTB_EVENT_ADMIT) return BTB_PROCESS_ILLEGAL_TRANSITION;
        next = BTB_PROCESS_READY;
        break;
    case BTB_PROCESS_READY:
        if (event != BTB_EVENT_DISPATCH) return BTB_PROCESS_ILLEGAL_TRANSITION;
        next = BTB_PROCESS_RUNNING;
        break;
    case BTB_PROCESS_RUNNING:
        if (event == BTB_EVENT_YIELD) next = BTB_PROCESS_READY;
        else if (event == BTB_EVENT_WAIT) next = BTB_PROCESS_WAITING;
        else if (event == BTB_EVENT_EXIT) next = BTB_PROCESS_TERMINATED;
        else return BTB_PROCESS_ILLEGAL_TRANSITION;
        break;
    case BTB_PROCESS_WAITING:
        if (event != BTB_EVENT_WAKE) return BTB_PROCESS_ILLEGAL_TRANSITION;
        next = BTB_PROCESS_READY;
        break;
    case BTB_PROCESS_TERMINATED:
    default:
        return BTB_PROCESS_ILLEGAL_TRANSITION;
    }
    /* A revision is an explicit monotonic generation. Refuse overflow before
     * replacing any user-visible state; never wrap an old generation to zero. */
    if (process->revision == UINT32_MAX) return BTB_PROCESS_REVISION_EXHAUSTED;
    BtbProcess changed = *process;
    changed.state = next;
    ++changed.revision;
    if (event == BTB_EVENT_EXIT) changed.exitCode = exitCode;
    *process = changed;
    return BTB_PROCESS_OK;
}

const char *BtbProcessStateName(BtbProcessState state)
{
    switch (state) {
    case BTB_PROCESS_NEW: return "new";
    case BTB_PROCESS_READY: return "ready";
    case BTB_PROCESS_RUNNING: return "running";
    case BTB_PROCESS_WAITING: return "waiting";
    case BTB_PROCESS_TERMINATED: return "terminated";
    }
    return "invalid state";
}
