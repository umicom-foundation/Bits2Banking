# Chapter 128 — What happens when a computer runs out of storage?

*System Administration From Zero · Stage 10 · Umicom Foundation*

A computer can have a fast processor and plenty of memory yet still fail to save a document because its disk is full. A database may refuse new transactions when it cannot write data or logs. An application can appear healthy until it needs additional space.

This is why administrators monitor **storage capacity** and **filesystem health**.

## Three different quantities

A disk or volume has a total capacity, an amount already used and an amount available. Some filesystems reserve space or apply quotas, so the amount a particular user can write may be smaller than the simple free-space figure.

A **filesystem** organises files and directories on storage. A **volume** is a logical storage area. A **partition** is a defined region of a disk. These words are related but not interchangeable.

## View your drives on Windows

Open PowerShell and type:

```powershell
Get-PSDrive -PSProvider FileSystem |
    Select-Object Name, Root, Used, Free
```

This reads drive information. The free-space values are in bytes. For a quick friendlier view of one drive, you can use:

```powershell
Get-Volume | Select-Object DriveLetter, FileSystem, Size, SizeRemaining
```

`Get-Volume` is available on supported Windows systems. It may show special or system volumes, some without drive letters. **Do not format, delete or resize a volume as a classroom exercise.**

## View filesystems on Linux

Open a Linux terminal and enter:

```bash
df -h
```

`df` shows how much filesystem space is used and available. The `-h` option makes sizes easier to read. A full disk warning should prompt a review of the affected filesystem, log growth and expected application usage.

## Space is not the same as health

A disk can have free space but still experience hardware faults or slow input/output operations. Conversely, a small filesystem might be almost full without indicating a failed physical disk. Monitoring needs both capacity and relevant error evidence.

A production database may also have storage allocated to data, transaction logs, temporary files and backups. Free space on the wrong volume may not help the failing component.

## A practical question

Umicom Notes cannot save new records. Its data volume is 99% full. Would it be wise to delete the log folder immediately? Usually not. Those logs may contain essential failure evidence, and the folder may be controlled by a retention policy. Investigate approved cleanup, log rotation, additional capacity and recovery arrangements.

**Exercise:** Record the free space of one practice drive or filesystem. Explain the difference between *insufficient space*, *a slow storage device* and *a missing path*. Each produces a different next step in troubleshooting.
