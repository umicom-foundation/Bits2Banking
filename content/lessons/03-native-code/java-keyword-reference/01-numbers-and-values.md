<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/java-keyword-reference/01-numbers-and-values.md

PURPOSE:
A type describes the values a name can hold. Put the local examples inside main in a Java class.

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

# Numbers, characters, and result types

[Course contents](index.md) · [Next · Decisions, loops, and early exits](02-decisions-and-loops.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/01-numbers-and-values.html)

A type describes the values a name can hold. Put the local examples inside main in a Java class.

## Use the fragments

A type describes the values a name can hold. Put the local examples inside main in a Java class.

For a local statement, place it inside `public static void main(String[] args)` in a class named `ReceiptPractice`. Save it in `ReceiptPractice.java`. Use `javac ReceiptPractice.java` from a JDK 25, then `java ReceiptPractice`. Take class declarations, package declarations and module descriptors as separate examples.

## Examples by spelling

### boolean

Store a yes-or-no value. The words true and false are literal values.

```java
boolean posted = true;
```

The value is true.

### byte

Hold a signed 8-bit whole number.

```java
byte ticketCount = 12;
```

The count is 12 and its permitted range is −128 through 127.

### short

Hold a signed 16-bit whole number.

```java
short queueDepth = 300;
```

The stored value is 300.

### int

Hold a signed 32-bit whole number.

```java
int receiptCents = 250;
```

The whole-cents amount remains 250.

### long

Hold a signed 64-bit whole number. The L marks the literal as long.

```java
long archiveRows = 3_000_000_000L;
```

The count is 3,000,000,000.

### char

Store one UTF-16 code unit. Many text symbols need two or more code units.

```java
char paidMark = 'P';
```

The code unit represents P.

### float

Hold a 32-bit floating-point value. The f suffix selects this literal type.

```java
float scale = 0.5f;
```

The scale is one half.

### double

Hold a 64-bit floating-point value. Use explicit units and rounding for money.

```java
double hours = 0.5;
```

The value is 0.5 hours.

### void

Declare that a method gives no value back. Put this method inside a class.

```java
static void display() { System.out.println("ready"); }
```

Calling display prints ready.

## Compare another language

Java defines fixed widths for these integer types. C fixes minimum ranges for its ordinary integer types and provides fixed-width names in its library when the implementation supports them.

## Try it

Choose a type for the count 150. The shown byte cannot hold it unchanged. short, int and long can.

## Apply it to Umicom

Use synthetic receipt amounts to write down the range and unit of a field before sending it between a training application and a database.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Java](../../../courses/learning-java/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Java SE 25 lexical structure, section 3.9](https://docs.oracle.com/javase/specs/jls/se25/html/jls-3.html#jls-3.9)

[Course contents](index.md) · [Next · Decisions, loops, and early exits](02-decisions-and-loops.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/01-numbers-and-values.html)
