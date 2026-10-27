# Lesson 264 — Complete the native inference qualification capstone

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Bring correctness, numerical analysis, memory ownership and performance measurement together.

## 1. Understand the concept

A research prototype becomes credible when its claims match independently collected evidence. One test proving a hand-worked softmax value is a starting point. A complete inference qualification must also verify the last canonical tape row, per-layer hidden states, full vocabulary logits, deterministic sampled sequences, checkpoint-bound cache identity, finite-value rules, failure-atomic operations and the first and repeated context-rollover boundaries.

Optimisations that change model architecture—grouped-query attention, RoPE, cache quantisation and speculative sampling—require their own compatibility contracts. They are not hidden flags for the existing learned-absolute-position decoder. A sound comparison reports which features are implemented, which are mathematical studies, and which still require independently reviewed training or integration.

## 2. Work through the numbers

Consider a three-layer decoder with context capacity six. Evaluate prompts of length 1, 5 and 6, and generate enough tokens for two full-window rollovers. Compare the complete logits for every generated step, not just final token IDs. For the one-query arithmetic isolate, include head counts 1, 2 and 4 with channel counts divisible by those heads. Record each failure rejection with output sentinels.

A complete result distinguishes four statuses: arithmetic unit tests passed; canonical tape row parity passed; actual multi-layer session parity passed; Release full-session timings measured. Passing the first does not imply the remaining three.

## 3. Apply the concept to native model engineering

The Framework companion provides a bounded standalone C23 kernel and a canonical-tape comparison test that can be linked when the appropriate existing target is available. Its compile and unit-test success does not mean the stacked decoder has been switched to the new kernel. Training still uses the original differentiable attention operator. Accelerated whole-model generation remains unverified until integrated tests and timing comparisons support the claim.

A well-written evidence report includes exact source revision, compiler, CPU, checkpoint digest, inputs, seeds, numerical thresholds, observed failures, median/percentile latency and the independent oracle. The method remains valuable even if an optimisation proves slower.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 148](../11-maths-for-ai/148-separate-ttft-tpot-and-throughput.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** What can be claimed after a standalone unit test passes but the integrated decoder test has not run?

<details>
<summary>Reveal the worked answer</summary>
<p>The bounded unit-tested arithmetic cases and their rejection contracts passed in that configuration. Integrated multi-layer equivalence, safe rollover and real-model speed have not yet been demonstrated.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[263 — Measure prefill and decode performance separately](263-measure-prefill-and-decode-performance-separately.md) · [Course route](../../courses/llm-from-scratch/efficient-decoding-learning-path.html) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
