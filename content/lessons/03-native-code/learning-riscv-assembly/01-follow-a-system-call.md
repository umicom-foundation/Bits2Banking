# Follow a system call from C into Assembly

Assembly gives names to processor operations. Start with six lines from Umicom rather than a large program.

## 1. Read the C promise first

A function declaration describes the values a caller supplies and the value it receives back. The diagnostic program declares:

```text
UmicomU64 UmicomProgramSystemCall(UmicomU64 number,
    UmicomU64 first, UmicomU64 second, UmicomU64 third);
```

`UmicomU64` is the project's unsigned 64-bit integer type. Unsigned means the values are not negative. `number` selects a service; the other three values carry its arguments. This declaration does not implement the function. Its implementation is in `programs/diagnostic/entry.S`.

## 2. Find a label, not a C brace

The line `UmicomProgramSystemCall:` is a label naming an instruction location. `.global` makes that symbol available to the linker, which connects this Assembly definition with the C declaration. A line starting with a dot such as `.section` directs the assembler; it is not an instruction executed by the processor.

 <svg viewbox="0 0 700 110" role="img" aria-label="The Assembly function adapts the C calling convention to Umicom&#x27;s native service convention." style="width:100%;max-width:700px"><title>The Assembly function adapts the C calling convention to Umicom&#x27;s native service convention.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">C calls bridge</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Bridge rearranges registers</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">ECALL enters monitor</text></svg>

The Assembly function adapts the C calling convention to Umicom's native service convention.

```text
UmicomProgramSystemCall:
    mv a7, a0
    mv a0, a1
    mv a1, a2
    mv a2, a3
    ecall
    ret
```

## 3. Understand both conventions

The C compiler places these four integer arguments in a0 through a3. The native service convention expects the operation number in a7 and the three arguments in a0 through a2. The four moves connect the two conventions. The `ecall` causes a controlled trap; the Kernel checks the request and resumes the program when allowed. A trap is a transfer of control to a handler, not necessarily an error.

The reply replaces a0. The monitor's current contract preserves the other integer registers across successful calls. In particular, the return address remains available to `ret`. This contract is why the six-line bridge can return correctly. It is not safe to assume that every operating system uses this same convention.

## 4. Keep addresses and values separate

For ABI_QUERY, a0 contains a selector number, not a pointer. For COPY, a0 names a destination address, a1 names a source address and a2 is a byte count. The same physical register can represent different kinds of information for different services. Read the operation's contract before interpreting its arguments.

## Worked exercise

Trace `UmicomProgramSystemCall(3, 5, 0, 0)`. After the moves, a7=3 and a0=5. Selector 5 asks for the copy limit. The current monitor replies 64 in a0; the C function therefore returns 64. That number is a maximum byte count, not a pointer.

<details>

<summary>Check your understanding</summary>

Why is copying a0 to a7 done first? Because the next move overwrites a0. Reversing these two moves would lose the original service number. Why is there no ordinary C `return`? Assembly uses an instruction sequence; `ret` expresses the return transfer.

</details>

## Read the source next

Compare `programs/diagnostic/entry.S` with `include/umicom/kernel/user_abi.h`. Then read `programs/support/native_contract.c`, which calls this bridge without knowing how registers are moved. That separation allows host tests to supply fake replies while the guest test uses real ECALL instructions.

---

[Read this lesson in HTML](../../../courses/learning-riscv-assembly/lessons/01-follow-a-system-call.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Understand entry, return and program exit](02-entry-return-and-exit.md)
