# A complete memory budget calculation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Format:** Narration and storyboard, approximately four minutes.

**Opening visual:** Write the equation `2 × layers × positions × KV heads × head width × bytes per scalar`.

**Narration (0:00–1:00):** “First count the tensor scalars. The factor of two represents keys and values. Multiply the layers, reserved context length and per-head geometry. Only then multiply by bytes per scalar.”

**Worked example (1:00–2:00):** `2×2×4×2×4×4=512 bytes` per session. Convert a 1,024-byte raw budget to two complete reservations. Three maximum slots do not create more memory capacity.

**Arithmetic boundary (2:00–3:00):** Before a product `a×b`, check `a==0 || b<=SIZE_MAX/a`. Explain that unsigned wraparound can incorrectly turn a huge requested allocation into a small number. Never allocate from a wrapped product.

**Storage-vs-process frame (3:00–4:00):** The 512 bytes describe raw K/V only. Draw additional boxes for model weights, temporary tensors, allocator headers and application memory. A measured RSS value is not the same as a calculated K/V reservation.

**Final question:** “How many 512-byte stores fit into 1,500 bytes?” Answer: two, leaving 476 bytes unused for another full store.

*Service to Many Leads to Greatness.*
