<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/04-content-and-timestamps.md

PURPOSE:
Understand content changes and timestamp limits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand content changes and timestamp limits

A build system records how source files become programs and when work must be repeated. This course begins with a small existing Notes library and follows dependencies, generated configuration, tests and evidence into the shared Umicom build architecture.

## Start here

A terminal is a window that accepts commands. A directory is a folder. This course uses a small teaching project in the Bits2Banking checkout; it does not rebuild the complete Framework. You need a C23 compiler, CMake 3.26 or newer, and Ninja. On Windows, open the installed MSYS2 UCRT64 terminal and install the packages below if they are missing:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

Close that terminal and open PowerShell. Adjust the checkout path if yours is elsewhere:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S "labs/native/build-dependency-graph" -B "build/dependency-graph" -G Ninja -DBUILD_TESTING=ON
cmake --build "build/dependency-graph" --parallel 2
ctest --test-dir "build/dependency-graph" --output-on-failure --no-tests=error
```

Run each command separately and stop if it reports an error. For a Linux Bash terminal with GCC, CMake and Ninja installed, change to the Bits2Banking checkout with `cd`, then use the same three `cmake`/`ctest` commands. These are learner exercises; the guide does not assert that a particular machine has passed them. See [Learning CMake](../../../courses/learning-cmake/index.html) for a longer setup and command walkthrough.

Package names can be checked in the official [MSYS2 GCC](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-gcc), [CMake](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-cmake) and [Ninja](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-ninja) listings.


## Two descriptions of a file

A file has bytes, which are its content, and metadata such as a modification time. These are different observations. Copying a file can preserve its old time while changing bytes; touching a file can change its time without changing bytes.

A **digest** is a fixed-size summary computed from bytes. SHA-256 is useful for comparing exact content. It does not tell us whether two different programs have the same meaning. A comment edit and a logic edit both change a raw content digest.

## Study without corrupting a project

1. Create a separate scratch copy of the dependency lab if you want to experiment with timestamps. Keep its build folder separate too.
2. Read the source file and record its digest with `Get-FileHash -Algorithm SHA256` in PowerShell, or `sha256sum` in Bash.
3. Add a comment and compute the digest again. The values should differ because the bytes differ.
4. Compare this with the dry-run result from the incremental lesson. The build driver can decide to compile again without first determining whether C semantics changed.
5. Read Framework's public-contract fingerprint implementation linked below. Identify the inputs it observes. Do not disable it as a shortcut to fewer build jobs.

## Why ignoring comments needs care

A language-aware analyser must understand preprocessing, string literals, line continuations and compiler options. Text that looks like a comment delimiter inside a string is data. Preprocessor line information can affect diagnostics and macros. Generated files and build rules may also depend on exact source bytes for reasons unrelated to compilation.

## A sound optimisation exercise

Design a checklist with cases for a used public header, an unused header, a private include, a comment, a compiler flag and changed content with a preserved timestamp. Record the expected affected artifacts separately from observed jobs. An optimisation is credible only when it preserves correctness for these cases.

The Umicom learning-pack verifier provides a simpler comparison: a lesson resource is accepted against an exact declared digest. It is not trying to determine equivalent prose. The dependency system and the learning system use content identity for different purposes.


## Read the source

[Open the example source](../../../../../Umicom-Applications/framework/cmake/UmicomPublicContractFingerprint.cmake).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Observe incremental work before changing the build](03-observe-incremental-work.md) · [Next: Give generated configuration one owner](05-generated-configuration.md)
