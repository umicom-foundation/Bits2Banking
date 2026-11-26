<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/practice/07-compare-exact-declared-types.md

PURPOSE:
  Exercise successful and unmatched FreeBASIC TypeOf comparisons in the preprocessor.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom Windows icon](../../../../assets/branding/umicom.ico)

# Compare exact declared types in FreeBASIC

[Practice contents](index.md) · [FreeBASIC type and catalogue lesson](../07-read-a-basic-type-and-catalogue.md)

Suppose a small native adapter asks for a field declared as `Long`.
This exercise asks the FreeBASIC compiler whether two proposed fields
have exactly that declared type.

## 1. Check the types before the values

Open [`exact_type_choice.bas`](../../../../labs/languages/reflection-workshop/practice/exact_type_choice.bas).
`degrees` is declared as `Long`, a 32-bit integer in FreeBASIC.
`fractionalDegrees` is `Double`. The `#if` directives compare the
declared types during compilation. The computed choice determines which
`Print` statement is included in the executable.
[FreeBASIC TypeOf](https://www.freebasic.net/wiki/KeyPgTypeof)

## 2. Compile in the fb dialect

Use FreeBASIC 1.10 or later from a PowerShell terminal in the
Bits2Banking repository root. Use an unused build folder and run
the executable after compilation succeeds.

```powershell
$Lab = '.\content\labs\languages\reflection-workshop\practice'
$Out = '.\build\reflection-practice-basic'
New-Item -ItemType Directory -Path $Out -Force | Out-Null
$Program = Join-Path $Out 'exact-type-choice.exe'
fbc -lang fb -x $Program (Join-Path $Lab 'exact_type_choice.bas')
& $Program
```

```text
first member: admitted
second member: refused
```

## 3. Check the other branch in a copy

Give `fractionalDegrees` a `Long` type and the whole-number initializer
`68`. Rebuild and check that its second line changes to
`second member: admitted`. The name of the variable stays the same.
The compiler's answer follows its type declaration.

## 4. Describe the decision

Say what the compiler compared and what the running program printed.
An adapter can use an exact declaration check when its format requires
one type. A separate conversion rule would be a different decision.

[Practice contents](index.md)
