# Chapter 67 — Configure reproducible C23 toolchains and build directories

**Bits to Banking · System Administration From Zero · Stage 5 · Umicom Foundation**  
**Audience:** First-time computer users, older learners, new contributors and returning professionals.  
**Practical mode:** Read-only observation by default; any exercise that writes uses a clearly identified private training directory.  
**Implementation policy:** New Umicom executable functionality uses C23 or Assembly. PowerShell and Linux terminal commands here are interactive instructions, not implementation scripts.

## The problem we are solving

**Why can the same source code compile on one contributor’s computer and fail on another?**

A **toolchain** is the collection of compilers, linkers, build systems and libraries required to turn source into executable code. **CMake** describes targets and configuration; **Ninja** executes generated build steps; **GCC** or **Clang** compiles C23 source. The versions and the target ABI matter.

For Umicom projects, Windows contributors commonly use MSYS2 UCRT64. Mixing tools from different compiler environments can create dependency problems even when each command works separately. A CMake **preset** records a known configuration, but it does not automatically install the correct compiler or prove that the source is correct.

**Source directory** and **build directory** must remain separate. Generated object files and logs belong under a build/output location, not in the source tree. A successful configure step is not the same as a successful compile, and a compiled program has not necessarily passed its tests. This distinction is central to professional troubleshooting.

![Course illustration: Configure reproducible C23 toolchains and build directories](../../assets/diagrams/sysadmin-source-to-stage-update42.svg)

## Words you need before you continue

- **C23** — The 2023 ISO C language revision used for new native Umicom code.
- **Preset** — Named CMake configuration that captures chosen options and build location.
- **Build artefact** — A generated object, library, executable or package.
- **ABI** — Binary-level contract governing function calls and data layout.

## Worked Umicom example

A student opens PowerShell with an older GCC first on PATH while the Umicom project expects MSYS2 UCRT64. `gcc --version` alone identifies a version, not necessarily the one CMake has already cached. `Get-Command gcc` and `CMakeCache.txt` reveal which executable is being used.

## Before touching your computer

Read each command all the way through. Check the directory or filename first. A **command** is something you type in the terminal; the command output is the evidence you interpret. If a step requires a file or application that is not installed, record **not available** and continue with the conceptual part. Do not invent a result and do not try a more powerful command merely to make the exercise appear to pass.

> **Safety boundary:** Never solve a toolchain mismatch by deleting source files or changing public Framework APIs. Record the full compiler path, version, preset, first error and target before attempting a repair.

## Windows — PowerShell 7, step by step

Start Windows Terminal and select **PowerShell**, or use **PowerShell 7** directly. Confirm with `$PSVersionTable.PSVersion`. The prompt ending in `>` is where you enter the command; **do not type the prompt itself**. Commands are shown exactly, except for placeholders such as `YOUR_APPROVED_LINUX.iso`, which must be replaced with a real filename before execution.

### 1. Check which build tools are selected

```powershell
Get-Command cmake, ninja, gcc -ErrorAction SilentlyContinue | Select-Object Name, Source
cmake --version
ninja --version
```

**Expected result and interpretation:** Note the returned paths and versions. A missing tool should be installed only from an approved source.

### 2. Check the UCRT64 GCC executable directly

```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" --version
Get-Command "C:\msys64\ucrt64\bin\gcc.exe" -ErrorAction SilentlyContinue
```

**Expected result and interpretation:** This calls the selected compiler, bypassing ambiguity in PATH. If it is missing, follow the established MSYS2 setup lesson.


## Linux — terminal, step by step

Open the distribution's Terminal application. The examples assume an ordinary, non-root account. Linux paths use `/` and case-sensitive names on most filesystems; a Windows path beginning `C:\` must not be pasted unchanged into Linux commands.

### 1. Identify compiler and build tools

```bash
command -v cc
cc --version
cmake --version
ninja --version
```

**Expected result and interpretation:** The installed versions and paths are shown. Do not assume `cc` selects GCC.

### 2. Inspect supported CMake presets in a checked-out project

```bash
cmake --list-presets
```

**Expected result and interpretation:** Run at the root of a project containing CMakePresets.json. The output lists named configurations.


## Guided practice laboratory

1. Inspect your toolchain paths; note missing tools rather than installing everything at once.
2. Explain which files a `cmake -S ... -B ...` command reads and creates.
3. Identify the native laboratory in Update 42 and its separate `output/learning-build/deployment-rehearsal` directory.
4. Describe the difference between Configure, Build, Test and Install in one sentence each.

**Keep evidence:** Note the date, selected environment, commands entered, expected outcomes and actual outcomes. Omit passwords, tokens, private patient/customer details and unnecessary machine identifiers. A missing or failed step belongs in your report; it is not a reason to hide the error.

## Common problems and how to investigate

| Symptom | Safe investigation |
|---|---|
| CMake reports compiler not found | Check whether the expected compiler exists and whether the correct path was supplied; do not mix MSYS2 environments. |
| Compiler warning appears during build | Read the specific warning, identify affected file and review before editing. Do not suppress warnings globally. |

Never substitute `git reset --hard`, `git clean -fd`, broad permission changes, service shutdown or force-push for diagnosis. Those operations can discard unrelated work.

## Review questions with suggested answers

1. **Does CMake compile C code by itself?**

   *Answer:* It primarily configures and generates a build; the build step invokes a compiler.

2. **Why separate source and build directories?**

   *Answer:* It protects source files and makes generated artefacts easier to inspect and replace.

3. **Is a successful compile a passing test?**

   *Answer:* No. Tests must run and report their own results.


## How this fits into Umicom

We keep the responsibilities clear. **Umicom Kernel** owns privileged boot and hardware behaviour. **Umicom OS** composes the operating-system environment. **Umicom Framework** owns reusable C23/Assembly services, build, VCS, security and application lifecycle contracts. **Bits2Banking** owns the teaching material and isolated laboratories. A lesson should not be mistaken for proof that a production system is ready.

**Next:** 68 — Stage a practice release without installing system-wide.
