<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/29-turn-field-metadata-into-explicit-checks.md

PURPOSE:
Turn field metadata into explicit checks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Turn field metadata into explicit checks

[Course contents](index.md)

## What you will build

You will write a small D program that describes three preview settings and checks their values. Reflection discovers the fields at compile time. Ordinary comparisons validate one object's values while the program runs. You will learn why those are different jobs, how to reject incomplete rules before compilation finishes, and how the same design idea relates to Umicom Framework's existing C reflection registry. This lesson continues the field-label example in lesson 25. The complete new source is labs/languages/native-language-boundary/reflected_ranges.d. It is an original teaching example, not a production D dependency.


## 1. Separate a description from a rule being enforced

Metadata is information about other information. A field name and its type are metadata; a label saying Width is metadata too. A declaration that says width should be between 1 and 8192 describes a rule. It does not itself stop another part of the program assigning zero. Enforcement happens only when code checks the value and acts on the result. Keep this distinction visible when building editors, configuration screens or import tools. A user interface may explain a rule, but the shared service must still validate requests that arrive through other paths.


## 2. Declare an annotation type

InclusiveRange is a struct with two long fields, minimum and maximum. Inclusive means both endpoints are accepted. D's long is a signed 64-bit integer; it is not necessarily the same width as C's long on every operating system. The example uses long for rule boundaries and accepts only D uint and long data fields. Every value of those two types fits the comparison type. Adding ulong would need a different checked conversion policy because its largest values do not fit a signed long.

~~~d
struct InclusiveRange { long minimum; long maximum; }
struct PreviewOptions
{
    @InclusiveRange(1, 8192) uint width;
    @InclusiveRange(1, 8192) uint height;
    @InclusiveRange(1, 1000) uint steps;
}
~~~


## 3. Read the annotation syntax

The @ before InclusiveRange attaches a user-defined attribute, often abbreviated UDA, to the following declaration. The numbers form a compile-time instance of the annotation struct. They do not add two boundary fields to every PreviewOptions object. The actual object still holds width, height and steps. The example defines what InclusiveRange means by writing a validator; the compiler does not invent that meaning. A missing annotation or two conflicting annotations will be rejected by our own static assertions.


## 4. Make the validator a template

The function declaration has two parameter lists: firstInvalidField(T)(ref const T value). The first introduces the type parameter T, allowing the compiler to produce a suitable function for a selected record type. The second is the ordinary runtime parameter list. ref borrows the caller's object rather than making a whole-record copy. const prevents this function from changing the object through that reference. It does not promise that another alias or thread cannot change the object, so callers must arrange stable access. The returned string is empty for success or names the first out-of-range field.


## 5. Discover names and types while compiling

FieldNameTuple!T obtains the stored field names. The exclamation mark introduces a template argument; it is not the logical-not operator in this position. static foreach expands a block for each compile-time entry. FieldTypeTuple!T[index] selects the matching field type, and alias gives that type a local name, Field. The extra braces inside static foreach create a distinct scope for each expansion so names such as Field and rules do not collide. This is code chosen at compilation, not a runtime search through source text.

~~~d
static foreach (index, name; FieldNameTuple!T) {
    {
        alias Field = FieldTypeTuple!T[index];
        static assert(is(Field == uint) || is(Field == long));
        enum rules = getUDAs!(__traits(getMember, T, name), InclusiveRange);
        static assert(rules.length == 1);
        static assert(rules[0].minimum <= rules[0].maximum);
        // The runtime comparison follows here.
    }
}
~~~


## 6. Inspect the declared member, then read the object's value

__traits(getMember, T, name) identifies the declared member so getUDAs can select its InclusiveRange annotations. Later, __traits(getMember, value, name) accesses that member on the particular runtime object. The first expression concerns the type declaration; the second concerns stored data. The enum declaration gives rules a compile-time value. static assert checks the schema while compiling. In contrast, the ordinary if compares the actual numeric field against the accepted range whenever the function runs. This separation avoids confusing a valid schema with a valid object.

~~~d
const long number = cast(long)__traits(getMember, value, name);
if (number < rules[0].minimum || number > rules[0].maximum)
    return name;
~~~


## 7. Follow the complete control flow

For PreviewOptions, the generated checks visit width, height and steps in field order. A width of zero returns width immediately. If width is acceptable but height is 8193, the result is height. If all fields are within their ranges, the function reaches return "". It deliberately returns only the first failure. An application that needs every failure would need a bounded result collection and an explicit capacity contract. This function neither repairs values nor starts a preview job. The caller decides how to display the error and whether to proceed.


## 8. Compile with tests enabled

Use the D compiler installed in the first course lesson. Confirm its actual location and version; a command with a familiar name can be an unrelated shell alias or wrapper. The following commands use DMD. They build a standalone D teaching program and do not link Framework. Run one command at a time and stop on failure. -unittest includes the unittest blocks, while -checkaction=context requests useful check diagnostics. Keep checks enabled during learning; do not add -release merely to suppress a failing assertion.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
Get-Command dmd
 dmd --version
 dmd -unittest -checkaction=context -of=reflected-ranges.exe reflected_ranges.d
& ".\reflected-ranges.exe"
~~~


## 9. Know the expected result and qualification limit

The valid record is 640 by 360 with 20 steps. The invalid record has width zero. The intended output includes Valid object: true, First invalid field: width, and Original values remain: 640 x 360, steps 20. The unittest block covers low and high failures, inclusive endpoints, two errors with a defined first result, and unchanged valid input. The example has been source-reviewed but has not been compiled in the current qualification environment because no verified D compiler is available there. These are expected results for you to check, not a reported D test pass.


## 10. Try a compile-time failure separately

1. Copy the example to a scratch directory so the original remains a useful reference.
2. Remove the InclusiveRange annotation from width, then compile. The static assertion should explain that exactly one annotation is required.
3. Restore the annotation and reverse its limits to InclusiveRange(8192, 1). Compilation should reject the reversed range.
4. Restore the limits and change width's type to string. The supported-type assertion should reject the schema rather than attempt a numeric cast.
5. Restore the original source and rebuild before testing runtime invalid values. A schema error and an out-of-range value are different experiments.


## 11. Check what the ranges do not prove

Width 8192 and height 8192 are each in range, but their combined image can still consume substantial memory. Channels, bytes per element, batch size, frames, temporary tensors and model weights add further costs. A field range also says nothing about authorization, file ownership, a model's supported resolution or a device's capacity. Cross-field rules and overflow-checked memory calculations belong in a separate shared service. Reflection helps keep repetitive metadata work consistent; it does not replace domain reasoning or make a program safe by itself.


## 12. Compare with Umicom Framework's C reflection

Framework already defines UmiReflectionTypeDescriptor, UmiReflectionFieldDescriptor and an owned registry. C declarations use UMI_REFLECTION_FIELD and UMI_REFLECTION_ARRAY_FIELD to obtain offsets and sizes through the C compiler. Registration validates descriptor bounds and copies accepted arrays. That is different from D's compile-time field discovery: the C metadata is explicit. A field description string does not automatically create a numeric validator. Reuse the existing Framework registry when implementing inspectors; do not create another registry in each application or claim this D example automatically generates C bindings.


## 13. Follow metadata ownership

A C registry must not keep pointers into a temporary caller array after promising to own its metadata. Nonempty spans need independent copies. Empty spans need a clear representation too: Framework now uses null descriptor pointers when the matching count is zero, even if the caller supplied a nonnull pointer. A retrieved snapshot's populated descriptor pointers refer into that exact snapshot object. Copying the entire C struct by value copies those pointer values; it does not make them point into the new struct's arrays. Use the documented snapshot API and lifetime rather than assuming every struct is freely relocatable.


## 14. Plan a reviewed integration

If a project needs a D client, place a narrow, reviewed C ABI between it and Framework. Decide integer widths, string encoding, ownership, error values and whether callbacks are synchronous. Keep reusable validation and memory policy in Framework's C services. D reflection can help a teaching tool detect missing fields or generate a reviewed catalogue, but generated code still needs tests and versioned contracts. This lesson's normal D program uses the standard library and is not presented as a BetterC or no-runtime executable. Follow lesson 19 before crossing that boundary.


## Which stage performs each operation?

| Operation | Stage | Result |
| --- | --- | --- |
| Read field names and annotations | Compilation | A selected set of generated checks |
| Reject a missing or reversed range | Compilation | A diagnostic from static assert |
| Check width = 0 | Program execution | The field name width |
| Assess total model or image memory | Separate runtime service | An estimate with explicit limits |
| Approve an action or allocate storage | Separate application policy | A decision with ownership and failure handling |

## Further reading

- [D user-defined attributes](https://dlang.org/spec/attribute.html#uda)
- [D standard type and attribute traits](https://dlang.org/phobos/std_traits.html)
- [Framework reflection descriptor definitions](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/reflection/types.h)
- [Complete reflected range example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/reflected_ranges.d)

[Previous: Look up records without confusing storage with learning](28-look-up-records-with-associative-arrays.md)

[Next: State the effects of a binary reader](30-state-the-effects-of-a-binary-reader.md)
