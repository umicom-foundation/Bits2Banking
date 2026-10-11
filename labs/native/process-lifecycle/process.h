/*-----------------------------------------------------------------------------
 * Bits2Banking · Umicom Foundation
 * File: labs/native/process-lifecycle/process.h
 * PURPOSE: Teach process states and validated transitions in hosted C23.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_PROCESS_H
#define BTB_PROCESS_H
#include <stdint.h>

typedef enum BtbProcessState {
    BTB_PROCESS_NEW = 0,
    BTB_PROCESS_READY,
    BTB_PROCESS_RUNNING,
    BTB_PROCESS_WAITING,
    BTB_PROCESS_TERMINATED
} BtbProcessState;

typedef enum BtbProcessEvent {
    BTB_EVENT_ADMIT = 0,
    BTB_EVENT_DISPATCH,
    BTB_EVENT_YIELD,
    BTB_EVENT_WAIT,
    BTB_EVENT_WAKE,
    BTB_EVENT_EXIT
} BtbProcessEvent;

typedef enum BtbProcessResult {
    BTB_PROCESS_OK = 0,
    BTB_PROCESS_INVALID_ARGUMENT,
    BTB_PROCESS_ILLEGAL_TRANSITION,
    BTB_PROCESS_REVISION_EXHAUSTED
} BtbProcessResult;

typedef struct BtbProcess {
    uint32_t identifier;
    uint32_t revision;
    BtbProcessState state;
    int exitCode;
} BtbProcess;

/* A process *model*, not a launcher, scheduler, operating-system process or
 * kernel syscall implementation. ExitCode is accepted only for EXIT events. */
BtbProcessResult BtbProcessInit(BtbProcess *process, uint32_t identifier);
BtbProcessResult BtbProcessApply(BtbProcess *process,
                                 BtbProcessEvent event, int exitCode);
const char *BtbProcessStateName(BtbProcessState state);
#endif
