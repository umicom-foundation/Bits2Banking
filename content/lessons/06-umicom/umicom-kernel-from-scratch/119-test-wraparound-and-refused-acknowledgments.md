<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/119-test-wraparound-and-refused-acknowledgments.md

PURPOSE:
Test wraparound and refused acknowledgments

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Test wraparound and refused acknowledgments

[Course contents](index.md)
TCP sequence numbers use 32-bit unsigned arithmetic. After 4,294,967,295, the next value is zero. Ordinary numeric comparison therefore cannot establish stream order near wraparound. The existing sequence helpers use modular distance with a span restricted to less than half the sequence space.


## 1. Draw a wrapped interval

~~~text
oldest = 4,294,967,294
reserve 4 positions:
4,294,967,294 -> 4,294,967,295 -> 0 -> 1
next = 2
~~~

An acknowledgment of zero releases two positions in this example. Zero is numerically smaller than oldest, yet it is later in this short stream interval. The tracker delegates this relationship to the same sequence arithmetic used by its other operations.


## 2. Refuse ambiguous or invalid state

Limiting the outstanding span avoids the ambiguous half-space case. Initialization rejects zero capacity and capacities above the supported maximum. Operations inspect state bounds before using them. This is defensive checking of the host contract; it does not turn a mutable C structure into tamper-proof storage.


## 3. Preserve outputs on refusal

A duplicate acknowledgment releases no new positions and is rejected by the new-acknowledgment operation. An old acknowledgment or one beyond next is also refused. The released output remains unchanged on these paths. The caller must check the decision before using that output; a previous value is not a new release count.

~~~text
ack == oldest       -> duplicate, no new release
ack behind oldest   -> old, no release
ack beyond next     -> future, no release
oldest < ack <= next in modular interval -> new release
~~~


## 4. Use an independent model

The hosted regression tracks a small literal outstanding count alongside the production sequence counters. It reserves and acknowledges combinations within small capacities and compares the observed state. This is stronger than computing the expected result with the same helper under test, which could repeat the same mistake on both sides.

The refusal cases also snapshot the tracker and output sentinel values. A sentinel is a recognizable initial value used to detect an unexpected write. Comparing those values after rejected input checks the preservation contract. The wraparound cases use known boundary numbers rather than random values alone.


## 5. Know what remains to build

A complete TCP sender still needs connection states, retransmission storage, timers, congestion control, peer-window handling, packet assembly and device integration. Passing sequence tests establishes a reusable arithmetic component. It does not establish any of those higher-level behaviors.

Exercise: why should the available count not increase after a duplicate acknowledgment? Because no additional sequence position was newly confirmed. Increasing it would let the sender reserve more outstanding data than its capacity permits.


[Previous lesson](118-account-for-outbound-tcp-sequences.md)

[Next lesson](120-qualify-shared-vm-slices-in-a-guest.md)
