<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/35-measure-records-before-sharing-their-bytes.md

PURPOSE:
Measure records before sharing their bytes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Measure records before sharing their bytes

[Course contents](index.md)

## Your first question: what occupies memory?

A computer stores data in small numbered locations. A byte is a group of eight bits; a bit can hold zero or one. A variable gives a region of storage a useful name and a type. A record groups several named fields into one value. You will make a tiny record containing a kind number and a count, inspect where each field begins, and distinguish its native representation from a deliberately designed file format. No knowledge of processor instructions is required. Complete the earlier variable, array and Type exercises first if their syntax is unfamiliar; keep their programs available for comparison.


## Prepare a safe exercise folder

Open PowerShell, which accepts commands and displays their results. Use the repository path below only after you have a local Bits2Banking checkout. Set-Location changes the directory in which subsequent relative paths are interpreted; it does not copy or compile anything. Get-Command asks which executable the shell would use. A missing fbc command means the FreeBASIC compiler is not installed or its directory is absent from PATH. Consult the course setup lesson instead of renaming a different compiler.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
Get-Command fbc
fbc -version
Get-Content .\record_layout.bas
~~~


## Give two fields meaningful names

Type starts a record definition, NativeRecord names that type, and End Type finishes it. This definition describes the arrangement of future values; it is not itself an instance. kind uses UByte, an unsigned one-byte integer. count uses ULong, the FreeBASIC unsigned four-byte integer used here. Unsigned means the stored integer is never negative. These language-specific names must not be translated to a similarly named C type by guesswork.

~~~freebasic
Type NativeRecord
    kind As UByte
    count As ULong
End Type
~~~


## Size, offset and alignment are different questions


| Term | Question it answers | Example meaning |
| --- | --- | --- |
| Size | How many bytes does this type occupy? | The whole record may need more than five bytes. |
| Offset | How many bytes from the start does this field begin? | Offset zero is the first byte. |
| Alignment | At which address boundaries may a value be placed? | A target may prefer a four-byte integer to begin on a multiple of four. |
| Padding | Which bytes exist between or after fields? | Unused gaps can make the next field or array element suitably aligned. |


## Draw one possible native layout

On a target that places the count at offset four, the first field occupies byte zero, bytes one through three are a gap, and the four-byte count occupies bytes four through seven. The record then occupies eight bytes. That is an illustration, not a universal output promise. Another compiler target or packing option can choose a different layout. Padding is not an additional field you should treat as application data.

~~~text
Illustrative native record, only if count offset is 4:
offset:   0    1    2    3    4    5    6    7
role:   kind  gap  gap  gap  count occupies four bytes

Field=1 record in this example:
offset:   0    1    2    3    4
role:   kind  count occupies four bytes
~~~


## Ask the compiler instead of guessing

SizeOf(NativeRecord) asks for the size of the named record type. OffsetOf(NativeRecord, count) asks for the position of its count field. Neither operation reads a file or checks the validity of a live pointer. The laboratory checks that kind begins at zero, that count does not overlap it, and that the whole record is large enough to hold count. It prints the observed native numbers without insisting that every target use the illustrative eight-byte layout.

~~~freebasic
Print SizeOf(NativeRecord)
Print OffsetOf(NativeRecord, count)
~~~


## Change packing deliberately

The second declaration adds Field=1. For these two plain integer fields, this asks FreeBASIC to pack fields on one-byte boundaries. The program expects count at offset one and the record size to be five. This is useful for learning what packing changes. It is not a recommendation to pack every structure in a native application: a tightly packed multi-byte field can have a less suitable address for direct access, and a foreign library can require a different layout.

~~~freebasic
Type PackedRecord Field=1
    kind As UByte
    count As ULong
End Type
~~~


## Copy meanings, not anonymous bytes

Dim normal As NativeRecord creates one ordinary record. Assignments store seven in kind and hexadecimal 01020304 in count. Hexadecimal is base sixteen: each pair of digits can describe one byte, so the value is useful when discussing byte order. The example then assigns normal.kind to packed.kind and normal.count to packed.count. These are typed field assignments. They preserve the values even if the surrounding record layouts differ. A raw copy of the complete native record into the packed record would not have that contract.


## Notice a FreeBASIC array size rule

An array contains several elements of one declared type. The expression samples(5 To 7) declares three elements with indexes five, six and seven. In FreeBASIC, SizeOf(samples) reports the size of the array element datatype. It does not report the complete array payload in the manner of sizeof applied to a C array object. The example explicitly checks that it returns four. Carrying the wrong rule across languages can make a buffer length too small or a later copy too large.

~~~freebasic
Dim samples(5 To 7) As ULong = {11, 22, 33}
Dim elementCount As LongInt = CLngInt(UBound(samples)) - CLngInt(LBound(samples)) + 1
Dim payloadBytes As LongInt = elementCount * SizeOf(ULong)
~~~


## Work through the arithmetic

LBound returns the first valid index and UBound the last. Subtract five from seven to get two intervals, then add one to count all three elements. CLngInt converts each bound to the signed 64-bit arithmetic type before subtraction. Three elements multiplied by four bytes each gives twelve payload bytes. These tiny fixed bounds cannot overflow that type. A reusable routine accepting arbitrary bounds must check empty-array cases, dimensions, multiplication and target-size limits separately; this formula alone is not a general allocation service.


## Compile, then run only after success

Run the first command by itself. The -lang fb option chooses the FreeBASIC dialect, -w all requests warnings, -exx enables supported runtime error checks, and -x names the output executable. A warning is a message to investigate; an error prevents a trustworthy new build. If compilation fails, stop and read the first diagnostic. Do not launch an old executable left by an earlier successful build. After compilation succeeds, the second command runs the program; the final command displays its process exit code.

~~~powershell
fbc -lang fb -w all -exx record_layout.bas -x record_layout.exe
& .\record_layout.exe
$LASTEXITCODE
~~~


## Interpret each observation


| Observation | Expected meaning |
| --- | --- |
| native bytes and count offset | Target-dependent values that satisfy the record checks. |
| packed bytes and count offset | Five bytes and offset one for the declared packed integers. |
| array element bytes | Four; this is not the twelve-byte payload. |
| elements and payload bytes | Three and twelve. |
| fields agree; no raw record was saved | The typed copies preserved the values. |
| Exit code | Zero when every explicit check succeeds. Integer spacing may vary. |


## A packed record is still not a file protocol

Packing controls gaps; it does not specify the order in which the bytes of a multi-byte integer are stored. A file protocol also needs a version, field meanings, allowed ranges, byte order and a way to reject incomplete input. Use the existing encode_record.bas exercise to study explicit little-endian integer encoding. Little-endian places the least significant byte first. That encoder writes each chosen byte rather than assuming that a record image is portable. Keep pointers, runtime string descriptors and unused padding out of portable files.


## Why runtime descriptors need special care

A variable-length String needs runtime bookkeeping that describes its contents. Its size in a record does not equal the length of the text it refers to. Dynamic arrays likewise require bookkeeping. Saving only those internal records does not save all of their referenced data, and restoring an old address does not recreate the original storage. Use Len for the counted string length in the earlier text exercises and a documented encoder for persistent content. Do not attempt to repair this by casting addresses to integers.


## Use this knowledge at the Framework boundary

Umicom Framework remains responsible for reusable C services and their ownership rules. A BASIC client must match the published C declarations, calling convention, field types and lifetime contract. Matching one observed size is necessary in some interfaces but insufficient: offsets, alignment, ownership and semantic rules also matter. Prefer existing accessor functions or explicit byte-buffer APIs where they avoid exposing internal records. This laboratory inspects language behavior; it does not add BASIC parsing to Umicom C or qualify a new Framework binary interface.


## Troubleshoot and test your understanding

1. If fbc is missing, return to the setup lesson and verify its actual executable path; do not assume another command with a similar name is compatible.
2. If a native offset differs from the illustration, compare target and compiler options before calling it an error. The packed checks have a different, explicit expectation.
3. Change the array bounds to 10 To 12 while keeping three values. Predict the element count before running again.
4. Explain why five bytes of record storage do not establish byte order. Then inspect encode_record.bas and identify the shifts that establish it.
5. Explain why a String field cannot be archived by saving only its runtime descriptor. Keep your answers in a separate study note.


## Qualification boundary

These original FreeBASIC sources were authored and checked against the language reference. FreeBASIC compilation and execution have not been performed in the current mirror environment. Website link checks and tests of separate C implementations do not establish that this BASIC source compiles. Record your compiler version, target, command, output and exit code when you qualify it.


## Language references


- [FreeBASIC Type and Field alignment](https://www.freebasic.net/wiki/wikka.php?wakka=KeyPgType)
- [FreeBASIC SizeOf, including array and string rules](https://www.freebasic.net/wiki/wikka.php?wakka=KeyPgSizeof)
- [FreeBASIC OffsetOf](https://www.freebasic.net/wiki/wikka.php?wakka=KeyPgOffsetof)


[Previous: Swap values without confusing their owners](34-swap-values-without-confusing-their-owners.md)

[Next: Own worker threads and protect shared state](36-own-worker-threads-and-protect-shared-state.md)
