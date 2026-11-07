<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/16-use-an-oracle-for-a-small-model.md

PURPOSE:
Explain the lesson: Choose an independent expected result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Choose an independent expected result

## Prepare
Use deadline.c and the laboratory's existing tests. An oracle is the rule used to decide whether an observed result is correct.

For this small model, a hand-calculated table is a useful oracle. Copying the implementation into the test would reproduce many of the same mistakes.

## Construct a case
Start at tick twenty and arm interval three. Write the expected deadline, status at twenty-two, status at twenty-three and state after Fire.

Expected: deadline twenty-three, NOT_DUE, DUE and FIRED.

Now compare the code with the table rather than using the code itself to generate all expectations.

## Lab
Add cases for an unbounded wait, time reversal, a pending rearm and addition overflow. Explain the rule behind each expected refusal.

For overflow, the source checks the interval before addition. An unsigned wrap would produce a small deadline and corrupt the meaning of the wait.

## Preserve evidence
Keep the initial state, operations and results in the test. A failure message should identify which expectation failed. “Test failed” alone is harder to investigate.

## Troubleshoot
Do not change an expected result merely to match current output. First consult the API contract and trace the input. If the contract is ambiguous, clarify it and then update implementation and tests together.

## Continue
Apply this method to the bounded course notebook or a Framework activity model: use small examples whose results you can compute independently, then add boundary and refusal cases.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/monotonic-deadlines/deadline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-define-cancellation-at-a-deadline.md)

