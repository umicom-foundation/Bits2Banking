# Video lesson — Softmax, KV budgets and inference metrics by hand

**Bits to Banking · Umicom Foundation**  
**Script and storyboard:** Sammy Hegab  
**Format:** Short educational lecture with numerical overlays and captions.

## Purpose

This lesson reinforces native LLM Lessons 249–264 and Mathematics Units 137–148. Diagram annotations are conceptual and do not depict measured Umicom Framework runtime performance.

## Storyboard and narration

### Scene 1 — Softmax without overflow

**Visual:** Scores [2,1,0] are shifted to [0,−1,−2]. **Narration:** Subtracting the maximum does not change the mathematical softmax distribution. It makes exponentials numerically manageable. Calculate the exponentials and check that their normalised probabilities sum to approximately one.

### Scene 2 — Memory as a product

**Visual:** Introduce `2×L×T×Hkv×d×bytesPerElement`. **Narration:** Memory is a product of model and context dimensions. Doubling context doubles raw KV capacity; changing head-sharing or scalar precision affects it independently. Remember page tables and fragmentation.

### Scene 3 — Operations per byte

**Visual:** Dot product reading two FP32 scalars and doing a multiply plus add. **Narration:** Arithmetic intensity is FLOPs divided by bytes moved. For one multiply and one addition over eight bytes, the simple estimate is 0.25 FLOP per byte. It is an estimate of possible bottlenecks, not an observed processing speed.

### Scene 4 — Three latency clocks

**Visual:** Timeline: request arrival, first token and subsequent tokens. **Narration:** Time to first token differs from the average gap between later tokens. Throughput measures emitted tokens per elapsed service interval. State the conventions before quoting numbers.

## On-screen recap

The architecture, mathematical contract and actual observed performance are three different subjects. A viewer should be able to repeat the worked numbers and identify which proof would establish an inference optimisation's correctness.

## Suggested check-for-understanding

Pause before the final scene, hide the answer and ask the learner to explain one invariant using the numbers on screen. Reveal the original equation, not merely a claimed conclusion.

*Service to Many Leads to Greatness.*
