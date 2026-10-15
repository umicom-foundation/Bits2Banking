# Chapter 61 — Understand virtual machines, hosts and guests

**Bits to Banking · System Administration From Zero · Stage 5 · Umicom Foundation**  
**Audience:** First-time computer users, older learners, new contributors and returning professionals.  
**Practical mode:** Read-only observation by default; any exercise that writes uses a clearly identified private training directory.  
**Implementation policy:** New Umicom executable functionality uses C23 or Assembly. PowerShell and Linux terminal commands here are interactive instructions, not implementation scripts.

## The problem we are solving

**How can a beginner practise operating-system administration without risking the computer they use every day?**

A **virtual machine (VM)** is a simulated computer with its own operating system, virtual disk and network devices. The actual computer is called the **host**. The virtual computer is the **guest**. A **hypervisor** or emulator provides the guest's virtual hardware. An application running in the guest normally cannot change the host's ordinary files unless you deliberately share storage or grant other access. This is useful for learning, but it is not an absolute security boundary.

A VM is not the same as a folder, a Git repository or a shell window. A folder stores data; a repository tracks versions; a shell runs commands in the current operating system. A VM runs another operating system instance. A **container**, by contrast, normally shares its host's operating-system kernel. We introduce containers only after learners can explain the host–guest boundary.

Imagine teaching a new Umicom contributor how to install Linux. Doing that on the family computer's real disk would risk existing files. In a VM, the learner can inspect a simulated disk and return to a known snapshot. This is why the course uses isolated, disposable guests for administration experiments.

![Course illustration: Understand virtual machines, hosts and guests](../../assets/diagrams/sysadmin-host-guest-update42.svg)

## Words you need before you continue

- **Host** — Your real computer and its operating system.
- **Guest** — A separate system running in virtual hardware.
- **Hypervisor** — Software that creates or supervises virtual machines.
- **Snapshot** — A recorded VM state that may support returning to an earlier point; not a backup of the host.

## Worked Umicom example

An Umicom Kernel learner needs to understand boot output. They can run a separately prepared RISC-V teaching image in QEMU, read serial output and stop the guest, while retaining the Windows or Linux host intact. They must distinguish a QEMU process starting successfully from proof that the Umicom kernel actually booted and reached its expected state.

## Before touching your computer

Read each command all the way through. Check the directory or filename first. A **command** is something you type in the terminal; the command output is the evidence you interpret. If a step requires a file or application that is not installed, record **not available** and continue with the conceptual part. Do not invent a result and do not try a more powerful command merely to make the exercise appear to pass.

> **Safety boundary:** For the first exercise **do not create a virtual disk or launch an installer**. A snapshot may not protect a host folder shared into the guest. Never point a VM disk command at a physical drive containing personal files.

## Windows — PowerShell 7, step by step

Start Windows Terminal and select **PowerShell**, or use **PowerShell 7** directly. Confirm with `$PSVersionTable.PSVersion`. The prompt ending in `>` is where you enter the command; **do not type the prompt itself**. Commands are shown exactly, except for placeholders such as `YOUR_APPROVED_LINUX.iso`, which must be replaced with a real filename before execution.

### 1. See your machine architecture

```powershell
Get-CimInstance Win32_ComputerSystem | Select-Object Manufacturer, Model, HypervisorPresent
Get-CimInstance Win32_Processor | Select-Object Name, NumberOfCores, NumberOfLogicalProcessors
```

**Expected result and interpretation:** The manufacturer, model and logical processor count are displayed. HypervisorPresent may be false on an otherwise virtualisation-capable PC.

### 2. Check whether QEMU is already installed

```powershell
Get-Command qemu-system-x86_64, qemu-system-riscv64 -ErrorAction SilentlyContinue | Select-Object Name, Source
```

**Expected result and interpretation:** A missing command produces no listing. Do not assume QEMU is installed simply because Windows supports virtualisation.


## Linux — terminal, step by step

Open the distribution's Terminal application. The examples assume an ordinary, non-root account. Linux paths use `/` and case-sensitive names on most filesystems; a Windows path beginning `C:\` must not be pasted unchanged into Linux commands.

### 1. Identify the host and potential hypervisor

```bash
uname -s
uname -m
lscpu
```

**Expected result and interpretation:** Look for the architecture and, when supported, virtualisation information. Some commands might be unavailable in a minimal guest.

### 2. Check QEMU without starting a guest

```bash
command -v qemu-system-x86_64
command -v qemu-system-riscv64
```

**Expected result and interpretation:** A printed path means the executable is discoverable. No VM starts.


## Guided practice laboratory

1. Draw two boxes labelled Host and Guest. Put PowerShell or Terminal in the host box and a hypothetical Linux service in the guest box.
2. Run the read-only hardware commands; write down your CPU architecture without publishing personal computer identifiers.
3. Explain in your own words why a guest snapshot and an ordinary file backup solve different problems.
4. Describe one boundary that would be weakened by mapping the host Documents folder into an untrusted guest.

**Keep evidence:** Note the date, selected environment, commands entered, expected outcomes and actual outcomes. Omit passwords, tokens, private patient/customer details and unnecessary machine identifiers. A missing or failed step belongs in your report; it is not a reason to hide the error.

## Common problems and how to investigate

| Symptom | Safe investigation |
|---|---|
| HypervisorPresent is False | This does not by itself prove the processor lacks virtualisation support. Consult hardware specifications and firmware settings before changing anything. |
| QEMU command is not recognised | The tool is not installed or its directory is not on PATH. Continue with theory and postpone VM creation. |

Never substitute `git reset --hard`, `git clean -fd`, broad permission changes, service shutdown or force-push for diagnosis. Those operations can discard unrelated work.

## Review questions with suggested answers

1. **What is the host?**

   *Answer:* The physical machine and operating system that run the virtualisation software.

2. **Does a snapshot replace backups?**

   *Answer:* No. Snapshots are tied to the VM environment and may not protect other storage or survive host failure.

3. **Can a guest access host folders?**

   *Answer:* Sometimes, if sharing was explicitly configured; do not assume isolation of shared data.


## How this fits into Umicom

We keep the responsibilities clear. **Umicom Kernel** owns privileged boot and hardware behaviour. **Umicom OS** composes the operating-system environment. **Umicom Framework** owns reusable C23/Assembly services, build, VCS, security and application lifecycle contracts. **Bits2Banking** owns the teaching material and isolated laboratories. A lesson should not be mistaken for proof that a production system is ready.

**Next:** 62 — Prepare a disposable virtual-machine laboratory.
