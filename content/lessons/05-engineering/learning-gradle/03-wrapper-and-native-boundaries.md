<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-gradle/03-wrapper-and-native-boundaries.md

PURPOSE:
Pin the build tool and preserve native boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Pin the build tool and preserve native boundaries

## Before you begin
Finish the two preceding lessons and record the installed Gradle version. This lab does not ship an unreviewed wrapper JAR. Generate a wrapper only from a trusted installed distribution, inspect the generated files and verify the distribution checksum against Gradle's official published value before sharing them.

## Understand the wrapper
The wrapper scripts select a configured Gradle distribution. They do not pin every dependency, the selected JDK, a native compiler or an installed Umicom SDK. A reproducible record therefore needs more than the wrapper version.

~~~powershell
gradle wrapper --gradle-version 9.9.1 --distribution-type bin
~~~

Review gradlew, gradlew.bat, gradle/wrapper/gradle-wrapper.jar and gradle-wrapper.properties together. The first wrapper invocation can download the selected distribution. Keep credentials out of distribution URLs. Consult the official wrapper guide for distributionSha256Sum and wrapper-JAR verification rather than inventing a checksum.

## Plan a native client
An Android or desktop Java client may eventually load a native C library. Keep the C service, Java native declarations, native-library packaging and target ABI as separate contracts. The same Java source compiling on a workstation does not establish that an Android device can load the corresponding library.

## Exercise
Create a table with four identities: Gradle distribution, JDK, Umicom Framework SDK and target architecture. For each, name the file or command that would supply evidence. Mark the Framework SDK and device cells not applicable for this pure-Java fixture, rather than inventing a successful native integration.

Expected conclusion: the wrapper answers which build tool starts; toolchain selection answers which compiler builds classes; the SDK and architecture describe a separate native boundary. Use this distinction in the later mobile and desktop application courses.

[Gradle wrapper guide](https://docs.gradle.org/current/userguide/gradle_wrapper.html) · [JVM toolchain guide](https://docs.gradle.org/current/userguide/toolchains.html)

[Course contents](index.md) · [Previous lesson](02-run-and-inspect-tests.md) · [Next lesson](04-read-task-outcomes-before-claiming-execution.md)
