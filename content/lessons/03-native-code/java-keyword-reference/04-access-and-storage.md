<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/java-keyword-reference/04-access-and-storage.md

PURPOSE:
A member is a field or method declared in a class. Access modifiers describe who can use it. A field can belong to the class or to an individual object.

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

# Access, storage, and shared state

[Course contents](index.md) · [Previous · Classes, objects, and contracts](03-classes-and-interfaces.md) · [Next · Errors, package names, and reserved spellings](05-errors-and-reserved-spellings.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/04-access-and-storage.html)

A member is a field or method declared in a class. Access modifiers describe who can use it. A field can belong to the class or to an individual object.

## Use the fragments

A member is a field or method declared in a class. Access modifiers describe who can use it. A field can belong to the class or to an individual object.

For a local statement, place it inside `public static void main(String[] args)` in a class named `ReceiptPractice`. Save it in `ReceiptPractice.java`. Use `javac ReceiptPractice.java` from a JDK 25, then `java ReceiptPractice`. Take class declarations, package declarations and module descriptors as separate examples.

## Examples by spelling

### public

Allow access from other code when the declaring type and module are accessible.

```java
class Receipt { public int cents() { return 250; } }
```

Accessible callers can call cents.

### private

Limit normal source access to the declaring top-level type and its nested types.

```java
class Receipt { private int cents = 250; }
```

An unrelated class cannot access the field directly.

### protected

Allow package access and qualified subclass access under Java rules.

```java
class Base { protected int cents = 250; }
class Receipt extends Base { int amount() { return cents; } }
```

The subclass can use the inherited field.

### static

Declare a member on the class itself.

```java
class Receipt { static int count = 3; }
```

Use Receipt.count without creating a Receipt.

### final

Assign a local variable at most once. Other uses restrict overriding or subclassing.

```java
final int unit = 100;
```

A later assignment to this local variable is a compile error.

### synchronized

Run a section while holding an object monitor.

```java
Object gate = new Object();
synchronized (gate) { System.out.println("one section"); }
```

This block acquires the monitor for gate and releases it on exit.

### volatile

Give a field volatile visibility and ordering rules across threads.

```java
class Job { volatile boolean finished; }
```

A volatile read and write of finished follow the visibility rules. A compound update still needs its own protection.

### transient

Exclude a field from Java default object serialisation.

```java
class Draft implements java.io.Serializable { transient int previewIndex; }
```

Default serialisation leaves previewIndex out.

### native

Declare a method implemented outside Java. This declaration has no method body.

```java
class ReceiptBridge { static native int amountCents(); }
```

Calling it requires the linked native implementation. Do not run this fragment alone.

### strictfp

Recognise an obsolete modifier in older source.

```java
strictfp class OldReceipt { double half() { return 0.5; } }
```

Java SE 25 treats floating-point expressions with the current strict rules without this modifier.

## Compare another language

Java volatile and C volatile serve different language contracts. Keep a thread-coordination design explicit and test it on its intended runtime.

## Try it

If a value belongs to each individual receipt, give the object its own field. A single static receipt amount would be shared by every instance.

## Apply it to Umicom

Describe who owns a temporary report preview and when it can be discarded. Keep receipt arithmetic separate from shared window state.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Java](../../../courses/learning-java/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Java SE 25 lexical structure, section 3.9](https://docs.oracle.com/javase/specs/jls/se25/html/jls-3.html#jls-3.9)

Practise the four storage and sharing keywords in [Save a draft and publish a preview](08-save-a-draft-and-publish-a-preview.md).

[Course contents](index.md) · [Previous · Classes, objects, and contracts](03-classes-and-interfaces.md) · [Next · Errors, package names, and reserved spellings](05-errors-and-reserved-spellings.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/04-access-and-storage.html)
