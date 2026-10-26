# A Native Multi-Layer Transformer, One Block at a Time

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT

**Intended length:** Approximately 7–9 minutes.  
**Audience:** Programming beginners learning neural-network engineering.

### Scene 1 — Why one block is not a language model

**Visual:** Three small boxes labelled Embeddings, Transformer Block and Logits. A second Transformer box slides into the middle.

**Narration:** “Last time, we learnt how one Umicom Transformer block handles queries, keys, values and feed-forward operations. A larger decoder can apply several blocks in sequence. The first block's output becomes the second block's input. We don't need a second mathematical engine. We need correct composition of the operations we already have.”

### Scene 2 — Follow the numbers

**Visual:** Four token positions by eight channels; the data stays `[4,8]` between blocks. Feed-forward arrows widen to 12 and shrink back to 8.

**Narration:** “Think of the hidden state as four rows of eight numbers. Each Transformer block accepts this shape and gives us the same shape back. Inside each block, the feed-forward network temporarily expands the width and contracts it again. The final vocabulary head changes the width to the number of available token IDs.”

### Scene 3 — Ownership belongs to Framework

**Visual:** A green Umicom Framework layer containing a tape, two parameter groups and the canonical attention module. A thin Studio GUI receives a result.

**Narration:** “The Framework owns tensors, memory, loss, differentiation and the optimiser. The application should request an operation and present its result, not copy neural arithmetic into a private UI component.”

### Scene 4 — A real test

**Visual:** Contexts `A B C D` and `A B X Y` produce matching highlighted logits at A and B.

**Narration:** “A decoder must not peek at future tokens. When only the final two tokens change, the earlier two positions should keep exactly the same model inputs and numerically matching logits. The regression checks all vocabulary scores, not only a chosen word.”

### Scene 5 — What we have built

**Visual:** An educational stack labelled 2 layers; GPU-scale, giant corpus and verified chat policy appear as separate, unfilled outlines.

**Narration:** “This is now a real trainable multi-layer stack, but within an educational CPU tape. We have not built a production-scale language model or proved multi-layer cache reuse. Every milestone needs its own test evidence.”

**On-screen exercise:** If one hidden row has eight channels and two attention heads, how many channels go to each head? Answer: four.

**Related reading:** [Native LLM lesson 121](../../../lessons/10-native-ai/121-build-a-real-multi-layer-transformer.md) and [mathematics Unit 48](../../../lessons/11-maths-for-ai/48-track-tensor-shapes-through-the-stack.md).
