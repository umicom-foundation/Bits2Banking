# Reading rejection paths

[Course contents](index.md) · [Previous: Inputs, outputs and data types](02-inputs-outputs-and-data-types.md)

## Follow the failure as carefully as success

Open src/consensus/tx_check.cpp at v28.0 and locate CheckTransaction. Read its early-return branches. The function checks transaction-local conditions including nonempty input/output collections, output-value restrictions and repeated input references. Other validation stages provide context-dependent checks.

An early return stops the function when a condition fails. That can make the successful path easier to read, provided the error carries a useful reason. Do not remove a rejected-condition check merely because a normal sample transaction passes.

## Build a trace table

Use a notebook with columns: proposed input, expected rejection, evidence location, and untested assumptions. Try these fictional cases:

```text
case A: no outputs
case B: two inputs reference exactly the same previous output
case C: ordinary-looking values, but the referenced output was spent earlier
```

For A and B, identify the relevant local checks in the file. For C, follow callers and the wider state validation; do not claim this one function establishes availability. The boundary between local checks and ledger checks matters when designing a reusable validator.

## Apply the method to Umicom

Open a Framework API with a status return. List invalid input branches, then find tests that cover them. Ask whether the output is left unchanged on failure. Ask whether the caller checks the status. A library can reject bad input correctly while a UI still displays an old successful result.

These lessons use upstream code as reading material and original exercises. They do not copy Bitcoin Core implementation into Umicom or establish licence compatibility for any later reuse. An implementation change needs its own source review and tests.

## Exercise

Someone proposes: “CheckTransaction returned true, so we can credit the wallet immediately.” Explain the missing reasoning.

## Explained answer

Passing one set of structural checks does not establish script validity, current spendability, inclusion in an accepted block or settlement finality. Name the validation stage that produced a result in logs and UI state. A status such as structurally valid is more accurate than an unexplained verified label.

## Reading references

[Transaction types at v28.0](https://github.com/bitcoin/bitcoin/blob/v28.0/src/primitives/transaction.h) and [transaction checks at v28.0](https://github.com/bitcoin/bitcoin/blob/v28.0/src/consensus/tx_check.cpp) are fixed reading references. Use current maintained releases for any separate operational evaluation.

## Continue learning

[Course contents](index.md) · [Previous: Inputs, outputs and data types](02-inputs-outputs-and-data-types.md)

[Browser edition](../../../courses/introduction-to-bitcoin-source-code/lessons/03-reading-rejection-paths.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.

[Primary reference](https://github.com/bitcoin/bitcoin/tree/v28.0).
