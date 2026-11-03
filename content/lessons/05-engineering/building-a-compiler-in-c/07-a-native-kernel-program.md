# Run the interpreter as a native Kernel program

The CVM runtime is written in C. To use it on Umicom Kernel, a compiler must turn that C implementation into native instructions for the Kernel's supported processor. The resulting native program then interprets UMCB instructions. There are two instruction sets involved, with different responsibilities.

## Separate the layers

1. The processor executes RISC-V native instructions produced from the runtime's C source.
2. The runtime interprets the small CVM operations, such as PUSH and MULTIPLY.
3. When the native program finishes, it uses the Kernel's native system-call convention to report its result.

A **system call** is a controlled request from a user program to the Kernel. An **ABI**, or application binary interface, defines details such as which registers carry arguments and results. Portable C source does not remove the need for that native interface.

## Read the entry and workload

Open `umicom-kernel/programs/cvm/entry.S`. It transfers control to the C function and later requests process exit. Then open `programs/cvm/main.c`. The normal case encodes a small program, decodes it, checks operation identity and executes 7 × 6. Other selectors exercise insufficient fuel, division by zero, invalid bytecode flags and an unsupported selector.

The runtime has no heap allocator, file operation or host-service instruction. A **heap allocator** hands out dynamically sized memory blocks. This example instead supplies bounded arrays for bytecode, decoded instructions and results. Avoiding allocation simplifies the exercise; it does not prove that all C programs are memory-safe.

## Understand the Kernel-side checks

`kernel/cvm_validation.c` asks the existing process service to create and run the native image. It checks the reported exit, refuses a second entry into the exited process, destroys the process and compares memory-frame counts. A **frame** is a fixed-size unit of physical memory managed by the Kernel.

The optional CMake integration builds two native images at different optimisation settings. Optimisation changes how a compiler produces machine code. Both images must pass their own guest checks; a host test is not a substitute. The external runtime source and build recipe are recorded so that an outdated image cannot silently qualify different source.

## Optional practical route

Follow `umicom-kernel/docs/CVM_PROGRAM_GUIDE.md` for the exact optional configure and test commands. This exercise requires the RISC-V toolchain and emulator. Keep its build directory separate from the ordinary Kernel build. The expected completion marker is `UMICOM_KERNEL_CVM_READY`; an executable file merely existing is not a boot pass.

This integration is a qualification workload. It does not yet add a general-purpose CVM command to the normal Kernel console or load arbitrary bytecode from a user file.

## Exercise

Why must a RISC-V runtime executable be rebuilt for an x86-64 Kernel, even if the UMCB program stays byte-for-byte identical?

<details>

<summary>Explanation</summary>

The processor instructions and native calling interface differ. The portable data format is shared, but its interpreter is native code. Each port also needs working Kernel process and memory services before this workload can run.

</details>

## Find the implementation

Open `umicom-kernel/programs/cvm/main.c` in your Umicom source collection. Read the named functions alongside this lesson. Source reading and the expected outcomes below are not evidence of an executed build.

---

[Read this lesson in HTML](../../../courses/building-a-compiler-in-c/lessons/07-a-native-kernel-program.html) · [Learning sequence](../../../start/learning-sequence.md)
