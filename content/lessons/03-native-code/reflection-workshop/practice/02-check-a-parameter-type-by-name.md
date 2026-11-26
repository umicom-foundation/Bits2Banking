<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/practice/02-check-a-parameter-type-by-name.md

PURPOSE:
  Show a supported parameter type query and an absent name in required-input Umicom C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom Windows icon](../../../../assets/branding/umicom.ico)

# Check a parameter type by name in Umicom C

[Practice contents](index.md) · [Umicom C local type lesson](../02-check-a-local-type-in-umicom-c.md)

Umicom C's checked C profile can get the type of its signed input
parameter while compiling the program. The value then comes from the
host at execution time. Use one built file for two different measurements.

## 1. Read the accepted declaration

Open [`parameter_type.uc`](../../../../labs/languages/reflection-workshop/practice/parameter_type.uc).
`int umicom_run(int input)` declares the parameter within the compiled
entry. `typeof(input)` supplies the type of the local `sample`.
The separate initializer `{input}` reads the value for that run.

## 2. Compile once and run twice

Set `$UmicomC` to the tool built with local type query support. Start in
the Bits2Banking repository root. Use a fresh output folder and wait for
successful compilation before running the artifact.

```powershell
$UmicomC = 'C:\path\to\umicom-c.exe'
$Lab = '.\content\labs\languages\reflection-workshop\practice'
$Out = '.\build\reflection-practice-uc'
New-Item -ItemType Directory -Path $Out
$Artifact = Join-Path $Out 'parameter-type.umcb'
& $UmicomC compile-input (Join-Path $Lab 'parameter_type.uc') $Artifact
& $UmicomC exec-input $Artifact 20 --max-steps 64
& $UmicomC exec-input $Artifact -3 --max-steps 64
```

Expect `Result: 41` and `Result: -5`. The same bytecode doubles each signed
input and adds one. Follow the
[required-input execution guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/int-input.md)
for the host and instruction-budget contract.

## 3. Query an absent name

In [`missing_parameter_type.uc`](../../../../labs/languages/reflection-workshop/practice/missing_parameter_type.uc),
the query names `missing`. Look at the one parameter that is actually
declared. The checked query requires an earlier visible scalar name.

```powershell
$Rejected = Join-Path $Out 'missing-parameter.umcb'
& $UmicomC compile-input (Join-Path $Lab 'missing_parameter_type.uc') $Rejected
$LASTEXITCODE
Test-Path -LiteralPath $Rejected
```

Expect `type query requires a visible scalar local`, exit status 1 and
`False` for the new artifact. If an older artifact already has that
name, repeat the exercise in a fresh folder so the path check describes
this attempt.

## 4. Change the source of the value

Keep `typeof(input)` and change only the initializer to `{17}` in a copy.
Use a new artifact path. When you execute it with either input, expect 35.
The type query still uses the declared parameter. The initializer now
sets the value independently.

[Practice contents](index.md)
