<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/142-read-a-partial-permission-transition.md

PURPOSE:
Read a partial permission transition

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read a partial permission transition

A permission plan describes proposed changes for each range. An applicator calls the selected operation and receives a status. In the Kernel’s hosted exercise, a function pointer connects that applicator to a small in-memory model of the pages.

## Read the three counters

- `plannedCount` is the number of operations the reviewed plan requires.
- `attemptedCount` includes every operation the applicator tried, including the one that returned the refusal.
- `completedCount` advances only when the callback returns exact `EFI_SUCCESS`.

Imagine a plan with six steps. The first two report success and step three reports a refusal. The result records six planned, three attempted and two reported complete. The remaining calls stay unopened. The failed action and status let a reviewer locate the point that stopped the plan.

A callback’s success is a report about its own operation. The next admission stage needs a fresh query of all four ranges to establish their current attributes. Treat a partial sequence as an interrupted transition. Recheck the attributes before deciding whether another plan is appropriate.

## Run the simulated refusal cases

From the Kernel repository root, choose the same exact x64 ELF as in the previous exercise.

```powershell
cmake -S tests/x86_uefi_permission_apply -B build/permission-apply -G Ninja "-DUMICOM_TEST_ELF=C:/path/to/verified/umicom-kernel-x64-entry.elf"
cmake --build build/permission-apply
ctest --test-dir build/permission-apply --output-on-failure --no-tests=error
```

Find the `protective-refused` and `relax-refused` cases in `tests/x86_uefi_permission_apply/permission_apply_tests.c`. Tell a classmate where each case stops and which evidence shows the later calls were left untouched. Then check the `empty` case. An already-correct set of ranges has no planned calls and needs no callback ports.

If a test reports a refusal earlier than expected, compare the selected callback and captured ranges with the fixture. These tests use the in-memory model. Testing actual firmware is a separate workflow.

[Course contents](index.md) · [Previous lesson · Order page permission changes](141-order-page-permission-changes.md) · [Next lesson · Read an exact EFI and ELF pair](143-read-an-exact-efi-elf-pair.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/142-read-a-partial-permission-transition.html)
