<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/30-admit-every-active-record.md

PURPOSE:
Admit every active record before returning a match

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

# Admit every active record before returning a match

## A successful comparison is not complete admission

Suppose the first row is LAB.A and the second row has a symbol with no terminating zero. An early-return search can find LAB.A and report success while the retained catalogue is malformed. A later consumer may inspect the damaged row and encounter a different result. Shared admission checks the complete active catalogue first.


## Read the validation sequence

- Check that the count fits the fixed array before it controls a read.
- Validate each active instrument using the existing canonical instrument validator.
- Reject repeated active identifiers.
- Only then search for the requested identity or decide whether an insertion is a duplicate.
- Publish an output or append a staged record only after admission succeeds.


The validator checks the stored instrument contract, including terminated identifier, symbol and venue fields, a valid currency and a finite positive multiplier. This establishes a structurally usable catalogue. It does not establish that a venue recognizes the instrument, that prices are current or that trading is permitted.


## Keep inactive storage separate

Initialization resets the active count. It need not erase every unused record. Only the active prefix participates in admission, so old bytes beyond the count do not reject an otherwise valid empty list. Appending overwrites the destination with an admitted value.


## Preserve observable result precedence

| Condition | Result |
| --- | --- |
| Count above array capacity | INVALID_ARGUMENT |
| Malformed active record or repeated retained identity | INVALID_STATE |
| Valid full list, existing identity | ALREADY_EXISTS |
| Valid full list, new identity | CAPACITY_EXCEEDED |


## Study the watchlist scenario

The installed lab first inserts two valid synthetic instruments, then deliberately damages the later record. Lookup of the first identity and duplicate insertion must both refuse. A complete byte copy checks that refusal changed no storage. This controlled fixture uses a public caller-owned structure; it is not a pattern for editing an opaque application owner.


## Exercise and answer

Does checking only the requested row catch duplicate retained identities elsewhere? No. Complete admission must inspect the entire active set. With a fixed small capacity, the current implementation uses a bounded pairwise identity comparison. Any future indexing optimization must preserve the same admission and result contracts.

## Complete source and qualification commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md and identity_lifetime.c. Compilation, installed SDK linking and execution remain separate qualification steps.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/30-admit-every-active-record.html)
