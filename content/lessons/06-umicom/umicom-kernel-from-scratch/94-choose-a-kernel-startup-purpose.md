<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/94-choose-a-kernel-startup-purpose.md

PURPOSE:
Teach choose a kernel startup purpose through the native Kernel coordinator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Choose a Kernel startup purpose

## Start with the question you want to answer

A successful boot is not one universal result. A diagnostic Kernel deliberately runs checks before reaching its final marker. A normal system image prepares a session without executing that cumulative sequence first. Recovery supplies a smaller inspection path when ordinary startup cannot proceed. Before choosing an executable, write down which behaviour you intend to observe.

## Read the existing image profiles

The Kernel build defines these profiles in cmake/NormalBoot.cmake. They inherit the established source graph but select different compile definitions and output locations. A shared source file does not make their execution paths identical. Keep the complete build result with the exact image you launched.

| Profile | Purpose | Important boundary |
| --- | --- | --- |
| system | Enter the normal shell after startup | Human input still needs a real session |
| recovery | Enter independent recovery directly | No allocator or job admission |
| startup-check | Complete normal startup and stop | Does not open the shell |
| recovery-check | Exercise a malformed required job | Accept only the intended failure |
| forced-recovery-check | Exercise the direct recovery selection | Physical owner must remain uninitialised |

## Find the decision in C

The normal coordinator publishes its ready marker after job cleanup and frame-accounting checks. The automatic build stops at that point. This excerpt shows the distinction; it is part of the Kernel, not a standalone hosted program.

~~~c
UmicomKernelConsoleWriteLine("UMICOM_KERNEL_NORMAL_STARTUP_READY");
#ifdef UMICOM_KERNEL_STARTUP_AUTOMATED
    UmicomStartupPoweroff();
#endif
UmicomKernelConsoleShellRun();
~~~

## Work through a misleading result

Suppose startup-check prints readiness and exits, but you have never entered a shell command. You may report the automatic startup result with its source and environment identity. You cannot report that interactive editing, file commands or keyboard recovery worked. Those actions were deliberately excluded from this image.

## Exercise and recovery

Choose a profile for each question: can the two startup jobs complete, can a user type help, and can recovery start without physical allocation? Answer: startup-check, system, and forced-recovery-check respectively. If the wrong profile was launched, retain its output but repeat the intended exercise with the correct image; do not relabel an old log.

Companion source: umicom-kernel/kernel/normal_boot.c and tests/boot_services/normal_boot_tests.c. Read docs/NORMAL_BOOT_COORDINATOR.md in the same Kernel checkout. Match source revisions before running the exercises.

[Course contents](index.md) · [Previous lesson](93-qualify-contiguous-memory-without-device-claims.md) · [Next lesson](95-follow-startup-owner-transitions.md)
