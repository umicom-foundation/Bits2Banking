# Video script: Set up the Windows C toolchain

**Aim:** Use one consistent compiler, build system and library environment.

**Preparation:** Windows, internet access and PowerShell. No programming experience is required. A compiler turns source text into machine code; the toolchain is the set of programs used to build and inspect it. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/08-set-up-the-c-toolchain.md)

## Opening words

Next, we will take this topic one step at a time: set up the windows c toolchain. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Show the two terminal windows with labels: UCRT64 Bash for package installation and PowerShell for the following builds.

## Scene 2

Explain each tool in one sentence before installing it. Pause the lesson while packages download.

## Scene 3

Return to PowerShell and inspect Get-Command. Demonstrate & with the quoted compiler path.

## Walkthrough and pauses

### The tools we will use

**Say:** GCC compiles C source. A linker joins compiled pieces into an executable. CMake describes the project and generates build instructions. Ninja follows those instructions. CTest runs the checks registered by CMake. MSYS2 supplies these tools and libraries on Windows.

**Say:** UCRT64 is the MSYS2 environment used for these examples. It supplies 64-bit Windows programs using the Universal C Runtime. Keep its compiler and libraries together rather than mixing tools from unrelated MSYS2 environments.

### 1. Install or locate MSYS2

**Say:** Use the official MSYS2 installer linked below. C:\msys64 is the path in these examples. If you already have MSYS2 elsewhere, use that location; do not install another copy just to match a lesson. Open MSYS2 UCRT64 from Start. The next commands belong in that Bash terminal, not in PowerShell.

### 2. Update and install the basic tools

**On screen — type one line at a time:**

```bash
pacman -Syu
```

Pause. Read the result before continuing.

**Say:** pacman is the package manager. Read its instructions. If asked to close the terminal during the update, close it, reopen UCRT64 and run pacman -Syu again. Once the update finishes, install the basic build tools:

**On screen — type one line at a time:**

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-gdb
```

Pause. Read the result before continuing.

**Say:** --needed avoids reinstalling packages already current. GDB is a debugger: a tool for pausing and examining a running program. The first console lesson does not need GTK4 or SQLite. Install those later when a specific project requires them.

### 3. Return to PowerShell

**On screen — type one line at a time:**

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
Get-Command gcc, cmake, ninja, ctest
gcc --version
cmake --version
ninja --version
ctest --version
```

Pause. Read the result before continuing.

**Say:** This PATH change applies to this terminal and programs started from it. It does not permanently change Windows settings. Check that the tools resolve from the intended UCRT64 bin folder. A compiler version alone does not prove every C23 feature is supported; the small examples here use a conservative subset.

### If a tool is missing

**Say:** Check your MSYS2 location and confirm you installed the UCRT64 package names. In PowerShell, an executable path in quotes needs the call operator &: & "C:\msys64\ucrt64\bin\gcc.exe" --version. The & tells PowerShell to run the named program rather than treat its path as text.

### Your turn

**Say:** Record each tool version in your practice notes. Explain which tool compiles, which one generates build instructions and which one runs tests.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
