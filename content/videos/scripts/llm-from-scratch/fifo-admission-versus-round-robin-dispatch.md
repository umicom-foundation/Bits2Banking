# Video lesson — FIFO admission versus round-robin dispatch

**Bits to Banking · Umicom Foundation**  
**Narration and storyboard:** Sammy Hegab

## Opening and visualisation

Opening scene: three learners arrive at a service counter labelled A, B and C. Each requests a different number of computation steps. The queue can accept all three even though the K/V pool has memory for only two active sessions. Show the K/V pool budget as a physical constraint, not a count of prompts or generated tokens.

## Demonstration sequence

First show the waiting FIFO sequence A, B, C. Call AdmitNext twice; A and B obtain leases. A third admission is refused by the pool but C remains queued. Next show Dispatch and Acknowledge for A, B, A, B. These are logical work grants: an independent decoder must actually commit a token before Acknowledge is appropriate.

## Conclusion and learner check

After the first pair completes, admit C. Overlay two separate diagrams, one for admission and one for dispatch. Contrast a fair sequence of work units with unequal execution durations: round robin does not promise equal milliseconds. End with the terms waiting, ready, dispatched, completed and lease released.

## Accessible learning notes

A readable screen layout, subtitles, this text transcript and accessible colour contrast can help learners compare distinct operations. Model execution and admission are separate concepts and queue operations do not perform neural arithmetic. Any numerical times shown as examples must be interpreted as hypothetical rather than benchmark results. The Orca and vLLM research studies provide broader context, not evidence of Umicom performance.

## Review exercise

Ask viewers to explain which state changes when a waiting request is admitted and why an in-flight cancellation cannot safely free the K/V lease without application cooperation.
