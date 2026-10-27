# Video lesson — Building a native scheduling test matrix

**Bits to Banking · Umicom Foundation**  
**Narration and storyboard:** Sammy Hegab

## Opening and visualisation

Open with the difference between model parity and queue validity. Numerical tests must compare the canonical decoder against the incremental decoder. Scheduling tests instead compare exact request order, lease validity, pool allocation counters and state transitions.

## Demonstration sequence

Walk through a fixture A:2, B:2, C:1 with only two K/V stores. Verify submission sequence, full-pool rejection, alternating dispatch and eventual admission of C. Add a test for a stale ticket after slot reuse and a separate cross-owner ticket test. Use distinct headings for isolated test doubles and complete Framework qualification.

## Conclusion and learner check

Close with evidence reporting: GCC and Clang strict compilation, native CTest, sanitizer checks and the still-required Windows integration tests. Never invent a performance gain from a lower queue depth or a reduced attention-row count.

## Accessible learning notes

A readable screen layout, subtitles, this text transcript and accessible colour contrast can help learners compare distinct operations. Model execution and admission are separate concepts and queue operations do not perform neural arithmetic. Any numerical times shown as examples must be interpreted as hypothetical rather than benchmark results. The Orca and vLLM research studies provide broader context, not evidence of Umicom performance.

## Review exercise

Ask viewers to explain which state changes when a waiting request is admitted and why an in-flight cancellation cannot safely free the K/V lease without application cooperation.
