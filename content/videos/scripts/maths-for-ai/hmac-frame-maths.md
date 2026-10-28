# Video lesson script — Calculate the real size of a protected message

**Umicom Foundation · Written for learners · Sammy Hegab**

## Scene 1 — Narration and on-screen teaching

Start with the immutable 184-byte UMFW header and its 32-byte SHA checksum.

## Scene 2 — Narration and on-screen teaching

For a result containing two FP32 values, add eight bytes to obtain 224.

## Scene 3 — Narration and on-screen teaching

Add a 20-byte UMFA header and a 32-byte HMAC to obtain 276.

## Scene 4 — Narration and on-screen teaching

Explain why network RTT, TLS records and actual time-to-quality are not represented by this byte sum.

## Visual and accessibility description

Use labelled text and an accessible transcript. Introduce each diagram through its underlying numbers before animation. Keep private learner data and credentials out of the illustrative screens.

## Reference

[Return to the public course route](../../../courses/maths-for-ai/hmac-and-trust-mathematics.html)
