<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/135-check-boot-mode-and-process-exit.md

PURPOSE:
Check boot mode and process exit separately

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check boot mode and process exit separately

The previous lesson counted complete handoff records. An automated boot check also needs to know which boot path ran and how the process ended. On your worksheet, ask whether the expected boot path reported readiness and whether the process exited successfully. Each answer needs its own evidence.

## Choose the expected path before reading the output

The Umicom Kernel handoff runner checks three separately selected RISC-V images. A **terminal path** is the path that finishes that automated boot. Use the expected image to choose which complete readiness line belongs in its serial output.

| Expected image | Complete readiness record | Extra recovery evidence |
| --- | --- | --- |
| Normal startup | `UMICOM_KERNEL_NORMAL_STARTUP_READY` | The expected path finishes normal startup. |
| Required-service recovery | `UMICOM_KERNEL_RECOVERY_SELECTION_READY` | `recovery.reason=required-startup-service` |
| Forced recovery | `UMICOM_KERNEL_RECOVERY_SELECTION_READY` | `recovery.reason=forced-recovery`. This image makes no memory reservation, handoff or placement claim. |

Two opposing readiness records make the path ambiguous. A service-recovery transcript with both recovery reasons also fails the selected-mode check. The two admitted-memory paths still need the memory and handoff evidence from the previous lesson.

## Keep the answers in separate columns

The runner asks CMake to save three observations. It receives the process result, the captured serial standard output and the host diagnostic standard error separately. The two streams are separate channels of bytes. A process result can be an exit code or an error description. The runner checks for exit code `0` and looks for the expected boot records in the serial output. [CMake process results and streams](https://cmake.org/cmake/help/latest/command/execute_process.html#command:execute_process)

Draw a table on paper with one column for each observation. Predict what the runner can conclude from the following saved synthetic cases.

| Practice case | Process result | Readiness evidence | Expected check |
| --- | --- | --- | --- |
| Canonical run of each selected image | `0` | Each image has its own complete readiness on serial output. | Accept each expected path. |
| Status failure | `3` | Serial output looks like a normal startup. | Refuse because the process ended with an error. |
| Readiness on the diagnostic stream | `0` | The normal readiness line is only in host standard error. | Refuse because serial output lacks the required record. |
| Placement totals disagree | `0` | A normal readiness line is on serial output. | Refuse because the reported memory totals do not agree. |

The host integration fixture supplied those process and stream values to the runner. It checked the original exit and placement guards alongside the revised record checks. Keep a copy of the inputs and the selected mode together when you repeat the worksheet for a future boot check. A live QEMU run and physical target qualification give separate evidence about what the Kernel actually did.

[Course contents](index.md) · [Previous lesson · Count complete boot handoff records](134-count-complete-boot-handoff-records.md) · [Qualify normal boot at separate boundaries](99-qualify-normal-boot-at-separate-boundaries.md) · [Preserve startup stream identity](97-preserve-startup-stream-identity.md) · [Umicom OS · Read a captured boot observation](../umicom-os-from-scratch/19-read-a-captured-boot-observation.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/135-check-boot-mode-and-process-exit.html)

[Next lesson · Review one Kernel ELF from a partial build record](136-review-one-kernel-elf-from-a-partial-build.md)
