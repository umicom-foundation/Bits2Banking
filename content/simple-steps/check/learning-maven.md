<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-maven.md

PURPOSE:
Give learners an additional practical case for Learning Maven.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the build phase required by a release record

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional POM binds a named training check ReportContract to Maven’s verify phase. The release checklist specifically requires that check.

1. Prepare one sample record for a successful package invocation and one for a successful verify invocation that reports ReportContract ran.
2. Check which lifecycle phases were requested in each and which report can substantiate the required check.

**Check your result.** The package record shows packaging only for this requirement. The verify record also substantiates ReportContract.

[Step-by-step course guide](../course-guides/learning-maven.md) · [Full course](../../courses/learning-maven/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-maven.md)
