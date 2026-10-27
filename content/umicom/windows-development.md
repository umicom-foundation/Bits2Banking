# Build and run Umicom on Windows

This guide separates the tools that run on your Windows computer from the RISC-V Kernel that runs inside QEMU. A successful build creates programs; tests exercise particular behaviours; launching a window is a separate check. None of these steps alone proves that every product feature is complete.

## 1. Prepare the tools

Install Git for Windows and MSYS2 from their official sites. The commands below assume MSYS2 is installed at C:\msys64 and the repositories are under C:\umicom. Keep source and build folders separate.

Open **MSYS2 UCRT64** from the Start menu. UCRT64 identifies one compatible set of Windows compilers and libraries. Avoid combining its libraries with files from the MINGW64 or CLANG64 directories. See the [MSYS2 environment guide](https://www.msys2.org/docs/environments/).

In the UCRT64 terminal, update packages:

~~~sh
pacman -Syu
~~~

Follow any request to close the terminal, reopen UCRT64, and run the update again. Then install the development tools:

~~~sh
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-clang mingw-w64-ucrt-x86_64-lld mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-pkgconf mingw-w64-ucrt-x86_64-gtk4 mingw-w64-ucrt-x86_64-gtksourceview5 mingw-w64-ucrt-x86_64-sqlite3 mingw-w64-ucrt-x86_64-curl mingw-w64-ucrt-x86_64-qemu
~~~

GTK4 provides windows and controls; GtkSourceView provides source-editor widgets; SQLite provides a database library; curl provides network-transfer facilities. QEMU emulates a machine. Additional optional application features can require further packages named by their configure diagnostics. Use the official [GTK4 package](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-gtk4) and [QEMU package](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-qemu) listings when checking installations.

Open **PowerShell** for the remaining commands:

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
New-Item -ItemType Directory -Force "C:\umicom\_local\logs\repository-publication"
Get-Command git, cmake, ninja, gcc, clang, ld.lld, pkg-config, qemu-system-riscv64
cmake --version
gcc --version
clang --version
pkg-config --modversion gtk4 gtksourceview-5
~~~

The first command changes only this PowerShell process's tool search path. It does not install software. Inspect the reported executable paths. Use CMake 3.25 or newer for the version-6 preset files. A missing command must be installed before proceeding.

## 2. Understand the working folders

A repository contains editable source files. A build folder contains generated files, object files and executables. A preset is a named collection of build settings stored in that repository's CMakePresets.json. Preset names are not global.

| Repository | Configure, build and test preset | Purpose |
| --- | --- | --- |
| Umicom-Applications | windows-ucrt64-all-debug | Enabled application suite and its shared Framework |
| Umicom-Applications\framework | windows-ucrt64-debug | Standalone Framework |
| umicomOS | gtk4-debug | Windows-hosted OS desktop shell |
| umicomOS | headless-debug | OS services without a graphical shell |
| umicom-kernel | riscv64-clang-debug | Freestanding RISC-V images and QEMU checks |

For a new checkout, obtain its declared submodules before starting work. Existing development checkouts may contain newer child work: do not run a blanket submodule update to replace those edits with old parent revisions. First inspect:

~~~powershell
git status --short --branch
git submodule status --recursive
~~~

A leading minus means a child is uninitialised, plus means its checked-out revision differs from the parent pin, and U means a conflict. Initialise only missing children after confirming their intended revisions. Keep local source changes before any repository update.

## 3. Configure, build and test Applications

Run each command separately and stop on failure. PowerShell does not automatically stop after a failed native command. Immediately after a command, $LASTEXITCODE reports its exit code; zero normally means success. Do not test or install an incomplete build.

~~~powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-all-debug -DBUILD_TESTING=ON -DUMICOM_BUILD_NATIVE_TOOL=ON 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\applications-configure-review.log"
cmake --build --preset windows-ucrt64-all-debug --parallel 2 -- -k 0 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\applications-build-review.log"
ctest --preset windows-ucrt64-all-debug --output-on-failure --no-tests=error --output-log "C:\umicom\_local\logs\repository-publication\applications-tests-review.log"
~~~

Configuration should end with generated build files. Building should finish without FAILED or compiler errors. Ninja's -k 0 asks it to continue independent jobs after an error; it does not make that error acceptable. CTest should report its outcomes and return zero. Inspect skipped tests separately; a skipped GUI or platform check is not a pass.

Tee-Object displays output and writes it to a file. 2>&1 includes diagnostic output. Use a new log filename for each later run to preserve earlier evidence.

After the build and required tests succeed, launch one application at a time:

~~~powershell
Set-Location "C:\umicom\Umicom-Applications"
& ".\build\windows-ucrt64-all-debug\bin\umicom-desk.exe"
& ".\build\windows-ucrt64-all-debug\bin\umicom-studio-ide.exe"
& ".\build\windows-ucrt64-all-debug\bin\umicom-trader.exe"
& ".\build\windows-ucrt64-all-debug\bin\umicom-bank.exe"
& ".\build\windows-ucrt64-all-debug\bin\umicom-tms.exe"
& ".\build\windows-ucrt64-all-debug\bin\umicom-healthcare.exe"
~~~

Close each window before starting the next check. Desk provides the catalogue for the other enabled products, including Media. A catalogue entry does not prove that its entire workflow is implemented. Check each product's actual task: open and save a disposable file in Studio, inspect synthetic account data in Bank/Trader, and use synthetic data in Healthcare. Avoid real trading, banking or patient records during qualification.

The repository describes further native workflows in its docs/getting-started/NATIVE_WORKBENCH_QUALIFICATION.md. After changing a specific target, building that target is incremental; run its affected tests first and then the wider suite before a release. ctest --rerun-failed only repeats previously failing tests and is not a full qualification.

Optional development installation, after a successful complete build:

~~~powershell
cmake --install ".\build\windows-ucrt64-all-debug" --prefix "C:\umicom\installed\applications" 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\applications-install-review.log"
~~~

Installation copies the configured artifacts. It does not prove that a package works without your development PATH, and it must not be used to conceal a missing executable.

## 4. Standalone Framework and its SDK

The Framework is a library collection plus development tools, rather than one desktop application. An SDK is the set of headers, libraries and CMake package files another program needs to use it.

~~~powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-debug -DBUILD_TESTING=ON -DUMICOM_BUILD_NATIVE_TOOL=ON 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\framework-configure-review.log"
cmake --build --preset windows-ucrt64-debug --parallel 2 -- -k 0 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\framework-build-review.log"
ctest --preset windows-ucrt64-debug --output-on-failure --no-tests=error --output-log "C:\umicom\_local\logs\repository-publication\framework-tests-review.log"
cmake --install ".\build\windows-ucrt64-debug" --prefix "C:\umicom\installed\framework" 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\framework-install-review.log"
& ".\build\windows-ucrt64-debug\bin\umicom.exe" --help
~~~

The default standalone preset does not enable every GTK feature. Applications' graphical build supplies separate coverage. Never describe a headless Framework test run as a graphical test pass.

## 5. Umicom OS desktop shell

The Windows build launches a user-space shell. It does not boot a replacement Windows operating system. Linux image/bootstrap work and the original RISC-V Kernel have separate build paths.

~~~powershell
Set-Location "C:\umicom\umicomOS"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset gtk4-debug -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/msys64/ucrt64 -DBUILD_TESTING=ON -DUMICOM_OS_BUILD_TESTS=ON -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=C:/umicom/umicomOS/build/gtk4-debug/bin 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\os-configure-review.log"
cmake --build --preset gtk4-debug --parallel 2 -- -k 0 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\os-build-review.log"
ctest --preset gtk4-debug --output-on-failure --no-tests=error --output-log "C:\umicom\_local\logs\repository-publication\os-tests-review.log"
& ".\build\gtk4-debug\bin\umicom-os-shell.exe"
~~~

The explicit runtime directory gives the shell and tools a predictable bin folder. Without that setting, the OS application's default output can remain under build\gtk4-debug\applications\os. If a pre-existing build uses another compiler, select a new build directory; do not overwrite its cache with an incompatible toolchain.

Optional installation after qualification:

~~~powershell
cmake --install ".\build\gtk4-debug" --prefix "C:\umicom\installed\os" 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\os-install-review.log"
~~~

## 6. Umicom Kernel

The Kernel cross-compiles for RISC-V. Cross-compilation means that your Windows compiler produces instructions for a different processor. The .elf output runs under QEMU, not directly in Windows.

~~~powershell
Set-Location "C:\umicom\umicom-kernel"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset riscv64-clang-debug -DBUILD_TESTING=ON 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\kernel-configure-review.log"
cmake --build --preset riscv64-clang-debug --target umicom-boot-memory-contracts --parallel 2 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\kernel-boot-link-review.log"
cmake --build --preset riscv64-clang-debug --parallel 2 -- -k 0 2>&1 | Tee-Object "C:\umicom\_local\logs\repository-publication\kernel-build-review.log"
ctest --preset riscv64-clang-debug --output-on-failure --no-tests=error --output-log "C:\umicom\_local\logs\repository-publication\kernel-tests-review.log"
~~~

UMICOM_BUILD_NATIVE_TOOL belongs to Framework; it is not a Kernel option. The small boot-memory targets link the real boot source without libc at two optimisation levels. Their .elf files are link checks, not bootable firmware.

Start the normal interactive image:

~~~powershell
& "C:\msys64\ucrt64\bin\qemu-system-riscv64.exe" -machine "virt,aclint=off" -bios ".\build\riscv64-clang-debug\bin\umicom-system.elf" -display none -monitor none -chardev "stdio,id=console,mux=on,signal=off" -serial "chardev:console" -m 128M -smp 1 -no-reboot
~~~

The terminal is the guest's serial console. The machine is QEMU's RISC-V virt board, 128M is guest memory, and -smp 1 selects one virtual processor. The mux=on setting enables QEMU's character multiplexer. Close QEMU using its terminal escape sequence Ctrl+A then X. Do not type those as guest commands. See the [QEMU terminal key reference](https://www.qemu.org/docs/master/system/mux-chardev.html).

For the generated read-only block fixture:

~~~powershell
& "C:\msys64\ucrt64\bin\qemu-system-riscv64.exe" -machine "virt,aclint=off" -bios ".\build\riscv64-clang-debug\bin\umicom-system.elf" -display none -monitor none -chardev "stdio,id=console,mux=on,signal=off" -serial "chardev:console" -m 128M -smp 1 -no-reboot -global virtio-mmio.force-legacy=false -drive "file=./build/riscv64-clang-debug/fixtures/umicom-read-only.raw,if=none,format=raw,id=umicom_read_test,readonly=on" -device "virtio-blk-device,drive=umicom_read_test"
~~~

This fixture is synthetic block data, not a filesystem. Do not expect it to contain files. The filename umicom-writable-vfs-test.raw is not generated by the current configuration. To exercise writable filesystem persistence, use the existing fixture-managed checks:

~~~powershell
ctest --preset riscv64-clang-debug -R "^kernel\.riscv64\.disk_writable_filesystem" --output-on-failure --no-tests=error --output-log "C:\umicom\_local\logs\repository-publication\kernel-disk-review.log"
~~~

CTest prepares its synthetic disk and orders read-only, write and readback operations. Do not attach a physical host disk or reuse this test-owned disk for personal data. The bootable system and recovery images are in bin; no Windows installer is needed to launch them in QEMU.

## 7. Read failures by stage

| Symptom | Meaning and next action |
| --- | --- |
| No such preset | Check the current directory and cmake --list-presets. Use the table above. |
| build.ninja missing | Configuration did not finish. Fix configure first. |
| Unknown header or package | Verify compiler prefix and the SDK installation; a source checkout is not an installed SDK. |
| Undefined reference | Compilation succeeded but linking could not resolve a function. Inspect the first linker diagnostic and target dependencies. |
| Test Not Run | The executable, fixture or environment was unavailable. Do not count it as passed. |
| Test skipped | Required capability was intentionally unavailable. Keep this coverage gap visible. |
| Executable disappeared | Inspect antivirus history and the build result. Do not assume a source-code defect or a false positive. |
| Install cannot find executable | Complete the build and investigate quarantine before installing. |

Keep logs outside public repositories. A useful report includes the first error, the final summary, the source revision, compiler version and exact command. Never paste credentials, personal records or private conversations into public documentation.

Continue with [Introduction to Umicom Framework](../lessons/umicom-development/02-introduction-to-framework.md), [Introduction to CMake](../lessons/umicom-development/03-introduction-to-cmake.md) and [Windows security detection review](windows-security-review.md).
