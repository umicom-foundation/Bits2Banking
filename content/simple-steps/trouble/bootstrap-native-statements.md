<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/bootstrap-native-statements.md

PURPOSE:
Give learners an additional practical case for Bootstrap and Native Statement Reports.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reconnect an error with its form field

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A learner renames the error paragraph to amount-error. The correction input still describes itself using correction-error.

1. Read the input's aria-describedby attribute and the error paragraph's id in Display native validation feedback.
2. Set aria-describedby to amount-error in your practice copy. Read the input and paragraph in the browser inspector.

**Check your result.** The input is marked invalid and its description points to amount-error. The linked text says Enter a whole number of cents, such as -250 or 250.

[Step-by-step course guide](../course-guides/bootstrap-native-statements.md) · [Full course](../../courses/bootstrap-native-statements/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/bootstrap-native-statements.md)
