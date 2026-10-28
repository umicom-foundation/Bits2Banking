# Run a small Umicom C program in Umicom Kernel

A computer normally runs machine instructions for its processor. An interpreter is a program that reads a different set of instructions and carries out their meaning. Umicom C has a small interpreter called the C Virtual Machine, or CVM. In this lesson, a native RISC-V program contains that interpreter.

If the words *program*, *operating system* or *kernel* are new, first read [applications, an OS and a kernel](../00-getting-started/07-applications-os-and-kernel.md). The [Kernel memory source tour](91-follow-umicom-kernel-memory-source.md) explains address spaces. You can read the explanation below without installing anything.

## Follow the layers

```text
You type a command at the Kernel console
                    |
                    v
The Kernel copies and checks an ELF program
                    |
                    v
A separate user process runs the native interpreter
                    |
                    v
The interpreter reads four arithmetic instructions
                    |
                    v
The native program returns a number through EXIT
```

**ELF** names the file format used for the native program. It describes where machine instructions and data belong in memory. **Bytecode** means the interpreter's simpler instruction format. These are different files and different responsibilities. The processor runs the interpreter's machine instructions; the interpreter reads bytecode as data.

**User mode** is the processor's restricted execution mode for applications. A program cannot become the Kernel simply by returning a number. A **system call** is a request that crosses the boundary to a Kernel service. This example's native envelope makes one EXIT request after the interpreter finishes.

## Read the real example

Open [programs/cvm/main.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/programs/cvm/main.c) in Umicom Kernel. The arithmetic program contains:

```c
static const UmcInstruction arithmetic[] = {
    {UMC_PUSH, 7, 0U}, {UMC_PUSH, 6, 0U},
    {UMC_MULTIPLY, 0, 0U}, {UMC_RETURN, 0, 0U}
};
```

An **array** is an ordered collection of values. Each entry here is one instruction. The first field selects an operation. The second holds a number when the operation needs one. The final field records a source position; zero is used in this hand-written example.

1. PUSH places 7 on the interpreter's value stack.
2. The next PUSH places 6 above it.
3. MULTIPLY removes those two values and places their product, 42, on the stack.
4. RETURN finishes with 42.

A **stack** is a collection where the most recently placed value is the next one removed. It has a fixed capacity here. The runtime checks the instruction sequence and arithmetic rather than assuming every input is valid.

The native example first encodes the instructions into bytes, decodes them into fresh storage, and compares their operations. It then gives execution a budget. A **budget**, also called fuel, limits how many interpreter instructions may execute. This is separate from the Kernel timer that bounds native process execution.

## Prepare the optional Kernel profile

Use the [Kernel CVM program guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/CVM_PROGRAM_GUIDE.md) for the complete configure, build, test and QEMU commands. You need the Kernel checkout, the Umicom C checkout and the RISC-V Clang/QEMU toolchain described there.

This optional profile uses a separate build directory. Enabling it adds the reviewed CVM demonstration to the normal console. It does not install an arbitrary-source compiler inside the Kernel or replace the ordinary boot profile.

## Try the console

After starting the newly built normal system image, wait for `umicom> `. Enter one command at a time.

1. Type `ls /bin`. Find `umicom-cvm.elf` in the program list.
2. Type `run /bin/umicom-cvm.elf 0`.
3. Read the completion line. It should say `state=exited exit=42` and `calls=1`. Other numbers, such as the process identity, can differ.
4. Type `run /bin/umicom-cvm.elf 2`. This selects the deliberate division-by-zero example. The native program should return 49154, confirming that the interpreter rejected it.
5. Type `run /bin/umicom-cvm.elf 0` again. A rejected arithmetic operation in the earlier process must not prevent this new process from returning 42.
6. Type `poweroff` when finished.

The final command argument is a **selector**: a number choosing a built-in demonstration. It is not C source or a filename. The complete selector table is in the linked Kernel guide.

The console copies its demonstration programs into RAMFS, a filesystem kept in working memory. Those files disappear at poweroff. CVM uses the same file and process owners as the other demonstration programs. It does not get a special way to execute with Kernel privilege.

## Understand a failure

- **No program listed:** check that CVM was enabled and QEMU booted the correct new image.
- **A different completion value:** keep the console transcript and identify which selector you used.
- **No prompt:** inspect the earlier boot messages. Do not send more commands to a partially started system.
- **A test was not selected:** check the exact test name and configuration. No selected tests means no test evidence.
- **The example works in a host model:** that is useful, but it does not prove that a RISC-V guest or physical machine works. These are separate checks.

## Trace ownership in the source

Follow these real files in order:

1. [console_runtime.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/console_runtime.c) gives the optional reviewed ELF its console pathname.
2. [console_shell.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/console_shell.c) reads a bounded file snapshot and hands it to the process supervisor.
3. [process_supervisor.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/process_supervisor.c) coordinates execution and terminal collection.
4. [entry.S](https://github.com/umicom-foundation/umicom-kernel/blob/main/programs/cvm/entry.S) receives the argument and requests EXIT.
5. [main.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/programs/cvm/main.c) checks and executes the arithmetic bytecode.

## Check your understanding

Why does the Kernel load an ELF program instead of treating bytecode as native instructions? Because the processor understands machine code; the native interpreter supplies the bytecode's meaning.

Why keep the interpreter budget and the Kernel timer? They bound different layers. The budget limits interpreter work; the timer limits how long the native process can run before returning control.

Does this demonstrate a complete C compiler or a general operating system? No. It demonstrates one small, checked language runtime inside an isolated native process. Variables, general functions, system libraries and additional hardware need their own implementations and tests.

[Return to Developing with Umicom](index.md) · [Study process and stream ownership](supervise-service-ownership.md)
