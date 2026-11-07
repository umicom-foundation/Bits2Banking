<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/10-compose-a-work-pipeline.md

PURPOSE:
Explain the lesson: Compose a work pipeline from existing queues.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compose a work pipeline from existing queues

## Prepare
Open labs/native/work-dispatch in Bits2Banking. Its README gives PowerShell commands for an independent C23 build using CMake and Ninja. The neighbouring work-handoff and completion-queue folders must be present.

A pipeline passes work through stages. This example has admission, execution and delivery. Execution calculates a diagnostic digest of copied request bytes; it does not perform a bank operation or send a network request.

## Read the dependencies
CMake builds the existing handoff and completion implementations into a foundation library. The dispatcher links that library instead of reimplementing its queues.

The work queue holds eight items. The completion queue holds four notices. A record array connects each work token with a request identifier and connection identifier.

## Trace one request
1. Initialize a caller-owned BtbDispatch.
2. Submit connection 7 and the three bytes ABC.
3. Step once to calculate the digest and publish a completion notice.
4. Receive the receipt into caller-owned storage.
5. Check that the dispatcher has drained.

Submission copies the bytes. The receipt contains values rather than a pointer back into a released slot.

## Exercise
Draw three boxes labelled queued work, terminal notice and delivered receipt. Write the function responsible for crossing each boundary. Then trace the example without assuming that “executed” means “delivered”.

Expected: Step creates a terminal notice, while Receive consumes it and releases the work slot.

## Review
Composition reduces duplicated queue logic, but introduces its own responsibility: coordinating two capacities and preserving the mapping between them. Inspect BtbDispatchInvariants for the relationships that the adapter must maintain. A shared production implementation belongs in Framework; this isolated lab explains the contract before that larger integration.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/work-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-design-a-container-caller-contract.md) · [Next lesson](11-completion-backpressure.md)

