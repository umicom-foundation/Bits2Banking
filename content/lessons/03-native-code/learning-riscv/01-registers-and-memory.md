# Registers, memory and instructions

A processor follows instructions. We will trace a real Umicom instruction sequence without assuming you have written a program.

## 1. Separate three things

An **instruction** tells a processor to do one operation. A **register** is a small named storage location inside the processor. **Memory** holds larger collections of bytes outside those working registers. A byte is a group of eight bits; each bit has two possible values, 0 and 1. A memory address is a number used to identify a location. An address is not the content stored there.

Umicom's current native Kernel target uses RV64: the ordinary integer registers are 64 bits wide. That does not mean every variable consumes 64 bits or that all possible 64-bit addresses are usable. The Kernel chooses which memory locations a program can access.

 <svg viewbox="0 0 700 110" role="img" aria-label="The program arranges values in registers before requesting a Kernel service." style="width:100%;max-width:700px"><title>The program arranges values in registers before requesting a Kernel service.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">C function arguments</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Named registers</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Kernel request</text></svg>

The program arranges values in registers before requesting a Kernel service.

## 2. Give each register a role

Open `umicom-kernel/programs/diagnostic/entry.S`. The final `.S` identifies Assembly source processed by the build tools. In this example, names `a0` to `a7` identify argument registers. `sp` identifies the stack pointer, used to find the current function's stack storage. `ra` holds a return address. These are conventions shared by the compiler and Assembly code.

## 3. Trace the actual moves

```text
mv a7, a0
mv a0, a1
mv a1, a2
mv a2, a3
ecall
ret
```

`mv destination, source` copies a value into the destination. It does not erase the source. `ecall` requests service through the processor's environment-call mechanism; it is not a normal C function call. `ret` returns to the calling program after the monitor returns control.

Suppose the C caller passes `number=3, first=2, second=0, third=0`. Initially a0=3, a1=2, a2=0, a3=0. After the moves, a7=3, a0=2, a1=0, a2=0. In this Kernel, service 3 queries the ABI and selector 2 asks for word width. The expected reply in a0 is 64. The meanings come from `include/umicom/kernel/user_abi.h`, not from the RISC-V processor itself.

## 4. Why order matters

If the first instruction instead replaced a0 with a1, the original operation number would be lost before it reached a7. A sequence can use individually valid instructions and still produce the wrong result. This is why we test complete requests as well as individual arithmetic operations.

## Try it yourself

Draw boxes labelled a0, a1, a2, a3 and a7. Put 3, 0, 0 and 0 in the first four boxes. Trace each move. Which selector reaches the monitor? Predict before opening the answer.

<details>

<summary>Answer and explanation</summary>

a7 becomes 3; a0, a1 and a2 become zero. Selector zero asks for VERSION. The current reply is hexadecimal `0x00010000`, representing major version 1 and minor version 0. It is a contract version, not a date or product release.

</details>

## Connect the learning

Continue with [program privileges](02-programs-and-privileges.md). For a line-by-line Assembly explanation, use [Learning RISC-V Assembly](../../../courses/learning-riscv-assembly/index.html). No instructions on this page have been executed by opening the lesson.

---

[Read this lesson in HTML](../../../courses/learning-riscv/lessons/01-registers-and-memory.html) · [Learning sequence](../../../start/learning-sequence.md)


[Manuscript course contents](index.md)
