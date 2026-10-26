# Mathematics for AI — Unit 124: Compare Release timings with uncertainty

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

Performance measurements depend on workload, clock quality, CPU scheduling, caches, compiler options and operating-system conditions. A median is less sensitive to a single extreme sample than a simple mean, but it is not proof of universal speed.

## A fully worked example

Suppose five paired Release runs for a reference yield [4.0,4.1,4.4,4.2,5.1] ms. Sorted values are [4.0,4.1,4.2,4.4,5.1], so median is 4.2 ms. Candidate observations [4.5,4.3,4.4,4.6,5.0] ms have median 4.5 ms. In this small example the candidate is slower, even if it projects fewer rows.

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** Find the median of [3.0,4.0,4.5,5.0,10.0] milliseconds.

<details>
<summary>Show the worked answer</summary>

After sorting (already sorted), the middle observation is 4.5 milliseconds.

</details>

## Connect the idea to native C23

Run strict numerical parity first. Benchmark actual code and hardware, not a hypothetical cache-planning estimate.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](123-count-full-window-rollovers-correctly.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
