<!--
Umicom Bits2Banking
File: content/simple-steps/apply/building-bitcoin-in-c.md

PURPOSE:
Give learners an additional practical case for Building Bitcoin from Scratch Using Assembly and C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Draw a standard header byte map

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice team needs a paper map for an offline 80-byte Bitcoin header reader. It will check a time and nonce field.

1. Write the six header field sizes in order using Scope, bytes and compatibility. Mark each starting offset by adding prior sizes.
2. Mark the two four-byte scalar ranges the planned reader will inspect. Confirm their last byte indexes remain inside the header.

**Check your result.** Time starts at byte 68 and occupies 68–71. Nonce starts at 76 and occupies 76–79. All six field lengths sum to 80.

[Step-by-step course guide](../course-guides/building-bitcoin-in-c.md) · [Full course](../../courses/building-bitcoin-in-c/index.html) · [Small projects by course](index.md) · [First practice case](../practice/building-bitcoin-in-c.md)
