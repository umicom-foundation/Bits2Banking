<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/os-uefi-disk-image.md

PURPOSE:
Create and inspect a file-backed x64 UEFI Foundation disk candidate.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 9. Make an OS UEFI disk-image file

A GPT disk image contains a partition map. An EFI System Partition is a FAT filesystem on that disk where firmware can locate a boot application. This lesson creates a raw file that can be attached to a virtual machine as a disk. It leaves physical disks untouched.

1. Use the [reviewed x64 Foundation bundle](os-foundation-bundle.md), the [native Setup Centre console](os-optical-iso.md), and a native Linux build of the [release inspector](https://github.com/umicom-foundation/umicom-os/blob/main/tools/release-inspector/README.md). Obtain a trusted x64 GRUB EFI application configured to open `/boot/grub/grub.cfg` on the partition it was loaded from. Use the recorded expected digest of that file and of your `image.umi`, separately from the inputs you will pass to the packer.

2. In Linux or WSL, check the prerequisites in the [live UEFI image workflow](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/live-uefi-drive-image.md). Choose a new output directory. Keep the bundle and loader stable for the duration of the run. Enter both SHA-256 values in lowercase.

   ~~~bash
   set -eu
   read -r -p 'Absolute release inspector path: ' PE_TOOL
   read -r -p 'Reviewed Foundation image.umi SHA-256 (lowercase): ' BUNDLE_SHA256
   read -r -p 'Absolute path to the reviewed x64 EFI loader: ' EFI
   read -r -p 'Reviewed EFI loader SHA-256 (lowercase): ' EFI_SHA256
   OUT="$RUN/live-uefi-disk"
   bash "$OS/tools/boot-media/prepare-live-uefi-image.sh" \
     "$TOOL" "$SETUP" "$PE_TOOL" "$RUN/bundle" "$BUNDLE_SHA256" \
     "$EFI" "$EFI_SHA256" "$OUT"
   ~~~

   The packer builds a file-backed FAT filesystem, places it into a GPT image, reads the expected files back through the partition offset, and stores observations in `$OUT`.

3. Read the file receipt and the checked payload list. Confirm the output digest against the receipt.

   ~~~bash
   cat "$OUT/result.umi" "$OUT/payload-matches.txt"
   sha256sum "$OUT/UmicomOS-UEFI.img"
   ~~~

   Expect `UMICOM_X64_LIVE_UEFI_IMAGE 1`, `file-review=complete` and `firmware-boot=not-run`. Read the four payload matches. The x64 firmware fallback executable belongs at `EFI/BOOT/BOOTX64.EFI` on the partition. The remaining files are the kernel, initial filesystem and loader menu.

4. If your selected x64 UEFI VM setup supports presenting a raw image through a virtual USB controller, use a read-only attachment of this exact file. Keep the virtual firmware configuration, image digest, boot mode and serial capture with that check. A virtual optical drive uses a different path and must be tested with the optical ISO.

If the tool stops, read the last stage and corresponding log before choosing a new output directory. A missing `result.umi` leaves the file check incomplete.

**Check yourself.** This step gives you a reviewed disk-image file and its payload observations. Firmware acceptance, Secure Boot, persistent storage and installing onto a physical disk each need their own evidence.

[Previous · Optical VM boot](os-optical-vm.md) · [Next · Rehearse a verified transfer](inspect-and-copy.md) · [UEFI removable-media files](https://uefi.org/specs/UEFI/2.11/13_Protocols_Media_Access.html)
