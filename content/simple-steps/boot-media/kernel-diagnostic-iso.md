<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/kernel-diagnostic-iso.md

PURPOSE:
Create file-backed FAT and optical diagnostic images from the exact verified EFI application.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 4. Create the Kernel diagnostic ISO

Use the `$Kernel`, `$Tools`, `$Work`, `$Efi`, `$Pair` and `$PairPin` values from the [x64 diagnostic lesson](kernel-uefi-preflight.md). This step creates ordinary files.

1. Configure the hosted producer and register its tests against the exact EFI. Keep the independent manifest digest and EFI digest together.

   ~~~powershell
   $Optical = "$Work/optical"
   $EfiPin = (Get-FileHash -Algorithm SHA256 -LiteralPath $Efi).Hash
   cmake -S "$Kernel/tools/x64-uefi-preflight-optical" -B $Optical -G Ninja "-DCMAKE_MAKE_PROGRAM=$Tools/ninja.exe" "-DCMAKE_C_COMPILER=$Tools/gcc.exe" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON -DUMICOM_X64_OPTICAL_VERIFIED_INPUT=ON "-DUMICOM_X64_OPTICAL_PAIR_MANIFEST=$Pair" "-DUMICOM_X64_OPTICAL_PAIR_SHA256=$PairPin" "-DUMICOM_X64_OPTICAL_PAIR_EFI=$Efi" "-DUMICOM_TEST_PREFLIGHT=$Efi" "-DUMICOM_TEST_PREFLIGHT_SHA256=$EfiPin"
   if ($LASTEXITCODE -ne 0) { throw 'Optical producer configure failed.' }
   cmake --build $Optical --target umicom-kernel-x64-preflight-optical-verified-input umicom-kernel-x64-preflight-optical --parallel 1
   if ($LASTEXITCODE -ne 0) { throw 'Optical producer build or input staging failed.' }
   ctest --test-dir $Optical -R '^kernel[.]x64_preflight_optical[.]' --output-on-failure --no-tests=error
   if ($LASTEXITCODE -ne 0) { throw 'A file-only producer check failed.' }
   ~~~

   Look for checks of fresh and reproducible output, existing destinations and refused inputs.

2. Enter the verified staging directory and run the producer there.

   ~~~powershell
   $Stage = "$Optical/verified-preflight-input"
   Get-FileHash -Algorithm SHA256 -LiteralPath "$Stage/BOOTX64.EFI"
   Push-Location $Stage
   try {
       & "$Optical/umicom-kernel-x64-preflight-optical.exe"
       if ($LASTEXITCODE -ne 0) { throw 'Diagnostic image production failed.' }
   } finally {
       Pop-Location
   }
   Get-Item -LiteralPath "$Stage/umicom-x64-preflight-esp.img", "$Stage/umicom-kernel-x64-uefi-preflight.iso" | Select-Object Name, Length
   Get-FileHash -Algorithm SHA256 -LiteralPath "$Stage/umicom-x64-preflight-esp.img", "$Stage/umicom-kernel-x64-uefi-preflight.iso"
   ~~~

3. Record the expected sizes of 4,194,304 bytes for the FAT image and 4,241,408 for the ISO. The EFI application is inside the FAT image at `EFI/BOOT/BOOTX64.EFI`. The ISO catalogue points to the FAT image. Different artefacts have different hashes.

If the producer refuses an occupied output, preserve that run and configure a new output tree before trying again. If it rejects the input digest, identify the actual EFI and manifest. Keep the digest from independent evidence rather than recomputing an expected value just to make an unknown file pass.

**Check yourself.** The ISO gives x64 UEFI firmware a diagnostic application to load. It is still an optical diagnostic. A verified firmware run, physical device and full Kernel handoff each need separate evidence.

[Previous · Build the x64 diagnostic](kernel-uefi-preflight.md) · [Next · Build an OS Foundation bundle](os-foundation-bundle.md) · [Full course lesson](../../lessons/06-umicom/umicom-kernel-from-scratch/145-trace-efi-through-a-diagnostic-iso.md) · [UEFI media access](https://uefi.org/specs/UEFI/2.11/13_Protocols_Media_Access.html)
