<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/fpml-for-treasury/01-read-the-two-legs.md

PURPOSE:
Follow payer, receiver, currency and rate terms before opening a schema.

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

# Read the Two Sides of a Swap

[Course contents](index.md) · [Next lesson · Read and Validate the Import Boundary](02-read-the-import-boundary.md)

Follow payer, receiver, currency and rate terms before opening a schema.

## Draw the agreement

A swap is an agreement to exchange calculated payment flows. Each side of that calculation is called a leg. For this exercise, Cedar pays a fixed rate and Birch pays a rate that follows a floating index. A notional amount supplies the base for the calculation. The example makes no exchange of notional principal.

~~~text
Cedar  -- fixed 4.25% on USD 100,000 -->  Birch
Cedar  <-- floating training index ----  Birch
~~~

FpML means Financial products Markup Language. It is a standard maintained by ISDA for representing financial product terms and related processes. A confirmation documents the terms agreed between parties. The standard has different views for different processes, so identify the view and version before selecting a schema.

## Read a small teaching record

XML gives each piece of data a named element. Read the text between each pair of tags. The urn:bits2banking namespace marks this shortened record as a local teaching format. Use the pinned FpML 5.13 Recommendation 2 source to look up official confirmation structures.

~~~xml
<trainingSwap xmlns="urn:bits2banking:training-swap" tradeId="TRN-401">
  <notional currency="USD">100000.00</notional>
  <fixed payer="Cedar" receiver="Birch">4.25</fixed>
  <floating payer="Birch" receiver="Cedar">TRAINING-INDEX</floating>
</trainingSwap>
~~~

## Work it out

1. Copy the four party roles in order. Check that the direction reverses between the fixed and floating legs.
2. Circle the currency and record it beside the notional. Then convert 4.25 percent to 425 basis points. One basis point is one hundredth of one percentage point.
3. Make a second copy with Cedar as both payers. Mark the two legs as a contradiction in this exercise and leave the accepted example alone.

A complete interest calculation would also need dates, schedules, day-count conventions and actual index observations. This short record gives enough information to practise import and role checking.

## Sources

- [ISDA FpML 5.13 Recommendation 2, build 8 notice](https://www.fpml.org/latest_news/isda-has-republished-the-recommendation-for-fpml-version-5-13-build-8/)
- [ISDA FpML specifications and views](https://www.fpml.org/the_standard/)

[Browser edition](../../../courses/fpml-for-treasury/lessons/01-read-the-two-legs.html)

