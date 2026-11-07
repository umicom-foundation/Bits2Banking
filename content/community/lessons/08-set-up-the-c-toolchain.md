# Set up the Windows C toolchain

Use one consistent compiler, build system and library environment.

**Before you start:** Windows, internet access and PowerShell. No programming experience is required. A compiler turns source text into machine code; the toolchain is the set of programs used to build and inspect it.

[Community learning route](../index.md) · [Printable HTML](../handouts/08-set-up-the-c-toolchain.html)

## The tools we will use

GCC compiles C source. A linker joins compiled pieces into an executable. CMake describes the project and generates build instructions. Ninja follows those instructions. CTest runs the checks registered by CMake. MSYS2 supplies these tools and libraries on Windows.

UCRT64 is the MSYS2 environment used for these examples. It supplies 64-bit Windows programs using the Universal C Runtime. Keep its compiler and libraries together rather than mixing tools from unrelated MSYS2 environments.

## 1. Install or locate MSYS2

Use the official MSYS2 installer linked below. C:\msys64 is the path in these examples. If you already have MSYS2 elsewhere, use that location; do not install another copy just to match a lesson. Open MSYS2 UCRT64 from Start. The next commands belong in that Bash terminal, not in PowerShell.

## 2. Update and install the basic tools

```bash
pacman -Syu
```

pacman is the package manager. Read its instructions. If asked to close the terminal during the update, close it, reopen UCRT64 and run pacman -Syu again. Once the update finishes, install the basic build tools:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-gdb
```

--needed avoids reinstalling packages already current. GDB is a debugger: a tool for pausing and examining a running program. The first console lesson does not need GTK4 or SQLite. Install those later when a specific project requires them.

## 3. Return to PowerShell

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
Get-Command gcc, cmake, ninja, ctest
gcc --version
cmake --version
ninja --version
ctest --version
```

This PATH change applies to this terminal and programs started from it. It does not permanently change Windows settings. Check that the tools resolve from the intended UCRT64 bin folder. A compiler version alone does not prove every C23 feature is supported; the small examples here use a conservative subset.

## If a tool is missing

Check your MSYS2 location and confirm you installed the UCRT64 package names. In PowerShell, an executable path in quotes needs the call operator &: & "C:\msys64\ucrt64\bin\gcc.exe" --version. The & tells PowerShell to run the named program rather than treat its path as text.

## Your turn

Record each tool version in your practice notes. Explain which tool compiles, which one generates build instructions and which one runs tests.

## Continue when you are ready

[Previous: Share a practice project and clone it](07-share-and-clone-a-project.md) · [Next: Write, compile and run a C program](09-build-your-first-c-program.md)

[Explore the related course](../../courses/learning-c/index.html). You can finish this exercise without leaving this page.

## Further reading

- [MSYS2 installer](https://www.msys2.org/)
- [MSYS2 environments](https://www.msys2.org/docs/environments/)
- [Updating MSYS2](https://www.msys2.org/docs/updating/)

[Video teaching script](../video-scripts/08-set-up-the-c-toolchain.md) · [Short community message](../messages/08-set-up-the-c-toolchain.md)
