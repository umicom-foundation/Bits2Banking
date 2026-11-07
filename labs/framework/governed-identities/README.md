# Governed identities lab

Read and change identity metadata through the shared Framework service. Follow borrowed observations, revision exhaustion and damaged row counts with synthetic data.

## Set up this lab

A terminal is an application where you type commands. A compiler translates C source into machine instructions; CMake prepares the build rules; Ninja carries out those rules. This lab also needs an installed Umicom Framework SDK containing its security library. You can read the lesson without installing anything.

1. Open the Bits2Banking checkout and find `labs/framework/governed-identities`. Read `main.c` and `CMakeLists.txt`.
2. In PowerShell on Windows, use your UCRT64 C23 compiler with CMake 3.26 or newer and Ninja. Set the SDK path below to your actual installation; it must match the compiler and architecture.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\governed-identities"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
& ".\build\btb-governed-identities.exe"
```
3. In Bash, change into the same lab and supply your SDK location.

```bash
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/your/framework-sdk
cmake --build build
ctest --test-dir build --output-on-failure
./build/btb-governed-identities
```
Stop at a failed command. A missing `UmicomFrameworkConfig.cmake` means CMake cannot locate the installed SDK. A link error means the SDK may not match the headers or compiler; do not replace Framework calls with local copies. Successful execution ends with `Governed identity lab passed.` The lab uses synthetic metadata and does not create operating-system users or login sessions.

## Expected observations

The program prints five lines: addition, borrowed/copy comparison, revision refusal, damaged-count refusal and the final passing line. A failed REQUIRE prints its source line and exits unsuccessfully. No passwords are requested and no files are persisted.
