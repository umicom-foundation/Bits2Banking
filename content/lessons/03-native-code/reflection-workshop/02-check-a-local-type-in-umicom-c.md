<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/02-check-a-local-type-in-umicom-c.md

PURPOSE:
  Demonstrate an accepted and refused local type query in the real Umicom C checked C profile.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Query a local type in Umicom C

[Previous · Native C23](01-name-fields-in-native-c.md) · [Workshop](index.md)
· [Next · Find inherited members in D](03-check-inherited-members-in-d.md)

A type tells the interpreter what sort of value a local can hold.
A qualifier adds a rule. `const` means that the program cannot update the
local through that declaration. The current Umicom C checked C profile
supports a small, useful type query during program admission.

## 1. Look at the three declarations

Open [`checked-local.c`](../../../labs/languages/reflection-workshop/checked-local.c).

```c
const unsigned char seed = {27};
typeof(seed) stored = {8};
typeof_unqual(seed) editable = {5};
```

1. `seed` declares a const unsigned byte.
2. `typeof(seed)` uses that type and keeps the const qualifier. The new
   local gets the initializer's value 8.
3. `typeof_unqual(seed)` uses the corresponding unqualified type. The
   initializer puts 5 into `editable`.
4. The sample increments `editable` to 6, then computes `6 * 10 + 8`.
   The returned value gives you a quick check of both locals.

The supported query refers to one earlier visible scalar name. The current
checked profile accepts these queries for `int`, `bool` and
`unsigned char` locals, and for the integer input parameter of
`int umicom_run(int input)`. Use the checked C source form shown here.
General type-name and expression queries belong to the native C23 lesson.
[Umicom C language reference](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

## 2. Interpret the accepted sample

Set `$UmicomC` to your built Umicom C console tool. Use the edition of the tool
that includes both local query specifiers. From the Bits2Banking repository
root, run the version check and the interpreter.

```powershell
$UmicomC = 'C:\path\to\umicom-c.exe'
$ReflectionLab = '.\content\labs\languages\reflection-workshop'
& $UmicomC --version
& $UmicomC interpret (Join-Path $ReflectionLab 'checked-local.c')
```

Read through the statement trace to `Result: 68`. The trace explains the
program steps. The `Result` line reports the value returned by `main`.
The feature is available in development builds that report `Umicom C 0.1.0`.
Run the two samples to check the behavior of the build you actually selected.

## 3. Check the refused update

Open [`checked-const-refusal.c`](../../../labs/languages/reflection-workshop/checked-const-refusal.c).
This file deliberately increments the const `stored` local. Interpret it
as a separate case.

```powershell
& $UmicomC interpret (Join-Path $ReflectionLab 'checked-const-refusal.c')
$LASTEXITCODE
```

Look for `cannot update a read-only local integer` at `++stored`. The
interpreter exits with status 1 for this fixture. If both cases fail at
the keyword, confirm the path to the tool and compare its build with the
language reference for your checkout.

The local query supplies a type for a new declaration while the program
is checked. Use an explicit public catalogue for settings names and text
labels in a shared Framework tool.

[Next · Find inherited members in D](03-check-inherited-members-in-d.md)
