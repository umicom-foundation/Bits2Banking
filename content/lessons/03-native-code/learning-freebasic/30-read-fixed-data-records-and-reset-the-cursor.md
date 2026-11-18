<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/30-read-fixed-data-records-and-reset-the-cursor.md

PURPOSE:
Read fixed data records and reset the cursor

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read fixed data records and reset the cursor

[Course contents](index.md)

## Put a small fixture inside a program

A fixture is a small, deliberately chosen set of inputs and expected results used for practice or checking behavior. You have already used variables and arrays. BASIC also has Data, Read and Restore for a sequential list embedded in the source. In this lesson, four records describe rectangle dimensions and the expected result of a checked area calculation. You will read them in order and return to the first record without opening a file.


## Give each keyword a precise job

The word record does not create a new BASIC type here. It is a rule we impose on the sequence: width, height, expected acceptance and expected output. The language sees a sequence of items. If the producer and reader disagree about the order or count, the intended records can become misaligned.


| Keyword or term | Meaning here |
| --- | --- |
| Data | Declares constant items in the module’s embedded data list |
| Read | Copies the next items from that list into named variables |
| Restore | Moves the next-read position to the first Data item after a label |
| Label | A source marker such as AreaCases: |
| Cursor | The position of the next item to be read; not the mouse pointer |
| Record | Our convention of four consecutive items describing one case |


## Read one record on paper

The first rectangle is 640 units wide and 360 units high. Multiplying gives 230400 units of area. The next value 1 says the operation should accept these inputs. In the two refusal cases, 0 means rejection and 71 is the old output that must remain. A unit could be one pixel in this numerical exercise, but no image is allocated or decoded. The labels and expected values are our own learning data.

~~~freebasic
AreaCases:
Data 640, 360, 1, 230400
Data 1920, 1080, 1, 2073600
Data 0, 720, 0, 71
Data 65536, 65536, 0, 71
~~~


## Understand where the data lives

In the fb dialect, Data items are simple constant numeric or string expressions prepared when the source is compiled. They are not user input requested at runtime. Data statements in a module form a sequence even when written on separate lines. They are module-local and belong in module-level code. This exercise uses only numeric items that match the destination types; it does not rely on implicit string-to-number conversions. The earlier file-reading lesson covers a different source of data.


## Keep the cursor inside the fixture

There is no safe end-of-data test in this example. Reading beyond the available Data items has undefined behavior according to the FreeBASIC manual and may crash. RECORD_COUNT is four because the fixture has four complete records. Each iteration reads four items, so the first loop consumes sixteen items. Never change the loop to keep reading until an error occurs, and never increase the count without supplying complete matching records. For external or variable-length data, use an explicitly bounded parser and record lengths instead of treating this trusted source fixture as a general importer.


## Choose numeric types deliberately

FreeBASIC ULong is an unsigned 32-bit integer. It can represent zero through 4294967295. ULongInt supplies a wider unsigned integer for the admission calculation. Integer is used for the small loop counter and the expected acceptance flag; do not infer a fixed wire width from that native-sized type. CULngInt makes the wider conversion explicit. Boolean describes acceptance, while the fixture stores the easy-to-read integers zero and one. The test compares whether each is nonzero rather than assuming the stored representation of True is exactly one.


## Check before multiplying

The policy requires both dimensions to be nonzero. The first line returns before the later division could use a zero height. The backslash operator performs integer division. The second line asks whether width is larger than the maximum representable count divided by height. If it is, the product would not fit and the function refuses before computing it. Only an admitted request assigns result. This is an output-preservation contract: refusal keeps the caller’s earlier value.

~~~freebasic
If width = 0 OrElse height = 0 Then Return False
If CULngInt(width) > MAX_COUNT \ CULngInt(height) Then Return False
result = width * height
Return True
~~~


## Trace the four cases

The final case is not a negative dimension. Both inputs fit individually, but their product does not fit the result type. This is a common source of allocation-size bugs in native programs. A type check on each argument is not enough to prove that a later multiplication is representable.


| Width × height | Why accepted or refused | Output |
| --- | --- | --- |
| 640 × 360 | Positive and representable | 230400 |
| 1920 × 1080 | Positive and representable | 2073600 |
| 0 × 720 | Zero dimension refused by this domain rule | 71 remains |
| 65536 × 65536 | 4294967296 exceeds the 32-bit maximum | 71 remains |


## Follow Read and Restore

1. Restore AreaCases selects the first item after that label. It does not execute a jump to the label and does not erase variables.
2. Each loop iteration declares destination variables, then Read consumes width, height, expectedAccepted and expectedArea in that order.
3. Set result to 71 before calling TryArea. Compare both acceptance and the resulting value with the fixture.
4. After four iterations, stop reading. Restore AreaCases moves the cursor back, allowing exactly the first record to be read again.
5. End 0 exits successfully before the label in normal execution. The Data items were already prepared as source data; no extra input needs to be typed.


## Compile the original exercise

Use the FreeBASIC compiler, not a C compiler. Open PowerShell in the lab directory and run one command at a time. The fb dialect selects the language discussed here. The exx option enables useful runtime checks, but it is not permission to read past the Data list. Stop if compilation fails, because an older executable may still exist.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -exx data_records.bas -x data-records-basic.exe
.\data-records-basic.exe
~~~


## Read the output and troubleshoot

The program prints four case numbers, acceptance flags and area values. Expect accepted results 230400 and 2073600, then two refused cases preserving 71. Finally it prints the restored first dimensions, 640 by 360. Print may insert spacing around numbers. A nonzero exit means a checked expectation failed. If fbc is not found, return to the setup lesson and locate the actual installed compiler; installing Python or Conda does not supply FreeBASIC. If one expected value is wrong, calculate it independently before editing the fixture.


## Use this idea in Umicom learning projects

Embedded fixtures are useful for small arithmetic lessons, deterministic format examples and adapter tests. Shared production logic should remain in the C23 Framework owner. A BASIC teaching client can call a reviewed C interface, as the earlier boundary lesson shows. Data does not make FreeBASIC source executable by Umicom C, and it is not a database, a vector store or an LLM training file format. A compiled fixture also requires rebuilding the program when its values change.


## Practice with a complete record

1. Add one positive record with width 1 and height 4294967295. Calculate the expected acceptance and result, then update the trusted record count together.
2. Explain why Restore changes the next read but does not restore result to 71. Variables and cursor state are separate.
3. Count the items consumed by the first loop. Four records with four items each consume sixteen items.
4. Describe a safer design for reading an unknown number of external records: an explicit length, bounded parsing and checked errors. Do not intentionally read beyond this fixture.


## Read the language reference


- [FreeBASIC Data](https://www.freebasic.net/wiki/KeyPgData)
- [FreeBASIC Read](https://www.freebasic.net/wiki/KeyPgRead)
- [FreeBASIC Restore](https://www.freebasic.net/wiki/KeyPgRestore)


[Previous: Expose state through a read-only property](29-expose-state-through-a-read-only-property.md)

[Next: Edit record fields with an explicit candidate](31-edit-records-with-an-explicit-candidate.md)
