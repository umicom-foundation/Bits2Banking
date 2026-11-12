<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/41-refuse-a-changed-media-review.md

PURPOSE:
Refuse a changed media review

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Refuse a changed media review

## Prepare the exercise

Complete the review lesson and keep the exact fingerprint and confirmation it printed. Use only the synthetic image in your unique lab directory. The following mutation changes an ordinary practice file; it is not a recipe for modifying a distribution or a device.

## Time passes between review and action

A file can change after a person reviews it. The application therefore reconstructs current observations when copy is requested and sends the earlier accepted values to UmiBootMediaApply. This is a comparison of reviewed intent with current state. It does not make a mutable pathname permanently safe, and the Framework transfer implementation retains its own handle and recheck rules.

Read the copy branch in main.c. The fingerprint passed to Apply comes from argv[4], not from UmiBootMediaPlanFingerprint(plan). Replacing it with the new plan value would silently approve the new observation. A confirmation control is useful only when it authorizes the exact operation that was presented.

```c
status = UmiBootMediaReviewFile(imagePath, newPath, &plan, NULL, NULL, &report);
if (status == UMI_STATUS_OK) {
    status = UmiBootMediaApply(plan, reviewedFingerprint,
        reviewedConfirmation, NULL, NULL, &report);
}
UmiBootMediaPlanDestroy(plan);
```

## Try a deliberate stale observation

Paste the values from before the mutation. The copy should return a nonzero status and leave the destination absent. The added sector preserves sector alignment while changing the length and digest; the stale CTest case exercises the same idea using a different fill byte. Record the actual refusal instead of assuming a particular diagnostic string.

Do not continue by automatically substituting a newly printed fingerprint. First inspect the changed image and decide whether the change was expected. For further copying exercises, create a fresh practice image in another new directory, then inspect and review it. This keeps the original failed experiment available for comparison.

```powershell
$ExtraSector = [byte[]]::new(512)
$Stream = [System.IO.File]::Open($Image, [System.IO.FileMode]::Append, [System.IO.FileAccess]::Write)
try { $Stream.Write($ExtraSector, 0, $ExtraSector.Length) } finally { $Stream.Dispose() }
& $Lab copy $Image $Copy "PASTE_OLD_FINGERPRINT" "PASTE_OLD_CONFIRMATION"
Test-Path -LiteralPath $Copy
```

## Separate identity from provenance

A digest identifies observed bytes for comparison. It does not tell you who produced them, whether a signing key is trusted or whether the software is safe to execute. A distribution workflow needs an independently reviewed source and signing policy in addition to byte checks. In this laboratory, the generator is known teaching source and the image remains non-bootable.

## Review and recover

If the changed image is copied using the old fingerprint, retain both files and the exact command and stop: the admission contract did not behave as expected. If the image is refused during inspection instead, distinguish a structural failure from a stale-plan failure; both prevent writing, but they diagnose different conditions. Do not mark the stale-review check as observed without recording which path rejected it.

[Lab setup and complete commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md) · [Read the C23 application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Framework media contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/boot_media/media.h)

[Course contents](index.md) · [Previous lesson](40-own-a-reviewed-media-plan.md) · [Next lesson](42-copy-and-verify-regular-file-media.md)
