<!--
Umicom Bits2Banking
File: labs/build-tools/jvm-identity/README.md

PURPOSE:
Build and inspect one JVM fixture through two independent build tools.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# One JVM fixture with Maven and Gradle

This lab teaches build tools through one Java record and three JUnit tests. Java is the subject-specific boundary for the Maven and Gradle courses. It does not implement weight-management logic or duplicate Umicom Framework services.

## Prepare

Use an installed JDK 17, Maven 3.9 or a compatible later release, and Gradle 9.9.1 for the Gradle route. Run each command separately and stop when a command fails. The first build can download pinned plugins and dependencies from Maven Central. The lab does not install tools or publish artifacts.

From the Bits2Banking repository:

~~~powershell
Set-Location labs/build-tools/jvm-identity
java -version
javac -version
mvn -version
gradle --version
~~~

Maven uses its reported Java home; Gradle selects an installed Java 17 toolchain. Automatic Gradle toolchain download is disabled. A missing compiler needs setup, not a lower language setting chosen merely to hide the failure.

## Maven route

~~~powershell
mvn validate
mvn test
mvn package
jar tf target/jvm-identity-1.0.0.jar
~~~

Expect three tests in target/surefire-reports: identity preservation, missing component and blank version. The JAR is a library without a main entry point. It should contain BuildIdentity.class, not the test class. Package does not install an application.

## Gradle route

~~~powershell
gradle build --dry-run
gradle test
gradle build
~~~

Inspect build/reports/tests/test/index.html and build/test-results/test. Expect the same three tests. The library belongs in build/libs. A dry run is a task plan; UP-TO-DATE is reuse of prior output, not a newly executed test. Use gradle test --rerun-tasks for the course exercise that specifically needs a fresh observation.

## Compare and diagnose

Keep the source unchanged while comparing tools. Record source revision, actual Java installations, build-tool versions, complete command, exit code and report counts. A dependency-resolution failure precedes compilation. A compiler failure precedes a new test report. An assertion failure names behaviour that needs investigation. Existing output directories can contain reports from an earlier invocation.

The recipes and tests are authored. Maven and Gradle execution has not yet been qualified for this lab. Do not substitute a source-file inspection for those results. Neither route exercises JNI, an Android device or an installed Framework SDK.

Generated target, build and .gradle directories stay ignored. Review any generated wrapper scripts, properties and JAR as a separate source change; verify their origin and checksums using the official Gradle instructions.

[Learning Maven](../../../content/courses/learning-maven/index.html) · [Learning Gradle](../../../content/courses/learning-gradle/index.html)
