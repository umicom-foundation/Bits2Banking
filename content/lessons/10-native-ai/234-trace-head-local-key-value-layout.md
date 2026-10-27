# Lesson 234 — Trace head-local key and value layout

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Calculate flat memory offsets safely and recognise when tensor layout differs from logical attention shape.

## 1. Understand the problem

A textbook attention tensor is often written `[heads, tokens, headWidth]`. Real Framework storage may be layer-major, padded or strided. **Logical shape is not proof of physical contiguity.** A single-query kernel must consume the actual storage contract or an explicitly verified view; it must not infer a stride from a drawing in a lesson.

For tightly packed head-major storage, the zero-based FP32 element index is `((head × validTokenCapacity) + token) × headWidth + channel`. With a larger physical token stride, replace `validTokenCapacity` in that formula with the *allocated* token pitch. Bounds are checked against the true allocation before multiplying.

## 2. Fully worked example

Take `heads=2`, allocated token pitch `T=3`, `headWidth=2`. For `head=1`, `token=2`, `channel=1`, the flat index is `((1×3+2)×2)+1 = 11`, the last of 12 elements. If a developer mistakenly flattens as `[token, head, width]`, they obtain `((2×2+1)×2)+1 = 11` for this boundary example, so the bug hides. Check another point: `head=1`, `token=0`, `channel=1` should be `7`; token-major gives `3`. One matching endpoint is not a layout proof.

## 3. Engineering verification and connection to Umicom Framework

Compare the memory view against the existing K/V store API rather than inventing a second layout. Qualify two distinct head–token pairs, non-square dimensions, a strided view, a first/last valid row and a rejected out-of-range row. Validate all multiplies against `SIZE_MAX` before allocating or calculating an address.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 125](../11-maths-for-ai/125-identify-single-query-attention-dimensions.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** What test catches an accidental swap between head-major and token-major axes?

<details>
<summary>Reveal the worked answer</summary>

Use a deliberately non-symmetric labelled tensor (for example, values encode head and token), then retrieve several interior elements. Shape and total element count alone cannot detect the swap.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](233-define-a-single-query-attention-contract.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](235-calculate-one-query-causal-attention.md)

*Service to Many Leads to Greatness.*
