<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/141-order-page-permission-changes.md

PURPOSE:
Order page permission changes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Order page permission changes

Kernel preparation assigns each reserved memory range a job. Instructions belong on code pages. Constants and the handoff record hold data. A stack holds temporary data as the program runs. Each role needs a different combination of two switches.

The RO switch makes a range read-only. The XP switch prevents instruction execution. In this x86-64 boot profile, the planner expects code to become RO with XP cleared. Constants and the handoff page need RO and XP. The writable stack needs XP with RO cleared.

## Order the changes with paper first

1. Start with a code page that is writable and has XP set. Write its initial and final switch states.
2. Add RO before clearing XP. The intermediate page has both switches set. That order keeps the page from becoming writable and executable at the same time.
3. Repeat with a stack that has RO set and XP cleared. Set XP before clearing RO.
4. Compare a page that already matches its role. The plan contains no operation for its two switches.

Umicom builds one checked plan for all four roles. It verifies the captured ranges and existing observations before it lists changes. Setting all required restrictions first creates a simple rule a test can check across roles. Flags outside RO and XP belong to their existing owners.

## Verify the planner with the linked image fixture

At the Kernel repository root, set the CMake option `UMICOM_TEST_ELF` to the absolute path of the verified x64 Kernel ELF you intend to study. Use the same file for configure and test.

```powershell
cmake -S tests/x86_uefi_permission_transition -B build/permission-transition -G Ninja "-DUMICOM_TEST_ELF=C:/path/to/verified/umicom-kernel-x64-entry.elf"
cmake --build build/permission-transition
ctest --test-dir build/permission-transition --output-on-failure --no-tests=error
```

Expect the ordered case to pass. The exhaustive case considers all 256 combinations of the two input switches across four roles. If configuration refuses the file, check that the path points to the linked x64 image and that it stayed unchanged. The harness reads the ELF as fixture data. Its test host uses no firmware.

[UEFI memory attribute protocol](https://uefi.org/specs/UEFI/2.11/37_Secure_Technologies.html#memory-protection)

[Course contents](index.md) · [Previous lesson · Read a declared hardware timebase](140-read-a-declared-hardware-timebase.md) · [Next lesson · Read a partial permission transition](142-read-a-partial-permission-transition.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/141-order-page-permission-changes.html)
