# Lesson 274 — Verify greedy and sampled sequence parity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Distinguish deterministic token generation from full numerical agreement.

## 1. Concept and motivation

Greedy decoding chooses the highest-scoring token. Nucleus sampling first constructs a probability distribution over a constrained candidate set and then uses a pseudorandom stream. For reproducible comparison, reference and candidate must use the same checkpoint, exact prompt, seed, temperature, top-K and top-p. Their random generators must advance in the same way, even when the candidate implementation is faster.

## 2. Worked example

With a prompt of one token and a context of six, eight generated tokens trigger both prefix growth and repeated rollover. Compare the emitted eight-token arrays exactly using the same sampler; then separately compare intermediate logits to detect hidden differences that did not yet affect token choice.

## 3. Native Framework implementation and evidence

Use `UmiAiTrainingStackedPrefixGenerateNucleus` as the independent full-context oracle and compare against the incremental session. Test both a greedy policy and a nontrivial sampled policy; record explicit seeds instead of relying on process-time initialisation.

## 4. Mathematical companion

Read [Mathematics Unit 159 — Distinguish logit and token agreement](../11-maths-for-ai/159-distinguish-logit-and-token-agreement.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Why can two implementations match greedy output but disagree with top-p sampling?

<details>
<summary>Reveal the worked answer</summary>

Near-threshold probability differences can change nucleus membership or cumulative weights without changing the largest logit.

</details>

## 6. Interpretation

Equal sampled tokens are a useful end-to-end smoke test, not a complete numerical proof.

## Continue learning

[273 — Reject stale checkpoint-bound caches](273-reject-stale-checkpoint-caches.md) · [275 — Set finite-precision acceptance thresholds](275-set-finite-precision-acceptance-thresholds.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
