<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/47-interpret-uefi-boot-catalogue-counts.md

PURPOSE:
Interpret UEFI boot catalogue counts

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->



# Interpret UEFI boot catalogue counts

## Prepare the EFI comparison

Run the efi-zero and efi-one scenarios after building the installed ISO lab. Both should return status 0 with ISO9660, El Torito and EFI flags set; BIOS should be zero. These are structural observations over synthetic memory. The fixture has no usable EFI filesystem or executable firmware loader.

An El Torito catalogue identifies a platform in its validation entry and may identify other platforms in section headers. The supported profiles here are BIOS platform 0 and EFI platform 0xef, both using no-emulation entries. A section can therefore add EFI support alongside a BIOS default entry.

## Zero does not always mean empty

UEFI specifies a special interpretation for no-emulation EFI boot entries: a sector count of zero or one means the image continues from its start to the end of the medium. Apply that rule only after identifying the EFI platform. A BIOS entry with zero load count remains invalid in this service.

For the lab, the source has 49152 bytes and the EFI image starts at byte 40960. A zero or one count therefore describes the remaining 8192 bytes. Treating zero as an empty load rejects this representation; treating one as exactly 512 bytes misreads its EFI meaning.

~~~c
uint64_t load = (platform == 0xefU && sectors <= 1U)
    ? bytes - start
    : (uint64_t)sectors * 512U;
/* Establish start < bytes before evaluating bytes - start. */
~~~

## Validation is more than finding a marker

A catalogue validation entry carries an identifier, signature and 16-bit checksum. The checksum covers that validation record, not the whole ISO. Its presence does not authenticate a publisher. After checking it, the parser still has to validate each supported boot entry and any bounded section counts.

The shared implementation rejects an entry whose start is at or beyond the source end. It also rejects a non-special count that would load beyond the source. It reports unsupported emulation and platforms as unavailable. No parser flag establishes that the referenced bytes form an EFI system partition that firmware can use.

## Compare independent failure cases

Run bios-zero and compare it with efi-zero. The count is the same, but the platform changes the contract. Next read the Framework hybrid regression case: its default BIOS entry remains present while an EFI section uses zero. Explain why checking only the default entry would miss part of that catalogue.

Add a case whose EFI start lies at the end of the source. Expect a parse error even with the special zero count: there is no remaining image. Keep checksum mutation, range mutation and unsupported-platform mutation in separate tests so a failure identifies the rule being exercised.

## Use the specification without claiming a boot

UEFI 2.11 section 13.3 describes EFI images on optical media and the zero/one count convention. Read that section alongside the code. The service implements a limited inspection profile; a real qualification must also establish the filesystem, loader architecture, firmware mode and actual startup result.

If your synthetic test disagrees with the expected result, inspect the platform byte, count field and checksum. If a real image returns unavailable, preserve it and review its profile. Do not change its catalogue merely to force this learning client to accept it.

[UEFI 2.11 specification, section 13.3](https://uefi.org/sites/default/files/resources/UEFI_Spec_Final_2.11.pdf)

[Installed SDK lab and commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-iso-inspection/README.md) · [Course contents](../../../courses/umicom-os-from-scratch/index.html)

[Written contents](index.md) · [Previous lesson](46-decode-optical-records-and-byte-order.md) · [Next lesson](48-qualify-produced-images-in-stages.md)

<!-- Repository laboratory sources live outside the published content root.
Public repository links replace the former local-only routes, retained here for review:
../../../../labs/native/framework-iso-inspection/README.md
Offline source files remain available in their listed repository/learning-pack locations. -->
