<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/07-compare-an-elf-and-coff-object.md

PURPOSE:
Compare ELF64 and Windows ARM64 COFF

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Compare ELF64 and Windows ARM64 COFF

An instruction set describes what the CPU executes. An object format describes how tools store the instructions, names, sections and relocation records. The same short ARM64 answer can be packaged for the two linkers.

Use a built Umicom C on PATH with the two native constant commands. Work in a new folder with a local copy of the examples. Both commands require a new output path. Their bounded input reads the integer return from `main` in `answer.c` and emits a function named `umc_constant_return` for the caller to link.

```powershell
umicom-c emit-constant-aarch64-elf answer.c answer-umicom.o
umicom-c emit-constant-arm64-coff answer.c answer-umicom.obj
llvm-readobj --file-headers --sections --symbols answer-umicom.o answer-umicom.obj
llvm-objdump -d answer-umicom.o answer-umicom.obj
```

Find `EM_AARCH64` in ELF and `IMAGE_FILE_MACHINE_ARM64` in COFF. Both define `umc_constant_return`. In the ELF symbols, find `$x`, the local mapping symbol that marks this Arm section as instructions. COFF uses its own section and symbol rules.

Compare the two disassemblies with the hand-written `return-constant.S` object. The three instruction words should agree. The complete object files differ because their headers and tables describe different formats. [Arm ELF64 ABI](https://github.com/ARM-software/abi-aa/blob/main/aaelf64/aaelf64.rst) · [Microsoft PE and COFF format](https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#arm64-processors)

[Course contents](index.md) · [Previous lesson](06-link-an-elf-call.md) · [Next lesson](08-link-a-windows-arm64-caller.md) · [Source · answer.c](../../../courses/learning-aarch64-assembly/examples/answer.c) · [Source · return-constant.S](../../../courses/learning-aarch64-assembly/examples/return-constant.S) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/07-compare-an-elf-and-coff-object.html)
