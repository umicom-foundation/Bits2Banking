<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/practice/index.md

PURPOSE:
  Guide learners through seven distinct reflection and metadata admission checks.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom Windows icon](../../../../assets/branding/umicom.ico)

# Practice matching and refusing metadata

In the [reflection workshop](../index.md) you read field and type
descriptions. Here you will use that information to make a small decision.
Every exercise gives you a case that matches and a case that stays absent
or is refused.

1. [C23 · Find a published field ID](01-find-a-published-field-id.md).
   Look up a measurement and an internal field by number.
2. [Umicom C · Check a parameter type by name](02-check-a-parameter-type-by-name.md).
   Compile a required-input artifact and try a name outside its scope.
3. [D · Check a proposed overload](03-check-a-proposed-overload.md).
   Count the declared methods and ask whether two proposed calls compile.
4. [Java · Read a retained record annotation](04-read-a-retained-record-annotation.md).
   Check a runtime display unit and a class-file-only note.
5. [PHP · Read arguments from a property attribute](05-read-property-attribute-arguments.md).
   Read a literal label and handle a property without that label.
6. [Python · Bind a proposed function call](06-bind-a-proposed-function-call.md).
   Check two proposed keyword lists with a real function signature.
7. [FreeBASIC · Compare exact declared types](07-compare-exact-declared-types.md).
   Ask the compiler to choose a result for a whole and a fractional type.

For each exercise, write down the declared fact, the input to the
check, and the observation. Use the expected result to verify your
record. In an application, decide what absence should mean before
feeding the result to a form, report or action.
