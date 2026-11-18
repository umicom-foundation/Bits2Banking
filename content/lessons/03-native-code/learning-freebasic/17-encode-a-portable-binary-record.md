<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/17-encode-a-portable-binary-record.md

PURPOSE:
Encode a portable four-byte record

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Encode a portable four-byte record

[Course contents](index.md)
Two programs can agree on a number and still disagree about the bytes used to store it. A file contains bytes, not a BASIC variable declaration. This lesson starts with the number written as hexadecimal 12345678, gives each of its four bytes an explicit position, and reconstructs the number. You will learn the difference between a numeric value, a printed representation, a memory layout and a file format. The exercise stays in memory; it does not open or overwrite any file.


## 1. Prepare the small exercise

Finish the earlier lessons on integer types, arrays and procedures first. Open labs/languages/native-language-boundary/encode_record.bas in your Bits2Banking checkout. This complete, original teaching example needs FreeBASIC in its fb dialect. It does not call Umicom Framework or link the C boundary object. It has been authored and source-reviewed; execution with a FreeBASIC compiler remains to be performed. Passing the separate C lab tests would not validate this program.


## 2. Count bits, bytes and possible values

A bit is one binary digit: zero or one. A byte contains eight bits and has 256 possible bit patterns. An unsigned byte interprets those patterns as integers from zero through 255. Four bytes contain 32 bits and can represent unsigned values from zero through 4,294,967,295. FreeBASIC UByte supplies an unsigned 8-bit integer and ULong supplies an unsigned 32-bit integer. Integer and UInteger have target-dependent size, so they are not substitutes for a specified 32-bit field. Our loop index may use Integer because the index is not stored in the record.

Dim declares storage. As gives its type. The array has indexes zero, one, two and three: four elements in total. &h introduces hexadecimal, a base-16 notation using digits 0–9 and letters A–F. Each hexadecimal digit describes four bits; two digits describe one byte. CULng explicitly converts a value to ULong. The hexadecimal text 12345678 represents the decimal value 305419896. Changing the notation does not change that value.

~~~basic
Dim As ULong value = CULng(&h12345678)
Dim bytes(0 To 3) As UByte
~~~


## 3. Choose an order before writing bytes

The byte containing the lowest eight bits is called the least significant byte. A little-endian format places that byte first. A big-endian format places the most significant byte first. Neither choice is a quality ranking. Network protocols and file formats choose an order so every reader can reconstruct the same value. Our format requires exactly four bytes, little-endian, with no header, length field or checksum. It is a teaching field format, not a complete file container.

Read the diagram as hexadecimal byte values, not decimal numbers. On a big-endian machine this same encoder still produces 78 56 34 12 because it uses arithmetic on the value. It does not inspect the host representation. Writing a Type variable directly with a binary file operation could instead expose padding, field layout and target-specific representations. An explicit encoder avoids relying on those details.

~~~text
Value:                 0x12345678
Byte index:            0    1    2    3
Our little-endian bytes:78   56   34   12
Big-endian alternative:12   34   56   78
~~~


## 4. Extract each byte with a shift and a mask

Shr shifts the unsigned value right. At position zero the shift is zero; at position one it is eight bits; the final shift is 24 bits. And here is a bitwise operation: a bit is retained only when both operands have that bit set. The mask 255 has its lowest eight bits set. Masking therefore retains exactly one byte after the shift. CUByte converts that bounded value to UByte. The parentheses state the intended evaluation order explicitly. No shift reaches 32 bits, and no conversion is asked to preserve a value above 255.

~~~basic
For position As Integer = 0 To 3
    bytes(position) = CUByte((value Shr (8 * position)) And CULng(255))
Next position
~~~


## 5. Check the entire output contract first

LBound and UBound report the lowest and highest array indexes. <> means not equal. OrElse combines Boolean conditions with short-circuit evaluation. The array parameter uses bytes() As UByte; FreeBASIC passes the array by reference, so writing an element changes the caller’s array. The encoder accepts only bounds zero through three. An array from one through four also has four elements, but does not satisfy this function’s declared indexing contract. Returning False before the loop leaves rejected output unchanged. This is a deliberate narrow contract, not a general array serializer.

~~~basic
If LBound(bytes) <> 0 OrElse UBound(bytes) <> 3 Then Return False
~~~


## 6. Reconstruct the value without partial output

Shl moves each byte into its assigned bit position. Converting to ULong before shifting prevents the calculation from being expressed as a narrow byte operation. Bitwise Or combines the disjoint bit groups. candidate is local scratch storage. The ByRef output parameter is assigned only after every byte has been processed. As with the encoder, the decoder checks bounds before the loop. A rejected input keeps the caller’s previous output value. These functions contain no allocation or retained pointer; callers own the arrays and output variables.

~~~basic
Dim As ULong candidate = 0
For position As Integer = 0 To 3
    candidate = candidate Or (CULng(bytes(position)) Shl (8 * position))
Next position
output = candidate
Return True
~~~


## 7. Compile and run one command at a time

Use the path of your own checkout if it differs. Run each command separately and stop if it fails. The version command identifies the compiler. -lang fb selects the language dialect, -w all requests warnings, and -exx enables runtime checks such as array bounds checking. -x names the executable. The last line runs it. The expected output is shown next; it is an expectation for owner qualification, not a claimed execution result.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -version
fbc -lang fb -w all -exx encode_record.bas -x encode-record.exe
.\encode-record.exe
~~~

The program checks the exact encoded bytes before printing them. It then checks that zero, one, 12345678, the highest single bit and all 32 bits set survive encode/decode. A round trip alone is insufficient: two equally mistaken functions could agree with each other. That is why the independently specified byte sequence is also checked. Invalid-size and invalid-lower-bound cases confirm that both rejection and unchanged output occur.

~~~text
78 56 34 12
Explicit byte-format checks passed
~~~


## 8. Try controlled changes and understand the failure

1. Make a separate practice copy. Change one expected byte from &h78 to &h79. Run the same build and execution commands for that copy. The test should report unexpected byte order and exit with a nonzero code.
2. Restore the expected byte. Change the array declaration in the main example to indexes one through four. The encoder should reject it before writing. Do not remove the bound check just to obtain a passing result.
3. Restore the declaration. Reverse the encoder’s byte order without changing the decoder. Observe which checks reject the inconsistency. Then explain what a matching big-endian decoder would have to change.
4. Write down the format in plain English before designing a second field. Specify width, signedness, byte order and permitted values. A field name or a BASIC Type declaration alone is not a portable format.


## 9. Relate this to Umicom’s native interfaces

An SDK C function and a stored record are different contracts. A C ABI describes how compiled functions exchange parameters on a particular platform. A wire or disk format describes bytes that may survive different platforms and software versions. At the Framework boundary, use its actual public fixed-width types and ownership rules; for persisted data, use an existing reviewed Framework format service when one meets the requirement. Do not pass a BASIC array descriptor as an undocumented C byte pointer. Do not invent a new format when an application can use an existing supported format.


## 10. Recover from common problems

If fbc is not recognized, the compiler is not available in that terminal; install a suitable release through your normal toolchain procedure and verify its version. If compilation reports syntax or type errors, compare the complete example and the selected fb dialect before altering operations. If the expected bytes differ, check the declared order and integer types first. This example does not cover variable-length records, Unicode strings, signed encodings, authentication, checksums or concurrent array mutation. Those need their own contracts and tests.


## Keep the six ideas separate

| Term | Meaning in this example |
| --- | --- |
| Value | The unsigned integer 305419896 |
| Notation | Hexadecimal 12345678 or decimal 305419896 |
| Layout | The compiler’s placement of a variable in memory |
| Format | The agreed four bytes 78 56 34 12 |
| Serialization | Converting a value into the specified byte sequence |
| Deserialization | Reconstructing a value from that sequence |

## Further reading

- [FreeBASIC manual: ULong](https://www.freebasic.net/wiki/wikka.php?wakka=KeyPgUlong)
- [FreeBASIC manual: bit shifting](https://www.freebasic.net/wiki/wikka.php?wakka=KeyPgOpShl)
- [FreeBASIC manual: array bounds](https://www.freebasic.net/wiki/wikka.php?wakka=KeyPgLbound)

[Previous: Pass a BASIC callback to C with an explicit lifetime](16-call-back-through-a-c-boundary.md)

[Next: Distinguish comments, strings and language boundaries](18-comments-and-language-boundaries.md)
