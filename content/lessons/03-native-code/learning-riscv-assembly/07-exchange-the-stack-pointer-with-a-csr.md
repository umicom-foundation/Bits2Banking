<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/07-exchange-the-stack-pointer-with-a-csr.md

PURPOSE:
Explain the lesson: Exchange the stack pointer with a control register.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Exchange the stack pointer with a control register

A trap interrupts ordinary execution to handle an event or fault. Its entry code must begin working before it can assume the interrupted program's stack is usable.

## Setup recap

Open arch/riscv64/trap_entry.S in Umicom Kernel. This is a source-reading exercise; do not paste machine-mode instructions into an ordinary desktop application.

A register is a small named storage location in the processor. sp is the stack pointer. A control and status register, or CSR, holds processor-control information.

## 1. Find the prepared landing pointer

UmicomRiscvMachineTrapPrepare initialises the reserved stack margins, then writes the stack-top address into mscratch.

The ordering matters: it publishes the address after the reserved storage is prepared.

## 2. Trace the exchange

The trap entry begins with:

```asm
csrrw sp, mscratch, sp
```

For this instruction, the old mscratch value becomes the new sp, while the old sp value is written to mscratch.

Draw two boxes before and after the instruction. The kernel now has its own landing stack, and the interrupted stack pointer remains available as a value.

## 3. Delay memory access

Only after the exchange does the entry reserve its frame and store a register. It does not dereference the interrupted sp merely to save the first register.

Later code reads mscratch and records the old sp in the frame. Recording a possibly invalid address as data is different from using it to access memory.

## Exercise

Use symbolic values OWNED_TOP and INTERRUPTED_SP. Trace the exchange, subtraction of the frame size and first store. Name which address is used for the store.

Then explain what could fail if mscratch itself were corrupted. This protocol still assumes a valid landing pointer and accessible kernel RAM.

## Scope

This is the current machine-mode trap path, not a universal entry sequence for every privilege mode or operating system. The source comments explain its non-nesting policy. Read the matching restoration path before changing any register ownership.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap_entry.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](08-map-a-trap-frame-by-byte-offset.md)


[Previous: Explain a word-sized result on RV64](06-explain-a-word-sized-result.md)
