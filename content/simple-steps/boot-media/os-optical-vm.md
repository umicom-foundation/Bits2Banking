<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/os-optical-vm.md

PURPOSE:
Exercise the reviewed ISO in an isolated x64 optical virtual machine.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 8. Check a virtual optical boot

Choose one firmware mode that the reviewed ISO’s El Torito catalogue supports. The ISO’s digest links the source image to any later run. Record normal and recovery as separate guest runs.

1. Record the ISO name, expected SHA-256, emulator version and selected firmware. For a normal Windows user, inspect the artifact with the documented media CLI and observe its hash without changing it.

   ~~~powershell
   $Media = Read-Host 'Absolute path to the installed media CLI'
   $Iso = Read-Host 'Absolute path to the reviewed UmicomOS.iso'
   & $Media inspect-optical --image $Iso
   if ($LASTEXITCODE -ne 0) { throw 'The image inspection failed.' }
   Get-FileHash -Algorithm SHA256 -LiteralPath $Iso
   ~~~

   Check the observed digest against the independent review pin. For BIOS, look for a reported BIOS load range. For UEFI, look for an EFI load range. Choose a mode whose range is present.

2. On an x64 VirtualBox host, choose **New**, give the guest a name, choose a 64-bit Linux profile and skip unattended installation if offered. Use no virtual hard disk for the optical live smoke check. Disable networking, host sharing and device pass-through. Under **Storage**, attach the exact ISO as a virtual optical drive. Set the firmware to match the catalogue entry you plan to exercise.

3. Enable the first serial port as COM1 under **Serial Ports**. For a quick startup observation, choose **Raw File** and set an unused log destination. Choose **Umicom OS normal (diskless foundation)** at the menu. In a separate guest run and log, choose **Umicom OS recovery (diskless foundation)**. Look for `UMICOM_INIT` in the first and a requested recovery mode in the second.

4. For full evidence, arrange a two-way serial connection before either run. A VirtualBox raw-file port captures output only. At the guest prompt type `poweroff`. Keep each complete capture through `UMICOM_SHUTDOWN`, record the completed emulator outcome when available, and follow the [native optical evidence checker](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/optical-boot-qualification.md). Preserve the VM settings, ISO hash, capture hash and firmware choice. Record a truncated log or missing process outcome as incomplete.

If firmware reports no medium, check optical attachment, boot order and the catalogue entry. Changing the firmware creates a new test combination, so use a new run record.

**Check yourself.** The firmware observation attaches the exact ISO as virtual optical media. Your two results identify the mode they actually reached. A quick prompt observation is only one stage of the full evidence check.

[Previous · Create the optical image](os-optical-iso.md) · [Next · Prepare a UEFI disk file](os-uefi-disk-image.md) · [VirtualBox VM configuration](https://docs.oracle.com/en/virtualization/virtualbox/7.2/user/create-vm.html) · [VirtualBox storage](https://docs.oracle.com/en/virtualization/virtualbox/7.2/user/storage.html)
