# Video lesson — MQA, GQA and paged KV memory

**Bits to Banking · Umicom Foundation**  
**Script and storyboard:** Sammy Hegab  
**Format:** Short educational lecture with numerical overlays and captions.

## Purpose

This lesson reinforces native LLM Lessons 253–257 and Mathematics Units 140–144. Diagram annotations are conceptual and do not depict measured Umicom Framework runtime performance.

## Storyboard and narration

### Scene 1 — Multi-head attention

**Visual:** Eight query heads, each with its own K/V bank. **Narration:** Standard multi-head attention stores separate keys and values for each query head. Decoding often spends significant time rereading these arrays. They are derived from learned projection matrices; changing their arrangement changes the model.

### Scene 2 — Shared KV banks

**Visual:** Eight queries map to two KV banks, four queries per bank. **Narration:** Grouped-query attention maps several query heads to one key/value head. The mapping `floor(queryHead/groupSize)` is explicit, so query 6 belongs to shared bank 1 when each bank serves four queries. Multi-query attention is the limiting case with one KV head. Neither design can be assumed to preserve a differently trained checkpoint.

### Scene 3 — Count bytes

**Visual:** Parameter card showing `2×L×T×Hkv×d×bytes`. **Narration:** Two is for keys and values. Multiply by layers, tokens, KV heads, head width and bytes per scalar. The number is raw cache storage, not all process memory or a guaranteed speed prediction.

### Scene 4 — Pages and logical order

**Visual:** A logical 34-token sequence mapped across three 16-token physical blocks in non-contiguous locations. **Narration:** A page table separates logical sequence order from physical allocation. It can reduce allocation waste but still requires valid ownership, correct block indices, checkpoint identity and safe eviction.

## On-screen recap

The architecture, mathematical contract and actual observed performance are three different subjects. A viewer should be able to repeat the worked numbers and identify which proof would establish an inference optimisation's correctness.

## Suggested check-for-understanding

Pause before the final scene, hide the answer and ask the learner to explain one invariant using the numbers on screen. Reveal the original equation, not merely a claimed conclusion.

*Service to Many Leads to Greatness.*
