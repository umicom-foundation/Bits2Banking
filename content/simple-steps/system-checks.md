<!--
Umicom Bits2Banking
File: content/simple-steps/system-checks.md

PURPOSE:
Read system details and available memory and storage.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Step 2. Check your computer

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Open PowerShell 7. Run one command at a time. These checks show which tools fit your computer and how much room you have to install them.

1. Check your Windows edition and choose the right tool installer.

   ```powershell
   Get-CimInstance Win32_OperatingSystem | Select-Object Caption, OSArchitecture
   [System.Runtime.InteropServices.RuntimeInformation]::OSArchitecture
   ```

   The first command shows the edition and whether Windows is 64-bit. The second gives you the architecture for choosing tools. Use the x64 instructions in Step 4 when it shows `X64`. If it shows `Arm64`, open the Windows on Arm guide in that step. [Microsoft’s architecture reference](https://learn.microsoft.com/dotnet/api/system.runtime.interopservices.runtimeinformation.osarchitecture)

2. Check your processor.

   ```powershell
   Get-CimInstance Win32_Processor | Select-Object Name, NumberOfCores
   ```

   `Name` shows your processor model. `NumberOfCores` shows how many physical cores it has.

3. Check how much working memory (RAM) Windows reports.

   ```powershell
   [math]::Round((Get-CimInstance Win32_ComputerSystem -ErrorAction Stop).TotalPhysicalMemory / 1GB, 1)
   ```

   A result of `16` means about 16 GiB of RAM as reported by Windows. Firmware can reserve memory, so the installed capacity may differ.

4. Check how much storage is free on the C drive.

   ```powershell
   Get-PSDrive -Name C
   ```

   Read the value under `Free (GB)`. If you plan to install tools on another drive, use its letter in place of `C`.

If PowerShell cannot read your specs, search **About your PC** from Start. Look under **Device specifications** and **Windows specifications**. The **System type** entry there also distinguishes an x64 PC from an ARM-based PC.

[Previous: Step 1. Install PowerShell 7](powershell-setup.md) · [Next: Step 3. Make a practice folder](work-folder.md)

[Full lesson on what is inside a computer](../lessons/01-computers/01-inside-a-computer.md)
