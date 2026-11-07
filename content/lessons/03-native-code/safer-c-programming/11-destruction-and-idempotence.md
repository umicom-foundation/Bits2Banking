<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/11-destruction-and-idempotence.md

PURPOSE:
Explain the lesson: Make repeated cleanup harmless.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Make repeated cleanup harmless

## Prepare
Open `BtbNoteDestroy` and the final assertions in the fault-injection test. Cleanup releases resources that an object owns. Idempotent cleanup means repeating the cleanup operation has the same resource state as performing it once.

The lab starts with `BtbNote note = {0};`. Zero initialization establishes the empty representation expected by Init and Destroy.

## Follow destruction
Destroy first accepts a null note pointer as a no-op. For a real note it checks whether a release callback exists, releases each non-null owned field, then assigns a zero-valued structure to the object.

The final assignment is important: it clears the pointers, revision and allocator together. A second destruction sees empty state and releases nothing.

## Trace the counts
After successful Init, live is 2. After successful Replace, live is still 2: two new allocations replaced two old ones. After Destroy, live is 0. After another Destroy, live remains 0.

These counts alone do not prove the correct allocations were released; the test combines them with field contents and revision checks. A more advanced allocator double can track individual allocation identities.

## Exercise
Draw the object after each of those four operations. Include title pointer, body pointer, revision and callback context. Explain why Init is allowed again after destruction but refused while the original initialized object still owns fields.

Expected reasoning: the empty representation can accept new ownership; reinitializing a live object would otherwise lose its existing allocations.

## Diagnose a cleanup failure
If live becomes negative or a release aborts, inspect whether two paths release the same ownership. If live stays positive, inspect every early return after an allocation. Do not “fix” a leak by resetting the live counter.

Only call Destroy for objects obeying the documented initialization contract. Random uninitialized storage may contain arbitrary pointer values. Production Framework objects may use explicit Create/Destroy handles or reference counts instead; follow their actual lifecycle rather than assuming this teaching structure's rules apply everywhere.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/fault-injection/note.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-borrowed-pointers-after-replacement.md) · [Next lesson](12-failure-matrix-and-sentinels.md)

