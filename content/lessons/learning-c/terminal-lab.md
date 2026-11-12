# Lab: create, compile and run C in a terminal

This lab begins with an empty practice folder. You will install tools, write a C file, ask a compiler to build it, and run the result. No IDE or earlier course is required. A terminal is a text window. A shell, such as PowerShell or bash, interprets commands entered there. A compiler translates source text into machine code.

## Setup recap: Install the development tools

Choose the instructions for your operating system below. Install the compiler, CMake, Ninja and debugger before creating the exercise files; then check that their version commands work in the terminal you will use for the lesson.

### Windows

1. Install MSYS2 from [its official installation guide](https://www.msys2.org/). The examples below assume its usual `C:\msys64` location; adapt it if you chose another.
2. Open the **MSYS2 UCRT64** terminal from the Start menu. Follow the site's complete update procedure. If instructed to close the terminal and repeat an update, do so before installing tools.
3. In that terminal, install GCC, CMake, Ninja and GDB:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-gdb
```

`pacman` is MSYS2's package manager. GCC compiles C, CMake describes a build, Ninja performs scheduled build work, and GDB helps inspect a running program. This command installs packages; it does not compile your application.

4. Open PowerShell and make those tools available for this terminal session:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
gdb --version
```

PATH is a list of folders searched for commands. This assignment changes the current process environment, not your saved source or permanent system settings.

### Linux with apt

On a supported Debian/Ubuntu system, use its package manager:

```bash
sudo apt update
sudo apt install build-essential cmake ninja-build gdb
gcc --version
cmake --version
ninja --version
gdb --version
```

`sudo` requests administrative permission for installing system packages. Other Linux distributions use their own package managers. Use a compiler that supports the requested C23 mode and CMake 3.24 or newer for the later repository labs. If an older distribution supplies older tools, update through its supported toolchain procedure. The [GCC standards guide](https://gcc.gnu.org/onlinedocs/gcc/Standards.html) documents `-std=c23`.

## 2. Create a folder and a C file

Use a new folder. The writing commands below replace a file with the same name.

PowerShell:

```powershell
New-Item -ItemType Directory -Path 'C:\umicom-learning\first-c'
Set-Location 'C:\umicom-learning\first-c'
@'
/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: hello.c
 *
 * PURPOSE:
 *   Print a first message from a terminal-built C program.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdio.h>

int main(void)
{
    puts("Hello from Bits2Banking.");
    return 0;
}
'@ | Set-Content -Encoding ascii hello.c
Get-Content hello.c
```

`New-Item` creates the directory. `Set-Location` changes the current directory. The here-string contains literal text, including quotes and line breaks. `Set-Content` saves it and `Get-Content` reads it back. ASCII is sufficient for this example's text and avoids a byte-order marker with older PowerShell versions.

In bash, copy this complete block. The lines between the two `EOF` markers become the C file:

```bash
mkdir -p "$HOME/umicom-learning/first-c"
cd "$HOME/umicom-learning/first-c"
cat > hello.c <<'EOF'
/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: hello.c
 *
 * PURPOSE:
 *   Print a first message from a terminal-built C program.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdio.h>

int main(void)
{
    puts("Hello from Bits2Banking.");
    return 0;
}
EOF
cat hello.c
```

`mkdir -p` creates the practice directory and any missing parent directories. `cd` selects it. The quoted delimiter keeps the C text literal, and `cat hello.c` displays the saved file. The closing `EOF` must be on its own line without indentation. Both shells create the same source; their file-writing commands differ.

## 3. Understand the source

The opening comment explains the file. `#include <stdio.h>` introduces declarations for standard input/output functions. `int main(void)` is the program entry function; `void` says it accepts no parameters here, and `int` describes its completion result. Braces enclose its statements. `puts` prints the string and a newline. `return 0` reports successful completion. A semicolon ends each statement.

## 4. Compile and run separately

PowerShell:

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic -g hello.c -o hello.exe
$LASTEXITCODE
.\hello.exe
$LASTEXITCODE
```

Bash:

```bash
gcc -std=c23 -Wall -Wextra -Wpedantic -g hello.c -o hello
echo $?
./hello
echo $?
```

`-std=c23` selects the language mode. The warning options ask for useful diagnostics. `-g` includes debug information and `-o` names the result. Run only after successful compilation. Expect `Hello from Bits2Banking.` and a completion code of zero. `./` or `.\` identifies a program in the current directory. Compilation does not launch it.

## 5. Make and repair a small mistake

Open `hello.c` in an editor: `notepad hello.c` in PowerShell, or your chosen editor in Linux. Save a reference copy first. Remove the semicolon after `puts`, save and compile. Read the first error and its source line. Restore the semicolon, save and compile again before running. An old executable can survive a failed build; its presence is not evidence that the new source compiled.

If `gcc` is unrecognised, check PATH. If it rejects `c23`, check the compiler version. If it cannot find `hello.c`, display your current folder and its files with `Get-Location` / `Get-ChildItem`, or `pwd` / `ls` in bash.

## Continue from the same example

Compare your file with [the repository's hello.c](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/first-c-programs/hello.c). Continue with [values](03-values-and-calculations.md), [functions](06-functions-with-a-contract.md), then [the C and Assembly lab](terminal-assembly-lab.md). The [Visual Studio transition lab](terminal-to-visual-studio.md) shows how to keep the same source and compiler while adding an IDE.

[Course contents](index.md) · [Deeper terminal guide](../08-system-administration/03-open-powershell-or-linux-terminal.md)
