<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/40-own-a-reviewed-media-plan.md

PURPOSE:
Own a reviewed media plan

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Own a reviewed media plan

## Prepare the exercise

Use the image accepted in the preceding lesson and the $Copy path from the lab README. The parent directory must already exist and the destination itself must not exist. Keep the Framework lab executable and source open side by side. This lesson reads image metadata and prepares a plan; it does not start a copy.

## A plan has an owner

UmiBootMediaPlan is an opaque type: the header declares its name while Framework owns its internal representation. Your application receives a pointer and becomes responsible for releasing it. Initializing the pointer to NULL makes cleanup explicit even when review fails. Do not allocate the private structure or guess its size in application code.

```c
UmiBootMediaPlan *plan = NULL;
UmiBootMediaReport report = {0};
UmiStatus status = UmiBootMediaReviewFile(imagePath, newPath,
    &plan, NULL, NULL, &report);
if (status == UMI_STATUS_OK) {
    puts(UmiBootMediaPlanDestination(plan));
    puts(UmiBootMediaPlanFingerprint(plan));
    puts(UmiBootMediaPlanConfirmation(plan));
}
UmiBootMediaPlanDestroy(plan);
```

## Borrowed text is not an independent copy

The three getter results belong to the plan. They are useful while the plan is alive, but destroying the plan ends their lifetime. Printing each string immediately, as the lab does, is valid. Saving its pointer in a window and then destroying the plan would leave that window with invalid memory. A persistent interface must either retain the plan for the required lifetime or copy the text into its own checked storage.

The report has a different lifetime: it is a caller-owned value. That distinction is why a report can be inspected after plan destruction, whereas a getter pointer cannot. Draw both objects and label the direction of ownership before adding a progress callback or UI.

## Review has no destination side effect

Review should print a destination, a fingerprint and a CREATE confirmation. Test-Path should still return False. If it returns True, investigate the existing file; do not overwrite it merely to complete the lesson. The fingerprint binds the reviewed operation to its observed input and destination. The human-readable confirmation adds an explicit admission step, but neither value is proof that the image publisher is trustworthy.

Find where main.c destroys the plan on both successful and rejected paths. Explain why moving that destruction above printf would be incorrect. The review CTest scenario also checks that the destination remains absent, so a future implementation cannot quietly turn review into a copy.

```powershell
& $Lab review $Image $Copy
Test-Path -LiteralPath $Copy
```

## Review and recover

Choose a fresh destination if the requested file already exists. Keep the previous file and its history. If review fails, present that failure and avoid displaying old review values as if they describe the new request. The next lesson uses the review fingerprint to detect changes between review and execution.

[Lab setup and complete commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md) · [Read the C23 application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Framework media contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/boot_media/media.h)

[Course contents](index.md) · [Previous lesson](39-inspect-an-image-without-booting-it.md) · [Next lesson](41-refuse-a-changed-media-review.md)
