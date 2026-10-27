# Video storyboard — A cache is correct only while its assumptions hold

**Series:** Build an LLM from Scratch · **Course lead:** Sammy Hegab · Umicom Foundation  
**Companion:** Lessons 239, 242–245, 248; Mathematics Units 133–134

## Scene 1 — The tempting incorrect shortcut

**Narration:** “A context window fills up. Why not move the cached keys and values left by one and append a new row? That looks efficient, but for a learned absolute-position decoder it is generally the wrong calculation.”

**Visual:** Show `A@0 B@1 C@2` becoming `B@0 C@1 D@2`. Highlight the changes from `B@1` to `B@0` and `C@2` to `C@1`.

## Scene 2 — Position is part of the input

**Narration:** “The decoder embeds token identity *and* position. Reusing the projection for `B@1` as though it were `B@0` is not the same computation. Earlier available history changes too. At rollover, our conservative path rebuilds all layers using the canonical decoder.”

**Visual:** Draw two arrows: safe unchanged-position append to proposed fast path; reassigned-position window to canonical rebuild. Label the gate “correctness policy, not performance guess”.

## Scene 3 — Model identity

**Narration:** “A cache is derived from one frozen checkpoint. A different checkpoint may have the same tensor dimensions but different weights. Byte identity, provenance approval and compatibility are separate checks.”

**Visual:** Two checkpoint cards share `layers=2, heads=4` but carry different content identifiers. Show the old cache rejected for the updated model.

## Scene 4 — Failure atomicity

**Narration:** “A proposed token can fail because the caller’s output buffer is too short or a callback refuses the output. A rejected step must not leave half a token in history, partially published K/V rows or a consumed random draw.”

**Visual:** Timeline: calculate → validate → commit; inject a buffer failure before commit, then show prefix, cache version and sampler state unchanged. Repeat with adequate capacity and the same seed.

## Scene 5 — How a test proves the contract

**Narration:** “Cross the first and repeated rollover boundaries, retry failures and compare intermediate attention outputs and complete logits to the reference. Only then may anyone benchmark a proposed single-query kernel.”

**On-screen next steps:** [LLM learning path](../../../courses/llm-from-scratch/single-query-attention-learning-path.html), [Mathematics companion](../../../courses/maths-for-ai/single-query-attention-mathematics.html).

*Service to Many Leads to Greatness.*
