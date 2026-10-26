# Lesson 214 — Qualify real projection capture across multiple layers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Design tests that reveal incorrect layer ordering or a hidden upper-layer dependence on future tokens.

## Why this matters

Every layer has separate projection weights and receives a different intermediate state. Therefore a one-layer capture test cannot establish that a two- or six-layer implementation uses the correct offsets and tensor lifetimes. The qualification should vary layer count, context length, head count and seeded initialisation.

Within each case, first compare the traced logits to the canonical decoder. Next test fixed-position growth: capture prefix K/V, add a token and independently obtain the longer canonical trace. Check every stored earlier row in every layer. Finally cross the first rollover and compare the returned logits with a full reference on the shifted context.

A good regression also keeps checkpoint bytes unchanged and tests wrong layer indices, wrong capacities and overlapping output buffers. These conditions are distinct; passing only token-sampling parity does not prove that stored per-layer tensors have the correct values.

## Work through the numbers and tensor shapes

Let `L=3`, `C=4`, `D=8` where D means projected channels. The source row at layer 2, token 3 begins at offset `(2×4+3)×8=88`. A storage implementation that mistakenly used `layer×D + token×C` would return a plausible-looking float slice from the wrong location.

The intended output of a full observation contains `L×C×D = 96` key floats and another 96 value floats. Test cases should calculate these counts independently before allocating buffers.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** Why is matching only the final vocabulary logits inadequate to prove that every layer's stored K/V rows were copied to the correct offsets?

<details><summary>Reveal the worked explanation</summary>

The logits are computed inside the original model before the stored K/V are used. An offset error in the copy may leave logits unchanged. Separate K/V row comparisons are therefore essential.

</details>

## Continue studying

[Previous lesson](213-test-capture-error-atomicity-and-memory.md) · [Next lesson](215-interpret-causal-stability-and-evicted-history.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/214-qualify-capture-across-multiple-layers.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
