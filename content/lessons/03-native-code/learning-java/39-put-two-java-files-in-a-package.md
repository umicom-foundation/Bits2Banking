<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/39-put-two-java-files-in-a-package.md

PURPOSE:
Compile two related Java files and run the program from its compiled class folder.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Put two Java files in a package

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

A reading report has two Java files. Put them in a named package so both parts can be found when the program runs.

Start with [Keep a reading in a record](36-keep-a-reading-in-a-record.md). Use a JDK with Java 21 support, a text editor and PowerShell.

## 1. Create the folders

Open PowerShell in a new practice folder. Run this command.

```powershell
New-Item -ItemType Directory -Force src/training/readings, classes
```

Save [Reading.java](../../../labs/java-path/first-package/src/training/readings/Reading.java) and [ReadingReport.java](../../../labs/java-path/first-package/src/training/readings/ReadingReport.java) in `src/training/readings`. Both source files declare `package training.readings;`.

A package groups related types under a name. The dots in `training.readings` correspond to the two folder names `training/readings`.

## 2. Compile the two files

```powershell
javac --release 21 -d classes src/training/readings/Reading.java src/training/readings/ReadingReport.java
Get-ChildItem classes/training/readings
```

The `-d classes` option tells the compiler where to write its result. You should see `Reading.class` and `ReadingReport.class` under the package folders.

## 3. Run the report by its full name

```powershell
java -cp classes training.readings.ReadingReport
```

`-cp classes` makes `classes` the starting folder for the search. The full name combines the package and class. Java finds `training/readings/ReadingReport.class` inside that folder. The output is `North Office read 8`.

If Java reports that it cannot find the main class, check that you are in the practice folder, that both class files exist, and that you typed `training.readings.ReadingReport` with matching capitals.

## 4. Change one value and rebuild

In `ReadingReport.java`, change `8` to `12` and save. Repeat the two-file compile and then run the report. Expect `North Office read 12`.

[Compile a module](20-package-a-report-as-a-module.md) after you are comfortable finding and running a class in a named package.

[Previous lesson](38-make-a-choice-with-if.md) · [Next lesson](40-read-one-command-line-argument.md) · [Java course](index.md)
