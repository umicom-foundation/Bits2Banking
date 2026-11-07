<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/12-create-build-evidence.md

PURPOSE:
Keep build results useful for the next developer

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep build results useful for the next developer

CMake describes how a software project is prepared for building. In this course you will follow a small C project from source files to executables, understand dependencies, run tests and record useful evidence. Every chapter includes the setup needed to enter the exercise directly.

## Start here

A terminal is a window in which you type commands. A folder groups files; a path tells a command where a file or folder is. Source files contain the instructions people edit. A build folder contains the machine-readable results. Keep the two folders separate.

This course uses the existing labs/native/bounded-ledger-line project in Bits2Banking. It decodes a fictional message such as 1001:+2500: training account 1001, with a change of 2500 pence. It does not connect to a bank.

On Windows, install MSYS2. In its UCRT64 terminal install the tools:

~~~bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
~~~

Open PowerShell. Adjust the repository path if your copy is elsewhere. Run each line separately and stop on an error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
gcc --version
ninja --version
cmake -S labs/native/bounded-ledger-line -B build/ledger-line -G Ninja -DBUILD_TESTING=ON
cmake --build build/ledger-line --parallel 2
ctest --test-dir build/ledger-line --output-on-failure --no-tests=error
~~~

Use CMake 3.24 or newer and a compiler with C23 support. On Linux, install these tools through the distribution's package manager, open Bash in the repository, and use the same three cmake/ctest commands. The small project builds independently of Framework. [Learning C](../../../courses/learning-c/index.html) gives a slower installation walkthrough.

The expected test names end in syntax, mutations and example. Missing tools, missing executables and zero selected tests need investigation. For experiments, copy the lab to a separate practice folder and point -S at that folder; preserve the original example.


## A result needs an identity

“Tests passed” is incomplete without knowing which source and environment were tested. Build evidence connects a command, its inputs and its outcome. It helps a learner distinguish a source defect from a missing tool or an old executable.

Use a folder you choose for logs. Never place passwords, access tokens, account data or unrelated private files in a public report.

## Record a small run

The following PowerShell example uses the parser lab. The timestamp gives this run a separate folder. Check the result after each command and stop if it failed.

~~~powershell
$RunLogs = "C:/umicom/_local/logs/ledger-$(Get-Date -Format yyyyMMdd-HHmmss)"
New-Item -ItemType Directory -Force $RunLogs
cmake -S labs/native/bounded-ledger-line -B build/ledger-line -G Ninja -DBUILD_TESTING=ON 2>&1 | Tee-Object "$RunLogs/configure.log"
$LASTEXITCODE
cmake --build build/ledger-line --verbose 2>&1 | Tee-Object "$RunLogs/build.log"
$LASTEXITCODE
ctest --test-dir build/ledger-line --output-on-failure --no-tests=error --output-log "$RunLogs/tests.log"
$LASTEXITCODE
~~~

PowerShell does not automatically stop after every failed native command. Do not paste past a failed stage without investigating it.

In Bash, enable pipeline failure reporting before piping commands through tee. Use a directory you own:

~~~bash
set -o pipefail
run_logs="./run-logs/ledger-$(date +%Y%m%d-%H%M%S)"
mkdir -p "$run_logs"
cmake -S labs/native/bounded-ledger-line -B build/ledger-line -G Ninja -DBUILD_TESTING=ON 2>&1 | tee "$run_logs/configure.log"
~~~

Check the status immediately and continue with build and test only after success.

## Add source information

At the repository root, record git rev-parse HEAD and git status --short. The commit identifier alone does not describe uncommitted changes. Record cmake --version and your compiler version. Do not put a local report into public source merely to count files.

## Interpret results carefully

A skipped test means coverage was not exercised. A timeout means the process did not finish within its limit. A passing old log does not validate a later edit. Keep observed outcomes separate from fixes that have only been written.

## Extend your learning

The existing builds-and-diagnostics course follows larger Umicom examples. The build-evidence lab provides a C example for reading structured diagnostic inputs. Begin with this small run, then compare identities and outcomes before analysing a larger application.

## Read the source

[Open the example source](../../../../labs/native/build-evidence/README.md).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Give generated files one owner and complete dependencies](11-generate-files-once.md)
