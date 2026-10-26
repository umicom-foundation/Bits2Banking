# Multi-layer K/V storage — a complete learning path

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

This reading route connects the native Framework's real bounded cache **storage** owner with the separate mathematical proofs still needed for fast Transformer **inference**. It contains education only; all C23 implementations, regression tests and dataset controls belong to Umicom Framework.

## Learn the required foundation

Start with [prefix invariance](162-causal-prefix-growth-and-hidden-state-invariants.md), [upper-layer history dependence](179-recognise-upper-layer-history-divergence.md), and [the independent KV proof matrix](184-define-the-independent-proof-matrix-for-kv-caching.md). Those lessons explain why causal growth and rolled-window inference have different correctness requirements.

## Work with the native K/V owner

### Lifetime and initial rows

- [Lesson 185: Own K/V Rows for Each Transformer Layer](185-own-k-v-rows-for-each-transformer-layer.md)
- [Lesson 186: Separate Cache Storage From Decoder Mathematics](186-separate-cache-storage-from-decoder-mathematics.md)
- [Lesson 187: Prefill Every Layer as One Transaction](187-prefill-every-layer-as-one-transaction.md)
- [Lesson 188: Append a Token While Positions Stay Fixed](188-append-a-token-while-positions-stay-fixed.md)
- [Lesson 189: Refuse Silent Eviction When the Context Is Full](189-refuse-silent-eviction-when-the-context-is-full.md)
- [Lesson 190: Rebuild the Entire Window After Rollover](190-rebuild-the-entire-window-after-rollover.md)

### Validation, identity and data layout

- [Lesson 191: Verify the Shifted Token Sequence](191-verify-the-shifted-token-sequence.md)
- [Lesson 192: Pin a Cache to a Checkpoint Identity](192-pin-a-cache-to-a-checkpoint-identity.md)
- [Lesson 193: Reject Non-Finite Projection Values](193-reject-non-finite-projection-values.md)
- [Lesson 194: Measure Stored Token-Layer Work](194-measure-stored-token-layer-work.md)
- [Lesson 195: Keep Queries, Keys and Values Distinct](195-keep-queries-keys-and-values-distinct.md)
- [Lesson 196: Read the Layer-Major K/V Layout](196-read-the-layer-major-k-v-layout.md)

### Numerical acceptance and regression

- [Lesson 197: Prove Numerical Parity Before Using Cached Attention](197-prove-numerical-parity-before-using-cached-attention.md)
- [Lesson 198: Explain Upper-Layer History Dependence](198-explain-upper-layer-history-dependence.md)
- [Lesson 199: Plan a Fair K/V Performance Experiment](199-plan-a-fair-k-v-performance-experiment.md)
- [Lesson 200: Run the Native Multi-Layer K/V Owner Regression](200-run-the-native-multi-layer-k-v-owner-regression.md)

### Model changes, cancellation and future qualification

- [Lesson 201: Invalidate Cache State After a Model Update](201-invalidate-cache-state-after-a-model-update.md)
- [Lesson 202: Understand Reset and Cancellation](202-understand-reset-and-cancellation.md)
- [Lesson 203: Protect the Memory Boundary on Every Read](203-protect-the-memory-boundary-on-every-read.md)
- [Lesson 204: Define the Acceptance Gate for True Incremental Inference](204-define-the-acceptance-gate-for-true-incremental-inference.md)

## Use the HTML course

Open [the browser-based native K/V learning path](../../courses/llm-from-scratch/kv-cache-learning-path.html) or [the complete HTML continuation catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The browser course does not execute native software.

## What is still required before an acceleration claim?

A future backend must produce K/V rows using the authoritative trained model, independently match every relevant canonical decoder logit, handle the first and repeated evictions without history mismatch, and demonstrate measured speed on representative hardware. Neither stored row counts nor unsigned checkpoint digests satisfy those requirements by themselves.

*Service to Many Leads to Greatness.*
