<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/41-inspect-layout-without-serializing-padding.md

PURPOSE:
Inspect layout without serializing padding

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Inspect layout without serializing padding

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `record_layout.d` in `labs/languages/native-language-boundary` in the course checkout. Identify the widths of the integer fields. Record the compiler target architecture so you can compare member offsets, alignment and total record size.

## Why a structure has more than field values

A structure groups named values into a single value. A native program must also arrange its fields in memory so machine instructions and foreign functions can access them correctly. This lesson separates those two subjects: the values you mean, and the storage arrangement chosen for them. You will inspect a small D structure, compare a deliberately packed form, and explain why copying arbitrary memory bytes is not a portable way to save an account, image description or network message. Work through the earlier variables, arrays, structures and const lessons first if those words are unfamiliar.


## Open the original laboratory

PowerShell is the command interpreter used in these instructions. Set-Location chooses a folder. Get-Command identifies the program that will receive the following command; dmd -version asks that compiler for its version. If you use LDC or another D compiler, consult its own equivalent options and record the actual compiler instead of assuming the command name proves compatibility. The supplied example uses the ordinary D runtime for console output, not BetterC.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
Get-Command dmd
dmd -version
Get-Content .\record_layout.d
~~~


## Declare two integer fields

struct introduces a structure type. NativeRecord is the chosen name. Braces surround its field declarations and each declaration ends with a semicolon. ubyte holds a nonnegative one-byte integer; uint holds a nonnegative four-byte integer. The program later creates a value with kind seven and count 0x01020304. The hexadecimal prefix 0x means the following digits use base sixteen. Keeping these fields small makes it possible to draw the storage by hand.

~~~d
struct NativeRecord
{
    ubyte kind;
    uint count;
}
~~~


## Inspect three distinct properties


| Expression | What it describes |
| --- | --- |
| NativeRecord.sizeof | Total storage size in bytes, including padding. |
| NativeRecord.alignof | Address-boundary requirement for the structure. |
| NativeRecord.count.offsetof | Byte position of count relative to the record start. |
| uint.sizeof | Size of this field datatype, four bytes. |


## Read a possible arrangement

Suppose the compiler reports count at offset four and a record size of eight. Byte zero holds kind; three following bytes are padding; bytes four through seven hold the count. Padding can also appear at the end of structures so successive array elements meet alignment requirements. The example deliberately prints default-layout observations instead of asserting that every target uses this drawing. You should compare the actual result with the compiler target and ABI, meaning the application binary interface that defines conventions for compiled components.

~~~text
Illustrative default arrangement, not a universal target promise:
byte offset   0    1    2    3    4    5    6    7
meaning      kind  gap  gap  gap  count spans four bytes

The values are kind=7 and count=0x01020304.
The gaps do not become additional application fields.
~~~


## Control field packing in a separate type

Inside PackedRecord, align(1): applies one-byte alignment to the following fields. The colon introduces an attribute scope for those declarations. The example checks that this packed type has alignment one, count offset one and total size five. Packing reduces these gaps; it does not convert integer byte order or make an arbitrary foreign function accept the object. Keep ordinary Framework-facing records at the alignment required by their published declarations.

~~~d
struct PackedRecord
{
    align(1):
    ubyte kind;
    uint count;
}
static assert(PackedRecord.alignof == 1);
static assert(PackedRecord.count.offsetof == 1);
static assert(PackedRecord.sizeof == 5);
~~~


## Distinguish a compile-time check from a runtime check

static assert asks the compiler to reject a declaration if its condition is false. Its input here is type metadata that is known without running the program. An ordinary assert inside unittest runs when the executable is built with unit tests and those tests execute. Normal if statements in main also check important value observations, returning a nonzero process result on failure. None of these checks demonstrates the behavior of another compiler configuration that was not used.


## Copy fields across layouts

NativeRecord(7, 0x01020304) constructs a value for the two declared fields. PackedRecord(native.kind, native.count) constructs another value using those field values. The sizes can differ while the values still agree. That is the point of the experiment. Do not replace the typed construction with a raw copy of NativeRecord.sizeof bytes into a smaller PackedRecord: the smaller destination cannot receive that many bytes and the count may begin at a different offset.


## Static arrays own a fixed number of elements

uint[3] samples declares storage for three uint values. This is a static array: the number of elements is part of its type. In this example samples.length is three and samples.sizeof is twelve. Each element occupies four bytes. The spelling typeof(samples) asks for the compile-time type of the expression; typeof(samples).sizeof therefore lets a static assertion check the array size. This rule differs from FreeBASIC SizeOf(arrayName), so always consult the language you are actually compiling.

~~~d
uint[3] samples = [11, 22, 33];
static assert(typeof(samples).sizeof == 12);
assert(samples.length == 3);
~~~


## A slice describes a view

samples[] creates a slice over the array. auto asks the compiler to infer the variable type from its initializer. The view has a length and refers to existing storage; creating it does not copy the three integers. view.sizeof describes the slice value itself, not all the referenced elements. The program prints that descriptor size without hard-coding a pointer-width assumption. The twelve-byte payload calculation comes from view.length multiplied by uint.sizeof.

~~~d
auto view = samples[];
assert(view.length == 3);
assert(view[1] == 22);
assert(view.length * uint.sizeof == 12);
~~~


## Keep the owner alive

The backing array samples remains alive while main and its local view are being used. A borrowed view does not license accessing destroyed native memory, and a descriptor copied into a file cannot bring that memory back later. The multiplication in this tiny fixture is safe because the count is exactly three. A general interface that accepts arbitrary lengths must admit the count before multiplication and verify the complete accessible span before reading it. Use a shared checked Framework service for reusable byte-budget policies.


## Compile with the checks enabled

Run the compilation line first and stop on an error. -unittest includes the unittest blocks, -checkaction=context requests useful check-failure context, and -of chooses an output filename. After a successful compile, run the executable. PowerShell does not automatically prevent the next line from launching an old executable after a failed compiler invocation, so running the commands separately matters. The final line displays the process exit code.

~~~powershell
dmd -unittest -checkaction=context -of=record_layout_d.exe record_layout.d
& .\record_layout_d.exe
$LASTEXITCODE
~~~


## Read the results with their limits


| Output | Interpretation |
| --- | --- |
| native bytes, alignment and count offset | Observe the selected target; do not assume the illustrative eight-byte arrangement. |
| packed bytes=5, alignment=1, count offset=1 | The deliberately packed two-field type. |
| array bytes=12, elements=3, element bytes=4 | Storage owned by this static array. |
| slice descriptor bytes | Size of the view value on this target; not its payload. |
| payload bytes=12 | Counted integer storage referenced by the slice. |
| fields agree; no raw record was saved | Typed field construction preserved the meanings. |


## Use reflection for checks, not magic compatibility

Reflection means inspecting information about program declarations. Here offsetof, sizeof, alignof and typeof expose useful compile-time facts. The earlier field_metadata.d example explores richer declaration metadata. These facilities can support binding checks and generated adapters, but matching a size does not prove two APIs agree. You must also match field order, types, calling convention, ownership, nullability and semantic rules. A change to a record can require an ABI version change even when old code still compiles.


## Design file bytes explicitly

A portable encoding decides exactly what each byte means. For an illustrative kind plus a little-endian 32-bit count, a format might specify one kind byte followed by four count bytes in least-significant-first order. It would also define valid kind numbers, versioning and incomplete-input handling. This is a separate contract from native padding or packing. Existing byte-encoding exercises show the shifts and masks involved. Do not persist raw pointers, D slice descriptors, object references or uninitialized padding as if they were stable document data.


## When this helps Umicom applications

A Media client can inspect the layout of a documented image descriptor before calling a C service. A Trader integration can verify binding declarations while using explicit decimal and message contracts for real records. A Studio tool can present field metadata during development. These are possible uses for language bindings; they do not move the shared engine out of C or prove that a binding has been qualified. Keep the actual reusable validation and ownership logic in Framework and make the D client a thin adapter.


## Practice and recover

1. Draw the default record using the numbers printed by your compiler, including every gap. Label your compiler target beside the drawing.
2. Remove align(1) only in a study copy. Predict which static assertions may fail, then compile and read the diagnostic before restoring the file.
3. Explain why view.sizeof is not a byte budget for the referenced elements. Identify the owner and its lifetime.
4. Compare the FreeBASIC record_layout.bas array calculation with this D program. State which language each rule belongs to.
5. If a check fails, retain the compiler command and first diagnostic. Do not silence it by removing the assertion until you understand the target or declaration mismatch.


## Qualification boundary

The source and lesson are authored with official reference review. No D compiler execution or resulting program run has been performed in the current mirror environment. Course discovery checks and separate C tests do not qualify this D program or its ABI with Framework. Keep exact compiler and runtime evidence when you perform those checks.


## Read the language specification


- [D alignment attributes](https://dlang.org/spec/attribute.html#align)
- [D structure and field properties](https://dlang.org/spec/struct.html#struct_properties)
- [D arrays and slices](https://dlang.org/spec/arrays.html)


[Previous: Preserve qualifiers when returning a borrowed view](40-preserve-qualifiers-when-returning-a-borrowed-view.md)

[Next: Separate atomic access from thread lifetime](42-separate-atomic-access-from-thread-lifetime.md)
