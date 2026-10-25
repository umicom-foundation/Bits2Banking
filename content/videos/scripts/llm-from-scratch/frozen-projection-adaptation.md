# Video narration — Train a Frozen Projection with Low-Rank Adapters

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Format:** teaching narration and storyboard · **Estimated duration:** 6–8 minutes

## 00:00 — The problem

**Visual:** One box labelled *frozen projection* receives a row of input numbers. A second, smaller route branches away and rejoins at the output.

**Narration:** “When a language model learns a new skill, one approach is to change all of its trained weights. Another approach is to keep an original weight matrix unchanged and train a smaller correction. Today we will understand that correction using just two matrices.”

## 01:00 — Calculate the shapes

**Visual:** Display the formula `Y = XW + (XA)B` and a shape table.

**Narration:** “The input X has I features. The frozen matrix W maps I features to O output features. We introduce A, which reduces I features to a smaller rank r, and B, which expands r values back to O. Both branches now produce compatible outputs that can be added.”

**Worked example:** For `I=64`, `O=64` and `r=4`, the frozen base has 4,096 values. The two trainable matrices together have 512 values. Explain that the frozen base still has to be available at inference time.

## 02:30 — Which values are allowed to change?

**Visual:** Base W marked *frozen*, A and B marked *trainable*. B begins as a matrix of zeros.

**Narration:** “The new path initially contributes zero because B contains zeros. The first output is therefore the original frozen output. When our loss function measures an error, backpropagation provides gradients for the trainable matrices. The optimiser receives only A and B; it never writes W.”

## 03:30 — Show the C23 contract

**Visual:** Highlight `UmiAiTrainingLowRankTrainStep` beside an input tensor, target tensor and result showing loss before the update.

**Narration:** “The Umicom Framework owns the training tape, the loss calculation, backpropagation and the atomic SGD update. The learning application calls one shared service. After each step, the Framework removes temporary graph nodes so memory does not grow indefinitely.”

## 04:45 — A checkpoint is not a complete training history

**Visual:** Two boxes, *adapter weights* and *optimiser state*, with a clear gap between them.

**Narration:** “A checkpoint containing adapter weights can help us reproduce an adapted output when paired with the exact frozen base. But a stateful optimiser also has momentum-like statistics. Saving weights alone cannot promise an exact continuation of an AdamW training run.”

## 05:45 — The limitation

**Visual:** One projection module versus a full multi-layer Transformer.

**Narration:** “Our tested educational service trains a low-rank correction for one dense projection using mean-squared error. A complete language-model fine-tuner also needs token-level language losses, adapter injection into selected Transformer blocks, checkpoint compatibility, approved data and independent evaluation. We should not call the small demonstration a production LLM.”

## 06:45 — Learner challenge

**On-screen exercise:** Input width 32, output width 16, rank 2. How many adapter parameters?

**Narration:** “Pause and calculate: A has 32 times 2 entries, and B has 2 times 16 entries. That totals 96 trainable values. Then identify which matrix is frozen, and which two the optimiser may update.”

**Related manuscript:** [Train a Frozen Projection with Low-Rank Adapters](../../../lessons/10-native-ai/train-a-frozen-projection-with-low-rank-adapters.md).
