<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-x86-assembly/06-reserve-storage.md

PURPOSE:
  Teach a beginner to reserve storage in NASM using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Reserve storage in NASM

[Previous lesson](05-write-initialized-data.md) · [Course contents](index.md) · [Next lesson](07-count-and-repeat-bytes.md) · [HTML edition](../../../courses/learning-x86-assembly/lessons/06-reserve-storage.html)

A practice application might need room to prepare a record before it has any values to write. NASM reserve directives describe how much space to set aside. For this lesson, put those declarations in `.bss`, the section used for storage without an initialized payload. The object records the extent of the storage so later tools know how much room is needed. [NASM manual, RES directives](https://www.nasm.us/doc/nasm03.html#section-3.2.2)

## Count units and convert them to bytes

Each directive takes one operand. The operand counts units of the width named by that directive. Multiply the count by the width to find the bytes reserved.

| Directive | Bytes per unit | Practice count | Bytes reserved |
| --- | ---: | ---: | ---: |
| `RESB` | 1 | 3 | 3 |
| `RESW` | 2 | 2 | 4 |
| `RESD` | 4 | 3 | 12 |
| `RESQ` | 8 | 2 | 16 |
| `REST` | 10 | 2 | 20 |
| `RESO` | 16 | 1 | 16 |
| `RESY` | 32 | 2 | 64 |
| `RESZ` | 64 | 1 | 64 |

Use small literal counts at first so they are known when assembly assigns positions. The unit widths do not align the next location automatically. If a design needs an alignment boundary, choose and verify that boundary separately. [NASM manual, reserved storage and critical expressions](https://www.nasm.us/doc/nasm03.html#section-3.2.2)

## Reserve a practice workspace

1. Save the following text as `record-scratch.asm` in the same practice folder.

~~~nasm
section .bss
tag_buffer:     resb 3   ; Leave room for the three-byte tag.
day_slots:      resw 2
entry_slots:    resd 3
order_slots:    resq 2
extended_slots: rest 2
colour_block:   reso 1
review_rows:    resy 2
review_block:   resz 1
scratch_end:
~~~

2. If NASM and LLVM’s object inspector are already available, assemble an x86-64 ELF object and read its section and symbol records.

~~~powershell
nasm -f elf64 record-scratch.asm -o record-scratch.o
llvm-readobj --sections --symbols record-scratch.o
~~~

3. Find `.bss` and check that its type is `SHT_NOBITS`. In this ELF object, that section describes a range of storage without occupying an equal number of initialized bytes in the file. Count the reserved bytes as `3 + 4 + 12 + 16 + 20 + 16 + 64 + 64 = 199`. Compare `scratch_end` with `tag_buffer` for the same 199-byte span.
4. Compare this output to the object from the previous lesson. The initialized record has data bytes in `.data`. The scratch example records its size, symbols and offsets in the object. File size alone will include metadata and cannot tell you how much storage each section describes.

In a normally linked and loaded native program, the loader can supply zero-filled storage for its BSS range. That happens later. This worksheet assembles and inspects an object only. Code that fills a scratch buffer must still keep track of its capacity and how many bytes it has written before attempting to read a record.

## Compare the reserved layout with another assembler

Save the following GNU-style source as `record-scratch-compare.s`. Each `.zero` operand is already a byte count. The `.bss` section gives these ranges uninitialized storage semantics in the ELF object.

~~~asm
.bss
tag_buffer:     .zero 3
day_slots:      .zero 2 * 2
entry_slots:    .zero 3 * 4
order_slots:    .zero 2 * 8
extended_slots: .zero 2 * 10
colour_block:   .zero 1 * 16
review_rows:    .zero 2 * 32
review_block:   .zero 1 * 64
scratch_end:
~~~

Use either available assembler to produce an object. The inspector shows the object’s native format.

~~~powershell
clang --target=x86_64-unknown-linux-gnu -c record-scratch-compare.s -o record-scratch-clang.o
llvm-readobj --sections --symbols record-scratch-clang.o
as --64 -o record-scratch-gnu.o record-scratch-compare.s
llvm-readobj --sections --symbols record-scratch-gnu.o
~~~

An ELF inspector identifies the section as `SHT_NOBITS`. A GNU assembler configured for Windows can instead produce COFF and identify the range as uninitialized data, with no raw data pointer. Section sizes may include padding in that format. Compare the two labels to recover the exact span in either object. [GNU assembler section reference](https://sourceware.org/binutils/docs/as/Bss.html)

## Check your understanding

1. How much space does `RESY 2` reserve? Two 32-byte units reserve 64 bytes.
2. What changes if `day_slots` uses `RESB 2`? Only 2 bytes are reserved there, so the later labels move 2 bytes earlier.
3. When reviewing a data import in Umicom Bank or an example built on Framework, which measurement would you use before writing a record? Use the capacity of the receiving buffer. Before reading a field, check how many bytes were actually written or received.
