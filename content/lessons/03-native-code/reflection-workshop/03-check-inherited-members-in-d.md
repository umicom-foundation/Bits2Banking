<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/reflection-workshop/03-check-inherited-members-in-d.md

PURPOSE:
  Use D declaration traits to distinguish direct members from names inherited through a base class.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Find inherited members in D

[Previous · Umicom C](02-check-a-local-type-in-umicom-c.md) · [Workshop](index.md)
· [Next · Read Java record components](04-read-java-record-components.md)

A class can use declarations it inherits from a base class. A report may
need to answer two separate questions. Which names come from this class
itself? Which names become visible through its base classes?

## 1. Draw the two classes

Open [`inherited_members.d`](../../../labs/languages/reflection-workshop/inherited_members.d).
Draw `BaseProbe` above `WaterProbe`. Put `threshold` in the first box and
`sampleCount` in the second. The base class is the declaration a derived
class builds on. The colon in `WaterProbe : BaseProbe` marks that
relationship.

## 2. Compare the compiler's answers

1. `__traits(derivedMembers, WaterProbe)` gives the names declared for the
   selected class without its base classes.
2. `__traits(allMembers, WaterProbe)` also includes inherited names.
3. `staticIndexOf` searches each compile-time sequence for a specific name.
   A nonnegative index means the name occurs there. The program checks
   membership and can use any order the compiler provides.
4. `static assert` makes the three expected facts conditions of compilation.
   `main` displays those facts when you run the executable. The sample
   creates no `WaterProbe` instance.

The language specification leaves the order of the two member sequences
unspecified. Reports that promise a user-facing order need their own
ordering rule. [D traits reference](https://dlang.org/spec/traits.html)
· [D staticIndexOf](https://dlang.org/phobos/std_meta.html#staticIndexOf)

## 3. Build and compare the three results

Use DMD with the standard D library. If needed, follow
[Install D and compile a first program](../learning-d/01-install-and-run.md).
Run these commands from the Bits2Banking repository root and stop if
the compilation fails.

```powershell
dmd --version
New-Item -ItemType Directory -Path '.\build\reflection-d' -Force | Out-Null
dmd -w -of=.\build\reflection-d\inherited_members.exe .\content\labs\languages\reflection-workshop\inherited_members.d
.\build\reflection-d\inherited_members.exe
```

```text
direct threshold: no
all threshold: yes
direct sampleCount: yes
```

Read each line back to the diagram. If the code fails at the `std.meta`
import, confirm which D compiler and standard library your terminal uses.
If a static assertion fails after an edit, compare the exact case-sensitive
member names and the class that declares each one.

## 4. Ask about one new name

Add a `bool ready;` declaration to `WaterProbe` in a practice copy. Add a
fourth membership check for `ready` using `DirectMembers`, then print a
line with the result. After rebuilding, expect that check to say yes.
The source declaration and the compiled report now agree on the added
member.

[Next · Read Java record components](04-read-java-record-components.md)
