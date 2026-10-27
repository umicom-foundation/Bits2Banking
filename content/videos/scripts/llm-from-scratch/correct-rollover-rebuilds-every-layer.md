# Rollover is not shifting a ring buffer

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Format:** Narration and storyboard, approximately four minutes.

**Opening visual:** Show context `[40,41,42,43]` with token position labels 0,1,2,3 and the shifted context `[41,42,43,44]` relabelled 0,1,2,3.

**Narration (0:00–1:10):** “A bounded Transformer with learned absolute embeddings associates different numerical vectors with positions. After the oldest token leaves, survivors occupy new positions. Their projections and upper-layer histories may change even though the visible token IDs look familiar.”

**Visual proof (1:10–2:00):** Trace token 41 from position 1 before eviction to position 0 after eviction. Mark cached K/V from the earlier position as invalid for the new forward pass.

**Demonstration (2:00–3:10):** Try a malformed shift `[99,42,43,44]`. Show rejection without mutation. Then supply `[41,42,43,44]` together with all recomputed per-layer K/V rows. Observe a single atomic replacement.

**Narration (3:10–4:00):** “We are not claiming a faster cache just because we could rearrange memory. The canonical decoder is the numerical authority at every learned-position rollover.”

**Closing exercise:** Calculate how many token-layer rows must be rebuilt for three layers and eight context positions. Answer: 24.

*Service to Many Leads to Greatness.*
