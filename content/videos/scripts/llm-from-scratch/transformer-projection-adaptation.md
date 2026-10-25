# Training Small Adapters Inside a Transformer Block

**Bits to Banking · Umicom Foundation**  
**Narration and educational storyboard**  
**Author:** Sammy Hegab

## Intended audience and learning outcome

An introductory developer who has read about matrix multiplication and gradients. After the video, the learner can identify the six dense projection roles of a Transformer block, explain why a frozen base may receive a trainable low-rank correction, and distinguish a block-level proof from complete language-model fine-tuning.

## Scene 1 — Inside the original block

**Visual:** A simple left-to-right diagram: input → normalisation → Q/K/V → causal attention → output projection → residual → normalisation → feed-forward up/down → residual.

**Narration:** “A Transformer block is not one giant equation. It is a sequence of smaller, testable operations. Umicom Framework already owns the mathematics of normalisation, causal attention, matrix multiplication and reverse-mode gradients. We will keep those owners and change only selected dense projections.”

**On-screen term:** A *projection* maps a row of numbers into another row using a weight matrix.

## Scene 2 — Add one small correction

**Visual:** Show `XW` as the original path, alongside `XA` then `×B`. Add the two output rows.

**Narration:** “We keep the original matrix W unchanged. We introduce two small trainable matrices A and B. The new output is the original result plus a low-rank correction. When B starts at zero, the correction is zero: an untrained adapter preserves the original prediction.”

**Worked example:** Input channels 128, output channels 256, rank 8. Display original weights `32,768` and trainable adapter values `3,072`.

## Scene 3 — Attach to the Framework

**Visual:** Highlight Query and feed-forward Up roles in the block. Overlay the existing `UmiAiTrainingLowRankForward` name next to each chosen projection.

**Narration:** “The Framework now offers an optional projection hook. A missing adapter calls the established matrix multiplication. A selected adapter uses the established low-rank tape primitive. The rest of the Transformer stays exactly where it belongs.”

**Engineering callout:** The complete frozen base is checked against the canonical weight tensor before starting the adapted graph. A matching shape is not enough.

## Scene 4 — Follow gradients, not just outputs

**Visual:** Reverse arrows from a scalar loss to the two small matrices. Leave canonical W grey and unchanged.

**Narration:** “Automatic differentiation calculates how the loss responds to each trainable adapter value. The application asks the Framework for A and B handles only. Its transactional optimiser writes those two matrices, not the original W. After the update, temporary graph nodes are released and the retained weights remain available.”

**Micro-example:** `y = xw+(xa)b` with `x=2`, `w=3`, `a=0.5`, `b=0`, target 7. First loss 0.5, after one learning-rate-0.1 step on b the loss becomes 0.405.

## Scene 5 — Evidence before deployment

**Visual:** Five test cards labelled Initial parity, Frozen base, Gradient update, Graph rollback and Wrong-base rejection.

**Narration:** “The first scientific question is not whether fine-tuning sounds promising. It is whether the untrained adapter reproduces the original block, whether the base weights remain unchanged, whether the adapter can learn under a declared objective, and whether failed operations leave the model consistent.”

**Closing message:** “This is a qualified Transformer-block adaptation component, not yet complete Umicom LLM fine-tuning. Decoder lifecycle, token-level response masking, optimiser-state restart and held-out evaluation are separate engineering milestones.”

## Companion reading and learner activity

Read [Fine-tuning Transformer projections](../../../lessons/10-native-ai/adapt-attention-and-feed-forward-projections.md) and [Maths Unit 24](../../../lessons/11-maths-for-ai/24-gradients-through-low-rank-projections.md). Calculate the low-rank parameter count for a 64×64 projection and rank 4. Then explain why frozen weights are still needed when the adapter has finished training.
