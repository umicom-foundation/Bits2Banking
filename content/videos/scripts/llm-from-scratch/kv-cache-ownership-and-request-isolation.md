# Video Lesson — KV-Cache Ownership and Request Isolation

**Bits to Banking · Umicom Foundation**  
**Author and narrator:** Sammy Hegab  
**Companion reading:** LLM Lessons 287, 290–293.

## Learning objective

Explain why shared model weights do not make mutable attention state shareable without explicit contracts.

## Narration

An LLM server can process requests from different people using one common model. Sharing immutable weights is usually natural. Sharing the key/value projections calculated from a prompt is more subtle. Those projections depend on the exact token prefix, model checkpoint, positional policy and attention-head geometry.

Picture two requests. The first asks about banking; the second asks about a mathematical proof. Both can use the same matrix weights, but their histories and random sampling states remain separate. If the model accidentally reads a K/V row from the other session, the generated output can become incorrect and potentially disclose information from the wrong context.

The cache owner must know which request or immutable prefix page owns each row. A reference-counted prefix can be shared only when the token IDs and every relevant model identity match. Cancelling one request removes its own references without invalidating another user's continuing generation. A model update makes old projections stale even when the visible prompt remains identical.

Group-query attention changes how many K/V heads must be stored. With sixteen query heads and four K/V heads, four query heads share each K/V group. That ratio can reduce K/V payload to one quarter of standard MHA under otherwise matching dimensions. It also changes checkpoint shapes, so an old MHA model cannot automatically be relabelled as GQA.

Quantisation similarly introduces a numerical representation change. Storing eight-bit values may reduce tensor payload, but scale values, metadata, dequantisation costs and altered attention probabilities all matter. Neither shared prefixes nor compact KV formats are implemented merely by changing a memory counter.

## Visual storyboard

| Frame | Visual description | Key label |
|---|---|---|
| 1 | Shared model weights serving two sessions | Immutable weights |
| 2 | Two separate histories and RNG states | Distinct request owners |
| 3 | Identical initial tokens branching at token four | Share only valid causal prefix |
| 4 | Refcounts falling from two to one | Release one reference safely |
| 5 | Sixteen Q heads mapping to four KV heads | GQA memory ratio 4:1 |
| 6 | Int8 KV blocks with scales and error bars | Lower precision changes arithmetic |

## Discussion exercise

List at least four properties that must match before two generation sessions can safely share a cached prefix. Explain what happens to the shared cache when the model is retrained.

*Service to Many Leads to Greatness.*
