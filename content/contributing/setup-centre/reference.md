<!--
Umicom Bits2Banking
File: content/contributing/setup-centre/reference.md

PURPOSE:
Provide a wiki-style entry point to Setup Centre source, tests and work vocabulary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Setup Centre contributor reference

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use this page when you need to find the code that owns a decision or explain a test result. Start with the [contributor workshop](index.md) if you want a sequence of exercises.

| Question | Source to read |
|---|---|
| Which product, board, edition, source, output and app choices can a request represent? | [Boot plan header](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/setup_centre/boot_plan.h) |
| Which combinations are documented, diagnostic, await qualification or are unavailable? | [Route table and validation](https://github.com/umicom-foundation/umicom-framework/blob/main/src/setup_centre/boot_plan.c) |
| Which console spellings map to those values? | [Boot plan command](https://github.com/umicom-foundation/umicom-framework/blob/main/src/setup_centre/boot_plan_cli.c) |
| Where are Win32 messages, workers and controls handled? | [Win32 Setup Centre adapter](https://github.com/umicom-foundation/umicom-framework/blob/main/adapters/win32/setup_centre.c) |
| Which code controls media inspection, review, confirmation and readback? | [Media CLI](https://github.com/umicom-foundation/umicom-framework/blob/main/src/boot_media/cli.c) · [Media transfer contract](https://github.com/umicom-foundation/umicom-framework/blob/main/src/boot_media/transfer.c) |
| What proves that a planner request is handled correctly? | [Planner test](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/setup_centre/test_boot_plan.c) · [Native verification lesson](04-verify-a-native-review.md) |

**Board profile** names the machine and firmware contract expected by a guest. **Artifact** means the exact input or output bytes, such as a RISC-V ELF, Windows EFI application, optical ISO or raw disk image. **Readiness** is the planner's answer about available next steps. **Qualification** records checks completed for the exact build, artifact, environment and intended use.

A plan can be documented before the necessary toolchain or media is selected. A file-inspection result can tell you what a formatted image contains. A virtual guest result records a run on the named emulator and firmware. Physical writing and install, restart and recovery observations each need their own evidence.

For a contribution, keep reusable rules in Framework. A product shell or adapter should translate controls and display the shared result. If an edit supersedes existing source, keep the prior implementation and explain the replacement using the project's preservation convention. If the issue concerns device or firmware support, link the exact source and selected profile. Keep sensitive or private evidence out of educational material.

[User guide](../../umicom/setup-centre-boot-planning.md) · [Setup Centre workshop](index.md) · [General contribution guide](../index.md)
