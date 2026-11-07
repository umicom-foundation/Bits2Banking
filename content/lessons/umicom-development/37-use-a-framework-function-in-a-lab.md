# Use a Framework function in a practical lab

A library is compiled code that another program can call. A header describes the names, types and rules of those calls. This lab uses Framework's SHA-256 service to calculate a digest: a fixed-size description of some bytes. It teaches how to read a contract, link a small consumer and check the result. It does not build a second hashing engine.

## Setup recap

Use a C23 compiler, CMake 3.24 or newer, Ninja, Bits2Banking sources and an installed Umicom Framework SDK containing the `base` component. On Windows, use matching MSYS2 UCRT64 tools and SDK. On Linux, use a native SDK built for that computer's architecture. See [terminal setup](../learning-c/terminal-lab.md) for installation and [using an installed SDK](06-use-an-installed-sdk.md) for the package layout. Run `gcc --version`, `cmake --version` and `ninja --version` to confirm the tools are on PATH.

Choose an empty practice location. The examples below use `C:\umicom-learning` or `$HOME/umicom-learning`. Change the source and SDK paths if your installations differ. Stop after a failed command and read its error before continuing.

## 1. Copy the small consumer

PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
New-Item -ItemType Directory -Force 'C:\umicom-learning'
Copy-Item -Recurse 'C:\umicom\Umicom-Bits2Banking\labs\native\framework-hash' 'C:\umicom-learning\framework-hash'
Set-Location 'C:\umicom-learning\framework-hash'
Get-Content main.c
```

Bash:

```bash
mkdir -p "$HOME/umicom-learning"
cp -R "$HOME/umicom/Umicom-Bits2Banking/labs/native/framework-hash" "$HOME/umicom-learning/framework-hash"
cd "$HOME/umicom-learning/framework-hash"
cat main.c
```

Do this copy once into a new destination. Repeating a recursive copy into an existing folder can create an unintended nested folder.

## 2. Understand the call before compiling

```c
char hex[UMI_SHA256_HEX_CAPACITY];
UmiStatus status = UmiSha256Buffer("abc", 3U, hex);
```

`hex` is space owned by this program. The capacity is 65 characters: 64 hexadecimal digits and the zero character ending the C string. `3U` says to read three bytes. The zero character after `abc` in the string literal is not included. `UmiStatus` is a result code; check it before using the output. The lab uses `REQUIRE` to print a failed condition and return an error to the terminal.

The path from the application to the engine is:

```text
main.c → sha256.h contract → Umicom::base library → Framework implementation
```

In `CMakeLists.txt`, `find_package` locates the installed SDK, while `target_link_libraries` connects this executable to its `base` library. Neither line copies the engine into the lab.

## 3. Configure, build and run

PowerShell:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON -DCMAKE_PREFIX_PATH='C:/umicom/installed/framework'
cmake --build build --parallel 2
& '.\build\btb-framework-hash.exe' known
ctest --test-dir build --output-on-failure --no-tests=error
```

Bash:

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk"
cmake --build build --parallel 2
./build/btb-framework-hash known
ctest --test-dir build --output-on-failure --no-tests=error
```

The expected digest is `ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad`. The executable then prints `PASS known`. CTest registers five cases: `known`, `chunks`, `changed`, `rejected` and `chain`. These are expected outcomes to check on your machine, not a substitute for running them.

## 4. Make a controlled mistake

In your practice copy, change the length in `Known` from `3U` to `4U`. Rebuild and run `known` again. It should fail its comparison because you now hash the terminating zero as well. Restore `3U`, rebuild and repeat. This demonstrates why an input's length is part of its contract.

If CMake cannot find `UmicomFramework`, check the SDK's `lib/cmake/UmicomFramework/UmicomFrameworkConfig.cmake`. If the linker cannot find `UmiSha256Buffer`, check that the headers and library belong to the same SDK revision. Do not copy a newer header over an older library.

## Source map and next steps

Read Framework's [`sha256.h`](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/base/sha256.h), then [`sha256.c`](https://github.com/umicom-foundation/umicom-framework/blob/main/src/base/sha256.c). The consumer is `labs/native/framework-hash/main.c` in Bits2Banking. Continue with [incremental calls and failure contracts](38-incremental-functions-and-failure-contracts.md), or return to the [Framework course](index.md).

[Previous: Map a shared feature before changing it](36-map-a-shared-feature-before-changing-it.md)
