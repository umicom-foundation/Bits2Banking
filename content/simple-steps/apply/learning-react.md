<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-react.md

PURPOSE:
Give learners an additional practical case for Learning React.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a parent total and a displayed summary in step

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local React board counts room inspections. The parent starts at 4 and has an Add inspection action.

1. Use the components lesson to pass the count down as a prop to a summary. Keep updates in the parent with the action handler.
2. Trace one activation and the next render. Read both the summary text and the parent’s stored count.

**Check your result.** The initial summary reads Inspections 4. One accepted action makes both the stored value and displayed total 5.

[Step-by-step course guide](../course-guides/learning-react.md) · [Full course](../../courses/learning-react/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-react.md)
