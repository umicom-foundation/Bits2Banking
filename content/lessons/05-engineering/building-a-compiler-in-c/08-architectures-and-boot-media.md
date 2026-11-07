# Understand architectures, firmware and boot media

A computer starts by running **firmware**: software supplied for that machine which prepares hardware and finds the next program to load. A **bootloader** prepares an operating-system kernel and transfers control to it. The kernel then takes responsibility for memory, interrupts and devices.

## Architecture is only one compatibility condition

An **instruction-set architecture** defines the machine instructions a processor understands. RISC-V64, x86-64 and ARM64 are different instruction sets. ARM64 is also called AArch64. Supporting one does not automatically support the others, nor every board using the same instruction set.

Machines can also differ in firmware, memory layout, interrupt controller, timer, display, keyboard and storage devices. A kernel that prints to a virtual serial port may still lack a driver for a laptop keyboard or storage controller. That is why a supported target names the processor, machine profile, firmware and required devices.

## Read the current Umicom boundaries

| Project | What to inspect | Limit |
| --- | --- | --- |
| Umicom Kernel | `arch/riscv64`, `platform/qemu-riscv64`, `CMakePresets.json` | The current native port is RISC-V64 |
| Umicom OS | `image/configs/umicom_riscv64_defconfig` and `umicom_x86_64_defconfig` | These are Linux-based image recipes, not ports of Umicom Kernel |
| Umicom Framework | `src/vm_manager/boot_targets.c` | Planning an emulator command does not implement the guest kernel |

## A file, a disk image and an optical image

An ELF file contains native program data and metadata for a loader. A raw disk image represents the bytes of a disk, potentially including partition tables, filesystems and a bootloader. An ISO represents an optical-disc filesystem; booting it also needs the appropriate boot information. Changing a filename from `.elf` to `.iso` does not perform those transformations.

A USB stick is a storage device. To boot from it, its contents must match a firmware-supported boot arrangement. The UEFI removable-media convention uses architecture-specific loader names, such as `EFI/BOOT/BOOTX64.EFI` for x86-64 and `EFI/BOOT/BOOTAA64.EFI` for ARM64. The loader must really contain code for that architecture; its filename alone is not sufficient.

## Choose evidence appropriate to the claim

1. Check that the target builds.
2. Observe an actual emulator boot with the intended firmware and image.
3. Exercise normal startup, recovery, input, storage and shutdown.
4. Only then qualify a named physical machine and record its hardware and firmware details.

Secure Boot adds a signature-trust requirement. A successful unsigned emulator boot does not establish that a machine configured for Secure Boot will accept the image. No physical disk-writing exercise is required in this lesson.

## Exercise

A virtual ARM64 board boots successfully. Can the same result qualify every ARM64 laptop?

<details>

<summary>Explanation</summary>

No. The instruction set may match while firmware and devices differ. Keep the virtual-board result, then qualify each supported hardware profile separately. The current source does not provide a universal Umicom Kernel USB or CD image.

</details>

## Find the implementation

Open `umicom-kernel/CMakePresets.json` in your Umicom source collection. Read the named functions alongside this lesson. Source reading and the expected outcomes below are not evidence of an executed build.

---

[Read this lesson in HTML](../../../courses/building-a-compiler-in-c/lessons/08-architectures-and-boot-media.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Run the interpreter as a native Kernel program](07-a-native-kernel-program.md)

[Next: Design a small programming language in C](09-designing-a-language.md)
