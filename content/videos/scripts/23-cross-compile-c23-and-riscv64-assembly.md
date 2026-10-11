# Episode 23 — Cross-compile C23 and RISC-V64 Assembly

**Running time:** approximately 11–15 minutes.  
**Companion lessons:** [79. Relocations](../../lessons/05-engineering/79-relocations-and-position-independent-code.md), [80. Cross-compilation](../../lessons/05-engineering/80-cross-compile-c23-riscv64.md), [76. Umicom Kernel boot](../../lessons/06-umicom/76-freestanding-c-and-umicom-kernel.md).  
**Working example:** [`labs/native/cross-target-object`](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/cross-target-object).

## 00:00–01:30 — One computer, two instruction sets

**Narration**

Imagine you are developing Umicom Kernel on a Windows laptop. Your laptop uses an x86-64 processor, but the Kernel research project is being brought up on RISC-V64. How can the Windows laptop produce instructions for the other processor?

The answer is a cross-compiler. The computer running the compiler is the host. The processor that will execute the generated instructions is the target. Those are independent choices.

Today we will compile an ordinary C23 object for the host, then use Clang's RISC-V64 target to compile a similar object for a different architecture. We will also examine a short Assembly function that reads a RISC-V machine-mode register.

We will not try to run RISC-V instructions inside an ordinary Windows application. We will inspect the resulting object files, then connect them to the real Umicom Kernel startup design.

**On screen:** Display [host/target diagram](../../assets/diagrams/host-target-cross-compilation.svg); highlight the host and target boxes.

## 01:30–03:20 — Build for the host first

**Narration**

Open `labs/native/cross-target-object`. The project contains a C source file, a CMake project and a small toolchain configuration. The C source calculates a deterministic value from fictional boot inputs. It needs no graphical user interface, file access or operating-system calls.

We deliberately build an object library rather than an executable. CMake's `OBJECT` library form tells the compiler to produce object files, then stop. That is an ideal first cross-compilation exercise because we do not yet need a linker script or a target runtime.

**On screen — PowerShell:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\cross-target-object" `
    -B ".\output\learning-build\cross-target-host" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\cross-target-host" --parallel 2
```

**Narration**

Find `probe.c.obj`. It normally contains x86-64 COFF object code when GCC is targeting Windows. The filename itself does not prove the architecture; the object header does. We can use the Framework's read-only binary inspector to check.

## 03:20–05:30 — Select the RISC-V64 target

**Narration**

CMake does not guess the target architecture simply because our folder is named RISC-V. It must be told which compiler and target to use.

Our `riscv64-clang.cmake` toolchain file selects Clang, specifies `riscv64-unknown-elf` and tells CMake to use compile-only checks rather than try to link and run a host-style executable.

**On screen — PowerShell:**

```powershell
clang --version
$Toolchain = (Resolve-Path `
    ".\labs\native\cross-target-object\toolchains\riscv64-clang.cmake").Path
cmake -S ".\labs\native\cross-target-object" `
    -B ".\output\learning-build\cross-target-riscv64" `
    -G Ninja `
    "-DCMAKE_TOOLCHAIN_FILE=$Toolchain"
cmake --build ".\output\learning-build\cross-target-riscv64" --parallel 2
```

**Narration**

These steps require a Clang build with RISC-V target support. If that support is not installed, do not change the project to pretend the target exists. Use the native build and study the toolchain file until an appropriate compiler is available.

A successful RISC-V build produces `probe.c.obj` and `riscv64_hart.S.obj`. Neither one is a complete boot image.

## 05:30–07:40 — Read one RISC-V Assembly instruction

**Narration**

Open `riscv64_hart.S`. It defines a function named `BtbRiscvReadHartId`. The instruction `csrr a0, mhartid` reads the hardware-thread identifier into register `a0`, then `ret` returns from the function.

Why `a0`? Under the usual RISC-V calling convention, `a0` is the first integer return register. We can understand the data flow in this three-line function without knowing every detail of the instruction set.

But there is an essential restriction: `mhartid` is a machine-mode control and status register. It cannot be read from ordinary user-mode code. This function is compiled so that we can inspect it; we do not execute it on a normal application host.

Now open the real [Umicom Kernel boot Assembly](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S). Notice the extra responsibilities: selecting the boot hart, establishing the stack, preserving the device-tree address, clearing BSS and passing arguments into `UmiKernelMain()`.

The Kernel cannot assume that an operating system has already prepared those things. It is itself the component that will help establish the operating-system environment.

## 07:40–09:30 — Compare the binary headers

**Narration**

Find the new RISC-V `.obj` files. Ask `umicom-education binary` to inspect one of them. The header should identify ELF and RISC-V64. The earlier host object should instead identify its own host-target format, generally COFF and x86-64 on Windows.

The object header shows the intended instruction set. It does not tell us whether the object is safe, whether every symbol is defined, or whether a complete boot loader has been built.

The RISC-V object still contains sections and relocation information. A linker must place those sections into a target image, resolve references and establish an entry point. For the actual kernel, a linker script describes its memory layout and boot entry.

**On screen:** Compare both outputs beside the [object/ELF diagram](../../assets/diagrams/static-archive-and-linker.svg).

## 09:30–11:30 — What a real kernel needs

**Narration**

Umicom Kernel has a separate repository because kernel startup, privileged execution, memory management and device ownership require different rules from a hosted application framework. It is written primarily in C23 with Assembly at the architecture-specific boundaries.

For the RISC-V research configuration, QEMU can load an ELF image with the appropriate boot arrangement. The first-boot learning guide explains why an image linked at `0x80200000` requires the correct firmware loading path. That choice is part of the Kernel's boot contract, not a setting we should copy blindly into every new programme.

Read the Kernel's first-boot guide and its recurring build-and-test instructions before attempting a boot. A successful object compilation is one checkpoint; a successful QEMU run is another. Neither proves that an operating system is complete.

## 11:30–End — Exercise

**Narration**

For your exercise, write down the host architecture, the target architecture and the file format of each object you produced. Then locate the single line in CMake that selects the target and the Assembly instruction that reads `mhartid`.

If the first cross-build fails, preserve the diagnostic. Ask whether the compiler knows the target, whether CMake selected the expected toolchain and whether you accidentally used a cached build folder configured for another architecture.

In the next set of lessons we will develop these concepts further: linker scripts, executable layouts, predictable packaging and the boundary between hosted C programmes and freestanding kernels.

You can find the full lab, written chapters and actual Umicom Kernel source links through Bits2Banking. Share what you have learned so another contributor can reproduce the same result.
