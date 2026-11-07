<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/18-read-a-memory-mapped-timer.md

PURPOSE:
Explain the lesson: Read a memory-mapped timer.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a memory-mapped timer

Some devices expose registers at particular memory addresses. A register is a location whose value is interpreted by hardware. Accessing it can observe or change a device rather than ordinary program data.

## Setup recap

Open platform/qemu-riscv64/timer.c in the Umicom Kernel repository. This is a source-reading lab; do not run its pointer accesses in a desktop C program. The addresses belong to the configured QEMU virt guest.

A hexadecimal number begins with 0x. Each hexadecimal digit represents four binary bits. An offset is a distance added to a starting address.

## 1. Work out the address

The adapter defines a CLINT base of 0x02000000 and adds 0x4000 to reach its timer block. It then adds 0x7ff8 for the time counter:

```text
0x02000000 + 0x00004000 = 0x02004000
0x02004000 + 0x00007ff8 = 0x0200bff8
```

Write these additions on paper. The result locates this platform's counter; it is not an address shared by every RISC-V computer.

## 2. Read the type

MachineTimeRegister returns a pointer to volatile UmicomU64. The width describes a 64-bit value. Volatile tells the compiler that accesses to this location must follow the implementation's volatile-access rules.

Volatile does not supply a lock, validate the address or make an arbitrary device access portable. The platform adapter and execution environment must agree on the register map and supported access width.

## 3. Follow the public function

UmicomPlatformTimerRead dereferences that pointer and returns the observed counter. Callers receive a value, not ownership of the register.

Ticks count progress of the platform timer. They are not a formatted calendar date. Converting ticks into seconds requires the timer frequency, which this small function does not determine.

## Exercise and explanation

Draw three boxes: generic Kernel logic, platform timer function and emulated device register. Put the fixed address only in the last two boxes.

Explain why a new hardware port should replace the platform adapter rather than scatter new addresses through generic scheduling code. If the guest machine configuration changes, recheck the map before interpreting timer observations.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/platform/qemu-riscv64/timer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](19-distinguish-a-deadline-from-a-delay.md)


[Previous: Publish a kernel contract only after validation](17-publish-a-contract-only-after-validation.md)
