<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/evidence-lab.md

PURPOSE:
Use a small C23 program to practise what each virtual boot observation can support.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 12. Review the evidence in C

When deciding whether a release has an exercised virtual boot, check the structure first. Then compare the exact image for the normal capture and the recovery capture, the chosen firmware and the outcome of each run. This lab puts the decision into a small C program containing fictional observations.

1. Open `labs/native/boot-evidence-review` in your Bits2Banking checkout and read the [lab setup](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/boot-evidence-review). Use UCRT64 GCC with CMake and Ninja, or corresponding native Linux tools. Run each command separately and stop on a failed configure or build.

   ~~~powershell
   Set-Location 'C:/umicom/Umicom-Bits2Banking'
   $Tools = 'C:/msys64/ucrt64/bin'
   $env:Path = "$Tools;$env:Path"
   $Build = Join-Path $env:USERPROFILE ("boot-evidence-" + (Get-Date -Format 'yyyyMMdd-HHmmss'))
   cmake -S labs/native/boot-evidence-review -B $Build -G Ninja "-DCMAKE_C_COMPILER=$Tools/gcc.exe" "-DCMAKE_MAKE_PROGRAM=$Tools/ninja.exe" -DBUILD_TESTING=ON
   cmake --build $Build
   ctest --test-dir $Build --output-on-failure --no-tests=error
   ~~~

2. Compare two results. The recovery row in `wrong-image` contains the digest of a different ISO. Both rows still claim a successful launch. Predict which check the program refuses, then run it.

   ~~~powershell
   $Tool = "$Build/btb-boot-evidence-review.exe"
   & $Tool optical
   $LASTEXITCODE
   & $Tool wrong-image
   $LASTEXITCODE
   ~~~

   Expect exit zero for the complete virtual optical row and exit one for the mismatched case. Try `direct-only` to see why a different boot route needs separate evidence. Try `no-shutdown` to see the result of an incomplete capture.

3. Find `struct Capture` in `main.c`. It represents the saved observations for one guest. Follow `Review` from its structure check to the comparison of transcript digests. In your own source copy, change one field in the normal or recovery observation, predict the refusal, and run the tests again.

Use the workshop’s linked image and optical tools to evaluate real files and logs. This program consumes practice rows and never opens a disk or starts an emulator.

**Check yourself.** You can explain why a complete log for a different ISO leaves the intended release’s boot unanswered. The same rule applies when one person builds two images at different times.

[Previous · Physical readiness](physical-readiness.md) · [Workshop contents](index.md) · [Full algorithms course](../../courses/learning-algorithms/index.html)
