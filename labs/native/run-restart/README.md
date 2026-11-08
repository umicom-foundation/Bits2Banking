<!--
Umicom Bits2Banking
File: labs/native/run-restart/README.md

PURPOSE:
Build and interpret the controlled C restart lifecycle exercise.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Restart a Framework-owned session

This C23 program uses the installed Framework build service. It supplies a controlled executor to make cancellation and completion visible. The selected file must exist because normal launch preparation is exercised, but the lab does **not** execute that file or create a child process.

## Build and exercise

Install a C23 compiler, CMake 3.25 or later, Ninja and a matching Framework SDK containing the restart service. Open a terminal in the lab directory. A terminal runs commands; CMake prepares build instructions and Ninja compiles them. Stop on a configure or build error before using an existing executable. Substitute your own SDK location for the Windows example.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\run-restart"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
.\build\run-restart.exe "$PWD\build\run-restart.exe" handover
ctest --test-dir build --output-on-failure --no-tests=error
~~~

1. Expect the handover scenario to wait while zero completed results are acknowledged. After the result is copied, the replacement executor completes. The final line reports two executor calls and zero child processes.
2. Run the same command with **stop** and **revoke**. Each reports one executor call. Stop cancels the pending intent; revocation refuses renewed launch permission.
3. Read **main.c** beside Framework’s **run_restart.h**. The lab coordinates public calls; it does not implement a second restart state machine.

On Linux or macOS, use the same CMake commands with your SDK path, then **./build/run-restart "$PWD/build/run-restart" handover**. Your SDK and compiler must target the same platform.

A missing header or linker symbol indicates an older or mismatched SDK. Rebuild and install the intended Framework before retrying. A BUSY deadline failure is a failed exercise, not permission to increase the timeout until it disappears. Preserve the command and output. This lab does not verify GUI lifetime, process termination, binary freshness or transcript storage; Framework and Studio have separate scenarios for those boundaries. Record their actual results independently.
