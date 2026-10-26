# Checkpoint and Training-Cursor Lifecycle in Umicom AI

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## A reusable training service, not application-owned state

A fine-tuning session contains several identities that must not drift apart: a frozen native decoder, selected trainable projection adapters, the reviewed dataset, the deterministic epoch schedule and the next-example cursor. All reusable state-management logic belongs in **Umicom Framework**, so Studio, AuthorEngine and future native applications can call the same API instead of implementing separate checkpoint formats.

The frozen decoder is identified by its canonical checkpoint SHA-256. The dataset is identified by the ordered SHA-256 calculated by the established reviewed-corpus owner. The selected adapter roles, rank and committed SGD count are held by the adapter service. The continuation service combines these declarations into one portable in-memory snapshot.

## Ownership and lifetime

`UmiAiTrainingDecoderProjectionAdapterSnapshotRestore` creates a **new** adapter with an independent training tape; it does not mutate the previous live adapter. The caller destroys that adapter using the established Framework destruction operation before destroying its borrowed frozen decoder. A snapshot buffer can be released after the restoration call; it is not retained by reference.

`UmiAiTrainingSupervisedContinuationSnapshotRestore` restores both the trained adapter and the exact logical cursor. Its caller must provide the already-approved frozen decoder and immutable dataset. A valid digest cannot make an unauthorised source legitimate.

## Training and evaluation boundaries

One `TrainNext` call advances one example in the existing deterministic training order. `FinishEpoch` is a separate step so a failed held-out evaluation cannot cause the last training example to be repeated. The earlier complete-run experiment API remains available unchanged.

A training attempt rejected before the SGD transaction leaves the adapter and cursor as they were. A successful SGD transaction is committed in memory. If the process crashes before the complete new snapshot becomes durable, restart must use the last **durable** approved snapshot, not a guessed cursor offset.

## Where a real application integrates

A thin Umicom application presents the user interface, chooses approved storage destinations through existing Framework services, calls the public checkpoint and training APIs, and displays progress and held-out metrics. It must not copy the low-rank maths, manually mutate opaque weights or implement a second dataset shuffle.

## Check yourself

Why does a saved cursor without matching trained weights not provide exact recovery? Because the cursor specifies **which gradients have already been applied**, while the weights record their cumulative numerical effect. A mismatch repeats or skips learning work. Review [the cursor equation](97-resume-deterministic-sgd-mid-epoch.md) and [the checkpoint's contents](95-what-an-adapter-checkpoint-must-save.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
