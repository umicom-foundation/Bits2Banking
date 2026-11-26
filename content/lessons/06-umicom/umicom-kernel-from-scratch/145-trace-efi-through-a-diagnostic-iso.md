<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/145-trace-efi-through-a-diagnostic-iso.md

PURPOSE:
Trace an EFI file through a diagnostic ISO

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Trace an EFI file through a diagnostic ISO

The file-only native producer takes the staged `BOOTX64.EFI` and writes a small FAT image and an optical ISO. The EFI application is stored at `EFI/BOOT/BOOTX64.EFI` inside the FAT image. An El Torito catalogue entry tells firmware where it can find that FAT image within the ISO.

### Draw the path taken by the bytes

```text
diagnostic EFI + separately verified manifest
    -> verified staging directory holding BOOTX64.EFI
    -> FAT image holding EFI/BOOT/BOOTX64.EFI
    -> optical ISO with a catalogue pointing to that FAT image
```

Build the existing optical producer in the same `$StageBuild` directory as the previous lesson. The following program operates on files in the staging directory. Use a fresh directory for a production exercise and leave USB drives and discs outside this exercise.

```powershell
cmake --build "$StageBuild" --target umicom-kernel-x64-preflight-optical --parallel 1
Push-Location (Join-Path $StageBuild 'verified-preflight-input')
try {
    & "$StageBuild/umicom-kernel-x64-preflight-optical.exe"
    if ($LASTEXITCODE -ne 0) { throw 'The file-only producer failed.' }
    Get-ChildItem -File | Select-Object Name,Length
} finally {
    Pop-Location
}
```

The command should create an ordinary FAT image and ISO alongside the staged input. Keep the earlier manifest and the reported file names. Record separate SHA-256 hashes for the staged EFI, the FAT file and the complete ISO. Each file has a distinct role and byte count.

### Explain the independent comparisons

An ISO catalogue check locates the referenced image. A byte comparison against the separate FAT file checks that its exact bytes appear in the ISO at that location. A FAT directory check finds the EFI file inside its expected directory chain and compares its content to the staged EFI. A readable outer ISO header by itself leaves the two inner comparisons unverified.

As a review exercise, explain what each of these checks would observe if the producer put the EFI under another path while keeping the ISO and FAT structures valid. The original EFI digest can still be correct for its input. The directory comparison supplies separate evidence that firmware can find the expected filename. Boot and installation outcomes require their own qualification.

[Course contents](index.md) · [Previous lesson · Admit a verified optical input](144-admit-a-verified-optical-input.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/145-trace-efi-through-a-diagnostic-iso.html)
