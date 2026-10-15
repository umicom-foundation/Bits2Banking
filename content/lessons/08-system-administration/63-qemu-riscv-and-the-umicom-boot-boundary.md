# Chapter 63 — Understand QEMU, RISC-V and the Umicom boot boundary

**Bits to Banking · System Administration From Zero · Stage 5 · Umicom Foundation**  
**Audience:** First-time computer users, older learners, new contributors and returning professionals.  
**Practical mode:** Read-only observation by default; any exercise that writes uses a clearly identified private training directory.  
**Implementation policy:** New Umicom executable functionality uses C23 or Assembly. PowerShell and Linux terminal commands here are interactive instructions, not implementation scripts.

## The problem we are solving

**Why does an emulator start even when a guest operating system cannot boot?**

**QEMU** can emulate hardware devices and processors. The **RISC-V virt** machine is a standard virtual board useful for operating-system education. Its firmware or bootloader sets up the machine and transfers control to a kernel. The kernel then initialises memory, exceptions and drivers before any ordinary user-space service can run. These are separate stages with separate evidence.

For Umicom, the Linux kernel and the minimal recovery layer are distinct from the reusable application Framework. A successful C23 unit test on the host proves a specific native component test; it does **not** prove that the compiled kernel boots under QEMU. Likewise, QEMU displaying a window or console is not evidence that the guest filesystem or user-space application started.

Architectures are important. An x86-64 host executable does not become a RISC-V guest kernel merely because the filename ends in `.elf`. Build the intended target with a compatible toolchain, inspect its architecture, and boot using the exact documented profile. This lesson is read-only until the learner has the vetted boot artefacts from the Umicom Kernel project.

![Course illustration: Understand QEMU, RISC-V and the Umicom boot boundary](../../assets/diagrams/sysadmin-image-layers-update42.svg)

## Words you need before you continue

- **Emulator** — Software that reproduces the behaviour of a machine architecture or its devices.
- **RISC-V** — An instruction-set architecture used by real and virtual processors.
- **Firmware** — Early code that prepares a machine for its next boot stage.
- **Guest kernel** — The privileged core that runs within the emulated or virtual machine.

## Worked Umicom example

An engineer sees QEMU print a firmware banner but no Umicom prompt. This narrows the problem: the emulator and firmware ran, but the next boot phase may have failed. They capture the serial output and exact kernel SHA rather than declaring the whole OS operational. A later GTK desktop test proves a different layer.

## Before touching your computer

Read each command all the way through. Check the directory or filename first. A **command** is something you type in the terminal; the command output is the evidence you interpret. If a step requires a file or application that is not installed, record **not available** and continue with the conceptual part. Do not invent a result and do not try a more powerful command merely to make the exercise appear to pass.

> **Safety boundary:** Do not guess a `-kernel` path or boot flags from an unrelated tutorial. The exact Umicom Kernel QEMU runbook and output should be reviewed against the checked-out source revision. Keep guest storage and host storage separate.

## Windows — PowerShell 7, step by step

Start Windows Terminal and select **PowerShell**, or use **PowerShell 7** directly. Confirm with `$PSVersionTable.PSVersion`. The prompt ending in `>` is where you enter the command; **do not type the prompt itself**. Commands are shown exactly, except for placeholders such as `YOUR_APPROVED_LINUX.iso`, which must be replaced with a real filename before execution.

### 1. Check that RISC-V QEMU is installed

```powershell
Get-Command qemu-system-riscv64 -ErrorAction SilentlyContinue
qemu-system-riscv64 --version
```

**Expected result and interpretation:** The version is printed if QEMU is installed and on PATH. If it is missing, postpone the boot exercise.

### 2. List supported machines without booting

```powershell
qemu-system-riscv64 -machine help
```

**Expected result and interpretation:** Look for a machine named `virt`. This lists emulated machine types without opening a virtual disk.


## Linux — terminal, step by step

Open the distribution's Terminal application. The examples assume an ordinary, non-root account. Linux paths use `/` and case-sensitive names on most filesystems; a Windows path beginning `C:\` must not be pasted unchanged into Linux commands.

### 1. Check QEMU and possible machine names

```bash
command -v qemu-system-riscv64
qemu-system-riscv64 -machine help
```

**Expected result and interpretation:** The machine list may include `virt`, and no guest is launched.

### 2. Inspect an existing ELF with a trusted native tool

```bash
file ./YOUR_VERIFIED_KERNEL.elf
```

**Expected result and interpretation:** Only run when you have a verified local artefact; check that the reported target architecture matches the intended guest.


## Guided practice laboratory

1. Identify the host architecture using `uname -m` or PowerShell processor queries.
2. Write the expected order: QEMU machine → firmware → kernel → recovery/user space → Framework applications.
3. From the real Umicom Kernel documentation, note the name and output of a boot smoke test without executing unverified flags.
4. Explain two types of evidence required before saying the guest actually booted.

**Keep evidence:** Note the date, selected environment, commands entered, expected outcomes and actual outcomes. Omit passwords, tokens, private patient/customer details and unnecessary machine identifiers. A missing or failed step belongs in your report; it is not a reason to hide the error.

## Common problems and how to investigate

| Symptom | Safe investigation |
|---|---|
| QEMU shows no output | This may indicate the wrong console flags, architecture, firmware, kernel or a genuine kernel problem. Inspect the target-specific runbook; do not guess. |
| file identifies an x86-64 executable | The file is not a RISC-V guest kernel. Rebuild for the correct target rather than renaming it. |

Never substitute `git reset --hard`, `git clean -fd`, broad permission changes, service shutdown or force-push for diagnosis. Those operations can discard unrelated work.

## Review questions with suggested answers

1. **Does a QEMU process existing prove guest readiness?**

   *Answer:* No. It proves only that the emulator process started.

2. **Why separate Kernel and Framework?**

   *Answer:* A kernel owns privilege, hardware and core OS concerns; Framework supplies reusable user-space application services.

3. **What is a safe first emulator command?**

   *Answer:* A version or machine-help command, because it starts no guest and writes no disk.


## How this fits into Umicom

We keep the responsibilities clear. **Umicom Kernel** owns privileged boot and hardware behaviour. **Umicom OS** composes the operating-system environment. **Umicom Framework** owns reusable C23/Assembly services, build, VCS, security and application lifecycle contracts. **Bits2Banking** owns the teaching material and isolated laboratories. A lesson should not be mistaken for proof that a production system is ready.

**Next:** 64 — Identify operating systems, architectures and guest environments.
