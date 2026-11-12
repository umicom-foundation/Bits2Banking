<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/ui-values-reactive-revisions.md

PURPOSE:
Keep reactive observations readable when revisions are exhausted

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Keep reactive observations readable when revisions are exhausted

## Use revisions as accepted-change identities

The reactive store maps paths to values and records a revision for the owner and each changed row. An accepted put advances the owner and changed row once. A failed put must not create an apparent new observation. This is why counters used as identities need a defined policy at their maximum value instead of ordinary unsigned wraparound.


Open ShowRevision in the lab. It creates and initializes a heap-allocated store, publishes ready under status, then injects UINT64_MAX into the public record for an isolated boundary exercise. That direct assignment is a fixture technique. Production clients must not edit a live revision to bypass admission or to make a failed update look new.


~~~c
UmiUiValue observed;
UmiStatus status = umi_ui_reactive_observable_store_get(
    store, "status", &observed);
if (status != UMI_STATUS_OK) {
    /* Preserve the current presentation and report the refused lookup. */
}
~~~


## Separate reading from changing state

At the revision limit, another put returns CAPACITY_EXCEEDED, while get remains available. The lab must still observe ready. The value and owner revision are preserved. Preventing another write does not require destroying the last accepted evidence or making the application blank.


| Boundary | Expected behavior | Reason |
| --- | --- | --- |
| Last available revision | One accepted put reaches UINT64_MAX | Use the remaining identity exactly once |
| Revision exhausted | Refuse further puts | Do not recycle an observation identity |
| Rows full | Existing row can be replaced | Replacement does not need another slot |
| Malformed active row | Refuse access with INVALID_STATE | Do not index or compare damaged owner data |


The store has 256 bounded rows and no internal mutex. Allocate large records deliberately and serialize the complete operation in the application model. Validating a count before lookup is necessary for memory safety, but it is not a lock against another thread changing the count immediately afterward.


## Make a recovery decision without hiding history

If a live owner exhausts its revision space, define how the application retires that owner and creates a new observation context. Shut down borrowers and preserve any required accepted state. Silently resetting the revision inside the same live instance can make cached observations appear current when they belong to an earlier sequence.


## Practice with the expected output

Run revision through the owner commands and compare all three observations: CAPACITY_EXCEEDED, readable value ready and the exact decimal maximum. A successful laboratory exit means these checks agreed. It does not qualify concurrent UI callbacks, persistence or a product restart. Write down which additional evidence a real application would need for those workflows.


For a design exercise, describe how a status panel could remain useful after writes are refused. Keep its accepted snapshot visible, separate the rejected draft from stored state and show a specific recovery action. Use the existing approved layout when wiring the model into a product; this console lesson defines state behavior rather than a new visual design.

## Source and practice

[UI value laboratory and owner commands](../../../labs/native/framework-ui-values/README.md) · [HTML edition](../../courses/umicom-development/lessons/ui-values-reactive-revisions.html)

[Previous lesson](ui-values-property-publication.md) · [Next lesson](ui-values-archive-admission.md) · [Course index](index.md)
