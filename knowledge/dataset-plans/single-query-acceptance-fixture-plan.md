# Proposed dataset plan — Single-query attention acceptance fixtures

**Purpose:** Specify tiny deterministic synthetic evaluation data for a future Framework C23 regression suite.  
**State:** Proposal only; **no raw training dataset, checkpoint, production test or numerical kernel** is bundled here.  
**Owner:** Umicom Foundation · **Training permission:** Not assessed (not designed for training).

| Fixture ID | Controlled inputs | Required observation | Intended rejection / boundary |
| --- | --- | --- | --- |
| SQ-001 | `H=1,D=2,T=2`; known Q/K/V in Lesson 235 | One attention vector and full canonical-row parity | Reject physical row outside valid `T` |
| SQ-002 | Two heads with distinct tags | Head order survives concatenation | Detect swapped head/token stride |
| SQ-003 | Scores `[1000,999]` with finite values | Stable, normalised finite result | No direct exponent overflow |
| SQ-004 | Capacity `4`, valid length `2` | Garbage changes in unused slots do not change answer | Catch padded-row over-read |
| SQ-005 | Mask all rows | Defined rejection and unchanged output/session | No zero-denominator publication |
| SQ-006 | Prompt `P=2`, capacity `C=4`, `G=6` appends | First 2 eligible appends then 4 rebuilds | Learned-position rollover boundary |
| SQ-007 | Same dimensions, different frozen checkpoint bytes | Cache-identity refusal | Reject misleading shape compatibility |
| SQ-008 | Too-short output buffer after candidate sampling | Cache, history and sampler state unchanged | Failure-atomic retry |
| SQ-009 | Layer counts 1, 2 and 3 | Every output logit compared per generation step | Catch upper-layer propagation drift |
| SQ-010 | Generated tokens 10+ with seeded sampler | Reproducible candidate and reference replay | First and repeated evictions |

For each actual execution, capture build SHA, compiler, model identity and provenance, prompt IDs, shapes, masks, position policy, precision, tolerance formula, first divergent location, cache-version transitions and measured work counters. Maintain independent reference outputs and document every permitted numeric tolerance. A synthetic test that passes in isolation is not evidence of integration in the complete Windows Framework checkout.
