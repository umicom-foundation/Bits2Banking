# Lesson 311 — Run inference checks through native Framework tools

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test run inference checks through native framework tools within the bounded multi-layer Transformer.

## The underlying mechanism

Native C23 libraries, CMake targets and CTest make the inference laboratory repeatable without introducing script-language functionality. Existing Umicom CLI capabilities provide repository inspection and locking in supported installations; the course does not invent new CLI subcommands.

## Step-by-step worked example

Configure the opt-in `learning/native-ai-stacked-qualification` CMake project, build the numerical comparison and qualifier targets, then run CTest with the registered `framework.ai.stacked_qualification` expression. A separate paired benchmark is registered by the previous educational batch.

## C23 implementation and Framework boundaries

The course distinguishes a compiled numerical library from the terminal commands used to configure, build and run it. All numerical comparison logic in this laboratory is implemented in native C23.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

Use explicit CMake source and binary directories. A successful configure does not establish that the application linked or that its numerical regressions passed; inspect the build and test results independently.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** What distinguishes CMake configuration, compilation and CTest execution?

<details><summary>Reveal the worked answer</summary>

Configuration generates the build graph, compilation produces targets, and CTest executes registered regression programs and checks their exit statuses.

</details>

## Mathematical connection

Read [Mathematics Unit 175](../11-maths-for-ai/175-count-unchanged-causal-prefix-checks.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](310-separate-numerical-qualification-from-performance.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
