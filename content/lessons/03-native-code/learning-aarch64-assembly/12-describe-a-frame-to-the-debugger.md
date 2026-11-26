<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/12-describe-a-frame-to-the-debugger.md

PURPOSE:
Describe a saved stack frame to debugging tools

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Describe a saved stack frame to debugging tools

The earlier nested-call example saved X29 and X30. A debugger needs enough information to reconstruct the previous frame when execution is interrupted inside this function. Call-frame information, or CFI, describes where the frame and saved registers are at each instruction range.

The `stp` instruction changes the stack. `.cfi_def_cfa_offset 16` describes that change. The following CFI entries locate the saved registers relative to the canonical frame address. Later directives describe the restoration after `ldp`.

```powershell
clang --target=aarch64-none-elf -c call-with-cfi.S -o call-with-cfi.o
llvm-readobj --sections call-with-cfi.o
llvm-dwarfdump --eh-frame call-with-cfi.o
```

Look for `.eh_frame` and a frame description with the 16-byte adjustment. Compare the offset rules for the two saved registers. A machine can still assemble the instructions if the metadata is omitted, but tools then have less evidence about the saved state. This is an ELF example. A Windows binary uses its own unwind format. [Microsoft ARM64 exception handling](https://learn.microsoft.com/en-us/cpp/build/arm64-exception-handling)

[Course contents](index.md) · [Previous lesson](11-admit-a-counted-byte-span.md) · [Next lesson](13-check-the-byte-contract-in-host-c.md) · [Source · call-with-cfi.S](../../../courses/learning-aarch64-assembly/examples/call-with-cfi.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/12-describe-a-frame-to-the-debugger.html)
