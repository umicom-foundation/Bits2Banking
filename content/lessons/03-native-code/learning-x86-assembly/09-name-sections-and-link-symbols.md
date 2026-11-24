<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-x86-assembly/09-name-sections-and-link-symbols.md

PURPOSE:
  Teach a beginner to name sections and link symbols in NASM using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Name sections and link symbols in NASM

[Previous lesson](08-include-a-known-byte-fixture.md) · [Course contents](index.md) · [HTML edition](../../../courses/learning-x86-assembly/lessons/09-name-sections-and-link-symbols.html)

## Separate the data and its reference

An object file can publish a symbol for another object to use. It can also refer to a name whose definition will come from another object. The assembler writes a relocation record so the linker knows which bytes will need the final address.

This example publishes one 64-bit slot named `count_pointer`. The slot will eventually contain the address of `source_count`, which is supplied elsewhere. The exercise stops at the object file.

~~~nasm
bits 64
section .rodata
global count_pointer
extern source_count
count_pointer:
    dq source_count
~~~

| Spelling | Example | What it tells the assembler |
| --- | --- | --- |
| `bits` | `bits 64` | Select the instruction encoding mode. It does not switch a running processor, and an ELF64 data-only object still needs an appropriate output format. |
| `section` | `section .rodata` | Place new declarations in the named section. Here it is read-only data in the ELF object. |
| `segment` | `segment .rodata` | Use NASM's alternate spelling of the same section directive. |
| `global` | `global count_pointer` | Make this definition visible to a linker outside the current assembly unit. |
| `extern` | `extern source_count` | Declare a name that another object will define. The relocation records the use of the unresolved name. |

[NASM manual, assembler directives](https://www.nasm.us/doc/nasm08.html) · [NASM manual, declaring data](https://www.nasm.us/doc/nasm03.html#section-3.2.1)

## Inspect the symbol and relocation

1. Save as `count-reference.asm`. Assemble with `nasm -f elf64 count-reference.asm -o count-reference.o`.
2. Run `llvm-objdump -t -r count-reference.o`. Look for `count_pointer` defined in `.rodata`, `source_count` marked undefined, and an `R_X86_64_64` relocation at offset zero that names `source_count`.
3. Change `section` to `segment` and assemble again. Compare the same three observations. If the symbol is still undefined, that is the expected state before linking. A missing relocation usually means the source did not refer to that name in the stored data.

## Compare with GNU-style assembly

~~~asm
.section .rodata,"a",@progbits
.globl count_pointer
.extern source_count
count_pointer:
    .quad source_count
~~~

Save as `count-reference.s`. Run `clang --target=x86_64-unknown-linux-gnu -c count-reference.s -o count-reference-clang.o` and use the same object inspection command. Here the selected Clang target supplies the object format and target architecture.

## Compare with a C declaration

~~~c
#include <stdint.h>

extern const uint32_t source_count;
const uint32_t *const count_pointer = &source_count;
~~~

The C declaration also says that another unit defines `source_count`. Its compiled object can put the pointer in a relocation-bearing data section chosen by the compiler. That section name and exact relocation representation depend on the target. The external name still has to match the definition. This is one small version of the agreement that lets an Umicom C file refer to separately compiled assembly.
