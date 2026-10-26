# Hold-Out Evaluation and Reproducible Training Order

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT

**Intended length:** Approximately 8–10 minutes.  
**Audience:** Students building trusted training/evaluation workflows.

### Scene 1 — Different documents, different partitions

**Visual:** Three fictional public source cards. Two go to training, one to held-out evaluation. The same document cannot appear on both sides.

**Narration:** “If a document is used both for practice and for the examination, the final score may exaggerate generalisation. Keep every exact original source in only one partition. Near-duplicate wording requires extra review, too.”

### Scene 2 — A deterministic shuffle

**Visual:** Indices `[0,1,2,3]` rearrange by a sequence of explicit swaps. The held-out index never enters the list.

**Narration:** “The order of examples matters to SGD. We use the existing Framework random-index service with a known seed for each epoch. That makes the experiment reproducible without introducing another random generator.”

### Scene 3 — Loss weighted by targets

**Visual:** One example has one supervised token with loss 1.0; another has three supervised tokens with average loss 3.0.

**Narration:** “Don't just average the two example averages. The second represents three targets. The overall mean is `(1×1+3×3)/4 = 2.5`.”

### Scene 4 — Record what changed

**Visual:** Initial held-out loss, then epoch one, two and three; original-source digest and model-step count shown separately.

**Narration:** “Training and held-out loss are different evidence. This laboratory emits aggregate counts and an identity digest for the token windows, not private text. A token-window digest does not verify source licences.”

### Scene 5 — Recovery limits

**Visual:** An unexpected failure after several SGD updates; already committed updates remain in the model.

**Narration:** “The complete multi-epoch run is not one atomic transaction. If an operation fails after some updates, the model may have changed. Snapshot a trusted model beforehand when rollback is required. Never claim the whole run succeeded after a partial failure.”

**Student task:** Explain why a held-out example must not appear in the training permutation.

**Related reading:** [Lesson 130](../../../lessons/10-native-ai/130-run-held-out-stacked-training-experiments.md) and [Mathematics Unit 53](../../../lessons/11-maths-for-ai/53-compare-training-and-heldout-loss.md).
