<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/verify-kernel-launch-kit.md

PURPOSE:
Teach learners to verify a prebuilt standalone RISC-V Kernel system and recovery kit.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a prebuilt Kernel launch kit

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use this read-only check before booting a prebuilt standalone Umicom Kernel kit for the RISC-V QEMU `virt,aclint=off` machine. The checker reads files and compares fingerprints. Keep the published kit unchanged while you check it.

## 1. Find the three files

In the folder containing the extracted kit, look for `identity.json`, `umicom-system.elf` and `umicom-recovery.elf` side by side. The JSON file records the expected fingerprints for the two ELF files. An ELF is a file format that can contain compiled code for a particular machine.

In PowerShell, replace the example folder with your own.

~~~powershell
$Kit = 'C:/path/to/extracted-launch-kit'
Get-Item -LiteralPath "$Kit/identity.json", "$Kit/umicom-system.elf", "$Kit/umicom-recovery.elf"
~~~

Expect three entries. If a file is missing, check that you selected the extracted kit folder and received the complete kit.

## 2. Get the published fingerprint

Find the 64 hexadecimal characters labelled as the SHA-256 fingerprint of `identity.json` in a trusted publisher record separate from the kit files. The publisher must provide this identity before you can use this workflow. Copy it into PowerShell when prompted.

~~~powershell
$ExpectedSha256 = Read-Host 'Paste the published identity.json SHA-256'
$Kernel = 'C:/path/to/trusted/umicom-kernel'
$IdentityChecker = Join-Path $Kernel 'cmake/QualificationEvidence.cmake'
Get-Item -LiteralPath $IdentityChecker
~~~

Replace the example Kernel path with the checkout you trust and confirm that its checker file appears. A fingerprint calculated from your downloaded receipt cannot establish which receipt the publisher expected.

## 3. Run the checker

~~~powershell
cmake -DMODE=verify-launch-kit "-DKIT=$Kit" "-DEXPECTED_IDENTITY_SHA256=$ExpectedSha256" -P $IdentityChecker
$LASTEXITCODE
~~~

Expect `RISC-V Kernel launch kit fingerprints agree for system and recovery` and exit status `0`. The checker can refuse an unexpected receipt, an ELF that differs from the receipt, or a kit for a different machine or ABI. If it refuses, keep the output and obtain the correct kit or publisher fingerprint before opening QEMU.

## 4. Follow the console guide

After the check succeeds, set the image folder and the path to your installed QEMU executable for the [RISC-V console guide](kernel-riscv-console.md). Replace the example QEMU path if you installed it elsewhere.

~~~powershell
$Images = $Kit
$Qemu = 'C:/msys64/ucrt64/bin/qemu-system-riscv64.exe'
Get-Item -LiteralPath $Qemu
~~~

In that guide, use **Run and compare the consoles**. The fingerprint check establishes agreement with the published file identities. A successful console run supplies the separate evidence that the guest started.

[Choose a Kernel or OS target](choose-a-target.md) · [Boot media wiki](../../wiki/boot-media.md)
