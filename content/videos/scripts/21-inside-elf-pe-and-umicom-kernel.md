# Episode 21 — Inspect executable files and follow Umicom Kernel startup

**Duration:** Approximately 17–22 minutes, including demonstration and QEMU review.

**Companion reading:** [Lesson 74](../../lessons/05-engineering/74-read-elf-pe-coff-with-c23.md), [Lesson 75](../../lessons/05-engineering/75-abi-stack-and-calling-conventions.md) and [Lesson 76](../../lessons/06-umicom/76-freestanding-c-and-umicom-kernel.md).

**Source references:** [Umicom Framework](https://github.com/umicom-foundation/umicom-framework), [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel).

## 00:00–02:30 — An executable is a structured file

**On screen:** Show two files: `umicom-education.exe` and `umicom-kernel.elf`. Open a diagram of their different header structures.

**Narration:**

"These two files contain machine code, but they are not interchangeable. One is a Windows application, built to run inside a Windows process. The other is a RISC-V64 kernel image intended for a different execution environment.

We can examine both files from one computer without attempting to run either. That is the purpose of a binary inspector: treat the file as data and identify the header fields that describe it.

The Umicom Education tool now has a C23 `binary --file` command. We will use it to inspect the files and to understand where the compiler and linker stop, and where the operating-system loader or firmware begins."

## 02:30–05:30 — Examine a Windows PE file

**On screen:** Execute the inspector against `build/umicom-education/bin/umicom-education.exe`. Display `Format: PE`, `Architecture: x86-64` and `Entry point (RVA)`.

**Narration:**

"A Windows executable commonly uses Portable Executable, or PE, format. Near the start of the file is the `MZ` marker. A later field points to the PE signature. The following header identifies a machine, the number of sections and other properties.

Our C23 inspector reports the entry point as an RVA. That is a relative virtual address. It is not a complete instruction address on its own; the loader maps the image and uses its image base when interpreting that value.

The inspection command never starts the target programme. It opens the file for reading and interprets only a bounded header. That distinction matters when we examine unknown or damaged files."

## 05:30–08:00 — Object files and the linker's work

**On screen:** Show `main.o` and `catalogue.c.obj` or `.o` from the course catalogue build; run the inspector against a Windows COFF object. Then show `nm` output for the static archive.

**Narration:**

"An object file is an intermediate result. It contains compiled machine instructions, but symbols may still need to be resolved. A Windows object is usually a COFF object; a Linux object typically uses ELF.

The linker takes the object files and matching libraries, connects references, applies relocations and produces the final image. The file format also helps the linker reject objects that target the wrong processor or architecture.

The native inspector does not understand every possible library archive. That is fine: one tool should be clear about its limits. For a collection of object files, the toolchain's `ar` and `nm` utilities are appropriate next steps."

## 08:00–10:30 — Learn the ELF header

**On screen:** Highlight `7f 45 4c 46`, the class byte and `e_machine` in the ELF diagram. Show the RISC-V number 243 and x86-64 number 62.

**Narration:**

"ELF is used for many Linux executables, objects and kernel images. Its first four bytes spell a distinctive signature. Other bytes tell us whether the file is for a 32-bit or 64-bit address model and how multi-byte values are stored.

The machine field identifies the intended instruction set. A RISC-V64 ELF is still an ELF file when viewed from Windows. But the instructions inside are for RISC-V, not for your laptop's x86-64 CPU.

This is why we distinguish a host compiler from a target compiler. You can build code on one machine for another CPU, but you must use a toolchain that emits the correct target instructions and ABI."

## 10:30–14:30 — Move from C into RISC-V Assembly

**On screen:** Open `arch/riscv64/boot.S` in Umicom Kernel. Highlight `_start`, `la sp, __stack_top`, the BSS clearing loop, and argument setup for `UmiKernelMain()`.

**Narration:**

"At the beginning of a normal application, the operating system has already provided a stack and startup environment. A kernel cannot make that assumption. Umicom Kernel's first-boot Assembly performs those initial tasks by itself.

The `_start` symbol identifies the first entry. The code selects the boot hart, leaves interrupts disabled until an appropriate handler exists, and sets the stack pointer. It clears BSS so uninitialised static C objects begin with the zero values that the C language expects.

Only after that groundwork does control move into `UmiKernelMain`. The arguments are placed into registers according to the RISC-V calling convention: `a0` and `a1` for the first two arguments. This is a practical example of an ABI, not merely a theoretical table in a book."

## 14:30–19:00 — Build, inspect and run the kernel

**On screen:** Follow `docs/BUILD_AND_TEST.md`. Configure with the `riscv64-clang-debug` preset, build, test and inspect `umicom-kernel.elf`. If QEMU is available, run the documented command and show the serial output.

**Narration:**

"The compiler and linker can successfully produce an ELF image even when the hardware has never executed it. First, we compile and link the kernel. Next, we inspect the ELF header to confirm that it declares the RISC-V target. Finally, QEMU emulates the hardware environment and lets us see whether `_start` actually runs.

For the documented first-boot milestone, the image is loaded as machine-mode firmware using `-bios`. That detail belongs to this specific boot arrangement. It should not be copied blindly into every other kernel project or later firmware protocol.

Successful serial output gives us runtime evidence that the boot path reached its checks. It does not, by itself, prove that every kernel component is production-ready. We still need testing for memory, privilege handling, device access and failure recovery."

## 19:00–22:00 — Review and next exercise

**On screen:** Display the source → object → executable → loader → Assembly → C23 kernel diagram. Return to the Bits2Banking repository.

**Narration:**

"We have connected several subjects that might initially seem separate: C programming, Assembly, compilers, executable formats, linking, ABIs, firmware and operating systems. Each belongs to one continuous chain.

Our learning task is to observe every handoff rather than treating the entire build as a black box. We know what produced the file, what architecture it targets, how the loader finds its entry, and why the earliest kernel code must prepare an environment for C.

The Umicom repositories make these ideas concrete. You can inspect the exact source files, repeat the documented build and contribute corrections that will help the next person understand the same concepts."

**Practical task:** Inspect the headers of a Windows application, a Windows object file and an Umicom Kernel ELF. Record format, target architecture and entry-point meaning. Describe which of these files may run directly on the current host and why.

**Website reference:** Read Bits2Banking Lessons 74–76 and use the Umicom Kernel build guide for the latest QEMU commands.
