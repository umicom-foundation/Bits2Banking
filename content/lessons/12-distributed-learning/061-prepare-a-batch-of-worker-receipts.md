# Distributed Learning — Lesson 061: Prepare a batch of worker receipts without exposing gradients

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **prepare a batch of worker receipts without exposing gradients** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

After a worker update has been independently authenticated, authorised and evaluated, the coordinator can publish a canonical, non-secret decision receipt. Commit to the receipt bytes or to the existing record-chain digest; keep raw gradients, private dataset identifiers and model weights in protected storage. Merkle batches provide compact later evidence about which decisions belonged to a known snapshot.

## Step-by-step worked example

In a synthetic three-worker round, receipts record ACCEPT, REJECT and QUARANTINE. The auditor batches the three already-validated record digests in a declared order. Inclusion of the REJECT record proves its presence, not that it was accepted.

## Practical task

Produce a safe field list for a public receipt and a separate protected evidence record.

### Worked answer and reasoning

The public record should contain only carefully reviewed commitments and policy versions; private data, credentials and raw tensors remain off-chain.

## Threat model and qualification limits

Independent quality evaluation is a separate prerequisite, not something the Merkle root calculates. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [FedAvg original research](https://arxiv.org/abs/1602.05629)

## Continue learning

- [Browser lesson](../../courses/distributed-learning/lessons/061-prepare-a-batch-of-worker-receipts.html)
- [Course study route](../../courses/distributed-learning/verifiable-batch-evidence.html)
- [Next lesson](062-pin-a-base-checkpoint-in-every-proof-context.md)

*Service to Many Leads to Greatness.*
