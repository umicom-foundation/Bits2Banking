<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/70-keep-the-first-boot-failure.md

PURPOSE:
Keep the first boot failure when a report cannot be saved

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep the first boot failure when a report cannot be saved

In the previous lesson you traced a blocked service to its first dependency problem. Now imagine that the OS also cannot save its report. There are two facts to keep: the reason the boot entered recovery and the stage at which the report file could not be saved.

## Before you begin

Draw two columns, one for the first reason the boot entered recovery and one for the phase of each attempted report save. Use the lesson’s sample serial evidence to fill them in.

## Read the serial evidence

A serial transcript is a separate text record from the boot console. Keep the entire transcript when the report file is missing or might be older than the last serial record.

1. Look for `UMICOM_BOOT_REPORT_SAVE_FAILED`. The phase `initial` belongs to the first report save. `progress` belongs to a save after a service succeeds. `final` belongs to the last save. Each marker tells you about one save attempt. A later save can succeed. If storage was unavailable and the OS skipped a save attempt, there is no failure marker for that attempt.
2. Read the version 1 report between `UMICOM_REPORT_BEGIN` and `UMICOM_REPORT_END`. The `mode` records the startup path selected during admission. The `state` can change to `recovery` later. The reason tells you why it entered recovery.
3. Put the reason and the failed phase in separate notes. An earlier service failure can still be the primary reason when the last file save fails. When the save is itself the first failure, the primary reason is `report-write`. A reason of `requested` records a choice to enter recovery, so an actual save failure can replace it with `report-write`.

## Work through three cases

Use the following paper model for a failed save. `none` means the boot has recorded no primary failure at this point.

~~~text
IF a report save fails
    Record the phase in the serial save marker
    IF the boot reason is none OR requested
        Set the boot reason to report-write
    END IF
    Enter or continue recovery
END IF
~~~

| Boot reason before the save | Failed save phase | Primary reason you should record | Separate note |
| --- | --- | --- | --- |
| `service-timeout` | `final` | `service-timeout` | The final report save failed. |
| `none` | `initial` | `report-write` | The first report save failed. The normal service loop is skipped. |
| `requested` | `final` | `report-write` | Recovery was requested and the final report save failed. |

A timeout can explain why the boot left the normal path. The final save marker explains why the saved report may be missing or stale. The marker by itself cannot tell you which reason came first.

## Check your understanding

On paper, plan two services. The first service succeeds and the OS counts it as completed. Its `progress` save fails. Then let the `final` save succeed. Write down the completed count, the primary reason, the one failed phase and whether the second service runs.

**Expected result.** One service completed. The failure selects `report-write` and stops the service loop before the second service. Keep the `progress` failure marker even though the final save succeeded. The report can still describe recovery because the earlier failure already changed the boot state.

Use the same two columns when reviewing Umicom OS. The hosted admission fixture checks the C function `UmiOsBootReasonAfterReportWriteFailure` with fixed inputs. The phase traces above follow the boot source in `boot/foundation/init.c`. A boot that actually writes a report and emits a marker needs separate evidence from the running OS. The sequence is explained in `docs/foundation/service-supervision.md` in the Umicom OS source tree.

[Course contents](index.md) · [Previous lesson · Follow the first blocked boot service](69-follow-the-first-blocked-boot-service.md) · [Make recovery decisions testable](07-boot-admission.md) · [Read a captured boot observation](19-read-a-captured-boot-observation.md) · [Read qualification evidence](06-read-qualification-evidence.md) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/70-keep-the-first-boot-failure.html)

[Next lesson · Claim a temporary name for a boot report](71-claim-a-temporary-boot-report-name.md)
