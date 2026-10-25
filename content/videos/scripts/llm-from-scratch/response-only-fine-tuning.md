# Video lesson — Fine-Tune Only the Assistant's Response

**Narration and storyboard · Umicom Foundation · Sammy Hegab**  
**Format:** Educational video script, not a completed recording.

## Opening scene — The prompt and the answer

**Visual:** Two text cards. One says **Prompt: Hi**; the other says **Response:  OK**. A horizontal sequence adds `BOS` and `EOS` around the text.

**Narration:** "A Transformer does not directly understand our two text cards. It receives token IDs and learns to predict which ID comes next. We will show how to tell a small native model *which predictions* belong to the approved assistant response."

## Scene — Move the targets by one position

**Visual:** Two horizontal rows labelled `INPUT` and `TARGET`. Input begins with BOS; target begins with the first prompt token. Highlight the last prompt input and the first completion target.

**Narration:** "This is the most important alignment step. The model predicts the token after the one it just read. The first response character is supervised at the position of the last prompt token, not at the position of the first response character."

## Scene — Switch on the loss mask

**Visual:** Eight cells beneath the target row, with `0,0,1,1,1,1,0,0`. The selected cells correspond to completion bytes and the final EOS target.

**Narration:** "A one means this target contributes to loss. A zero means it is context or padding and does not contribute directly. The prompt is still used to calculate the response. We are masking the *training objective*, not deleting earlier information."

## Scene — Calculate a loss without code

**Visual:** Write `−ln(0.8) ≈ 0.2231` and `−ln(0.5) ≈ 0.6931`, then average to `0.4581`.

**Narration:** "Cross-entropy asks how much probability the model gave the correct answer. We average only selected targets. Dividing by every token in the context would reward or penalise the model for positions we deliberately excluded."

## Scene — Follow a gradient through the existing Framework

**Visual:** Draw `original decoder → frozen logits → adapter → selected rows → cross-entropy → backward → adapter-only SGD`. Put a lock icon above the original decoder.

**Narration:** "Our C23 Framework already owns the decoder, tape, matrix multiplication, cross-entropy and SGD. New source code composes those established components. The base decoder remains frozen, and only the adapter's trainable matrices change. This is a bounded logit-residual experiment, not full-model LoRA."

## Scene — Verify before claiming success

**Visual:** Show three checks: *ignored-row logit gradients are zero*, *selected loss matches an independently calculated answer*, *original checkpoint bytes remain unchanged*.

**Narration:** "The test does not pass just because the programme prints a number. We check its mathematics and memory ownership. We also check that the source material was separately approved for training. A correct loss mask cannot grant copyright permission or remove private data."

## Closing and learner exercise

**Visual:** Present prompt `AB`, reply `C`, with `[BOS,A,B,C,EOS]`.

**Narration:** "Which next-token targets should be selected for response-only learning? Write the input row, target row and mask before revealing the result. The selected targets are C and EOS. The prompt targets remain visible as context, but their loss mask is zero."

**Companion reading:** [Byte windows](../../../lessons/10-native-ai/prepare-assistant-response-training-windows.md), [selected cross-entropy](../../../lessons/10-native-ai/selected-token-cross-entropy-in-c23.md), [Mathematics Unit 25](../../../lessons/11-maths-for-ai/25-loss-masks-and-next-token-alignment.md).
