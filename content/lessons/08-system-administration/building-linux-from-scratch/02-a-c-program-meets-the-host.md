# A C program meets the host

[Course contents](index.md) · [Previous: What makes a Linux system](01-what-makes-a-linux-system.md) · [Next: Plan the toolchain and root filesystem](03-plan-the-toolchain-and-root-filesystem.md)

## A small experiment with a clear boundary

This lesson runs on an existing Linux system. It does not require root privileges, replace a kernel or create a boot image. A terminal accepts commands; the compiler builds a program; the program returns an exit status to the terminal's shell.

Save this original example as hello.c in a directory you choose:

```c
#include <stdio.h>

int main(void)
{
    if (puts("Hello from a user-space C program.") == EOF)
        return 1;
    return 0;
}
```

stdio.h declares standard input/output functions. puts writes the text followed by a newline. EOF is the failure result we check here. Returning zero reports success by this program's convention. The executable still depends on the host environment and libraries used to build it.

## Optional commands in a Linux shell

```sh
cc -std=c17 -Wall -Wextra -Wpedantic hello.c -o hello
./hello
printf 'exit status: %s\n' "$?"
```

Run the commands one at a time and stop on a compiler error. This sample uses C17-compatible syntax so it can illustrate a host baseline before the C23 toolchain is built. Umicom's main source standard remains C23. The expected message is the string above, followed by exit status 0 when output succeeds.

## Follow the layers

1. Source contains the requested behaviour.
2. Compilation and linking produce an executable for a target environment.
3. The operating system loads the program and its required runtime components.
4. The C library and system interfaces cooperate to write output.

The related Framework activity console example shows a real application entry point. Read its README and build configuration to identify dependencies before trying it in a newly constructed system.

## Exercise

Why might copying hello to another machine fail, even though both machines run Linux? List two causes.

## Explained answer

The processor architecture may differ, or the expected runtime loader/libraries may be absent or incompatible. File permissions can also prevent execution. A useful report records the compiler, target, linkage and observed error rather than only saying Linux does not work.

## Continue learning

[Course contents](index.md) · [Previous: What makes a Linux system](01-what-makes-a-linux-system.md) · [Next: Plan the toolchain and root filesystem](03-plan-the-toolchain-and-root-filesystem.md)

[Browser edition](../../../courses/building-linux-from-scratch/lessons/02-a-c-program-meets-the-host.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/console.c). This public revision matches the source inspected for this lesson.

[Primary reference](https://www.linuxfromscratch.org/lfs/view/12.4/).
