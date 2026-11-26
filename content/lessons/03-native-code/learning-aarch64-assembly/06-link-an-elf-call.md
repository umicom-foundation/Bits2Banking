<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/06-link-an-elf-call.md

PURPOSE:
Follow an unresolved call into an ELF link

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Follow an unresolved call into an ELF link

An object file can name a function that is defined elsewhere. Its relocation tells the linker which instruction needs a destination address. The Arm ELF object uses `R_AARCH64_CALL26` for the external `bl` in the previous lesson.

```powershell
llvm-readobj --relocations --symbols call-an-external.o
clang --target=aarch64-none-elf -std=c23 -ffreestanding -c provider.c -o answer-clang.o
ld.lld --entry=btb_call_external -o linked-elf.elf call-an-external.o answer-clang.o
llvm-objdump -d linked-elf.elf
```

Look for a relocation referencing `umc_constant_return` in the object. Clang emits that name from the function in `provider.c`. In the linked disassembly, the branch points at the defined function. Try a separate output without the provider. LLD should report the missing symbol.

The link entry is a convenient symbol for an offline experiment. It has no process startup routine, board setup or firmware services. Use the artifacts as evidence that the references resolved. The Umicom Kernel boot roadmap has its own separate loader and live-transfer qualification. [Arm ELF64 ABI](https://github.com/ARM-software/abi-aa/blob/main/aaelf64/aaelf64.rst)

[Course contents](index.md) · [Previous lesson](05-preserve-a-return-address.md) · [Next lesson](07-compare-an-elf-and-coff-object.md) · [Source · call-an-external.S](../../../courses/learning-aarch64-assembly/examples/call-an-external.S) · [Source · provider.c](../../../courses/learning-aarch64-assembly/examples/provider.c) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/06-link-an-elf-call.html)
