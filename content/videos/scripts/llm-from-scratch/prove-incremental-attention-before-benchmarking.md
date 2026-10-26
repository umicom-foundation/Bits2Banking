# Prove incremental attention before benchmarking

**Sammy Hegab · Umicom Foundation**  
**Format:** Engineering teaching script and benchmarking worksheet.

## Objective

Learners should distinguish three separate questions: Are the model's K/V values genuine? Does a proposed cache produce the same logits as the canonical decoder? Is any observed execution time actually lower?

## Opening narration

A speed claim cannot rescue an incorrect result. Building a K/V storage component is an important step, but not the same as computing attention incrementally. Umicom now has an explicit observation path which copies the actual canonical Transformer projections into a bounded, checkpoint-bound cache owner. It still executes the original full-context network for every observation.

Our next challenge is to use retained projections to perform less repeated mathematics **without changing the declared output semantics**. The test must compare every vocabulary logit, not just one sampled token. It must hold model identity, prompt positioning, context rollover, sampling policy and seed fixed.

## Scene 1 — A fair acceptance matrix

Draw rows for prefix lengths one, three and eight with an eight-token context. For each row, record checkpoint SHA-256, reference logits, candidate logits, maximum absolute error, token-layer operations, peak tracked allocations and wall-clock times. Then append one token at full capacity to test the first eviction. Repeat additional evictions to test reconstruction of learned absolute positions and upper-layer history.

Show that a NaN in either result makes a comparison invalid. A failure must preserve the caller's last complete report instead of writing a partly successful one.

## Scene 2 — Counting work correctly

A two-layer, eight-token canonical model evaluates sixteen token-layer rows for each complete generation step. Over twelve generated tokens this is 192 token-layer rows. A hypothetical cache planner may predict fewer rows, but an observation service that still runs twelve full forward passes has actually performed all 192. Stored rows are not a measurement of executed work.

## Scene 3 — Timing after correctness

Explain why CPU frequency, memory traffic, allocation overhead, cache warming and compiler optimisation change observed latency. Warm each path, alternate execution order, repeat measurements, and report the median alongside the range. Record the compiler, operating system, machine, model checkpoint and sampling settings. A faster single run is not a reproducible performance result.

## Closing exercise

A purported cache reports fewer stored rows but takes 4.7 milliseconds, while the canonical model takes 4.2 milliseconds for the same request. Has it demonstrated a speedup? **No.** Its observed latency is higher despite accepting fewer K/V rows. Check numerical parity and actual work before deciding whether the new path belongs in a release.

[Read Lesson 216](../../../lessons/10-native-ai/216-design-the-next-incremental-attention-reference.md) and [Mathematics Unit 112](../../../lessons/11-maths-for-ai/112-design-controlled-inference-benchmarks.md).
