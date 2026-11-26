<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/introduction-to-calypso-api-development.md

PURPOSE:
Provide practical first steps and a result to check for Introduction to Calypso API Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Introduction to Calypso API Development

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Draw a trade lookup with three boxes for the caller, the lookup interface and the repository that supplies the record. [A service boundary before an API call](../../lessons/09-treasury-tms-calypso/introduction-to-calypso-api-development/01-a-service-boundary-before-an-api-call.md)
2. Save the fake repository example as `TradeLookupLesson.java`. Type `javac TradeLookupLesson.java`, then `java TradeLookupLesson`. [A Java port and a fake repository](../../lessons/09-treasury-tms-calypso/introduction-to-calypso-api-development/02-a-java-port-and-a-fake-repository.md)
3. Change the lookup number from 42 to 43. Compile and run again using the fake repository. [A Java port and a fake repository](../../lessons/09-treasury-tms-calypso/introduction-to-calypso-api-development/02-a-java-port-and-a-fake-repository.md)

**Check your result.** The first run prints `42 GBP`. The second reports `Trade not found`.

[Continue in the full course](../../courses/introduction-to-calypso-api-development/index.html) · [All course guides](index.md)
