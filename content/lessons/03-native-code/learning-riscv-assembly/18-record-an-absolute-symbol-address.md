<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/18-record-an-absolute-symbol-address.md

PURPOSE:
  Teach a beginner to record an absolute symbol address using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Record an absolute symbol address

[Previous lesson](17-split-a-constant-into-two-instructions.md) · [Course contents](index.md) · [Next lesson](19-pair-a-location-with-a-relative-address.md) · [HTML edition](../../../courses/learning-riscv-assembly/lessons/18-record-an-absolute-symbol-address.html)

In Assembly, a **symbol** gives a name to a location. You can define its storage in one section and refer to its address in another section. The assembler writes enough information for the linker to find the final address once it chooses where the sections belong. That information is a **relocation**.

## Give an address two parts

Save this file as `absolute.s`. The function places the address of `course_seed` in the usual result register `a0`. The data word at that address contains 23. Read the two roles separately while tracing the example.

~~~asm
.text
.globl absolute_seed_address
absolute_seed_address:
    lui a0, %hi(course_seed)
    addi a0, a0, %lo(course_seed)
    ret

.data
.globl course_seed
course_seed:
    .word 23
~~~

~~~text
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -mno-relax -c absolute.s -o absolute.o
llvm-objdump -dr -M no-aliases absolute.o
~~~

Find `R_RISCV_HI20` at instruction offset 0 and `R_RISCV_LO12_I` at offset 4. They both name `course_seed`. `%hi` and `%lo` tell the assembler how to split the final address once it is available. The zero immediates in the object are placeholders the linker will fill.

1. Point to the label that names the start of the function.
2. Point to the label that names the data.
3. Cover the relocation lines and ask if the two instructions alone tell you the final address. Then reveal the symbol names the linker receives.
4. Change the data value from 23 to 24 and assemble again. The object should still refer to the named address with the same two relocation types. The stored word changes.

The example uses an absolute address pair for a range that fits those instructions. A relocatable operating system component often needs a pair based on the location of its instruction instead. The next lesson shows that form.

[RISC-V ELF object format and absolute addresses](https://docs.riscv.org/reference/abi/riscv-elf-object-files.html)
