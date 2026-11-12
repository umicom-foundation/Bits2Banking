<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/97-preserve-startup-stream-identity.md

PURPOSE:
Teach preserve startup stream identity through the native Kernel coordinator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Preserve startup stream identity

## Packets and lines have different boundaries

A program can write one line through several calls. Its output queue preserves packets, while the terminal presents lines. Printing a prefix for every packet would split words unnecessarily. Keeping a prefix forever would mix different producers. The coordinator therefore tracks the current job, stream selector and whether a line remains unfinished.

## Treat stderr as a separate owner

A single job can alternate stdout and stderr. If stdout ends with a partial word, stderr must not inherit that line as though it were ordinary output. A stream change ends the prior line and starts an explicitly labelled one. A different job also ends the prior line. Empty packets contain no bytes and do not change line ownership.

~~~c
if (!packet->bytes) return;
if (umicomStartupOutputOwner != name ||
    umicomStartupOutputSelector != packet->selector)
    UmicomStartupOutputFinish();
umicomStartupOutputOwner = name;
umicomStartupOutputSelector = packet->selector;
~~~

## Keep status text under Kernel ownership

Before a recovery reason or the final startup report is printed, the coordinator finishes any partial job line. Without that boundary, a message could appear as “[job] partialboot memory: reserved”. The bytes might all exist, but their apparent author would be wrong. The fix adds a newline only when the current line needs one; it does not discard accepted job output.

## Read escaped bytes literally

Startup jobs cannot send terminal escape commands through this path. Printable characters are emitted, newline ends a line, and other bytes are shown as hexadecimal escapes. A displayed backslash-x sequence describes a byte; it is not a request to execute a terminal control. The control-byte regression includes NUL, escape, carriage return, tab and a non-ASCII byte.

## Exercise and troubleshooting

Trace stdout “one”, an empty stderr packet, and stdout “ two\n”. The expected result is one stdout line with a single prefix. Now replace the empty packet with “warning”: the selector change must introduce a new stderr line. If the result is wrong, inspect ownership transitions before changing packet sizes or suppressing the producer.

Companion source: umicom-kernel/kernel/normal_boot.c and tests/boot_services/normal_boot_tests.c. Read docs/NORMAL_BOOT_COORDINATOR.md in the same Kernel checkout. Match source revisions before running the exercises.

[Course contents](index.md) · [Previous lesson](96-read-linker-boundaries-as-addresses.md) · [Next lesson](98-require-the-intended-recovery-cause.md)
