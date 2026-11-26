<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/practice/01-find-a-published-field-id.md

PURPOSE:
  Use exact field IDs to distinguish a published C23 row from absent metadata.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom Windows icon](../../../../assets/branding/umicom.ico)

# Find a published field ID in C23

[Practice contents](index.md) · [Native C23 catalogue lesson](../01-name-fields-in-native-c.md)

The reading structure has a temperature and an internal flag. An editor
needs the temperature's public label. Its lookup uses an agreed number
so a display label can change without changing how callers find the row.

## 1. Predict two lookup results

Open [`public_field_lookup.c`](../../../../labs/languages/reflection-workshop/practice/public_field_lookup.c).
Find the two numbers at the top. The type contains both fields. The
public table contains only 220, for `degrees_c`. Mark both numbers on
paper and circle the one you expect the table to return.

## 2. Build and check the report

Run the commands in PowerShell from the Bits2Banking repository root.
Use GCC with C23 support and an unused build folder. Run the last line
after compilation succeeds.

```powershell
$Lab = '.\content\labs\languages\reflection-workshop\practice'
$Out = '.\build\reflection-practice-c'
New-Item -ItemType Directory -Path $Out -Force | Out-Null
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror (Join-Path $Lab 'public_field_lookup.c') -o (Join-Path $Out 'public-field-lookup.exe')
& (Join-Path $Out 'public-field-lookup.exe')
```

```text
220: temperature
90: absent
```

## 3. Read the absent branch

Follow `find_public_field`. A match returns a pointer to a catalogue row.
When the search finishes without a match it returns `nullptr`, the C23
null pointer constant. The test checks the measurement's compiled offset
only after it confirms that a row exists. It then checks that ID 90 returns
the absence value.

## 4. Test what stays stable

Change only the label `temperature` to `reading temperature` in a practice
copy and rerun. Expect ID 220 to display the new label and ID 90 to remain
absent. The number still identifies the same published field.
[WG14 C23 text](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)

[Practice contents](index.md)
