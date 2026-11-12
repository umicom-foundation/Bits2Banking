<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-maven/02-compile-test-and-package.md

PURPOSE:
Compile test and package a Java library

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Compile test and package a Java library

## Before you begin
Use the jvm-identity lab from the preceding lesson. Confirm that Maven reports a JDK capable of compiling Java 17 source. The first build may retrieve the pinned plugins and test dependencies from Maven Central; retain any resolution failure separately from a Java compiler error.

## Execute a lifecycle phase
~~~powershell
mvn test
mvn package
~~~

The test phase follows earlier required phases in Maven's default lifecycle. The package phase continues far enough to produce the library artifact. Read target/surefire-reports and confirm that BuildIdentityTest actually ran all three methods without failures, errors or skips. A successful build message with zero tests is not the expected result. This POM sets failIfNoTests to catch a completely missing test suite.

BuildIdentity preserves a component and version. One test checks the resulting string and both accessors. Two refusal tests require IllegalArgumentException for a missing component or blank version. Those cases test behaviour, rather than merely calling the constructor.

## Distinguish artifacts from source
The expected archive is target/jvm-identity-1.0.0.jar. It is a library, not an executable application with a Main-Class entry. Inspect it with the JDK jar tool:

~~~powershell
jar tf target/jvm-identity-1.0.0.jar
~~~

Expect the compiled BuildIdentity class and package directories. Test classes belong to test output; the normal library JAR should not contain BuildIdentityTest. Keep generated target files out of source commits.

## Exercise and recovery
Change the expected display string in one test, rerun test, and inspect the failing method in the report. Restore the expectation only after explaining the actual contract. Do not use a skip-tests flag to turn this exercise green. If compilation fails first, there is no new test result yet; old XML reports may remain from a previous successful run.

[Apache Maven lifecycle guide](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html) · [Surefire JUnit support](https://maven.apache.org/surefire/maven-surefire-plugin/examples/junit.html)

[Course contents](index.md) · [Previous lesson](01-read-a-project-model.md) · [Next lesson](03-dependencies-and-reproducible-evidence.md)
