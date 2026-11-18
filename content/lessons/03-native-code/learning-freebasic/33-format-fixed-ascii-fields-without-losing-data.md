<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/33-format-fixed-ascii-fields-without-losing-data.md

PURPOSE:
Format fixed ASCII fields without losing data

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Format fixed ASCII fields without losing data

[Course contents](index.md)

## Imagine a form with six boxes

A fixed-width field reserves a known number of positions for a value. Draw six boxes on paper. Put A, B and 7 in the first three boxes and spaces in the last three. That is a left-aligned six-byte ASCII field. Put four spaces followed by 4 and 2 in another six boxes for a right-aligned field. These are text layouts, not numeric calculations. This exercise teaches formatting and input admission separately so that a long identifier never silently becomes a different identifier.


## Prepare the complete example

Open labs/languages/native-language-boundary/fixed_ascii_fields.bas in the Bits2Banking checkout. The earlier lessons explain installing FreeBASIC and opening PowerShell. Keep the original file unchanged while experimenting in a copy. The example uses small invented values and writes only to its console. It does not contact a bank, create a payment, export a production file or implement an external record standard.


## Introduce three formatting operations

Space(n) creates n spaces. LSet fills an existing string buffer from the left and pads unused positions with spaces. RSet fills it from the right and pads on the left. The destination keeps its current length. Both operations truncate overlong source text from the right; neither reports that the original identifier was too long. Their modern FreeBASIC call form uses a comma between destination and source. We will therefore validate lengths before using them.

~~~basic
Dim leftField As String = Space(6)
LSet leftField, "AB7"
Dim rightField As String = Space(6)
RSet rightField, "42"
~~~


## Read the result one byte at a time

The word byte means an eight-bit storage unit. Our exercise accepts only printable ASCII values, each occupying one byte. Number the six positions from one through six, matching the positions accepted by Asc in this example. A space is stored data even though it is visually blank. Adding brackets when printing makes leading and trailing spaces easier to see.


| Position | 1 | 2 | 3 | 4 | 5 | 6 |
| --- | --- | --- | --- | --- | --- | --- |
| Left field | A | B | 7 | space | space | space |
| Right field | space | space | space | space | 4 | 2 |


## Understand the function contract

TryAsciiField returns Boolean: True means the candidate was admitted and published; False means the caller’s output remains unchanged. ByRef lets the function access a caller-owned value. Const on source prevents this function from modifying that input through the parameter. fieldWidth and alignRight use ByVal, so the function receives their values. output is an explicitly writable reference. These declarations describe access, but our code still has to enforce the promised validation order.

~~~basic
Function TryAsciiField(ByRef source As Const String, ByVal fieldWidth As Integer, _
    ByVal alignRight As Boolean, ByRef output As String) As Boolean
~~~


## Admit the width before reserving storage

The function first refuses widths below one or above 32. Thirty-two is our teaching policy, not a universal limit of FreeBASIC. Bounding the request before Space prevents an accidental enormous allocation in this exercise. It then refuses Len(source) greater than fieldWidth. For these ASCII values Len counts the stored bytes. A width is a capacity decision; it should come from a documented record format, not from how wide a label happens to look on screen.


## Admit every byte before formatting

The For loop visits source positions one through Len(source). Asc reads the numeric value at the selected position. The function allows only values 32 through 126. That includes space and printable ASCII punctuation. It refuses tabs, line breaks, zero bytes and non-ASCII bytes. Empty input visits no positions and is intentionally allowed: it becomes an all-space field. If a real format requires a nonempty identifier, add that as a separate documented rule before formatting.

~~~basic
For position As Integer = 1 To Len(source)
    Dim code As UInteger = Asc(source, position)
    If code < 32 OrElse code > 126 Then Return False
Next position
~~~


## Build a candidate and publish once

Only after admission does the function create candidate = Space(fieldWidth). It checks that the returned length matches the request. It then chooses RSet or LSet with an If/Else block and finally assigns candidate to output. A candidate is a private draft of the result. The final assignment is the point where the caller sees the new field. This ordering prevents a normal validation refusal from leaving a half-formatted output. It is not a general transaction system or a promise that the entire runtime can recover from every resource failure.


## Trace a refused identifier

The accepted leftField initially contains AB7 followed by three spaces. The program saves a copy. It then requests ACCOUNT7 in a six-byte field. ACCOUNT7 has eight bytes, so the length check returns False before candidate construction or output assignment. The caller checks both the returned status and equality with the saved value. Checking only a printed error message would not establish that the earlier field survived.


## Use invalid exercises for different reasons

The tab exercise uses Chr(9) to construct a control byte. It fits inside six positions but fails the printable-ASCII policy. Width zero fails the lower bound, and width 33 fails the upper bound. Each exercise tests a different admission rule. The program also accepts empty input in a width-four field and expects four spaces. That contrast teaches that policy is explicit: an empty value is not automatically invalid in every record format.


## Observe truncation without adopting it as policy

Near the end, the example deliberately bypasses TryAsciiField. It creates a four-byte buffer and applies raw LSet to LONGER. The expected value is LONG. This is a counterexample that demonstrates data loss; it is not a recommended way to shorten an account code. The first four bytes can form a plausible-looking but different identifier. An interface that displays only the shortened value may hide the mistake from the user.

~~~basic
Dim clipped As String = Space(4)
LSet clipped, "LONGER"
Print "Raw LSet truncates: [" & clipped & "]"
~~~


## Compile with learning checks enabled

Use the installed FreeBASIC compiler. The -lang fb option selects its modern dialect. -w all requests warnings, and -exx enables additional runtime checks useful during learning. Execute the build and run commands separately. If compilation fails, stop and read the diagnostic instead of launching an older executable left in the directory. This example has been authored and reviewed; it still needs execution with your selected FreeBASIC toolchain.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -w all -exx fixed_ascii_fields.bas -x fixed_ascii_fields.exe
& .\fixed_ascii_fields.exe
$LASTEXITCODE
~~~


## Compare all five output lines

Expect the lines below and exit code zero. Brackets are display markers and are not stored inside the fields. If spaces appear missing, copy the line into a monospaced editor and count the positions between brackets. If a refusal changes the saved field, inspect whether output assignment moved above a validation check. If the raw truncation result differs, record the compiler version and exact source instead of changing the expected result without investigation.

~~~text
Left field: [AB7   ]
Right field: [    42]
Refused fields keep: [AB7   ]
Empty input becomes: [    ]
Raw LSet truncates: [LONG]
~~~


## Keep text layout separate from binary layout

A FreeBASIC String has a runtime representation. Passing its internal descriptor to a C function does not turn it into a portable six-byte record. At a Framework boundary, define an explicit byte pointer, byte count, encoding, ownership and lifetime. If an external protocol requires a terminator, reserve and write that separately; the six data positions do not automatically include it. If a protocol requires UTF-8 or a different encoding, this ASCII-only helper must not be used as a substitute.


## Use the idea in Umicom products

A thin BASIC learning client can demonstrate record formatting, while a reusable native Framework service should own a real shared serialization contract. Studio can show an overlong-field diagnostic before export. Trader or TMS import tools can preserve the original identifier and refuse incompatible widths. Media metadata fields can keep an explicit encoding instead of assuming display columns equal bytes. These are applications of admission and ownership; the lesson does not claim those product workflows are already wired to this example.


## Practice and explain each decision

1. Change AB7 to exactly six printable characters. Predict that no padding remains and no truncation occurs.
2. Try seven printable characters and confirm that the caller’s previous field is preserved.
3. Use an embedded line break constructed with Chr(10). Explain why a byte that fits numerically still violates the field policy.
4. Add an explicit nonempty-input rule to a copied exercise. Explain how its empty-input test must change.
5. Draw the distinction between six ASCII bytes, six Unicode code points and six visible text columns. State which one this function promises.


## Language references


- [FreeBASIC LSet reference](https://www.freebasic.net/wiki/KeyPgLset)
- [FreeBASIC RSet manual source](https://github.com/freebasic/fbc/blob/master/doc/manual/cache/KeyPgRset.wakka)
- [FreeBASIC Space manual source](https://github.com/freebasic/fbc/blob/master/doc/manual/cache/KeyPgSpace.wakka)


[Previous: Follow row, column and channel bounds](32-follow-row-column-and-channel-bounds.md)

[Next: Swap values without confusing their owners](34-swap-values-without-confusing-their-owners.md)
