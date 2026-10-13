# Chapter 276 — Install the C23 compiler, CMake and Ninja on Windows

**Bits to Banking · Absolute Beginner Course · Unit 4: Building real software**  
**Time:** 35–70 minutes depending on downloads · **Requirements:** Windows x64, internet access, installation permissions as required.

## Three tools, three responsibilities

A **compiler** translates C source into object code. **GCC** is one compiler we use for C23. A **build configuration tool**, CMake, reads `CMakeLists.txt` and prepares build instructions. **Ninja** executes those build instructions efficiently. A compiler is not a text editor; an editor is where we write code, and the compiler is what checks and translates it.

We use **MSYS2 UCRT64** on Windows because it provides a consistent native GCC toolchain and its dependencies. UCRT64 means that the resulting Windows programmes use Microsoft's Universal C Runtime. Do not confuse an MSYS2 UCRT64 shell with the PowerShell 7 shell; we may install tools in one environment and invoke them from the other.

## Step 1 — Check existing installations

Open PowerShell 7:

```powershell
cmake --version
ninja --version
```

If either command is not found, that is not a code error; we need to install the tool. Check whether MSYS2 exists at the common default path:

```powershell
Test-Path "C:\msys64\ucrt64\bin\gcc.exe"
```

`True` means that exact file exists; `False` means it does not. The file can be installed elsewhere, so this test is not a universal MSYS2 detector.

## Step 2 — Install MSYS2

Open the official site **https://www.msys2.org/** and use its documented Windows installer. The common installation folder is `C:\msys64`, which we use in later examples. If your institution manages software installation, follow its policies.

After installation, open **MSYS2 UCRT64** from the Start menu (not the generic MSYS shell). It uses an environment appropriate for building native Windows applications. If the package database prompts you to update, follow the official MSYS2 update instructions, closing and reopening the UCRT64 terminal when told to.

Inside the **MSYS2 UCRT64 terminal**, run:

```bash
pacman -Syu
```

Follow prompts; close and reopen the required MSYS2 terminal if the update tool requests it, and repeat updating as the official MSYS2 documentation requires. Then install GCC, CMake and Ninja packages for UCRT64:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

`pacman` is an MSYS2 package manager, not a normal PowerShell command. Do not enter these commands in the wrong shell.

## Step 3 — Return to PowerShell and check the actual executables

Close the MSYS2 terminal after installation. Open PowerShell 7 and run:

```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" --version
& "C:\msys64\ucrt64\bin\cmake.exe" --version
& "C:\msys64\ucrt64\bin\ninja.exe" --version
```

The `&` is PowerShell's **call operator**; it runs the quoted executable path. Simply writing `"C:\msys64\ucrt64\bin\gcc.exe"` displays a string instead of executing the programme. The versions may differ from your teacher's versions.

For the current PowerShell window only, place UCRT64 tools at the front of the command search path:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
```

This is an **interactive environment setting**, not a `.ps1` implementation script. It lasts for that PowerShell process and children, not permanently for the whole computer. Now `gcc --version`, `cmake --version` and `ninja --version` should resolve to the UCRT64 versions. `Get-Command gcc,cmake,ninja | Select-Object Name,Source` confirms which executables were selected.

## C23 language support

Older compilers may recognise an earlier C language standard but not ISO C23. Our native laboratory requests C23 through CMake. If configure says the compiler does not support the required standard, check `gcc --version`, verify that the UCRT64 compiler was selected, and update through the supported MSYS2 package manager rather than changing source requirements to an older dialect.

**Practice:** Explain which tool compiles, which configures and which executes the build plan. Record the *actual* paths and versions without guessing them. No code changes are needed yet.

**Next:** [Build the C23 Notes programme and run its tests](277-build-and-test-first-c23-notes-program.md).
