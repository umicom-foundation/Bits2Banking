<!--
Umicom Bits2Banking
File: content/simple-steps/toolchain.md

PURPOSE:
Set up the Windows compiler and build tools used in the starter route.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# 4. Set up the C development tools

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Install GCC to build the first C program. Install CMake and Ninja alongside it for the projects that follow. These steps use MSYS2 UCRT64 on Windows x64. If your system shows ARM64, follow the Windows on Arm instructions. [MSYS2 Windows on Arm guide](https://www.msys2.org/docs/arm64/)

1. Download and run the **x86_64** installer. Keep the default folder `C:\msys64` if this is your first installation. If you already have MSYS2, use its existing folder. [Official MSYS2 installer](https://www.msys2.org/)
2. Open **MSYS2 UCRT64** from the Start menu. Type this command there and press Enter.

   ```bash
   pacman -Suy
   ```

   If the update asks to close the terminal, confirm it. Open **MSYS2 UCRT64** again and run `pacman -Suy` again so it can finish updating. [MSYS2 update guide](https://www.msys2.org/docs/updating/)

3. In the same **MSYS2 UCRT64** window, run these three commands one at a time. Press Enter when prompted to install the listed packages.

   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc
   pacman -S --needed mingw-w64-ucrt-x86_64-cmake
   pacman -S --needed mingw-w64-ucrt-x86_64-ninja
   ```

4. Switch to **PowerShell 7**. Type the lines below. If you installed MSYS2 somewhere else, use that folder in the first line and keep `\ucrt64\bin` at the end.

   ```powershell
   $ucrt = 'C:\msys64\ucrt64\bin'
   $env:Path = "$ucrt;$env:Path"
   & "$ucrt\gcc.exe" --version
   & "$ucrt\cmake.exe" --version
   & "$ucrt\ninja.exe" --version
   ```

**Check your result.** You should see version information from all three tools. If PowerShell cannot find one, check your installation folder and repeat the matching package command in UCRT64. The `Path` change applies to this PowerShell window.

[Previous step — Make a practice folder](work-folder.md) · [Next step — Write a C program](c.md) · [Full Windows toolchain lesson](../community/lessons/08-set-up-the-c-toolchain.md)
