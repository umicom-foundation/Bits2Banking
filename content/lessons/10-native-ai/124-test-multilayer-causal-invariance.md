# Test causal invariance across every Transformer layer

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## A future token must not affect an earlier logit

A decoder-only language model predicts from left to right. The causal mask prevents an earlier token position from attending to a later position. But verifying the mask in one attention head is not sufficient: a composition error could reintroduce future information through another layer, residual connection or wrongly indexed representation.

Consider two four-token contexts: `[A,B,C,D]` and `[A,B,X,Y]`. They share the first two tokens. For a correctly implemented causal decoder, the logits at positions 0 and 1 must agree within the justified numerical tolerance. The logits at later positions may differ.

The new Framework regression executes a real three-layer stack twice with those two contexts. It compares all vocabulary logits for the shared earlier positions. This establishes an observable model-level causality property, not merely a unit test of an isolated attention mask.

## Why this property survives composition

By induction: embeddings at position `t` use only token `t` and the position index. If every block's output at `t` depends only on inputs at positions `<=t`, then a second block cannot introduce a dependency on `>t`. Residual addition and per-row normalisation preserve that restriction when implemented over the correct row boundaries.

There is a caveat: concatenating unrelated documents without resetting the sequence boundary makes earlier text from the previous document visible. A triangular causal mask alone does not implement document isolation.

## Practice

Which rows must match for `[M,N,P,Q]` versus `[M,N,R,S]`? Why does comparing only the next chosen token miss some mistakes?

<details><summary>Worked answer</summary>

Rows 0 and 1 should have matching logits for *every* vocabulary ID. Two incorrect logit distributions might still choose the same highest-scoring token, so token-ID equality alone is weaker than full-logit comparison.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
