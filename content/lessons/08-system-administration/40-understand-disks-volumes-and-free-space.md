# Chapter 40 — Understand disks, volumes, filesystems and free space

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** beginners of any age; younger learners should use a supervised computer.  
**Suggested study time:** 55–80 minutes.  
**Before this chapter:** Chapters 5–7 and 32: paths, drives and file systems.

## The question this chapter answers

**How can I understand and check this part of a computer without accidentally changing something important?**

## Why this matters

A disk is a storage device. A partition is a defined region on a disk. A volume is a logical storage unit that often has a drive letter or mount point. A filesystem organises files within the volume. Beginners often use the word 'drive' for all four, which can lead to wrong conclusions when a backup is full or an application cannot write.

Our exercises only inspect storage. Formatting, repartitioning, resizing and clearing disks can destroy information, so they are excluded. The goal is to answer: where does the learning project live, how much space is available, and which device actually holds it?

## A useful mental model

Imagine a large filing cabinet (disk). You divide it into drawers (partitions). A drawer might be labelled C: (volume or mount point). Inside it, an index and folders describe where papers belong (filesystem). Modern systems complicate the analogy with virtual disks, network shares, encryption and storage pools; that is why we inspect actual mappings rather than guessing.

## Key terms, explained before using them

| Term | Meaning |
|---|---|
| **Block device** | Storage exposed as addressable units or sectors. |
| **Partition** | A defined range on a physical or virtual disk. |
| **Volume** | A logical container for a filesystem. |
| **Filesystem** | Rules and metadata that organise directories and file content. |
| **Mount point** | A directory or letter through which a filesystem is accessed. |
| **Free space** | Capacity available for new data, subject to quotas and permissions. |

## Read this before typing commands

> **Authorisation and safety:** Use your own computer or an explicitly authorised learning environment. Start with an ordinary user account. Commands that install software, change access, restart services or modify networks are outside this exercise unless the text clearly identifies a harmless practice-file operation. You never need to disable a firewall or change system permissions to complete this chapter.

> **Reading code blocks:** Open PowerShell 7 on Windows (`pwsh`) or a terminal on Linux. Type the line inside the block, not the example prompt. Run one command at a time. Some examples contain multiple interactive commands separated by semicolons; verify their results individually. These are interactive commands, **not scripts added to Umicom**.

## Windows — PowerShell 7 practice

Do these steps on Windows. If you use Linux, read them for comparison and continue below. A missing command means that a tool or module may be unavailable; it is not a reason to bypass computer policy.

### Step 1 — Show filesystem drives

```powershell
Get-PSDrive -PSProvider FileSystem
```

**Expected result:** Drive names, roots and free/used figures appear where supported.

**Why this command matters:** Some drives are network shares rather than physical disks. A mapped drive can disappear when a new session starts.

**Safety and troubleshooting:** Do not infer a disk's health from free space alone.

### Step 2 — Inspect volumes without changing partitions

```powershell
Get-Volume | Select-Object DriveLetter, FileSystem, HealthStatus, SizeRemaining, Size
```

**Expected result:** Volumes and their reported attributes appear.

**Why this command matters:** This shows Windows logical volumes, not necessarily one row per physical disk. Some entries have no drive letter.

**Safety and troubleshooting:** Some systems restrict this command; do not switch to an elevated shell merely to finish the exercise.

### Step 3 — Read the current workspace location

```powershell
Get-Location
```

**Expected result:** The working directory appears.

**Why this command matters:** Compare its drive letter to the volume inventory to identify likely storage. Symlinks, junctions and network shares can alter the true location.

**Safety and troubleshooting:** If you use Z: or another mapped share for Umicom sources, confirm it is connected before building.

### Step 4 — Inspect your own home-directory folders

```powershell
Get-ChildItem -LiteralPath $HOME -Directory | Select-Object -First 10 Name
```

**Expected result:** Only the first ten folder names in your own profile appear.

**Why this command matters:** This bounds output and avoids scanning another person's directories. A folder name does not reveal its exact size.

**Safety and troubleshooting:** Never run a cleaning command based solely on a folder's name.

## Linux — terminal practice

Run these in a Linux terminal on an authorised computer or VM. Some distributions do not install the same commands. An unavailable check should be reported as unavailable; do not assume an unobserved result is successful. No command below requires `sudo`.

### Step 1 — Read disk, filesystem and mount columns

```bash
lsblk -o NAME,SIZE,FSTYPE,MOUNTPOINTS
```

**Expected result:** A tree of storage devices and mount points appears.

**Why this command matters:** Modern Linux may use encrypted layers, LVM or loop devices; the parent-child structure is significant.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 2 — Check space where the current directory lives

```bash
df -h .
```

**Expected result:** The filesystem containing the current directory is displayed with free capacity.

**Why this command matters:** A mount inside another directory may live on a different disk. Do not assume /home and / share capacity.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 3 — Identify the current directory

```bash
pwd
```

**Expected result:** Your working path appears.

**Why this command matters:** Use it to explain where a later file copy would go.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

## Worked Umicom support scenario

A beginner has 100 GB free on C: but the Umicom build fails when writing to Z:. The person checked the wrong filesystem. They inspect the repository path and both volume inventories. A write failure can also result from permissions or disconnection, so the diagnosis remains provisional until those checks are performed.

### A disciplined investigation sequence

1. **Describe the symptom precisely.** Identify what failed and the expected result.
2. **Identify the environment.** Record current account, machine class, working directory and observation time; redact private identifiers.
3. **Run the smallest relevant read-only check.** Choose evidence that distinguishes two possible causes.
4. **Compare results with the requirement.** Missing, blocked or outdated checks are not successful checks.
5. **Separate fact and interpretation.** Label hypotheses explicitly.
6. **Propose, do not silently apply, a change.** State approval, effect, rollback and validation criteria.

## Common mistakes and how to respond

| Incorrect assumption | Better engineering response |
|---|---|
| Free space means the disk is healthy. | Health depends on hardware, filesystem integrity, performance and error logs, not just capacity. |
| Deleting the build directory is always safe. | Some repositories have generated evidence or user-created files in the build tree. Inspect and back up before removing anything. |
| All visible drives are physical disks. | Drive letters and mount points may refer to virtual, removable or network storage. |

## Practical exercises — try these before opening the answers

1. Create a storage map on paper.
2. Explain a network drive failure.
3. Propose safe space investigation.

<details>
<summary><strong>Suggested answers and reasoning</strong> — open after attempting the exercises</summary>

1. **Create a storage map on paper.** Record one project path, its drive or mount point, its filesystem and available space.
2. **Explain a network drive failure.** A mapped share may be unavailable in an unattended process even when a user can open it interactively.
3. **Propose safe space investigation.** Check the intended volume, identify large owned test artefacts and obtain approval; do not start with deletion.

</details>

## Engineering connection: Umicom Framework

Umicom builds should be independent of a user's current working directory and must not assume build artefacts are on the same volume as source. Native packaging and installers should report target space requirements and errors accurately.

## Short support-note template

```text
Observation ID: PRACTICE-____
Observed at (include timezone):
Authorised machine or learning environment:
User-visible symptom:
Command or test (never paste credentials):
Observed result:
What remains unknown:
Proposed next safe check:
Approval required before any change:
```

## References and further study

- https://learn.microsoft.com/powershell/module/storage/get-volume
- https://man7.org/linux/man-pages/man8/lsblk.8.html

**Course progression:** [Chapter 39](39-accounts-groups-and-scheduled-work.md) → **Chapter 40** → [Chapter 41](41-make-and-verify-a-recoverable-backup.md).

---

**Safety reminder:** An honest *not available*, *not authorised* or *not run* result is better than a fabricated pass. No real system changes or remote repository writes are required.
