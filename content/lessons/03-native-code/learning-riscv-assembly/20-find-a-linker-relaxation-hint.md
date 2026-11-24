<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/20-find-a-linker-relaxation-hint.md

PURPOSE:
  Teach a beginner to find a linker relaxation hint using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Find a linker relaxation hint

[Previous lesson](19-pair-a-location-with-a-relative-address.md) · [Course contents](index.md) · [Next lesson](21-choose-a-local-or-imported-address.md) · [HTML edition](../../../courses/learning-riscv-assembly/lessons/20-find-a-linker-relaxation-hint.html)

A linker may have a shorter way to encode an address once it knows the final layout. RISC-V object files can mark some instructions as eligible for such a change. The term **relaxation** describes this opportunity. A tool that displays one input object can show the hints before any linking happens.

## Compare the same source twice

Use the `relative.s` file from the previous lesson. Keep its two labels and build it with both assembler options. Keep the resulting objects under different names.

~~~text
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -mno-relax -c relative.s -o fixed.o
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -mrelax -c relative.s -o eligible.o
llvm-objdump -dr -M no-aliases fixed.o
llvm-objdump -dr -M no-aliases eligible.o
~~~

| Look for | Fixed object | Eligible object |
| --- | --- | --- |
| Upper PC-relative relocation | One, naming the data symbol | One, naming the data symbol |
| Lower PC-relative relocation | One, naming the pairing label | One, naming the pairing label |
| Relaxation entries | Zero | Two, at the locations of the address instructions |

In both listings, first compare the printed instruction words. They are identical for this source and target. Then count `R_RISCV_RELAX` lines. These extra lines describe a possibility available to a later linker. They carry no new instruction for the processor to execute.

Keep the target and assembler options written next to your record. If your two objects show the same set of relocations, check which flag reached the assembler and which filename you inspected. A firmware engineer can inspect the linked output separately when exact instruction layout matters. Here the exercise ends at the object files.

[RISC-V linker relaxation](https://docs.riscv.org/reference/abi/riscv-elf-linker-relaxation.html)
