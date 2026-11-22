<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/fpml-for-treasury/02-read-the-import-boundary.md

PURPOSE:
Trace a versioned XML document to a smaller record a treasury service can review.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom Foundation" width="220">
</picture>

# Read and Validate the Import Boundary

[Course contents](index.md) · [Previous lesson · Read the Two Sides of a Swap](01-read-the-two-legs.md) · [Next lesson · Check the Mapped Terms in C23](03-check-terms-in-c.md)

Trace a versioned XML document to a smaller record a treasury service can review.

## Separate structure from business rules

A namespace identifies a vocabulary. An XML Schema, often called an XSD, defines permitted structures in that vocabulary. A valid structure is one input to review. This lab also checks that the parties are distinct, the legs reverse, the currency matches the import box, and the trade reference has not changed meaning.

~~~text
1. Save the source identity with the approved parser's fixture.
2. Select the namespace, pinned version and confirmation view.
3. Validate the document against the approved local schema.
4. Map the terms and check the narrower training rules.
5. Compare the id and version with the accepted record.
6. Return a candidate or a review result.
~~~

An adapter is the small piece of software that connects different representations. A production XML adapter needs a maintained parser, a local schema pack and explicit limits on document size and nesting. Configure the parser so an exercise cannot fetch external resources. The project receives an already checked record and keeps the original confirmation identity for review.

## Decide what to do with a repeat

- First appearance of TRN-401 revision 1, all fields valid. Create one candidate record.
- Second appearance of TRN-401 revision 1 with identical terms. Mark as duplicate and keep one candidate.
- Second appearance of TRN-401 revision 1 with a different fixed payer. Mark for review and leave the first record intact.
- TRN-401 revision 2 with changed terms. Send to the proposed amendment review path. Production amendment semantics belong to the agreed business process.

An idempotent operation has the same effect after one application or after a repeat with the same valid identity and content. A delivery count can increase even when the number of saved trades stays at one.

## Connect the review to treasury and trading

In a TMS practice screen, show the normalized trade id, currency, both leg directions and the current review state together. Keep accepted records separate from any new candidate. A Trader practice importer can use the same terms for an exposure display once the terms have been reviewed.

- [Introduction to Treasury Management Systems](../../../courses/introduction-to-treasury-management-systems/index.html)
- [Learning XML](../../../courses/learning-xml/index.html)
- [ISDA FpML 5.13 Recommendation 2, build 8 notice](https://www.fpml.org/latest_news/isda-has-republished-the-recommendation-for-fpml-version-5-13-build-8/)

[Browser edition](../../../courses/fpml-for-treasury/lessons/02-read-the-import-boundary.html)

