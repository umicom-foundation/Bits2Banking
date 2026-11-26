<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/index.md

PURPOSE:
  A practical entry point for comparing language reflection, type queries and explicit catalogues.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Reflection from declarations to a report

A field stores one part of a record, such as a station name or a temperature.
Metadata describes the field. It can tell you its name, its declared type, or
whether an application chose to publish it. Reflection lets a program ask the
compiler or runtime for some of those facts.

This workshop follows a small workbench idea. You need a readable description
of a temperature reading before deciding what to display in a settings
panel. The examples use fictional readings and run locally.

## Start here

1. [Describe fields in native C23](01-name-fields-in-native-c.md). Make a
   declaration and a public catalogue from one list.
2. [Query a local type in Umicom C](02-check-a-local-type-in-umicom-c.md).
   Watch the checked interpreter preserve a qualifier and reject an update.
3. [Find inherited members in D](03-check-inherited-members-in-d.md).
   Ask two questions about the same class before compilation finishes.
4. [Read Java record components](04-read-java-record-components.md). Use the
   runtime Class object to list names and accessor metadata.
5. [List public PHP properties](05-list-public-php-properties.md).
   Select public declarations and check which one declares readonly.
6. [Inspect a Python property](06-inspect-a-python-property.md). Look at the
   property object, then explicitly get its value and observe the difference.
7. [Read a FreeBASIC type and catalogue](07-read-a-basic-type-and-catalogue.md).
   Confirm a compile-time type and print the application's own labels.

Each lesson uses its own compiler or interpreter. Follow the course link
when you need installation steps. Run the first lesson on paper if you are
still setting up tools. Mark the fields that were discovered and the labels
the programmer supplied.

| Language | What this workshop observes | When the observation is made |
| --- | --- | --- |
| Native C23 | One expression's type and a catalogue written from a defined field list | The type is decided at compile time; the report reads the catalogue at runtime |
| Umicom C | The type and top-level qualifier of a supported earlier local | While admitting the checked C program |
| D | Declared and inherited member names | During compilation |
| Java | A record's declared components and accessor names | While the program runs |
| PHP | Selected property declarations, named types and readonly status | While the program runs |
| Python | Dataclass field declarations and a property descriptor | While the program runs |
| FreeBASIC | One expression's type and a deliberately maintained catalogue | The type is decided at compile time; the catalogue is read at runtime |

## Use the results in an Umicom project

A Studio property panel needs a stable public list of fields and labels.
A measurement reader also needs units and a rule for admitting values.
Write those decisions explicitly even when a language can discover the
declared name and type. When crossing from one language into shared
Framework C, confirm the public declaration, version and ownership rules
at the boundary. Then test a valid reading and a refused one.

[Umicom Framework development](../../../courses/umicom-development/index.html)
· [Umicom Windows icon](../../../assets/branding/umicom.ico)

## Continue with Framework

[Keep a Framework metadata snapshot](08-keep-a-framework-metadata-snapshot.md) to practise retaining an independent copy after a registry changes.

## Practise reflection with two cases

[Open the seven practice exercises](practice/index.md) and check the matching and absent or refused case in each language.
