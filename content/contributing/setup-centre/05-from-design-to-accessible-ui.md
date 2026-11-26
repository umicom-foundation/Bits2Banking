<!--
Umicom Bits2Banking
File: content/contributing/setup-centre/05-from-design-to-accessible-ui.md

PURPOSE:
Connect owner-approved design, shared branding and accessible native review evidence.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Carry an approved design into an accessible UI

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use the approved Setup Centre walkthrough to agree on what a contributor can see and do. Preserve the existing toolkit, flows and assets. The smallest reviewable change ties one action from that walkthrough to an existing Framework result.

1. Read the approved steps in order. Copy the decision fields into a checklist for product and profile, input source, edition and contents, destination and review. Write one supporting source or test beside each step. Keep requested product ideas visibly separate from available choices.
2. Inspect the [native launcher resources](https://github.com/umicom-foundation/umicom-framework/tree/main/examples/setup_centre/resources) and [Framework brand masters](https://github.com/umicom-foundation/umicom-framework/tree/main/resources/brand). Use the current Umicom icon and the supplied logo variants where the design calls for them. Preserve proportions and use the existing Segoe UI text and Cascadia Code or Consolas code roles. Record which resource the build actually embeds before judging its appearance.
3. Create a two-case test card. In the first case move through a valid Kernel RISC-V64 QEMU review using Tab and arrow keys. In the second case preview a Kernel RISC-V64 VirtualBox request. The status and reason should be readable with the same keyboard route. Text carries the meaning in both cases, including high contrast.
4. In an authorized native review, record the build and environment. Use the documented GUI self-check for the exact revision and separately observe keyboard order, readable status, resize or DPI behaviour, and the icon. A self-check may verify controls and route wiring without proving rendering or keyboard accessibility. Preserve unexecuted checks as pending.

| Case | Expected review | Expected action |
|---|---|---|
| Kernel RISC-V64, QEMU | Documented QEMU route and correct machine label | The preview shows its next workflow. It starts no guest by itself. |
| Kernel RISC-V64, VirtualBox | Unavailable, with the provider choice and limitation readable | The preview recommends no runnable VirtualBox route. The original selections remain visible for correction. |

**Contributor handoff.** Record the reviewed revision, change, two expected results, observations actually collected, and any evidence still needed. Preserve the host installer and previous behaviour. Use the [contributor reference](reference.md) to find the correct code owner and report a focused improvement.

[Previous](04-verify-a-native-review.md) · [Workshop](index.md) · [Contributor reference](reference.md)
