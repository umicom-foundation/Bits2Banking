# Learning Visual Studio for Umicom development

## What you will learn

Install an editor, open a real repository, change and save a file, build a small
Umicom project, run its tests and investigate one controlled failure. This guide
uses **Visual Studio IDE**, not Visual Studio Code. The repository's existing
compiler remains responsible for producing the executable.

Before starting, complete [Introduction to Computers](../../courses/learning-computer-architecture/index.html)
if files and folders are unfamiliar. The first sections of
[Learning C](../../courses/learning-c/index.html) explain the program text.
You do not need to finish the entire C course to practise opening a file.

## 1. Separate the tools

```text
Visual Studio: edit, navigate, save and read diagnostics
  PowerShell terminal
    CMake: choose build settings
    Ninja: rebuild the affected files
    GCC: compile C             LLD/other linker: combine machine code
    CTest: run registered checks
    GDB: pause and inspect a compatible debug executable
```

An **IDE** is an integrated development environment: several development tools
in one application. A repository stores source and its history. A build directory
stores generated results. Saving text, compiling it and executing it are three
different actions. A successful save alone cannot demonstrate a working program.

## 2. Install Visual Studio

1. Open [Microsoft's installation guide](https://learn.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=visualstudio).
   Choose a supported Visual Studio release and an edition whose licence fits
   your use. Download its installer from Microsoft.
2. Start the installer. Select **Desktop development with C++**. The workload
   name includes C++, but it supplies native development and CMake integration
   used when editing C projects too.
3. Complete installation and any requested restart. Start Visual Studio.
4. Select **Continue without code** if the start screen offers it. Later use
   **File > Open > Folder** to open a repository. Do not create a new solution
   that replaces its existing `CMakeLists.txt`.

The workload's Microsoft compiler is not automatically the compiler selected
by Umicom's presets. Keep the established MSYS2 UCRT64 GCC, CMake and Ninja
installation. In the **MSYS2 UCRT64** terminal, install missing tools with:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-gdb
```

Use MSYS2's documented full-update procedure first if the installation is old;
do not mix packages from different MSYS2 environments. A Windows PowerShell
window does not understand `pacman` unless its environment has been configured
for MSYS2, so run that installation command in the named terminal.

## 3. Open the small compiler repository

1. Choose **File > Open > Folder** and select `C:\umicom\umicom-c`.
2. Find `tools/main.c` in Solution Explorer's folder view. Double-click it.
3. Locate `int main(int argc, char **argv)`. It receives the command-line words.
4. Follow the `run` and `execute` variables to the call to `umc_execute`.
5. Open `include/umicom_c/umicom_c.h` beside it. The declaration explains the
   arguments and result types; the definition in `src/vm.c` performs the work.

An editor may start a CMake configuration when opening a folder. Check the
selected preset and output before using a build button. This project uses
`windows-ucrt64-debug` on Windows. If an automatic configuration used another
compiler, stop that operation and use the terminal workflow below. Do not
change an old build directory's compiler to make it fit.

[Microsoft's preset guide](https://learn.microsoft.com/en-us/cpp/build/cmake-presets-vs?view=msvc-170)
explains preset support and version differences. The project commands below
remain the reference if your IDE version cannot interpret a preset.

## 4. Build, test and run in the terminal

Open **View > Terminal** and select a PowerShell terminal, or use a separate
PowerShell window. Run each command separately and stop if `$LASTEXITCODE` is
nonzero. Logs get a new directory every session.

```powershell
Set-Location "C:\umicom\umicom-c"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
$LogRoot = "C:\umicom\_local\logs\visual-studio-$(Get-Date -Format yyyyMMdd-HHmmss)"
New-Item -ItemType Directory -Force $LogRoot
cmake --preset windows-ucrt64-debug -DBUILD_TESTING=ON 2>&1 | Tee-Object "$LogRoot\configure.log"
$LASTEXITCODE
cmake --build --preset windows-ucrt64-debug --parallel 2 2>&1 | Tee-Object "$LogRoot\build.log"
$LASTEXITCODE
ctest --preset windows-ucrt64-debug --output-on-failure --no-tests=error --output-log "$LogRoot\tests.log"
$LASTEXITCODE
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" --version
```

This small project is a starting point; it does not rebuild all Umicom
Applications. Keep its build directory between edits so Ninja can use the
dependency information it already recorded. A shared header change can
correctly rebuild several files even if you edited only one file.

## 5. Create and save a program

Choose **File > New > File**, select a text file and enter:

```c
/*-----------------------------------------------------------------------------
 * Umicom C Learning Example
 * File: answer.uc
 *
 * PURPOSE:
 *   Evaluate a small expression with the Umicom C arithmetic interpreter.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
int main(void) { return 6 * 7; }
```

Choose **Save As**, create `C:\umicom\examples\umicom-c` or another location
you prefer, and save `answer.uc` using UTF-8 without a byte-order mark. Make
sure Windows has not added `.txt` to its name. The file belongs to you; no
application-specific AppData directory is required.

```powershell
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" run "C:\umicom\examples\umicom-c\answer.uc" --max-steps 4
```

Expect `Result: 42`. Edit 7 to 8, save with **Ctrl+S**, and run the same command:
expect 48. You changed input to the interpreter, so this exercise does not
require rebuilding the interpreter itself. Editing `src/vm.c` would require
rebuilding it. This distinction avoids unnecessary work.

## 6. Debug the interpreter with its matching debugger

A **breakpoint** pauses a process before a selected instruction. Debug symbols
connect machine instructions to source lines. GCC's Windows debug information
is not the same as a Microsoft PDB; do not assume Visual Studio's default F5
configuration can debug this GCC executable. Use the matching UCRT64 GDB in
the terminal for this workflow:

```powershell
& "C:\msys64\ucrt64\bin\gdb.exe" --args ".\build\windows-ucrt64-debug\bin\umicom-c.exe" run "C:\umicom\examples\umicom-c\answer.uc" --max-steps 4
```

At the `(gdb)` prompt type:

```text
break main
run
print argc
next
break umc_execute
continue
print count
print fuel
backtrace
continue
quit
```

`argc` counts the executable name and its arguments; this invocation has five.
`count` should be four for this expression and `fuel` should be four. `next`
advances one source line; `backtrace` lists active function calls. If GDB says
symbols are missing, confirm that this is the Debug executable from the chosen
build directory. These commands debug the compiler/interpreter process on the
host, not an Umicom Kernel guest.

## 7. Investigate a deliberate failure

Run the expression again with `--max-steps 3`. It should report exhaustion and
return code 1 without printing a result. Open `src/vm.c`; find the comparison
between the instruction position and `fuel`. Disassembly reveals four
instructions, including the final return. The rejected run is the expected
behaviour, not an instruction to remove the budget check.

After a genuine code fix, rebuild the affected target and run its focused
regression, for example:

```powershell
cmake --build --preset windows-ucrt64-debug --target umicom-c --parallel 2
ctest --preset windows-ucrt64-debug -R "^umicom\.c\.cli-budget$" --output-on-failure --no-tests=error
```

A focused pass does not replace wider release testing. If the executable was
removed by endpoint protection, inspect its recorded detection instead of
assuming a missing-file error is a compiler defect.

## 8. Move to the larger projects

Use the same open-folder and terminal habits for Framework and Applications.
Choose each repository's documented preset. Keep `.c` files and public headers
in their source folders; do not copy generated binaries into source control.
For Kernel use its RISC-V cross-toolchain and QEMU guide; F5 on its ELF is not
a Windows launch. For OS image development use the Linux build-host workflow.

**Exercise:** you save `answer.uc`, but execution still prints the old answer.
What do you check first? **Answer:** confirm the saved full path, the extension,
and the path passed to `run`. Rebuilding the whole Framework cannot correct a
command that reads the wrong file.

Continue with [Umicom C's execution guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/execution-guide.md),
then [Umicom Kernel's first session](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_SYSTEM_SESSION.md).
Source links describe the matching repository edition; if a new page is not
published yet, read the same relative path in your local checkout.

## Continue from a terminal exercise

The [terminal-to-Visual-Studio lab](../learning-c/terminal-to-visual-studio.md) starts with one small C program, keeps its compiler explicit, and follows configure, build, test and debugger commands. Its setup recap lets you begin without completing another course first.
