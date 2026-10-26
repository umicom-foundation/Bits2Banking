# Lesson 98 — Handle Failures Without Losing or Repeating Training

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning objectives

Separate three states: an attempted update, a committed adapter update and a durably saved checkpoint. Learn what to do when disk I/O, evaluation or a training step fails.

## 1. A training attempt is not automatically a commit

Assume a native training call receives approved next-token targets. It validates the model, source identity, mask and learning rate; constructs its temporary tape graph; computes selected cross-entropy; differentiates it; then asks the established SGD writer to update the adapter parameters. If any calculation fails **before** the SGD transaction completes, no new training step should be counted.

Once the SGD writer returns success, the update is committed in the active in-memory adapter. An error in a later measurement cannot safely pretend that update never happened. The next valid cursor must reflect the weights that actually exist.

## 2. Evaluate at a clear boundary

In the new continuation API, the run deliberately separates `TrainNext` and `FinishEpoch`. Training the final example advances the offset to the known training-example count. `FinishEpoch` carries out the held-out evaluation and transitions to the next epoch. If held-out assessment is unavailable, the training state stays at the end-of-epoch boundary; it does **not** train that example again.

## 3. Memory snapshots and durable files are different

`SnapshotEncode` returns one complete native byte array. Successful encoding does not imply that bytes have reached a storage device. A production Umicom application should apply the existing Framework approved-file policy to write a new staging file, flush and publish it safely, keep the earlier known-good snapshot until the new one is verified, and restrict filesystem permissions.

Do not teach an application to overwrite its only recovery copy directly. Reopening a file and comparing its digest and complete length can detect accidental damage but cannot prove the source was trusted. An appropriately signed approval is a separate security decision.

## 4. Predict recovery behaviour

| Failure point | In-memory weights | Next safe action |
|---|---|---|
| Invalid source approval | Unchanged | Correct review evidence; do not train |
| Insufficient snapshot buffer | Unchanged | Allocate exact capacity and encode again |
| Invalid loss mask | Unchanged | Correct window preparation |
| Completed SGD, later evaluation fails | Updated | Keep committed cursor and retry evaluation |
| Crash after update but before durable snapshot | Possibly lost from disk | Resume **only** from the last complete approved snapshot |
| Tampered snapshot | Never admitted | Recover from independently approved good copy |

## Practice

A trainer saved a complete snapshot after 12 updates and then performed 3 more updates before a power failure. The only intact on-disk checkpoint has 12 updates. Can it resume as though 15 updates survived? **No.** It must restore 12 updates and repeat the subsequent deterministic sequence, or adopt a separately designed durable per-step transaction mechanism.

Read [portable record integrity](96-build-portable-snapshot-records.md) and [restart verification](99-verify-restored-training-against-uninterrupted.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
