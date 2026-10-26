# Video lesson — Proving Causality Across Multiple Transformer Layers

**Bits to Banking · Umicom Foundation**  
**Author/presenter:** Sammy Hegab  
**Format:** Narration and accessible storyboard for a prospective educational recording

## Opening narration

“Welcome to Bits to Banking. Today we will take a small native C23 language-model problem and calculate it using visible, verifiable steps. Our goal is to understand exactly what Umicom Framework currently computes, and which claims require further engineering and tests.”

## Scene 1 — Put the problem on screen

Draw two sequences that share a two-token prefix and have different suffixes. Trace causal attention arrows only backwards; display 2×260=520 checked logits for a 260-vocabulary example. Emphasise that checking output IDs alone is insufficient. Name the Framework C23 causality qualifier and its unchanged-checkpoint gate.

The illustrations use synthetic token IDs, never confidential financial records or source material. Introduce each numerical symbol verbally before the formula appears. Provide alt text for the diagram and do not rely solely on colour to distinguish two policies.

## Scene 2 — Native code and ownership

Show the public `umicom/ai/training/` header and explain that actual Transformer mathematics, random sampling and model state remain in Umicom Framework. Educational Markdown and HTML teach those services but do not provide another runtime. Pause at each return status and point out who owns the model and output buffer.

## Scene 3 — Worked example and evidence

Calculate the lesson's key numerical example on a board. Distinguish values derived mathematically from output measured by CTest on an actual decoder. A synthetic fixture can illustrate a contract, but it must never be displayed as a successful real model qualification. Explain the difference between output parity and wall-clock acceleration.

## Practice

Ask the learner whether a model with the same argmax but different second-highest logit qualifies for cache promotion.

Offer students time to calculate independently; then walk through the answer by naming the inputs, formula and relevant invariant.

## Closing narration

“Keep model identity, training-data approval, numerical correctness and observed performance as separate engineering evidence. Continue with the HTML course or its original Markdown manuscript, and remember: Service to Many Leads to Greatness.”

**Production note:** This is a written teaching script, not an actual video or a completed training experiment.
