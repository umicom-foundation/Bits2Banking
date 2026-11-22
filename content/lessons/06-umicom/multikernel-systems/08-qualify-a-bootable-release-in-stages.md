<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/08-qualify-a-bootable-release-in-stages.md

PURPOSE:
Qualify a bootable release in stages.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Qualify a bootable release in stages

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

[Course contents](index.md) · [Previous lesson](07-check-a-core-owned-memory-range.md)

A boot begins when firmware transfers control to a loader or the first system program. An operating system reaches a useful state when its selected kernel, services and console work. An installer writes that system to a chosen storage device. A separate restart after removing the starting media verifies that the installed system can boot on its own.

An **ISO** is an optical disc image. A **raw USB image** contains bytes for a disk. A publisher may qualify one file for both uses. **UEFI** firmware can look for a default loader name for its processor architecture on removable media. Image format, architecture, drivers, and startup behavior each need evidence.

## Build a release evidence worksheet

1. Choose one target and write down the exact processor architecture, firmware mode, image format and expected first useful screen or command. Example A is an Umicom Kernel RISC-V emulator guest. Example B is an x86-64 Umicom OS Foundation diskless Linux boot. Choose separate rows for normal and recovery.
2. Identify every boot component with its release version and digest. In PowerShell, substitute the path to the reviewed file in the command below. Compare the resulting SHA-256 value with the trusted release record. A matching digest establishes file identity.
3. Describe what you expect the guest to show after startup. Record the emulator version, guest image digest, exact readiness marker and shutdown outcome when you perform the boot. Avoid handing a guest a physical disk when a diskless run or a disposable virtual disk suffices.
4. For a future installer, add an independent storage trial with a disposable blank virtual disk. Confirm the target by identity and capacity, record the proposed changes, and boot again after removing the starting image. A real computer adds firmware, drivers, recovery and hardware qualification. Record unsupported or missing stages as pending.

```powershell
Get-FileHash -Algorithm SHA256 -LiteralPath 'C:/Images/reviewed-release.iso'
```

## Practice

Explain what each observation establishes. An ELF executable loaded by the QEMU RISC-V virt model shows one virtual-board path. A disc-image structure check shows that an expected structure exists. A restart from a freshly installed virtual disk provides separate evidence that the disk can start independently. No install or media write is required to complete the worksheet.

## Apply it to Umicom

Use this worksheet for Umicom Kernel and Umicom OS release tests. Keep the Linux Foundation and native Kernel rows separate so an observation from one does not become a release claim about the other. Use the same reporting distinctions when Umicom Automated Testing records a build, boot, service check, or recovery step.

[UEFI removable media boot behavior](https://uefi.org/specs/UEFI/2.11/03_Boot_Manager.html) · [QEMU RISC-V virt model](https://www.qemu.org/docs/master/system/riscv/virt.html) · [Compiler lesson on architectures and boot media](../../../courses/building-a-compiler-in-c/lessons/08-architectures-and-boot-media.html)


[Next lesson on firmware inventory and hart entry](09-separate-firmware-inventory-from-hart-entry.md).
