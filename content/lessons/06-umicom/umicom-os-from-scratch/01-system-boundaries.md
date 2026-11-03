# A system has several layers

A kernel manages machine resources and provides controlled entry points. An operating system also needs startup policy, programs, files and tools. Umicom OS has a Linux-based image foundation and Framework-backed user-space software. Umicom Kernel is a separate native kernel project. Learning one does not establish that the other boots.

## Find the owners

1. Open `umicomOS/boot/foundation/init.c`. Identify the PID1 guard before privileged setup.
2. Open `umicomOS/boot/foundation/config.c`. This parser accepts a complete service graph before launch.
3. Open `Umicom-Applications/framework/src/os_image/prepare.c`. The host tool captures declared inputs; it is not the guest's init process.
4. Open `umicom-kernel/kernel/boot_services.c`. Its native process ownership belongs to a different runtime.

## Exercise

Draw four boxes: host build tools, image files, guest PID1 and guest services. Put the native Kernel in a separate diagram. For each arrow, write whether it transfers source, an executable, configuration or runtime observations.

## Check your understanding

<details>

<summary>Does a successful Windows application build prove that the OS boots?</summary>

No. It qualifies a host build. A boot claim requires execution evidence for a specific image, machine profile and firmware, including normal and recovery paths.

</details>

This course uses the hands-on systems-learning approach of [Linux From Scratch](https://www.linuxfromscratch.org/lfs/). These lessons and Umicom examples are original; they are not a reproduction of the LFS book.

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#os) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-os-from-scratch/lessons/01-system-boundaries.html) · [Learning sequence](../../../start/learning-sequence.md)
