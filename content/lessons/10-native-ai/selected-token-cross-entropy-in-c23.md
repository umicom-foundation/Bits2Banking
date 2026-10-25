# Compute Assistant-Response-Only Cross-Entropy in C23

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native Framework APIs:** `UmiAiTrainingSelectedCrossEntropy`, `UmiAiTrainingDecoderLogitAdapterTrainSelected`

## Learning outcome

Explain why a loss mask changes the training objective, calculate its mean loss by hand, follow gradients through the original Framework tape, and verify that a frozen language-model decoder remains unchanged while an adapter learns.

## 1. Start with probabilities, not a new optimiser

Suppose a next-token model assigns a probability of 0.8 to one correct reply token and 0.5 to another. Their negative log-likelihoods are:

`L₁ = −ln(0.8) ≈ 0.2231` and `L₂ = −ln(0.5) ≈ 0.6931`.

If these are the only two supervised positions, **response-only mean cross-entropy** is:

`L = (L₁ + L₂) / 2 ≈ 0.4581`.

If a prompt has several context tokens but the training objective does not supervise them, the denominator must be **2**, not the total context size. Padding does not provide legitimate target instructions either.

## 2. Keep the original numerical owner

The Framework already implements `UmiAiTrainingCrossEntropy` and reverse-mode differentiation on the native C23 tape. The new selected-token function composes existing operations:

1. Inspect logits with shape `[rows, vocabulary]`.
2. Validate that mask values are exactly 0 or 1, and at least one row is selected.
3. Build a fixed, nontrainable row-selection matrix with one `1` per selected target.
4. Multiply the selector by the original logits using `UmiAiTrainingMatmul`.
5. Calculate the **existing** cross-entropy on the selected rows.
6. Let the **existing** `UmiAiTrainingBackward` propagate gradients through that matrix to the original logits.

For all-ones masks, the service delegates directly to ordinary cross-entropy. The dense selection matrix is a bounded, correctness-first teaching bridge, not a production-scale fused GPU loss kernel.

## 3. The complete objective at the decoder adapter boundary

```c
#include "umicom/ai/training/decoder_logit_adapter.h"

/* A caller owns the already-created adapter and a full context of valid IDs.
   mask[] comes from a reviewed supervised window; length is contextLength. */
UmiAiTrainingDecoderLogitStep report = {0};
UmiStatus status = UmiAiTrainingDecoderLogitAdapterTrainSelected(
    adapter, inputs, targets, contextLength,
    mask, contextLength, 0.025F, &report);

if (status == UMI_STATUS_OK) {
    /* report.crossEntropyBeforeUpdate is the RESPONSE-ONLY mean loss. */
}
```

This public entry point reuses the *actual frozen decoder's* logits, the previous logit-residual adaptation tape, the canonical backward calculation and transactional SGD. The historical unmasked `TrainStep` and `Evaluate` functions are unchanged. Callers must deliberately select the masked interface.

The adapter here still modifies final logits; it is **not yet a complete set of LoRA weights injected throughout the opaque decoder's Q/K/V and feed-forward projections**. Keep that limitation visible when interpreting evidence.

## 4. Why the gradient of an ignored row is zero

A selection matrix contains one row for each supervised token. An ignored row has no nonzero entry in that matrix. Its logit values therefore do not influence the selected loss, so the chain-rule gradient through the selection operation is zero at that position.

For example, logits with four input rows and a mask `[0,1,0,1]` produce a two-row selected logit tensor. A numerical test must confirm that the gradient of every logit in input rows zero and two is exactly zero, within the tape's defined float representation.

Use independent expected cross-entropy values to avoid a test that simply repeats the same implementation's answer.

## 5. Failure handling and evaluation

The selected objective refuses an all-zero mask, a mask containing a value other than 0 or 1, an out-of-vocabulary selected target, or insufficient tensor capacity. It leaves a caller's loss handle unchanged on rejection and uses the tape's existing rollback contract for intermediate nodes.

The decoder adapter's public API additionally requires **every** submitted target ID, including ignored positions, to be a valid vocabulary ID. Padding targets should use the existing `PAD=0` token, not a `SIZE_MAX` sentinel. The lower-level selection operator can ignore arbitrary target values in excluded rows, but the adapter's stricter historic decoder contract is preserved.

Compare held-out selected-token loss on examples from completely separate reviewed sources. Lower training loss alone cannot authorise new financial-system code or live trading decisions.

## 6. Exercises

**A.** A full context contains eight rows, three of which have a loss mask of 1. What is the loss denominator? **Answer:** 3.

**B.** The selected token probabilities are 1/2 and 1/4. Compute the mean cross-entropy. **Answer:** `(-ln(1/2) - ln(1/4))/2 = (0.6931 + 1.3863)/2 ≈ 1.0397`.

**C.** Why should an adapter-only training test compare the base decoder's checkpoint bytes before and after learning? **Answer:** to detect unintended changes to the supposedly frozen original decoder.

**D.** Does a selected-token objective make unreviewed data safe? **Answer:** no. The mask controls gradient participation, not legal permission, privacy or source provenance.

**Next:** [Mathematics Unit 25 — Loss masks](../11-maths-for-ai/25-loss-masks-and-next-token-alignment.md).
