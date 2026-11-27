<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/41-choose-a-report-period-with-switch.md

PURPOSE:
Show how a Java switch expression chooses a result from a command-line word.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Choose a report period with switch

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

A report tool may ask you to choose daily or weekly output. In this exercise, one word selects the report heading.

Start with [Read one command-line argument](40-read-one-command-line-argument.md) and use the same JDK and practice folder.

## 1. Save and compile the class

Save [ReportPeriod.java](../../../labs/java-path/ReportPeriod.java) in your practice folder. Open PowerShell in that folder.

```powershell
javac --release 21 ReportPeriod.java
```

You should see a new `ReportPeriod.class` file.

## 2. Choose the report period

```powershell
java ReportPeriod daily
java ReportPeriod weekly
$LASTEXITCODE
```

The first run prints `Daily report.` The second prints `Weekly report.` The exit code is 0.

`switch` reads the first argument. Each `case` names a word and the arrow points to the value that word selects. The program stores the chosen value in `heading` and prints it once.

## 3. Check the default choice

```powershell
java ReportPeriod monthly
$LASTEXITCODE
```

You should see `Choose daily or weekly.` and exit code 2. `default` supplies an empty heading when no case matches. The following `if` detects it and reports the problem. Try the command without a period and check that it also returns 2.

If Java cannot find `ReportPeriod`, return to the folder that contains `ReportPeriod.class`. The choices are written in lower case. Use `weekly` when you want that match.

## 4. Read the choice as pseudocode

```text
If exactly one word was given:
    Select a heading using daily or weekly.
    Use an empty heading for an unknown word.
Otherwise, use an empty heading.
If the heading is empty, show the choices and return exit code 2.
Print the heading.
```

In C23, a `switch` can select on a whole-number code. When the input is text, you can compare it first and assign the corresponding code. The same input and expected output can be used to check both implementations.

[Previous lesson](40-read-one-command-line-argument.md) · [Next lesson](42-sort-readings-with-comparator.md) · [Java course](index.md) · [Java language reference for switch expressions](https://docs.oracle.com/javase/specs/jls/se21/html/jls-15.html#jls-15.28)

