# Video lesson — Native decoder logits and low-rank adaptation

**Bits to Banking · Umicom Foundation**  
**Narration and storyboard · Author: Sammy Hegab**

**Learning objective:** distinguish a frozen native Transformer from its trainable output adapter; explain next-token cross-entropy and how to verify the original model remains unchanged.

## Opening — What will we build? (0:00–0:45)

**On screen:** two clearly separate boxes: *Frozen Umicom Decoder* and *Trainable Low-Rank Logit Adapter*.

**Narration:** “Our Umicom Framework already produces logits using a native C23 decoder-only Transformer. Today we keep every original model weight frozen and train two small matrices that correct the output logits. We are not changing the attention calculations or claiming to have created a general-purpose coding assistant.”

## The mathematics (0:45–2:30)

**On screen:** `Z_adapted = Z + (Z × D) × U`, then a shape diagram: `[T,V] × [V,r] × [r,V]`.

**Narration:** “Z contains the original model's token scores. D reduces the score representation to a small rank. U expands it back to vocabulary width. The result is added to the untouched scores. If U starts at zero, the first adapted prediction is exactly the frozen prediction, up to floating-point conventions.”

**Worked example:** display a rank-one residual from Mathematics Unit 22, `x=[2,1]`, `D=[0.5,−0.2]`, `U=[0.1,−0.3]`. Show the intermediate `0.8`, the residual `[0.08,−0.24]`, and the corrected output.

## Training objective (2:30–4:10)

**On screen:** a three-choice next-token distribution and its correct target.

**Narration:** “Cross-entropy asks how much probability the model assigned to the observed next token. The Framework's own training tape calculates stable cross-entropy and reverse-mode gradients. Only the adapter matrices are passed to the optimiser. Lower loss on one short example does not prove strong performance on new documents.”

## Engineering validation (4:10–5:30)

**On screen:** a simple checklist beside a CTest terminal screenshot placeholder, not fabricated results.

**Narration:** “Before we accept an adaptation, we compare frozen decoder logits before and after training, reject invalid token IDs and non-finite learning rates, verify that repeated steps do not grow the temporary graph, and evaluate on genuinely held-out examples. Model training and adapter training are separate lifecycles.”

## Closing — What follows? (5:30–6:00)

**On screen:** “Next: reviewed corpus integrity, then projection-level Transformer adapters.”

**Narration:** “The component in this lesson is a logit-residual learning head. LoRA placed inside attention or feed-forward projections is a different architecture and needs its own implementation and tests. The Umicom Framework remains the source of truth for both.”

**Companion reading:** [Native adapter lesson](../../../lessons/10-native-ai/train-a-frozen-decoder-logit-adapter.md) · [Cross-entropy](../../../lessons/11-maths-for-ai/21-cross-entropy-for-native-fine-tuning.md) · [Low-rank matrices](../../../lessons/11-maths-for-ai/22-low-rank-residuals-and-frozen-models.md).
