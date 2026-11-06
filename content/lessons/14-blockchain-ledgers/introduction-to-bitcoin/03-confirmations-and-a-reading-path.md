# Confirmations and a reading path

[Course contents](index.md) · [Previous: Hashes, signatures and ownership](02-hashes-signatures-and-ownership.md)

## Why several histories can temporarily exist

Messages take time to travel. Two participants can learn about different valid candidate blocks before hearing about the other candidate. A block groups transactions and refers to a previous block. A chain is a linked history of such blocks.

Bitcoin nodes apply consensus rules and use accumulated proof of work to select among valid competing chains. A longer-looking list of invalid blocks is not acceptable. A confirmation describes a transaction's inclusion in the selected chain and subsequent blocks built on that history. It is not a promise that a transaction can never be displaced.

```text
shared block --> candidate A --> another valid block
           \--> candidate B
```

Draw this fork on paper. Circle the currently selected history. If selection changes, a wallet may need to update the status of transactions. This change is called a reorganisation. Software displaying balances must account for it rather than treating the first received message as permanent truth.

## Learn in a deliberate order

1. Explain inputs, outputs and change without code.
2. Distinguish hashes from signatures and state validation.
3. Read the Introduction to Bitcoin Source Code course to see how one implementation separates responsibilities.
4. Study the independent blockchain construction course for encoding and state changes.
5. Only then attempt the Assembly and C implementation labs. A small ledger is not automatically Bitcoin-compatible.

This course does not require buying bitcoin, joining a mining pool or opening a trading account. The purpose is to understand software and protocols. Performance and investment claims are outside the examples.

## Exercise

Two nodes agree that a block hash is correctly calculated. Is that enough to accept all its transactions? List at least three other questions.

## Explained answer

No. Are the referenced outputs available? Do signatures and spending conditions hold? Are values and fees valid? Does the block satisfy the relevant header and consensus constraints? These questions are not replaced by a vote that the hash looks right.

## Connect to existing lessons

Use the existing blockchain-ledgers library after these foundations for Merkle proofs, forks and finality. A general ledger lesson may use an account model; keep that model distinct from Bitcoin's unspent-output model.

## Continue learning

[Course contents](index.md) · [Previous: Hashes, signatures and ownership](02-hashes-signatures-and-ownership.md)

[Browser edition](../../../courses/introduction-to-bitcoin/lessons/03-confirmations-and-a-reading-path.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.

[Primary reference](https://bitcoin.org/bitcoin.pdf).
