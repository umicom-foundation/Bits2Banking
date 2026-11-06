# History, replay and recovery

[Course contents](index.md) · [Previous: Validate before changing state](02-validate-before-changing-state.md)

## Memory is not durable storage

The previous function changes a value in memory. A process crash loses that value unless a durable record survives. Replay reconstructs state by reading accepted events in order and applying the same rules again.

```text
validated proposal
       |
       v
durable accepted event -> acknowledged result
       |
       v
replay events -> rebuilt state -> compare checkpoint
```

This diagram expresses a requirement, not a complete disk algorithm. Appending bytes, flushing an application buffer, asking the operating system to sync, and surviving power loss are different guarantees. A practical implementation must state which it provides on each platform.

## Design an interruption exercise

Imagine a record containing length, sequence, payload and digest. Stop the writer halfway through the payload. On restart, the reader must distinguish a complete valid record from an incomplete tail. It must not silently interpret partial bytes as another valid event.

1. Define a maximum record length before allocating memory.
2. Validate the length and sequence before applying the payload.
3. Check the digest over the documented bytes.
4. Apply each accepted event once, using a stable event identifier to detect duplicates.
5. Report damaged or incomplete data explicitly and preserve it for recovery analysis.

For product integration, use Framework's persistence and transactional facilities after inspecting their contracts. Do not create a second unreviewed ledger writer inside every application. A teaching file format helps explain requirements; it is not a replacement for proven storage behaviour.

## Exercise

A client times out after submitting event E. It resends E with the same identifier. What should the service return if E was already accepted? What if the same identifier carries different content?

## Explained answer

Return the recorded outcome for the identical accepted event without applying it again. A reused identifier with different content is a conflict to reject and investigate. Timeout means the client does not know the outcome; it does not prove that the server did nothing.

## Continue the implementation

The next modules will add a bounded decoder and integrate Framework hashing, followed by executable crash-recovery exercises. Network consensus and signatures remain separate milestones. The available opening module establishes the byte and state contracts those later parts will depend on.

## Continue learning

[Course contents](index.md) · [Previous: Validate before changing state](02-validate-before-changing-state.md)

[Browser edition](../../../courses/building-blockchain-from-scratch/lessons/03-history-replay-and-recovery.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.
