<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-gradle/02-run-and-inspect-tests.md

PURPOSE:
Run and inspect Gradle tests

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Run and inspect Gradle tests

## Before you begin
Check that the lab can find an installed Java 17 toolchain. gradle.properties disables automatic toolchain download so a missing JDK produces a setup problem rather than silently provisioning a compiler. Read the selected Java installation in Gradle's diagnostics before changing the requested language version.

## Build the shared fixture
~~~powershell
gradle test
gradle build
~~~

The source and the three JUnit test methods are the same ones used by Maven. Inspect build/reports/tests/test/index.html and the XML under build/test-results/test. Confirm the number of tests and inspect any failure. The archive belongs under build/libs, while compiled classes and test output use other build subdirectories.

## Read incremental outcomes accurately
UP-TO-DATE means Gradle decided that an earlier output still satisfied its input tracking for that task. It does not mean the task executed again during this invocation. A run with all tasks skipped or up to date can be useful evidence, but it answers a different question from a fresh compiler execution.

~~~powershell
gradle test --rerun-tasks
~~~

Use a forced rerun when the exercise specifically requires new execution evidence. Do not make repeated forced rebuilds the default response to every unexplained problem; inspect inputs, reports and the source revision first.

## Exercise and recovery
Break the expected display string in BuildIdentityTest, run test and locate the failed assertion in the report. Restore it, rerun, and record both outcomes. Compare the method names with Maven's Surefire report. If no tests appear, verify the test filename, package, JUnit dependency and useJUnit configuration before claiming success.

[Gradle Java plugin test tasks](https://docs.gradle.org/current/userguide/java_plugin.html) · [Gradle JVM toolchains](https://docs.gradle.org/current/userguide/toolchains.html)

[Course contents](index.md) · [Previous lesson](01-projects-plugins-and-tasks.md) · [Next lesson](03-wrapper-and-native-boundaries.md)
