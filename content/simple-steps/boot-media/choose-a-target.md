<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/choose-a-target.md

PURPOSE:
Select an image and virtual machine that match the intended boot path.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 1. Choose the target

On paper or in a notes file, write one line: **project, processor, firmware, medium, expected result**. The same project can have different results for different media.

| If you want to try | Choose | Expect to observe |
| --- | --- | --- |
| Native Kernel system and recovery consoles | Umicom Kernel, RISC-V64, QEMU `virt`, an ELF loaded as firmware | The selected console accepts a command and shuts down |
| Kernel diagnostic on x64 UEFI | Umicom Kernel, x64 UEFI, a diagnostic EFI application on FAT or optical ISO | The firmware runs the preflight and receives its return status |
| Linux-based OS Foundation guest | Umicom OS, x64 or RISC-V, the matching QEMU system emulator, a kernel and initial filesystem bundle | The requested mode reaches its expected boot and shutdown markers |
| OS Foundation from virtual optical media | Umicom OS, x64, reviewed BIOS or UEFI firmware, an optical ISO | Firmware starts GRUB and the selected normal or recovery entry reaches its expected guest result |
| OS Foundation from a virtual USB disk | Umicom OS, x64 UEFI, a raw GPT disk file with a matching EFI loader | Firmware finds the loader via the EFI System Partition and the guest reaches the selected mode |

1. Decide whether you have an executable, a folder of boot files or a complete medium image. An ELF provides machine code and load information. An ISO has an optical filesystem. A raw disk image contains the bytes of a disk and can include a partition table and filesystem.
2. Pick the exact machine. The project’s native Kernel chooses QEMU’s `virt` board for RISC-V64. A standard x64 optical VM exercises a different processor and firmware path. Record the emulator as well as the target CPU.
3. Check the selected boot route. The x64 Kernel preflight demonstrates a firmware check and returns. OS Foundation Live starts an initial RAM filesystem. A physical installer needs a separate install and recovery design.

Record the filename, byte count, reviewed SHA-256, exact build revision and target. If you need a checksum on Windows, PowerShell reads a file without changing it.

~~~powershell
$Image = Read-Host 'Absolute path to the image or executable file'
Get-Item -LiteralPath $Image | Select-Object Name, Length
Get-FileHash -Algorithm SHA256 -LiteralPath $Image
~~~

**Check yourself.** A file renamed from `umicom-system.elf` to `umicom-system.iso` has the same bytes and the same SHA-256. Keep the ELF and choose its documented RISC-V QEMU profile.

[Workshop contents](index.md) · [Boot the Kernel in QEMU](kernel-riscv-console.md) · [QEMU RISC-V system emulator](https://www.qemu.org/docs/master/system/target-riscv.html) · [UEFI media access](https://uefi.org/specs/UEFI/2.11/13_Protocols_Media_Access.html)
