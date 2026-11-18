'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/record_layout.bas
'
' PURPOSE:
'   Inspect record offsets and element sizes without treating native storage as a portable file.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

Type NativeRecord
    kind As UByte
    count As ULong
End Type

' Field=1 is deliberately local to this exercise. It changes packing, not
' byte order, field meaning, pointer lifetime or compatibility with a C API.
Type PackedRecord Field=1
    kind As UByte
    count As ULong
End Type

If SizeOf(UByte) <> 1 OrElse SizeOf(ULong) <> 4 Then End 1
If OffsetOf(NativeRecord, kind) <> 0 Then End 2
If OffsetOf(NativeRecord, count) < SizeOf(UByte) Then End 3
If SizeOf(NativeRecord) < OffsetOf(NativeRecord, count) + SizeOf(ULong) Then End 4
If OffsetOf(PackedRecord, count) <> 1 OrElse SizeOf(PackedRecord) <> 5 Then End 5

Dim normal As NativeRecord
normal.kind = 7
normal.count = &h01020304
Dim packed As PackedRecord
packed.kind = normal.kind
packed.count = normal.count
If normal.kind <> packed.kind OrElse normal.count <> packed.count Then End 6

' FreeBASIC SizeOf(arrayName) reports one element's datatype size. Explicit
' bounds supply the element count; this small fixture cannot overflow LongInt.
Dim samples(5 To 7) As ULong = {11, 22, 33}
Dim elementCount As LongInt = CLngInt(UBound(samples)) - CLngInt(LBound(samples)) + 1
Dim payloadBytes As LongInt = elementCount * SizeOf(ULong)
If SizeOf(samples) <> SizeOf(ULong) Then End 7
If elementCount <> 3 OrElse payloadBytes <> 12 Then End 8

Print "native bytes="; SizeOf(NativeRecord); ", count offset="; OffsetOf(NativeRecord, count)
Print "packed bytes="; SizeOf(PackedRecord); ", count offset="; OffsetOf(PackedRecord, count)
Print "array element bytes="; SizeOf(samples); ", elements="; elementCount; ", payload bytes="; payloadBytes
Print "fields agree; no raw record was saved"
End 0
