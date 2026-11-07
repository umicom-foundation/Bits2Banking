<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/12-cancellation-is-a-result.md

PURPOSE:
Explain the lesson: Treat cancellation as a terminal result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Treat cancellation as a terminal result

## Prepare
Read BtbDispatchCancel and the cancel/capacity tests in the work-dispatch lab. Cancellation means a request will not perform its intended work. The caller still needs a clear result and resource release.

## Follow the conditions
Cancel accepts a valid identity for QUEUED work. If the identity is stale, it refuses. If the item has already reached a terminal state, it returns FINAL. If the completion queue is full, it returns BACKPRESSURE before changing the item.

A successful cancellation transitions the work item and enqueues a CANCELLED notice with zero bytes transferred. Receive later delivers the receipt and releases the slot.

## Why a notice matters
Silently removing a queued item would leave its submitter waiting indefinitely unless another contract explained the disappearance. A terminal notice gives the caller an explicit outcome.

Cancellation also consumes completion capacity. Treating it as “free” could overfill the same queue used for successful results.

## Lab trace
1. Submit two requests and save both identities.
2. Cancel the second while it is queued.
3. Step the first.
4. Receive both terminal results.
5. Match each result to its saved identity.

Expected: one cancellation and one success. Notice order follows when terminal results were queued; do not assume cancellation notices retain original submission order.

## Review the limit
Step performs one operation synchronously. There is no active asynchronous phase that another thread can interrupt. Supporting cancellation of a running worker would require acknowledgement and lifetime rules beyond this example.

If a cancellation refuses because of backpressure, drain a receipt and retry according to the caller's policy. Do not mark the UI request cancelled until the service actually accepts that transition.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/work-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-completion-backpressure.md) · [Next lesson](13-own-a-receipt-after-release.md)

