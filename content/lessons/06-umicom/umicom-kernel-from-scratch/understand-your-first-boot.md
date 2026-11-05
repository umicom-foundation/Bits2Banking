# Umicom Kernel from Scratch: understand your first boot

## Goal and starting point

By the end you will explain what starts a kernel, distinguish a host from a
guest, and identify the real source files responsible for a typed command.
Start with [Introduction to Computers](../../../courses/learning-computer-architecture/index.html).
For reading the C snippets later, complete the first functions and arrays
sections of [Learning C](../../../courses/learning-c/index.html).

You do not need to modify boot code or write a disk in this lesson. A **kernel**
manages the processor, memory and access to devices. An **operating system**
usually adds programs, files, accounts and other services around a kernel.
Having a kernel does not automatically provide a desktop or a login screen.

## 1. Follow the journey

```text
Your Windows or Linux computer (host)
  QEMU creates a virtual RISC-V machine (guest)
    entry code establishes the processor's starting environment
      Kernel initialises memory and services
        serial console reads input
          command engine uses the RAM filesystem or process services
```

**RISC-V** names the processor instruction set used by this native kernel.
**Assembly** is a textual way to name instructions closely related to that
processor. **C** expresses most services at a higher level. A **serial console**
is a stream of text and input bytes, not a graphical desktop.

QEMU's `virt` machine is a documented virtual board. A physical computer has
its own firmware and devices, so a virtual-board pass does not show that any
physical computer will boot the same image. See the
[QEMU board reference](https://www.qemu.org/docs/master/system/riscv/virt.html).

## 2. Build and launch one existing system

Follow [Your first Umicom Kernel session](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_SYSTEM_SESSION.md).
Its local path is `umicom-kernel/docs/FIRST_SYSTEM_SESSION.md`. Complete setup,
configure, build and tests before running the interactive image. Keep the
timestamped logs. Stop on the first failed step.

The interactive executable is `umicom-system.elf`. The diagnostic executable
`umicom-kernel.elf` runs checks and finishes. ELF describes an executable
container; neither name identifies a bootable CD image. There is currently
no native Kernel USB installer or account-creation command.

## 3. Observe one complete input/output example

Type these commands at the guest prompt:

```text
help files
create /notes/lesson.txt
write /notes/lesson.txt "The kernel keeps this note in memory"
cat /notes/lesson.txt
```

The path begins with `/`, the guest filesystem root. A **path** names an item
and its containing folders. The quotation marks group the sentence as one
argument. An **argument** is information supplied to a command. `cat` should
display the sentence; it reads a file and writes the text to the console.

```text
keys -> accepted line -> command and arguments -> file service -> console text
```

Now type `append /notes/lesson.txt " until shutdown"`, then repeat `cat`.
The extra words should appear at the end. Type `poweroff` when finished. This
RAM file will not survive the guest shutdown. The Windows source file and
your host logs are separate and remain where you saved them.

## 4. Read the real implementation in order

Open these files in your editor. Locate the named symbol with text search:

1. `umicom-kernel/kernel/console_line.c`: find
   `UmicomKernelConsoleLineFeed`. It receives one input byte and decides when
   a complete line can be used. An incomplete line is not yet a command.
2. `umicom-kernel/kernel/console_shell.c`: find
   `UmicomKernelConsoleShellExecute`. It parses words and chooses a command.
   Then find `UmicomShellTopicHelp` to see the text shown by `help files`.
3. In the same file, find `UmicomShellWrite`. It distinguishes replacing from
   appending. This is the behaviour you observed, not a second lesson-only
   imitation of file storage.
4. `umicom-kernel/kernel/ramfs.c` implements the memory-backed filesystem.
   Leave its allocator details for later lessons; first identify the boundary
   between command presentation and file operations.

The [console header](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/console_shell.h)
documents ownership. **Ownership** answers who must keep memory alive and who
must release it. The console retains its resources until they are closed; a
callback must not start another command while the current command is busy.

## 5. Check your understanding

**Question:** why does typing text into the guest not change a C source file?
**Answer:** console text is input to an already-compiled program. It can request
only commands that program implements. Editing source happens in the host editor.

**Question:** does `help programs` start a program? **Answer:** no. It describes
`run` and `runrw`; launching requires a separate explicit command.

**Question:** why does the lesson avoid a USB writer? **Answer:** this build
targets a virtual board, and its ELF has no physical installation layout.

Continue with [Read a native kernel without booting it](../../../courses/umicom-kernel-from-scratch/lessons/01-native-kernel-and-host-models.html),
then follow that course's numbered lessons. Those lessons progressively explain
the input limits and ownership rules used here. Keep the existing sequence;
this orientation prepares you for it rather than replacing its lessons.
