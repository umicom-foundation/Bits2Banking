# Video lesson script — Why HMAC is not the same as a checksum

**Umicom Foundation · Written for learners · Sammy Hegab**

## Scene 1 — Narration and on-screen teaching

A checksum detects changed bytes. Its calculation is public and an attacker can recompute it.

## Scene 2 — Narration and on-screen teaching

A keyed MAC makes producing a matching tag depend on possession of a secret key; the secret should be unique to one enrolled worker and rotated under governance.

## Scene 3 — Narration and on-screen teaching

Check the corresponding RFC 4231 test vector before implementing the portable C23 helper.

## Scene 4 — Narration and on-screen teaching

Finish by separating message authenticity from worker authorisation and model quality.

## Visual and accessibility description

Use labelled text and an accessible transcript. Introduce each diagram through its underlying numbers before animation. Keep private learner data and credentials out of the illustrative screens.

## Reference

[Return to the public course route](../../../courses/llm-from-scratch/authenticated-federated-learning.html)
