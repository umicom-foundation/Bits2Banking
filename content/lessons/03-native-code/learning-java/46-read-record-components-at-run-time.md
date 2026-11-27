<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/46-read-record-components-at-run-time.md

PURPOSE:
Read a record’s components at run time

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read a record’s components at run time

A reading holds two values, the minute it was taken and the measurement. A report needs both names and values so readers can tell what each number means. In Java, **reflection** lets a running program ask a known class what information it exposes. In C23, you can write a small table containing the information the report needs.

## 1. Run the Java report

1. Open the folder where you save your practice files.
2. Save [ReadingComponentReport.java](../../../labs/java-path/ReadingComponentReport.java) in that folder. The file name must match the public class name.
3. In PowerShell, check that `javac -version` reports a JDK that can target Java 21.
4. Compile the source, then run the class.

```powershell
javac --release 21 .\ReadingComponentReport.java
java -cp . ReadingComponentReport
```

You should see these two lines.

```text
minute = 15
value = 42
```

A **component** is one of the names and types listed in a record declaration. This record declares `minute` and `value`.

1. `Reading.class.getRecordComponents()` gives the loop both components in declaration order.
2. `component.getName()` gives the label to print.
3. `component.getAccessor()` gives the public method that reads it, such as `minute()`.
4. `invoke(reading)` runs that method on the particular reading with values `15` and `42`.

## 2. Read the same information in C23

1. Save [reading_component_report.c](../../../labs/java-path/reading_component_report.c) beside the Java file.
2. Check that `gcc --version` works in your PowerShell session. Use a GCC release that accepts `-std=c23`.
3. Compile and run the C program.

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror .\reading_component_report.c -o .\reading-component-report.exe
.\reading-component-report.exe
```

Expect the same two lines. The C program supplies its own list of member names. For each entry, `offsetof` asks the C compiler where that member begins inside a `Reading`. The loop copies the bytes into an `int` before printing. The table is for these two `int` members. A table for other member types would also need to describe how to read each type.

## 3. Change a value, then compare the two outputs

1. Change the sample measurement from `42` to `43` in both source files.
2. Run the same compile and run commands.
3. Check that `minute = 15` remains and that `value = 43` appears in both reports.

If Java reports that it cannot find the main class, check the location of `ReadingComponentReport.class` and run the command from that folder. If the second program still prints `42`, check that the edit was saved and the compile command succeeded before rerunning it.

## How this applies to Umicom

An IDE can describe the fields it can display when a project provides this information. A network message needs a separate written format for field names and sizes. Native structure offsets apply to the current build and may differ on another architecture.

Read [Keep a reading in a record](../../../courses/learning-java/lessons/36-keep-a-reading-in-a-record.html) for the record basics and [Verify a Java and C23 file contract](../../../courses/learning-java/lessons/21-verify-a-java-and-c23-file-contract.html) for an example of a shared file format.

- [Java 21 Class.getRecordComponents documentation](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/lang/Class.html#getRecordComponents())
- [Java 21 RecordComponent documentation](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/lang/reflect/RecordComponent.html)
- [C23 working draft, section 7.21 for offsetof](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)

[Previous lesson](45-build-a-plain-text-reading-report.md) · [Next lesson](47-load-defaults-from-a-jar.md) · [Java course](index.md) · [Browser edition](../../../courses/learning-java/lessons/46-read-record-components-at-run-time.html)
