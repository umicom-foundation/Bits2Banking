# Mathematics for AI — Unit 36: Token-Weighted Held-Out Averages

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## The everyday idea: not every example has the same size

A classroom has two quizzes. The first has two questions and an average error of 1.0; the second has six questions and average error 0.5. Simply averaging `1.0` and `0.5` would give 0.75, but it would mistakenly give the short quiz as much influence as the longer one.

A fair combined average weights each average by its number of questions:

`weightedAverage = (2×1.0 + 6×0.5) ÷ (2+6) = (2+3)÷8 = 0.625`.

## Replace questions with selected tokens

For supervised AI, one prompt/completion example can contain two **selected assistant target tokens**, while another contains six. If each example reports average selected-token cross-entropy, aggregate evaluation must weight those losses by the selected-token counts.

**Formula:** `meanSelectedLoss = Σ(exampleLoss × selectedTokens) ÷ Σ(selectedTokens)`.

The symbol `Σ` means add over all included examples. Both sums use **only** approved, selected assistant/EOS targets. Ignored prompt and padding positions do not belong in either denominator.

## Train and evaluation are different groups

An average computed on training examples answers whether the chosen objective was fitted on those examples. A held-out average measures a different set of source-isolated examples. Comparing one to the other can reveal possible overfitting, but it does not diagnose every cause or prove generalisation.

The existing Umicom supervised-evaluation service reports example counts, selected targets, token-weighted mean cross-entropy and top-one accuracy. An application must not label a denominator of all context positions as the selected-token count.

## Add perplexity carefully

Perplexity for next-token evaluation is commonly `exp(meanCrossEntropy)`. If mean loss is `ln(2)≈0.6931`, perplexity is about `2`. It is an interpretation of the stated probability model, **not** proof that the model is correct about every factual answer. Large exponential values can overflow floating-point storage, so the Framework records whether a finite perplexity is available.

## Practise

One example has three selected tokens and loss 0.6. Another has one selected token and loss 1.8. The weighted mean is `(3×0.6+1×1.8)÷4=3.6÷4=0.9`. The unweighted average of 1.2 would be misleading.

**Continue:** [held-out qualification](../10-native-ai/99-verify-restored-training-against-uninterrupted.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
