# Lesson 93 — Prove Real-Tape Results Before Optimisation

**Series:** Bits2Banking · Building an LLM from Scratch · C23 · **Author:** Sammy Hegab, Umicom Foundation

## Learning outcome
Independent evidence is a prerequisite for any claimed performance improvement.

## Concept in everyday terms
A banking reconciliation is not correct because its programme displays a green light. We check the source transactions and independently calculated totals. Similarly, a training-tape acceptance report only evaluates supplied results; it does not run the tests.

## Equation and every symbol
`error = |analytical gradient - numerical gradient|`

- **Analytical gradient:** derivative calculated by the training tape's backward pass.
- **Numerical gradient:** derivative independently approximated by perturbing one weight.
- **| |:** absolute value; only the size of the difference matters.

If the first gradient is 0.0234 and the second is 0.0231, the absolute error is 0.0003. With a previously declared tolerance of 0.0008, this example is within tolerance. The real test may differ.

The new native `UmiAiTrainingRotaryAcceptanceEvaluate` API rejects missing or contradictory observations, but it must never be described as running the decoder tests itself.

## Engineering laboratory
1. Review source revision and selected build preset.
2. Run the production rotary gradients, budget and rewind tests.
3. Compare numerical gradient error against a declared tolerance.
4. Reject incomplete results; record environment and evidence.

## Self-assessment
Describe the difference between a synthetic unit-test fixture and an actual production acceptance run. Identify one source of numerical error and one source of memory error.

## Remedial study
- [Mathematics unit 19: Evidence and numerical tolerances](../../maths-for-ai/lessons/19-evidence-thresholds-and-uncertainty.html)
- [Mathematics unit 20: Chain rule and computation graphs](../../maths-for-ai/lessons/20-matrix-chain-rule-and-computation-graphs.html)

## Companion formats
- `93-check-real-tape-evidence.html` browser lesson
- `content/videos/scripts/llm-from-scratch/93-check-real-tape-evidence.md` narrated storyboard
