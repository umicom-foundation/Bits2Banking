<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-rust.md

PURPOSE:
Give learners an additional practical case for Learning Rust.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a borrowed label while making an owned report

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice Rust record owns the text Cedar, and a printable report needs a copy that can survive the original record.

1. Use the borrowing lesson to read the title temporarily and distinguish that borrow from an owned String in a report.
2. Make an owned copy for the report. End the original scope and trace which value can still be printed safely.

**Check your result.** The owned report print contains Cedar after the original record is gone. Its text is stored in the report.

[Step-by-step course guide](../course-guides/learning-rust.md) · [Full course](../../courses/learning-rust/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-rust.md)
