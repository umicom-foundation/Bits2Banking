# Episode 91 — Read your computer's information safely

**Bits to Banking · Umicom Foundation · Beginner video series**  
**Companion lessons:** Chapters 267–271 · **Suggested duration:** 10–13 minutes.

## Opening — Why administration begins with evidence (0:00–2:00)

**On screen:** Show a simple computer information card for Windows, CPU, RAM, storage and running processes. Use fictional values rather than a private system identifier.

**Narration:** “Before changing a computer, an administrator needs to know what is installed, what is available and which resources are under pressure. A build that runs out of disk space is not fixed by editing C code.”

## Inspect Windows and CPU (2:00–5:00)

In ordinary PowerShell, type:

```powershell
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion, OsArchitecture
Get-CimInstance Win32_Processor | Select-Object Name, NumberOfCores, NumberOfLogicalProcessors
```

Explain `Select-Object` as “show only these columns”. Do not interpret the number of logical processors as a direct speed rating. Students should record broad machine specifications only; no serial numbers.

## Inspect RAM and storage (5:00–8:00)

```powershell
[math]::Round((Get-CimInstance Win32_ComputerSystem).TotalPhysicalMemory / 1GB, 2)
Get-PSDrive -PSProvider FileSystem
```

**Narration:** “Memory and storage are not interchangeable. RAM is temporary working space; storage retains the source, compiler and build outputs. A developer can have a powerful CPU but still have a build fail because the disk is full.”

## Inspect processes and explain permissions (8:00–11:00)

```powershell
Get-Process | Select-Object -First 8 Name, Id
whoami
```

Explain standard user versus administrator. **Do not** demonstrate stopping a random process, disabling an antivirus or changing access-control lists.

## Linux comparison and closing (11:00–13:00)

Show the same concepts through `pwd`, `lscpu`, `df -h`, `free -h`, and `whoami` in a Linux terminal. Emphasise that the interface changes but the engineering questions remain the same.

**Activity:** Students produce a small five-field machine readiness note and distinguish “read-only diagnosis” from “system modification”.
