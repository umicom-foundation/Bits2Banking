<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/java-keyword-reference/03-classes-and-interfaces.md

PURPOSE:
A class describes a kind of object. An interface specifies a contract that objects can provide. Short snippets here may declare a class, a member or a local variable as described.

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

# Classes, objects, and contracts

[Course contents](index.md) · [Previous · Decisions, loops, and early exits](02-decisions-and-loops.md) · [Next · Access, storage, and shared state](04-access-and-storage.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/03-classes-and-interfaces.html)

A class describes a kind of object. An interface specifies a contract that objects can provide. Short snippets here may declare a class, a member or a local variable as described.

## Use the fragments

A class describes a kind of object. An interface specifies a contract that objects can provide. Short snippets here may declare a class, a member or a local variable as described.

For a local statement, place it inside `public static void main(String[] args)` in a class named `ReceiptPractice`. Save it in `ReceiptPractice.java`. Use `javac ReceiptPractice.java` from a JDK 25, then `java ReceiptPractice`. Take class declarations, package declarations and module descriptors as separate examples.

## Examples by spelling

### class

Define a kind of object.

```java
class Receipt { int cents = 250; }
```

A newly created Receipt has cents equal to 250.

### new

Create an object or array.

```java
int[] amounts = new int[2];
```

The two integer elements initially contain zero.

### this

Refer to the current object in an instance method or constructor.

```java
class Receipt { int cents; Receipt(int cents) { this.cents = cents; } }
```

A Receipt constructed with 250 stores 250 in its field.

### super

Refer to a superclass member or invoke its constructor.

```java
class Base { int cents() { return 250; } }
class Receipt extends Base { int amount() { return super.cents(); } }
```

A Receipt object returns 250 from amount.

### extends

Choose a superclass or extend an interface.

```java
class Entry { }
class Receipt extends Entry { }
```

A Receipt is usable where an Entry is expected.

### abstract

Leave some implementation to a concrete subclass.

```java
abstract class Entry { abstract int cents(); }
```

A concrete subclass must provide cents.

### interface

Declare a contract.

```java
interface Priced { int cents(); }
```

An implementation can provide a method named cents.

### implements

Declare that a class implements an interface.

```java
interface Priced { int cents(); }
class Receipt implements Priced { public int cents() { return 250; } }
```

The class provides the required method and returns 250.

### instanceof

Ask whether an object has a given type. This example also binds a pattern variable.

```java
Object value = "receipt";
if (value instanceof String text) { System.out.println(text.length()); }
```

The test succeeds and shows 7.

### enum

Give a type a fixed set of named instances.

```java
enum EntryState { POSTED, PENDING }
```

EntryState.POSTED names one of the two instances.

## Compare another language

Java uses classes and interfaces. Go can satisfy an interface through a matching method set. C can express a similar application contract through function declarations and data structures.

## Try it

Explain the difference between a class named Receipt and the receipt made by new Receipt(). One describes the type and the other is an individual object.

## Apply it to Umicom

Sketch a training report interface. Let Bank and TMS exercises provide synthetic data through the same contract.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Java](../../../courses/learning-java/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Java SE 25 lexical structure, section 3.9](https://docs.oracle.com/javase/specs/jls/se25/html/jls-3.html#jls-3.9)

[Course contents](index.md) · [Previous · Decisions, loops, and early exits](02-decisions-and-loops.md) · [Next · Access, storage, and shared state](04-access-and-storage.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/03-classes-and-interfaces.html)
