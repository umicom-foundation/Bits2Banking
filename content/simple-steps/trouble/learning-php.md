<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-php.md

PURPOSE:
Give learners an additional practical case for Learning PHP.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Count bytes at a storage boundary

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A two-column practice worksheet labels every length as characters. Its UTF-8 sample is café and the storage limit is four bytes.

1. In the text-boundary lesson, compare encoded length with the count of letters a reader sees. Write both values for the sample.
2. Apply the four-byte storage limit to the encoded value. Keep the result separate from any display label length.

**Check your result.** The sample has four letters and five UTF-8 bytes. The four-byte storage rule refuses it.

[Step-by-step course guide](../course-guides/learning-php.md) · [Full course](../../courses/learning-php/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-php.md)
