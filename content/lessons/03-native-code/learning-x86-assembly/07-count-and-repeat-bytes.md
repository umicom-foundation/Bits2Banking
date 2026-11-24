<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-x86-assembly/07-count-and-repeat-bytes.md

PURPOSE:
  Teach a beginner to count and repeat bytes in NASM using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Count and repeat bytes in NASM

[Previous lesson](06-reserve-storage.md) · [Course contents](index.md) · [Next lesson](08-include-a-known-byte-fixture.md) · [HTML edition](../../../courses/learning-x86-assembly/lessons/07-count-and-repeat-bytes.html)

## Give the length a name

A practice record starts with one marker byte, contains three zero bytes, and ends with another marker. The record is five bytes long. Ask the assembler to calculate that number from the two positions. Then store the calculated length and the record's offset from its section in two extra bytes.

~~~nasm
section .rodata
record_start:
    db 0x51
    times 3 db 0
    db 0x7e
record_length equ $ - record_start
record_offset equ record_start - $$
    db record_length, record_offset
~~~

| Spelling | Example | What it tells the assembler |
| --- | --- | --- |
| `times` | `times 3 db 0` | Assemble the data declaration three times. The source produces three adjacent bytes. |
| `equ` | `record_length equ $ - record_start` | Give a single assembly-time value to the name. The directive itself adds no bytes. |
| `$` | `$ - record_start` | Use the position at the start of the current source statement to calculate the distance from the label. |
| `$$` | `record_start - $$` | Subtract the section's beginning to obtain an offset within it. |

The first expression is evaluated when its `equ` statement is assembled. The number is used again by `db`, which emits it as one byte. For this small record, all quantities fit in a byte. A larger format would need a larger length field and a defined byte order. [NASM manual, data and expression syntax](https://www.nasm.us/doc/nasm03.html)

## Inspect the result without running it

1. Save the NASM source as `count-record.asm` in a practice folder. Run `nasm -f elf64 count-record.asm -o count-record.o`.
2. Run `llvm-objdump -s -j .rodata count-record.o`. Find these seven bytes in order, `51 00 00 00 7e 05 00`.
3. Change the repeat count to four, assemble again, and check for one additional zero byte and a length field of `06`. The record remains at offset zero because it is the first data in the section.

If the inspector reports that the section is missing, check the file name, assembler exit code and the spelling of `.rodata`. An object file contains assembly output and layout information for a linker. This exercise examines bytes and does not build a runnable application.

## Compare the same layout with the Clang assembler

~~~asm
.section .rodata,"a",@progbits
section_start:
record_start:
    .byte 0x51
    .fill 3, 1, 0
    .byte 0x7e
.equ record_length, . - record_start
.equ record_offset, record_start - section_start
    .byte record_length, record_offset
~~~

Save as `count-record.s` and run `clang --target=x86_64-unknown-linux-gnu -c count-record.s -o count-record-clang.o`. Inspect its `.rodata` section with the same `llvm-objdump` command and the new output path. Both source styles describe the same bytes using different assembler conventions.

In C, you might define a file header whose length is calculated by the code that writes it. Here the bytes are fixed at assembly time. The separate length field helps another program check where the record ends.
