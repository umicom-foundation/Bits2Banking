<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-maven/01-read-a-project-model.md

PURPOSE:
Read a Maven project model

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read a Maven project model

## Before you begin
Install a supported JDK and Maven from their official distributions. Open the Bits2Banking checkout and locate labs/build-tools/jvm-identity. This lab deliberately uses Java 17 language features and an explicit compiler plugin; a Java runtime alone cannot compile it.

~~~powershell
Set-Location labs/build-tools/jvm-identity
java -version
javac -version
mvn -version
~~~

Record the Java home shown by Maven. If it differs from the JDK you intended, correct the shell environment before changing source. Run each command separately and stop on an error.

## Read the identity before the source
Open pom.xml. Its groupId, artifactId and version together name the library. The modelVersion describes the POM format; it is not the Maven executable version. The default namespace identifies Maven elements. BuildIdentity.java belongs under src/main/java/org/umicom/learning because its package declaration names that package.

~~~xml
<groupId>org.umicom.learning</groupId>
<artifactId>jvm-identity</artifactId>
<version>1.0.0</version>
~~~

Run mvn validate from the folder containing the POM. Success means the requested lifecycle phase completed; it does not prove that Java classes were compiled or that a test ran. The Apache POM guide explains the project model and inherited defaults.

## Exercise
Change only the version in a scratch copy to 1.0.1. Predict which source package names must change. Then run validate and compare the source tree with the original.

Expected conclusion: none of the Java package names change merely because the artifact version changed. Coordinates identify a distributable library; package names identify classes inside it. Keep those two identities separate when diagnosing an incorrectly selected dependency.

## Recover from a parse error
Temporarily omit one closing XML tag in the scratch copy. Read the first POM parsing diagnostic and its line number, restore the tag, and rerun validate. Do not bypass the malformed model by deleting the compiler or test configuration.

[Apache Maven POM guide](https://maven.apache.org/guides/introduction/introduction-to-the-pom.html)

[Course contents](index.md) · [Next lesson](02-compile-test-and-package.md)
