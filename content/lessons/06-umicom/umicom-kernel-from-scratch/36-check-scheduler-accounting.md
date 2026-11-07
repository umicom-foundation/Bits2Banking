<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/36-check-scheduler-accounting.md

PURPOSE:
Explain the lesson: Check scheduler accounting.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check scheduler accounting

## Prepare
Read BtbRoundRobinSnapshotRead. The snapshot reports ready, waiting, running and live counts.

An invariant is a relationship that must remain true after every supported operation. Here live must equal ready plus waiting plus running.

## Trace the counts
Admit A and B: ready two, waiting zero, running zero, live two. Dispatch A: ready one, running one. Make A wait: ready one, waiting one, running zero.

The total live count remains two.

## Lab
Continue by dispatching and exiting B, then cancelling A's matching wait. Calculate the counts after each step.

Expected final state: all counts zero. The stopped slots still exist as storage, but they are not live tasks.

## Exercise and explanation
Why derive live by inspecting task states rather than just adding counters? Comparing independent representations can expose a missed counter update. Copying the same arithmetic into both sides would provide less evidence.

## Troubleshoot
If snapshot reading reports BAD_STATE, preserve the preceding operation sequence. Inspect where the task state and count should have changed together.

The snapshot's final assignment occurs after its checks. A failed snapshot must not be presented as a fresh successful observation. This model assumes its internal arrays are used through the API and is not a complete validator for arbitrary corrupted memory.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/round-robin-scheduler/round_robin.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](35-cancel-a-wait-with-an-explicit-result.md) · [Next lesson](37-read-the-native-scheduler-boundary.md)

