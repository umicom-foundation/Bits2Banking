# Video lesson — Reconcile queue counts and physical KV memory

**Bits to Banking · Umicom Foundation**  
**Narration and storyboard:** Sammy Hegab

## Opening and visualisation

Begin with units. There are two K/V matrices per layer, one storage row per token and four bytes per FP32 element. On screen compute 2×2 layers×4 positions×8 channels×4 bytes = 512 bytes per store.

## Demonstration sequence

A raw K/V budget of 1,024 bytes can hold two stores. Display a table for requests A, B and C: waiting, ready, in-flight, active K/V bytes and idle bytes. The number of live requests equals waiting plus ready plus in-flight. When A completes under idle retention, the category of 512 bytes changes without shrinking physical memory.

## Conclusion and learner check

Finish by deriving effective admission upper bound min(request slots, pool slots, floor(budget/store bytes)) and explaining why an observed rate cannot be inferred from counters alone.

## Accessible learning notes

A readable screen layout, subtitles, this text transcript and accessible colour contrast can help learners compare distinct operations. Model execution and admission are separate concepts and queue operations do not perform neural arithmetic. Any numerical times shown as examples must be interpreted as hypothetical rather than benchmark results. The Orca and vLLM research studies provide broader context, not evidence of Umicom performance.

## Review exercise

Ask viewers to explain which state changes when a waiting request is admitted and why an in-flight cancellation cannot safely free the K/V lease without application cooperation.
