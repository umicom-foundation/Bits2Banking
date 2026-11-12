<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/60-interpret-cancellation-after-payload-writing.md

PURPOSE:
Teach interpret cancellation after payload writing through the installed Framework media client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Interpret cancellation after payload writing

## A late stop has different evidence

The flush, verify and finished phases occur after the lab has attempted the complete payload. A cancellation request there cannot undo accepted writes. Framework retains the regular-file output, reports cancellation and leaves verified false. An output that happens to contain all expected bytes does not change the meaning of that transfer result.


| Stop phase | Work already reached |
| --- | --- |
| flush | Payload writing completed; the explicit flush is about to run. |
| verify | The explicit flush succeeded; readback is about to proceed. |
| finished | Required readback, extent checks and handle release succeeded before the final callback. |


## Read the completion order

Locate the final lines of UmiBootMediaApply. Checked handle release precedes the finished notification, and verified is assigned only after that callback accepts completion. Returning nonzero from the finished callback still cancels the operation. This is the documented callback policy, not proof that earlier bytes were rolled back or that the file is bootable.


~~~c
if (s == UMI_STATUS_OK)
    s = BmTick(r, UMI_BOOT_MEDIA_FINISHED, bytes + tail, bytes + tail, cb, ctx);
r->verified = s == UMI_STATUS_OK;
~~~


## Run a separate observation

- Use a fresh reviewed destination for each of the three late-stop phases.
- Retain the cancelled transfer report, including output-created=1, write-started=1 and verified=0.
- Run the separate verify command against the retained regular file and source. Save its result separately instead of replacing the original report.


## Expected observation and recovery

The synthetic file exercises expect a later comparison to find equal bytes. That later success is a new read-only observation, with no creation or write effect. The CTest script saves cancellation.txt and later-verification.txt separately. A different installed version or unexpected I/O error may produce another result; retain that evidence and diagnose it. None of these checks executes firmware or starts an operating system.

[Complete application](../../../../labs/native/framework-boot-media/main.c) · [Lab setup and recovery](../../../../labs/native/framework-boot-media/README.md)

[Course contents](index.md) · [Previous lesson](59-cancel-before-the-first-payload-write.md) · [Next lesson](61-check-native-release-without-retrying-handles.md)
