# Mathematics for AI — Unit 25: Loss Masks and Next-Token Alignment

**Umicom Foundation · Author: Sammy Hegab**  
**Prerequisites:** [Variables and functions](02-variables-and-functions.md), [cross-entropy](21-cross-entropy-for-native-fine-tuning.md)

## 1. A model predicts what comes next

An autoregressive decoder receives token `tᵢ` and predicts the following token `tᵢ₊₁`. The subscript `i` means a position in a sequence. During teacher-forced training the real preceding tokens are supplied, rather than using the model's earlier guesses.

Suppose a prompt is `AB` and a response is `C`. Write the full sequence with special tokens:

`[BOS, A, B, C, EOS]`

We train on next-token pairs, not token copies. At position `0`, the input is `BOS` and the target is `A`; at position `1`, `A → B`; at position `2`, `B → C`; at position `3`, `C → EOS`.

## 2. A mask selects the answer

If `A` and `B` are prompt context, the model does not need to receive loss for predicting them in this *response-only* exercise. The two desired targets are `C` and `EOS`. We therefore assign mask values `[0,0,1,1]` for the four next-token pairs. A mask value `1` means include this row's loss; `0` means exclude it.

Let `mᵢ` be a mask, `pᵢ` the predicted probability of the correct target at position `i`, and `Lᵢ = −ln(pᵢ)` the corresponding negative log-likelihood. The selected mean is:

`L(selected) = (Σᵢ mᵢ Lᵢ) / (Σᵢ mᵢ)`.

The denominator counts selected targets. It is **not** the total number of sequence positions. All-zero masks must be refused because division by zero has no defined training meaning.

## 3. Worked probability example

Suppose the model assigns 0.80 probability to `C` and 0.50 probability to `EOS` in the two selected positions:

- `−ln(0.80) ≈ 0.2231`.
- `−ln(0.50) ≈ 0.6931`.
- Mean selected loss: `(0.2231 + 0.6931) / 2 ≈ 0.4581`.

Changing either prompt-only loss does not change this particular selected mean, because the corresponding mask is zero. The prompt still influences the hidden states and predictions at the selected rows: *ignored loss* does not mean *ignored input context*.

## 4. What changes when the context is padded?

If the decoder expects eight inputs but the meaningful stream contains fewer tokens, right-padding positions receive `PAD` tokens. Their target mask remains zero. A loss on padding might teach the model to predict padding rather than useful answers.

The full reviewed prompt and completion must fit within the context. Truncating an answer but leaving an apparently valid EOS loss would create misleading training evidence.

## 5. Practice and answers

**Practice:** A sequence contains five next-token targets, with mask `[0,1,0,1,1]`. How many losses enter the average? **Answer:** 3.

**Practice:** Selected probabilities are `1/2`, `1/4`, and `1/2`. Calculate the average negative log-likelihood. **Answer:** `−(ln(1/2) + ln(1/4) + ln(1/2))/3 ≈ (0.6931 + 1.3863 + 0.6931)/3 ≈ 0.9242`.

**Practice:** Why is the first response target paired with the final prompt input token? **Answer:** the model always predicts the token *after* the current input position.

## Connect to the C23 Framework

Study [the byte-window laboratory](../10-native-ai/prepare-assistant-response-training-windows.md), then [selected-token cross-entropy](../10-native-ai/selected-token-cross-entropy-in-c23.md). Both use the established Umicom Framework tokenizer, tape and loss semantics. No numerical engine belongs inside this Markdown repository.
