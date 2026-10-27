# Weight-space deltas, duplicates and local SGD

**Bits2Banking video narration and storyboard · Sammy Hegab · Umicom Foundation**

## Learning outcome

Explain the demonstrated concept using synthetic data and reproduce the numerical example. No illustrated screen is evidence of an implemented remote training network.

## Narration timeline

00:00–01:30: Calculate +0.029 from three genuine synthetic worker deltas. Annotate the sample-count denominator.

01:30–03:20: Replay a duplicate A submission, reject it and explain lost-ack delivery.

03:20–04:50: Cancel a pending worker; compare a missing sample with a valid zero delta.

04:50–06:10: Introduce local SGD steps versus communication rounds and explain why saved bytes are not a proof of faster convergence.

## Visual description and accessibility

Provide a caption for every on-screen equation and a transcript for each narration segment. Avoid colour-only distinctions between an accepted and a rejected worker. Clearly label any hardware/network metrics as illustrative unless they come from independent measurements.

## Closing question

Which piece of evidence would be required before calling this classroom operation genuine distributed learning?
