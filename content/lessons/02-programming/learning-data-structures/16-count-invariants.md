<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/16-count-invariants.md

PURPOSE:
Explain the lesson: Use conservation rules to check a pipeline.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use conservation rules to check a pipeline

## Prepare
Read BtbDispatchInvariants. An invariant is a relationship that should remain true after every allowed public operation. It helps detect states that no valid operation sequence should produce.

The dispatcher records accepted, succeeded, cancelled and delivered counts. It also has occupied work records and terminal notices.

## Read two equations
```text
accepted = delivered + occupied records
succeeded + cancelled = delivered + terminal records
```
The first accounts for every accepted request. It is either delivered or still occupies storage. The second accounts for every terminal result. It is either delivered or awaiting delivery.

## Work through an example
Accept three requests. Execute one, cancel one, leave the third queued. Before receiving:
- accepted = 3;
- succeeded = 1;
- cancelled = 1;
- delivered = 0;
- occupied = 3;
- terminal = 2.

Both equations hold. Receive one result: delivered becomes one, occupied two, terminal one. The equations still hold.

## Exercise
Continue by executing and receiving the remaining requests. Check both equations after each operation. Use separate columns rather than calculating only the final totals.

## Beyond counters
Equal totals are necessary but not sufficient. The invariant checker also verifies notice-to-record mappings, generations, slot indices and duplicate notices. Two incorrect notices could preserve the same total.

## Troubleshoot
The checker reports inconsistent state; it does not silently repair it. When it fails, find the first operation after which the invariant changed. A bounded operation trace is more informative than overwriting counters until the equation looks correct. In a production service, record enough context to reproduce the transition without exposing sensitive request contents.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/work-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-quiesce-then-drain.md) · [Next lesson](17-digests-and-meaning.md)

