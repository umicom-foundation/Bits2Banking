<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-maven/03-dependencies-and-reproducible-evidence.md

PURPOSE:
Track dependencies and build evidence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Track dependencies and build evidence

## Before you begin
Keep one successful lab build and its console output. Open pom.xml and locate the junit dependency and the three build plugins. The test library is versioned separately from the compiler, test runner and archive plugins.

## Understand test scope
The junit dependency has test scope. It is available to compile and run tests, while the public BuildIdentity class needs only the Java platform. Keeping the test dependency out of the production API prevents callers from needing JUnit simply to use the library.

~~~powershell
mvn dependency:tree
mvn help:effective-pom
~~~

These diagnostic goals can themselves require plugin downloads. Compare the effective model with your authored POM: inherited defaults explain values that do not appear explicitly in the file. Do not copy the entire generated model back into the source POM as a repair.

## Separate package install and deploy
Package creates the local build artifact. Maven install adds an artifact to the local Maven repository; deploy publishes to a configured remote artifact repository. Neither is equivalent to installing a desktop application or deploying the Umicom OS. This lab needs package, not a remote publication step.

## Exercise
Record the Maven version, JDK home, source revision, plugin versions, dependency tree and three-test report. Copy the project to another scratch folder while keeping generated outputs out of the copy. Predict which downloads can be reused through the local Maven cache and which files must be rebuilt.

Expected conclusion: a cache can supply dependencies but does not establish that the second source tree passed its tests. An offline build succeeds only when every required dependency and plugin is already available. Keep network errors, missing artifacts and test failures as different observations.

## Connect a native client later
A future Java client of Umicom Framework should call a deliberately designed native boundary. A Maven JAR alone cannot prove C ABI compatibility, native-library discovery or correct ownership. Record the native SDK identity separately when adding that integration.

[Apache dependency guide](https://maven.apache.org/guides/introduction/introduction-to-dependency-mechanism.html) · [Maven lifecycle reference](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)

[Course contents](index.md) · [Previous lesson](02-compile-test-and-package.md) · [Next lesson](04-distinguish-verification-from-artifact-existence.md)
