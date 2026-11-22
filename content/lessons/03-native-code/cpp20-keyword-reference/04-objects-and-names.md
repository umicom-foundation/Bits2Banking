<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/cpp20-keyword-reference/04-objects-and-names.md

PURPOSE:
Read class, member-access, dispatch and naming keywords, and distinguish two contextual class identifiers.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Organise data and actions into objects

[Course contents](index.md) · [Previous lesson — Declare names, storage and size](03-declarations-and-storage.md) · [Next lesson — Read ownership, errors and conversions](05-memory-errors-and-conversions.md)

## What you will learn

Read class, member-access, dispatch and naming keywords, and distinguish two contextual class identifiers.

## Read the words in context

A **class** defines a type with members such as data fields and functions. An **object** is an instance of a type. A **derived class** builds on a base class. A **namespace** groups names and helps distinguish unrelated parts of a program.

## Reserved keywords in this lesson

| Spelling | Meaning | Read this example |
| --- | --- | --- |
| `class` | Declares a class. Members are private by default. | `class Account { int cents = 0; };` |
| `struct` | Declares a class whose members are public by default. | `struct Receipt { int cents = 0; };` |
| `union` | Declares members that share storage. Read an active member for this example. | `union Sample { int cents; float rate; }; Sample reading{12};` |
| `public` | Allows access to a class member from ordinary calling code. | `class Receipt { public: int cents = 8; };` |
| `protected` | Allows access in the class and in permitted derived-class contexts. | `class Report { protected: int rows = 0; };` |
| `private` | Restricts access to the declaring class and its friends. | `struct Receipt { private: int cents = 8; };` |
| `this` | In a suitable member function, points to the object on which the function runs. | `struct Receipt { int cents; int value() { return this->cents; } };` |
| `friend` | Grants a declared function or class access to otherwise restricted members. | `class Box { int cents = 7; friend int read(Box box) { return box.cents; } };` |
| `virtual` | Enables selection of the applicable overridden member function through base references or pointers. | `struct Base { virtual int count() const { return 0; } };` |
| `explicit` | Prevents a constructor like this one from being used for implicit conversion. | `struct Cents { explicit Cents(int n) : value(n) {} int value; };` |
| `operator` | Names an overloaded operation. This example supplies a callable object using operator(). | `struct Six { int operator()() const { return 6; } };` |
| `namespace` | Creates a named scope. Access the amount below as trial::cents. | `namespace trial { int cents = 12; }` |

## Contextual spellings

| Spelling | Meaning | Read this example |
| --- | --- | --- |
| `override` | After a member-function declaration, asks the compiler to verify that the function overrides a base virtual member. | `struct Preview : Base { int count() const override { return 2; } };` |
| `final` | After a class name in this position, prevents using that class as a base. It can also prevent further overrides of a virtual function. | `struct FrozenReport final { int rows; };` |

## Try it and check

Which declaration exposes cents by default, the first class or the first struct? What could the class offer to let callers read a checked value?

**Check:** The struct exposes it by default. A class can provide a public member function that returns the value while keeping its underlying field private.

## Apply it to an Umicom project

Draw a practice Umicom Bank statement model with a public reading operation and a private record value. Separate the type itself from an object holding a single example receipt.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/cpp20-keyword-reference/lessons/04-objects-and-names.html)

[Course contents](index.md) · [Previous lesson — Declare names, storage and size](03-declarations-and-storage.md) · [Next lesson — Read ownership, errors and conversions](05-memory-errors-and-conversions.md)
