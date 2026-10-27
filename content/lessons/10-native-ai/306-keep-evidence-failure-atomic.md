# Lesson 306 — Keep numerical evidence failure-atomic

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test keep numerical evidence failure-atomic within the bounded multi-layer Transformer.

## The underlying mechanism

A diagnostic should never publish a partial success report after discovering invalid input or mismatching logits. A partial report could be mistaken for a completed qualification when it only covers a prefix of the requested sequence.

## Step-by-step worked example

Initialise an output report to a recognisable byte pattern and pass an out-of-range token ID. The service rejects the input before creating any accepted evidence; an exact byte comparison of the report before and after the failure confirms publication atomicity.

## C23 implementation and Framework boundaries

The C23 qualification service accumulates its counters in a private local report and writes the caller’s report only after all requested comparisons and checkpoint checks succeed. Every early failure releases the temporary cache.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

Failure atomicity concerns caller-visible state. A canonical training-tape rollback may reset gradient-readiness metadata according to its existing documented contract; do not claim the tape is bitwise unchanged.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** A test observes a correct first step but an error at step seven. May it return a success report for the first six steps?

<details><summary>Reveal the worked answer</summary>

Not through the complete-run qualification API. It must report failure and leave the caller’s output unchanged.

</details>

## Mathematical connection

Read [Mathematics Unit 182](../11-maths-for-ai/182-distinguish-deterministic-replay-from-sampling.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](305-detect-stale-model-identity-during-qualification.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
