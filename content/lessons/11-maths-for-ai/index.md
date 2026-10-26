# Mathematics for AI — Written Lessons

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

This is the reading map for the editable mathematics manuscripts. The complete [illustrated HTML course](../../courses/maths-for-ai/index.html) is available for every unit, with worked examples and accessible diagrams. Written Markdown companions are available for all twenty illustrated units, plus advanced Markdown-only units through Unit 104 covering cross-entropy, low-rank adaptation, loss masking, supervised evaluation, checkpoint mathematics, reproducibility and evidence. The HTML course and its existing interactive diagrams remain available alongside the editable manuscripts.

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


## Further mathematics — Units 39–78

The original illustrated course through [Unit 20](../../courses/maths-for-ai/index.html) is preserved. All subsequent units have editable Markdown and browser-friendly HTML counterparts in the [advanced mathematics catalogue](../../courses/maths-for-ai/advanced-units.html). Each entry below links to both views.

39. **Counting neural network parameters** — [Written lesson](39-model-parameter-counts-and-shapes.md) · [HTML companion](../../courses/maths-for-ai/lessons/39-model-parameter-counts-and-shapes.html).
40. **The arithmetic of low-rank adapters** — [Written lesson](40-low-rank-factorisation-counts.md) · [HTML companion](../../courses/maths-for-ai/lessons/40-low-rank-factorisation-counts.html).
41. **Compute KV cache memory** — [Written lesson](41-attention-cache-and-memory-units.md) · [HTML companion](../../courses/maths-for-ai/lessons/41-attention-cache-and-memory-units.html).
42. **Working out optimiser storage** — [Written lesson](42-moments-gradients-and-storage.md) · [HTML companion](../../courses/maths-for-ai/lessons/42-moments-gradients-and-storage.html).
43. **Why attention work grows quadratically** — [Written lesson](43-attention-score-matrix-growth.md) · [HTML companion](../../courses/maths-for-ai/lessons/43-attention-score-matrix-growth.html).
44. **Convert timing observations into rates** — [Written lesson](44-training-throughput-and-uncertainty.md) · [HTML companion](../../courses/maths-for-ai/lessons/44-training-throughput-and-uncertainty.html).
45. **Comparing models with multiple objectives** — [Written lesson](45-loss-accuracy-and-objective-tradeoffs.md) · [HTML companion](../../courses/maths-for-ai/lessons/45-loss-accuracy-and-objective-tradeoffs.html).
46. **Overflow-safe multiplication and addition** — [Written lesson](46-safe-capacity-arithmetic.md) · [HTML companion](../../courses/maths-for-ai/lessons/46-safe-capacity-arithmetic.html).
47. **Count parameters in several Transformer layers** — [Written lesson](47-count-parameters-in-transformer-layers.md) · [HTML companion](../../courses/maths-for-ai/lessons/47-count-parameters-in-transformer-layers.html).
48. **Track tensor shapes from embeddings to logits** — [Written lesson](48-track-tensor-shapes-through-the-stack.md) · [HTML companion](../../courses/maths-for-ai/lessons/48-track-tensor-shapes-through-the-stack.html).
49. **Prove that future tokens do not change earlier outputs** — [Written lesson](49-prove-causal-prefix-independence.md) · [HTML companion](../../courses/maths-for-ai/lessons/49-prove-causal-prefix-independence.html).
50. **Combine cross-entropy for selected answer tokens** — [Written lesson](50-combine-selected-token-cross-entropies.md) · [HTML companion](../../courses/maths-for-ai/lessons/50-combine-selected-token-cross-entropies.html).
51. **Understand deterministic training permutations** — [Written lesson](51-understand-deterministic-training-permutations.md) · [HTML companion](../../courses/maths-for-ai/lessons/51-understand-deterministic-training-permutations.html).
52. **Measure a portable stacked-model checkpoint** — [Written lesson](52-measure-portable-stacked-checkpoint-sizes.md) · [HTML companion](../../courses/maths-for-ai/lessons/52-measure-portable-stacked-checkpoint-sizes.html).
53. **Compare training loss with held-out loss** — [Written lesson](53-compare-training-and-heldout-loss.md) · [HTML companion](../../courses/maths-for-ai/lessons/53-compare-training-and-heldout-loss.html).
54. **Estimate full-context generation work across layers** — [Written lesson](54-estimate-full-context-generation-work.md) · [HTML companion](../../courses/maths-for-ai/lessons/54-estimate-full-context-generation-work.html).
55. **Logit rankings and the most likely token** — [Written lesson](55-logit-rankings-and-the-most-likely-token.md) · [HTML companion](../../courses/maths-for-ai/lessons/55-logit-rankings-and-the-most-likely-token.html).
56. **Temperature and probability concentration** — [Written lesson](56-temperature-and-probability-concentration.md) · [HTML companion](../../courses/maths-for-ai/lessons/56-temperature-and-probability-concentration.html).
57. **Top-K versus top-p nucleus membership** — [Written lesson](57-topk-versus-topp-nucleus-membership.md) · [HTML companion](../../courses/maths-for-ai/lessons/57-topk-versus-topp-nucleus-membership.html).
58. **Left-padding and token position indices** — [Written lesson](58-left-padding-and-token-position-indices.md) · [HTML companion](../../courses/maths-for-ai/lessons/58-left-padding-and-token-position-indices.html).
59. **Count full-context token-layer work** — [Written lesson](59-count-full-context-token-layer-work.md) · [HTML companion](../../courses/maths-for-ai/lessons/59-count-full-context-token-layer-work.html).
60. **Weighted selected-token loss and perplexity** — [Written lesson](60-weighted-selected-token-loss-and-perplexity.md) · [HTML companion](../../courses/maths-for-ai/lessons/60-weighted-selected-token-loss-and-perplexity.html).
61. **Hash ordered tokens independently of the CPU word size** — [Written lesson](61-hash-ordered-tokens-portably.md) · [HTML companion](../../courses/maths-for-ai/lessons/61-hash-ordered-tokens-portably.html).
62. **Absolute loss thresholds versus accuracy thresholds** — [Written lesson](62-absolute-loss-thresholds-versus-accuracy.md) · [HTML companion](../../courses/maths-for-ai/lessons/62-absolute-loss-thresholds-versus-accuracy.html).
63. **Prefill and decoding work, counted carefully** — [Written lesson](63-prefill-and-decoding-row-arithmetic.md) · [HTML companion](../../courses/maths-for-ai/lessons/63-prefill-and-decoding-row-arithmetic.html).
64. **Why the attention score table grows quadratically** — [Written lesson](64-quadratic-attention-and-causal-mask.md) · [HTML companion](../../courses/maths-for-ai/lessons/64-quadratic-attention-and-causal-mask.html).
65. **Distinguish saved activations from stored weights** — [Written lesson](65-activation-memory-is-not-parameter-memory.md) · [HTML companion](../../courses/maths-for-ai/lessons/65-activation-memory-is-not-parameter-memory.html).
66. **Understand quantisation as a controlled numerical approximation** — [Written lesson](66-quantisation-error-and-the-accuracy-budget.md) · [HTML companion](../../courses/maths-for-ai/lessons/66-quantisation-error-and-the-accuracy-budget.html).
67. **Calculate tokens per second without hiding prefill** — [Written lesson](67-throughput-first-token-and-decode-time.md) · [HTML companion](../../courses/maths-for-ai/lessons/67-throughput-first-token-and-decode-time.html).
68. **Combine numerical gates without confusing their meanings** — [Written lesson](68-loss-thresholds-and-model-admission.md) · [HTML companion](../../courses/maths-for-ai/lessons/68-loss-thresholds-and-model-admission.html).
69. **Count UTF-8 bytes separately from displayed characters** — [Written lesson](69-utf8-byte-sequences-and-character-counts.md) · [HTML companion](../../courses/maths-for-ai/lessons/69-utf8-byte-sequences-and-character-counts.html).
70. **Calculate capacity for streamed Unicode scalars** — [Written lesson](70-safe-buffer-capacity-for-streamed-utf8.md) · [HTML companion](../../courses/maths-for-ai/lessons/70-safe-buffer-capacity-for-streamed-utf8.html).
71. **Count Token-Layer Rows in a Proposed Cache** — [Written lesson](71-count-token-layer-rows-in-a-cache-plan.md) · [HTML companion](../../courses/maths-for-ai/lessons/71-count-token-layer-rows-in-a-cache-plan.html).
72. **Calculate What a Causal Prefix Can and Cannot See** — [Written lesson](72-calculate-causal-prefix-invariance.md) · [HTML companion](../../courses/maths-for-ai/lessons/72-calculate-causal-prefix-invariance.html).
73. **Separate Logit Agreement from Token Agreement** — [Written lesson](73-separate-logit-parity-from-token-agreement.md) · [HTML companion](../../courses/maths-for-ai/lessons/73-separate-logit-parity-from-token-agreement.html).
74. **Keep Absolute Token Positions Distinct from Ring Slots** — [Written lesson](74-keep-absolute-positions-through-rolling-windows.md) · [HTML companion](../../courses/maths-for-ai/lessons/74-keep-absolute-positions-through-rolling-windows.html).
75. **Budget Raw Key/Value Storage Across Transformer Layers** — [Written lesson](75-budget-key-value-memory-across-layers.md) · [HTML companion](../../courses/maths-for-ai/lessons/75-budget-key-value-memory-across-layers.html).
76. **Measure Inference Timing Without Confusing Workload and Speed** — [Written lesson](76-measure-time-and-uncertainty-honestly.md) · [HTML companion](../../courses/maths-for-ai/lessons/76-measure-time-and-uncertainty-honestly.html).
77. **Calculate Complete HTML and Markdown Course Coverage** — [Written lesson](77-calculate-html-and-markdown-coverage.md) · [HTML companion](../../courses/maths-for-ai/lessons/77-calculate-html-and-markdown-coverage.html).
78. **Calculate Source-Preserving HTML Output Capacity** — [Written lesson](78-calculate-source-preserving-html-output-capacity.md) · [HTML companion](../../courses/maths-for-ai/lessons/78-calculate-source-preserving-html-output-capacity.html).

79. **Read The Right Logit Row** — [Written lesson](79-read-the-right-logit-row.md) · [Browser HTML](../../courses/maths-for-ai/lessons/79-read-the-right-logit-row.html).
80. **Causal Suffix Invariance** — [Written lesson](80-causal-suffix-invariance.md) · [Browser HTML](../../courses/maths-for-ai/lessons/80-causal-suffix-invariance.html).
81. **Pending Samples And Append Counts** — [Written lesson](81-pending-samples-and-append-counts.md) · [Browser HTML](../../courses/maths-for-ai/lessons/81-pending-samples-and-append-counts.html).
82. **Calculate Real Token Layer Work** — [Written lesson](82-calculate-real-token-layer-work.md) · [Browser HTML](../../courses/maths-for-ai/lessons/82-calculate-real-token-layer-work.html).
83. **Compare Actual And Planned Cache Work** — [Written lesson](83-compare-actual-and-planned-cache-work.md) · [Browser HTML](../../courses/maths-for-ai/lessons/83-compare-actual-and-planned-cache-work.html).
84. **Count Evictions After Context Fills** — [Written lesson](84-count-evictions-after-context-fills.md) · [Browser HTML](../../courses/maths-for-ai/lessons/84-count-evictions-after-context-fills.html).
85. **Read Content Hash Identities** — [Written lesson](85-read-content-hash-identities.md) · [Browser HTML](../../courses/maths-for-ai/lessons/85-read-content-hash-identities.html).
86. **Budget Key Value Memory** — [Written lesson](86-budget-key-value-memory.md) · [Browser HTML](../../courses/maths-for-ai/lessons/86-budget-key-value-memory.html).
87. **Choose A Numerical Parity Tolerance** — [Written lesson](87-choose-a-numerical-parity-tolerance.md) · [Browser HTML](../../courses/maths-for-ai/lessons/87-choose-a-numerical-parity-tolerance.html).
88. **Interpret Nucleus Membership** — [Written lesson](88-interpret-nucleus-membership.md) · [Browser HTML](../../courses/maths-for-ai/lessons/88-interpret-nucleus-membership.html).
89. **Track UTF-8 As Bytes** — [Written lesson](89-track-utf8-as-bytes.md) · [Browser HTML](../../courses/maths-for-ai/lessons/89-track-utf8-as-bytes.html).
90. **Design Independent Regression Evidence** — [Written lesson](90-design-independent-regression-evidence.md) · [Browser HTML](../../courses/maths-for-ai/lessons/90-design-independent-regression-evidence.html).

91. **Calculate a Three-Dimensional K/V Shape** — [Written lesson](91-calculate-a-three-dimensional-k-v-shape.md) · [HTML companion](../../courses/maths-for-ai/lessons/91-calculate-a-three-dimensional-k-v-shape.html).
92. **Count Appends and Full Rebuilds** — [Written lesson](92-count-appends-and-full-rebuilds.md) · [HTML companion](../../courses/maths-for-ai/lessons/92-count-appends-and-full-rebuilds.html).
93. **Verify a One-Step Rolling Sequence** — [Written lesson](93-verify-a-one-step-rolling-sequence.md) · [HTML companion](../../courses/maths-for-ai/lessons/93-verify-a-one-step-rolling-sequence.html).
94. **Convert K/V Floats into Memory Bytes** — [Written lesson](94-convert-k-v-floats-into-memory-bytes.md) · [HTML companion](../../courses/maths-for-ai/lessons/94-convert-k-v-floats-into-memory-bytes.html).
95. **Reject Unsafe Capacity Multiplication** — [Written lesson](95-reject-unsafe-capacity-multiplication.md) · [HTML companion](../../courses/maths-for-ai/lessons/95-reject-unsafe-capacity-multiplication.html).
96. **Distinguish Finite Values From NaN** — [Written lesson](96-distinguish-finite-values-from-nan.md) · [HTML companion](../../courses/maths-for-ai/lessons/96-distinguish-finite-values-from-nan.html).
97. **Separate SHA-256 Content Identity From Trust** — [Written lesson](97-separate-sha-256-content-identity-from-trust.md) · [HTML companion](../../courses/maths-for-ai/lessons/97-separate-sha-256-content-identity-from-trust.html).
98. **Locate a Row in Layer-Major Storage** — [Written lesson](98-locate-a-row-in-layer-major-storage.md) · [HTML companion](../../courses/maths-for-ai/lessons/98-locate-a-row-in-layer-major-storage.html).
99. **Compare Predicted and Observed Row Counts** — [Written lesson](99-compare-predicted-and-observed-row-counts.md) · [HTML companion](../../courses/maths-for-ai/lessons/99-compare-predicted-and-observed-row-counts.html).
100. **Calculate Failure-Atomic Replacement** — [Written lesson](100-calculate-failure-atomic-replacement.md) · [HTML companion](../../courses/maths-for-ai/lessons/100-calculate-failure-atomic-replacement.html).
101. **Distinguish Attention Scores From Values** — [Written lesson](101-distinguish-attention-scores-from-values.md) · [HTML companion](../../courses/maths-for-ai/lessons/101-distinguish-attention-scores-from-values.html).
102. **Keep Softmax Numerically Stable** — [Written lesson](102-keep-softmax-numerically-stable.md) · [HTML companion](../../courses/maths-for-ai/lessons/102-keep-softmax-numerically-stable.html).
103. **Compare Full-Context and Prefix Work** — [Written lesson](103-compare-full-context-and-prefix-work.md) · [HTML companion](../../courses/maths-for-ai/lessons/103-compare-full-context-and-prefix-work.html).
104. **Distinguish Latency From Workload** — [Written lesson](104-distinguish-latency-from-workload.md) · [HTML companion](../../courses/maths-for-ai/lessons/104-distinguish-latency-from-workload.html).

## Reading mathematics alongside the native LLM course

The introductory units explain calculations used later in the C23-based lessons. [Train a frozen decoder logit adapter](../10-native-ai/train-a-frozen-decoder-logit-adapter.md) connects Units 21–22 to the real native decoder without duplicating its implementation. [Review dataset leakage](../10-native-ai/check-reviewed-corpus-for-data-leakage.md) explains a separate source-integrity gate. The [low-rank fine-tuning lesson](../10-native-ai/train-a-frozen-projection-with-low-rank-adapters.md) applies shapes, gradients and memory ownership to one reusable Framework component. [Transformer projection adaptation](../10-native-ai/adapt-attention-and-feed-forward-projections.md) extends that study from one dense projection to the actual pre-layer-normalised block. [Assistant-response training windows](../10-native-ai/prepare-assistant-response-training-windows.md) and [selected-token cross-entropy](../10-native-ai/selected-token-cross-entropy-in-c23.md) connect the mathematics to the original byte tokenizer, frozen decoder and native training tape. [Projection-level response-only adaptation](../10-native-ai/train-transformer-projections-with-response-only-loss.md) and [held-out adapter evaluation](../10-native-ai/evaluate-frozen-decoder-and-adapters.md) connect Units 27–28 to one Framework-owned training laboratory. Continue with [native inference and cache semantics](../10-native-ai/63-qualify-kv-cached-nucleus-generation.md), [canonical-decoder parity](../10-native-ai/71-qualify-canonical-decoder-kv-parity.md) and [unpadded prefix streaming](../10-native-ai/73-stream-growing-prefix-generation-in-c23.md), or use [Lesson 93](../10-native-ai/93-check-real-tape-evidence.md) for numerical acceptance evidence and [Lesson 94](../10-native-ai/94-plan-a-fused-rotary-tape-operator.md) for gradient propagation.

For a complete [native checkpoint and restart study route](../10-native-ai/native-checkpoint-and-resume-learning-path.md), continue from Unit 33 into the optional C23 laboratory.

The [formula dictionary](../../courses/maths-for-ai/formulas.html) supplies further definitions. The classroom examples are illustrative mathematics, not investment advice or a source of real transaction statistics.
