# Why programs ask the Kernel for help

A program needs services, but it must not gain unrestricted access to every other program or device.

## 1. Understand the boundary

The **Kernel** is the privileged part of this experimental system. A **user program** runs with fewer permissions. Permission describes an allowed action, such as reading a mapped page. It is different from knowing an address: knowing a number does not grant access to the memory at that number.

Umicom's current teaching monitor handles U-mode requests in machine mode. U-mode is the processor's user privilege level. Machine mode is a more privileged execution level. This describes this implementation; other system designs use different arrangements.

 <svg viewbox="0 0 700 110" role="img" aria-label="Arguments cross a checked boundary; a user address does not become an unrestricted Kernel pointer." style="width:100%;max-width:700px"><title>Arguments cross a checked boundary; a user address does not become an unrestricted Kernel pointer.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Unprivileged program</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Checked ECALL boundary</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Kernel-owned service</text></svg>

Arguments cross a checked boundary; a user address does not become an unrestricted Kernel pointer.

## 2. Read the real service vocabulary

In `include/umicom/kernel/user_abi.h`, EXIT is operation 0, IDENTITY is 1, COPY is 2 and ABI_QUERY is 3. IDENTITY gives the identity assigned by the Kernel. COPY moves a bounded number of bytes through checked memory. ABI_QUERY describes available compiled routes; it does not grant access to an account, device or file.

## 3. A small request still needs checks

Imagine asking to copy 16 bytes. The Kernel must check the source can be read and the destination can be written. If the range crosses into another page, checking its first address is insufficient. The second page might be missing or read-only. The current COPY limit is 64 bytes, and the monitor uses its own scratch storage. A size limit controls work; memory ownership checks control access. Both matter.

Follow `kernel/user_memory.c` and `tests/user_memory/user_memory_tests.c`. The tests deliberately place ranges across page boundaries. A page is a fixed-size block used by the memory mapping system; this profile uses 4096-byte pages. You do not need to memorise this number to understand why both ends of a range matter.

## 4. A controlled fault is not automatically a broken test

A **fault** is a processor-reported condition such as a forbidden memory access. Some Kernel tests intentionally provoke one and then verify that only the offending program stops. A test passes only if the expected cause, process state and cleanup checks all agree. Merely printing a success word in a user program cannot establish isolation.

## Try it yourself

A source begins eight bytes before the end of one page and the request needs 16 bytes. How many bytes come from the next page? Would checking only the first page be enough?

<details>

<summary>Answer and explanation</summary>

Eight bytes come from each page. The first page's permission says nothing about the second. The whole range must be checked before the operation is accepted.

</details>

## Next step

Read [the Kernel system-call lesson](../../06-umicom/umicom-kernel-from-scratch/07-native-system-calls.md), then inspect the actual rejection tests. A host test checks C logic in a normal process; QEMU checks the compiled guest's processor transitions. Neither alone proves behavior on every physical device.

---

[Read this lesson in HTML](../../../courses/learning-riscv/lessons/02-programs-and-privileges.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next lesson: Trace a short sequence of register changes](03-binary-and-instruction-traces.md)

[Previous lesson: Registers, memory and instructions](01-registers-and-memory.md)


[Manuscript course contents](index.md)
