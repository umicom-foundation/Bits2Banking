<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/144-admit-a-verified-optical-input.md

PURPOSE:
Admit a verified optical input

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Admit a verified optical input

The file-only optical producer opens `BOOTX64.EFI` in its current directory. A verified staging target lets you prepare that directory with an EFI file whose hash matches the selected diagnostic manifest. It also compares the exact manifest bytes to the pin you saved with the producer evidence.

### Configure one fresh staging directory

Set `$Kernel` to your Umicom Kernel source path, `$StageBuild` to a new writable build directory, `$Manifest` and `$EfiFile` to the previously verified paths, and `$ManifestPin` to the saved 64-digit SHA-256 string. Keep a trusted copy of the pin with the earlier evidence. Recomputing the pin from an unexplained replacement would discard that earlier comparison.

```powershell
cmake -S "$Kernel/tools/x64-uefi-preflight-optical" -B "$StageBuild" -G Ninja `
  -DUMICOM_X64_OPTICAL_VERIFIED_INPUT=ON `
  "-DUMICOM_X64_OPTICAL_PAIR_MANIFEST=$Manifest" `
  "-DUMICOM_X64_OPTICAL_PAIR_SHA256=$ManifestPin" `
  "-DUMICOM_X64_OPTICAL_PAIR_EFI=$EfiFile"
cmake --build "$StageBuild" --target umicom-kernel-x64-preflight-optical-verified-input
```

Use the C compiler and Ninja settings from the preflight guide for your host. Stop before the build if configuration reports an error. This explicit target prepares an ordinary file in the build directory.

### Check what was staged

```powershell
$staged = Join-Path $StageBuild 'verified-preflight-input/BOOTX64.EFI'
$pair = Get-Content -LiteralPath $Manifest -Raw | ConvertFrom-Json
(Get-FileHash -LiteralPath $staged -Algorithm SHA256).Hash -ieq $pair.efi.sha256
```

Expect `True`. Run the staging target again with the same inputs. The existing matching staged file remains usable. If a previously staged file has different bytes, keep the directory for review and configure a fresh one. The verified target refuses to replace the conflict.

### Predict refusals

Write down which boundary would fail for a different manifest pin, a valid manifest with the wrong role, or a selected EFI file with another digest. The first checks the saved report identity. The second checks the allowed purpose. The third checks the selected bytes. Keeping these checks separate makes the first failure easier to diagnose.

[Course contents](index.md) · [Previous lesson · Read an exact EFI and ELF pair](143-read-an-exact-efi-elf-pair.md) · [Next lesson · Trace an EFI file through a diagnostic ISO](145-trace-efi-through-a-diagnostic-iso.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/144-admit-a-verified-optical-input.html)
