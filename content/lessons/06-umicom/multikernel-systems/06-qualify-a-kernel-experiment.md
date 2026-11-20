<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/06-qualify-a-kernel-experiment.md

PURPOSE:
Design a staged experiment that measures when a separate kernel earns its cost.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Qualify a kernel experiment

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

An **ISA** is the instruction set a processor can execute. QEMU can translate instructions and emulate a guest built for a different ISA. A compatible hardware-accelerated VM also needs a guest boot path, trap handlers and virtual devices. A **hart** is a hardware thread in RISC-V. The inspected Umicom Kernel bootstrap parks secondary harts, so a one-hart boot only provides evidence about that execution path.

## Choose evidence for each step

| Experiment | Evidence to retain | Claim you can make |
| --- | --- | --- |
| C23 host lab | Expected bytes, accepted and refused requests, compiler and test result | The sample request parser followed its contract on that host. |
| One emulated guest | Image identity, boot observation, current probe, bounded request and restart trace | The selected guest completed a functional service exercise. |
| Two-hart emulator | Separate stacks, trap and allocator ownership, boot handshakes and message traces | The two initialisations and specified handoff ran in that emulator. |
| Matched hardware workload | Host and guest identities, placement, latency, completed work, output quality and recovery | Performance and failure scope on the measured configuration. |

Read the RISC-V bootstrap and find the branch that parks a nonzero hart. Sketch the state that must be owned before a second hart can enter. Include its stack, trap state, timer, memory region and communication initialization. Identify which owner writes to the console. [Umicom Kernel bootstrap](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S) · [QEMU system emulation](https://www.qemu.org/docs/master/system/introduction.html)

## Write a fair comparison plan

1. Define one job and an outcome. Use a fixed integer transform first. A later inference trial can fix model identity, input size, numeric precision and quality criteria.
2. Record ordinary Linux execution and a Framework-managed worker as baselines. Compare a separate-kernel profile only after specifying the unmet requirement and how the profile enforces it.
3. Keep hardware and major software settings consistent where practical. Record unavoidable differences. Measure time after warm-up, successful work, refusals, recovery time and resources retained after a fault.
4. Compare one hypothetical report with another. A report with lower average latency but fewer completed requests needs its rejection and timeout counts beside the latency. Keep emulator timings with functional observations and use hardware measurements for performance decisions.

As a final check, write one sentence each for Framework, OS and Kernel. Name who admits the work, who composes the supported profile and recovery route, and who enforces native resource access. Give each claim an observable test.
