<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/71-claim-a-temporary-boot-report-name.md

PURPOSE:
Claim a temporary name for a boot report

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Claim a temporary name for a boot report

Lesson 70 followed a boot failure and a separate report-save problem. This lesson follows the writer before it can put any bytes in a new report. A **temporary file** gives the writer a place to prepare the next version while the last complete report keeps its published name.

## Claim a name for this attempt

In the saved Umicom OS test, the published name is `report`. The writer tries `report.tmp` first. If that name is occupied, it tries `report.tmp.1` and continues in order through `report.tmp.7`. There are eight choices in total. An occupied name may belong to another writer or an earlier attempt.

The writer uses exclusive creation. On Linux, `O_CREAT` with `O_EXCL` asks the operating system to create a new file and refuse an existing name in the same call. The successful call returns a file descriptor, the handle for writing to that newly opened file. In this exercise, an attempt owns a temporary name only after its exclusive creation succeeds. [Linux `open(2)`](https://man7.org/linux/man-pages/man2/open.2.html)

The error `EEXIST` means the name is taken. That is the one open error that advances the writer to another slot. An error such as `EACCES`, which can mean access is denied, stops the attempt.

~~~text
FOR each temporary name in the allowed order
    TRY to create the name exclusively
    IF creation succeeds
        RECORD the new file as owned by this attempt
        CONTINUE to the report-writing stage
    END IF
    IF the error is other than EEXIST
        STOP the attempt
    END IF
END FOR
STOP when all eight names are occupied
~~~

## Follow the names on paper

Draw eight boxes. Label the first `report.tmp` and the rest `.1` through `.7`. Before looking at the answers, mark the occupied boxes and trace where the writer stops.

| Starting condition | Open attempts | Acquired name |
| --- | ---: | --- |
| All names free | 1 | `report.tmp` |
| First name occupied | 2 | `report.tmp.1` |
| First seven names occupied | 8 | `report.tmp.7` |
| All eight names occupied | 8 | None |
| First name occupied, next open gives `EACCES` | 2 | None |

Now let the first two names be occupied and assume the third opens successfully. The predicted acquired name is `report.tmp.2`. The first two names stay outside this attempt's cleanup. If all opens fail, the writer has no new file to write, close, rename or remove.

This Umicom OS report writer chooses its own bounded temporary names. In the media exercise, the learner chooses the final destination; an occupied user-selected destination calls for a new reviewed choice. Keeping those two kinds of names separate makes it easier to decide who may retry.

The saved tests injected the open results and checked the attempted names, flags and recorded operations of `UmiOsWriteReport`. Real Linux filesystem behavior and a guest boot publish remain separate checks. The next lesson follows the file once the writer has acquired it.

[Course contents](index.md) · [Previous lesson · Keep the first boot failure when a report cannot be saved](70-keep-the-first-boot-failure.md) · [Next lesson · Keep a complete report through replacement](72-keep-a-complete-report-through-replacement.md) · [Read file effects separately from status](57-read-file-effects-separately-from-status.md) · [Retain failed media artifacts for recovery](62-retain-failed-media-artifacts-for-recovery.md) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/71-claim-a-temporary-boot-report-name.html)
