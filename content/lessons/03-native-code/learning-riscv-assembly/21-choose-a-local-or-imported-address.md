<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/21-choose-a-local-or-imported-address.md

PURPOSE:
  Teach a beginner to choose a local or imported address using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Choose a local or imported address

[Previous lesson](20-find-a-linker-relaxation-hint.md) · [Course contents](index.md) · [HTML edition](../../../courses/learning-riscv-assembly/lessons/21-choose-a-local-or-imported-address.html)

The assembler shorthand `la` asks for the address of a named object. Options can tell the assembler whether to use a direct relative pair or consult a table of addresses. The results become clearer when you inspect the real instructions and relocations.

## Compare local and imported address forms

Save this as `address-macros.s`. It refers to `course_seed`, which another object would define. The file has no definition for that name. The exercise stops before linking.

~~~asm
.text
.globl inspect_address_macros
inspect_address_macros:
    .option push
    .option nopic
    la a0, course_seed
    .option pic
    la a1, course_seed
    lla a2, course_seed
    .option pop
    ret
~~~

~~~text
clang --target=riscv64-unknown-elf -march=rv64i -mabi=lp64 -mno-relax -c address-macros.s -o address-macros.o
llvm-objdump -dr -M no-aliases address-macros.o
~~~

| Source choice | Typical expansion in this object | Upper relocation |
| --- | --- | --- |
| `la a0, course_seed` after `.option nopic` | `auipc`, then `addi` | `R_RISCV_PCREL_HI20` |
| `la a1, course_seed` after `.option pic` | `auipc`, then `ld` | `R_RISCV_GOT_HI20` |
| `lla a2, course_seed` | `auipc`, then `addi` | `R_RISCV_PCREL_HI20` |

A **global offset table**, or GOT, is a table of addresses. Here the `ld` loads an address from such a table slot. It does not read the integer stored at `course_seed`. The `lla` shorthand requests the direct local-address form. Use it when that addressing choice fits the symbol and link configuration. The `.option push` and `.option pop` pair saves and restores the surrounding assembler choices.

In C, a declaration introduces the name of an object whose storage can be provided elsewhere. This companion shows which value the address operation returns. Save it as `declared-address.c`.

~~~c
#include <stdint.h>

extern int32_t course_seed;

const int32_t *seed_location(void)
{
    return &course_seed;
}
~~~

Use `gcc -std=c23 -Werror -fsyntax-only declared-address.c` to check the declaration and return types. The two languages can share a named object once their types, target and link arrangement agree. In Umicom Kernel work, record the exact target and confirm the intended references before writing an entry-point or loading example.

[RISC-V ELF GOT and PC-relative relocations](https://docs.riscv.org/reference/abi/riscv-elf-object-files.html)
