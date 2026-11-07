# Lab: build a small application with the Framework SDK

An SDK is a software development kit: headers describe available functions, compiled libraries supply implementations, and package files explain how to use them. This lab builds the existing Bits2Banking activity counter against an installed Umicom Framework SDK. A consumer is an application using that SDK. It does not need to compile the whole Framework for every edit.

## Setup recap: Prepare a development folder and tools

You need a C23 compiler, CMake 3.24 or later, Ninja, a Bits2Banking checkout and a compatible installed Framework SDK. On Windows install the MSYS2 UCRT64 tools and add `C:\msys64\ucrt64\bin` to the current PowerShell PATH. On Linux use a C23 compiler and the CMake and Ninja packages for your distribution. Check `gcc --version`, `cmake --version` and `ninja --version` before continuing. The [terminal setup lab](../learning-c/terminal-lab.md) explains installation, folders, command prompts and exit codes in detail.

Use an SDK built for the same operating system, processor and compatible compiler runtime as your consumer. The commands below assume a Windows UCRT64 SDK at `C:\umicom\installed\framework`, or a Linux SDK at `$HOME/umicom-sdk`. Replace the location with your actual installation. An SDK directory must contain `lib/cmake/UmicomFramework/UmicomFrameworkConfig.cmake`; an empty folder does not provide an SDK. See [Using an installed SDK](06-use-an-installed-sdk.md) before continuing if it is not installed.

In PowerShell, check the package file:

```powershell
Get-Item 'C:\umicom\installed\framework\lib\cmake\UmicomFramework\UmicomFrameworkConfig.cmake'
New-Item -ItemType Directory -Force 'C:\umicom-learning'
Copy-Item -Recurse 'C:\umicom\Umicom-Bits2Banking\labs\native\framework-activity' 'C:\umicom-learning\framework-activity'
Set-Location 'C:\umicom-learning\framework-activity'
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
```

Copy only when the destination does not already exist. In bash, with the repository under `$HOME/Umicom-Bits2Banking`:

```bash
ls "$HOME/umicom-sdk/lib/cmake/UmicomFramework/UmicomFrameworkConfig.cmake"
mkdir -p "$HOME/umicom-learning"
cp -R "$HOME/Umicom-Bits2Banking/labs/native/framework-activity" "$HOME/umicom-learning/framework-activity"
cd "$HOME/umicom-learning/framework-activity"
```

## 2. Read the project before building

Open [the activity lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/CMakeLists.txt). Each file has one responsibility:

| File | Responsibility |
| --- | --- |
| `activity.h` | Declares the shared teaching function and its result type. |
| `activity.c` | Checks the count and advances it once. |
| `console.c` | Calls the function and prints the result. |
| `window.c` | Connects a button and label to the same function. |
| `test_activity.c` | Checks valid values, boundaries and unchanged output on failure. |
| `CMakeLists.txt` | Describes targets, dependencies and test registration. |

`find_package(UmicomFramework CONFIG REQUIRED COMPONENTS base)` loads package instructions. `target_link_libraries(... Umicom::base)` supplies the shared base dependency. Including a header alone does not link an implementation. The activity rule is an educational example; production rules reused by Umicom products belong in Framework.

## 3. Configure and build just this consumer

PowerShell:

```powershell
cmake -S . -B build-ucrt -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build-ucrt --parallel 2
.\build-ucrt\btb-activity-console.exe
ctest --test-dir build-ucrt -R '^bits2banking\.framework_activity\.' --output-on-failure --no-tests=error
```

Bash:

```bash
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk" -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build --parallel 2
./build/btb-activity-console
ctest --test-dir build -R '^bits2banking\.framework_activity\.' --output-on-failure --no-tests=error
```

Run one command at a time and stop on errors. Expect `Completed exercises: 1` and six passing tests for the unmodified example. These are expected results, not a report of execution on your machine. `CMAKE_PREFIX_PATH` tells package discovery where to search. The generated build directory records this source location and compiler; do not copy it between computers or toolchains.

## 4. Understand the function contract

The input `current` is an unsigned count. `next` points to caller-owned output memory. Counts 0 through 999 advance by one. At 1000 the function returns `UMI_STATUS_CAPACITY_EXCEEDED`. An input above 1000 or a null output pointer returns `UMI_STATUS_INVALID_ARGUMENT`. Rejected calls leave a supplied output value unchanged.

Trace `BtbActivityAdvance(999U, &result)` on paper. `&result` means the address of the result variable. The checks succeed, the function writes 1000 and returns success. With input 1000, it returns before the assignment. The tests deliberately start output at 77 to make an accidental write visible.

## 5. Add the window after the console works

Install GTK4 development files for the same toolchain. Confirm `pkg-config --modversion gtk4` works. Reconfigure the same Windows consumer with `cmake -S . -B build-ucrt -DBTB_ACTIVITY_GTK4=ON`, build target `btb-activity-window`, then run `.\build-ucrt\btb-activity-window.exe`. In bash substitute `build` and `./build/btb-activity-window`. Read [Introduction to GTK4](05-introduction-to-gtk4.md) for signals, widgets and callbacks. The window uses the same activity function; it does not need a second copy of the counting rule.

## 6. Investigate a controlled change

In the practice copy, change the increment from `+ 1U` to `+ 2U`. Rebuild the consumer and run its six tests. The first, last and in-place cases should expose the changed behaviour. Restore the increment and repeat. If package discovery fails, correct the SDK path. If linking fails, check target dependencies and toolchain compatibility before editing unrelated code.

[Framework course contents](index.md) · [Lab: keep an event deadline observable](event-deadline-lab.md)
