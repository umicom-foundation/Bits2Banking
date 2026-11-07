<!--
Umicom Bits2Banking
File: labs/native/c-build-stages/README.md

PURPOSE:
C build stages laboratory

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# C build stages with Umicom C

This small consumer separates native compilation from interpreting an embedded language. The application delegates language parsing and execution to Umicom C. It does not duplicate those engines.

## Prepare the SDK

Install GCC, CMake and Ninja. Use the same compiler family and architecture for the SDK and consumer. In PowerShell:

~~~powershell
Set-Location "C:/umicom/umicom-c"
$env:Path = "C:/msys64/ucrt64/bin;" + $env:Path
cmake --preset windows-ucrt64-debug
cmake --build --preset windows-ucrt64-debug --parallel 2
cmake --install build/windows-ucrt64-debug --prefix "C:/umicom/installed/umicom-c"
~~~

In Bash, from the umicom-c checkout, choose a local prefix:

~~~bash
cmake -S . -B build/lesson-sdk -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/lesson-sdk --parallel 2
cmake --install build/lesson-sdk --prefix "$PWD/installed/lesson-sdk"
~~~

These are instructions for you to execute, not a record of a successful build. If a step fails, resolve that error before continuing. Do not combine libraries built for different processors or C runtimes.

## Build the consumer

PowerShell:

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking/labs/native/c-build-stages"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/umicom-c"
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure --no-tests=error
& ./build/btb-build-stages.exe
~~~

Bash, from this lab directory, replace the prefix with the SDK folder created above:

~~~bash
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/absolute/path/to/umicom-c/installed/lesson-sdk
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure --no-tests=error
./build/btb-build-stages
~~~

Expected application output is Value: 42. The test checks a successful program, a syntax error, division by zero and null arguments. It does not prove every compiler path correct.

## Inspect individual GCC stages

Create out as described in the course. These commands do not run the executable:

~~~text
gcc -std=c23 -E main.c -o out/main.i
gcc -std=c23 -S -O0 -g main.c -o out/main.s
gcc -std=c23 -c -O0 -g main.c -o out/main.o
gcc -std=c23 -c -O0 -g -I"C:/umicom/installed/umicom-c/include" runner.c -o out/runner.o
gcc out/main.o out/runner.o -L"C:/umicom/installed/umicom-c/lib" -lumicom_c_compiler -lumicom_c_runtime -o out/stage-program.exe
~~~

For Linux use your SDK include/lib directories and name the final output out/stage-program. Run ./out/stage-program.exe in PowerShell or ./out/stage-program in Bash. The SDK's configured library directory may be lib64; inspect the installed prefix if -L does not find the archives. CMake's imported targets avoid guessing that directory.

## File map

| File | Responsibility |
|---|---|
| main.c | Embedded program, printed result, process exit status |
| runner.h | Declaration and output contract |
| runner.c | Calls the existing compiler, then the checked interpreter |
| test_runner.c | Accepted input and rejected-input publication checks |
| CMakeLists.txt | Targets and installed SDK dependency |

Read the native build stages module in Learning C for preprocessing, assembly, symbols, archives, diagnostics and incremental rebuilds. An editor can call these tools; it does not need to rebuild every Framework source when using an installed compatible SDK.
