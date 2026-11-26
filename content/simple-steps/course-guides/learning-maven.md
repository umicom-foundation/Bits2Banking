<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-maven.md

PURPOSE:
Provide practical first steps and a result to check for Learning Maven.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning Maven

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Open the Maven jvm-identity lab and find its artifact name and version in `pom.xml`. [Read a Maven project model](../../courses/learning-maven/lessons/01-read-a-project-model.html)
2. Run `mvn test`. Check `target/surefire-reports` for the three `BuildIdentityTest` methods. [Compile test and package a Java library](../../courses/learning-maven/lessons/02-compile-test-and-package.html)
3. Run `mvn package`, then `jar tf target/jvm-identity-1.0.0.jar`. [Compile test and package a Java library](../../courses/learning-maven/lessons/02-compile-test-and-package.html)

**Check your result.** All three tests pass, and the JAR contains `BuildIdentity` with the test class left in the separate test output.

[Continue in the full course](../../courses/learning-maven/index.html) · [All course guides](index.md)
