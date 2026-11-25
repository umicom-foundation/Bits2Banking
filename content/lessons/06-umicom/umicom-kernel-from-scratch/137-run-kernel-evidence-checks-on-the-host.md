<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/137-run-kernel-evidence-checks-on-the-host.md

PURPOSE:
Run Kernel evidence checks on the host

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Run Kernel evidence checks on the host

[Previous lesson](136-review-one-kernel-elf-from-a-partial-build.md) · [Course index](index.md) · [Next lesson · Match ELF files to a finished Kernel build](138-match-elf-files-to-a-finished-kernel-build.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/137-run-kernel-evidence-checks-on-the-host.html)

The **host** is the computer running your tools. A **guest** is the system started inside an emulator. A host test can check that a boot report contains the expected records even when you have no emulator available. In this lesson, you will run tests that use synthetic files and transcripts, then identify the evidence their results provide.

## Find the tests first

1. Use a Kernel build directory already configured with `BUILD_TESTING=ON`. Set `$Build` to that directory. The example uses a separate build folder that you can replace with yours.

   ```powershell
   $Build = "C:/umicom/umicom-kernel/build/riscv64-clang"
   $EvidenceCases = '^kernel\.(evidence\.|boot_handoff\.records\.)'
   ctest --test-dir $Build -N -R $EvidenceCases
   if ($LASTEXITCODE -ne 0) { throw 'Could not list the selected Kernel tests.' }
   ```

2. Read the result before continuing. In the configuration used in this lesson, it lists **43 tests**. The 24 `kernel.evidence.*` tests check identity records against controlled source and image files. The 19 `kernel.boot_handoff.records.*` tests check sample startup and recovery messages. On a different Kernel revision, your recorded number may change.

3. To see exactly which programs the test runner would use, ask it for structured output.

   ```powershell
   $Listing = ctest --test-dir $Build --show-only=json-v1 -R $EvidenceCases
   if ($LASTEXITCODE -ne 0) { throw 'Could not read the Kernel test commands.' }
   ($Listing -join "`n" | ConvertFrom-Json).tests |
       Select-Object name, @{Name='Program'; Expression={$_.command[0]}}
   ```

   The selected fixtures use CMake on the host to evaluate files or strings. In the configuration checked for this lesson, they have no required fixtures or test dependencies. A required fixture is an extra action the runner can add to prepare for a test.

## Run and read the result

4. Run the selected cases and retain the result in a JUnit file. JUnit is a structured test report, so you can open it in another test tool or compare it with a later run.

   ```powershell
   $Report = Join-Path (Resolve-Path $Build) 'kernel-host-evidence.xml'
   ctest --test-dir $Build -R $EvidenceCases --parallel 2 --output-on-failure --no-tests=error --output-junit $Report
   if ($LASTEXITCODE -ne 0) { throw 'A Kernel host evidence check failed.' }
   ```

   In the recorded exercise, the summary was `100% tests passed out of 43` and the structured report recorded zero failures and zero skips. One test intentionally supplied conflicting boot mode records. Its pass means the checker correctly refused that input.

5. Record the scope with the result. **43 host evidence checks passed.** The test list, command, and report explain what was exercised. Booting a real Kernel image, detecting physical hardware, and completing an installation each require separate evidence. The separately named `kernel.qualification.identity` also has its own preparation requirement. Selecting only the two prefixes above keeps those additional actions out of this exercise.

## If the result differs

- If the directory or tests are missing, check the configured build path and `BUILD_TESTING`. An empty test selection means there is no evidence for this exercise.
- If a test fails, keep its complete name and output. First ask whether it supplied a synthetic source file, an image digest, or a boot transcript. Open the corresponding test source before changing the Kernel, so you can distinguish a checker defect from a correctly refused sample.
- If you need evidence about an actual linked image, use the preceding lesson to inspect its executable header. Then use an approved guest or hardware workflow to collect a fresh real boot transcript.
