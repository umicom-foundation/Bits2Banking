<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/11-trace-a-file-backed-entry.md

PURPOSE:
Separate the ELF file offset, virtual entry address and physical mapping before loading code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Trace an executable entry to its file bytes

[Course contents](index.md) · [Previous lesson](10-change-inactive-private-pages.md) · [Browser edition](../../../courses/multikernel-systems/lessons/11-trace-a-file-backed-entry.html)

An ELF executable places groups of bytes into loadable segments. A segment describes where its file bytes begin, how many file bytes it has and where those bytes belong in the memory view. The entry point names the virtual address where a prepared program would start.

## Trace the check

Find the entry’s offset within its segment. Add that offset to the segment’s file offset to locate the exact first entry byte in the file. Use the prepared page table separately to find the physical byte. The three coordinates describe different spaces.

~~~text
Choose the loadable segment containing the entry address.
Subtract the segment's virtual start from the entry address.
Check that the difference is inside the file-backed part.
Add the difference to the file offset and to the mapped physical start.
Record the coordinates without writing or starting the target.
~~~

## Run the Kernel’s hosted layout checks

In the sibling Umicom Kernel checkout use the focused hosted test project. Run each command separately and stop on errors. These cases use synthetic files and a memory model.

~~~powershell
cmake -S tests/riscv_domain_address_space -B build/domain-layout-host -G Ninja -DBUILD_TESTING=ON
cmake --build build/domain-layout-host
ctest --test-dir build/domain-layout-host --output-on-failure --no-tests=error -R '^kernel[.]riscv_domain_address[.]image-(layout-exact|entry-in-bss|late-rights)$'
~~~

Expect three cases to pass. The exact layout case locates a byte 44 positions into a segment whose file data starts at offset 4096. That locates file offset 4140. The entry-in-BSS case rejects an entry in the zero-fill part. The late-rights case refuses a range with incompatible page permissions.

## Predict a result

Assume a segment has 48 file bytes and 64 memory bytes. Decide whether offset 40 or offset 52 identifies a byte in the file. Then explain why the valid file location alone does not establish that the same byte is already resident in the prepared RAM.

The layout test checks the coordinates and required page permissions with the existing ELF inspector. A successfully verified layout can still contain different bytes at the physical address. The Kernel must separately verify the installed data and instruction visibility before beginning execution.

- [Kernel layout receipt declaration](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/riscv64/domain_image.h)
- [Kernel hosted source fixture](https://github.com/umicom-foundation/umicom-kernel/blob/main/tests/riscv_domain_address_space/domain_address_tests.c)
- [ELF program loading specification](https://gabi.xinuos.com/elf/07-pheader.html)
