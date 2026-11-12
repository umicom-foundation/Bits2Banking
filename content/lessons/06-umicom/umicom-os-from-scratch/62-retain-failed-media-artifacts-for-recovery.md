<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/62-retain-failed-media-artifacts-for-recovery.md

PURPOSE:
Teach retain failed media artifacts for recovery through the installed Framework media client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Retain failed media artifacts for recovery

## Before you begin

Create a dedicated scratch directory for the regular-file media exercises and keep a copy of the original input identity. Prepare separate destination names for the first attempt and any later retry. Decide where status, phase, size and digest observations will be recorded before invoking the client.

## Choose preservation before retry

After a failed transfer, the most useful evidence is often the source identity, requested destination, report and retained output. Automatic deletion would hide whether creation or writing happened. The existing lab deliberately creates a unique scratch directory for each test and never removes its artifacts. Treat a partial image as diagnostic material, not as a ready distribution.


## Build a small evidence record

- Record the executable path, source revision and installed Framework prefix used for the operation.
- Keep the original review fingerprint and confirmation with the exact source and destination paths.
- Save stdout, stderr, exit status, final report flags, file length and a digest when the file exists.
- Record any later verification as a separate observation with its own time and executable identity.


## Use another destination deliberately

A retained output occupies its path even when its length is zero. Exclusive creation must refuse another copy to that path. Pick a new regular-file destination and review it again. Do not automatically replace the user-supplied token with a freshly generated one inside the application. Doing so would silently approve changed source or destination observations.


~~~powershell
& $Lab review $Image $NewCopy
# Read the new destination and tokens before issuing the next copy.
& $Lab copy $Image $NewCopy "NEW_REVIEW_FINGERPRINT" "NEW_REVIEW_CONFIRMATION"
~~~


## Investigate contradictory evidence

If a success report accompanies different hashes, stop distribution and retain both files. If an early refusal created a file, compare the actual phase and the installed service revision before assuming the report is wrong. The no-memory and close-error unit scenarios require controlled injection; a normal console run cannot reliably reproduce them by choosing a special filename.


## Keep the qualification boundary clear

The supplied image is a synthetic partition-table fixture with no working operating system. Copying, hashing and retaining it teach recovery ownership. They do not establish signature trust, removable-device identity, optical burning support or firmware compatibility. Extend the evidence chain only with observations actually made in the appropriate environment.

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Complete application](../../../../labs/native/framework-boot-media/main.c) · [Lab setup and recovery](../../../../labs/native/framework-boot-media/README.md)
-->
[Complete application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md)

[Course contents](index.md) · [Previous lesson](61-check-native-release-without-retrying-handles.md) · [Next lesson](63-qualify-installed-media-recovery-behaviour.md)
