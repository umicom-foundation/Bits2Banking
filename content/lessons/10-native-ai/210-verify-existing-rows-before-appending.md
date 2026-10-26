# Lesson 210 — Verify prior K/V rows before appending another token

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Check the invariant that fixed-position prefix history must remain stable.

## Why this matters

When one token is appended to a prefix shorter than the context limit, the earlier tokens keep their absolute positions. Under causal attention, none of their already-computed hidden states should depend on the new future token. This gives a checkable invariant: recomputing the longer prefix must reproduce **all earlier K and V components in every layer**.

The capture first performs another canonical full-context trace. It reads each prior key/value row from the store, compares it against the corresponding newly observed row, and refuses the append if any absolute difference exceeds a predeclared tolerance or any value is non-finite. Only after those comparisons pass does the store accept the new token's K/V row.

This makes the storage owner more trustworthy, but does not mean the implementation is yet reusing K/V **during** attention. The fresh reference pass still computes everything. The store's counters measure admitted rows, whereas the capture's counters measure complete reference evaluations.

## Work through the numbers and tensor shapes

For `C=4`, `L=2` and a two-token prompt, prefill uses one full reference evaluation: `4 × 2 = 8` token-layer computations and accepts `2 × 2 = 4` stored rows. Appending token three requires another eight computed token-layer rows but admits only two additional K/V rows. After appending token four, total actual computation is `3 × 8 = 24` token-layer rows, while cumulative admitted rows are `4+2+2 = 8`.

These different numbers are both correct. The difference of 16 is **not** an observed compute saving, because all 24 token-layer rows were actually evaluated.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** What would it mean if an upper-layer previous key changes when a new future token is appended without an eviction?

<details><summary>Reveal the worked explanation</summary>

It would violate the expected causal prefix-invariance contract or reveal a numerical/implementation problem. The append must be rejected and the model operator or trace investigated rather than accepting the new row as valid.

</details>

## Continue studying

[Previous lesson](209-prefill-real-kv-rows-from-an-unpadded-prompt.md) · [Next lesson](211-rebuild-all-layers-after-absolute-position-rollover.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/210-verify-existing-rows-before-appending.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
