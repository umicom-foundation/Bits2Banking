<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/27-separate-host-target-and-image.md

PURPOSE:
Separate the host, target and image

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate the host, target and image

## Setup recap

Continue after the boot-evidence module. Keep the Umicom OS and Umicom C checkouts available for reading, and open boot/cvm-probe/CMakeLists.txt. A text editor is enough for this first study. Practical execution later requires a compiler that supports the selected target.

## Name the three different things

The host is the machine running your build tools. The target is the machine and operating-system interface for which those tools produce code. An image is the packaged collection that a boot process consumes. A Windows host executable, a Linux-target executable and an OS boot image are not interchangeable artifacts.

The small CVM probe is a useful example because it has the same arithmetic runtime source on each target. Shared source does not make the resulting machine code or system-library interface universal. A Windows .exe cannot be placed in a Linux guest and expected to run. The freestanding RISC-V Kernel envelope is different again.

## Read the CMake boundary

The probe project uses UMICOM_C_SOURCE_DIR to select the runtime source. It creates the runtime library and a native executable, without adding the source compiler. Native host process checks are registered only when CMAKE_CROSSCOMPILING is false. A cross build can finish successfully while providing no local launch result.

UMICOM_OS_CVM_STATIC requests a static link for a Linux target. It also requires the target static C library. The option does not turn a Windows compiler into a Linux compiler, change the root-filesystem inventory or register a startup service.

## Exercise

Make a table with host, target, output file and intended execution environment for three cases: Windows native probe, Linux probe and Kernel CVM envelope. Add a separate row for the OS archive. For each, write which command creates it and which observation would show it actually ran.

If your build succeeds but no native process tests appear, inspect the cross-compilation setting before assuming coverage vanished. Do not launch a foreign binary to obtain a misleading failure. Keep compilation evidence separate from process and boot evidence.

## Read the source

[Open the OS source](https://github.com/umicom-foundation/umicom-os/blob/main/boot/cvm-probe/CMakeLists.txt). Use the matching checkout for qualification.

## Continue learning

[Course contents](index.md) · [Previous: Design repeatable boot-evidence checks](26-design-repeatable-boot-evidence-checks.md) · [Next: Run a fixed runtime trace probe](28-run-a-fixed-runtime-trace-probe.md)
