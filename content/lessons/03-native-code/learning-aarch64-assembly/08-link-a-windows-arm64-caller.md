<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/08-link-a-windows-arm64-caller.md

PURPOSE:
Link a Windows ARM64 call without executing the image

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Link a Windows ARM64 call without executing the image

Build the independent C caller for Windows ARM64 and link it against the Umicom C COFF output from the previous lesson. The files are read and written as development artifacts. No Arm runtime is required for this link experiment.

```powershell
clang --target=aarch64-pc-windows-msvc -O0 -std=c23 -ffreestanding -fno-stack-protector -c caller.c -o caller-arm64.obj
llvm-readobj --relocations caller-arm64.obj
lld-link /machine:arm64 /subsystem:console /entry:btb_arm_entry /nodefaultlib /out:linked-arm64.exe caller-arm64.obj answer-umicom.obj
llvm-readobj --file-headers --coff-imports linked-arm64.exe
```

Look for `IMAGE_REL_ARM64_BRANCH26` against `umc_constant_return` in the caller and an ARM64 PE image from the linker. The image's minimal entry is intended for object inspection. Make a separate link without the Umicom C object and check that it refuses the unresolved function. Do not open or run either image during this lab.

If `lld-link` refuses the file's machine type, inspect each object header before altering the linker flags. Windows x64, Windows ARM64, AArch64 ELF and Arm64EC are different link targets. Preserve the first linker diagnostic for review in Umicom Studio. [Microsoft ARM64 ABI](https://learn.microsoft.com/en-us/cpp/build/arm64-windows-abi-conventions) · [Microsoft PE and COFF format](https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#arm64-processors)

[Course contents](index.md) · [Previous lesson](07-compare-an-elf-and-coff-object.md) · [Source · caller.c](../../../courses/learning-aarch64-assembly/examples/caller.c) · [Source · answer.c](../../../courses/learning-aarch64-assembly/examples/answer.c) · [Next lesson](09-load-a-stored-byte.md) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/08-link-a-windows-arm64-caller.html)
