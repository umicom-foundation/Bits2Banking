<!--
Umicom Bits2Banking
File: content/simple-steps/check/bootstrap-native-statements.md

PURPOSE:
Give learners an additional practical case for Bootstrap and Native Statement Reports.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check both sides of the negative signed limit

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local FreeBASIC TryAddCents call receives -2147483647 as its left value. Use -1 and -2 in separate cases. Start each result at 42.

1. Calculate each sum in a wider temporary as shown in Display native validation feedback.
2. Write the result code and output value for each case using the signed 32-bit bounds.

**Check your result.** Adding -1 returns 1 and publishes -2147483648. Adding -2 returns 0 and leaves the output at 42.

[Step-by-step course guide](../course-guides/bootstrap-native-statements.md) · [Full course](../../courses/bootstrap-native-statements/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/bootstrap-native-statements.md)
