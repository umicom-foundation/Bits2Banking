# Chapter 69 — Inspect runtime dependencies and test relocation

**Bits to Banking · System Administration From Zero · Stage 5 · Umicom Foundation**  
**Audience:** First-time computer users, older learners, new contributors and returning professionals.  
**Practical mode:** Read-only observation by default; any exercise that writes uses a clearly identified private training directory.  
**Implementation policy:** New Umicom executable functionality uses C23 or Assembly. PowerShell and Linux terminal commands here are interactive instructions, not implementation scripts.

## The problem we are solving

**Why can a program work in a build folder but fail when opened from another computer or folder?**

A compiled executable may depend on **shared libraries** such as DLL files on Windows or `.so` files on Linux. It may also depend on data files, fonts, schemas, environment variables and a working directory. Merely copying the executable does not guarantee these resources follow it.

A **static library** normally contributes code to the linked program. A **dynamic library** is loaded at run time. A **relocatable application** can find the resources it needs even when the installation folder differs from the build folder. Umicom Framework owns reusable Windows runtime packaging and application-startup policy; thin products should consume those facilities instead of introducing separate copying scripts.

Professional diagnosis starts by distinguishing three phases: linking, operating-system loader startup, and later application initialisation. Missing DLL errors occur before ordinary application code may run. A missing icon, schema or configuration can be a later resource-resolution failure. Test each boundary separately and record the exact message.

![Course illustration: Inspect runtime dependencies and test relocation](../../assets/diagrams/sysadmin-dependency-chain-update42.svg)

## Words you need before you continue

- **DLL** — Windows dynamic-link library loaded at run time.
- **Shared object** — Common Linux shared-library file, often ending in `.so`.
- **Loader** — Operating-system component that loads an executable and its dependencies.
- **Working directory** — Directory from which relative file paths are interpreted.

## Worked Umicom example

Umicom Trader launches from a PowerShell window but fails when double-clicked. One plausible cause is that PowerShell configured `C:\msys64\ucrt64\bin` on PATH, while the desktop shortcut does not. The proper fix is Framework-owned runtime staging and relocatable paths, tested by icon launch—not telling end users to open a development shell.

## Before touching your computer

Read each command all the way through. Check the directory or filename first. A **command** is something you type in the terminal; the command output is the evidence you interpret. If a step requires a file or application that is not installed, record **not available** and continue with the conceptual part. Do not invent a result and do not try a more powerful command merely to make the exercise appear to pass.

> **Safety boundary:** Do not download random DLLs from search results to silence loader errors. Do not modify PATH globally or copy SDK files into Windows system directories without an approved package policy.

## Windows — PowerShell 7, step by step

Start Windows Terminal and select **PowerShell**, or use **PowerShell 7** directly. Confirm with `$PSVersionTable.PSVersion`. The prompt ending in `>` is where you enter the command; **do not type the prompt itself**. Commands are shown exactly, except for placeholders such as `YOUR_APPROVED_LINUX.iso`, which must be replaced with a real filename before execution.

### 1. Inspect the staged executable first

```powershell
Get-Item "C:\umicom\learning-stage-update42\bin\btb-deployment-review-demo.exe" | Select-Object FullName, Length
```

**Expected result and interpretation:** The file exists and its size is reported. If absent, return to the staging lesson.

### 2. Inspect declared Windows DLL imports, if objdump is installed

```powershell
& "C:\msys64\ucrt64\bin\objdump.exe" -p "C:\umicom\learning-stage-update42\bin\btb-deployment-review-demo.exe" | Select-String 'DLL Name' 
```

**Expected result and interpretation:** The list shows named import dependencies; it does not prove every dependency resolves on another machine.


## Linux — terminal, step by step

Open the distribution's Terminal application. The examples assume an ordinary, non-root account. Linux paths use `/` and case-sensitive names on most filesystems; a Windows path beginning `C:\` must not be pasted unchanged into Linux commands.

### 1. Inspect the dynamic section of your own build

```bash
readelf -d "$HOME/umicom-learning-stage/bin/btb-deployment-review-demo" | grep NEEDED
```

**Expected result and interpretation:** Only works when the binary and readelf are available. A fully static binary may have no dynamic section.

### 2. Run the staged program from another working directory

```bash
cd "$HOME"
"$HOME/umicom-learning-stage/bin/btb-deployment-review-demo"
```

**Expected result and interpretation:** A successful relocation run is evidence that this particular demonstration does not depend on its original build CWD.


## Guided practice laboratory

1. Read the executable path and imported libraries for a known training build.
2. Try running the staged demo from a different current directory.
3. Document which dependencies the loader provides and which resources the application must locate itself.
4. Explain why working on your machine does not prove that a release is distributable.

**Keep evidence:** Note the date, selected environment, commands entered, expected outcomes and actual outcomes. Omit passwords, tokens, private patient/customer details and unnecessary machine identifiers. A missing or failed step belongs in your report; it is not a reason to hide the error.

## Common problems and how to investigate

| Symptom | Safe investigation |
|---|---|
| objdump.exe is not found | Install or select an approved toolchain; do not substitute a random internet executable. |
| A library is listed but still cannot load | The loader may not find the right architecture, ABI or dependent libraries. Capture the exact message and inspect the package. |

Never substitute `git reset --hard`, `git clean -fd`, broad permission changes, service shutdown or force-push for diagnosis. Those operations can discard unrelated work.

## Review questions with suggested answers

1. **What happens before main() starts?**

   *Answer:* The operating system locates and loads the executable and needed runtime libraries.

2. **Can CWD changes break a program?**

   *Answer:* Yes, when code incorrectly relies on relative paths.

3. **Who should own shared runtime deployment?**

   *Answer:* Umicom Framework, with thin applications using its tested facilities.


## How this fits into Umicom

We keep the responsibilities clear. **Umicom Kernel** owns privileged boot and hardware behaviour. **Umicom OS** composes the operating-system environment. **Umicom Framework** owns reusable C23/Assembly services, build, VCS, security and application lifecycle contracts. **Bits2Banking** owns the teaching material and isolated laboratories. A lesson should not be mistaken for proof that a production system is ready.

**Next:** 70 — Understand application startup and shutdown supervision.
