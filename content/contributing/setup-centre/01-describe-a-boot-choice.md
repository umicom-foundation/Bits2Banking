<!--
Umicom Bits2Banking
File: content/contributing/setup-centre/01-describe-a-boot-choice.md

PURPOSE:
Teach typed requests and readiness results using the shared C23 planner.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Turn a boot choice into a C23 request

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An enum names possible choices, such as QEMU or an ISO file. A structure keeps the choices together so Framework can judge their compatibility. Open the [planner header](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/setup_centre/boot_plan.h) and [implementation](https://github.com/umicom-foundation/umicom-framework/blob/main/src/setup_centre/boot_plan.c) in a matching Framework checkout.

1. Write this request in ordinary words. Use a reviewed, prebuilt independent Umicom Kernel for RISC-V64 in QEMU.
2. Match each part to a field. The independent Kernel has the standalone edition and no OS application flags.

   ~~~c
   /* Keep product, board, source and output together for one review. */
   const UmiSetupBootSelection request = {
       .product = UMI_SETUP_BOOT_KERNEL,
       .target = UMI_SETUP_BOOT_RISCV64_VIRT,
       .edition = UMI_SETUP_BOOT_STANDALONE,
       .source = UMI_SETUP_BOOT_PREBUILT,
       .output = UMI_SETUP_BOOT_QEMU,
       .applications = 0U
   };
   UmiSetupBootPlan plan = {0};
   const UmiStatus status = UmiSetupPlanBoot(&request, &plan);
   ~~~

3. In the source, follow validation, route selection and the final assignment to the caller's plan. Keep a line for the returned status and another for the readiness in the plan.
4. Trace a copy of the request with UMI_SETUP_BOOT_VIRTUALBOX. Then make an invalid copy that requests the Foundation edition with the Kernel product. What may the caller display in each case?

| Request | Status | Expected plan |
|---|---|---|
| Kernel RISC-V64 QEMU | UMI_STATUS_OK | UMI_SETUP_BOOT_WORKFLOW_DOCUMENTED, with RISC-V QEMU virt in the machine description |
| Kernel RISC-V64 VirtualBox | UMI_STATUS_OK | UMI_SETUP_BOOT_NOT_AVAILABLE, with no artifact and a reason |
| Kernel paired with the Foundation edition | UMI_STATUS_INVALID_ARGUMENT | The existing caller-owned output stays unchanged |

An OK status allows you to display the review. The readiness explains what the reviewed choices can lead to. The planner receives no artifact filename or device handle, so it cannot evaluate actual media bytes.

**Try it yourself.** Replace the product with Umicom OS and use the Foundation edition, x86-64 and USB. The plan reports UMI_SETUP_BOOT_QUALIFICATION_REQUIRED. Copy its physical-transfer limitation into your notes. Mark the actual device as unselected.

[Workshop](index.md) · [Next · Present the shared plan](02-present-the-shared-plan.md)
