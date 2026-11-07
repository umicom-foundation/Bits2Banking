<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/19-distinguish-a-deadline-from-a-delay.md

PURPOSE:
Explain the lesson: Distinguish a deadline from a delay.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish a deadline from a delay

A delay describes how long to wait. A deadline describes the timer value at which something should happen. Confusing them can schedule an event in the past.

## Setup recap

Read UmicomPlatformTimerRead, UmicomPlatformTimerSetCompare and MachineTimeCompareRegister in the QEMU timer adapter. Use paper values for this exercise; no guest execution is required.

A hart is a hardware execution context. This introductory Kernel configuration begins with hart zero. The adapter keeps an explicit address stride for its compare register.

## 1. Choose an absolute value

Suppose the timer reads 100 and the desired delay is 20 ticks. The corresponding deadline is 120. Writing 20 as the compare value would already be behind the observed time.

The adapter accepts the deadline as supplied. A caller adding a delay must also consider whether that addition can overflow the counter type.

## 2. Follow the register selection

The compare-register address adds hartId multiplied by an eight-byte stride to the timer base. Eight bytes hold a 64-bit compare value.

This arithmetic describes the adapter's layout. It does not discover which hart IDs actually exist. A valid caller must use a supported hart identity.

## 3. Separate pending from handling

When the timer reaches the compare threshold, the timer condition can become pending. Interrupt-enable state and execution privilege also affect when a handler runs.

A timer threshold is therefore not a promise that a C function will execute at an exact instant. Handler latency and the platform environment matter.

## Exercise and expected reasoning

For a current value of 250, classify deadlines 200, 250 and 275 as already reached, reached now or still ahead. Then explain why the far-future value used by UmicomPlatformTimerDisable is a practical convention, not a separate hardware off switch.

Read UmicomPlatformTimerCompareRead. It reuses the same register-location helper as SetCompare. This keeps save and restore operations aimed at the same register.

When investigating a timer problem, record the current counter, intended deadline, hart and enable state separately. A missing handler message does not by itself identify which one is wrong.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/platform/qemu-riscv64/timer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](18-read-a-memory-mapped-timer.md) · [Next lesson](20-bound-emergency-diagnostics.md)

