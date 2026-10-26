# Video lesson — Why Learned Positions Require a Full KV Rebuild

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Intended audience:** Beginning native LLM and Transformer students.

## Scene 1 — Four positions and five tokens

**Visual:** A four-slot timeline: first `[A B C D]`, then `[B C D E]`. Show each token's slot number above it.

**Narration:** "Our bounded educational stacked decoder uses learned absolute positional embeddings. At first, B is in position one. After the window moves, B is in position zero. This does not merely change a label; it changes the numerical position embedding combined with B. Its projected attention state may therefore change."

**Teacher's question:** "Is moving a token from slot one to slot zero the same calculation as leaving it at slot one?" Wait for the viewer to answer before revealing no.

## Scene 2 — Why the upper layers matter

**Visual:** A first-layer arrow from A to C, followed by a second-layer arrow from the first-layer state of C to its second-layer state. Fade A from the shortened context.

**Narration:** "There is a second subtlety. At a previous time, the representation of C in an upper layer may already contain information from A. After A leaves the window, the canonical model with the new shorter history does not have precisely the same inputs. Causal masking stops tokens from seeing the future; it does not remove previously accumulated information from the past."

## Scene 3 — A safe native contract

**Visual:** A full-window replacement button, not an ordinary overwrite ring. Show K and V values for all layers being replaced together.

**Narration:** "For the current learned-position architecture, Umicom's K/V owner does not allow a fifth incremental append into a four-slot cache. It requires an explicitly shifted token sequence and a fresh set of key/value projections for every layer. Every submitted float is checked before publishing the first replacement. A malformed token sequence or a NaN leaves the previous state unchanged."

## Scene 4 — Count the work

**On-screen:** `layers = 3`, `context = 4`, `prefill = 2`, `generated = 7`.

**Narration:** "The last sampled token is pending, so seven output tokens cause six cache transitions. Two of these transitions append a single token; four rebuild the entire context. The stored work is three times the sum of two prefill rows, two appended rows and four times four rebuild rows. That is sixty token-layer rows. A full-context reference requests eighty-four. The difference, twenty-four rows, is a computation count—not a measured reduction in milliseconds."

## Practice and worked answer

**Question:** Why is replacing only the final K/V row after eviction unsafe for the current decoder?

**Answer:** Retained tokens move to new absolute positions, and upper-layer states can depend on history no longer present. Every layer's K/V projections must be recalculated for the shifted canonical context.

## Continue

[Read LLM Lesson 190](../../../lessons/10-native-ai/190-rebuild-the-entire-window-after-rollover.md) and [Mathematics Unit 93](../../../lessons/11-maths-for-ai/93-verify-a-one-step-rolling-sequence.md). The video depicts the established safe contract, not a finished accelerated Transformer.

*Service to Many Leads to Greatness.*
