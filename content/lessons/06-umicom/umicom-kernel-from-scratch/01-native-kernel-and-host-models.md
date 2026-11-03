# Read a native kernel without booting it

Umicom Kernel owns its own memory, processes, traps and machine interfaces. Umicom OS's Linux-based foundation uses a different kernel. A native Kernel course must explain that distinction instead of presenting the projects as interchangeable images.

## Start with the source

1. Open `include/umicom/kernel/types.h` to see the native integer and size types.
2. Open `kernel/console_line.c`. It contains bounded text operations that do not require a hosted C runtime.
3. Read `kernel/console_internal.h`. Its byte operations keep metadata copies independent of libc.
4. Compare `tests/boot_services` with the architecture sources. The host tests deliberately model machine entry; they do not execute RISC-V instructions.

## Exercise

Classify a decimal parser, physical frame allocator, timer trap and UART driver. Which can be exercised directly on your development host? Which require a model or machine execution? Write the limitation beside each result.

The first lab uses a real production parser on the host. Memory mapping, interrupts, process isolation and booting will need additional labs. Nothing in this hosted demonstration proves that a Kernel image boots.

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#kernel) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/01-native-kernel-and-host-models.html) · [Learning sequence](../../../start/learning-sequence.md)
