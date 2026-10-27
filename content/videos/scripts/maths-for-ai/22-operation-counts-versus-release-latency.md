# Video script 22 — Operation counts versus Release latency

**Series:** Mathematics for AI · **Course lead:** Sammy Hegab · Umicom Foundation  
**Companion:** Units 132, 135–136 and LLM Lessons 246–248.

## Scene 1 — Count what the kernel does

**Voiceover:** “For a one-query attention step with `H` heads, `T` retained tokens and `D` channels per head, dot products and value accumulation require approximately `4×H×T×D` counted multiply/add operations. This convention excludes exponentials, projection matrices and various memory costs.”

**Board:** Use `H=4,T=64,D=16`. Calculate `4×4×64×16=16,384`. Label this “arithmetic estimate — not a stopwatch reading”.

## Scene 2 — Count what memory delivers

**Voiceover:** “Keys and values together contain `2×H×T×D` numbers. At four bytes per FP32 value, the same example moves at least `32,768` payload bytes if each number is read once. Real hardware can move more because of cache-line granularity, retries or intermediate buffers.”

**Board:** Label K/V payload separately from scratch, model weights and checkpoint files.

## Scene 3 — Compare five measurements

**Voiceover:** “Suppose a reference median is five milliseconds and a candidate median is 4.8 milliseconds in a tiny controlled sample. The ratio is about 1.042, not evidence that all models or computers are four per cent faster. One or more candidate runs may still be slower.”

**Board:** Show two small arrays, sort them and underline their medians. Highlight sample variability.

## Scene 4 — Correctness before speed

**Voiceover:** “A faster but numerically different decoder is not the same model. First pass every-head and every-logit parity, rollover and failure-atomicity tests against the real Framework; then report Release timing distributions on the same hardware, seed, model and workload.”

**On-screen reading:** [Unit 135](../../../lessons/11-maths-for-ai/135-estimate-attention-arithmetic-and-memory-traffic.md), [Unit 136](../../../lessons/11-maths-for-ai/136-read-paired-latency-measurements.md).

*Service to Many Leads to Greatness.*
