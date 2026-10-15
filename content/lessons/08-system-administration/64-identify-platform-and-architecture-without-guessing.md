# Chapter 64 — Identify an operating system and architecture without guessing

**Bits to Banking · System Administration From Zero · Stage 5 · Umicom Foundation**  
**Audience:** First-time computer users, older learners, new contributors and returning professionals.  
**Practical mode:** Read-only observation by default; any exercise that writes uses a clearly identified private training directory.  
**Implementation policy:** New Umicom executable functionality uses C23 or Assembly. PowerShell and Linux terminal commands here are interactive instructions, not implementation scripts.

## The problem we are solving

**How do you know which instructions and installer belong to the computer or VM in front of you?**

An operating system has a **name**, a **release**, an **architecture** and an environment. Windows 11 on x86-64 and Linux on RISC-V may both offer a command line, but they require different executables, package sources and service managers. Even within one machine, the host and a virtual guest can report different operating-system versions.

A 64-bit processor may execute some 32-bit programs, but that does not imply all binary formats, drivers and shared libraries are compatible. Never choose a downloadable package solely because its filename says “64-bit”. A package may also depend on the correct operating system, runtime libraries and toolchain ABI.

Collect a **baseline** before installing or troubleshooting. An OS baseline records only the useful technical identifiers: OS release, architecture, command interpreter version and selected tools. Do not copy machine serial numbers, network credentials or other identifiers into a public issue report.

![Course illustration: Identify an operating system and architecture without guessing](../../assets/diagrams/sysadmin-image-layers-update42.svg)

## Words you need before you continue

- **Architecture** — The processor family targeted by executable instructions.
- **ABI** — Rules for how compiled code calls functions and exchanges values.
- **Distribution** — A packaged Linux operating system with a specific software-management ecosystem.
- **Baseline** — A short record of known system properties and versions.

## Worked Umicom example

A contributor tries an x86-64 Windows GCC package inside an aarch64 Linux VM. The file cannot run because both the operating-system and architecture expectations are wrong. The correct diagnosis begins with `uname -m`, `/etc/os-release` and the intended toolchain, not with disabling security controls.

## Before touching your computer

Read each command all the way through. Check the directory or filename first. A **command** is something you type in the terminal; the command output is the evidence you interpret. If a step requires a file or application that is not installed, record **not available** and continue with the conceptual part. Do not invent a result and do not try a more powerful command merely to make the exercise appear to pass.

> **Safety boundary:** Only record information relevant to troubleshooting. Do not post full system inventories to public forums without checking for personal, private or business details.

## Windows — PowerShell 7, step by step

Start Windows Terminal and select **PowerShell**, or use **PowerShell 7** directly. Confirm with `$PSVersionTable.PSVersion`. The prompt ending in `>` is where you enter the command; **do not type the prompt itself**. Commands are shown exactly, except for placeholders such as `YOUR_APPROVED_LINUX.iso`, which must be replaced with a real filename before execution.

### 1. Read operating-system information

```powershell
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion, OsArchitecture
$PSVersionTable.PSVersion
```

**Expected result and interpretation:** You should see a Windows name, version, architecture and PowerShell version. These are read-only observations.

### 2. Locate the command that will run

```powershell
Get-Command pwsh, git, gh, cmake -ErrorAction SilentlyContinue | Select-Object Name, Source
```

**Expected result and interpretation:** `Source` identifies the selected executable, helping diagnose unexpected older versions.


## Linux — terminal, step by step

Open the distribution's Terminal application. The examples assume an ordinary, non-root account. Linux paths use `/` and case-sensitive names on most filesystems; a Windows path beginning `C:\` must not be pasted unchanged into Linux commands.

### 1. Read kernel and distribution separately

```bash
uname -s
uname -m
cat /etc/os-release
```

**Expected result and interpretation:** `uname` reports the running kernel and architecture; `/etc/os-release` identifies the distribution.

### 2. Inspect the shell and tools

```bash
printf '%s\n' "$SHELL"
command -v cmake
command -v gcc
```

**Expected result and interpretation:** A shell path and any installed tool paths are displayed.


## Guided practice laboratory

1. Create a baseline note with OS, release, architecture and PowerShell or shell version.
2. Compare your output with the instructions for the current Umicom repository.
3. Explain what would change if the work moved into a virtual Linux guest.
4. Check that `Get-Command` or `command -v` resolves the tool you expected.

**Keep evidence:** Note the date, selected environment, commands entered, expected outcomes and actual outcomes. Omit passwords, tokens, private patient/customer details and unnecessary machine identifiers. A missing or failed step belongs in your report; it is not a reason to hide the error.

## Common problems and how to investigate

| Symptom | Safe investigation |
|---|---|
| A command is missing | Different editions and minimal images ship different tools. Note the absence rather than installing a random replacement. |
| Two versions of GCC appear | Check the resolved executable path. PATH order, toolchain profile and ABI must agree. |

Never substitute `git reset --hard`, `git clean -fd`, broad permission changes, service shutdown or force-push for diagnosis. Those operations can discard unrelated work.

## Review questions with suggested answers

1. **Does PowerShell 7 make Windows into Linux?**

   *Answer:* No. A shell runs on an operating system; changing shells does not replace the kernel.

2. **Why keep the OS release alongside architecture?**

   *Answer:* Software depends on both, plus ABI and library versions.

3. **Why avoid sharing serial numbers in a bug report?**

   *Answer:* They are usually unnecessary and can disclose identifiable system details.


## How this fits into Umicom

We keep the responsibilities clear. **Umicom Kernel** owns privileged boot and hardware behaviour. **Umicom OS** composes the operating-system environment. **Umicom Framework** owns reusable C23/Assembly services, build, VCS, security and application lifecycle contracts. **Bits2Banking** owns the teaching material and isolated laboratories. A lesson should not be mistaken for proof that a production system is ready.

**Next:** 65 — Understand disk images, partitions and root filesystems.
