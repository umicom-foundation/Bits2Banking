<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/43-name-the-report-periods-with-an-enum.md

PURPOSE:
Use a Java enum to carry one of two known report periods.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Name the report periods with an enum

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

This practice report supports two periods, daily and weekly. Give those choices a type named `Period`. The command still receives text, so it checks the word and turns it into a known period before using it.

Use a JDK that supports Java 21 and your PowerShell practice folder. [Choose a report period with switch](41-choose-a-report-period-with-switch.md) explains how the program selects a result from one word.

## 1. Run the two supported choices

Save [ReportPeriodChoice.java](../../../labs/java-path/ReportPeriodChoice.java) in the practice folder. Open PowerShell there and compile it.

```powershell
javac --release 21 -Xlint:all -Werror ReportPeriodChoice.java
```

After compilation succeeds, run both choices.

```powershell
java -cp . ReportPeriodChoice daily
java -cp . ReportPeriodChoice weekly
```

```text
DAILY
WEEKLY
```

Each run prints one line and exits with code 0. The lower-case words are the accepted input. The upper-case words are the names declared in the enum.

## 2. Read the enum and the conversion

```java
private enum Period {
    DAILY,
    WEEKLY
}
```

An enum declares a fixed set of named values. `Period.DAILY` and `Period.WEEKLY` are the two values of this type. In `main`, the declaration `Period period` gives the result a type that Java can check. The report can use that value after the command-line text has been checked.

`parsePeriod` checks that you supplied exactly one word. The `switch` maps `daily` to `Period.DAILY` and `weekly` to `Period.WEEKLY`. `period.name()` prints the chosen enum constant’s name exactly as it was declared.

## 3. Check how the command refuses other input

```powershell
java -cp . ReportPeriodChoice monthly
$LASTEXITCODE
```

```text
Enter exactly one report period, daily or weekly.
2
```

The parser returns `null` when it cannot select a `Period`. The program checks for that result before calling `name()`. It writes the usage message to the error stream and exits with code 2. Try the command again with no period or with `daily weekly`. Both runs should give the same message and exit code.

If PowerShell stops when Java exits with code 2, enter `$LASTEXITCODE` at the next prompt. If Java cannot find the class, check that you are in the folder where `javac` completed successfully.

## 4. Express the same choices in C23

C23 also lets you name a set of choices. In this declaration, `REPORT_DAILY` and `REPORT_WEEKLY` are integer constants with the values 1 and 2.

```c
enum report_period {
    REPORT_DAILY = 1,
    REPORT_WEEKLY = 2
};
```

A C program can map the same two input words to those constants and supply its own display text. Java’s enum values are objects of type `Period`, so the Java example can ask the selected value for its declared name. Both programs check text at the command line and then use a named value inside the report.

[Java enum classes](https://docs.oracle.com/javase/specs/jls/se21/html/jls-8.html#jls-8.9) · [C23 working draft, enumeration specifiers](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf#page=126)

[Previous lesson](42-sort-readings-with-comparator.md) · [Next lesson](44-keep-related-counts-in-one-snapshot.md) · [Java course](index.md)
