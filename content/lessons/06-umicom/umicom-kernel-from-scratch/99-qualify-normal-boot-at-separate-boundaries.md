<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/99-qualify-normal-boot-at-separate-boundaries.md

PURPOSE:
Teach qualify normal boot at separate boundaries through the native Kernel coordinator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Qualify normal boot at separate boundaries

## Build an evidence chain

The coordinator tests answer whether given boundary outcomes lead to the intended next action. The controller tests answer how real jobs are admitted, retried and collected under their host model. Native image tests answer whether the configured guest can execute the corresponding machine path. A manual session answers whether actual input and shell operations work. Each result has a different scope.

## Run the hosted project deliberately

Use a native host C23 compiler. The coordinator targets compile the real normal_boot.c with explicit test observations and the existing recovery parser. Stop after a failed configure or build; a later test run may otherwise execute an older binary. These commands are an exercise for the reader, not a recorded passing result.

~~~powershell
Set-Location C:\umicom\umicom-kernel
cmake -S tests/boot_services -B build/host-boot-services -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/host-boot-services
ctest --test-dir build/host-boot-services -R "^kernel\.normal_boot\." --output-on-failure
~~~

## Record what the fixture does not execute

The 32 coordinator cases use four compiled profiles. They observe machine finish operations through a hosted jump, supply synthetic memory counters, and replace the shell call with a counter. No privileged instructions, real UART, hardware clock or user ELF execution occurs. A passing interactive-profile case means the coordinator reached its shell call; it does not mean a person successfully typed a command.

## Continue into native qualification

Keep skipped or unexecuted checks explicit. A host-only result cannot establish a physical USB boot, an optical ISO, a new CPU architecture or Secure Boot compatibility.

- Follow the Kernel normal-startup guide for the configured RISC-V machine.
- Retain separate outputs for automatic startup, required-job recovery and forced recovery.
- Launch the interactive system image and perform the documented input, file and shutdown exercises.
- Record source and local changes, image digest, toolchain, emulator version, machine arguments and actual results.

## Exercise and troubleshooting

The hosted cases pass while the guest prints nothing. Start before the C coordinator: inspect firmware entry, the linker map, loaded image and serial configuration. If the guest prints a recovery reason, follow that named boundary instead. Preserve the complete output and exact image before rebuilding; otherwise the next observation may no longer describe the same artifact.

Companion source: umicom-kernel/kernel/normal_boot.c and tests/boot_services/normal_boot_tests.c. Read docs/NORMAL_BOOT_COORDINATOR.md in the same Kernel checkout. Match source revisions before running the exercises.

[Course contents](index.md) · [Previous lesson](98-require-the-intended-recovery-cause.md)

[Next lesson](100-bind-a-guest-run-to-current-source.md)
