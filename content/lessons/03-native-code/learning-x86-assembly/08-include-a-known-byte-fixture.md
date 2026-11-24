<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-x86-assembly/08-include-a-known-byte-fixture.md

PURPOSE:
  Teach a beginner to include a known byte fixture in NASM using object-only exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Include a known byte fixture in NASM

[Previous lesson](07-count-and-repeat-bytes.md) · [Course contents](index.md) · [Next lesson](09-name-sections-and-link-symbols.md) · [HTML edition](../../../courses/learning-x86-assembly/lessons/08-include-a-known-byte-fixture.html)

## Include three known bytes

A record can contain a small block that is kept in a separate file. NASM's `incbin` copies bytes into the assembly output at the current position. It does not parse them as instructions or change their encoding. In this practice record, one marker byte comes first, then the file contents, then the copied length.

Prepare a fresh practice folder. Run these PowerShell statements from that folder to create a three-byte input.

~~~powershell
$path = Join-Path (Get-Location) 'practice-note.bin'
if (Test-Path -LiteralPath $path) { throw 'Choose a fresh practice folder.' }
[IO.File]::WriteAllBytes($path, [byte[]](0x31, 0x00, 0x32))
~~~

The file contains one digit byte, one zero byte, and another digit byte. Its size is three, even though the zero byte does not display as an ordinary character.

~~~nasm
section .rodata
    db 0xa5
included_start:
    incbin "practice-note.bin"
included_length equ $ - included_start
    db included_length
~~~

| Spelling | Example | What it tells the assembler |
| --- | --- | --- |
| `incbin` | `incbin "practice-note.bin"` | Copy the binary file's bytes into the current assembly section. |
| `incbin` with two numbers | `incbin "practice-note.bin", 1, 2` | Start one byte into this specific input and copy two bytes. The output for this version would contain `00 32` at the labels. |

[NASM manual, including external binary files](https://www.nasm.us/doc/nasm03.html#section-3.2.3)

## Inspect the object

1. Save the assembly as `include-note.asm` next to the input. Run `nasm -f elf64 include-note.asm -o include-note.o` from the practice folder.
2. Run `llvm-objdump -s -j .rodata include-note.o`. Expect the five bytes `a5 31 00 32 03`.
3. Add the offset and length shown in the table. The new output should be `a5 00 32 02`. If the file cannot be found, check the current practice folder and the source name before retrying.

## Compare the same bytes with Clang

~~~asm
.section .rodata,"a",@progbits
    .byte 0xa5
included_start:
    .incbin "practice-note.bin"
.equ included_length, . - included_start
    .byte included_length
~~~

Save as `include-note.s`. From the same practice folder run `clang --target=x86_64-unknown-linux-gnu -c include-note.s -o include-note-clang.o`. The same section inspection now uses the Clang object.

For a real project, make the binary input part of the build's dependency list. Rebuilding the object after the input changes then becomes part of the ordinary build workflow.
