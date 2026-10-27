# Lesson 257 — Understand paged KV memory and block tables

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Explain how non-contiguous cache blocks can represent a logical token sequence.

## 1. Understand the concept

Autoregressive sessions have different prompt lengths and may end at unpredictable times. Reserving each session's maximum possible context as one contiguous K/V allocation can waste memory. A **paged KV cache** divides physical storage into fixed-size blocks. Each sequence stores a logical-to-physical block table, so a logical token position can locate its K/V without requiring all tokens to occupy adjacent physical addresses.

This idea is related to virtual memory, but a KV cache does not become correct merely by adopting memory pages. Its block table must preserve token order, layer/head layout, reference ownership and model identity. Eviction must not leave a stale mapping visible; shared physical blocks require explicit lifetime accounting.

## 2. Work through the numbers

Let block size be 16 tokens and one session retain 34 valid tokens. It requires `ceil(34/16)=3` physical blocks with capacity for 48 tokens, leaving 14 unused positions in the final block. A second session with 9 tokens needs one block. Together they use four allocated blocks. A fixed 128-token reservation per session would instead reserve 256 token slots.

To locate logical token 33, calculate `blockIndex=floor(33/16)=2` and `withinBlock=33 mod 16=1`. The block table provides the physical block identifier for logical block 2; the kernel then reads offset 1 within that physical block.

## 3. Apply the concept to native model engineering

A C23 implementation needs checked multiplication of block counts, tokens, head width and bytes; independently validated indices; and an ownership model supporting cancellation without use-after-free. The attention kernel should accept a verified view or an iterator rather than understanding allocator internals. Testing should include reordered physical blocks, shared blocks, short final blocks and allocation failure.

The PagedAttention research behind vLLM reports throughput gains for its tested workloads, but those results are not measurements for the bounded native Umicom model. The distinction between logical order and physical allocation is the transferable lesson.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 144](../11-maths-for-ai/144-calculate-paged-kv-internal-fragmentation.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** What physical offset does logical token 52 have inside 16-token blocks?

<details>
<summary>Reveal the worked answer</summary>
<p><code>52 mod 16=4</code>, so the within-block offset is 4; the logical block index is <code>floor(52/16)=3</code>.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[256 — Quantise KV caches with an error budget](256-quantise-kv-caches-with-an-error-budget.md) · [258 — Distinguish absolute positions from rotary positions](258-distinguish-absolute-positions-from-rotary-positions.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
