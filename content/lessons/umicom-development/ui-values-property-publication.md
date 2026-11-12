<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/ui-values-property-publication.md

PURPOSE:
Publish a copied property without sharing caller storage

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Publish a copied property without sharing caller storage

## Give each record a clear owner

A property bag owns a collection of named UI values. It is useful for application presentation because a caller can prepare a value, publish it once and then reuse its own storage. The bag does not retain a pointer into the caller's stack. This lesson follows the publish and invalid-value scenarios to distinguish independent copies from accidental shared storage.


~~~c
UmiUiPropertyBag *properties = NULL;
UmiUiValue title;
UmiStatus status = umi_ui_property_bag_create(&properties);
if (status != UMI_STATUS_OK) return status;
/* The complete lab checks setters and destroys properties on every exit. */
status = umi_ui_value_set_string(&title, "Accepted title");
if (status == UMI_STATUS_OK)
    status = umi_ui_property_bag_set(properties, "title", &title);
~~~


After successful publication, the lab changes the caller's title to Caller changed. Reading the bag must still produce Accepted title. Compare the two addresses conceptually: one record belongs to the caller; the other lives inside Framework's property owner. A copied observation returned by get is a third record, with its own lifetime.


## Reject a malformed replacement before publication

The invalid-value scenario deliberately changes the incoming kind to 99. The shared value validator rejects that discriminator. The bag returns INVALID_ARGUMENT, keeps its one property and does not advance the revision. The old title remains readable. This is a component-boundary exercise, not a pattern for constructing legitimate application data.


| Stage | Caller responsibility | Framework responsibility |
| --- | --- | --- |
| Prepare | Apply business and encoding policy | Construct owned values |
| Submit | Keep source readable during the call | Validate and copy before mutation |
| Observe | Interpret status and property kind | Return a separate observation |
| Release | End borrowers before owner destruction | Destroy the bag through its API |


## Understand what the mutex protects

The property bag serializes its own internal mutations. That does not make an external source record safe if another thread writes to it while publication copies it. Serialize access to caller-owned records as well. A lock inside one service cannot retroactively protect memory owned elsewhere.


The lab uses a cleanup label so failed checks still destroy a created bag. Inspect that path before adding another return statement. Cleanup is part of the example's behavior, not a cosmetic detail: a user guide should teach which function releases each resource and what happens when preparation fails halfway through.


## Practice a refusal-aware model update

Design a title-edit handler using a draft value and an accepted property. On success, show the accepted title. On refusal, retain the existing title and report the status beside the draft input. Write the control flow first; do not invent a new window layout for this exercise. Existing approved product layouts determine where the presentation belongs.


As a review question, explain why counting a logged setter call is weaker evidence than reading the property afterward. A call can be refused, a stored copy can be independent and a GUI can display an older snapshot. Qualify each boundary deliberately rather than assuming a successful input event proves the whole workflow.

## Source and practice

[UI value laboratory and owner commands](../../../labs/native/framework-ui-values/README.md) · [HTML edition](../../courses/umicom-development/lessons/ui-values-property-publication.html)

[Previous lesson](ui-values-aliased-text.md) · [Next lesson](ui-values-reactive-revisions.md) · [Course index](index.md)
