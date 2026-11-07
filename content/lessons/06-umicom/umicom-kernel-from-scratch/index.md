# Umicom Kernel from Scratch

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## First boot and bounded input

Read the boot guide, distinguish host models from a native kernel, and handle input without crossing its bounds.

1. [Understand your first boot](understand-your-first-boot.md)
1. [Read a native kernel without booting it](01-native-kernel-and-host-models.md)
1. [A byte span is not a string](02-bounded-input.md)
1. [Reject overflow before multiplying](03-overflow-and-ownership.md)
1. [Never execute a damaged prefix](04-damaged-console-lines.md)

## Firmware, services and storage

Follow firmware reservations, system calls, file operations and ownership.

1. [Read firmware bytes without following their addresses](05-firmware-metadata.md)
1. [Keep firmware-owned pages out of the allocator](06-reserved-pages.md)
1. [How a program asks the Kernel for a service](07-native-system-calls.md)
1. [Create a file and run a program at the Kernel console](08-files-at-the-console.md)
1. [Check what a native program needs](09-program-requirements.md)
1. [Understand how the Kernel counts disk space](10-understanding-disk-space.md)
1. [Test storage boundaries without changing a disk](11-testing-storage-boundaries.md)
1. [Keep results separate from the memory they describe](12-ownership-and-cleanup.md)

## Memory boundaries and diagnostics

Inspect bounded file ranges, discover native contracts and read timers without allocating diagnostic storage.

1. [Read a file one bounded part at a time](13-read-file-ranges.md)
1. [Inspect file bytes in hexadecimal](14-inspect-binary-files.md)
1. [Test the boundary between a program and the Kernel](15-test-user-memory-boundaries.md)
1. [Discover the contract a native program needs](16-discover-the-native-program-contract.md)
1. [Publish a kernel contract only after validation](17-publish-a-contract-only-after-validation.md)
1. [Read a memory-mapped timer](18-read-a-memory-mapped-timer.md)
1. [Distinguish a deadline from a delay](19-distinguish-a-deadline-from-a-delay.md)
1. [Bound emergency diagnostics](20-bound-emergency-diagnostics.md)
1. [Format a register without allocation](21-format-a-register-without-allocation.md)

## Project: a physical frame inventory

Reserve, allocate and release modeled frames with explicit exhaustion and overflow checks.

1. [Represent physical frames as an inventory](22-physical-frames-as-an-inventory.md)
1. [Validate a frame-pool base before changing state](23-alignment-and-address-validation.md)
1. [Reserve a whole frame range or leave it unchanged](24-reserve-a-range-before-allocation.md)
1. [Follow first-fit allocation and reuse](25-first-fit-and-reuse.md)
1. [Reject invalid and repeated frame releases](26-release-and-double-release.md)
1. [Test exhaustion without losing the caller's output](27-exhaustion-and-output-preservation.md)
1. [Compare unchanged storage with a reliable snapshot](28-snapshots-and-padding.md)
1. [Keep the modeled address range inside its integer type](29-address-overflow-and-pool-boundaries.md)

## Project: task scheduling

Trace ready, running and waiting states, cancellation and task identity.

1. [Model ready, running and waiting tasks](30-model-ready-running-and-waiting.md)
1. [Dispatch in ready-queue order](31-dispatch-in-ready-queue-order.md)
1. [Require an idle processor before dispatch](32-require-an-idle-processor-before-dispatch.md)
1. [Match a wake event to its wait](33-match-a-wakeup-to-its-wait.md)
1. [Reuse a task slot without reusing its identity](34-exit-and-reuse-task-slots.md)
1. [Cancel a waiting task explicitly](35-cancel-a-wait-with-an-explicit-result.md)
1. [Check scheduler accounting](36-check-scheduler-accounting.md)
1. [Read the native scheduler boundary](37-read-the-native-scheduler-boundary.md)

## Project: storage writeback

Separate staged bytes from stable bytes, budget flushes and validate a complete imported image.

1. [Distinguish staged and stable sectors](38-distinguish-staged-and-stable-sectors.md)
1. [Explain a dirty marker](39-explain-a-dirty-marker.md)
1. [Flush with a limited budget](40-flush-with-a-limited-budget.md)
1. [Retry only remaining storage work](41-retry-only-remaining-storage-work.md)
1. [Simulate loss of unflushed data](42-simulate-loss-of-unflushed-data.md)
1. [Export the stable view](43-export-the-stable-view.md)
1. [Import into a candidate first](44-import-into-a-candidate-first.md)
1. [Reject extra storage-image bytes](45-reject-extra-storage-image-bytes.md)

## Project: an asynchronous device queue

Prepare requests, publish them, check completion ownership and wait for reset acknowledgement.

1. [Copy a request before publication](46-copy-a-request-before-publication.md)
1. [Publish only a prepared request](47-publish-only-a-prepared-request.md)
1. [Check owner before consuming a result](48-check-owner-before-consuming-a-result.md)
1. [Record cancellation without freeing memory](49-record-cancellation-without-freeing-memory.md)
1. [Respect the model's completion order](50-respect-the-models-completion-order.md)
1. [Validate completed byte counts](51-validate-completed-byte-counts.md)
1. [Wait for reset acknowledgement](52-wait-for-reset-acknowledgement.md)
1. [Retire a slot before generation wrap](53-retire-a-slot-before-generation-wrap.md)

## Project: a system-call boundary

Check rights, revisions, text and capacity before publishing an event and its reply.

1. [Describe a service request](54-describe-a-service-request.md)
1. [Read a service without changing it](55-read-a-service-without-changing-it.md)
1. [Check a publish right](56-check-a-publish-right.md)
1. [Refuse a stale revision](57-refuse-a-stale-revision.md)
1. [Bound and validate service text](58-bound-and-validate-service-text.md)
1. [Publish an event and its reply](59-publish-event-and-reply-together.md)
1. [Report full capacity without overwriting](60-report-full-capacity-without-overwriting.md)
1. [Design a kernel-boundary test table](61-design-a-kernel-boundary-test-table.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

# Umicom Kernel from Scratch

A kernel manages access to a computer's memory, devices and processor. This course follows small pieces of Umicom Kernel so that each new idea has a source file to read and a practical question to answer. Begin with the boot overview, then learn how the Kernel checks input, manages memory and offers services to programs.

## Get ready

1. Read [Introduction to Computers](../../01-computers/index.md) if files, programs and operating systems are unfamiliar.
2. Follow the [terminal lab](../../learning-c/terminal-lab.md) to install a C compiler, CMake and Ninja and practise creating, compiling and running a small program. Keep practice work in a folder you choose.
3. Keep an Umicom Kernel checkout available beside Bits2Banking. The examples use `C:\umicom\umicom-kernel` on Windows and `$HOME/umicom/umicom-kernel` on Linux. Substitute your own checkout path when it differs.
4. Read each lesson's setup recap before running its commands. Host tests run on your current operating system; boot exercises need the separately prepared Kernel image and emulator described in the boot lesson.

You can read the lessons without running commands. Building a host test does not install an operating system or qualify the Kernel for physical hardware. Work through [Learning C](../../learning-c/index.md) alongside this course when a C concept is new.

## Learning sequence

The first group explains what is being built. The next group studies how untrusted bytes become checked input. Storage and program contracts follow once those foundations are familiar.

1. [Understand your first boot](understand-your-first-boot.md): identify the emulator, firmware and Kernel in a boot journey.
2. [Read a native kernel without booting it](01-native-kernel-and-host-models.md): distinguish source inspection, host checks and native execution.
3. [A byte span is not a string](02-bounded-input.md): describe input using an address and a length.
4. [Reject overflow before multiplying](03-overflow-and-ownership.md): check the size of an operation before accessing memory.
5. [Never execute a damaged prefix](04-damaged-console-lines.md): keep incomplete console input from becoming a command.
6. [Read firmware bytes without following their addresses](05-firmware-metadata.md): interpret metadata as bounded input.
7. [Keep firmware-owned pages out of the allocator](06-reserved-pages.md): preserve memory that another component owns.
8. [How a program asks the Kernel for a service](07-native-system-calls.md): follow a system call across the program boundary.
9. [Create a file and run a program at the Kernel console](08-files-at-the-console.md): practise a prepared console workflow.
10. [Check what a native program needs](09-program-requirements.md): compare program requirements with Kernel capabilities.
11. [Understand how the Kernel counts disk space](10-understanding-disk-space.md): connect storage metadata to a reported result.
12. [Test storage boundaries without changing a disk](11-testing-storage-boundaries.md): use controlled input to study refusal cases.
13. [Keep results separate from the memory they describe](12-ownership-and-cleanup.md): follow ownership and cleanup.
14. [Read a file one bounded part at a time](13-read-file-ranges.md): choose and check a range of bytes.
15. [Inspect file bytes in hexadecimal](14-inspect-binary-files.md): make binary data readable during investigation.

## Practical labs: read, change and check

Follow these after the introductory lessons. Each lab includes its own setup recap and explains the expected result.

- [Test the boundary between a program and the Kernel](15-test-user-memory-boundaries.md)
- [Discover the contract a native program needs](16-discover-the-native-program-contract.md)

For each lab, write down the input, expected decision and observed result. If a command fails, keep its first diagnostic and stop before the next stage. A failing test is evidence to investigate; changing its expected result requires an explanation of the intended behaviour.

## Continue learning

- [Learning RISC-V Assembly](../../03-native-code/learning-riscv-assembly/index.md) connects C calls to registers and instructions.
- [Framework functionality and lab map](../../umicom-development/functionality-lab-map.md) connects reusable user-space services to small applications.
- [Umicom lessons](../index.md) provides related Framework, OS and application material.

The course is growing. Hardware installation, device support and complete operating-system administration require their own implementation and qualification; these lessons describe the specific source and exercises they cover.

## Continue with a practical source study

A native program asks a kernel what services and data sizes it supports. Several queries can succeed before a later query fails. This lab follows the code that keeps a partly discovered contract from becoming a caller's accepted result.

- [Publish a kernel contract only after validation](17-publish-a-contract-only-after-validation.md)


- [Read a memory-mapped timer](18-read-a-memory-mapped-timer.md)

- [Distinguish a deadline from a delay](19-distinguish-a-deadline-from-a-delay.md)

- [Bound emergency diagnostics](20-bound-emergency-diagnostics.md)

- [Format a register without allocation](21-format-a-register-without-allocation.md)

- [Represent physical frames as an inventory](22-physical-frames-as-an-inventory.md)

- [Validate a frame-pool base before changing state](23-alignment-and-address-validation.md)

- [Reserve a whole frame range or leave it unchanged](24-reserve-a-range-before-allocation.md)

- [Follow first-fit allocation and reuse](25-first-fit-and-reuse.md)

- [Reject invalid and repeated frame releases](26-release-and-double-release.md)

- [Test exhaustion without losing the caller's output](27-exhaustion-and-output-preservation.md)

- [Compare unchanged storage with a reliable snapshot](28-snapshots-and-padding.md)

- [Keep the modeled address range inside its integer type](29-address-overflow-and-pool-boundaries.md)

- [Model ready, running and waiting tasks](30-model-ready-running-and-waiting.md)

- [Dispatch in ready-queue order](31-dispatch-in-ready-queue-order.md)

- [Require an idle processor before dispatch](32-require-an-idle-processor-before-dispatch.md)

- [Match a wake event to its wait](33-match-a-wakeup-to-its-wait.md)

- [Reuse a task slot without reusing its identity](34-exit-and-reuse-task-slots.md)

- [Cancel a waiting task explicitly](35-cancel-a-wait-with-an-explicit-result.md)

- [Check scheduler accounting](36-check-scheduler-accounting.md)

- [Read the native scheduler boundary](37-read-the-native-scheduler-boundary.md)

- [Distinguish staged and stable sectors](38-distinguish-staged-and-stable-sectors.md)

- [Explain a dirty marker](39-explain-a-dirty-marker.md)

- [Flush with a limited budget](40-flush-with-a-limited-budget.md)

- [Retry only remaining storage work](41-retry-only-remaining-storage-work.md)

- [Simulate loss of unflushed data](42-simulate-loss-of-unflushed-data.md)

- [Export the stable view](43-export-the-stable-view.md)

- [Import into a candidate first](44-import-into-a-candidate-first.md)

- [Reject extra storage-image bytes](45-reject-extra-storage-image-bytes.md)

- [Copy a request before publication](46-copy-a-request-before-publication.md)

- [Publish only a prepared request](47-publish-only-a-prepared-request.md)

- [Check owner before consuming a result](48-check-owner-before-consuming-a-result.md)

- [Record cancellation without freeing memory](49-record-cancellation-without-freeing-memory.md)

- [Respect the model's completion order](50-respect-the-models-completion-order.md)

- [Validate completed byte counts](51-validate-completed-byte-counts.md)

- [Wait for reset acknowledgement](52-wait-for-reset-acknowledgement.md)

- [Retire a slot before generation wrap](53-retire-a-slot-before-generation-wrap.md)

- [Describe a service request](54-describe-a-service-request.md)

- [Read a service without changing it](55-read-a-service-without-changing-it.md)

- [Check a publish right](56-check-a-publish-right.md)

- [Refuse a stale revision](57-refuse-a-stale-revision.md)

- [Bound and validate service text](58-bound-and-validate-service-text.md)

- [Publish an event and its reply](59-publish-event-and-reply-together.md)

- [Report full capacity without overwriting](60-report-full-capacity-without-overwriting.md)

- [Design a kernel-boundary test table](61-design-a-kernel-boundary-test-table.md)

</details>
