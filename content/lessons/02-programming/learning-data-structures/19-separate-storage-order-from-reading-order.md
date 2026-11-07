<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/19-separate-storage-order-from-reading-order.md

PURPOSE:
Explain the lesson: Read events in chronological insertion order.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read events in chronological insertion order

## Prepare
Open BtbDiagnosticRead in ring.c. Storage order means the physical arrangement in the array. Reading order means the sequence presented to a client.

After wrapping, the oldest retained event may be in the middle of the array.

## Work an example
Insert ten events into an eight-slot ring. Events one and two are overwritten. The retained sequence is three through ten.

The read loop visits (head + i) modulo capacity, where i starts at zero. It copies records into a separate snapshot in the intended order.

## Lab
Draw the physical positions after each insertion, then create a second row containing the snapshot order. Compare the two rows.

Expected: the snapshot starts with sequence three even though physical array position zero now holds a later event.

## Exercise and explanation
Would copying the entire records array directly produce the correct order? Only before wrapping, or in special positions. General readers must respect head and count.

## Troubleshoot
A display that appears to jump backwards may be showing physical order. Check the conversion to a snapshot before changing the event timestamps.

The read function copies values. A caller can inspect that snapshot without retaining pointers into the live ring. In this teaching model all operations still run on one thread; copying does not make concurrent access automatically safe.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/diagnostic-ring/ring.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](18-store-recent-events-in-a-ring.md) · [Next lesson](20-account-for-overwritten-observations.md)

