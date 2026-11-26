<!--
Umicom Bits2Banking
File: content/contributing/setup-centre/04-verify-a-native-review.md

PURPOSE:
Teach the focused native build and separate command evidence from boot evidence.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Verify a native review

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use a Windows PowerShell terminal with CMake and the MSYS2 UCRT64 GCC and Ninja tools installed. The example selects absolute tool paths. Use your actual Framework checkout. The focused targets build the shared planner test and the console, with no installer launch, VM or media device in this exercise.

1. Configure a fresh practice directory and build the focused targets. Run one command at a time. Stop on a nonzero native exit code.

   ~~~powershell
   $Framework = 'C:/umicom/Umicom-Applications/framework'
   $Tools = 'C:/msys64/ucrt64/bin'
   $Build = Join-Path $env:USERPROFILE ('setup-review-' + [guid]::NewGuid().ToString('N'))
   cmake -S "$Framework/examples/setup_centre" -B $Build -G Ninja "-DCMAKE_C_COMPILER=$Tools/gcc.exe" "-DCMAKE_MAKE_PROGRAM=$Tools/ninja.exe" -DBUILD_TESTING=ON
   cmake --build $Build --target umicom-setup umicom-setup-boot-plan-test
   ctest --test-dir $Build -R '^framework[.]setup_centre[.]boot_plan$' --output-on-failure --no-tests=error
   ~~~

   Expect one selected CTest. Open the [test file](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/setup_centre/test_boot_plan.c) to see the individual C cases behind that result.

2. Ask the new console for the documented Kernel QEMU route and the unavailable Kernel VirtualBox route. Compare each result's exit code immediately after it prints.

   ~~~powershell
   $Setup = Join-Path $Build 'bin/umicom-setup.exe'
   & $Setup boot-plan --product kernel --arch riscv64 --source prebuilt --output qemu
   $LASTEXITCODE
   & $Setup boot-plan --product kernel --arch riscv64 --source prebuilt --output virtualbox
   $LASTEXITCODE
   ~~~

   The first readiness is workflow-documented. The second is not-available and the artifact is None. Both commands expect exit zero because both presentations are valid reviews.

3. Repeat with a malformed request. The Kernel cannot take the Foundation edition.

   ~~~powershell
   & $Setup boot-plan --product kernel --arch riscv64 --edition foundation --source prebuilt --output qemu
   $LASTEXITCODE
   ~~~

   Expect usage output and exit 2. Record all three cases in your notes and keep this command evidence separate from any eventual VM or media test.

If a build cannot find the target, confirm that the checkout contains the planner, its focused test and their build wiring. If CTest reports no matching tests, check the configure option and use ctest --test-dir with the same build folder. If protection software blocks a practice executable, stop and use the paper trace from lesson 1.

[Previous](03-keep-review-and-work-separate.md) · [Workshop](index.md) · [Next · Design and accessibility](05-from-design-to-accessible-ui.md)
