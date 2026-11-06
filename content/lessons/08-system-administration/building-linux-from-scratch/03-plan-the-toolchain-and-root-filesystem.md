# Plan the toolchain and root filesystem

[Course contents](index.md) · [Previous: A C program meets the host](02-a-c-program-meets-the-host.md)

## Separate the builder from the result

A toolchain is the compiler, assembler, linker and related components used to create programs. Build identifies the machine doing the compilation; host identifies where the resulting program will run; target is also relevant when that program is itself a compiler. These names become important when constructing tools for another environment.

A root filesystem is the directory tree a running system sees starting at /. It includes programs, libraries and configuration. It is not just the kernel image. A sysroot gives build tools a controlled view of target headers and libraries so they do not accidentally use unrelated host files.

```text
existing Linux host
    -> temporary tools
    -> target headers and libraries
    -> base programs and configuration
    -> bootable image and isolated boot verification
```

## Prepare a reproducibility notebook

1. Select one book edition and record its URL.
2. Check that edition's host requirements before downloading package sources.
3. Record package versions and verified source checksums.
4. Record the target architecture and intended virtual-machine environment.
5. Keep configure, build and check output in separate dated logs.
6. Stop at a failed prerequisite instead of building later layers on an unknown state.

This opening course intentionally gives no disk-formatting or bootloader-install command. Those operations require an exact device and image plan. A VM image is an appropriate later exercise, but even an image workflow needs backups and verified paths.

## Exercise

A program builds because it finds a library in the host's /usr directory, but that library is missing from the target root filesystem. What went wrong, and what should the build evidence record?

## Explained answer

The build used an undeclared host dependency. Record the actual include/library paths and target dependencies, then correct the toolchain/sysroot configuration. Do not fix it by copying arbitrary host directories into the image. Umicom OS packaging should make its required Framework and GTK runtime versions explicit and verify them in the intended runtime environment.

## Continue

The next module is host qualification and VM preparation. Use the existing Umicom OS and Kernel courses to compare their responsibilities while keeping the Linux-based distribution route separate from the native Umicom Kernel route.

## Continue learning

[Course contents](index.md) · [Previous: A C program meets the host](02-a-c-program-meets-the-host.md)

[Browser edition](../../../courses/building-linux-from-scratch/lessons/03-plan-the-toolchain-and-root-filesystem.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/console.c). This public revision matches the source inspected for this lesson.

[Primary reference](https://www.linuxfromscratch.org/lfs/view/12.4/).
