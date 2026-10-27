# Video Lesson — Paired Native Benchmarking and Token Parity

**Bits to Banking · Umicom Foundation**  
**Author and narrator:** Sammy Hegab  
**Companion reading:** LLM Lessons 281–286.

## Learning objective

Distinguish mathematical correctness from performance evidence when comparing a canonical Transformer with a cached decoder.

## Narration

A faster numerical routine is only useful when it computes the intended result. Imagine two versions of a Transformer. The reference version evaluates the entire context for each new token. The candidate version reuses previously calculated keys and values. The candidate performs fewer attention queries while a prompt grows, but that count alone says nothing about the user's waiting time.

Start by fixing the model. Both versions load identical weights and receive identical token IDs, a shared prompt length, an unchanged context policy and the same random seed. Let the reference produce eight tokens and record each ID. Run the candidate and compare all eight. If even one ID differs, stop the performance comparison and investigate the numerical path.

Now consider logits. Equal token IDs are necessary for a paired behavioural test, but they are not proof of numerical parity. Two slightly different probability distributions can select the same token. A stronger test compares every vocabulary logit and the newly projected K/V rows at every Transformer layer. That qualification belongs to the existing Framework numerical tests.

After the correctness checks, choose a monotonic elapsed timer. Warm up both paths and alternate which runs first. Record every measurement, not only the fastest. Separate the median duration from operation counts. A short test of five paired calls is an educational observation; it is not a statistically complete claim about all models and hardware.

Finally look at context rollover. With learned absolute positions, removing the oldest token changes the positions of all remaining tokens. The cache must be rebuilt under the canonical model. A workload dominated by rebuilding may run slower despite successful single-query attention. This is why the complete generation call matters.

## Visual storyboard

| Frame | Visual description | On-screen calculation |
|---|---|---|
| 1 | Two paths from the same checkpoint and prompt | Same weights + same tokens + same seed |
| 2 | Parallel generated token rows | Reference IDs = Candidate IDs |
| 3 | One vocabulary distribution compared with another | All logits, not only argmax |
| 4 | Paired A→B, B→A timing timeline | Elapsed = end − start |
| 5 | Growing prefix entering full-window rollover | Recompute after absolute-position shift |
| 6 | Results showing counters and measured medians separately | Work reduction ≠ measured speedup |

## Discussion exercise

A candidate reports 40% fewer query rows but a 10% higher measured generation median. Explain why the two statements can both be correct. The answer must mention full-context fallback or non-attention work.

*Service to Many Leads to Greatness.*
