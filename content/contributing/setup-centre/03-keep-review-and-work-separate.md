<!--
Umicom Bits2Banking
File: content/contributing/setup-centre/03-keep-review-and-work-separate.md

PURPOSE:
Teach review purity, Win32 worker ownership and device admission using real interfaces.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep review, worker and device responsibilities clear

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The planner maps a choice to a route. Later a user may supply an actual file, ask a worker to process it and review the result. Physical device writing has separate requirements. In this lesson, draw those decisions and walk through a fictional cancellation.

1. In the [planner header](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/setup_centre/boot_plan.h), underline the sentence listing what review does. The review receives selection values and returns stable text. It does no file or process work.
2. Find WM_SETUP_PROGRESS and WM_SETUP_DONE in the [native Windows adapter](https://github.com/umicom-foundation/umicom-framework/blob/main/adapters/win32/setup_centre.c). Trace which code posts work results and which window thread updates controls. Write down who owns a progress payload when the message is sent successfully and how the sender handles a failed post.
3. Draw a separate row for a potential device workflow. Place target discovery, source verification, plan review, exact confirmation, apply and readback in that order. The [media command contract](https://github.com/umicom-foundation/umicom-framework/blob/main/src/boot_media/cli.c) has separate commands for those operations. Read the [ordinary-file transfer exercise](../../simple-steps/boot-media/inspect-and-copy.md) if you want to practise.
4. Walk this example on paper. The user reviews a build route and dismisses its next step before choosing any media. Later they review an image path, then the file digest differs at recheck. Write the last permitted action in both cases.

**Expected result.** In the first case, the operation log ends at review and no worker or device is opened by that review. In the second, the changed digest invalidates the old review, and a worker must refuse to proceed on it. A fresh review needs independently trusted input. A physical target also needs a qualified release path and its own verified identity.

A worker may need time to stop. Preserve its state long enough to consume completion and close owned resources. On a physical workflow, a stop after writes begin may leave a partial target and needs explicit reporting. Leave that case to a qualified device workflow and use a paper trace here.

[Previous](02-present-the-shared-plan.md) · [Workshop](index.md) · [Next · Native verification](04-verify-a-native-review.md)
