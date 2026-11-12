<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-gradle/04-read-task-outcomes-before-claiming-execution.md

PURPOSE:
Read task outcomes before claiming execution

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read task outcomes before claiming execution

Gradle can avoid work when declared inputs and outputs make reuse appropriate. Your report should distinguish a task that executed from one that was already up to date or restored cached outputs. A successful command does not always mean the tests executed again.

## Inspect the fixture

The JVM identity lab applies the Java plugin, requests a Java 17 toolchain and configures JUnit tests. Maven and Gradle share the Java sources but maintain separate output directories and build metadata. A Maven report cannot prove that Gradle discovered the tests.

The lab does not silently provide a downloaded wrapper. Use the reviewed Gradle version described in the lab README. If you add a wrapper later, review its files and origin as another source change. Automatic Java toolchain downloading is disabled in this fixture.

## Compare two runs

From labs/build-tools/jvm-identity:

~~~powershell
gradle --version
gradle test --info
gradle test --info
~~~

Run each command separately and inspect its exit status. Compare the test task outcome across the two runs. The second may be up to date. The official [build-cache guide](https://docs.gradle.org/current/userguide/build_cache.html) explains how task outputs can also be restored from a cache when enabled. Observe your actual result rather than predicting a cache hit.

## Request fresh execution for diagnosis

~~~powershell
gradle --no-build-cache --rerun-tasks test
~~~

This is a small diagnostic exercise, not an everyday instruction to rebuild everything. Inspect build/test-results/test/TEST-org.umicom.learning.BuildIdentityTest.xml and the HTML report under build/reports/tests/test. Expect the three declared JUnit tests when discovery and execution succeed.

In an experimental copy, change the expected component string in BuildIdentityTest.java. Repeat the diagnostic command. Expect a failing task and nonzero result. Preserve the report, restore the intended expectation and repeat. If a report is missing, investigate admission and discovery before reporting any passing count.

## Connect the evidence to native builds

Ninja's no-work result, Gradle's task outcomes and a matching Umicom C configuration record describe different mechanisms. None alone proves a fresh test execution or authenticates a binary. Keep the command, tool identities, source context, task outcome and current report together.

If reused output seems wrong, inspect whether the changed input was declared. Forcing every task to run can expose a symptom without repairing the missing dependency. A permanent rerun workaround is not a substitute for that diagnosis.

The Java fixture is a course-specific example. Maven and Gradle execution remains unqualified until those commands run in the selected environment; source review and native C tests do not supply JVM execution evidence.

[Course contents](index.md) · [Previous lesson](03-wrapper-and-native-boundaries.md)
