# Mathematics for AI — Written Lessons

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

This is the reading map for the editable mathematics manuscripts. The complete [illustrated HTML course](../../courses/maths-for-ai/index.html) is available for every unit, with worked examples and accessible diagrams. Written Markdown companions are available for all twenty illustrated units, plus eighteen advanced Markdown-only units covering cross-entropy, low-rank adaptation, loss masking, supervised evaluation, checkpoint mathematics, reproducibility and evidence. The HTML course and its existing interactive diagrams remain available alongside the editable manuscripts.

## A route from arithmetic to model training

Begin with familiar numbers and notation. Vectors and matrices then supply the language needed for attention. Later units introduce probability, derivatives, numerical checks, training memory and evidence. You can read the HTML lessons without installing software.

## Units and companion formats

1. **Numbers, fractions and percentages** — [Written lesson](01-counting-ratios-and-percentages.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/01-counting-ratios-and-percentages.html).
2. **Variables and functions** — [Written lesson](02-variables-and-functions.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/02-variables-and-functions.html).
3. **Vectors and dot products** — [Written lesson](03-vectors-and-dot-products.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/03-vectors-and-dot-products.html).
4. **Matrices and shapes** — [Written lesson](04-matrices-and-shapes.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/04-matrices-and-shapes.html).
5. **Probability, softmax and loss** — [Written lesson](05-probability-softmax-and-loss.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/05-probability-softmax-and-loss.html).
6. **Derivatives and the chain rule** — [Written lesson](06-derivatives-and-chain-rule.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/06-derivatives-and-chain-rule.html).
7. **Angles and rotary position** — [Written lesson](07-angles-and-rotary-position.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/07-angles-and-rotary-position.html).
8. **Attention and KV work** — [Written lesson](08-attention-and-kv-work.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/08-attention-and-kv-work.html).
9. **Reading maths in code** — [Written lesson](09-reading-maths-in-code.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/09-reading-maths-in-code.html).
10. **Gradient descent and learning rates** — [Written lesson](10-gradient-descent-and-learning-rate.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/10-gradient-descent-and-learning-rate.html).
11. **Matrix weights and training** — [Written lesson](11-matrix-weights-and-training.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/11-matrix-weights-and-training.html).
12. **Finite differences and floating point** — [Written lesson](12-finite-differences-and-floating-point.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/12-finite-differences-and-floating-point.html).
13. **Attention scores and causal masks** — [Written lesson](13-attention-scores-and-causal-masks.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/13-attention-scores-and-causal-masks.html).
14. **Independent gradient checks** — [Written lesson](14-independent-gradient-checks.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/14-independent-gradient-checks.html).
15. **Repeatability and precision** — [Written lesson](15-repeatability-and-precision.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/15-repeatability-and-precision.html).
16. **Tensor shapes and indexing** — [Written lesson](16-tensor-shapes-and-indexing.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/16-tensor-shapes-and-indexing.html).
17. **Backpropagation from a small example** — [Written lesson](17-backpropagation-from-a-small-example.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/17-backpropagation-from-a-small-example.html).
18. **Memory budgets and rollback** — [Written lesson](18-memory-budgets-and-rollback.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/18-memory-budgets-and-rollback.html).
19. **Evidence thresholds and uncertainty** — [Written lesson](19-evidence-thresholds-and-uncertainty.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/19-evidence-thresholds-and-uncertainty.html) · [Video script](../../videos/scripts/maths-for-ai/19-evidence-thresholds-and-uncertainty.md).
20. **Matrix chain rule and computation graphs** — [Written lesson](20-matrix-chain-rule-and-computation-graphs.md) · [Illustrated HTML](../../courses/maths-for-ai/lessons/20-matrix-chain-rule-and-computation-graphs.html) · [Video script](../../videos/scripts/maths-for-ai/20-matrix-chain-rule-and-computation-graphs.md).

21. **Cross-entropy for native fine-tuning** — [Written lesson](21-cross-entropy-for-native-fine-tuning.md) · softmax, target-token probability and token-level training loss.
22. **Low-rank residuals and frozen models** — [Written lesson](22-low-rank-residuals-and-frozen-models.md) · matrix factorisation, frozen weights and trainable parameter counts.
23. **Projection adapters and parameter counts** — [Written lesson](23-projection-adapters-and-parameter-counts.md) · dimensions, parameter budgets and the cost of keeping a frozen base.
24. **Gradients through low-rank projections** — [Written lesson](24-gradients-through-low-rank-projections.md) · scalar chain rule, adapter updates and matrix-gradient shapes.
25. **Loss masks and next-token alignment** — [Written lesson](25-loss-masks-and-next-token-alignment.md) · teacher forcing, response-only targets, BOS/EOS and padding.
26. **Gradient flow through selected rows** — [Written lesson](26-gradient-flow-through-selected-rows.md) · a tape-owned row selector, mean cross-entropy and ignored-row gradients.
27. **Selected gradient paths in Transformers** — [Written lesson](27-selected-gradient-paths-in-transformers.md) · prompt context, masked logits and adapter gradient flow.
28. **Parameter budgets and evaluation loss** — [Written lesson](28-parameter-budgets-and-evaluation-loss.md) · trainable matrix counts, frozen weights and held-out cross-entropy.
29. **Token-weighted loss** — [Written lesson](29-token-weighted-loss.md) · average losses by selected target counts.
30. **Accuracy and perplexity** — [Written lesson](30-accuracy-and-perplexity.md) · evaluate held-out targets honestly.
31. **Permutations without replacement** — [Written lesson](31-permutations-without-replacement.md) · seeded deterministic training order.
32. **Integer bounds and evidence identities** — [Written lesson](32-integer-bounds-and-evidence-identities.md) · source and model digest contracts.
33. **Epoch cursors and integer invariants** — [Written lesson](33-epoch-cursors-and-integer-invariants.md) · predict completed steps after restart.
34. **Hashes, content identity and signatures** — [Written lesson](34-hashes-content-identity-and-signatures.md) · distinguish exact bytes from authority.
35. **SGD, AdamW and restart state** — [Written lesson](35-sgd-and-adamw-state-for-restarts.md) · learn why moment tensors change continuation.
36. **Token-weighted held-out averages** — [Written lesson](36-token-weighted-held-out-averages.md) · combine unequal-length target sequences.
37. **Quality thresholds and trade-offs** — [Written lesson](37-quality-thresholds-and-tradeoffs.md) · loss and accuracy acceptance.
38. **Binary layouts and safe capacity** — [Written lesson](38-binary-layouts-and-safe-capacity.md) · little-endian values, checked sizes and digests.

## Reading mathematics alongside the native LLM course

The introductory units explain calculations used later in the C23-based lessons. [Train a frozen decoder logit adapter](../10-native-ai/train-a-frozen-decoder-logit-adapter.md) connects Units 21–22 to the real native decoder without duplicating its implementation. [Review dataset leakage](../10-native-ai/check-reviewed-corpus-for-data-leakage.md) explains a separate source-integrity gate. The [low-rank fine-tuning lesson](../10-native-ai/train-a-frozen-projection-with-low-rank-adapters.md) applies shapes, gradients and memory ownership to one reusable Framework component. [Transformer projection adaptation](../10-native-ai/adapt-attention-and-feed-forward-projections.md) extends that study from one dense projection to the actual pre-layer-normalised block. [Assistant-response training windows](../10-native-ai/prepare-assistant-response-training-windows.md) and [selected-token cross-entropy](../10-native-ai/selected-token-cross-entropy-in-c23.md) connect the mathematics to the original byte tokenizer, frozen decoder and native training tape. [Projection-level response-only adaptation](../10-native-ai/train-transformer-projections-with-response-only-loss.md) and [held-out adapter evaluation](../10-native-ai/evaluate-frozen-decoder-and-adapters.md) connect Units 27–28 to one Framework-owned training laboratory. Continue with [native inference and cache semantics](../10-native-ai/63-qualify-kv-cached-nucleus-generation.md), [canonical-decoder parity](../10-native-ai/71-qualify-canonical-decoder-kv-parity.md) and [unpadded prefix streaming](../10-native-ai/73-stream-growing-prefix-generation-in-c23.md), or use [Lesson 93](../10-native-ai/93-check-real-tape-evidence.md) for numerical acceptance evidence and [Lesson 94](../10-native-ai/94-plan-a-fused-rotary-tape-operator.md) for gradient propagation.

For a complete [native checkpoint and restart study route](../10-native-ai/native-checkpoint-and-resume-learning-path.md), continue from Unit 33 into the optional C23 laboratory.

The [formula dictionary](../../courses/maths-for-ai/formulas.html) supplies further definitions. The classroom examples are illustrative mathematics, not investment advice or a source of real transaction statistics.
