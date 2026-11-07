# Building Blockchain from Scratch

Construct a small offline ledger step by step: exact record bytes, validation, state changes and recoverable storage. Reuse Framework services when integrating the teaching design.

## Before you begin

- [Introduction to Blockchain](../../../courses/introduction-to-blockchain/index.html)
- [Learning C](../../../courses/learning-c/index.html)

The first prerequisite supplies the subject background. Additional language courses prepare you for the code examples; read their first-program, values, functions and data lessons before attempting the labs.

## Lessons available now

1. [An exact record format](01-an-exact-record-format.md)
2. [Validate before changing state](02-validate-before-changing-state.md)
3. [History, replay and recovery](03-history-replay-and-recovery.md)

## How to study

Read one lesson, predict the example result, then attempt the exercise before opening its explained answer. Save optional practice programs in a folder you choose. Expected outputs describe what to check; they are not a record that a command has run on your computer.

## Planned continuation

Next modules: canonical record decoder; Framework SHA-256 integration; signed proposals; immutable event identifiers; transactional persistence; replay; crash recovery; Merkle proofs; multi-node simulation; adversarial tests and protocol limits.

These opening lessons do not claim a complete pricing engine, Bitcoin node, blockchain network, Linux distribution or production web server. Each course develops the relevant part in order.

[Finance and systems learning routes](../../../courses/finance-and-systems.html)

[Browser contents](../../../courses/building-blockchain-from-scratch/index.html)

## Practical labs: read, change and check

Follow these after the introductory lessons. Each lab includes its own setup recap and explains the expected result.

- [Link records with Framework hashes](04-link-records-with-framework-hashes.md)

## Continue with a practical source study

Two programs can describe the same record yet hash different bytes. This lab continues the Framework hash exercise by designing a small unambiguous record representation before using the existing SHA-256 service.

- [Define the bytes before hashing a record](05-define-the-bytes-before-hashing.md)


- [Turn record fields into defined bytes](06-turn-record-fields-into-defined-bytes.md)

- [Connect a record to the previous digest](07-connect-a-record-to-the-previous-digest.md)

- [Replay a chain to check determinism](08-replay-a-chain-to-check-determinism.md)

- [Detect an edited record](09-detect-an-edited-record.md)

- [Give a hash input a domain](10-give-a-hash-input-a-domain.md)

- [Separate integrity from approval](11-separate-integrity-from-approval.md)

- [Choose a trusted reference for verification](12-choose-a-trusted-reference-for-verification.md)

- [Plan a small chain-verification project](13-plan-a-small-chain-verification-project.md)
