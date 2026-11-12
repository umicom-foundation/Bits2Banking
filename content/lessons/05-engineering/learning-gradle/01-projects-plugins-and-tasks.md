<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-gradle/01-projects-plugins-and-tasks.md

PURPOSE:
Read projects plugins and tasks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read projects plugins and tasks

## Before you begin
Use labs/build-tools/jvm-identity in Bits2Banking with an installed JDK 17 and a supported Gradle distribution. The course was authored against the Gradle 9.9.1 manual. Record your actual version; a newer manual is not evidence that an older local distribution supports every setting.

~~~powershell
Set-Location labs/build-tools/jvm-identity
gradle --version
gradle tasks --all
~~~

settings.gradle.kts names the project. build.gradle.kts applies the Java plugin, identifies the artifact and selects the installed Java toolchain. Kotlin is the configuration language here; the application fixture is Java. This explicit JVM teaching example does not replace native Framework services.

## Follow the graph
A task is a unit of build work. Dependencies between tasks express which work must happen first. The Java plugin contributes compilation, test and archive tasks; the project does not need to create equivalent tasks by hand.

~~~powershell
gradle build --dry-run
~~~

Read the scheduled task names. A dry run explains task selection without executing those tasks. It is not a compilation or test pass. Compare the graph with Maven's lifecycle phases from the companion course: both express build order, but a Gradle task name is not a Maven phase.

## Exercise
Locate the source and test directories used by both tools. Predict whether changing settings.gradle.kts changes the Java package declaration. Check the resulting archive basename after a real build in the next lesson.

Expected conclusion: project naming and Java package naming remain distinct. Keep the common source files intact so differences in observed outcomes can be investigated in build configuration, test execution or toolchain selection.

[Gradle Java plugin](https://docs.gradle.org/current/userguide/java_plugin.html)

[Course contents](index.md) · [Next lesson](02-run-and-inspect-tests.md)
