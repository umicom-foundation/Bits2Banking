<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/42-copy-and-verify-regular-file-media.md

PURPOSE:
Copy and verify regular-file media

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Copy and verify regular-file media

## Prepare the exercise

Create a fresh image and destination using the lab README. Do not reuse the intentionally changed image from the previous lesson. Review it and check the printed destination. Keep the fingerprint and confirmation from this new review. The application exposes only ordinary-file copying; physical drive selection is outside this lab.

## Execute the reviewed operation

Run each command separately and stop on an unexpected error. The copy should report that it copied and verified a new regular file. The independent verify operation should report equal contents, and the two hashes should agree. These are three related observations of a specific pair of files. None runs guest instructions.

UmiBootMediaApply consumes a plan once. The application destroys that plan on return and does not retry it in the background. A retry needs a new observation and a deliberate decision about any partial output. That rule keeps a failed transfer from being treated as an unobserved continuation of a previous approval.

```powershell
& $Lab copy $Image $Copy "PASTE_REVIEW_FINGERPRINT" "PASTE_REVIEW_CONFIRMATION"
& $Lab verify $Image $Copy
Get-FileHash -LiteralPath $Image, $Copy -Algorithm SHA256
```

## Preserve an existing destination

Repeat the same copy request after success. Review of the now-existing destination should fail and its bytes should remain unchanged. The exists CTest scenario preloads a small document, attempts the copy and compares the destination digest afterwards. Its purpose is to verify preservation, not merely that a function returned an error.

The confirmation scenario changes only the confirmation string and expects refusal before the destination is created. Together these cases separate admission failures from failures after writing has begun. A false success message is especially harmful here because it can cause later code to publish incomplete media.

## Interpret failure reports

UmiBootMediaReport distinguishes outputCreated, writeStarted and verified. A failed copy can leave a new partial file for diagnosis. Keep it marked as incomplete; do not rename it into a release artifact. The Framework API also supports a synchronous progress callback for cancellation. The lab deliberately passes NULL so you can first understand the simpler ownership path. A UI extension must not destroy its plan or mutate transfer inputs inside that callback.

After a successful copy, append a small note to a disposable copy and run verify again. It should refuse the changed length or contents. The tamper scenario performs that check. Verification observes the current files; it does not guarantee they cannot change later.

## Verify the whole extent, not just a prefix

The file's extent is its current length. A 2 MiB prefix can have an unchanged SHA-256 digest even after somebody appends 512 bytes. Reading only the length captured at open time cannot establish whole-file equality on its own.

Framework rechecks metadata through the same open native handle. Inspection checks the source after hashing and structural rereading. Apply checks it before destination acquisition and after streaming; read-back also checks the exact length of a regular-file target. The independent verify operation checks the copy's length after hashing. A changed length returns UMI_STATUS_INVALID_STATE and leaves verified false. A native query failure retains its own error status.

1. Keep the original source and destination private while copying. Linux file locks are cooperative: a different writer can ignore them.
2. Check the result of UmiBootMediaApply or UmiBootMediaVerifyFile before publishing output. Do not infer success from a matching displayed digest alone.
3. If the source grows during recheck, the new destination must remain absent. If growth happens after writing begins, keep the partial result and its failure report; it is not a release image.
4. Rebuild the Framework SDK used by the lab before qualifying a library change. Recompiling only the client against an old SDK does not exercise the new implementation.

Read the private BmCheckRegularSize helper in Framework's src/boot_media/io.c and its call sites in transfer.c. It inspects the pinned handle without reopening a pathname or accepting a larger read limit. Clients continue to call the public media API demonstrated in this lab.

The Framework extent regressions exercise fresh ordinary files. Linux adds deliberate append interference at several progress boundaries. These test callbacks violate the production no-mutation rule intentionally; never use that pattern in a UI. Run the full media suite in addition to focused extent cases, and record which platform-specific cases were present. No test result is implied by this lesson.

Even repeated size checks cannot guarantee a snapshot against arbitrary same-length concurrent rewrites, or prevent changes after return. Byte agreement remains separate from operating-system bootability and publisher authenticity.

## Review and recover

Keep diagnostics and partial files when a transfer fails. Correct the input, SDK or destination condition and choose a new output name for a fresh review. A matching copy is ready for subsequent release checks, but a bootable distribution still needs compatible content, loader configuration, firmware and startup evidence.

[Lab setup and complete commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md) · [Read the C23 application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Framework media contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/boot_media/media.h)

[Course contents](index.md) · [Previous lesson](41-refuse-a-changed-media-review.md) · [Next lesson](43-prepare-an-iso-through-native-services.md)
