<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/nodejs-native-reporting.md

PURPOSE:
Give learners an additional practical case for Node.js and Native Statement Reports.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Identify an empty response before parsing

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The local producer returns success with an empty standard output in a training case.

1. Record its exit status and output length separately. Identify which piece of evidence is missing from the adapter’s report contract.
2. Compare the result with the documented valid snapshot before feeding either one to a display.

**Check your result.** The empty response has no complete report. The valid snapshot can be parsed and displayed.

[Step-by-step course guide](../course-guides/nodejs-native-reporting.md) · [Full course](../../courses/nodejs-native-reporting/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/nodejs-native-reporting.md)
