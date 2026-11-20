<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/09-test-the-runnable-jar.md

PURPOSE:
  Build, inspect and test the Java archive that an application will ship.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test the runnable JAR

A Java archive can carry compiled class files and a manifest. The manifest tells the Java runtime which class to start when you run the archive. In this lab, compile a practice application and check the same archive you would hand to another user.

## Setup recap

Use a writable exercise directory, an Umicom Command build with the Java Console Application recipe, CMake, Ninja and a supported JDK. Set JAVA_HOME to that JDK. Run java -version and javac -version and confirm both are from your selected installation. Create a project named **Journal Check** with target journal_check in a new folder. The starter prints its name and uses synthetic data only.

## 1. Compile and run the archive

Open the generated folder and confirm that src/Main.java contains the top-level main method. Run each command separately and stop if a step fails.

~~~powershell
umicom make --source . --preset windows-ucrt64-debug
umicom build --source . --preset windows-ucrt64-debug --target run-program
jar tf build/windows-ucrt64-debug/bin/journal_check.jar
java -jar build/windows-ucrt64-debug/bin/journal_check.jar
~~~

On Linux substitute linux-debug for the preset and folder name. The listing contains Main.class and META-INF/MANIFEST.MF. The final command prints **Journal Check** on one line. The CTest output check runs this JAR and considers the text, exit status and standard error.

## 2. Change one thing and recompile

1. In the practice source change the printed text to **Journal Draft**. Leave the expected output in the generated CMake file alone.
2. Run the make command again. Expect compilation to succeed and the console test to show a difference between the expected and actual text.
3. Restore the original text and repeat the command. Confirm the test passes before previewing the Runtime stage.

~~~powershell
umicom install --build build/windows-ucrt64-debug --prefix stage --component Runtime --dry-run
~~~

The preview prints the staging action. It creates no stage directory. A later install copies the tested JAR into the chosen directory. The recipient needs a compatible Java runtime.

## Exercise and explanation

Run the old JAR after editing the source but before rebuilding. Write down why it still prints the original text. Then run the rebuilt JAR and compare its output with the test. If a run fails before printing, inspect the JDK selection and manifest. If the program prints different text and exits successfully, inspect the test's expected output.

## Source for this lesson

Read how the recipe points the run, test and Runtime actions to one archive. [Java console recipe in Umicom Framework](https://github.com/umicom-foundation/umicom-framework/blob/main/src/developer_project/templates/java_console.c)

[Course contents](index.md) · [Previous lesson](08-read-a-test-failure-and-recompile.md) · [Next lesson](10-check-a-c-java-translation.md)
