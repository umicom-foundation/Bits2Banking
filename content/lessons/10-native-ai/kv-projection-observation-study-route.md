# Native K/V projection observation — written learning path

**Sammy Hegab · Umicom Foundation**

This path continues after [Lesson 204](204-define-the-acceptance-gate-for-true-incremental-inference.md). Every numbered lesson has an accompanying browser HTML page. None of the exercises require private banking data or access to a production model.

- [Lesson 205: Observe keys and values in the real Transformer](205-observe-keys-and-values-in-the-real-transformer.md) · [HTML](../../courses/llm-from-scratch/lessons/205-observe-keys-and-values-in-the-real-transformer.html)
- [Lesson 206: Trace projections without duplicating attention mathematics](206-trace-projections-without-duplicating-attention.md) · [HTML](../../courses/llm-from-scratch/lessons/206-trace-projections-without-duplicating-attention.html)
- [Lesson 207: Compare projection-trace logits with canonical decoder logits](207-compare-projection-trace-and-canonical-logits.md) · [HTML](../../courses/llm-from-scratch/lessons/207-compare-projection-trace-and-canonical-logits.html)
- [Lesson 208: Bind observed K/V rows to a frozen checkpoint](208-bind-the-capture-to-a-frozen-checkpoint.md) · [HTML](../../courses/llm-from-scratch/lessons/208-bind-the-capture-to-a-frozen-checkpoint.html)
- [Lesson 209: Prefill real K/V rows from an unpadded prompt](209-prefill-real-kv-rows-from-an-unpadded-prompt.md) · [HTML](../../courses/llm-from-scratch/lessons/209-prefill-real-kv-rows-from-an-unpadded-prompt.html)
- [Lesson 210: Verify prior K/V rows before appending another token](210-verify-existing-rows-before-appending.md) · [HTML](../../courses/llm-from-scratch/lessons/210-verify-existing-rows-before-appending.html)
- [Lesson 211: Rebuild every layer after learned-position rollover](211-rebuild-all-layers-after-absolute-position-rollover.md) · [HTML](../../courses/llm-from-scratch/lessons/211-rebuild-all-layers-after-absolute-position-rollover.html)
- [Lesson 212: Distinguish accepted K/V rows from actual decoder work](212-distinguish-stored-rows-from-computed-rows.md) · [HTML](../../courses/llm-from-scratch/lessons/212-distinguish-stored-rows-from-computed-rows.html)
- [Lesson 213: Test capture error atomicity and tape memory](213-test-capture-error-atomicity-and-memory.md) · [HTML](../../courses/llm-from-scratch/lessons/213-test-capture-error-atomicity-and-memory.html)
- [Lesson 214: Qualify real projection capture across multiple layers](214-qualify-capture-across-multiple-layers.md) · [HTML](../../courses/llm-from-scratch/lessons/214-qualify-capture-across-multiple-layers.html)
- [Lesson 215: Understand causal stability and evicted history](215-interpret-causal-stability-and-evicted-history.md) · [HTML](../../courses/llm-from-scratch/lessons/215-interpret-causal-stability-and-evicted-history.html)
- [Lesson 216: Design the next incremental-attention acceptance reference](216-design-the-next-incremental-attention-reference.md) · [HTML](../../courses/llm-from-scratch/lessons/216-design-the-next-incremental-attention-reference.html)

Study the [browser learning path](../../courses/llm-from-scratch/kv-projection-learning-path.html) and [supporting mathematics](../11-maths-for-ai/projection-trace-mathematics.md). Every native operator remains in Umicom Framework.
