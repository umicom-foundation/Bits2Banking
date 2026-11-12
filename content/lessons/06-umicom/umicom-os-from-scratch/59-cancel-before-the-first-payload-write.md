<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/59-cancel-before-the-first-payload-write.md

PURPOSE:
Teach cancel before the first payload write through the installed Framework media client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Cancel before the first payload write

## Compare two early boundaries

The recheck phase reads the current source and compares it with the reviewed plan before acquiring the destination. The first write-phase callback runs after regular-file acquisition but before the first payload write. Cancelling at these two points must produce different filesystem observations even though both operations return cancellation.


~~~powershell
& $Lab copy-until $Image $Copy "PASTE_REVIEW_FINGERPRINT" "PASTE_REVIEW_CONFIRMATION" recheck
# Choose a different new destination, review it, then repeat with phase write.
~~~


## Prepare each experiment independently

Use the existing lab README to build against a matching installed Framework and generate the synthetic practice image. For each experiment choose a new output path and run review. Copy the exact fingerprint and confirmation from that review. A destination path is part of the plan identity, so tokens from the previous path cannot approve the new experiment.


| Stop phase | Expected new output | Expected flags: created / write / verified |
| --- | --- | --- |
| recheck | Absent | 0 / 0 / 0 |
| write | Retained empty regular file | 1 / 0 / 0 |


## Check the prediction

- Capture stdout, stderr and the exit code from each owner-run command. Cancellation is a non-success result.
- For recheck, confirm the destination does not exist. For write, inspect its length and expect zero bytes.
- Read cancel-recheck and cancel-write in check.cmake. Notice that the tests preserve scratch directories rather than deleting failed artifacts.


## Expected observation and recovery

An empty file after the write-phase stop is consistent with exclusive creation; it is not evidence of an unexpected payload write. A second attempt using that same path should be refused because it now exists. Preserve it, choose another path and review again. Do not weaken exclusive creation to make a lesson retry appear successful, and do not substitute a physical drive for the regular-file output.

[Complete application](../../../../labs/native/framework-boot-media/main.c) · [Lab setup and recovery](../../../../labs/native/framework-boot-media/README.md)

[Course contents](index.md) · [Previous lesson](58-own-a-synchronous-progress-context.md) · [Next lesson](60-interpret-cancellation-after-payload-writing.md)
