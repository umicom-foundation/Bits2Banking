# Your first user-space build

[Course contents](index.md) · [Next: Processes, output and exit status](02-processes-output-and-exit-status.md)

## User space comes first

Linux is a kernel, the part of a system that manages resources and mediates access to devices. A distribution adds tools, libraries and applications. A normal program runs in user space and asks the operating system for services. Writing such a program is a useful first step before studying kernel development.

Use a Linux environment with a C compiler installed. The course's Learning C lessons explain source files, functions and terminals. Open a terminal in a practice folder that you own. `pwd` shows the current directory; `ls` lists its entries. These are shell commands, not C statements.

## Build a complete small program

Save this as `hello.c`:

```c
#include <stdio.h>

int main(void)
{
    puts("Umicom learning workspace");
    return 0;
}
```

Run these commands one at a time:

```sh
cc -std=c17 -Wall -Wextra hello.c -o hello
./hello
echo $?
```

The example uses the C17 subset supported by common system compilers; Umicom's main implementation targets C23. `-o hello` names the executable. `./hello` means the file named hello in the current directory. Expect the message and then status `0`. Read any compiler diagnostic before running an older executable left from a previous successful build.

## Exercise and answer

Change only the message and rebuild. Expect the new message. Then remove the closing quote in your practice copy and compile. Expect a diagnostic and a nonzero compiler status. Restore the quote. A failed compile does not prove that the previous executable disappeared.

## Connect to Umicom

Open the activity project's `console.c` and CMake file. It calls a shared rule and uses a build description to locate its dependencies. Your one-file example teaches the individual compiler step; the larger example teaches reproducible dependency management. Neither exercise installs an operating system or changes a boot disk. Later modules distinguish the Umicom OS user-space components from the freestanding Umicom Kernel.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/console.c). Path: `labs/native/framework-activity/console.c`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://docs.kernel.org/process/howto.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-linux-development/lessons/01-your-first-user-space-build.html).

[Course contents](index.md) · [Next: Processes, output and exit status](02-processes-output-and-exit-status.md)

Sammy Hegab · Umicom Foundation · Original learning material.
