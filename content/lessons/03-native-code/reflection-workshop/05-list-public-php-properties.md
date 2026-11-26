<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/05-list-public-php-properties.md

PURPOSE:
  Teach PHP reflection over public property names, named types and readonly declarations.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# List public PHP properties

[Previous · Java](04-read-java-record-components.md) · [Workshop](index.md)
· [Next · Inspect a Python property](06-inspect-a-python-property.md)

PHP can describe a class after it is loaded. The report in this lesson
shows the names and declared types of public properties. It helps you read
a settings interface before you create any readings.

## 1. Identify the three declarations

Open [`property_catalogue.php`](../../../labs/languages/reflection-workshop/property_catalogue.php).
Find these fields.

```php
public string $station;
public readonly int $degreesC;
private string $internalLabel;
```

A property is a named place for a value on an object. A declaration can
specify where it may be accessed and what type it holds. Here the intended
public report contains `station` and `degreesC`.

## 2. Trace the report in order

1. `new ReflectionClass(Reading::class)` gives you information about the
   loaded class. The sample creates no instance of `Reading`.
2. `getProperties(ReflectionProperty::IS_PUBLIC)` selects public
   declarations. The private declaration stays out of this catalogue.
3. `ksort(..., SORT_STRING)` orders the application report by name.
4. `getType()` reports the declared type. This sample handles
   `ReflectionNamedType`. A property declared with several possible types
   needs a different display rule.
5. `isReadOnly()` checks the declaration's readonly feature. Application
   forms still need their own rules for editable fields.

[PHP ReflectionClass API](https://www.php.net/manual/en/class.reflectionclass.php)
· [PHP ReflectionProperty API](https://www.php.net/manual/en/class.reflectionproperty.php)

## 3. Check syntax and run the program

Use PHP 8.1 or later. This release introduced readonly properties. Read
[Learning PHP](../../04-web/learning-php/index.md) if you need setup steps.
From the Bits2Banking repository root, run the version check and lint
before running the file.

```powershell
php -v
php -l .\content\labs\languages\reflection-workshop\property_catalogue.php
php .\content\labs\languages\reflection-workshop\property_catalogue.php
```

After linting succeeds, the program should print these two lines.

```text
degreesC: int, declared readonly
station: string, ordinary declaration
```

If linting fails at `readonly`, compare the terminal's PHP version with
the requirement. If you later add a union such as `int|string`, the
sample reports that it expected one named type. That refusal keeps the
exercise's simple catalogue format predictable.

## 4. Change what the public catalogue includes

In a practice copy, add a public `bool $calibrated;`. Run the lint and the
program again. Check that `calibrated: bool, ordinary declaration` comes
first and the private `internalLabel` stays outside the list.

[Next · Inspect a Python property](06-inspect-a-python-property.md)
