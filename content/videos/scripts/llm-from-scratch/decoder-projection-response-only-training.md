# Video Lesson — Fine-Tune Real Transformer Projections Without Changing the Base Decoder

**Umicom Foundation · Bits to Banking**  
**Writer and presenter:** Sammy Hegab  
**Language:** UK English  
**Format:** Educational narration and storyboard; this is not a completed recording.

## Learning goals

Show, visually and numerically, how a frozen native C23 Transformer decoder
can be adapted using selected low-rank Q/K/attention/MLP projections, how a
response-only training mask is formed, and why loss and checkpoint identity
must be independently verified.

## Scene 1 — The original model (0:00–1:05)

**Visual:** A diagram of an existing decoder. Draw token embeddings and
positional embeddings entering one pre-layer-normalised Transformer block,
followed by a vocabulary projection. Mark the original weight matrices in
grey with lock symbols. Do not imply that a pretrained large model is present.

**Narration:** “We have already built a small, inspectable Transformer decoder
inside Umicom Framework. It predicts token probabilities using its existing
weights. Now we want to teach it a small, reviewed task without silently
changing its original checkpoint. That is the purpose of adapter training.”

## Scene 2 — The two low-rank matrices (1:05–2:20)

**Visual:** Show an original `8 × 8` matrix, then an `8 × 2` down matrix and a
`2 × 8` up matrix. Animate the residual computation:

`Y = XW + (XA)B`.

**Narration:** “The frozen matrix W keeps its trained values. The two smaller
matrices, A and B, are trainable. With width eight and rank two, their sizes
are sixteen and sixteen, adding thirty-two trainable values. The initial up
matrix contains zeros, so the first adapted result matches the frozen result.
Training gradually changes these new matrices, not W.”

## Scene 3 — Choose the projection locations (2:20–3:20)

**Visual:** Highlight Query, Key, Value, attention output, feed-forward up and
feed-forward down in the **existing** Transformer block. Show checkboxes
selecting Query, Key, attention output and feed-forward down. Display the
parameter count: `32 + 32 + 32 + 48 = 144`.

**Narration:** “We can choose exactly where adapters participate. Every
projection still executes through Umicom Framework's shared tape, attention
and matrix operations. No second implementation of a Transformer belongs in
Bits2Banking or an application module.”

## Scene 4 — Train only the answer (3:20–4:40)

**Visual:** Present the four-position input/target/mask table:

| Input | Next target | Loss mask |
| --- | --- | ---: |
| BOS | Q | 0 |
| Q | A | 1 |
| A | EOS | 1 |
| PAD | PAD | 0 |

**Narration:** “A supervised example includes the prompt and the assistant's
answer. The prompt supplies context, but we do not want to reward the model
for reproducing the prompt as its answer. Only the answer and the final
end-of-sequence target contribute to this training loss. The two selected
loss terms are averaged over two tokens, not four.”

## Scene 5 — The gradient path (4:40–6:00)

**Visual:** Trace arrows backwards from selected token logits through the
vocabulary projection, Transformer attention and MLP, into the adapter-up and
adapter-down tensors. Keep the original decoder weights locked.

**Narration:** “The existing Framework cross-entropy and Backward operators
calculate gradients. We update only adapter matrices using the existing
transactional optimiser. Notice that a prompt position can still affect later
answer predictions through attention, even when its own prediction target is
excluded from the loss.”

## Scene 6 — Lifetime and integrity (6:00–7:10)

**Visual:** Two separate tape containers. Label one ‘Canonical decoder tape’
and the other ‘Adapter training tape’. Show a SHA-256 checkpoint fingerprint
and an unchanged-base comparison.

**Narration:** “The original decoder's tape has a fixed parameter prefix and
rewinds after use. We must not place new long-lived adapter tensors where that
rewind can erase them. Instead, the Framework owns a separate tape with frozen
copies of the real decoder parameters. It checks the original model's exact
checkpoint identity before every adapter operation. If that checkpoint
changes, the old adapter is refused rather than applied to the wrong model.”

## Scene 7 — Interpret the experiment (7:10–8:15)

**Visual:** Show separately labelled numbers for pre-update training loss,
post-update training loss and **held-out** evaluation loss. Add a clear warning
that all results are measurements of a small educational model.

**Narration:** “A decreasing training loss is encouraging, but it is not the
same as useful generalisation. Test on separately reviewed, held-out examples.
Check that the original checkpoint remains unchanged and that every C23
regression really executed. This laboratory is a step towards Umicom AI
applications; it is not yet a production-scale language model.”

## Closing learner exercises

Ask the viewer to calculate the trainable parameter count for an `8 × 8`
projection with rank four, explain why ignored prompt-position logits are not
the same as removing the prompt from the context, and identify which Framework
object owns adapter tensors during training.

**Companion reading:** [Projection response-only fine-tuning](../../../lessons/10-native-ai/train-transformer-projections-with-response-only-loss.md),
[Mathematics Unit 27](../../../lessons/11-maths-for-ai/27-selected-gradient-paths-in-transformers.md)
and [Mathematics Unit 28](../../../lessons/11-maths-for-ai/28-parameter-budgets-and-evaluation-loss.md).

**Production note:** Voice, music, images, B-roll and captions remain subject
to explicit rights review. This script is educational material, not an
approved AI-training dataset or a generated recording.
