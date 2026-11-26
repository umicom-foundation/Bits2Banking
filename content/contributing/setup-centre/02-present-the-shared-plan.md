<!--
Umicom Bits2Banking
File: content/contributing/setup-centre/02-present-the-shared-plan.md

PURPOSE:
Trace native Win32 controls into a pure Framework planner and back to a readable review.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Present the shared plan in Win32

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A Win32 adapter connects the Windows controls to a Framework operation. The existing launcher delegates to the shared adapter. Start by following [the Win32 launcher](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/setup_centre/windows_main.c), [the adapter](https://github.com/umicom-foundation/umicom-framework/blob/main/adapters/win32/setup_centre.c) and the [planner contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/setup_centre/boot_plan.h).

1. Find WM_COMMAND in the adapter. It is a Windows message sent for an action from a control or menu. Mark where a review action can read the current product, board, source, edition and desired output. Search for UmiSetupPlanBoot in the revision being reviewed. A revision that contains the planner without the UI connection can still be traced on paper.
2. Sketch one mapping card per control. For the architecture card, the displayed text RISC-V64 QEMU virt must produce UMI_SETUP_BOOT_RISCV64_VIRT. Keep the enum value attached to the control item or use an explicit mapping. Display order and translated labels can change.
3. Trace the call on the window thread. The planner performs a bounded, synchronous selection review. Render its machine, artifact, workflow and limitation after a successful call. Render a clear input error on a rejected request and clear any stale result from an earlier selection.
4. Change only the output from QEMU to VirtualBox for a standalone Kernel RISC-V64 example. Predict the displayed reason and which next action disappears. Changing it back can produce a fresh documented route.

**Expected result.** Both valid choices can produce a review. QEMU displays the documented route. VirtualBox displays unavailable with the limitation visible. Neither review starts a guest. When an invalid selection leaves the C output untouched, the adapter must avoid presenting an earlier plan as the new result.

For an accessibility review, read the status and the reason together. A narrow view or high zoom still needs a way to reach the complete text. Return keyboard focus to a useful control after a refused selection.

[Previous](01-describe-a-boot-choice.md) · [Workshop](index.md) · [Next · Worker and device boundaries](03-keep-review-and-work-separate.md)
