<!--
Umicom Bits2Banking
File: content/umicom/setup-centre-boot-planning.md

PURPOSE:
Guide users through read-only Setup Centre boot-media choices and their limits.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Plan a Kernel or OS boot in Setup Centre

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Start by choosing what you want to try. **Umicom Kernel** is the independent native kernel. **Umicom OS Foundation** is the current Linux-based development guest. Their files are different. An OS Foundation guest does not install itself on a computer.

1. **Choose the product and target.** Keep both names in your notes. RISC-V64 is available for the independent Kernel in QEMU. The x86-64 Kernel route produces an EFI diagnostic ISO. Linux Foundation has x86-64 and RISC-V64 QEMU workflows.
2. **Choose the source.** Select a local build if you have the source and its prerequisites. Select prebuilt if you already have reviewed files. Compare their digest against an independently recorded trusted value before using them.
3. **Choose the edition and contents.** Use Foundation for the current Umicom OS guest and standalone for Umicom Kernel. A published bundle has the contents listed in its manifest. Requested editions or apps that lack qualified guest packages remain unavailable.
4. **Choose where to use the result.** QEMU can directly load the matching kernel or Foundation bundle. VirtualBox needs a compatible x86-64 optical ISO for the Foundation route. Check the exact ISO's catalogue before selecting BIOS or UEFI. A raw GPT image represents a virtual disk, with a separate workflow from optical media.
5. **Read both readiness and limits.** A documented workflow tells you what to do next. A diagnostic result identifies a tool for testing firmware. Qualification required means you still need evidence before proceeding with the requested use. Unavailable means the selected combination has no current workflow.

### Use the Windows wizard

1. Open **Umicom Setup Centre**, then choose **Boot and install**.
2. Choose **Product**, **Target machine**, **Source and contents**, and **Output**. Use **Next** after each choice.
3. On **Review**, read the readiness, artifact and workflow. Use **Back** or an earlier step to correct a choice.
4. If you chose a Foundation QEMU route, **Open QEMU review** takes you to the existing VM input form. Select the exact Linux kernel and initial filesystem and review those files there.
5. If you chose a local x86-64 Foundation ISO, **Open media staging** takes you to the verified-input form. It prepares a new source directory for the Linux ISO producer.

A standalone Kernel QEMU plan shows its ELF workflow. Use the separate Kernel launch guide for that artifact. USB review explains the conditions for a qualified transfer.

### Try two read-only choices

In PowerShell select the absolute path to your current Setup Centre console. These two commands list choices and limits. They require no input files and will not start QEMU or write an image.

~~~powershell
$Setup = Read-Host 'Absolute path to umicom-setup.exe'
& $Setup boot-plan --product kernel --arch riscv64 --source prebuilt --output qemu
& $Setup boot-plan --product os --arch x86_64 --edition foundation --source prebuilt --output usb
~~~

Expect workflow-documented for the Kernel QEMU plan, and qualification-required for the OS USB request. The USB review explains the requirements for the source, device and confirmation. It has neither chosen nor touched a device.

In a Windows Setup Centre build with boot review controls, select the same product, architecture, source, edition and output, then read the shared result. If those controls are missing in your build, use the native console above. If the console does not recognize boot-plan, check the installed release or follow the [contributor build lesson](../contributing/setup-centre/04-verify-a-native-review.md).

### Follow the matching guide

| Your goal | Continue here |
|---|---|
| Start independent Kernel system or recovery | [Kernel RISC-V64 QEMU workshop](../simple-steps/boot-media/kernel-riscv-console.md) |
| Build a Kernel x86-64 diagnostic | [Prepare the diagnostic EFI](../simple-steps/boot-media/kernel-uefi-preflight.md) · [Produce a diagnostic ISO](../simple-steps/boot-media/kernel-diagnostic-iso.md) |
| Prepare an OS x86-64 Foundation bundle | [Build and verify a Foundation bundle](../simple-steps/boot-media/os-foundation-bundle.md) · [Boot it directly](../simple-steps/boot-media/os-direct-boot.md) |
| Inspect or start a compatible Foundation optical ISO | [Produce the ISO](../simple-steps/boot-media/os-optical-iso.md) · [Try virtual optical boot](../simple-steps/boot-media/os-optical-vm.md) |
| Make a file-backed OS UEFI image | [Prepare the raw disk file](../simple-steps/boot-media/os-uefi-disk-image.md) |
| Learn image writing with an ordinary file | [Rehearse review, transfer and readback](../simple-steps/boot-media/inspect-and-copy.md) |
| Determine if a physical USB or install is appropriate | [Physical readiness guide](../simple-steps/boot-media/physical-readiness.md) |

A file hash tells you which bytes you have. Keep it with the intended machine, firmware and medium. For hardware installation, look for a release-qualified installer, exact target support and a rehearsed recovery route. The current Foundation preview remains a diskless guest. The hosted application installer follows the [separate host Setup Centre guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/install-and-try-umicom.html).

[Boot media workshop](../simple-steps/boot-media/index.md) · [Contributor workshop](../contributing/setup-centre/index.md)
