<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/20-bound-emergency-diagnostics.md

PURPOSE:
Explain the lesson: Bound emergency diagnostics.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Bound emergency diagnostics

Diagnostics are the messages used to explain a failure. A diagnostic path can fail too. An emergency handler must avoid waiting forever for a device that may no longer respond.

## Setup recap

Read platform/qemu-riscv64/trap_emergency.c. UART is a serial communication device. In this adapter, a status register indicates when the transmitter can accept a byte.

This is a source-reading exercise. The QEMU-specific memory addresses must not be dereferenced by a normal desktop application.

## 1. Find the loop limit

UmicomTrapEmergencyByte checks the transmitter at most 10,000 times. If it becomes ready, the function writes one byte and returns. Otherwise the function reaches the end without writing that byte.

The count bounds loop iterations. It does not specify 10,000 milliseconds or guarantee a wall-clock deadline. A hardware access itself still depends on the platform responding.

## 2. Bound the text too

UmicomTrapEmergencyText limits a message to 128 characters and stops at a terminating zero. Its inputs are local immutable literals, not pointers supplied by a failing user program.

The emergency path avoids an allocator and formatted-output library. That reduces dependencies when ordinary program state may already be damaged.

## 3. Explain the tradeoff

The report can be incomplete when the transmitter is unavailable. That is preferable to an unbounded loop that prevents the handler from attempting its final stop operation.

The source explicitly keeps a normal emergency as failure. A separate fault-test build may recognise a precise injected failure, but this does not make unexpected production faults successful.

## Exercise and explanation

Create a table for a transmitter ready immediately, ready on the final permitted poll and never ready. State whether a byte is written and whether the loop can continue indefinitely through its own logic.

Now estimate the maximum number of polls for a 20-character literal when every byte is refused. The bound is 20 multiplied by 10,000. Do not convert it to time without measurements.

A missing transcript is a limit of this diagnostic channel. It is not evidence that no fault occurred or that crash information was stored durably.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/platform/qemu-riscv64/trap_emergency.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](19-distinguish-a-deadline-from-a-delay.md) · [Next lesson](21-format-a-register-without-allocation.md)

