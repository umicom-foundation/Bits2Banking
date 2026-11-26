<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-rust.md

PURPOSE:
Give learners an additional practical case for Learning Rust.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# End the borrow before changing the list

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice Vec owns titles Cedar and Elm. The caller borrows the first title, pushes Pine, then tries to use the earlier borrow.

1. Mark the lifetime of the borrowed title in the course’s borrow exercise. Identify the mutation inside that lifetime.
2. Use the borrowed title before pushing Pine. In the scratch trace verify that the original borrow is no longer used afterward.

**Check your result.** The printed earlier title is Cedar. The list then contains Cedar, Elm and Pine in order without retaining the earlier borrow across the push.

[Step-by-step course guide](../course-guides/learning-rust.md) · [Full course](../../courses/learning-rust/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-rust.md)
