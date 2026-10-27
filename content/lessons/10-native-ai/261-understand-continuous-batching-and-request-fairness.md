# Lesson 261 — Understand continuous batching and request fairness

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Explain latency and throughput trade-offs for several concurrent prompts.

## 1. Understand the concept

A single-user native laboratory processes one session at a time. A serving system may have hundreds of sessions with different prompt lengths, token limits and KV occupancy. **Continuous batching** schedules active decode steps together and admits or retires sessions as they progress. Unlike a fixed batch that waits for every request to finish, a continuous scheduler can reuse freed capacity.

Batching improves hardware utilisation only when the batching overhead and memory bandwidth permit it. A heavy prefill can delay short decode jobs; an unlimited long-context request can exhaust the cache budget. Fairness and admission controls therefore matter to perceived responsiveness as much as raw tokens per second.

## 2. Work through the numbers

Imagine request A needs ten output tokens, request B needs three, and request C needs six. A scheduler that holds a static batch until all three finish wastes B's slot after its third token. A continuous scheduler can admit request D when B completes, subject to its memory and priority constraints.

A simple fairness indicator is queueing delay before the first decode step. Compare that delay with time-to-first-token and sustained decode-token latency for short and long requests. Report percentiles: an average alone can hide starvation.

## 3. Apply the concept to native model engineering

A future native scheduler would need bounded per-session state, cancellation, quotas, checkpoint-bound cache storage and rules for not interleaving unsafe tape operations. The existing Umicom educational session is caller-serialised; it must not simply be driven concurrently from multiple threads without a documented synchronisation contract.

This lesson concerns model-serving architecture and is not a claim that a production continuous-batching runtime has been added to the Framework.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 148](../11-maths-for-ai/148-separate-ttft-tpot-and-throughput.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** Why might a faster kernel fail to improve a short request’s time-to-first-token during heavy serving load?

<details>
<summary>Reveal the worked answer</summary>
<p>Queueing and prefill scheduling can dominate TTFT; accelerating the decode kernel does not necessarily reduce admission delay.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[260 — Explain speculative decoding and verification](260-explain-speculative-decoding-and-verification.md) · [262 — Preserve checkpoint and cache portability](262-preserve-checkpoint-and-cache-portability.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
