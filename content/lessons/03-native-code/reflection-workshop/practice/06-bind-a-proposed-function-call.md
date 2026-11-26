<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/practice/06-bind-a-proposed-function-call.md

PURPOSE:
  Use Python signature binding to check a complete call and refuse a missing required name.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom Windows icon](../../../../assets/branding/umicom.ico)

# Bind a proposed function call in Python

[Practice contents](index.md) · [Python property inspection lesson](../06-inspect-a-python-property.md)

A function signature lists its parameters and their rules. A tool can
check that a proposed call supplies the required names before it decides
whether to run the function.

## 1. Identify the required keywords

Open [`signature_dry_check.py`](../../../../labs/languages/reflection-workshop/practice/signature_dry_check.py).
The `*` makes `station` and `degrees_c` keyword-only. A proposed call
must use those names. Write down which one is missing from the second
example.

## 2. Read the reflection operation

`signature(format_reading)` describes the function. `bind` checks the
proposed arguments against that description. When it succeeds, it supplies
a mapping of parameter names to values. When a required name is missing,
it raises `TypeError`. The example's function would raise its own
assertion if it ever ran, which makes the absence of a function call
visible. [Python signature binding](https://docs.python.org/3.14/library/inspect.html#inspect.Signature.bind)

## 3. Run both checks

Use Python 3.11 or later. Open PowerShell in the Bits2Banking repository
root, then run the version check and the example.

```powershell
$Lab = '.\content\labs\languages\reflection-workshop\practice'
python --version
python -B (Join-Path $Lab 'signature_dry_check.py')
```

```text
complete call: station, degrees_c
missing measurement: refused
```

## 4. Check shape and value separately

In a practice copy change the first `degrees_c=68` to
`degrees_c="unknown"`. Run it again and observe that the names still bind.
The annotation describes a type, while `bind` checks the way arguments
fit the signature. A real measurement caller should validate the actual
value before submitting it to the function.

[Practice contents](index.md)
