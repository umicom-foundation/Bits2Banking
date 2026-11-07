# Understand entry, return and program exit

A function return and a program exit solve different problems. Umicom's entry routine shows the distinction clearly.

## 1. How execution begins

An executable file contains instructions, data and information describing where those pieces belong in memory. Umicom currently uses ELF files for native programs. Its loader checks the file, maps its segments, provides a stack and places one integer argument in a0. A **segment** is a region described by the executable, with properties such as read or write permission.

The loader begins at the executable's entry address. In the diagnostic program, that address names `UmicomProgramEntry`. There is no automatic command-line argument array or standard C library startup in this profile.

```text
UmicomProgramEntry:
    call UmicomProgramMain
    li a7, UMICOM_USER_CALL_EXIT
    ecall
.Lumicom_program_no_return:
    j .Lumicom_program_no_return
```

## 2. Explain each step

`call` transfers execution to the C function and records a return address. The compiler builds that function's instructions. When C returns its result, the result is in a0. `li` means load an immediate value: put the EXIT operation number into a7. The assembler may translate a convenient instruction spelling into one or more machine instructions.

The next ECALL asks the monitor to finish this invocation using the result in a0. There is no older user function to return to. The final `j` jumps back to its own label if EXIT unexpectedly returns. It is a defensive fallback, not the intended successful path. The Kernel's deadline still bounds such a broken invocation.

 <svg viewbox="0 0 700 110" role="img" aria-label="C returns to the entry routine; the entry routine asks the Kernel to end the program." style="width:100%;max-width:700px"><title>C returns to the entry routine; the entry routine asks the Kernel to end the program.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">ELF entry</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">C function result in a0</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">EXIT request</text></svg>

C returns to the entry routine; the entry routine asks the Kernel to end the program.

## 3. Data must be prepared before C runs

Open `programs/diagnostic/main.c`. `umicomProgramCounter` starts at 32, so its initial value must be loaded. `umicomProgramZero` has no explicit nonzero initializer and must start with zero bytes. It contains 4097 bytes, deliberately crossing a page boundary. The loader must initialize the entire region, not only its first page.

The program checks these values rather than fixing them itself. Otherwise a broken loader could be hidden by the test. `volatile` on these test objects requires observable accesses; it is not a general promise of thread safety or memory ownership.

## 4. Distinguish a result from evidence

A program returning zero cannot by itself prove the Kernel restored memory accounting or enforced permissions. `kernel/executable_validation.c` checks process state, trap cause, copied bytes, call count and final frame counts independently. The read-only-write case deliberately faults; the busy-loop case deliberately times out. Their expected outcomes differ from a normal exit.

## Exercise with an explained answer

If UmicomProgramMain returns 12, which register carries 12 into EXIT? What would happen if the entry routine used a normal return instead?

<details>

<summary>Answer</summary>

a0 carries 12. A normal return would require a valid caller in this user address space. The entry routine has no such caller, so EXIT is the defined boundary. Guessing a return address is not a safe alternative.

</details>

## Optional practical step

After preparing the Kernel tools, run its `kernel.riscv64.executable_loading` test as described in `docs/NATIVE_ABI_DISCOVERY.md`. Keep the log. A passing host test of the reply reader is useful, but it does not execute these Assembly instructions.

---

[Read this lesson in HTML](../../../courses/learning-riscv-assembly/lessons/02-entry-return-and-exit.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Follow a system call from C into Assembly](01-follow-a-system-call.md)

[Next: Preserve register values when execution is interrupted](03-preserving-interrupted-registers.md)
