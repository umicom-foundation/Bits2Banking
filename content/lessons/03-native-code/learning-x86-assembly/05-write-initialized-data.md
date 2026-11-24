<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-x86-assembly/05-write-initialized-data.md

PURPOSE:
  Teach a beginner to write initialized data in NASM using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Write initialized data in NASM

[Previous lesson](04-follow-arguments-through-a-function.md) · [Course contents](index.md) · [Next lesson](06-reserve-storage.md) · [HTML edition](../../../courses/learning-x86-assembly/lessons/05-write-initialized-data.html)

An assembler can turn a short text file into an object file. An object file can hold instructions, data and information about their locations. This lesson creates a small practice record in its data section. You can inspect the record in the object without building or starting an application.

## Choose a width

The directive tells the assembler how wide each data unit is. A name followed by a colon is a label. It marks the position of the next byte. These directives describe data for the assembler.

| Directive | Bytes per unit | Operand used below |
| --- | ---: | --- |
| `DB` | 1 | An ASCII tag containing three one-byte characters |
| `DW` | 2 | An integer occupying one word |
| `DD` | 4 | An integer occupying one doubleword |
| `DQ` | 8 | An integer occupying one quadword |
| `DT` | 10 | The extended-precision floating-point literal `1.0` |
| `DO` | 16 | Exactly 16 ASCII characters in one unit |
| `DY` | 32 | Exactly 32 ASCII characters in one unit |
| `DZ` | 64 | Exactly 64 ASCII characters in one unit |

The wider `DT`, `DO`, `DY` and `DZ` directives reject integer numeric operands. Use the supported operand type for the directive you select. In the example, the point in `1.0` identifies a floating-point literal. The three wide strings have exact widths so you can count their bytes directly. [NASM manual, initialized data and constants](https://www.nasm.us/doc/nasm03.html#section-3.2.1)

## Assemble the practice record

1. In a practice folder, save the following text as `record-data.asm`. It describes a fictional review record and three text samples.

~~~nasm
section .data
format_tag:    db 'B2B'  ; Three ASCII bytes identify the practice format.
review_day:    dw 0x0205
entry_number:  dd 0x01020306
ledger_order:  dq 0x0807060504030201
extended_unit: dt 1.0   ; Store one x87 extended-precision value.
wide_text:     do 'red-orange-green'
row_text:      dy '0123456789abcdefghijklmnopqrstuv'
block_text:    dz 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_'
record_end:
~~~

2. If NASM and LLVM’s object inspector are already available, assemble an x86-64 ELF object and inspect its data and labels.

~~~powershell
nasm -f elf64 record-data.asm -o record-data.o
llvm-objdump --full-contents --section=.data record-data.o
llvm-objdump --syms record-data.o
~~~

3. Find the leading bytes `42 32 42 05 02 06 03 02 01`. The start of this record contains the ASCII letters and digit of `B2B`. On x86, the least significant byte of a multi-byte integer appears first. The word `0x0205` therefore appears as `05 02`. This convention is called little-endian byte order.
4. Compare the offsets of `format_tag` and `record_end`. This record spans `3 + 2 + 4 + 8 + 10 + 16 + 32 + 64 = 139` bytes. Object headers, labels and any padding contribute to the file separately.

The tag contains exactly three bytes. A reader that expects a C string would need an explicit terminating zero or a supplied byte count. When a record is read by Umicom Framework or another application, specify the byte widths, field lengths and byte order in its format so another tool can read the same file. [NASM manual, string constants](https://www.nasm.us/doc/nasm03.html#section-3.4.4)

## Compare the layout with another assembler

Save the following GNU-style source as `record-data-compare.s`. It places the same fields at the same offsets. The `.byte` row spells out the ten expected bytes of the extended-precision value to make the comparison independent of assembler-specific floating-point syntax.

~~~asm
.data
format_tag:    .ascii "B2B"
review_day:    .short 0x0205
entry_number:  .long  0x01020306
ledger_order:  .quad  0x0807060504030201
extended_unit: .byte  0,0,0,0,0,0,0,0x80,0xff,0x3f
wide_text:     .ascii "red-orange-green"
row_text:      .ascii "0123456789abcdefghijklmnopqrstuv"
block_text:    .ascii "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"
record_end:
~~~

Use either available assembler to create an object and inspect its data. The Clang command below explicitly selects ELF. GNU `as` uses its configured object format.

~~~powershell
clang --target=x86_64-unknown-linux-gnu -c record-data-compare.s -o record-data-clang.o
llvm-objdump --full-contents --section=.data record-data-clang.o
as --64 -o record-data-gnu.o record-data-compare.s
llvm-objdump --full-contents --section=.data record-data-gnu.o
~~~

Use the labels to compare the 139-byte record if the section ends with padding. An inspector may display several bytes together. Read them in the order shown and break the group into two hex digits per byte. [LLVM object inspector guide](https://llvm.org/docs/CommandGuide/llvm-objdump.html)

## Check your understanding

1. If an additional one-byte flag follows the tag, what happens to `review_day`? It moves from offset 3 to offset 4 unless the record layout is changed elsewhere.
2. What could happen if you write the day with `DD` and keep reading it as a word? The following fields move because `DD` writes four bytes. A reader using the former offsets would read some bytes from the wrong field.
3. Why inspect the output instead of immediately linking it? The object already shows whether the record’s data bytes and defined offsets match the format.
