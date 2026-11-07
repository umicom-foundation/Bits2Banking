<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/23-preserve-address-stable-owners.md

PURPOSE:
Explain the lesson: Preserve an address-stable owner.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve an address-stable owner

## Prepare
Read Valid and BtbDiagnosticRingInit in ring.c. The live ring stores its own address in self. Later operations require self to equal the address of the object being used.

This is an address-stability contract: initialise the object in its final location and do not copy the live owner.

## Trace a copy
Suppose ring is initialised at address A. Copying its fields to another object at address B also copies self as A. The new object's own address is B, so validation refuses it.

The existing regression exercises that case.

## Lab
Draw the two objects and arrows from their self fields. Explain why copying a snapshot is permitted while copying the live ring is not.

Expected: a snapshot contains observation values and no ownership marker. The live ring represents a specific owner.

## Exercise and explanation
Does this self check prevent every misuse? No. It is a useful guard within a documented single-threaded API, not memory isolation or protection against arbitrary memory corruption.

## Troubleshoot
If an operation unexpectedly returns BAD_STATE after moving a structure, inspect whether a container relocation or assignment copied the live owner. Keep its storage stable, or redesign ownership through a separate stable allocation.

Do not “repair” a copied ring by manually changing self. That bypasses the intended lifecycle instead of establishing a supported transfer operation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/diagnostic-ring/ring.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](22-treat-sequence-exhaustion-explicitly.md) · [Next lesson](24-publish-a-snapshot-after-validation.md)

