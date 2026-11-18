<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/22-build-a-small-framework-preview-lab.md

PURPOSE:
Build a small Framework preview lab

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Build a small Framework preview lab

[Course contents](index.md)
A target is a named output managed by a build system. A small target lets you study one service without compiling every application. The supplied framework-preview-revisions lab is a console program. It uses Framework's real reload bookkeeping, has no graphical window, and performs no download or model operation. Its output will make a later GTK preview design easier to reason about.


## Prepare the workspace

Keep learning work in a separate directory. These example paths assume Bits2Banking is at C:\learning\Umicom-Bits2Banking and the primary Framework source is at C:\learning\Umicom-Applications\framework. Substitute your actual paths consistently. PowerShell accepts the commands below. C source belongs in main.c, not at the PowerShell prompt. Do not type the prompt itself.

1. Open the Bits2Banking folder in your editor and locate labs/native/framework-preview-revisions/main.c and CMakeLists.txt.
2. Confirm GCC, CMake and Ninja are installed. On Windows, use the same UCRT64 toolchain for this example and its dependencies.
3. Read main.c once before building. It allocates two bounded objects, calls Framework functions, prints the result and frees both objects.
4. Configure the source-study mode below. It compiles only the production reload service needed by this exercise.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;C:\Program Files\CMake\bin;$env:Path"
gcc --version
cmake --version
ninja --version
Set-Location "C:\learning\Umicom-Bits2Banking"
cmake -S labs/native/framework-preview-revisions -B build/preview-study -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/learning/Umicom-Applications/framework
cmake --build build/preview-study --parallel 2
ctest --test-dir build/preview-study --output-on-failure
~~~

Run each command separately and stop if it fails. Check $LASTEXITCODE immediately after a native command: zero normally means success. CMake configures build rules, Ninja executes the rules, and CTest runs the declared check. A configuration result does not establish compilation or test success. The test expects generation 3 with two acknowledgements and no pending work.


## Use an installed SDK

An SDK provides headers, libraries and package metadata. With a compatible SDK installed at C:\SDKs\Umicom, configure a different build folder using the command below. Leave UMICOM_FRAMEWORK_SOURCE unset. This exercises package discovery rather than compiling the service directly from the checkout.

~~~powershell
cmake -S labs/native/framework-preview-revisions -B build/preview-sdk -G Ninja -DCMAKE_PREFIX_PATH=C:/SDKs/Umicom
~~~

The package must export Umicom::frontend and contain the capture/acknowledge APIs. Missing declarations or unresolved functions can indicate an older SDK or mismatched headers and libraries. Do not hide that by copying a header alone. Source-study success does not qualify an installed SDK. The SDK owner must build, install and validate the matching package.


## Exercise

Find the two free calls. Why are they both reached after an allocation failure? The cleanup label handles null pointers safely and releases any allocation that did succeed. Framework borrows these pointers; the lab retains ownership.


[Previous lesson](21-choose-an-interactive-development-tool.md) · [Next lesson](23-separate-layout-refresh-from-c-rebuilds.md)
