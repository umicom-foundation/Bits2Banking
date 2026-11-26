<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/05-preserve-a-return-address.md

PURPOSE:
Preserve the return address across a nested call

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Preserve the return address across a nested call

`bl` branches to a function and stores the return address in X30, also called the link register. A leaf function such as the earlier example can return straight through X30. A nested call replaces it, so this function stores both X30 and the previous frame pointer X29 first.

1. `stp` subtracts 16 from SP and stores two 8-byte registers on the stack.
2. `mov x29, sp` gives the current frame a stable reference.
3. `bl` installs the return address for the inner call. The saved outer address stays in the frame.
4. `ldp` reloads both registers and adds 16 back to SP. `ret` can now use the original address.

```powershell
clang --target=aarch64-none-elf -c call-an-external.S -o call-an-external.o
llvm-objdump -dr call-an-external.o
```

Check that the stack adjustment is −16 on entry and +16 on exit. If you remove the restoring instruction in a private copy, the assembler can still encode it. A successful assembly gives no evidence that stack ownership is balanced. This ELF teaching source omits platform unwinding declarations and is used for offline inspection. [Arm AAPCS64 calling convention](https://github.com/ARM-software/abi-aa/blob/main/aapcs64/aapcs64.rst)

[Course contents](index.md) · [Previous lesson](04-trace-a-bounded-loop.md) · [Next lesson](06-link-an-elf-call.md) · [Source · call-an-external.S](../../../courses/learning-aarch64-assembly/examples/call-an-external.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/05-preserve-a-return-address.html)
