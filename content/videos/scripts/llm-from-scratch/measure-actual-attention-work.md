# Video lesson — What an attention-work counter tells us

**Bits to Banking · Umicom Foundation**  
**Author and narrator:** Sammy Hegab

## Narration

Performance discussions often start with an exciting ratio. A full-context decoder processes many query rows, but incremental generation needs the newest query for each layer. Does removing earlier rows make the language model twice as fast? The answer depends on the implementation and the measurement boundary.

Consider a six-token context with two layers, a two-token prompt and seven generated tokens. The canonical initial trace executes twelve token-layer rows. Four incremental appends execute eight more queries in total: one per layer at each append. Two full-window rollovers execute twenty-four token-layer rows. That is forty-four observed attention-query rows versus eighty-four for the full-context reference policy.

But the newest query still reads its historical K/V memory. The code still performs matrix projections, normalisation, residual operations, feed-forward work, sampling and allocation. As the prefix approaches its context limit, cache bandwidth and allocation costs may dominate. The measured end-to-end result can be smaller, unchanged or worse than the old implementation.

For a reproducible benchmark, identify the compiler, optimisation level, actual CPU, checkpoint identity, input prompt, context size, number of generated tokens, rollover count and timing convention. Report time to first token separately from later token gaps. A good benchmark is not a story about optimisation. It is a carefully defined observation.

## Visual storyboard

1. Draw the active query as a single row and the historical K/V as a retained matrix.
2. Show the shape and index invariants using the concrete example from the narration.
3. Compare reference and incremental paths with identical inputs and checkpoint identity.
4. Conclude with the difference between tested numerical behaviour and measured execution speed.
