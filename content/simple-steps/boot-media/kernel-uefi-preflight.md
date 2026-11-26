<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/kernel-uefi-preflight.md

PURPOSE:
Build and identify the x64 Kernel ELF and its UEFI preflight application.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 3. Build the Kernel x64 UEFI diagnostic

The repository has a separate x64 boot entry and an EFI diagnostic. The diagnostic examines the embedded ELF and checks a firmware allocation contract, releases that allocation and returns. A complete Kernel handoff and desktop installation are separate work.

1. Open PowerShell with CMake and the matching MSYS2 UCRT64 Ninja installed. Use an LLVM installation with Clang, LLD, llvm-ar and llvm-readobj. Edit the paths below to match your workstation and keep the build directory new.

   ~~~powershell
   $Kernel = 'C:/umicom/umicom-kernel'
   $Tools = 'C:/msys64/ucrt64/bin'
   $LLVM = 'C:/Program Files/LLVM/bin'
   $env:Path = "$LLVM;$Tools;$env:Path"
   $Work = Join-Path $env:USERPROFILE ("umicom-kernel-x64-" + (Get-Date -Format 'yyyyMMdd-HHmmss'))

   cmake -S "$Kernel/targets/x86_64_boot" -B "$Work/elf" -G Ninja "-DCMAKE_MAKE_PROGRAM=$Tools/ninja.exe" "-DCMAKE_C_COMPILER=$LLVM/clang.exe" "-DCMAKE_ASM_COMPILER=$LLVM/clang.exe" "-DCMAKE_AR=$LLVM/llvm-ar.exe" "-DUMICOM_X86_ELF_LINKER=$LLVM/ld.lld.exe" -DCMAKE_BUILD_TYPE=Release
   if ($LASTEXITCODE -ne 0) { throw 'Entry configure failed.' }
   cmake --build "$Work/elf" --target umicom-kernel-x64-entry --parallel 1
   if ($LASTEXITCODE -ne 0) { throw 'Entry build failed.' }

   $Elf = "$Work/elf/umicom-kernel-x64-entry.elf"
   $ElfPin = (Get-FileHash -Algorithm SHA256 -LiteralPath $Elf).Hash
   & "$LLVM/llvm-readobj.exe" --file-headers --program-headers $Elf
   ~~~

   Check `EM_X86_64` and entry address `0x200000`. Record the ELF hash.

2. Use that exact file and digest to link the preflight and produce the paired evidence.

   ~~~powershell
   cmake -S "$Kernel/targets/x86_64_uefi_preflight" -B "$Work/efi" -G Ninja "-DCMAKE_MAKE_PROGRAM=$Tools/ninja.exe" "-DCMAKE_C_COMPILER=$LLVM/clang.exe" "-DCMAKE_ASM_COMPILER=$LLVM/clang.exe" "-DCMAKE_AR=$LLVM/llvm-ar.exe" "-DUMICOM_X86_EFI_LINKER=$LLVM/lld-link.exe" "-DUMICOM_X86_BOOT_ELF=$Elf" "-DUMICOM_X86_BOOT_ELF_SHA256=$ElfPin" -DUMICOM_X86_PREFLIGHT_EVIDENCE=ON "-DUMICOM_X86_COFF_INSPECTOR=$LLVM/llvm-readobj.exe" -DCMAKE_BUILD_TYPE=Release
   if ($LASTEXITCODE -ne 0) { throw 'Preflight configure failed.' }
   cmake --build "$Work/efi" --target umicom-kernel-x64-uefi-preflight-evidence --parallel 1
   if ($LASTEXITCODE -ne 0) { throw 'Preflight evidence failed.' }

   $Efi = "$Work/efi/BOOTX64.EFI"
   $Pair = "$Work/efi/uefi-preflight-pair-Release.json"
   $PairPin = (Get-FileHash -Algorithm SHA256 -LiteralPath $Pair).Hash
   Get-Content -LiteralPath $Pair
   Get-FileHash -Algorithm SHA256 -LiteralPath $Efi
   ~~~

3. Keep the ELF, EFI, manifest and its hash together. The evidence target checks that the loaded ELF bytes in the EFI application match the chosen file. Compare the separately observed hash to the manifest. If your selected ELF changed, make a fresh preflight build against the new hash.

**Check yourself.** You have two distinct executables and a manifest that identifies the pair. This stage has exercised the builders and the offline checks. Firmware execution needs a guest test and its own capture.

[Previous · RISC-V console](kernel-riscv-console.md) · [Next · Create the diagnostic ISO](kernel-diagnostic-iso.md) · [Kernel preflight documentation](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/X86_64_UEFI_PREFLIGHT.md)
