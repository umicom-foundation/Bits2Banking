<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/30-model-ready-running-and-waiting.md

PURPOSE:
Explain the lesson: Model ready, running and waiting tasks.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Model ready, running and waiting tasks

## Prepare
Open labs/native/round-robin-scheduler/round_robin.h. The laboratory README includes PowerShell build commands for the hosted C model. Hosted means it runs as an ordinary program on an existing operating system.

A task is a unit of work. A scheduler chooses which ready task may run. A waiting task needs an event before it can continue.

## Draw the states
Draw READY, RUNNING, WAITING and STOPPED. Admission creates a ready task. Next selects it to run. Yield returns it to ready. Wait removes it from the processor until a matching wake event.

This model represents one teaching processor using runningSlot. UINT32_MAX means that processor is idle.

## Lab
Trace two tasks, Notes and Reports. Admit both, dispatch Notes and make Notes wait for key seventeen. Which task can be selected next?

Expected: Reports. Notes is waiting and is absent from the ready queue.

## Exercise and explanation
Does changing a state field actually switch CPU execution? No. This is a model for reasoning. Umicom Kernel's user_scheduler.c also has privileged execution, trap and context contracts that this lab does not implement.

## Troubleshoot
Keep the host model and native kernel separate in your notes. A passing model check does not demonstrate a boot, timer interrupt or hardware context switch. Use it to learn the state transitions before reading the corresponding Kernel implementation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/round-robin-scheduler/round_robin.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](29-address-overflow-and-pool-boundaries.md) · [Next lesson](31-dispatch-in-ready-queue-order.md)

