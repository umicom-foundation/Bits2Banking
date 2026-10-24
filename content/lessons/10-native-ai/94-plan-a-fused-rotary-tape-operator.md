# Lesson 94 — Plan a Correct Fused Rotary Operator

**Series:** Bits2Banking · Building an LLM from Scratch · C23 · **Author:** Sammy Hegab, Umicom Foundation

## Learning outcome
A design exercise, not a completed performance optimisation.

## Concept in everyday terms
A manufacturing line may use several steps, each temporarily storing its output. A fused operator tries to combine stages. The change is only worthwhile when the result is the same and memory ownership remains safe.

## Equation and every symbol
`inputGradient = R(position)^T * outputGradient`

- **R(position):** two-dimensional rotation applied at the token's absolute position.
- **^T:** transpose, which for a rotation reverses the forward rotation.
- **outputGradient:** how the final loss changes when the rotated output changes.
- **inputGradient:** how the loss changes when the original input changes.

For the 90-degree teaching case, forward maps `[1,0]` to `[0,1]`; the transpose maps a gradient `[0,1]` to `[1,0]`.

**Status:** This is a design exercise. Batch 93–94 does not supply a fused production attention operator.

## Engineering laboratory
1. Draw the existing query/key rotation and causal attention graph.
2. List saved intermediates and gradient dependencies.
3. Design tape-owned failure-atomic rollback and gradient accumulation.
4. Confirm parity and memory safety before benchmarking.

## Self-assessment
Describe the difference between a synthetic unit-test fixture and an actual production acceptance run. Identify one source of numerical error and one source of memory error.

## Remedial study
- [Mathematics unit 19: Evidence and numerical tolerances](../11-maths-for-ai/19-evidence-thresholds-and-uncertainty.md)
- [Mathematics unit 20: Chain rule and computation graphs](../11-maths-for-ai/20-matrix-chain-rule-and-computation-graphs.md)

## Companion formats
- [Illustrated HTML course lesson](../../courses/llm-from-scratch/lessons/94-plan-a-fused-rotary-tape-operator.html)
- [Video narration and storyboard](../../videos/scripts/llm-from-scratch/94-plan-a-fused-rotary-tape-operator.md)
