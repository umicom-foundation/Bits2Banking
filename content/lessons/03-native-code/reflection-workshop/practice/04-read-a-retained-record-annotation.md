<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/practice/04-read-a-retained-record-annotation.md

PURPOSE:
  Show that Java reflection can observe runtime annotations and reports class-file-only annotations absent.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom Windows icon](../../../../assets/branding/umicom.ico)

# Read a retained record annotation in Java

[Practice contents](index.md) · [Java record reflection lesson](../04-read-java-record-components.md)

An annotation attaches a fact to a declaration. A retention policy tells
Java how long to keep the annotation for its consumers. This exercise
checks a display unit and a note meant for class-file readers.

## 1. Read the two policies

Open [`RecordUnitLookup.java`](../../../../labs/languages/reflection-workshop/practice/RecordUnitLookup.java).
`DisplayUnit` uses `RUNTIME` and is attached to `degreesC`. `BuildNote`
uses `CLASS` and is attached to `samples`. Both are declared for record
components. The runtime reflection API can read the display unit. The
class-file-only note will be absent from this API.

[Java retention policies](https://docs.oracle.com/en/java/javase/25/docs/api/java.base/java/lang/annotation/RetentionPolicy.html)
· [Record component annotations](https://docs.oracle.com/en/java/javase/25/docs/api/java.base/java/lang/reflect/RecordComponent.html#getAnnotation(java.lang.Class))

## 2. Compile the record and read its report

Use a JDK with record support, such as JDK 25. From the Bits2Banking
repository root run the following in PowerShell. Start with an unused
build folder and run `java` after `javac` succeeds.

```powershell
$Lab = '.\content\labs\languages\reflection-workshop\practice'
$Out = '.\build\reflection-practice-java'
New-Item -ItemType Directory -Path $Out -Force | Out-Null
javac -d $Out (Join-Path $Lab 'RecordUnitLookup.java')
java -cp $Out RecordUnitLookup
```

```text
degreesC runtime unit: Celsius
samples runtime build note: absent
```

## 3. Identify the absent result

Follow `getAnnotation(BuildNote.class)` to its `null` branch. The program
turns that API result into the word `absent`. Use the retention policy
to explain why the code can declare a note that this method cannot read.

## 4. Make the note visible in a practice copy

Change the `BuildNote` retention to `RUNTIME` and rebuild. The second
line should now say `samples runtime build note: batch sample count`.
The display unit remains `Celsius`. This is a useful way to separate
a declaration from its availability to a running tool.

[Practice contents](index.md)
