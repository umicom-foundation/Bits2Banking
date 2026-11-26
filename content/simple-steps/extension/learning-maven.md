<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-maven.md

PURPOSE:
Give learners an additional practical case for Learning Maven.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a test helper out of application runtime

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch POM lists a library whose only use is making assertions in test classes.

1. Mark the library with Maven’s test scope and classify it in the project’s test compile and test runtime classpaths.
2. Review the declared scopes for the normal application runtime and check that it does not need that helper.

**Check your result.** The helper belongs to test compile and test runtime. It has no entry on the application’s normal runtime classpath for this fixture.

[Step-by-step course guide](../course-guides/learning-maven.md) · [Full course](../../courses/learning-maven/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-maven.md)
