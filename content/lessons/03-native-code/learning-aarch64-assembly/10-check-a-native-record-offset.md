<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-aarch64-assembly/10-check-a-native-record-offset.md

PURPOSE:
Check a C record offset before using it in Assembly

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check a C record offset before using it in Assembly

The practice record has a one-byte `present` field followed by a four-byte `units` field. The C compiler may insert padding between fields to align the second field. In this target layout, `units` begins four bytes from the record start. The Assembly instruction reads from `[x0, #4]`.

The C example uses `offsetof` and `static_assert`, checks the record's full size and refers to the Assembly function. These checks make assumptions visible before either object is used.

```powershell
clang --target=aarch64-none-elf -std=c23 -ffreestanding -c record-layout.c -o record-layout.o
clang --target=aarch64-none-elf -c read-record.S -o read-record.o
ld.lld --entry=btb_record_layout_probe -o record-inspection.elf record-layout.o read-record.o
llvm-objdump -d record-inspection.elf
```

Expect a resolved call and a word load at offset four. In a private copy, put `units` first. The old static assertions should fail. Native records follow the target's calling and layout conventions. If a file supplies its own fixed format, read that format's defined byte offsets independently. [Arm procedure call standard](https://github.com/ARM-software/abi-aa/blob/main/aapcs64/aapcs64.rst)

[Course contents](index.md) · [Previous lesson](09-load-a-stored-byte.md) · [Next lesson](11-admit-a-counted-byte-span.md) · [Source · read-record.S](../../../courses/learning-aarch64-assembly/examples/read-record.S) · [Source · record-layout.c](../../../courses/learning-aarch64-assembly/examples/record-layout.c) · [HTML edition](../../../courses/learning-aarch64-assembly/lessons/10-check-a-native-record-offset.html)
