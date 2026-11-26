<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/06-inspect-a-python-property.md

PURPOSE:
  Show static attribute lookup and the separate effect of reading a Python property value.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Inspect a Python property

[Previous · PHP](05-list-public-php-properties.md) · [Workshop](index.md)
· [Next · Read a FreeBASIC type and catalogue](07-read-a-basic-type-and-catalogue.md)

A Python attribute may contain data, or it may run code when you read it.
This example prints the declared fields of a temperature reading. It
also checks what happens when you inspect the `summary` property and then
read its value.

## 1. Open the two mechanisms

Open [`static_property.py`](../../../labs/languages/reflection-workshop/static_property.py).

1. `@dataclass` uses the annotations on `station` and `degrees_c` to
   define the two data fields in the exercise.
2. `fields(Reading)` returns a description of each declared dataclass
   field. Each description includes its `name` and declared `type`.
3. `@property` makes `summary` run its getter when accessed in the usual
   way. The getter adds one to a counter each time it runs.

The getter builds a text value from the reading. The counter makes its
execution visible.

## 2. Predict both counter readings

Look at `getattr_static(reading, "summary")`. This lookup returns the
property descriptor, the object that describes how ordinary property access
works. The getter's body stays idle during this lookup. The next line
that reads `reading.summary` directly runs the getter.

Write down the two counts you expect before opening the terminal.
[Python dataclasses fields](https://docs.python.org/3.14/library/dataclasses.html#dataclasses.fields)
· [Python static attribute lookup](https://docs.python.org/3.14/library/inspect.html#inspect.getattr_static)

## 3. Run a local reading

Use Python 3.11 or later. This is a Python-language exercise and uses
only the standard library. If needed, follow
[Learning Python](../../02-programming/learning-python/index.md) for setup.
From the Bits2Banking repository root run these commands.

```powershell
python --version
python -B .\content\labs\languages\reflection-workshop\static_property.py
```

```text
station: str
degrees_c: int
summary descriptor: property
reads before explicit access: 0
summary: Bench A at 68 C
reads after explicit access: 1
```

If PowerShell opens a store prompt or cannot find Python, check the
resolved command with `Get-Command python` and select your installed
interpreter. If the count is already 1 before the explicit access, look
for an earlier ordinary read of `reading.summary`.

## 4. Separate the description from another read

In a practice copy, run the static lookup a second time just before
printing the first counter value. Expect that count to stay 0. Add a
second ordinary read after the first and expect the final count to
become 2. This practice helps when designing an editor that can inspect
metadata without running arbitrary property getters.

[Next · Read a FreeBASIC type and catalogue](07-read-a-basic-type-and-catalogue.md)
