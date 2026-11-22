<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/java-keyword-reference/05-errors-and-reserved-spellings.md

PURPOSE:
A package groups types under a name. An exception describes a failure that travels to a caller or a handler.

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

# Errors, package names, and reserved spellings

[Course contents](index.md) · [Previous · Access, storage, and shared state](04-access-and-storage.md) · [Next · Contextual words in records and patterns](06-records-and-patterns.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/05-errors-and-reserved-spellings.html)

A package groups types under a name. An exception describes a failure that travels to a caller or a handler.

## Use the fragments

A package groups types under a name. An exception describes a failure that travels to a caller or a handler.

For a local statement, place it inside `public static void main(String[] args)` in a class named `ReceiptPractice`. Save it in `ReceiptPractice.java`. Use `javac ReceiptPractice.java` from a JDK 25, then `java ReceiptPractice`. Take class declarations, package declarations and module descriptors as separate examples.

## Examples by spelling

### package

Place a compilation unit in a named package. This line precedes imports and type declarations.

```java
package training.receipts;
class Receipt { }
```

The class belongs to training.receipts.

### import

Let code refer to an accessible type by its simple name. Put the import before the class.

```java
import java.util.List;
class Receipt { List<Integer> amounts = List.of(25); }
```

The list contains the one training amount 25.

### try

Start a region with an associated handler or cleanup.

```java
try { System.out.println(Integer.parseInt("25")); }
catch (NumberFormatException failure) { System.out.println("invalid"); }
```

This input prints 25.

### catch

Handle a matching exception from a try block.

```java
try { Integer.parseInt("wrong"); }
catch (NumberFormatException failure) { System.out.println("invalid"); }
```

It prints invalid.

### finally

Run cleanup when leaving a try statement under ordinary execution.

```java
try { System.out.println("check"); }
finally { System.out.println("finish"); }
```

It prints check then finish.

### throw

Send a failure along the exception path.

```java
static void reject() { throw new IllegalArgumentException("bad amount"); }
```

Calling reject raises the named exception.

### throws

Declare an exception that may leave a method.

```java
static void fail() throws java.io.IOException {
    throw new java.io.IOException("training failure");
}
```

Callers must handle or declare this checked exception.

### assert

Check an internal expectation when assertions are enabled.

```java
assert 250 >= 0 : "amount must be positive or zero";
```

This expectation passes when enabled. Use java -ea to enable assertions. Use ordinary validation for input.

### const

Recognise a reserved word that has no declaration form in Java.

```java
const int amount = 250;
```

This intentionally fails. Use final int amount = 250; for an assigned-once local.

### goto

Recognise a reserved word that does not introduce a Java jump.

```java
goto done;
```

This intentionally fails. Use loop controls or a named method.

### _

Declare an unnamed variable in a permitted Java SE 25 context.

```java
for (int _ : new int[] { 20, 50 }) { System.out.println("row"); }
```

It prints row twice. No expression can use that unnamed value.

## Compare another language

C supports goto and uses status returns in many libraries. Java reserves goto and handles exceptions with explicit language statements.

## Try it

In the catch example, change wrong to 17 and print the parsed value in the try block. It prints 17 and skips the handler.

## Apply it to Umicom

Describe the non-destructive behaviour you expect from a malformed sample before proposing an improvement to a Studio import command.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Java](../../../courses/learning-java/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Java SE 25 lexical structure, section 3.9](https://docs.oracle.com/javase/specs/jls/se25/html/jls-3.html#jls-3.9)

[Course contents](index.md) · [Previous · Access, storage, and shared state](04-access-and-storage.md) · [Next · Contextual words in records and patterns](06-records-and-patterns.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/05-errors-and-reserved-spellings.html)
