# Chapter 22 — Build, test and inspect a read-only C23 program

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Use GCC, CMake and CTest to understand how native programs are built and verified.

## Why this matters

![Professional administration separates observation from change](../../assets/diagrams/sysadmin-observe-change-update38.svg)


A compiler translates C source into machine code. CMake describes build targets and configuration. Ninja executes build steps efficiently. CTest runs registered tests and reports their outcome. Each performs a different part of the workflow. A successful compilation is not the same as a passing test suite, and passing tests are not a claim of complete production readiness.

This update includes a small standalone laboratory under `labs/native/sysadmin-readonly-text`. Its native C23 program reads a text file, counts bytes and logical lines, and refuses binary or oversized inputs. It does not edit the file, scan privileged system paths or silently truncate content. The tests use checked-in fixtures and show success as well as deliberate rejection.

For a beginner, the purpose is twofold: see how the software tools fit together and understand that a read-only diagnostic program can still report errors responsibly. For the real Umicom project, shared production file services must remain Framework-owned rather than being duplicated from this educational sample.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Compiler** | Program that translates C23 source into executable machine code. |
| **CMake** | Declarative build-configuration tool. |
| **Ninja** | Native build execution engine. |
| **CTest** | Test runner used by CMake projects. |
| **Fail closed** | Reject invalid or incomplete input instead of pretending the result is valid. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Enter the Bits2Banking repository when available

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
```

**Expected observation:** The working directory is the checked-out learning repository.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Select the MSYS2 UCRT64 toolchain

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
```

**Expected observation:** The session searches the requested compiler and build tools first.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Configure the read-only C23 lab

```powershell
cmake -S ".\labs\native\sysadmin-readonly-text" -B ".\output\learning-build\sysadmin-readonly-text" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
```

**Expected observation:** CMake prepares build targets when prerequisites are installed.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 4 — Compile the source

```powershell
cmake --build ".\output\learning-build\sysadmin-readonly-text" --parallel 2
```

**Expected observation:** A native executable and test binary are built.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 5 — Run all registered tests

```powershell
ctest --test-dir ".\output\learning-build\sysadmin-readonly-text" --no-tests=error --output-on-failure
```

**Expected observation:** Tests report passed or failed; keep the output for evidence.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 6 — Inspect a sample text file safely

```powershell
& ".\output\learning-build\sysadmin-readonly-text\btb-sysadmin-text.exe" ".\labs\native\sysadmin-readonly-text\fixtures\sample.md"
```

**Expected observation:** The native program reports byte and line counts without modifying the file.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Configure the same lab with a Linux compiler

```bash
cmake -S labs/native/sysadmin-readonly-text -B output/learning-build/sysadmin-readonly-text -G Ninja -DBUILD_TESTING=ON
```

**Expected observation:** A Linux build directory is created if CMake and Ninja are installed.

### Linux step 2 — Build and test

```bash
cmake --build output/learning-build/sysadmin-readonly-text --parallel 2 && ctest --test-dir output/learning-build/sysadmin-readonly-text --output-on-failure
```

**Expected observation:** Native build and tests run in sequence.

## Worked support scenario

A student receives “CMake cannot find gcc”. They check `gcc --version` and `Get-Command gcc`, then confirm the UCRT64 compiler path. They do not change C23 code to solve a missing tool. After the toolchain is detected, a failed CTest case is investigated separately from compilation.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Running the sample executable from the wrong folder | Use the full documented relative path after setting the repository root. |
| Treating “No tests were found” as success | Run `ctest --no-tests=error` for explicit failure when tests are missing. |
| Assuming a read-only inspector validates all file formats | This lab accepts bounded text and deliberately rejects binary input. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. What is the difference between CMake and Ninja?
2. What proves that the test executable was actually run?

<details><summary>Show the suggested answers</summary>

1. CMake configures the build graph; Ninja runs the generated compile/link steps.
2. CTest output and its exit status, not just a successful build.

</details>

## How this connects to Umicom

The lab uses C23 only and remains educational. Native Framework process, file and test services remain the authority for reusable production implementations.

## Where to go next

Continue with [Chapter 23 — Troubleshoot problems systematically and write useful evidence](23-systematic-troubleshooting-and-reporting.md).
