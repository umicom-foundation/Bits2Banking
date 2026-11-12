<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/56-qualify-an-installed-image-client.md

PURPOSE:
Teach qualify an installed image client through the installed Framework GPT service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Qualify an installed image client

[Course contents](index.md) · [Previous lesson](55-distinguish-checksums-from-trust.md)

[Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/CMakeLists.txt) · [Build and run the lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/README.md) · [Qualification guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/QUALIFICATION.md)

Editing Framework source does not update a program that links an older installed library. This final lesson checks the installed package boundary before interpreting the lab’s results. A useful qualification record identifies the source, producer build, installed SDK and client build separately.

## Prepare the producer and client

Install a compatible Framework SDK that exports Umicom::gpt_image and the public image_inspection/gpt.h header. The producing build must include the new component. Use the ordinary Framework build and installation guide for that step. The commands below use C:/umicom/installed/framework as an example; substitute the actual qualified prefix consistently if it differs.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-gpt-inspection -B .\build\framework-gpt-inspection -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-gpt-inspection --parallel 2
ctest --test-dir .\build\framework-gpt-inspection --output-on-failure --no-tests=error
~~~

Run each command separately and stop on an unexpected error. PowerShell does not automatically stop after a failed native program. Inspect the exit code immediately. Do not interpret CTest output from an old binary as qualification of a source change whose build failed.

## Read the configuration guards

The lab requires an absolute existing SDK prefix. It resolves the chosen package configuration and checks that it remains inside that prefix. It then checks SDK environment metadata and the exported target’s installed layout. This catches a cached package that points somewhere other than the requested installation.

~~~cmake
umicom_require_sdk_environment(2)
umicom_require_installed_sdk_layout(
    "SDK_PREFIX" _headers Umicom::gpt_image)
target_link_libraries(gpt-inspection PRIVATE Umicom::gpt_image)
~~~

SDK_PREFIX in this explanatory fragment stands for the verified prefix variable used by the complete CMake file. The application does not add the Framework source directory to its build. Mixing a new header with an old archive bypasses the boundary and can produce missing symbols or incompatible behavior.

## Inspect expected outcomes

The lab registers eight scenarios. valid-512 and valid-4096 require accepted synthetic tables. reservation, stride, overlap and backup require controlled structural refusals. read-failure requires the callback error. retry requires refusal followed by acceptance of a fresh fixture. Each successful scenario exits zero; an unknown scenario or argument count exits two.

A controlled refusal is a successful test of refusal behavior. It is not acceptance of the malformed table. Read the printed status and the condition being checked before describing a result. A failed assertion prints its source location and expression and returns one.

## Record evidence

- Record Framework and Bits2Banking revisions, including local changes relevant to the run.
- Record compiler identity, architecture, SDK prefix and selected configuration path.
- Keep configure, build and CTest logs separately, including failed or skipped work.
- Record scenario output and exit status; do not replace original diagnostics with a summary alone.

## Exercise and worked explanation

Suppose the source contains UmiGptImageInspect but the linker cannot find it. The first question is which archive and package the client actually selected. Confirm the configured prefix, installed header and exported target. Reinstall from the intended producer build and configure a fresh client directory if the old cache points elsewhere. Copying source headers into an unrelated SDK is not a reliable repair.

## Continue toward a real media application

On Windows, the existing Framework branding helper embeds the canonical Umicom icon in this client. Course pages use SVG artwork and SVG/ICO favicons; the terminal controls its own font. The eight scenarios do not qualify a native media interface, destructive writes, optical burning or a computer boot. Continue with the earlier reviewed-copy lessons and record those workflows independently. This course remains in development.

[Primary GPT format reference](https://uefi.org/specs/UEFI/2.11/05_GUID_Partition_Table_Format.html)

[Standalone lesson](../../../courses/umicom-os-from-scratch/lessons/56-qualify-an-installed-image-client.html)

[Continue: Read file effects separately from status](57-read-file-effects-separately-from-status.md)
