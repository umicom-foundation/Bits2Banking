<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/25-declare-and-inspect-field-metadata.md

PURPOSE:
Declare field metadata and inspect it at compile time

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Declare field metadata and inspect it at compile time

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `field_metadata.d` in `labs/languages/native-language-boundary` in the course checkout. Choose a field and write down its type and the rule you expect its annotation to express. Compare that expectation with what the program prints.
A program stores values such as an account number. A form also needs information about those values: a label, a help message, or a rule about which fields can be edited. Information that describes other information is called metadata. In this lesson you will attach two labels to a small D record, ask the compiler to inspect them, and generate a readable description. You will also distinguish this technique from changing the record’s values, serializing memory, or providing unrestricted runtime reflection.


## 1. Begin with an ordinary record

Open the native-language-boundary lab folder. The complete new example is field_metadata.d. A module is a named compilation unit, usually stored in one file. This module imports writeln to display text and three utilities from std.traits to inspect declarations. It uses the normal D runtime and standard library. It is not a BetterC example and it is not a Framework plugin. The example has been authored and source-reviewed; no D compiler execution is claimed in this delivery.

A struct groups named fields. uint is D’s unsigned 32-bit integer, and long is its signed 64-bit integer. This distinction matters: a C long is not guaranteed to have the same width on every operating system. balanceMinor uses an integer count of minor currency units, such as cents for a currency with two decimal places. This small exercise has no currency field and must not be treated as a complete banking model.

~~~d
struct AccountSnapshot {
    uint account;
    long balanceMinor;
}
~~~


## 2. Define the kind of annotation you need

Label is another struct, with one string field called text. @Label(...) attaches a value of that type to the following declaration as a user-defined attribute, often abbreviated UDA. An attribute is an annotation. It is not an assignment to account or balanceMinor. A user-defined attribute also does not automatically validate input, draw a form, or grant permissions. Those behaviors require code that deliberately reads and interprets it.

~~~d
struct Label { string text; }

struct AccountSnapshot {
    @Label("Account number") uint account;
    @Label("Balance in minor units") long balanceMinor;
}
~~~

The at sign is also used by built-in D attributes such as @safe and @nogc. Those have language-defined meaning enforced by the compiler. Your Label attribute only has the meaning you give it. A label saying “read only” does not itself stop writes. Keeping display metadata separate from enforcement prevents a reassuring caption from being mistaken for an implemented rule.


## 3. Read the template declaration one piece at a time

The function returns void, meaning it returns no value. T is a template parameter: a type supplied while the compiler generates a particular function. The second empty pair of parentheses means that the generated function takes no runtime arguments. In the call, !AccountSnapshot selects the template argument and the final () calls the generated function. Templates can produce different compiled functions for different types; they are not automatically a dynamic registry of all types in a running process.

~~~d
void describe(T)()
{
    // The real implementation appears in field_metadata.d.
}

describe!AccountSnapshot();
~~~


## 4. Enumerate fields, then inspect each declaration

FieldNameTuple supplies an ordered compile-time sequence of field names. FieldTypeTuple supplies the matching field types. static foreach expands a block for each item during compilation. It differs from an ordinary foreach loop that traverses runtime values. The explicit inner braces give each expanded block its own scope, so repeated names such as labels and Field do not collide.

~~~d
static foreach (index, name; FieldNameTuple!T) {
    {
        enum labels = getUDAs!(__traits(getMember, T, name), Label);
        static assert(labels.length == 1,
            "Each field needs exactly one Label");
        alias Field = FieldTypeTuple!T[index];
        writeln(name, ": ", Field.stringof, " => ", labels[0].text);
    }
}
~~~

__traits(getMember, T, name) identifies the named member declaration. getUDAs filters its attributes to those of type Label. Here enum declares a compile-time constant; it does not introduce a list of named numeric states as an enum declaration can elsewhere. static assert requires exactly one label during compilation. alias Field gives the selected field type a local name without creating a field value. stringof supplies a textual description suitable for this demonstration, not a stable interchange type identifier.


## 5. Build and run deliberately

These are commands for a learner to execute. They are not evidence that the example has already been compiled here. Keep assertions enabled while learning; a release configuration that disables runtime assertions changes which checks execute. The static assertions are compile-time checks.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd --version
dmd -unittest -of=field_metadata.exe field_metadata.d
.\field_metadata.exe
~~~

1. Open PowerShell and change to the lab directory using the command below. Verify that field_metadata.d is present.
2. Run dmd --version. If PowerShell cannot find it, return to the course installation lesson and finish installing a D compiler. Do not rename the source file to an executable.
3. Compile with unit tests enabled and check the exit code before running the result. Stop if compilation reports an error.
4. Run field_metadata.exe and compare its lines with the expected example. Keep the compiler version and command with your own results.

The labels describe the fields while the stored values remain 17 and 1250. If a compiler prints a different type spelling, examine the generated description and compiler version rather than treating the spelling as a portable protocol. The example’s semantic field types and widths are the important contract.

~~~text
account: uint => Account number
balanceMinor: long => Balance in minor units
Values remain unchanged: 17, 1250
~~~


## 6. Make a failure teach you something

A compile-time error is useful here because it identifies an incomplete schema at the point where the type is declared. It cannot prove that a banking calculation is correct or that a translated label is understandable. Those need separate domain tests and review.

1. Remove the Label annotation from one field in a temporary learning copy. Recompile. Explain why the static assertion should reject it before main executes.
2. Restore the label, then attach a second Label to the same field. Explain why “exactly one” rejects ambiguity instead of silently choosing one.
3. Change only the label text and rebuild. The displayed description changes; the instance values do not.
4. Add a new field with a label. Identify the generated block that will describe it. Decide whether the new field needs its own persistence version before saving real records.


## 7. Translate the idea across a C boundary

Framework’s production boundary remains native C. The useful idea is explicit metadata that can drive forms, diagnostics and documentation from one reviewed definition. A C implementation can expose descriptor tables with stable field IDs, names, widths and validation functions. A D tool can generate or check such declarations during its own build. This lesson does not add a production generator or claim a new Framework reflection API.

Do not send a D string object, class reference, delegate or arbitrary record bytes directly to C as a portable format. Define an extern(C) interface using matching fixed-width fields, explicit byte lengths and documented lifetimes. For files or network messages, use a versioned encoding and validate it. Memory offsets, padding and compiler-generated type names are implementation details, not durable schema identifiers.


## 8. Check your understanding

1. Explain the difference between data, metadata and an enforcement rule.
2. Identify which statements execute during compilation and which produce output when the program runs.
3. Explain why annotating a password field does not automatically redact logs. Name the code path that would have to enforce redaction.
4. Design a small descriptor for a training-data source ID. Give it a stable machine name, a human label and a length rule, then explain how both a C validator and a UI could share that definition.


## Further reading

- [D language attributes and user-defined attributes](https://dlang.org/spec/attribute.html#uda)
- [D compile-time traits](https://dlang.org/spec/traits.html)
- [std.traits reference](https://dlang.org/phobos/std_traits.html)

[Previous: Use a C callback without capturing a D delegate](24-use-an-explicit-c-callback-context.md)

[Next: Select code before the program runs](26-select-code-before-the-program-runs.md)
