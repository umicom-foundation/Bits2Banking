# 24. Prepare a computer for Umicom development

Umicom Applications is a **superproject**: a Git repository that records the exact revisions of Umicom Framework and multiple application repositories using **submodules**. A submodule is another Git repository kept at a path inside the parent. The parent records a commit identifier for that child, so everyone can work from a reproducible set of versions.

We will use **Windows PowerShell** for the main walkthrough. The same ideas apply on Linux using its shell and package manager.

## Step 1 — install Git, GitHub CLI and development tools

In PowerShell, check what is already installed:

```powershell
git --version
gh --version
cmake --version
ninja --version
python --version
```

A missing command means that tool is not yet available from your terminal. On a Windows installation with WinGet, you can install common tools individually:

```powershell
winget install --id Git.Git -e
winget install --id GitHub.cli -e
winget install --id Microsoft.PowerShell -e
```

Close and reopen PowerShell after installation so updated environment variables can take effect. You can install an editor such as VS Code if Umicom Studio is not yet built:

```powershell
winget install --id Microsoft.VisualStudioCode -e
```

## Step 2 — install the Windows native toolchain

The current Windows Umicom development configuration uses **MSYS2 UCRT64**, GCC, CMake, Ninja and GTK4. Install MSYS2 from its official site and open the **MSYS2 UCRT64** terminal. Update package metadata and packages:

```bash
pacman -Syu
```

If the updater tells you to close the terminal, do so, reopen the UCRT64 terminal and run `pacman -Syu` again. Then install the core tools and desktop libraries:

```bash
pacman -S --needed \
  base-devel \
  mingw-w64-ucrt-x86_64-toolchain \
  mingw-w64-ucrt-x86_64-clang \
  mingw-w64-ucrt-x86_64-cmake \
  mingw-w64-ucrt-x86_64-ninja \
  mingw-w64-ucrt-x86_64-pkgconf \
  mingw-w64-ucrt-x86_64-gtk4 \
  mingw-w64-ucrt-x86_64-gtksourceview5
```

Open PowerShell and check the exact executables:

```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" --version
& "C:\msys64\ucrt64\bin\cmake.exe" --version
& "C:\msys64\ucrt64\bin\ninja.exe" --version
& "C:\msys64\ucrt64\bin\pkg-config.exe" --modversion gtk4
```

The final command should print an installed GTK4 version. If you receive “file not found”, confirm that MSYS2 is installed at `C:\msys64`, or adjust the path to your actual installation.

## Step 3 — clone the complete repository

Create a development folder and clone Umicom Applications:

```powershell
New-Item -ItemType Directory -Force -Path "C:\umicom" | Out-Null
Set-Location "C:\umicom"

git clone --recurse-submodules `
    "https://github.com/umicom-foundation/umicom-applications.git" `
    "C:\umicom\umicom-applications"
```

The initial checkout can take time because the project contains multiple submodules. Enter the parent repository and verify them:

```powershell
Set-Location "C:\umicom\umicom-applications"
git submodule sync --recursive
git submodule update --init --recursive
git submodule status
```

Do not copy the Framework folder into each application. The parent already records the Framework revision and each application's revision.

## Step 4 — configure the smaller headless build

The **headless** preset skips the graphical GTK4 frontends while exercising important native services. It is useful for confirming that the compiler and source tree are working before attempting a large desktop build.

```powershell
Set-Location "C:\umicom\umicom-applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

& "C:\msys64\ucrt64\bin\cmake.exe" `
    --preset windows-ucrt64-headless-debug
```

Now compile and run tests:

```powershell
& "C:\msys64\ucrt64\bin\cmake.exe" `
    --build --preset windows-ucrt64-headless-debug --parallel 2

& "C:\msys64\ucrt64\bin\ctest.exe" `
    --preset windows-ucrt64-headless-debug --output-on-failure
```

The configure step generates build files, the build compiles configured targets and the test step runs registered checks. **A successful configure does not mean every test will pass**. Read failures and preserve the complete diagnostic output when reporting a problem.

## Step 5 — build the desktop edition

After the headless profile works, configure the GTK4 profile:

```powershell
& "C:\msys64\ucrt64\bin\cmake.exe" `
    --preset windows-ucrt64-debug

& "C:\msys64\ucrt64\bin\cmake.exe" `
    --build --preset windows-ucrt64-debug --parallel 2

& "C:\msys64\ucrt64\bin\ctest.exe" `
    --preset windows-ucrt64-debug --output-on-failure
```

If Studio is built, its documented Windows executable path is:

```powershell
& ".\build\windows-ucrt64-debug\bin\umicom-studio-ide.exe" --console
```

If that file does not exist, first inspect the build error and whether the Studio target was enabled. Do not try to repair the situation by deleting source directories or modifying unrelated project files.

## Step 6 — understand the submodule status

```powershell
git status
git submodule status
```

Each submodule has its own commits. If you change `framework`, commit that work inside the Framework repository. The parent repository then needs a separate commit recording the new Framework revision. Beginners should do this only on a contribution fork or in a worktree expressly prepared for the change, not in an unfamiliar shared checkout.

## On Linux

The package names below are for an Ubuntu or Debian-derived development computer. Other distributions use different package managers and package names. Install the basic compiler and build tools:

```bash
sudo apt update
sudo apt install git gcc g++ cmake ninja-build pkg-config
```

For graphical GTK4 development, install the development headers provided by your distribution, such as `libgtk-4-dev` and `libgtksourceview-5-dev` on supported Ubuntu or Debian versions. A headless build does not require those graphical packages.

Clone the complete suite into your home directory:

```bash
mkdir -p "$HOME/umicom"
cd "$HOME/umicom"
git clone --recurse-submodules \
    https://github.com/umicom-foundation/umicom-applications.git
cd umicom-applications
```

Then configure, build and test using the Linux GCC headless preset recorded in the current repository:

```bash
cmake --preset linux-gcc-all-headless-debug
cmake --build --preset linux-gcc-all-headless-debug --parallel 2
ctest --preset linux-gcc-all-headless-debug --output-on-failure
```

Run `cmake --list-presets` when you want to inspect the available configurations. If the build fails because a development library is missing, read the specific CMake or compiler diagnostic and install that dependency from your distribution. Do not copy Windows `.exe` or MSYS2 commands verbatim into a Linux shell.

**Next:** [Build a real example using Framework components](25-use-the-framework.md).
