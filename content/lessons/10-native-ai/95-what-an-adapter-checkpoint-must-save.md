# Lesson 95 — What Must a Fine-Tuning Checkpoint Save?

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning objectives

Distinguish a base-model checkpoint from adapter weights, understand which optimiser data must survive a restart, and identify why a report is not an executable model. By the end, you should be able to draw a safe recovery boundary without relying on a scripting runtime.

## 1. Start with the three different kinds of state

A native language-model application can contain several related but different records. The **frozen decoder** contains the original token embeddings, position embeddings, Transformer weights and output projection. An **adapter** contains only smaller trainable matrices inserted into selected attention and feed-forward projections. A **training cursor** records where to continue in an approved, ordered dataset.

If the original model is unchanged, it is wasteful to duplicate it inside every adapter snapshot. More importantly, it is dangerous to load an adapter against a different original model merely because the tensor dimensions happen to fit. The Umicom adapter snapshot therefore binds the adapter to the SHA-256 of the canonical, complete frozen decoder checkpoint.

| Record | What it can restore | What it cannot establish |
|---|---|---|
| Frozen decoder checkpoint | Original model weights and training-step identity | Permission to use the model |
| Projection-adapter snapshot | Selected adapter weights and adapter SGD step count | AdamW moments or approved dataset identity |
| Continuation snapshot | Adapter snapshot plus dataset digest, training plan and next-example cursor | Trusted publisher identity or storage durability |
| Experiment receipt | Aggregate measurements and source/model references | The trainable weights themselves |

The existing Framework `UmiAiTrainingDecoderProjectionAdapter` owns an independent tape, so the original decoder's graph-rewind policy cannot discard the adapter leaves.

## 2. Why checkpointing is more than saving an array

Suppose the model has an eight-token context, channels equal to eight and a rank-two adapter. The adapter consists of two matrices per selected projection. Their dimensions are `[inputChannels, rank]` and `[rank, outputChannels]`. If the query weight is 8×8, its rank-two adapter has `8×2 + 2×8 = 32` trainable elements, rather than 64 elements in the full projection.

Saving just those 32 numbers is insufficient. The restore operation also needs the projection role, exact rank, original base identity, element representation and order. The portable Framework checkpoint preserves these contracts without serialising a compiler-dependent C structure.

## 3. The real Framework boundaries

Use `UmiAiTrainingDecoderProjectionSnapshotSize` to calculate required storage, `...Encode` to publish the complete encoded snapshot and `...Restore` to create a **new** owned adapter bound to the active frozen decoder. A successful restore must not mutate an existing adapter.

Only an in-memory buffer is exported by this API. A caller that saves it to disk must use approved Framework file-publication services, preserve a last-known-good copy and protect access permissions. A single successful memory encoding does not mean a durable disk write succeeded.

## 4. What a training restart still needs

The existing optimiser in this learning path is stateless SGD. Given identical adapter weights, learning rate and next examples, the next updates can be reproduced. AdamW additionally retains moment estimates for each parameter; restarting those estimates at zero changes the optimisation algorithm. The snapshot must therefore **not** be called an AdamW resume checkpoint.

## Practice and worked answer

**Question:** If a selected projection is 8×16 and adapter rank is 2, how many adapter elements must be saved? **Solution:** `8×2 + 2×16 = 16 + 32 = 48` trainable elements. The 8×16 base weights remain frozen and are identified separately. A complete restart must also know where the data cursor stopped.

**Next:** [Portable model records](96-build-portable-snapshot-records.md) and [restoring SGD state](97-resume-deterministic-sgd-mid-epoch.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
