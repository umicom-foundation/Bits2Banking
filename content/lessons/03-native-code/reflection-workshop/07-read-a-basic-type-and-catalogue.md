<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/07-read-a-basic-type-and-catalogue.md

PURPOSE:
  Teach exact FreeBASIC type queries and explicit field metadata through a complete local example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read a FreeBASIC type and catalogue

[Previous · Python](06-inspect-a-python-property.md) · [Workshop](index.md)

BASIC has several dialects. This lesson uses the `fb` dialect of FreeBASIC
1.10 or later. It asks the compiler about one member's type and reads a
small field catalogue the application supplies.

## 1. Read the measurement type

Open [`manual_catalogue.bas`](../../../labs/languages/reflection-workshop/manual_catalogue.bas).
`Reading` is a user-defined type. It groups a station identifier and a
temperature in one value. The example stores both as `Long`, a 32-bit
signed integer in FreeBASIC.

```freebasic
Dim As TypeOf(sample.degreesC) editable = sample.degreesC
editable = 70
```

1. `TypeOf(sample.degreesC)` supplies the type of the new variable.
2. The initializer copies the current measurement.
3. The assignment replaces the value in `editable`. The reading still
   has its earlier value.
4. `SizeOf(editable)` reports the byte count for that variable.

[FreeBASIC TypeOf](https://www.freebasic.net/wiki/KeyPgTypeof)
· [FreeBASIC Long](https://www.freebasic.net/wiki/KeyPgLong)

## 2. Read the public table

Find `descriptions(0 To 1)`. The product code chooses the two text names
and their units. The loop visits the catalogue's lower and upper indices
using `LBound` and `UBound`. A program can use this approach to publish
just the labels its interface promises.

`TypeOf` answers a question about an expression during compilation. This
runtime table gets its labels from the strings you entered.

## 3. Compile and read the report

First follow [Learning FreeBASIC](../learning-freebasic/index.md) if you
need to prepare your compiler. From the Bits2Banking repository root, use
a PowerShell terminal with your FreeBASIC tool available.

```powershell
fbc -version
New-Item -ItemType Directory -Path '.\build\reflection-basic' -Force | Out-Null
fbc -lang fb -x .\build\reflection-basic\manual_catalogue.exe .\content\labs\languages\reflection-workshop\manual_catalogue.bas
.\build\reflection-basic\manual_catalogue.exe
```

```text
station_id - station number
degrees_c - degrees Celsius
editable local bytes: 4
editable local value: 70
stored measurement: 68
```

If the compiler reports an error at `TypeOf`, check the dialect and
version. The example relies on support for applying `TypeOf` to a member
of a user-defined type.

## 4. Check what a rename changes

In a practice copy, rename the declaration and every use of `degreesC` to
`measuredC`. Rebuild and see that the editable variable is still four bytes.
The string `"degrees_c"` still labels the report. Change that separate row
only when you intend to alter the external label. A display name can stay
stable across a source rename.

[Return to the workshop](index.md) · [Compare the native C23 catalogue](01-name-fields-in-native-c.md)
