# Incremental Transformer inference — native C23 reading route

**Sammy Hegab · Umicom Foundation**

Begin with [the existing KV projection lesson](216-design-the-next-incremental-attention-reference.md). Continue with [Lesson 217](217-define-the-incremental-layer-step-contract.md) and read through [Lesson 232](232-run-the-qualification-matrix-before-optimising.md). The [browser course](../../courses/llm-from-scratch/incremental-attention-learning-path.html) provides full HTML companions and next/previous navigation for all sixteen lessons.

The sequence teaches the distinction between immutable weights, new-token projections, cached K/V, causal softmax, a row selector, residual paths and learned-position rollover. The final acceptance exercise checks every vocabulary logit and all newly proposed K/V rows; it must run against the actual Framework's native tape.

## Study procedure

1. Identify the canonical checkpoint and public C23 APIs.
2. Work the [mathematics route](../11-maths-for-ai/incremental-inference-mathematics.md) by hand.
3. Run the real model's native tests before interpreting logged counters.
4. Explain why one-token projection reuse does not eliminate all attention-query work.
5. Compare canonical full-context generation and opt-in growing-prefix generation under identical model and sampling settings.

No private training data is required for these lessons. Training-data rights and provenance remain separate review decisions. None of these exercises constitutes evidence of a production-scale LLM.
