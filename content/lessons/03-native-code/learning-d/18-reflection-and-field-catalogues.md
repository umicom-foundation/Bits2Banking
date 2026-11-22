<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/18-reflection-and-field-catalogues.md

PURPOSE:
Inspect fields with compile-time reflection

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Inspect fields with compile-time reflection

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `reflection.d` in `labs/languages/native-language-boundary` in the course checkout. Find the record declaration before reading the reflection code. Write down each field name and type so you can compare the list with what the program discovers.
Reflection means inspecting information about a program’s types or members. D can perform substantial inspection at compile time. This can generate repetitive adapters while preserving explicit types. Runtime reflection is a different question: what metadata remains available after the executable starts?

~~~d
import std.stdio : writeln;
import std.traits : FieldNameTuple;
struct MediaOptions
{
    uint width = 640;
    uint height = 360;
    bool preview = true;
}
void main()
{
    MediaOptions options;
    static foreach (name; FieldNameTuple!MediaOptions)
        writeln(name, " = ", __traits(getMember, options, name));
}
~~~

1. Save as reflection.d. Compile with dmd -w -g reflection.d and run. Expect width = 640, height = 360 and preview = true.
2. FieldNameTuple obtains the field names; the exclamation mark instantiates a template. static foreach expands the body for each name during compilation.
3. __traits(getMember, options, name) selects the named field. It does not execute a text command from an end user.
4. Add a uint frames = 1 field and rebuild. The catalogue expands because the compiler sees the new definition. The old executable cannot discover that source change until rebuilt.

__traits(allMembers, SomeType) can inspect a broader member set than only data fields. typeof obtains a type; is expressions can check type relationships. User-defined attributes attach programmer-chosen metadata. A string mixin creates source text during compilation, so its input must be controlled and reviewable; reflection is not a reason to compile untrusted model output.

A useful Umicom application could derive a settings descriptor table from approved declarations, then expose that table through a C ABI for Studio property editors. Stable field identifiers, privacy rules, valid ranges and serialization migrations still require design. Automatically listing a secret field would be a defect. This lesson demonstrates D inspection; it does not claim that Framework currently imports D types or offers a new designer UI.


## Practice

Add a private implementation detail and decide whether it belongs in a public settings catalogue. Explain why a hand-reviewed allowlist can be more appropriate than exposing every discovered member.


## Further reading

- [D traits reference](https://dlang.org/spec/traits.html)
- [D std.traits](https://dlang.org/phobos/std_traits.html)

## Continue learning

[Previous: Use templates and compile-time evaluation](17-templates-and-compile-time-work.md) · [Course contents](index.md) · [Next: Separate C linkage from the BetterC subset](19-c-abi-and-betterc.md)
