# Lesson 336 — Isolate independent inference conversations

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 and native Umicom Framework APIs  
**Prerequisite:** LLM Lesson 335; Mathematics Unit 204.

## Learning objective

Explain and test **isolate independent inference conversations** within the bounded, educational native Transformer architecture.

## Technical explanation and worked example

A pool may coordinate many independent sessions, but their mutable K/V histories must not merge. Each lease addresses one store with its own retained token count, appends and rollover counters. The shared pool accounts for memory, not for shared dialogue state. A cancellation of one request must release only its own reservation.

A tempting optimisation is to hand two conversations the same mutable cache because their first prompt tokens match. Without immutable-prefix snapshots, reference counting and copy-on-write rules, both conversations can append to the shared state and corrupt one another. Prefix sharing requires a separate design with explicit ownership; it does not follow automatically from a common checkpoint.

**Worked scenario.** Session A prefills `[11,12]`; session B prefills `[11,99]`. Each store reserves 512 bytes. A appends 13, while B appends 100. Inspecting A must show three retained tokens; B still has two until its own append. Releasing A must not change B's counters or cached projections.

**Native walkthrough.** Acquire two leases, operate on them independently, inspect each, then release in reverse order. Check `peakActiveSessions` against the number of simultaneous leases, not against all leases ever acquired.

## Practise

**Question:** If two requests share a checkpoint, can they automatically share mutable K/V rows?

<details><summary>Reveal the worked answer</summary>

No. Identical model identity is necessary but not sufficient; mutable per-request histories have separate lifetimes and need ownership isolation.

</details>

## Explore the mathematics

[Mathematics Unit 204](../11-maths-for-ai/204-write-a-failure-atomic-state-invariant.md) develops a related calculation. Distinguish stated design, tested library contracts and measured runtime evidence.

## Continue learning

[Previous lesson](335-rebuild-complete-kv-layers-at-learned-position-rollover.md) · [Next lesson](337-keep-model-updates-separate-from-active-cache-leases.md) · [Browser lesson](../../courses/llm-from-scratch/lessons/336-isolate-independent-inference-conversations.html)

*Service to Many Leads to Greatness.*
