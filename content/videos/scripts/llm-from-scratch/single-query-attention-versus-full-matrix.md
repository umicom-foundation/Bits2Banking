# Video storyboard — One query, not a full attention matrix

**Series:** Build an LLM from Scratch · **Course lead:** Sammy Hegab · Umicom Foundation  
**Companion:** Lessons 233–238; Mathematics Units 125–129  
**Estimated teaching format:** 6–8 minute explanatory screencast. Time suggestions are editorial, not verified runtimes.

## Scene 1 — What the Transformer needs (opening)

**Narration:** “When a decoder generates a new token, it asks one new question: which earlier tokens should this position attend to? A full attention-matrix operation may calculate answers for previous queries again. Our next optimisation wants only the newest query row.”

**Visual:** Draw a triangular causal attention matrix. Shade only its last row; mark earlier rows as correct but not required for this incremental step. Put a note on screen: “Reference computation and candidate computation must describe the same trained model.”

## Scene 2 — Trace the tensor shapes

**Narration:** “For three heads and five retained tokens, each head receives one query vector, five keys and five values. Head outputs remain separate until concatenation and the learned output projection.”

**Visual:** Show `[heads=3, queries=1, channels=4]` beside `K,V=[3,5,4]`. Animate the valid-length boundary before padded capacity. Circle the `5`: it is a number of admitted positions, not the total allocated slots.

## Scene 3 — Work through real numbers

**Narration:** “With a two-channel query `(2,0)` and keys `(1,0)` and `(0,1)`, the scaled scores are approximately `1.414` and `0`. Subtract the maximum before softmax. The first key gets about `80.44%` attention; the second gets about `19.56%`. Weighted values `(1,0)` and `(0,2)` produce `(0.8044,0.3911)`.”

**Visual:** Reveal the fractions and the weighted vector one line at a time. Show that a third padded key, even if zero, would incorrectly receive positive probability if included.

## Scene 4 — Why tests matter

**Narration:** “The single-query result must match the final row of the established Umicom Framework decoder. We compare every head and eventually every vocabulary logit. A matching sampled token cannot prove a correct probability distribution.”

**Visual:** Two columns labelled “existing decoder — independent reference” and “candidate single-query operator — not yet qualified”; overlay error checks, a masked-row test and a nonfinite-value rejection.

## Scene 5 — Close and next lesson

**Narration:** “This is not yet a claim that Umicom runs faster. We first prove the arithmetic, memory lifetime, checkpoint identity and rollover behaviour. Then we measure a Release build on the same hardware and input.”

**On-screen next steps:** [LLM learning path](../../../courses/llm-from-scratch/single-query-attention-learning-path.html), [Mathematics companion](../../../courses/maths-for-ai/single-query-attention-mathematics.html).

*Service to Many Leads to Greatness.*
