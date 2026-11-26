<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/10-find-a-missing-implementation.md

PURPOSE:
Find the installed component that provides a function named by the linker.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find the installed component behind a function

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A header tells the compiler that a function exists and describes what arguments it takes. The linker connects that call to a compiled implementation. If a compile succeeds and the linker later reports an undefined reference, look up the function name before changing the C code.

1. Find the call to `UmiInputFileRead` in `main.c` and its matching header. The call supplies a path, a byte limit and places for the result pointer and size.
2. In the PowerShell session from the first lesson, use the GNU `nm` tool supplied with the UCRT64 build tools to look for the implementation. A line ending in the function name with type `T` identifies a definition in an archive’s compiled code.

```powershell
nm --defined-only "$kit/lib/libumicom_platform.a" | Select-String 'UmiInputFile(Read|Free)$'
nm --defined-only "$kit/lib/libumicom_output_file.a" | Select-String 'UmiOutputFileCreate$'
```

3. Open `CMakeLists.txt` and compare those two archives with the `Umicom::platform` and `Umicom::output_file` targets. Each advertises the library and any other link requirements its callers need.
4. Rebuild the existing lab and run the input check. If you selected a different SDK to diagnose a missing definition, configure a fresh build folder with that prefix instead.

```powershell
cmake --build $build --parallel 2
ctest --test-dir $build -R '^learning\.venue\.cli\.read$' --output-on-failure --no-tests=error
```

**Check your result.** The first command finds both `UmiInputFileRead` and `UmiInputFileFree`. The second finds `UmiOutputFileCreate`. The read check runs successfully when the program links against the intended SDK components.

[Previous — Reuse the report](09-reuse-the-report-in-a-client.md) · [Course contents](index.md)
