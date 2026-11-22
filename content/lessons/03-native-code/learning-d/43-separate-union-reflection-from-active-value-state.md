<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/43-separate-union-reflection-from-active-value-state.md

PURPOSE:
Separate union reflection from active-value state

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate union reflection from active-value state

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `tagged_number.d` in `labs/languages/native-language-boundary` in the course checkout. Make two columns for a declared union member and the current tag. Pick a rejected access and predict which value the caller retains.

## Reflection answers a structural question

D can inspect declarations while compiling. That is useful for catalogues, checks and generated adapters, but the compiler cannot infer every rule your application assigns to runtime data. This lesson uses a numeric union to make the distinction concrete. Reflection can confirm that fields exist and overlap. A separate tag and accessor protocol decide which field a particular value is allowed to expose.

1. Review structs, enums, ref parameters and the earlier reflection lessons.
2. Open tagged_number.d alongside its C and FreeBASIC counterparts.
3. Predict what a field catalogue can establish without running the program.


## Define an explicit unselected state

NumberKind uses ubyte as its underlying type and gives invalid the value zero. The record initializes its kind to invalid. A newly declared record therefore has no selected numeric alternative in this application's contract, even though its storage has language-defined initialization. Being initialized is different from representing an admitted domain value.

~~~d
enum NumberKind : ubyte {
    invalid = 0, whole = 1, fractional = 2
}
~~~


## Overlap the numeric storage

NumberPayload is a union with long and double fields. Its members occupy overlapping storage. The example treats the payload as exactly one selected alternative at a time and never interprets the inactive member. There is no hidden runtime tag in the union declaration. TaggedNumber stores the application tag separately from the payload.

~~~d
private union NumberPayload {
    long wholeValue;
    double fractionalValue;
}
struct TaggedNumber {
    private NumberKind kind = NumberKind.invalid;
    private NumberPayload payload;
    // Complete construction and access methods are in the source file.
}
~~~


## Construct the value before returning it

The static fromWhole method creates a candidate record, writes the selected member and then sets its tag. Returning that candidate gives the caller a complete value. fromFractional performs the matching operation for double. The static keyword means no existing TaggedNumber instance is needed to call the factory. The laboratory does not publish partially changed records to another thread.

~~~d
static TaggedNumber fromWhole(long value) nothrow @nogc {
    TaggedNumber candidate;
    candidate.payload.wholeValue = value;
    candidate.kind = NumberKind.whole;
    return candidate;
}
~~~


## Use ref to preserve output on refusal

tryWhole receives a reference to a separate caller result. It checks kind first, returns false on a mismatch, and only then reads and copies the whole-number member. A ref result retains its old value unless the function assigns it. Using an out parameter would introduce initialization-on-entry semantics that do not match this preservation contract. The const method promises not to change the record through this receiver.

~~~d
bool tryWhole(ref long result) const nothrow @nogc {
    if (kind != NumberKind.whole) return false;
    result = payload.wholeValue;
    return true;
}
~~~


## Understand the effect annotations

nothrow and @nogc constrain the annotated helpers. Their paths perform numeric assignments and comparisons without throwing an Exception or allocating through the garbage collector. These attributes do not prove the tag is honest, make access thread-safe, or establish foreign ABI compatibility. main uses ordinary runtime output, so the example does not claim that the whole application is a BetterC or runtime-free program.


## Inspect declarations without reading a value

The static assertions ask whether both named members exist, compare their offsets and check that the union can hold either member. These expressions inspect declarations and layout; they do not evaluate an inactive payload in a runtime object. Compilation can reject a structural change that breaks the checks before an executable is produced.

~~~d
static assert(__traits(hasMember, NumberPayload, "wholeValue"));
static assert(__traits(hasMember, NumberPayload, "fractionalValue"));
static assert(NumberPayload.wholeValue.offsetof ==
              NumberPayload.fractionalValue.offsetof);
static assert(NumberPayload.sizeof >= long.sizeof &&
              NumberPayload.sizeof >= double.sizeof);
~~~


## Name what reflection does not prove

Those assertions cannot prove that fromWhole always writes the matching tag, that a file decoder rejected tag 99, or that a caller kept a borrowed pointer alive. They also do not prove a record contains a valid finite financial amount. Each is a separate semantic contract. A generic serializer that reads every reflected union member would violate this example's selection rule. Generate access through a reviewed tag-to-member mapping instead of assuming that every declared field is simultaneously meaningful.


## Follow the runtime checks

The exercise first constructs Whole(42). A whole read succeeds, while a fractional read fails and preserves −8.5. It then constructs Fractional(12.5), reads it successfully and verifies that a whole read fails without replacing 42. These deliberately different sentinels expose accidental output writes. The demonstration uses exactly representable values; it does not teach that arbitrary decimal fractions are exact in binary floating point.


| Stored value | Operation | Required observation |
| --- | --- | --- |
| Whole(42) | tryWhole | true; result 42 |
| Whole(42) | tryFractional | false; prior −8.5 unchanged |
| Fractional(12.5) | tryFractional | true; result 12.5 |
| Fractional(12.5) | tryWhole | false; prior 42 unchanged |
| Unknown or invalid tag | Either accessor | false; outputs unchanged |


## Test a forged state in the same module

D private visibility is module-based. The test code in tagged_number.d can deliberately assign cast(NumberKind)99 to the private tag. Normal clients in another module should use the factories. The cast does not establish membership in the enum's named alternatives. Both accessors refuse the unknown state before inspecting the payload. This deliberate corruption is a test of admission, not a recommended construction technique.


## Do not confuse a cast with conversion

Changing only the tag would relabel the existing bytes. A numeric conversion instead reads the selected source through its accessor, checks range or precision requirements, calculates a destination value and constructs a fresh record. Converting a very large long to double may lose integer precision. A money type needs its own units, scale and rounding rules. Reflection can help generate checks, but those rules must first be specified.


## Keep ownership rules proportional to the payload

The alternatives here contain no owning pointers, file handles or destructible objects. Adding such an alternative requires explicit lifetime rules for replacement, copies and destruction. A union of references is not automatically a safe variant merely because garbage collection exists. The active tag must govern cleanup as well as reads, and a foreign caller needs an independently reviewed ownership contract.


## Compile with unit checks

Use a supported D compiler. The unittest block exercises the protocol before main when unit checks are enabled; main repeats explicit runtime checks and returns a nonzero code on failure. Run each command separately and stop on an error. A test of course navigation does not qualify a D executable, and a successful C counterpart does not establish D compiler behavior.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd -unittest -checkaction=context -of=tagged_number_d.exe tagged_number.d
& .\tagged_number_d.exe
$LASTEXITCODE
~~~


## Read the expected output

A successful run prints these lines and returns zero. No raw union bytes are saved and no library consumes this record through a foreign interface.

~~~text
Umicom tagged-number checks passed.
Wrong and unknown tags preserved both output values.
Reflection checked fields and overlap, not runtime variant selection.
~~~


## Apply the idea to Umicom tools

A Studio property inspector, a compiler constant value or a Media parameter can have several alternatives. A C implementation can use an explicit enum plus union and checked accessors. D can be useful in an optional tooling experiment to inspect declarations and generate a reviewed C metadata table, while reusable production behavior remains in Framework's C services. Generated metadata must still specify valid tags, units, ranges and ownership. It is not evidence that arbitrary D records can be passed directly into the SDK.


## Troubleshoot the correct layer

1. If a static assertion fails, inspect declarations and target layout; do not weaken it merely to keep compilation moving.
2. If a mismatch changes an output, verify that no assignment occurs before the tag check and that the parameter is ref rather than out.
3. If a normal client can forge a tag, review the module boundary and API visibility.
4. If a serializer reads both payload members, redesign dispatch around the admitted tag.
5. If a foreign call misreads a value, investigate ABI and representation independently of the union's logical protocol.


## Exercises

Add a third numeric alternative and a checked accessor. Extend the structural checks and every mismatch test. Then sketch an explicit serialization format containing a one-byte tag and a documented value representation; explain why sizeof(TaggedNumber) bytes are not that format. Finally design a metadata generator that rejects unhandled union tags at compile time without ever reading an inactive runtime member.


## Official language references


- [D structs and unions](https://dlang.org/spec/struct.html)
- [D compile-time traits](https://dlang.org/spec/traits.html)


[Previous: Separate atomic access from thread lifetime](42-separate-atomic-access-from-thread-lifetime.md)

[Next: Distinguish conditional selection from argument evaluation](44-distinguish-conditional-selection-from-argument-evaluation.md)
