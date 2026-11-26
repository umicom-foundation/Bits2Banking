<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/143-read-an-exact-efi-elf-pair.md

PURPOSE:
Read an exact EFI and ELF pair

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read an exact EFI and ELF pair

The Umicom Kernel preflight workflow produces two linked artifacts. The EFI application is the diagnostic program the firmware can load. The ELF file is the Kernel entry payload embedded inside it. The current EFI application checks specific prerequisites and returns to firmware. Its manifest records the role `diagnostic-preflight`.

### Read the same pair that the build verified

Open PowerShell. Set `$EfiBuild` to the existing x64 preflight build directory. Stop on any error.

```powershell
$manifest = Join-Path $EfiBuild 'uefi-preflight-pair-Release.json'
$pair = Get-Content -LiteralPath $manifest -Raw | ConvertFrom-Json
$pair.role
$pair.efi | Format-List sha256,bytes,entryRva
$pair.elf | Format-List sha256,bytes,fileOffset,rva
$pair.embeddedPointerRelocationRva
```

A file offset counts bytes from the beginning of a file stored on disk. A relative virtual address, or RVA, counts bytes from the base where the loader places the image. The two values can differ. Use the manifest’s `fileOffset` when thinking about the saved EFI bytes. Use `rva` when following the loader's address calculation.

### Compare two real file identities

Set `$EfiFile` and `$ElfFile` to the files recorded by the checker. Compare sizes and full hashes without modifying either file.

```powershell
((Get-Item -LiteralPath $EfiFile).Length -eq $pair.efi.bytes)
((Get-FileHash -LiteralPath $EfiFile -Algorithm SHA256).Hash -ieq $pair.efi.sha256)
((Get-Item -LiteralPath $ElfFile).Length -eq $pair.elf.bytes)
((Get-FileHash -LiteralPath $ElfFile -Algorithm SHA256).Hash -ieq $pair.elf.sha256)
```

All four comparisons should produce `True`. The Kernel verifier also checks every embedded payload byte and the linker's pointer relocation before it writes the manifest. If an independently rebuilt EFI has a different hash or offset, it needs its own manifest even when it embeds the same ELF. Keep the previous build and evidence available for review.

### Decide what the result establishes

The pair is evidence of which output files were linked together. The `diagnostic-preflight` role tells readers which behavior this build contains. Save a separate firmware observation when a real boot is later authorized and tested.

[Course contents](index.md) · [Previous lesson · Read a partial permission transition](142-read-a-partial-permission-transition.md) · [Next lesson · Admit a verified optical input](144-admit-a-verified-optical-input.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/143-read-an-exact-efi-elf-pair.html)
