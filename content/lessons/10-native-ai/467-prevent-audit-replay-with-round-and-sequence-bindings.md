# LLM from Scratch — Lesson 467: Prevent false novelty from replayed training receipts

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **prevent false novelty from replayed training receipts** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A valid inclusion proof can be replayed. If a worker sends a proof that its update was included in round 5, the same proof does not authorise accepting that update again in round 6. Federated learning requires both evidence of historical inclusion and admission to the current round, tied to a live job ticket, signed contributor identity, dataset policy and base-checkpoint version. The existing FederatedJob service manages process-local tickets and rejects duplicate completion; a ledger proof does not replace it.

## Step-by-step worked example

An update receipt for checkpoint P, round 5, sequence 7 has a valid inclusion proof. The coordinator is currently at checkpoint Q, round 6. The receipt must be rejected for current execution even when its proof remains historically true.

## Practical task

List the fields checked by the current-round admission decision before FederatedJobComplete can be invoked.

### Worked answer and reasoning

At minimum compare authenticated worker, round, sequence, base checkpoint, data permission and unconsumed ticket; do not transplant historical proof as fresh authorisation.

## Threat model and qualification limits

The Merkle service intentionally contains no worker identities or key material. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Umicom native Framework SHA-256](https://github.com/umicom-foundation/umicom-framework)

## Continue learning

- [Browser lesson](../../courses/llm-from-scratch/lessons/467-prevent-audit-replay-with-round-and-sequence-bindings.html)
- [Course study route](../../courses/llm-from-scratch/merkle-proofs-and-ledger-boundaries.html)
- [Previous lesson](466-compare-batched-audit-roots-with-streaming-record-chains.md)
- [Next lesson](468-separate-signed-replica-observations-from-consensus.md)

*Service to Many Leads to Greatness.*
