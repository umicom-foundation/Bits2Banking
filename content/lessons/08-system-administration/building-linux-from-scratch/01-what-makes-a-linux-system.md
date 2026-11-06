# What makes a Linux system

[Course contents](index.md) · [Next: A C program meets the host](02-a-c-program-meets-the-host.md)

## The kernel is one part of the system

Linux is a kernel: it manages resources and provides interfaces used by programs. A usable Linux system also includes libraries, commands, configuration, services and a way to start them. A desktop adds graphical services and applications. Compiling one C program does not build an entire operating system.

Read the first C and Linux development lessons before practical work. These opening pages can be followed without changing your disks. Later construction should take place in an isolated virtual machine with recoverable snapshots, not on the machine holding your only source copies.

```text
firmware -> bootloader -> Linux kernel -> first user-space process
                                               |
                                               v
                                    services -> shell -> applications
```

User space is where ordinary programs execute with limited privileges. Kernel space has different privileges and interfaces. A hosted C program can use a library's printf function; a freestanding kernel environment cannot assume the same library exists.

## Relate the pieces to Umicom

Umicom Framework provides reusable application services. A Linux-based Umicom OS profile would need a kernel, root filesystem, packages and startup configuration around those applications. Umicom Kernel is a separate kernel project. Building that project is not the same operation as building the Linux kernel, and a host application window is not proof of a bootable system.

## Exercise

Classify these items: a kernel image, a C compiler, a GTK4 library, a shell, a user account database and an Umicom executable. Which are needed merely to run a prebuilt console program?

## Explained answer

The kernel supplies operating-system services; a compiler builds programs; GTK4 supports graphical applications; a shell runs commands; account data supports user identity; the executable is an application. A prebuilt console program needs the kernel and whatever runtime dependencies it was built for, not necessarily a compiler or GTK4. Precise dependencies come from the executable's build and linkage.

## Reading baseline

Linux From Scratch 12.4 is a fixed reading reference for this course's opening plan, not a claim about the newest available release. Later build instructions must use one complete, internally consistent book edition and its package versions.

## Continue learning

[Course contents](index.md) · [Next: A C program meets the host](02-a-c-program-meets-the-host.md)

[Browser edition](../../../courses/building-linux-from-scratch/lessons/01-what-makes-a-linux-system.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/console.c). This public revision matches the source inspected for this lesson.

[Primary reference](https://www.linuxfromscratch.org/lfs/view/12.4/).
