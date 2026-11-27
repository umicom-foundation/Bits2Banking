<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/java-keyword-reference/07-module-contracts.md

PURPOSE:
A module groups packages. A module descriptor is a file named module-info.java. These fragments introduce descriptor syntax, with fictional modules and packages that would need to exist for a real build.

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

# Contextual words in module contracts

[Course contents](index.md) · [Previous · Contextual words in records and patterns](06-records-and-patterns.md) · [Next · Save a draft and publish a preview](08-save-a-draft-and-publish-a-preview.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/07-module-contracts.html)

A module groups packages. A module descriptor is a file named module-info.java. These fragments introduce descriptor syntax, with fictional modules and packages that would need to exist for a real build.

## Use the fragments

A module groups packages. A module descriptor is a file named module-info.java. These fragments introduce descriptor syntax, with fictional modules and packages that would need to exist for a real build.

For a local statement, place it inside `public static void main(String[] args)` in a class named `ReceiptPractice`. Save it in `ReceiptPractice.java`. Use `javac ReceiptPractice.java` from a JDK 25, then `java ReceiptPractice`. Take class declarations, package declarations and module descriptors as separate examples.

## Examples by spelling

### module

Name a module and open its descriptor block.

```java
module training.receipts { }
```

The descriptor names the training.receipts module.

### open

Allow deep runtime reflection into the packages of the whole module, subject to platform policy.

```java
open module training.receipts { }
```

The descriptor declares an open module.

### requires

Declare a dependency on another named module.

```java
module training.receipts { requires java.logging; }
```

The descriptor lists java.logging as required.

### transitive

Make a readability dependency available to modules that read this module.

```java
module training.receipts { requires transitive java.sql; }
```

A module that reads this module also reads java.sql.

### exports

Expose the accessible types of a package to other modules.

```java
module training.receipts { exports training.receipts.api; }
```

The API package must exist in the module.

### to

Limit an exports or opens directive to named target modules.

```java
module training.receipts { exports training.receipts.api to training.reports; }
```

The API package is exported specifically to training.reports.

### opens

Allow runtime deep reflection into a named package of a normal module.

```java
module training.receipts { opens training.receipts.records; }
```

The named package is open for reflective access.

### uses

Declare a service the module may acquire through Java services.

```java
module training.reports { requires training.receipts;
    uses training.receipts.api.Report; }
```

The accessible Report service must be defined by the required module.

### provides

Register a provider for a service in a descriptor.

```java
module training.receipts { provides training.receipts.api.Report
    with training.receipts.csv.CsvReport; }
```

The descriptor registers CsvReport for Report.

### with

Introduce one or more provider implementations in a provides directive.

```java
module training.receipts { provides training.receipts.api.Report
    with training.receipts.text.TextReport; }
```

The declared provider is TextReport.

## Compare another language

Framework services can also have explicit build-time and runtime boundaries. Java module declarations describe their own readability, reflection, and service rules.

## Try it

On paper, draw a line from training.reports to training.receipts when the first requires the second. Ask separately which package the second exposes.

## Apply it to Umicom

Start a Studio dependency review by listing the build dependency, exposed API and implementation for one fictional reporting component.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Java](../../../courses/learning-java/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Java SE 25 lexical structure, section 3.9](https://docs.oracle.com/javase/specs/jls/se25/html/jls-3.html#jls-3.9)

[Course contents](index.md) · [Previous · Contextual words in records and patterns](06-records-and-patterns.md) · [Next · Save a draft and publish a preview](08-save-a-draft-and-publish-a-preview.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/07-module-contracts.html)
