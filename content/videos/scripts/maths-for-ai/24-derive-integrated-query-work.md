# Video lesson — Deriving query work and cache memory

**Bits to Banking · Umicom Foundation**  
**Author and narrator:** Sammy Hegab

## Narration

Let T denote the number of visible tokens, C the hidden-channel count and L the number of Transformer layers. A conventional full-window attention calculation processes T query rows per layer. A growing-prefix incremental step needs one query row per layer. That changes the query-row count from L times T to L, but not the fact that each new query must score all T visible keys.

With three layers and a five-token prefix, the old full-window shape represents fifteen query-layer rows. The new incremental attention path executes three. The dot-product work for the three query rows is approximately three times five times C scalar terms for Q against K, plus a comparable number for probabilities against V.

Now consider temporary memory. A simple stable-softmax implementation holds T double-precision scores, T single-precision probabilities and C candidate output values. That totals eight T plus four T plus four C bytes, excluding allocator metadata and other tensor buffers. For six tokens and eight channels, this temporary payload is one hundred and four bytes.

The same lesson gives us a caution. A row-count reduction is not a measured speedup. Real execution may be limited by memory traffic, allocation and other operators. Mathematics tells us what to measure, not what the stopwatch must say.

## Visual storyboard

1. Draw the active query as a single row and the historical K/V as a retained matrix.
2. Show the shape and index invariants using the concrete example from the narration.
3. Compare reference and incremental paths with identical inputs and checkpoint identity.
4. Conclude with the difference between tested numerical behaviour and measured execution speed.
