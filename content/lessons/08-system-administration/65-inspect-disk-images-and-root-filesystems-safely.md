# Chapter 65 — Understand disk images, partitions and root filesystems safely

**Bits to Banking · System Administration From Zero · Stage 5 · Umicom Foundation**  
**Audience:** First-time computer users, older learners, new contributors and returning professionals.  
**Practical mode:** Read-only observation by default; any exercise that writes uses a clearly identified private training directory.  
**Implementation policy:** New Umicom executable functionality uses C23 or Assembly. PowerShell and Linux terminal commands here are interactive instructions, not implementation scripts.

## The problem we are solving

**What is stored in a disk-image file, and why must beginners never confuse one with their computer’s real disk?**

A **disk image** is a file holding disk-like data. It may contain a partition table, one or more filesystems and data. A **filesystem** organises files and directories; a **root filesystem** holds the operating system’s user-space directories and configuration. A kernel is not the same thing as the root filesystem. A **RAM-based root filesystem** may exist only during the running guest session.

Formats such as raw, qcow2 and VHDX are not interchangeable. Some use metadata for snapshots or sparse allocation; others represent a linear sequence of sectors. A reported **virtual size** can exceed the image’s physical file size when sparse allocation is used. This does not grant the real disk unlimited space.

For the first exercise, we inspect ordinary files and existing image metadata. We do not partition, format, mount, write, expand or repair any disk. A learner who can explain the difference between `C:\umicom\guest.qcow2` and `C:` is much less likely to lose data in a later administration task.

![Course illustration: Understand disk images, partitions and root filesystems safely](../../assets/diagrams/sysadmin-image-layers-update42.svg)

## Words you need before you continue

- **Partition** — A named region of a disk using a partition-table scheme.
- **Filesystem** — The format that organises file data and metadata.
- **Root filesystem** — The primary directory hierarchy for a running Linux system.
- **Sparse disk image** — An image that allocates host storage as guest data is written.

## Worked Umicom example

A student sees a qcow2 image reporting a 20 GB virtual size while the host file occupies only 1 GB. They should not infer 19 GB of free physical storage. They should check the host filesystem’s remaining space and remember that the guest may grow the image when saving new data.

## Before touching your computer

Read each command all the way through. Check the directory or filename first. A **command** is something you type in the terminal; the command output is the evidence you interpret. If a step requires a file or application that is not installed, record **not available** and continue with the conceptual part. Do not invent a result and do not try a more powerful command merely to make the exercise appear to pass.

> **Safety boundary:** Do not run `mkfs`, `fdisk`, `diskpart clean`, `Remove-Disk`, `dd of=/dev/...`, or `qemu-img convert` in a beginner lesson. These can overwrite storage. This chapter is deliberately read-only.

## Windows — PowerShell 7, step by step

Start Windows Terminal and select **PowerShell**, or use **PowerShell 7** directly. Confirm with `$PSVersionTable.PSVersion`. The prompt ending in `>` is where you enter the command; **do not type the prompt itself**. Commands are shown exactly, except for placeholders such as `YOUR_APPROVED_LINUX.iso`, which must be replaced with a real filename before execution.

### 1. Inspect your practice directory

```powershell
Get-ChildItem "$HOME\UmicomLearning\VMs" -ErrorAction SilentlyContinue | Select-Object Name, Length
```

**Expected result and interpretation:** The listed values describe files in your practice folder only.

### 2. Check image information only for an existing image

```powershell
Get-Command qemu-img -ErrorAction SilentlyContinue
qemu-img info "C:\PATH\TO\YOUR-EXISTING-PRACTICE-IMAGE.qcow2"
```

**Expected result and interpretation:** Replace the placeholder with a verified personal practice image. The command is read-only; do not run it against real device paths.


## Linux — terminal, step by step

Open the distribution's Terminal application. The examples assume an ordinary, non-root account. Linux paths use `/` and case-sensitive names on most filesystems; a Windows path beginning `C:\` must not be pasted unchanged into Linux commands.

### 1. Inspect filesystem capacity without modifying it

```bash
df -h "$HOME"
ls -lh "$HOME/UmicomLearning/VMs"
```

**Expected result and interpretation:** `df` reports remaining space on the filesystem; `ls` reports file sizes.

### 2. Inspect image metadata if QEMU tools exist

```bash
qemu-img info "$HOME/UmicomLearning/VMs/EXISTING-PRACTICE-IMAGE.qcow2"
```

**Expected result and interpretation:** The report distinguishes virtual size and disk size if the file and utility exist.


## Guided practice laboratory

1. Draw file → disk image metadata → virtual blocks → guest partitions → guest filesystem.
2. Inspect the size of a harmless local practice file using `Get-Item` or `ls -lh`.
3. Explain why a read-only `qemu-img info` command is safer than converting or formatting an image.
4. Name the evidence required before a storage image can be claimed to boot under QEMU.

**Keep evidence:** Note the date, selected environment, commands entered, expected outcomes and actual outcomes. Omit passwords, tokens, private patient/customer details and unnecessary machine identifiers. A missing or failed step belongs in your report; it is not a reason to hide the error.

## Common problems and how to investigate

| Symptom | Safe investigation |
|---|---|
| Image format cannot be recognised | Confirm that the file is actually a supported image and was downloaded or created by a trusted source. |
| Guest reports disk full despite free host space | The guest filesystem and the host filesystem have separate capacities; diagnose both before changing a disk. |

Never substitute `git reset --hard`, `git clean -fd`, broad permission changes, service shutdown or force-push for diagnosis. Those operations can discard unrelated work.

## Review questions with suggested answers

1. **Can a file represent a disk?**

   *Answer:* Yes. That is the purpose of a disk-image file.

2. **Are virtual size and physical usage always equal?**

   *Answer:* No, especially with sparse formats.

3. **Does a readable disk image prove the OS boots?**

   *Answer:* No. Boot, filesystem and service readiness require independent evidence.


## How this fits into Umicom

We keep the responsibilities clear. **Umicom Kernel** owns privileged boot and hardware behaviour. **Umicom OS** composes the operating-system environment. **Umicom Framework** owns reusable C23/Assembly services, build, VCS, security and application lifecycle contracts. **Bits2Banking** owns the teaching material and isolated laboratories. A lesson should not be mistaken for proof that a production system is ready.

**Next:** 66 — Design safe learner identities and boundaries.
