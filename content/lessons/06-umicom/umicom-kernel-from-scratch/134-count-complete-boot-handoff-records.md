<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/134-count-complete-boot-handoff-records.md

PURPOSE:
Count complete boot handoff records

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Count complete boot handoff records

A startup transcript is the text a Kernel writes to its console while it starts. Some lines are short status records that a checker can read. A **handoff** here is the checked description of memory passed to the next part of startup. A complete line records that the Kernel admitted it. A note can contain the same words while describing something else.

## 1. Mark the complete records

Read these lines from a synthetic normal-startup transcript. The exercise also supplies a separate memory-placement line. Keep its values fixed for every round.

~~~text
boot.memory=reserved
boot.handoff=validated
boot handoff: riscv64 ram=1 reserved=2
UMICOM_KERNEL_NORMAL_STARTUP_READY
~~~

Underline the memory reservation line and circle the handoff status immediately after it. The summary describes one RAM range and two reserved ranges. Box the final line, which records normal startup readiness. The checker expects exactly one complete `boot.handoff=validated` line and exactly one normal readiness record.

## 2. Change one line at a time

Start with the same transcript for each row. Cover the answer column and count the complete handoff status lines on paper.

| Change | Complete handoff status lines | Expected check |
| --- | --- | --- |
| Leave the lines as shown. | 1 | Accept. |
| Replace the handoff status with `boot.handoff=validated-note`. | 0 | Refuse. The longer line has no exact match. |
| Keep the handoff status and append `diagnostic note: prior marker boot.handoff=validated; reconsidered`. | 1 | Accept. The note is outside the status count. |
| Write another copy of the handoff status directly under the first. | 2 | Refuse. Both adjacent lines count. |
| Add `-note` to the end of the readiness line. | 1 | Refuse. The readiness line has changed. |
| Leave the text as shown and use CRLF for its line endings. | 1 | Accept. |
| Leave off the line ending after the final readiness record. | 1 | Accept. The end of the input completes the last line. |

**LF** is a line-feed character. **CRLF** pairs a carriage return with a line feed. The checker treats those two line endings alike and compares the text between them.

The Kernel script looks for the marker between two line boundaries. It stops looking after the second exact copy because it only needs three answers for a required record. It can be absent, present once, or present more than once. [CMake literal string search](https://cmake.org/cmake/help/latest/command/string.html#search-and-replace-with-plain-strings)

~~~text
CONVERT each CRLF pair to LF
READ one complete line at a time, including the last line
COUNT exact matches for the expected handoff and readiness records
REQUIRE one of each, with the handoff following the memory reservation
CHECK the complete summary and the records expected for this boot mode
~~~

## 3. Keep the result with its evidence

All 19 host fixture checks matched their expected accept or refuse decision on synthetic transcripts. A guest test also needs the selected image, emulator result and actual startup output. When reviewing a refusal, keep the transcript as captured and record which expected line was missing, altered or repeated.

[Course contents](index.md) · [Previous lesson · Check the configured Kernel platform](133-check-the-configured-kernel-platform.md) · [Next lesson · Check boot mode and process exit separately](135-check-boot-mode-and-process-exit.md) · [Observe the boot reservation plan](128-observe-the-boot-reservation-plan.md) · [Encode a boot handoff through the Kernel](86-encode-a-boot-handoff-through-the-kernel.md) · [Umicom OS · Read a captured boot observation](../umicom-os-from-scratch/19-read-a-captured-boot-observation.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/134-count-complete-boot-handoff-records.html)
