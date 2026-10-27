# Video lesson — Inside the single-query branch

**Bits to Banking · Umicom Foundation**  
**Author and narrator:** Sammy Hegab

## Narration

A Transformer decoder sees a growing prefix of tokens. When a new token arrives, its token embedding is combined with a positional embedding. The first Transformer layer normalises this new state, then projects one query, one key and one value. But the query has a special role: it asks which already visible tokens matter for the next representation. The existing K/V store supplies the history.

The original educational incremental path built a full matrix of queries with zeros in the earlier rows. It called the training tape's full attention operator and then extracted the last row. This produced the right forward answer for the newest query but evaluated rows that would never be used. The integrated path passes only the newest query to a forward-only attention kernel. The kernel scores every visible K/V row, uses a stable softmax and returns one attention vector.

Notice what has not changed. The checkpoint, tokeniser, layer normalisation, Q/K/V projection weights, residual connections, feed-forward network and final logits head are the same. The differentiable training operator still exists for training. The inference operator is allowed to be forward-only because no parameter gradients are requested.

Question for the viewer: if there are four Transformer layers and seven visible tokens, how many query rows are executed during a growing-prefix step? Four, not twenty-eight. Yet each query may still examine seven keys. This distinction helps us reason about actual work instead of guessing speed.

## Visual storyboard

1. Draw the active query as a single row and the historical K/V as a retained matrix.
2. Show the shape and index invariants using the concrete example from the narration.
3. Compare reference and incremental paths with identical inputs and checkpoint identity.
4. Conclude with the difference between tested numerical behaviour and measured execution speed.
