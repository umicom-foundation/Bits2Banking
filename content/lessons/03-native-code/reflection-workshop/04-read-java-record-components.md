<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/04-read-java-record-components.md

PURPOSE:
  Teach Java runtime reflection through declared record components and accessor metadata.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read Java record components

[Previous · D](03-check-inherited-members-in-d.md) · [Workshop](index.md)
· [Next · List public PHP properties](05-list-public-php-properties.md)

A Java record names its parts in the declaration. These parts are called
components. Java's reflection API lets a running program read their names,
types and accessors. An accessor is the method that normally returns a
component's stored value.

## 1. Start with the record header

Open [`RecordCatalogue.java`](../../../labs/languages/reflection-workshop/RecordCatalogue.java)
and inspect the header.

```java
record Reading(String station, int degreesC) {}
```

1. `station` is the first component and has the type `String`.
2. `degreesC` is the second component and has the type `int`.
3. Java supplies accessors `station()` and `degreesC()` for this declaration.

Write those names down before looking at the program's output.

## 2. Follow the reflection calls

`Reading.class` gives the program a Class object that represents the loaded
type. `getRecordComponents()` walks its declared components in declaration
order. The loop prints the name, the type's short name and the name of the
accessor method. Reading that method's name leaves the value unread.

The last line uses `String.class.isRecord()` to check an ordinary class.
Keep a category check like this when inspecting a type supplied at runtime.
`getRecordComponents()` returns `null` for a type outside the record category.
[Java Class API](https://docs.oracle.com/en/java/javase/25/docs/api/java.base/java/lang/Class.html#getRecordComponents())
· [Java RecordComponent API](https://docs.oracle.com/en/java/javase/25/docs/api/java.base/java/lang/reflect/RecordComponent.html)

## 3. Build and read the report

Use JDK 25, the version covered in the
[Java keyword reference](../../../courses/java-keyword-reference/index.html).
This sample uses Java's standard record support, which is also available in
JDK 16 and later. From the Bits2Banking repository root, run one command at
a time.

```powershell
javac -version
New-Item -ItemType Directory -Path '.\build\reflection-java' -Force | Out-Null
javac -d .\build\reflection-java .\content\labs\languages\reflection-workshop\RecordCatalogue.java
java -cp .\build\reflection-java RecordCatalogue
```

```text
station: String, accessor station
degreesC: int, accessor degreesC
String is a record: false
```

If PowerShell cannot find `javac`, check that a JDK is installed and visible
on the terminal's path. If Java cannot find the class after compilation,
compare the name `RecordCatalogue` and the folder supplied in `-cp` with the
name and output folder used at the compilation step.

## 4. Add one declared component

Change the record header in a practice copy to add `boolean calibrated`
after `degreesC`. Rebuild with the updated file. Check for a new line
`calibrated: boolean, accessor calibrated` immediately before the final
class check. The reporting loop stays the same.

[Next · List public PHP properties](05-list-public-php-properties.md)
