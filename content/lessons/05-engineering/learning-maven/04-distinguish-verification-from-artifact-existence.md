<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-maven/04-distinguish-verification-from-artifact-existence.md

PURPOSE:
Distinguish verification from artifact existence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Distinguish verification from artifact existence

A JAR file left in a directory tells you that some operation created those bytes. It does not tell you whether the current sources passed their tests. This lesson uses the existing JVM identity fixture to keep lifecycle progress and evidence separate.

## Read the project first

Open labs/build-tools/jvm-identity/pom.xml. The project declares Java release 17 and explicit compiler, test and JAR plugin versions. Its JUnit dependency belongs to test scope. These are the versions declared by this lab, not a claim that every machine has them cached or that they are the newest releases.

Open BuildIdentityTest.java. It contains three tests: one checks component/version display, one rejects a missing component and one rejects a blank version. The expected exceptions are successful test outcomes when the required exception occurs.

## Run a verification workflow

From the lab directory, with the documented JDK and Maven available:

~~~powershell
mvn --version
mvn -B verify
~~~

Run the commands separately and stop if either fails. The first establishes which Maven and Java runtime you selected. The second requests the lifecycle through verify. Maven executes the earlier phases required to reach it; packaging and tests are distinct parts of that sequence. See the official [lifecycle introduction](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html).

## Inspect evidence rather than the final line alone

1. Check the native process exit status immediately after Maven returns.

2. Open target/surefire-reports/TEST-org.umicom.learning.BuildIdentityTest.xml. Confirm the named tests and their outcomes rather than trusting an old filename.

3. Confirm that the report belongs to this invocation and selected checkout. Preserve earlier reports outside target before running experiments.

4. Inspect the packaged artifact only after interpreting the test result. An existing JAR does not override a failed verification command.

## Controlled failure exercise

In an experimental copy, change the expected display text in preservesIdentity to a deliberately wrong value. Run mvn -B verify again. Expect the test phase to fail and a nonzero Maven result. Retain the failure report. Restore the intended expectation, review the change and run verification again.

Do not add skipTests to make the exercise green. Skipping the test changes the question being answered. The lab configures failIfNoTests so missing test discovery cannot quietly look like complete test evidence.

## Recovery and boundary

If dependencies are unavailable, preserve the resolver diagnostic and identify the unavailable coordinate. A network or cache failure is not a Java assertion failure. This course does not execute dependency downloads for you, publish artifacts, or replace Umicom's native C implementation. The JVM fixture exists to teach a requested build tool; Framework remains the reusable product boundary.

[Course contents](index.md) · [Previous lesson](03-dependencies-and-reproducible-evidence.md)
