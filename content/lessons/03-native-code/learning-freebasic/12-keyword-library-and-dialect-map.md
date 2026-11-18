<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/12-keyword-library-and-dialect-map.md

PURPOSE:
Navigate FreeBASIC keywords, library functions and dialects

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Navigate FreeBASIC keywords, library functions and dialects

[Course contents](index.md)
FreeBASIC includes language syntax, preprocessor directives, built-in procedures and runtime-library operations. A manual’s full index includes all of these, so it is larger than a reserved-keyword list. Learn them by purpose and verify the selected dialect. This course uses -lang fb; older QB-style source can follow different rules.

Some entries are multiword forms, some are procedures, and availability depends on dialect and target. The official full index is the authority for the complete callable and syntax surface; this table is a study map, not an exhaustive compatibility claim. Threading, synchronization, graphics, binary I/O and advanced type operators each need dedicated exercises before production use.

1. Choose a family and find its exact entry in the official manual.
2. Read its parameter types, return value, failure behavior and dialect notes.
3. Write the smallest valid example in a separate folder.
4. Add an invalid or boundary case and observe the result without touching real application data.
5. Record what was executed, then decide whether the operation belongs in a teaching client or a shared Framework C service.

C and FreeBASIC can cooperate through a verified ABI, but their source grammars do not become interchangeable. Do not place BASIC text inside a C source file and assume a normal C compiler interprets it. A mixed-language frontend requires its own defined parser, type conversions, diagnostics and code generation.


## A practical language and library map

| Family | Names to recognize | Meaning |
| --- | --- | --- |
| Declarations | Dim As Const Static Shared Common Extern Declare | Introduce storage, constants and interfaces |
| Parameter and linkage rules | ByVal ByRef Cdecl Stdcall Pascal Alias | Specify passing and external names |
| Built-in representations | Byte UByte Short UShort Long ULong Integer UInteger LongInt ULongInt Single Double String ZString WString Any Ptr Pointer | Choose storage and pointer interpretation |
| Decisions | If Then ElseIf Else End If Select Case Case Else End Select | Choose a branch |
| Repetition | For To Step Next While Wend Do Loop Until Exit Continue | Repeat or leave a loop |
| Procedures | Sub Function Return End Sub End Function Overload | Name reusable operations |
| Data and object structure | Type Union Enum Field Constructor Destructor Property Operator Extends Base Virtual Abstract | Describe records, alternatives and methods |
| Visibility and organization | Public Private Protected Namespace Using Scope End Scope | Control name visibility |
| Logical and arithmetic syntax | And Or Xor Not Eqv Imp AndAlso OrElse Mod Shl Shr | Combine values or bits |
| Legacy control/data forms | Goto Gosub Resume On Error Data Read Restore DefInt Let Call | Recognize older code; prefer structured new examples |
| Text and conversion helpers | Len Trim LCase UCase Left Right Mid Chr Asc Str Val CInt CLng Cast CPtr | Inspect and convert values under documented rules |
| Arrays and storage | LBound UBound ReDim Preserve Erase Allocate Callocate Reallocate Deallocate New Delete SizeOf TypeOf | Manage shape, storage and representation |
| Files and console | Open Close Input Line Input Print Write Get Put Seek Eof FreeFile Command | Read, write and obtain program inputs |
| Graphics and interaction | ScreenRes ScreenSet PSet Line Circle Paint Draw Color Inkey GetMouse | Use the optional graphics/console runtime |
| Preprocessing |  #include #define #undef #if #ifdef #ifndef #elseif #else #endif #macro #endmacro #error #pragma | Select and compose source before compilation |

## Further reading

- [FreeBASIC full index](https://www.freebasic.net/wiki/CatPgFullIndex)
- [FreeBASIC language reference](https://www.freebasic.net/wiki/DocToc)

## Continue learning

[Previous: Test errors and define record contracts](11-tests-errors-and-record-contracts.md) · [Course contents](index.md)

## Continue practice

[Next: Use Enum and Select Case to model job states](13-enums-and-state-transitions.md)

## Apply these names to a complete exercise

[Practice Overload with checked byte counts](27-select-an-overload-by-its-arguments.md). Read the source, predict refusals and keep the subject-language compiler evidence separate from C checks.
