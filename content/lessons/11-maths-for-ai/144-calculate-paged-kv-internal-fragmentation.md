# Mathematics for AI — Unit 144: Calculate paged KV internal fragmentation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Count allocated blocks and unused token slots.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

A cache divided into fixed-size blocks of `P` tokens needs `ceil(T/P)` blocks for a sequence of length `T`. If `T=34` and `P=16`, the session needs three blocks, storing up to 48 tokens. Internal unused capacity equals `48−34=14` token slots. The utilisation of those allocated slots is `34/48≈70.83%`.

Paging can reduce external fragmentation and the need for long contiguous allocations; it does not automatically eliminate unused space inside the final block.

## 3. Practice problem

**Question:** How many 32-token blocks are needed for 70 tokens, and how many slots remain unused?

<details>
<summary>Show the worked answer</summary>
<p><code>ceil(70/32)=3</code> blocks, 96 slots total, 26 unused.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 257 — Understand paged KV memory and block tables](../10-native-ai/257-understand-paged-kv-memory.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](143-measure-absolute-and-scale-aware-error.md) · [Next unit](145-rotate-a-two-dimensional-position-pair.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
