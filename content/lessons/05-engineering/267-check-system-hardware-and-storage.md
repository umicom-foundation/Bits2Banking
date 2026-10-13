# Chapter 267 — Inspect Windows, the processor, memory and storage

**Bits to Banking · Absolute Beginner Course · Unit 2: System administration**  
**Time:** 30 minutes · **Requirements:** a Windows computer and PowerShell. All commands are **read-only**.

## What is system administration?

A **system administrator** keeps computers usable, secure, updated and recoverable. Before installing a compiler or investigating a failed build, a good administrator gathers evidence about the machine. The **operating system** is the software that manages programmes, memory, disks, accounts and devices. The **CPU** executes instructions; **RAM** holds temporary working data; **storage** retains files after power is removed.

We will use built-in Windows commands that report information without changing settings. You do not need to understand every reported property yet. Start by recognising the hardware categories and whether your machine has enough free space to complete a build.

## Step 1 — Identify Windows and its architecture

```powershell
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion, OsArchitecture
```

`Get-ComputerInfo` collects details; `Select-Object` reduces the output to three columns. Look for **64-bit** or **x64**, which matters when choosing a compiler. This query may take several seconds. Your Windows edition and version will differ from the instructor's.

A shorter check is:

```powershell
[System.Environment]::OSVersion.Version
```

The first command is preferable when you want the Windows edition and architecture together.

## Step 2 — Read the processor and core count

```powershell
Get-CimInstance Win32_Processor | Select-Object Name, NumberOfCores, NumberOfLogicalProcessors
```

`Win32_Processor` is a Windows management class. **Cores** are CPU execution resources. **Logical processors** are scheduling units visible to Windows; a processor may present more logical processors than physical cores. The name and numbers are not a benchmark and do not automatically prove that one machine is faster than another.

## Step 3 — Check installed RAM

```powershell
[math]::Round((Get-CimInstance Win32_ComputerSystem).TotalPhysicalMemory / 1GB, 2)
```

The result is a number in units that PowerShell labels with the `1GB` binary constant (1,073,741,824 bytes). It is useful for planning how many builds or browser tabs you can run at once. Installed RAM is different from **free** RAM: Windows uses some memory for itself and running programmes.

## Step 4 — View drives and free space

```powershell
Get-PSDrive -PSProvider FileSystem
```

This displays accessible filesystem drives and the reported free and used capacity where available. Do not confuse the drive letter with the amount of free space. A low-space drive may cause CMake to fail while producing many temporary `.obj` files.

For an easy-to-read summary of fixed local disks, try:

```powershell
Get-CimInstance Win32_LogicalDisk -Filter "DriveType=3" |
    Select-Object DeviceID, VolumeName, Size, FreeSpace
```

The second command produces byte counts; Windows settings can show friendlier units. A shared or network drive may be reported differently, so confirm its availability before choosing it as a build directory.

## Step 5 — Locate programmes the shell can run

```powershell
Get-Command pwsh, git, gh, cmake, ninja -ErrorAction SilentlyContinue |
    Select-Object Name, Source
```

A missing row means the command was not found in the current command search path; it does **not** prove that the software has never been installed. Reopen PowerShell after installation. Later, the course shows exact GCC paths for MSYS2 UCRT64.

## Practice record

Create a *private* notes page with your Windows edition, CPU name, RAM, free space on your work drive and which tools are available. Do not post machine serial numbers, account IDs or security configuration in a public issue. The class can compare broad CPU architecture and build capacity without collecting unnecessary personal information.

**Review:** Why is free disk space relevant to CMake? What is the difference between RAM and storage? Why might `Get-Command git` produce no result just after installing Git? Why should every diagnostic begin with a read-only check?

**Next:** [Understand users, permissions and safe administration](268-users-permissions-and-safe-administration.md).
