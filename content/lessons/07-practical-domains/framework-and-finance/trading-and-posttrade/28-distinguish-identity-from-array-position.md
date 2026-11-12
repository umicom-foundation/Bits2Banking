<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/28-distinguish-identity-from-array-position.md

PURPOSE:
Distinguish an instrument identity from its array position

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
<!-- The approved offline logo alias remains for compatibility review:
![Umicom](../../../../assets/branding/umicom-logo.svg)
New website manuscripts use the preferred supplied wordmark. -->
![Umicom](../../../../assets/branding/umicom-wordmark.svg)

# Distinguish an instrument identity from its array position

## Begin with two different questions

Which instrument is this? asks for identity. Where is its record stored right now? asks for position. A watchlist index answers the second question. Removing an earlier row can change that position without changing the instrument. A pointer into the array has the same lifetime problem.


## Trace a small owner

| Before removal | After removing LAB.A |
| --- | --- |
| Slot 0: LAB.A | Slot 0: LAB.B |
| Slot 1: LAB.B | Slot 1: LAB.C |
| Slot 2: LAB.C | Slot 2: inactive |


A retained index of 1 originally identified LAB.B. After removal it identifies LAB.C. The number is still inside the array, so a simple bounds check cannot detect this semantic error. Keep the stable identifier when a selection must survive edits, then resolve it against the current owner.


## Use a result within its lifetime

~~~c
size_t index = SIZE_MAX;
UmiStatus status = umi_watchlist_find(watchlist, "LAB.B", &index);
if (status == UMI_STATUS_OK) {
    UmiInstrument copy = watchlist->instruments[index];
    /* Use this copied value; do not retain index across list edits. */
    (void)copy;
}
~~~


The caller serializes access from lookup through the copy. Copying after a concurrent writer changes the array would still be unsafe. Framework does not turn a plain index into a lock or a durable database key.


## Read the installed example

Open identity_lifetime.c in the existing order-lifecycle laboratory. The query scenario copies a selected instrument immediately after successful lookup. The navigation scenario keeps identifiers across edits and asks the workspace to resolve them again. Neither client owns private workspace arrays.


## Exercise and answer

An interface caches slot 2 and then removes slot 0. Can it safely use slot 2 because the allocation still exists? No. The logical record moved, and the old tail is inactive. Preserve the identifier and obtain a fresh result, or keep a value snapshot with a clearly limited meaning.

## Complete source and qualification commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md and identity_lifetime.c. Compilation, installed SDK linking and execution remain separate qualification steps.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/28-distinguish-identity-from-array-position.html)
