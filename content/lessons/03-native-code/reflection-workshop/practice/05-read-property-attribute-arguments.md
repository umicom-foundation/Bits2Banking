<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/practice/05-read-property-attribute-arguments.md

PURPOSE:
  Read a PHP attribute's existing literal arguments and handle an empty attribute list.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom Windows icon](../../../../assets/branding/umicom.ico)

# Read property attribute arguments in PHP

[Practice contents](index.md) · [PHP property reflection lesson](../05-list-public-php-properties.md)

A property can carry an attribute with a display label. Another property
may use the application's normal label. This program reads both cases
without creating a reading or an instance of the label class.

## 1. Find the literal label

Open [`attribute_arguments.php`](../../../../labs/languages/reflection-workshop/practice/attribute_arguments.php).
The `degrees` property carries `PublicLabel('Degrees Celsius')`.
The `station` property leaves that attribute absent. The label is
information about the property declaration.

## 2. Follow the two branches

1. `getProperty` finds the two known property names in the exercise type.
2. `getAttributes(PublicLabel::class)` gives the matching attributes.
   The `station` list is empty, so the program records absence.
3. `getArguments()` reads the supplied positional argument from the
   matching attribute on `degrees`. This exercise uses a plain string.
   Other constant expressions can require evaluation, so choose explicitly
   which metadata expressions your own application accepts.

[PHP attribute arguments](https://www.php.net/manual/en/reflectionattribute.getarguments.php)

## 3. Check syntax and see both cases

Use PHP 8.1 or later. In PowerShell from the Bits2Banking repository root
run the syntax check first. Continue when it reports no syntax errors.

```powershell
$Lab = '.\content\labs\languages\reflection-workshop\practice'
php -l (Join-Path $Lab 'attribute_arguments.php')
php (Join-Path $Lab 'attribute_arguments.php')
```

```text
degrees: Degrees Celsius
station: no PublicLabel
```

## 4. Change one declaration

In a practice copy add `#[PublicLabel('Station code')]` directly before
the `station` property. Repeat the syntax check and run. Expect the second
line to be `station: Station code`. Keep the original case to verify how
your application behaves when metadata is absent.

[Practice contents](index.md)
