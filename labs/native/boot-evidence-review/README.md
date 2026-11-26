<!--
Umicom Bits2Banking
File: labs/native/boot-evidence-review/README.md

PURPOSE:
Explain the C23 boot-evidence review exercise and how to check its results.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../content/assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../content/assets/branding/umicom.ico)

# Read a boot claim before approving it

A reviewed disk or ISO can be described in one sentence. To claim a successful virtual boot, you need the exact artifact, the firmware used, and one complete capture each for normal and recovery. This C23 exercise uses fictional pins and fixed observations so you can practise that decision without an image, emulator or device.

1. Use a terminal with CMake, Ninja and a compiler that supports C23. For a Windows PowerShell example, choose your GCC path and configure the lab from the Bits2Banking checkout.

   ~~~powershell
   Set-Location 'C:/umicom/Umicom-Bits2Banking'
   $Tools = 'C:/msys64/ucrt64/bin'
   $env:Path = "$Tools;$env:Path"
   $Build = Join-Path $env:USERPROFILE ("boot-evidence-" + (Get-Date -Format 'yyyyMMdd-HHmmss'))
   cmake -S labs/native/boot-evidence-review -B $Build -G Ninja "-DCMAKE_C_COMPILER=$Tools/gcc.exe" "-DCMAKE_MAKE_PROGRAM=$Tools/ninja.exe" -DBUILD_TESTING=ON
   if ($LASTEXITCODE -ne 0) { throw 'Configure failed.' }
   cmake --build $Build
   if ($LASTEXITCODE -ne 0) { throw 'Build failed.' }
   ctest --test-dir $Build --no-tests=error --output-on-failure
   ~~~

   Expect eleven tests covering successful optical and USB evidence, and a separate refusal for each changed observation. On Linux choose your native compiler and omit the `.exe` suffix.

2. Try the same cases directly and read the outcome before moving on.

   ~~~powershell
   $Tool = "$Build/btb-boot-evidence-review.exe"
   & $Tool optical
   $LASTEXITCODE
   & $Tool wrong-image
   $LASTEXITCODE
   ~~~

   The first case reports `Virtual optical boot evidence complete.` and exits zero. The second reports `A boot capture refers to a different image.` and exits one. Other case names are `virtual-usb`, `no-file-review`, `direct-only`, `wrong-firmware`, `no-shutdown`, `process-error`, `repeated-log`, `swapped-modes` and `malformed-pin`. An unknown case exits two.

3. Open `main.c`. Find the record containing the normal and recovery rows. Trace `Review` one check at a time. Change only the recovery firmware in your own practice copy. Predict the first difference, then rebuild and run the case again.

The digest checks in this application compare example strings. For an actual Foundation release, use the image inspector and optical evidence checker on the real artifact and logs. Your lab result belongs with the practice code. Your real VM result belongs with its own image and capture records.

[Step-by-step C exercise](../../../content/simple-steps/boot-media/evidence-lab.md) · [Foundation optical evidence checker](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/optical-boot-qualification.md)
