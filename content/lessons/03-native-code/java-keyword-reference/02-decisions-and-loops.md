<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/java-keyword-reference/02-decisions-and-loops.md

PURPOSE:
A condition asks a yes-or-no question. Use one fragment at a time inside a class method unless it declares a method of its own.

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

# Decisions, loops, and early exits

[Course contents](index.md) · [Previous · Numbers, characters, and result types](01-numbers-and-values.md) · [Next · Classes, objects, and contracts](03-classes-and-interfaces.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/02-decisions-and-loops.html)

A condition asks a yes-or-no question. Use one fragment at a time inside a class method unless it declares a method of its own.

## Use the fragments

A condition asks a yes-or-no question. Use one fragment at a time inside a class method unless it declares a method of its own.

For a local statement, place it inside `public static void main(String[] args)` in a class named `ReceiptPractice`. Save it in `ReceiptPractice.java`. Use `javac ReceiptPractice.java` from a JDK 25, then `java ReceiptPractice`. Take class declarations, package declarations and module descriptors as separate examples.

## Examples by spelling

### if

Choose a block when its condition is true.

```java
if (3 > 0) { System.out.println("positive"); }
```

The block prints positive.

### else

Handle a false condition.

```java
if (0 > 0) { System.out.println("positive"); }
else { System.out.println("zero or below"); }
```

The second path prints zero or below.

### for

Repeat a task. This form has start, test and update parts.

```java
for (int i = 1; i <= 2; ++i) { System.out.println(i); }
```

It shows 1 and then 2.

### while

Check the condition before each pass.

```java
int remaining = 2;
while (remaining > 0) { System.out.println(remaining--); }
```

It shows 2 and then 1.

### do

Run the body before the first condition test.

```java
do { System.out.println("once"); } while (false);
```

It shows once.

### continue

End this pass early and let the loop continue.

```java
for (int i = 1; i <= 3; ++i) {
    if (i == 2) { continue; }
    System.out.println(i);
}
```

It shows 1 and 3.

### break

Leave the closest loop early here.

```java
for (int i = 1; i <= 3; ++i) {
    if (i == 2) { break; }
    System.out.println(i);
}
```

Only 1 appears.

### switch

Choose one branch based on a value. This is a switch expression.

```java
int label = switch (1) { case 1 -> 10; default -> 0; };
```

The assigned result is 10.

### case

Describe a value or pattern for one branch.

```java
int code = switch (3) { case 3 -> 30; default -> 0; };
```

The branch named by case 3 supplies 30.

### default

Supply a fallback switch branch when no case matches.

```java
int code = switch (8) { case 3 -> 30; default -> 0; };
```

The fallback supplies 0.

### return

Finish a method with a result. Put this method in the class body.

```java
static int lineCount() { return 3; }
```

Calling lineCount returns 3.

## Compare another language

C, C++, Java and D share the shape of the counting for loop. Go leaves out the parentheses and Python usually visits the next value in a collection or range.

## Try it

Trace the continue example as if the loop started at zero. It then shows 0, 1 and 3.

## Apply it to Umicom

Write expected outputs for a Bank import that skips a blank practice row and for one that stops the whole import.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Java](../../../courses/learning-java/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Java SE 25 lexical structure, section 3.9](https://docs.oracle.com/javase/specs/jls/se25/html/jls-3.html#jls-3.9)

[Course contents](index.md) · [Previous · Numbers, characters, and result types](01-numbers-and-values.md) · [Next · Classes, objects, and contracts](03-classes-and-interfaces.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/02-decisions-and-loops.html)
