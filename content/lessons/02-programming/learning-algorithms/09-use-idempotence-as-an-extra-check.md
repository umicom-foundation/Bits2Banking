<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/09-use-idempotence-as-an-extra-check.md

PURPOSE:
Explain the lesson: Use idempotence as an extra check.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use idempotence as an extra check

An operation is idempotent when applying it again has the same observable effect as applying it once. Sorting an already sorted sequence is a useful example.

## Prepare

Read the second call to BtbListSort in sort_records.c. The first call has already produced the expected order. The second call must preserve that sequence.

Idempotence is a property of the result, not a promise that the implementation performs no work.

## Make the check precise

1. Establish the expected ordered values independently.
2. Sort the original input.
3. Compare every active value with that expectation.
4. Sort again.
5. Compare again.

The example uses the same explicit expected array for both comparisons. It does not copy the first result and assume that result was correct.

## Understand the limit

A function that always writes five zeroes could be idempotent and still be an incorrect sort. That is why the first expected-value check remains necessary.

Properties complement examples. They do not automatically replace all examples.

## Exercise

Name a second property for sorting: the smallest value must be at the beginning when the input is nonempty. Construct a broken result that satisfies this property but loses a duplicate.

Now combine size, value frequencies, ordering and idempotence. Explain what each detects.

## Connect to application work

Reapplying a layout preference or normalizing a configuration often benefits from idempotence. Sending a payment or appending a chat message usually requires a different duplicate-operation policy.

Never infer an operation's retry safety from its name. Read its contract and consider external effects.

Build and run the collections lab only after recording your predictions. When a check fails, preserve the failing input and result so the next investigation starts with evidence.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/sort_records.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-check-duplicates-survive-sorting.md)

