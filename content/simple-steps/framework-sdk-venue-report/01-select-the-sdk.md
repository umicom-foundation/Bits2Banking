<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/01-select-the-sdk.md

PURPOSE:
Connect an independent C23 consumer to the installed Framework package.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Select an installed SDK and build the venue project

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An installed SDK supplies the headers and libraries that the report program uses. Start from your Bits2Banking checkout and choose a Framework SDK built for the same platform and compiler runtime.

1. Check that the [MSYS2 C tools](../toolchain.md) are available on Windows. Look for an installed package file at `lib/cmake/UmicomFramework/UmicomFrameworkConfig.cmake` inside your SDK.
2. In PowerShell use the commands below. Replace the SDK location with the prefix you verified. A prefix is the folder that contains the SDK’s `lib` and `include` folders. Run each command separately. Stop if it fails.

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
$kit = 'C:/umicom/installed/framework'
$source = (Resolve-Path '.\labs\framework\venue-shift-report').Path
$build = Join-Path $env:TEMP ('btb-venue-build-' + [guid]::NewGuid().ToString('N'))
Get-Item "$kit/lib/cmake/UmicomFramework/UmicomFrameworkConfig.cmake"
cmake -S $source -B $build -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe "-DCMAKE_PREFIX_PATH=$kit;C:/msys64/ucrt64" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build $build --parallel 2
Get-Item "$build\btb-venue-report.exe"
```

3. Read the project’s `CMakeLists.txt`. The package lookup requests `base` for CSV, number and digest functions, `platform` for bounded file reads and `output_file` for new receipts. These imported targets supply their own compiler and linker requirements.
4. If configure cannot find the package, check the prefix and choose a fresh consumer build folder after changing it. If it finds the package and reports a missing component, check that the chosen SDK provides all three components. Follow the package diagnostic for missing system dependencies. The package configuration can look for GTK and other supporting libraries when the installed SDK was built with those features.

**Check your result.** The build produces `btb-venue-report.exe` in the new build folder. Keep the current PowerShell session for the next steps.

[Installed package selection in CMake](https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html)

[Course contents](index.md) · [Next — Check the input shape](02-check-the-input-shape.md)
