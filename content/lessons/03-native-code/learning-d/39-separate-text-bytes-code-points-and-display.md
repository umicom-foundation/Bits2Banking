<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/39-separate-text-bytes-code-points-and-display.md

PURPOSE:
Separate text bytes, code points and display

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate text bytes, code points and display

[Course contents](index.md)

## Begin with one word: unit

A count is useful only when you know what it counts. A byte is eight bits. A code unit is one storage element in an encoding. A Unicode code point is a numbered text value. A grapheme cluster groups code points for user-perceived text. A model token is chosen by a particular tokenizer. These are different units. This lesson uses a tiny D program to measure the same text in several representations and to reject malformed input before decoding it.


## Choose three known code points

Our original sample contains uppercase A, Greek capital omega and a slightly smiling face. We write the latter two with numeric source escapes so that the source file remains easy to inspect without depending on an editor’s glyph support. U+0041 is decimal 65. U+03A9 is decimal 937. U+1F642 is decimal 128578. U+ is a notation for a Unicode code point, not text that must appear in the stored string.


| Text item | Code point | UTF-8 bytes in hexadecimal |
| --- | --- | --- |
| A | U+0041 | 41 |
| Capital omega | U+03A9 | CE A9 |
| Slightly smiling face | U+1F642 | F0 9F 99 82 |


## Declare three string representations

D uses char units for UTF-8, wchar units for UTF-16 and dchar units for UTF-32. Their ordinary immutable string aliases are string, wstring and dstring. A literal suffix w or d chooses the latter representations. The backslash-u source escape has four hexadecimal digits, while backslash-U has eight. These source spellings describe code points; the chosen string representation determines their stored units.

~~~d
string utf8 = "A\u03A9\U0001F642";
wstring utf16 = "A\u03A9\U0001F642"w;
dstring utf32 = "A\u03A9\U0001F642"d;
~~~


## Compute lengths before running the program

A occupies one unit in each representation. Omega takes two UTF-8 bytes but one UTF-16 and one UTF-32 unit. The smiling face takes four UTF-8 bytes, two UTF-16 units and one UTF-32 unit. A pair of UTF-16 units represents that supplementary code point. Adding the contributions gives lengths seven, four and three. Those lengths describe array elements, not equal byte counts.


| Representation | Unit size | Array length | Text payload bytes |
| --- | --- | --- | --- |
| UTF-8 string | 1 byte | 7 | 7 |
| UTF-16 wstring | 2 bytes | 4 | 8 |
| UTF-32 dstring | 4 bytes | 3 | 12 |


## Do not mistake payload size for total memory use

The table counts only stored text units. A string variable also has a representation describing a view of storage, and a complete process has code, stack, runtime and other allocations. A source literal may occupy static storage. Multiplying length by unit size is useful for an explicitly defined text span, but it is not a measurement of total process memory. This distinction is important when comparing model applications: changing language does not remove the memory required for model weights, activations or decoded media.


## Decode deliberately with dchar iteration

A foreach loop over UTF-8 text with an explicit dchar value decodes successive code points. In the two-variable form used here, the index identifies the starting code-unit offset in the input. Because our input is UTF-8, those offsets are byte offsets. The expected offsets are zero, one and three. They are not the ordinal numbers zero, one and two of the displayed items. The loop never treats a continuation byte as the beginning of an independent ASCII character.

~~~d
foreach (size_t offset, dchar point; utf8)
{
    writeln("Byte offset ", offset, ": code point ", cast(uint) point);
}
~~~


## Follow the byte boundaries on paper

Write seven boxes and fill them with 41 CE A9 F0 9F 99 82. Draw one bracket around box zero, one around boxes one and two, and one around boxes three through six. These groups are the encoded code points. Cutting the string after box one would leave CE without its continuation byte. A byte limit that blindly cuts at any position can therefore create invalid UTF-8. A valid boundary is a property of the encoding, not merely an in-range array index.


## Validate a borrowed span first

The helper codePointCount accepts string text without taking ownership of an external allocation. It calls std.utf.validate and then counts decoded dchar values. For this small example validation is intentionally explicit even though decoding also has its own behavior. Validation establishes whether the supplied sequence is structurally well formed. It does not establish that text is truthful, permitted in a field, normalized, harmless markup or a suitable training sample.


## Create a malformed example without a broken source file

rejectsMalformedUtf8 constructs two char units from numeric values C3 and 28. C3 begins a multibyte UTF-8 sequence, but 28 is the ASCII opening parenthesis and is not a valid continuation. The source file itself remains valid because these bytes are constructed as data. The function calls validate inside try. catch handles UTFException and returns true to confirm the intended refusal. If no exception occurs, it returns false and the caller reports failure.

~~~d
char[2] malformed = [cast(char) 0xC3, cast(char) 0x28];
try
{
    validate(malformed[]);
}
catch (UTFException error)
{
    return true;
}
~~~


## Understand exceptions without hiding failures

An exception transfers control from an operation that cannot complete normally to a matching handler. This exercise catches the specific encoding exception around one intentionally bad input. It does not catch every exception and label the whole application successful. A malformed-data refusal is expected in this test. An allocation failure, unrelated logic error or failed compiler invocation is a different event that needs its own evidence. The example uses the ordinary D runtime; it does not claim BetterC compatibility or allocation-free exception handling.


## Separate code points from visible text

The second sample is e followed by U+0301, a combining acute accent. Its UTF-8 representation has three bytes and two code points. A renderer may combine them visually into an accented letter, but this program does not implement grapheme segmentation or rendering. It also does not normalize the sequence to a precomposed character. Two texts can look alike while having different byte sequences. That matters for search, signatures, deduplication and training-data comparisons.


## Read the checks in the complete source

Open utf_text_units.d. main checks all three lengths, the numeric value and starting offset of each decoded item, the combining sample, and the malformed-input refusal. It returns a nonzero code if any expectation is broken. The unittest block also checks empty input and distinguishes a literal backslash sequence from an actual source escape. Two backslashes in a source string represent an ordinary backslash; they do not start the same Unicode escape as one backslash. Those small cases make the intended interpretation reviewable.


## Compile and run with checks enabled

Use the D compiler installation from the setup lesson. -unittest includes unittest blocks. -checkaction=context requests contextual failure reporting for supported checks. Run the commands separately, stopping if compilation fails so that a previous executable is not confused with the new source. The current example is authored and reference-reviewed; its D compiler and runtime qualification remains to be performed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd -unittest -checkaction=context -of=utf_text_units.exe utf_text_units.d
& .\utf_text_units.exe
$LASTEXITCODE
~~~


## Compare numeric output instead of relying on glyphs

Expect the lines below and exit code zero. The program prints numeric values, so a terminal lacking an emoji font does not change the comparison. If the third byte offset is two rather than three, inspect whether the loop is reporting an item counter instead of the original UTF-8 offset. If malformed input passes, keep the exact toolchain version and output for investigation.

~~~text
UTF-8 units: 7
UTF-16 units: 4
UTF-32 units: 3
Byte offset 0: code point 65
Byte offset 1: code point 937
Byte offset 3: code point 128578
Combining example: 3 bytes, 2 code points
Malformed UTF-8 refused
~~~


## Apply explicit units at the C boundary

A C API needs a documented representation. If it accepts UTF-8 bytes, provide the UTF-8 span and byte length, keep its storage alive for the promised duration, and establish whether the callee may retain or modify it. A wchar pointer is not automatically an interchangeable native wide-string pointer on every platform. A terminator is a separate contract: D slice length should not be discarded in favor of assuming zero termination. Compile-time reflection can check wrapper types, but it cannot prove that a pointer remains valid after a background task outlives its caller.


## Connect the lesson to LLM preparation

Valid UTF-8 is only an early admission step. A training pipeline still needs rights and provenance, content review, splits, tokenizer identity and the model’s expected sample structure. Tokenization maps text to model-specific integer IDs. Seven UTF-8 bytes do not imply seven tokens or three tokens. A vector embedding is a numerical representation used for tasks such as retrieval; it is not the same thing as these UTF code units. Keep the original text and transformation record so an unexpected token sequence can be traced to its source.


## Practice with small controlled changes

1. Replace omega with an ASCII digit and predict all three lengths before compiling.
2. Keep the smiling face but remove A. Predict UTF-8 starting offsets zero and two for the remaining code points.
3. Change only the malformed continuation byte from 28 to A9. Explain why C3 A9 is now a valid sequence and why the refusal test must no longer expect true.
4. Compare the source spelling with one backslash-u and two backslashes followed by u. Count what is stored in each case.
5. Explain why a code-point count alone cannot enforce a maximum number of screen columns or model tokens.


## Primary language references


- [D string literal encodings](https://dlang.org/spec/lex.html#string_literals)
- [D foreach over character arrays](https://dlang.org/spec/statement.html#foreach_over_arrays_of_characters)
- [D std.utf validation](https://dlang.org/phobos/std_utf.html#validate)
- [D character types](https://dlang.org/spec/type.html)


[Previous: Follow nested static-array copies](38-follow-nested-static-array-copies.md)

[Next: Preserve qualifiers when returning a borrowed view](40-preserve-qualifiers-when-returning-a-borrowed-view.md)
