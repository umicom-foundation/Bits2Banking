<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/10-change-inactive-private-pages.md

PURPOSE:
Trace the Kernel’s two-pass permission check and a late refusal using ordinary host memory.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check every inactive page before changing rights

[Course contents](index.md) · [Previous lesson](09-separate-firmware-inventory-from-hart-entry.md) · [Next lesson](11-trace-a-file-backed-entry.md) · [Browser edition](../../../courses/multikernel-systems/lessons/10-change-inactive-private-pages.html)

An address space supplies the rules for finding an address and using the bytes there. A page table is the structure that holds those rules. In this exercise a RISC-V domain has two pages of private data and one separately reserved mailbox page. The mailbox gives the domains a place to exchange small control messages.

## Trace the check

Write permission lets the domain change data. Execute permission lets it fetch instructions. The Kernel’s inactive domain owner admits supervisor read/write or read/execute for this request. A change to read/execute keeps the original physical frame. The mailbox keeps read/write permission.

~~~text
Reserve the private pages and the separate mailbox.
Inspect the backing and existing permissions on every selected page.
If one page differs, preserve the complete table.
Otherwise change the permissions on the selected private pages.
Translate both private views and the mailbox again.
~~~

## Run the hosted C lab

Open a terminal in Bits2Banking alongside a sibling Umicom Kernel checkout containing inactive domain protection. The lesson links to the real allocator and page table code and uses one aligned byte array in the host program.

~~~powershell
cmake -S content/labs/native/riscv-inactive-domain -B build/riscv-inactive-domain -G Ninja -DUMICOM_KERNEL_SOURCE=../umicom-kernel -DBUILD_TESTING=ON
cmake --build build/riscv-inactive-domain
ctest --test-dir build/riscv-inactive-domain -V --no-tests=error
~~~

The first check reports that both private pages changed and the mailbox stayed writable. The second makes the later page disagree with the expected permissions. The refusal preserves every byte in the simulated RAM, including the first page’s translation. Both runs release the original tables and reservations.

## Predict a result

Before running the second check, predict the permission of the first private page after refusal. Locate the line that verifies it in the lab source. Then explain why a routine that changes each page immediately after checking it would leave a different result.

This is a hosted memory exercise. The hierarchy remains inactive. Installing it and synchronizing cached translations and instruction fetch are responsibilities of a later Kernel activation path.

- [Hosted C23 source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/native/riscv-inactive-domain/private_pages.c)
- [Kernel domain protection declaration](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/riscv64/domain_address_space.h)
- [RISC-V supervisor architecture](https://docs.riscv.org/reference/isa/v20260120/priv/supervisor.html)
