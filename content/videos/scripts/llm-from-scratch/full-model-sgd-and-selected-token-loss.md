# Train a Stacked Decoder with Selected-Token Cross-Entropy

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT

**Intended length:** Approximately 8 minutes.  
**Audience:** Beginner-to-intermediate C23 and AI students.

### Scene 1 — The difference between context and supervision

**Visual:** `[BOS, Q, A, EOS]` expands into inputs, next-token targets and a zero/one mask.

**Narration:** “The question helps the model interpret the answer, but we don't need to penalise it for every prompt token as if it were the answer. The loss mask selects response and end-of-sequence targets. Other rows supply context without a direct loss contribution.”

### Scene 2 — Walk through two probabilities

**Visual:** Correct target probabilities 0.5 and 0.25, with loss values 0.6931 and 1.3863.

**Narration:** “For each selected target, the loss is the negative natural logarithm of the model's assigned probability. Add the selected losses and divide by the number of selected targets. Ignore padding in the denominator.”

### Scene 3 — The backward pass across layers

**Visual:** Gradient arrows flow backward from logits through Block 2 and Block 1, then to the parameter leaves.

**Narration:** “The Framework already knows how to differentiate the tensor operations recorded on its training tape. Our stacked model calls that service. It updates the trainable leaves as one validated SGD transaction, so a rejected weight cannot leave half a model updated.”

### Scene 4 — When to evaluate

**Visual:** A loss measurement before SGD, then a new forward pass after SGD.

**Narration:** “The training call reports the loss before the update. To know what happened afterwards, evaluate again. Even if a tiny teaching example improves, it tells us nothing by itself about an unseen customer request or a real software development task.”

### Scene 5 — Safety and data rights

**Visual:** Reviewed public source → Framework admission → training windows. A private document is not allowed into the pipeline.

**Narration:** “Correct gradient mathematics does not create a right to train on a document. Source rights, personal-data review and leakage checks remain separate required controls. Educational examples are fictional.”

**Student task:** With probabilities 0.5 and 0.25 on two selected targets, calculate mean cross-entropy. Expected: approximately 1.0397.

**Related reading:** [Lesson 126](../../../lessons/10-native-ai/126-supervise-only-reviewed-completion-tokens.md) and [Mathematics Unit 50](../../../lessons/11-maths-for-ai/50-combine-selected-token-cross-entropies.md).
