# Know which bytes you booted

A source commit is useful evidence, but a boot run consumes built bytes. The native image workflow hashes its captured input manifest and checks the image bundle. The QEMU executable and selected firmware are further inputs.

## Default and explicit firmware

The compatible boot API can use QEMU's packaged RISC-V default. That does not identify an exact OpenSBI artifact. The explicit API `UmiOsImageBootWithFirmware` instead takes an absolute firmware path, SHA-256 digest and byte count. It verifies that pin, copies the accepted bytes into a new result directory, passes the captured path to QEMU and checks the capture again after execution.

The CLI accepts `boot --firmware ABS --sha256 SHA256 --bytes NUMBER` alongside its existing bundle, QEMU, mode and result arguments. Supply all three fields. `firmware --file ABS --sha256 SHA256 --bytes NUMBER` checks the pin without launching a process.

## Inspect a declaration before capturing source

The native command `umicom-os-image profile --file ABSOLUTE_PROFILE_PATH` prints declared source names and version pins without creating build output. Its profile-text digest identifies the declaration, while preparation hashes a manifest of the actual captured source bytes. Edit a comment in one listed source file: the declaration can remain unchanged even though a new captured-input identity is required.

Read `include/umicom/os_image/profile.h` and `src/os_image/profile.c` in Framework. Inspection and preparation use the same bounded grammar. A valid profile is not evidence that its sources exist or that their licences have been reviewed.

## Exercise

1. Read `include/umicom/os_image/boot_firmware.h` in Framework.
2. Find the pre-output and post-execution checks in `src/os_image/boot.c`.
3. Explain why the captured file is used rather than reopening the original source path for execution.
4. List what a matching digest does not establish: publisher authenticity, licence approval, compatibility or a secure boot chain.

The first explicit-firmware contract is for RISC-V QEMU `virt` direct-kernel runs. It does not certify x86 BIOS/UEFI, physical hardware or an installer. Obtain a reviewed compatible firmware artifact before attempting a real boot; this lesson does not supply an approved production image.

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#os) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-os-from-scratch/lessons/05-image-and-firmware-identity.html) · [Learning sequence](../../../start/learning-sequence.md)
