<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/kernel-riscv-console.md

PURPOSE:
Build and observe the RISC-V64 Kernel system and recovery consoles in QEMU.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# 2. Boot Umicom Kernel in RISC-V QEMU

Use a Windows PowerShell terminal with CMake, Ninja, Clang, LLD and the QEMU RISC-V system emulator available. An existing launch kit with reviewed `umicom-system.elf` and `umicom-recovery.elf` can skip the build. Use the paths that match your own tools.

If you are using a prebuilt kit, [check its two image files before opening QEMU](verify-kernel-launch-kit.md). The check uses the publisher's fingerprint and works without the original build directory.

## Prepare a fresh build

Run each command in order. Stop at the first nonzero exit code. This build produces the native images with the standard console behaviour.

~~~powershell
$Kernel = 'C:/umicom/umicom-kernel'
$Tools = 'C:/msys64/ucrt64/bin'
$Qemu = "$Tools/qemu-system-riscv64.exe"
$Build = Join-Path $env:USERPROFILE ("umicom-kernel-rv64-" + (Get-Date -Format 'yyyyMMdd-HHmmss'))
$env:Path = "$Tools;$env:Path"
& $Qemu --version
if ($LASTEXITCODE -ne 0) { throw 'Check the QEMU installation path before continuing.' }

cmake -S $Kernel -B $Build -G Ninja "-DCMAKE_TOOLCHAIN_FILE=$Kernel/cmake/toolchains/riscv64-clang.cmake" "-DCMAKE_MAKE_PROGRAM=$Tools/ninja.exe" "-DUMICOM_CLANG_EXECUTABLE=$Tools/clang.exe" "-DUMICOM_LLD_EXECUTABLE=$Tools/ld.lld.exe" "-DUMICOM_QEMU_RISCV64=$Qemu" -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=OFF -DUMICOM_KERNEL_CVM=OFF -DUMICOM_BUILD_SYSTEM_IMAGES=ON
if ($LASTEXITCODE -ne 0) { throw 'Kernel configure failed.' }

cmake --build $Build --target umicom-system-image umicom-recovery-image --parallel 2
if ($LASTEXITCODE -ne 0) { throw 'Kernel image build failed.' }
$Images = Join-Path $Build 'bin'
Get-FileHash -Algorithm SHA256 -LiteralPath "$Images/umicom-system.elf", "$Images/umicom-recovery.elf"
~~~

## Run and compare the consoles

1. Run either ELF directly in an interactive terminal. Use the correct `$Images` folder if you started from a kit.

   ~~~powershell
   & $Qemu -machine 'virt,aclint=off' -bios "$Images/umicom-system.elf" -display none -monitor none -serial stdio -m 128M -smp 1 -no-reboot -nic none
   $LASTEXITCODE
   ~~~

2. At the guest prompt, try `help boot` and `status`. Use `poweroff` to end the guest. Record the last console lines, including `UMICOM_KERNEL_END` when the guest emits it, and the QEMU exit code before running another native command.
3. Repeat the command with `umicom-recovery.elf`. At the guest prompt try `help`, then `status`, then `poweroff`. Record its reason for starting recovery.

The arguments attach no disk, network card or host folder. `-bios` loads this build as RISC-V machine-mode firmware and `-serial stdio` connects the guest to the current terminal. If a PowerShell pipeline prevents keyboard input reaching QEMU, run it directly and record the terminal output separately. If it stalls before the prompt, keep the last lines and recheck the ELF, QEMU executable and machine model.

**Check yourself.** Your results identify two distinct image hashes and the startup path for each guest. Use the Kernel course for further console and hosted test exercises.

[Choose a target](choose-a-target.md) · [Build a Kernel x64 UEFI preflight](kernel-uefi-preflight.md) · [Kernel course](../../courses/umicom-kernel-from-scratch/index.html) · [QEMU RISC-V firmware options](https://www.qemu.org/docs/master/system/target-riscv.html#risc-v-cpu-firmware)
