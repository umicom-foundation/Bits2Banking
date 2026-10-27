# Lesson 247 — Plan portable CPU kernel optimisation

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Separate a correct portable C23 reference from later hardware-specific acceleration.

## 1. Understand the problem

The first accepted single-query operator should prioritise a clear ownership contract, checked indices and numerical proof against the canonical decoder. Only then is it sensible to consider auto-vectorisation, cache-aware tiling or Assembly for a specific architecture. An Assembly path may change summation order, alignment assumptions and denormal handling; those differences require their own qualifications.

For small head widths and short contexts, the cost of constructing buffers or invoking many tiny Framework tape operations may dominate. For longer contexts, K/V reads and score accumulation can dominate. Neither conclusion implies that every CPU benefits from one kernel shape. Dispatch must select only **supported and tested** hardware instructions, with a portable fallback.

## 2. Fully worked example

Imagine processing 8 heads of width 64 against 128 retained keys. Ignoring exponentials and projections, a rough count is approximately `4×8×128×64 = 262,144` scalar multiply/add operations for score and weighted-value phases. A shorter context of 8 rows gives roughly `16,384` operations. The same fixed dispatch or temporary-allocation overhead occupies a much larger fraction of the smaller workload.

## 3. Engineering verification and connection to Umicom Framework

Capture reference vectors for each selected CPU backend, misaligned and aligned buffers, tail widths that do not match vector length, and differences in floating-point contraction. No backend should be deployed solely because a microbenchmark is favourable; whole-decoder parity and regression tests remain the gate.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 135](../11-maths-for-ai/135-estimate-attention-arithmetic-and-memory-traffic.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** Should an Assembly backend replace the portable C23 fallback as soon as it passes one benchmark?

<details>
<summary>Reveal the worked answer</summary>

No. Keep the validated portable path for unsupported hardware, diagnostics and numerical comparison, and qualify the accelerated path across shapes and supported instruction sets.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](246-benchmark-one-query-attention-with-fair-controls.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](248-define-the-single-query-kernel-acceptance-gate.md)

*Service to Many Leads to Greatness.*
