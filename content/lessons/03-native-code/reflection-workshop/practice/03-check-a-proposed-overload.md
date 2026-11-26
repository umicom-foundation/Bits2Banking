<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/practice/03-check-a-proposed-overload.md

PURPOSE:
  Teach D overload discovery and semantic checking of proposed calls.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom Windows icon](../../../../assets/branding/umicom.ico)

# Check a proposed overload in D

[Practice contents](index.md) · [D member reflection lesson](../03-check-inherited-members-in-d.md)

Two functions can share a name while accepting different kinds of input.
Each declaration is an overload. A report generator can check the
available signatures before it prepares a call.

## 1. Identify the choices

Open [`overload_probe.d`](../../../../labs/languages/reflection-workshop/practice/overload_probe.d).
`DisplayCheck` has two static `prepare` declarations. One accepts an
integer and the other accepts text. A complete `Measurement` groups
one integer inside a structure. Predict which proposed call matches.

## 2. Follow the two compiler queries

1. `getOverloads` finds the declarations with name `prepare`.
2. `__traits(compiles, ...)` checks whether the proposed expression is
   legal. The integer call can resolve. The sample defines no conversion
   from `Measurement` that makes it match either parameter.
3. The assertions make these observations part of compilation. The
   runtime output prints the compiler's answers without invoking `prepare`.

[D compiler traits](https://dlang.org/spec/traits.html)

## 3. Compile and compare

Use a DMD terminal and an unused build folder. Run the commands from the
Bits2Banking repository root and stop if compilation reports an error.

```powershell
$Lab = '.\content\labs\languages\reflection-workshop\practice'
$Out = '.\build\reflection-practice-d'
New-Item -ItemType Directory -Path $Out -Force | Out-Null
$Program = Join-Path $Out 'overload-probe.exe'
dmd -w "-of=$Program" (Join-Path $Lab 'overload_probe.d')
& $Program
```

```text
prepare overloads: 2
integer argument: admitted
whole measurement: refused
```

## 4. Offer the field instead

In a practice copy add a third `compiles` query using
`Measurement(68).degreesC` as the argument. Print `field argument: admitted`
when it succeeds. The expression now supplies the integer field. Keep the
original refused case so the two forms stay visible together.

[Practice contents](index.md)
