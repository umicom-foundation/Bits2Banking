<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/01-name-fields-in-native-c.md

PURPOSE:
  Teach compile-time type queries and an explicit field catalogue with an original C23 program.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Describe fields in native C23

[Workshop](index.md) · [Next · Query a local type in Umicom C](02-check-a-local-type-in-umicom-c.md)

A catalogue is a table a program can read to find a field's label and position.
In C23 you can give a compiler one field list and use it twice. You can also
ask the compiler for the type of one expression. Try both on a workbench
reading with a station number and a temperature.

## 1. Open the sample

From the Bits2Banking repository root, open
[`type-catalogue.c`](../../../labs/languages/reflection-workshop/type-catalogue.c).
Use a C compiler with `-std=c23` support and an available C standard library.
If this is your first native build, start with
[Learning C](../../../courses/learning-c/index.html).

Find `READING_FIELDS`. Each entry has a C type, a member name and a label.

```c
#define READING_FIELDS(X) \
    X(unsigned int, station_id, "station number") \
    X(int, degrees_c, "degrees Celsius")
```

## 2. Follow both uses of the list

1. `DECLARE_FIELD` forms the member declarations. For `degrees_c`, it
   produces `int degrees_c;`.
2. `DESCRIBE_FIELD` builds a table entry. `#name` turns the member name
   into text and `offsetof(Reading, name)` supplies the position from
   the start of the structure.
3. `typeof_unqual(saved.degrees_c)` gives the editable local the member's
   unqualified type. The initializer selects 68 and the next line sets
   this local to 70. The original reading keeps its 68.
4. `_Generic` chooses one of the labels supplied in the sample for the
   editable local's type.

C23 gives you the type query and the offset expression. The compiler gets
the field list and display labels from the program's single reviewed macro
list. A field's byte position depends on the compiled layout, so the sample
checks the two positions without publishing guessed offsets.
[WG14 C23 text, `6.7.3.6](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)

## 3. Build and read the report

Use a PowerShell terminal with GCC available. The reference toolchain is
GCC 16.2.0. Run each command separately. Continue to the last command
when compilation succeeds.

```powershell
gcc --version
New-Item -ItemType Directory -Path '.\build\reflection-c' -Force | Out-Null
gcc -std=c23 -Wall -Wextra -Wpedantic -Werror .\content\labs\languages\reflection-workshop\type-catalogue.c -o .\build\reflection-c\type-catalogue.exe
.\build\reflection-c\type-catalogue.exe
```

```text
station_id - station number
degrees_c - degrees Celsius
editable local type: int
editable local value: 70
stored measurement: 68
```

If GCC reports an unknown `-std=c23` option, check the compiler version
and select a build that supports this standard and `typeof_unqual`.
Keep the compiler diagnostics visible. A successful run needs the original
member and editable local to appear with their two separate values.

## 4. Change one public label

In a practice copy, change `"degrees Celsius"` to `"temperature in Celsius"`
inside `READING_FIELDS`. Rebuild the copy to the same private output folder.
Find the label in the second output line and check that the two numeric
values stay at 70 and 68.

[Next · Query a local type in Umicom C](02-check-a-local-type-in-umicom-c.md)
