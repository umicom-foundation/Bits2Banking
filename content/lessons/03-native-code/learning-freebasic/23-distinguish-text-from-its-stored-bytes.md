<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/23-distinguish-text-from-its-stored-bytes.md

PURPOSE:
Distinguish text from its stored bytes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Distinguish text from its stored bytes

[Course contents](index.md)

## What you will investigate

A string is a sequence stored in memory, but the relationship between stored units and displayed characters depends on its encoding. In this lesson you will inspect ordinary FreeBASIC String values, build a tiny UTF-8 example, keep track of an embedded zero byte, and see why cutting text at an arbitrary byte count can damage it. The complete source is labs/languages/native-language-boundary/text_bytes.bas. It uses small fixed fixtures, performs no file or network access, and does not call C through a raw pointer.


## 1. Begin with bytes

A byte contains eight bits and can represent a number from 0 through 255. An encoding assigns meaning to one or more bytes. ASCII represents a small set of letters, digits, punctuation and control values using values below 128. In the ASCII word Umicom, each letter occupies one byte, so the ordinary String has length six. This convenient one-byte relationship does not apply to all human writing. Avoid using the word character when the code actually measures bytes.


## 2. Understand ordinary FreeBASIC String storage

A variable-length String keeps a length as well as a reference to its character storage. Its elements are eight-bit units. The runtime can resize the storage when an assignment changes the value. Len(value) on the ordinary strings used here reports the number of those units. It does not decode a UTF-8 sequence into Unicode code points. Len(String), which names the type rather than a value, has a different purpose: it concerns the descriptor representation. Do not use it to measure the text of a variable.

~~~freebasic
Dim As String asciiText = "Umicom"
Print Len(asciiText)  ' Expected: 6
~~~


## 3. Build a known UTF-8 sequence

Unicode assigns code points to text elements. UTF-8 encodes a code point using one to four bytes. The example word cafe with an accented final e is represented here as the ASCII bytes for c, a and f followed by hexadecimal C3 A9. Hexadecimal is base sixteen; the decimal values of those last two bytes are 195 and 169. Chr constructs the selected eight-bit units, and the ampersand joins strings. Constructing the bytes explicitly keeps this fixture independent of how your editor saves the source file.

~~~freebasic
Dim As String utf8Text = "caf" & Chr(&HC3) & Chr(&HA9)
Print Len(utf8Text)                 ' Expected: 5 stored bytes
Print Asc(Mid(utf8Text, 4, 1))       ' Expected: 195
Print Asc(Mid(utf8Text, 5, 1))       ' Expected: 169
~~~


## 4. Read positions carefully

Mid(value, start, count) returns a selected part of the ordinary string. In this function, positions begin at one, so position four is the fourth stored unit. This differs from many zero-based C arrays. Asc returns the numeric value of the selected unit. Left chooses a prefix and Right chooses a suffix. These operations are useful for byte-oriented formats, but they do not automatically become UTF-8-aware simply because the bytes happen to encode text. Keep the position convention visible when moving an algorithm between languages.


## 5. Observe a broken prefix without printing it as text

Left(utf8Text, 4) keeps c, a, f and C3. It drops the following A9 byte needed by this two-byte sequence. The result still has a counted length of four, but it is not a complete UTF-8 representation of the intended word. The example checks the final numeric byte rather than asking the terminal to render invalid text. Left(utf8Text, 3) happens to end at a valid boundary for this known fixture and gives caf. That specific boundary is not a general truncation algorithm. Real arbitrary text needs a reviewed decoder and a boundary policy.


## 6. Keep code points, visible symbols and model tokens separate

A code point is not always a complete user-perceived symbol. A displayed letter can involve a base code point plus a combining mark, and an emoji sequence can involve several code points. A group displayed as one unit is often called a grapheme cluster. A language-model token is different again: it is a unit chosen by that model's tokenizer. You cannot reliably turn a UTF-8 byte count into a display width, a number of graphemes or an LLM token count with one fixed multiplier. This matters when setting editor limits, planning model context or preparing training data.


## 7. Store an embedded zero deliberately

The example creates A, a zero byte, and B in one variable-length String. Len reports three and Mid can still read B at position three. A conventional C string uses the first zero byte as its terminator, so a C function expecting that convention would see only A. An API that accepts a pointer and an explicit byte length can have a different contract, but it may still reject embedded zeros as invalid text. Check the exact API. Never assume a counted BASIC string and a C string describe the same data merely because both are called strings.

~~~freebasic
Dim As String embeddedZero = "A" & Chr(0) & "B"
Print Len(embeddedZero)             ' Expected: 3
Print Asc(Mid(embeddedZero, 2, 1))   ' Expected: 0
Print Mid(embeddedZero, 3, 1)        ' Expected: B
~~~


## 8. Read the narrow validation function

IsPlainAsciiLabel accepts one through 32 bytes and requires every byte to be between 32 and 126. The policy allows printable ASCII, including spaces. It refuses control bytes, embedded zero, empty input and anything longer than the declared limit. OrElse is a short-circuit OR: if the left condition already decides the result, the right one is not needed. The loop uses For and Next, and Return False stops at the first refused byte. This is a deliberately small teaching policy, not a recommended restriction for all Umicom names or a general Unicode validator.


## 9. Notice what validation does not change

The function borrows the input String through ByRef and reads it. It does not trim spaces, change case, replace characters or repair malformed encoding. A string of spaces is acceptable under this particular printable-byte policy; an application requiring a meaningful name needs an additional rule. Keeping transformations separate from validation helps callers know whether the original bytes were preserved. A training-data pipeline should record its transformations explicitly rather than silently changing source text during a check.


## 10. Compile and run the complete example

Use the FreeBASIC installation from the first course lesson. The commands below assume the owner-style repository location. Change the path if your checkout is elsewhere. -lang fb selects the modern FreeBASIC dialect, -exx enables additional runtime checks, and -w all enables warnings. These options do not prove memory safety; they help reveal mistakes during learning. Run each command separately and stop on failure. The example remains uncompiled in the current authoring environment because a verified FreeBASIC compiler is not available there.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
Get-Command fbc
fbc -version
fbc -lang fb -exx -w all text_bytes.bas -x text_bytes.exe
& ".\text_bytes.exe"
~~~


## 11. Compare the expected results

The program's checks require six bytes for Umicom, five for the accented UTF-8 fixture, numeric final bytes 195 and 169, three bytes in the embedded-zero string, and B after the zero. It prints caf as the known safe prefix. Numeric spacing can differ between compiler/runtime versions, so compare the values rather than decorative spaces. A terminal rendering of an accented word would depend on its encoding settings, which is why the checked result uses byte values. No successful compiler or terminal result is claimed until you run and inspect it.


## 12. Avoid unsafe shortcuts at the C boundary

Do not manually free a String's internal storage or keep a pointer to it across an assignment that may resize it. The runtime owns the descriptor and character allocation. Do not treat a fixed-length String declaration as a portable C text buffer: compiler-version rules for its padding and termination differ, so verify the selected version and use an explicit ABI contract. When calling Framework, declare the exact C types, capacity units, encoding and ownership from the public header. Do not pass the String descriptor where an API expects a pointer to characters. The earlier C interoperability lesson introduces that boundary with simple numeric values first.


## 13. Connect this lesson to AI data preparation

A dataset line can be valid JSON yet contain text that a downstream model or application rejects. A file extension does not establish its encoding. Preserve the original source privately, choose an explicit encoding, validate it, and record any normalization or replacement. A vector database stores retrieval representations; it does not fix broken source bytes or train a model merely by storing them. Tokenization comes after text preparation and must use the model's tokenizer. Framework's JSONL training helpers distinguish decoded UTF-8 bytes from tokens, so read each service's contract before using its counts in a memory plan.


## 14. Try controlled changes

1. Change the ASCII fixture to Umicom 42 and predict its byte length before compiling.
2. Add one more ordinary ASCII letter before the accented sequence. Recalculate the Mid positions and confirm why hard-coded positions are fixture-specific.
3. Move the embedded zero to the beginning. Explain what a conventional C string reader would see, while keeping the counted String's full length.
4. Try a 32-byte printable label and then a 33-byte one. Confirm the application limit without increasing it just to hide a refusal.
5. Write down three independent limits for a future chat input: maximum encoded bytes, maximum tokenizer tokens, and a display policy. Explain why they need different checks.


## Visual byte map for the UTF-8 fixture

| One-based position | Stored byte in hex | Decimal value | Meaning |
| --- | --- | --- | --- |
| 1 | 63 | 99 | c |
| 2 | 61 | 97 | a |
| 3 | 66 | 102 | f |
| 4 | C3 | 195 | First byte of U+00E9 |
| 5 | A9 | 169 | Second byte of U+00E9 |

## Further reading

- [FreeBASIC String representation and version notes](https://www.freebasic.net/wiki/KeyPgString)
- [FreeBASIC Len reference](https://www.freebasic.net/wiki/KeyPgLen)
- [UTF-8 definition in RFC 3629](https://www.rfc-editor.org/rfc/rfc3629)
- [Complete text-byte example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/text_bytes.bas)

[Previous: Keep temporary values inside a scope](22-keep-temporary-values-inside-a-scope.md)

[Next: Inspect a bounded binary header](24-inspect-a-bounded-binary-header.md)
