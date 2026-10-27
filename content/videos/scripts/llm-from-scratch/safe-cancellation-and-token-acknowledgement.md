# Video lesson — Safe cancellation and token acknowledgement

**Bits to Banking · Umicom Foundation**  
**Narration and storyboard:** Sammy Hegab

## Opening and visualisation

Introduce a bounded native model with a caller-serialised training tape. The scheduler is only the outer coordinator; the model remains the authority for all numerical work. A request holds a scheduler ticket before admission and a distinct pool lease after admission.

## Demonstration sequence

Animate three cancellations. Waiting cancellation clears metadata; ready cancellation releases the K/V lease; in-flight cancellation returns BUSY until the caller has stopped that step. If a model call fails before committing any change, ReturnUncommitted sends the quantum back to ready without counting a token.

## Conclusion and learner check

Emphasise that retry is unsafe after partial sampling or K/V append, because the scheduler cannot roll back another module. Finish by displaying the source-header convention and the requirement to preserve existing implementations when extending the Framework.

## Accessible learning notes

A readable screen layout, subtitles, this text transcript and accessible colour contrast can help learners compare distinct operations. Model execution and admission are separate concepts and queue operations do not perform neural arithmetic. Any numerical times shown as examples must be interpreted as hypothetical rather than benchmark results. The Orca and vLLM research studies provide broader context, not evidence of Umicom performance.

## Review exercise

Ask viewers to explain which state changes when a waiting request is admitted and why an in-flight cancellation cannot safely free the K/V lease without application cooperation.
