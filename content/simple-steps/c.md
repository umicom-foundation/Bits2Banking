<!--
Umicom Bits2Banking
File: content/simple-steps/c.md

PURPOSE:
Write, compile, run and adjust a C program for a coffee recipe.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# 5–7. Write, build and run a C program

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Suppose your coffee recipe calls for four minutes of brewing. Your timer asks for seconds. You’ll write a program that converts the time and shows the number to enter.

## 5. Write the program

1. In PowerShell, type these lines one at a time. Choose **Yes** if Notepad asks to create `coffee.c` in the practice folder you made in Step 3.

   ```powershell
   Set-Location -LiteralPath (Join-Path $env:USERPROFILE 'Bits2Banking-Practice\coffee-timer')
   notepad .\coffee.c
   ```

2. Paste the C code into Notepad and press **Ctrl+S**. If you see a **Save As** window, choose **All files** and use the name `coffee.c`.

   ```c
   #include <stdio.h>

   int main(void)
   {
       // Convert the recipe's minutes into seconds for the timer.
       const int brew_minutes = 4;
       const int brew_seconds = brew_minutes * 60;
       printf("Brew for %d seconds.\n", brew_seconds);
       return 0;
   }
   ```

   `main` is where the program starts. The two `int` lines store whole numbers. The `*` multiplies minutes by 60. The `#include` line makes `printf` available so the program can put the number where `%d` appears. `\n` ends the output line, and `return 0` reports a successful finish.

3. Back in PowerShell, type `Get-Item .\coffee.c`. The name should end in `.c`. Look for `coffee.c.txt` if PowerShell cannot find it, then save it again using **All files**.

## 6. Build the program

1. Stay in the same PowerShell window. Type these lines. If MSYS2 is installed elsewhere, change the folder in the first line to match Step 4.

   ```powershell
   $ucrt = 'C:\msys64\ucrt64\bin'
   $env:Path = "$ucrt;$env:Path"
   & "$ucrt\gcc.exe" -std=c23 -Wall -Wextra .\coffee.c -o .\coffee.exe
   ```

   GCC turns `coffee.c` into a runnable program. `-std=c23` selects the version of C and `-o` gives the output file its name. `-Wall` and `-Wextra` turn on helpful warnings.

2. A successful compile usually prints nothing. Type `Get-Item .\coffee.exe` to check that the file exists. If GCC shows an error, fix the first reported line, save, and try the compile command again before going on. [GCC’s C standards guide](https://gcc.gnu.org/projects/c-status.html#c23)

## 7. Run it and change one thing

1. Type this in PowerShell.

   ```powershell
   .\coffee.exe
   ```

   The program should print `Brew for 240 seconds.` The `.\` prefix tells PowerShell to run a file in the current folder.

2. In Notepad, change `brew_minutes = 4` to `brew_minutes = 3`. Save. Run the compile command from Step 6 again, then run `.\coffee.exe`. You should now see `Brew for 180 seconds.`

[Previous step — Set up the C tools](toolchain.md) · [Next step — Save your work with Git](git-local.md) · [Full first C program lesson](../community/lessons/09-build-your-first-c-program.md) · [Learning C course](../courses/learning-c/index.html)

<!-- Earlier demonstration code is retained for comparison. The active steps use an everyday task and check its result.

```c
#include <stdio.h>

int main(void)
{
    printf("%d\n", 2 + 1);
    return 0;
}
```

```powershell
gcc apples.c -o apples.exe
.\apples.exe
```
-->
