# Laboratory — Compile C23 and Assembly for a different processor

The computer running your compiler is the **host**. The processor that will eventually execute the generated code is the **target**. In this exercise the host can be Windows x86-64 or Linux x86-64, while the target can be RISC-V64.

We build **object files**, not a complete kernel or executable. No RISC-V code will be launched on your host.

## 1. Compile a native object

From PowerShell on Windows:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\cross-target-object" `
    -B ".\output\learning-build\cross-target-host" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\cross-target-host" --parallel 2
```

Search for `probe.c.obj`. It is an unlinked host object. It has no program entry point.

## 2. Check Clang's RISC-V64 support

```powershell
clang --version
```

To cross-compile this laboratory, Clang must support the `riscv64-unknown-elf` target. If Clang is not installed or reports an unsupported architecture, finish the native part and read the cross-compilation chapter before installing anything.

## 3. Compile RISC-V64 objects

```powershell
$Toolchain = (Resolve-Path `
    ".\labs\native\cross-target-object\toolchains\riscv64-clang.cmake").Path

cmake -S ".\labs\native\cross-target-object" `
    -B ".\output\learning-build\cross-target-riscv64" `
    -G Ninja `
    "-DCMAKE_TOOLCHAIN_FILE=$Toolchain"

cmake --build ".\output\learning-build\cross-target-riscv64" --parallel 2
```

The RISC-V configuration compiles `probe.c` and `riscv64_hart.S`. It uses `CMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY` so the compiler checks do not try to link a program using the host's C runtime.

Look for the generated object files:

```powershell
Get-ChildItem ".\output\learning-build\cross-target-riscv64" `
    -Recurse -File -Include "*.obj", "*.o"
```

Inspect the object with `umicom-education binary --file` or `llvm-readelf -h`, supplying the exact path reported by the search. A successful cross-compiled object should be **ELF, RISC-V, 64-bit**.

## 4. Understand the Assembly file

`riscv64_hart.S` reads the RISC-V `mhartid` control and status register into `a0`. It is a **machine-mode** operation and must not be called from an ordinary application. The laboratory compiles the instruction but does not execute it.

The real Umicom Kernel uses architecture-specific boot code to establish a stack, clear BSS, preserve boot arguments and enter freestanding C23. See [Umicom Kernel boot source](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S) and [the first-boot guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md).

## 5. Stop at the correct boundary

A relocatable RISC-V object does not prove that a kernel can boot. Producing a bootable ELF also needs a linker script, entry symbol, valid memory map, target runtime contracts and an emulator or appropriate hardware. Those are addressed in the Umicom Kernel lessons and repository.

Continue with [Cross-compilation from C23 to RISC-V64](../../../content/lessons/05-engineering/80-cross-compile-c23-riscv64.md).
