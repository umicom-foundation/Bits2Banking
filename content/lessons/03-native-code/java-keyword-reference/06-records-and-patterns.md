<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/java-keyword-reference/06-records-and-patterns.md

PURPOSE:
A contextual keyword has a special purpose only where a grammar rule admits it. Java may treat the same spelling differently in another location.

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

# Contextual words in records and patterns

[Course contents](index.md) · [Previous · Errors, package names, and reserved spellings](05-errors-and-reserved-spellings.md) · [Next · Contextual words in module contracts](07-module-contracts.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/06-records-and-patterns.html)

A contextual keyword has a special purpose only where a grammar rule admits it. Java may treat the same spelling differently in another location.

## Use the fragments

A contextual keyword has a special purpose only where a grammar rule admits it. Java may treat the same spelling differently in another location.

For a local statement, place it inside `public static void main(String[] args)` in a class named `ReceiptPractice`. Save it in `ReceiptPractice.java`. Use `javac ReceiptPractice.java` from a JDK 25, then `java ReceiptPractice`. Take class declarations, package declarations and module descriptors as separate examples.

## Examples by spelling

### var

Infer the type of a local variable with an initializer.

```java
var receiptCents = 250;
```

The local variable has type int; its type remains fixed.

### record

Declare a type for a small group of values.

```java
record Receipt(int cents) { }
```

new Receipt(250).cents() returns 250.

### sealed

Restrict which types may extend or implement this type directly.

```java
sealed interface Entry permits Receipt { }
record Receipt(int cents) implements Entry { }
```

Only the permitted direct implementation is admitted here.

### permits

List the allowed direct subtypes of a sealed type.

```java
sealed class Entry permits Receipt { }
final class Receipt extends Entry { }
```

Receipt is the permitted subclass.

### non-sealed

Let descendants of this direct subtype extend it more freely.

```java
sealed interface Entry permits TrainingEntry { }
non-sealed class TrainingEntry implements Entry { }
```

TrainingEntry can have additional subclasses.

### when

Qualify a pattern with a further condition in a switch label.

```java
Object entry = "paid";
int size = switch (entry) {
    case String text when !text.isEmpty() -> text.length();
    default -> 0;
};
```

The guard passes and the result is 4.

### yield

Supply the result of a switch expression from a block.

```java
int points = switch (1) {
    case 1 -> { int base = 10; yield base + 2; }
    default -> 0;
};
```

The switch result is 12.

## Compare another language

Python also has context-dependent words. Java var infers a static type. Python assignments bind a name, which may later refer to a different type of object.

## Try it

In the switch example with when, use an empty string. The guard fails and the fallback supplies zero.

## Apply it to Umicom

Choose and document the permitted states of a synthetic TMS report. Include a specific outcome for a state the lesson never expected.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Java](../../../courses/learning-java/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Java SE 25 lexical structure, section 3.9](https://docs.oracle.com/javase/specs/jls/se25/html/jls-3.html#jls-3.9)

[Course contents](index.md) · [Previous · Errors, package names, and reserved spellings](05-errors-and-reserved-spellings.md) · [Next · Contextual words in module contracts](07-module-contracts.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/06-records-and-patterns.html)
