# Lesson 335 — Rebuild complete K/V layers at learned-position rollover

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 and native Umicom Framework APIs  
**Prerequisite:** LLM Lesson 334; Mathematics Unit 203.

## Learning objective

Explain and test **rebuild complete k/v layers at learned-position rollover** within the bounded, educational native Transformer architecture.

## Technical explanation and worked example

A full context is an algorithmic boundary, not just a full allocation. When the oldest token is evicted, surviving tokens shift to different learned absolute positions. At upper Transformer layers, their hidden states also depend on the earlier context. A ring-buffer shift of historical K/V rows is therefore not generally equivalent to a canonical recomputation.

The existing store's `ReplaceRolled` accepts a specifically shifted token-ID sequence only when the cache is already full. It validates all the new K/V projections and replaces the **entire** multi-layer tensor together. The pool wraps this exact operation; it must not invent a shift-only shortcut.

**Worked scenario.** Context `[40,41,42,43]` rolls over to `[41,42,43,44]`. The caller supplies full new key and value tensors with `layers × context × channels` floats each. A proposed `[99,42,43,44]` must fail, even though its length is four. The legitimate shift increments `fullWindowRebuilds` once.

**Native walkthrough.** Use the canonical stacked decoder's projection trace to produce all new projections for the shifted context. Call pool `ReplaceRolled` and compare every K/V row. An isolated exercise may use synthetic floats to test storage but cannot establish model-logit parity.

## Practise

**Question:** Why is the first surviving token not safe to reuse after rollover?

<details><summary>Reveal the worked answer</summary>

Its learned absolute position changes, and its upper-layer representation may depend on the evicted prefix.

</details>

## Explore the mathematics

[Mathematics Unit 203](../11-maths-for-ai/203-index-layer-major-stored-projections.md) develops a related calculation. Distinguish stated design, tested library contracts and measured runtime evidence.

## Continue learning

[Previous lesson](334-prefill-a-prompt-and-append-without-moving-its-positions.md) · [Next lesson](336-isolate-independent-inference-conversations.md) · [Browser lesson](../../courses/llm-from-scratch/lessons/335-rebuild-complete-kv-layers-at-learned-position-rollover.html)

*Service to Many Leads to Greatness.*
