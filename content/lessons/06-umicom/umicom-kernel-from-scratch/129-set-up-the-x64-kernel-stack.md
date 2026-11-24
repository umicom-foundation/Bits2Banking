<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/129-set-up-the-x64-kernel-stack.md

PURPOSE:
Explain what the x64 entry checks before calling compiled C on a Kernel-owned stack.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Set up the x64 Kernel stack

[Course contents](index.md) · [Previous lesson](128-observe-the-boot-reservation-plan.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/129-set-up-the-x64-kernel-stack.html)

When compiled C calls another function, it uses a stack, a region of memory that holds return addresses and temporary values. Umicom Kernel's Assembly entry uses an area reserved for the Kernel. You can inspect this area inside the linked x64 file before a loader or virtual machine runs it.

## Follow the first transfer

1. The caller must supply a readable handoff record in a mapped memory region. It places the address in register `RDI` and the byte length in `RSI`.
2. The Assembly entry checks the numerical bounds and the proposed region's separation from the Kernel image. A numeric check cannot tell whether the caller actually mapped the memory. The caller supplies that guarantee.
3. The Assembly loads the address of the top of the Kernel's reserved stack into `RSP`. The C entry can then use the stack under the System V AMD64 calling convention.

~~~asm
leaq __umicom_x86_stack_top(%rip), %rsp
xorq %rbp, %rbp
call UmicomKernelX86BootEntry
~~~

The linker aligns the stack top to a 16-byte boundary. The `call` instruction stores an eight-byte return address, so `RSP + 8` is a multiple of 16 when the C function begins. [System V AMD64 stack convention](https://gitlab.com/x86-psABIs/x86-64-ABI/-/blob/master/x86-64-ABI/low-level-sys-info.tex)

## Inspect the file

1. Follow the [Kernel x64 build guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/X86_64_ENTRY_CONTRACT.md) to build the standalone ELF.
2. Run this from the Kernel checkout. Adjust the build folder if you chose a different one.

~~~powershell
llvm-readelf --file-header --program-headers --symbols build/x86_64-entry/umicom-kernel-x64-entry.elf
~~~

3. Find `__umicom_x86_stack_bottom` and `__umicom_x86_stack_top` in the symbol listing. Subtract the bottom from the top. Expect hexadecimal `0x4000`, or 16,384 bytes. Check that the containing memory segment permits reading and writing and has no execute flag.

For example, subtract `0x203000` from `0x207000`. The first possible return-address slot is immediately below `0x207000`. Explain why the difference between these two symbols is the size of the stack even if a second build places it at different addresses.

The file inspection checks the linked entry, segment permissions and stack placement. A real boot also needs a loader that supplies the mappings and a valid record, then transfers control on the chosen machine.

[Next lesson · Observe a message with query rights](130-observe-a-message-with-query-rights.md)
