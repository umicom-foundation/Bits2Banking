'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/encode_record.bas
'
' PURPOSE:
'   Encode and decode an explicit four-byte integer without exposing record layout.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

Function EncodeLittleEndian32(ByVal value As ULong, bytes() As UByte) As Boolean
    ' The caller owns exactly four output bytes. Validate before the first write.
    If LBound(bytes) <> 0 OrElse UBound(bytes) <> 3 Then Return False
    For position As Integer = 0 To 3
        bytes(position) = CUByte((value Shr (8 * position)) And CULng(255))
    Next position
    Return True
End Function

Function DecodeLittleEndian32(bytes() As UByte, ByRef output As ULong) As Boolean
    If LBound(bytes) <> 0 OrElse UBound(bytes) <> 3 Then Return False
    Dim As ULong candidate = 0
    For position As Integer = 0 To 3
        candidate = candidate Or (CULng(bytes(position)) Shl (8 * position))
    Next position
    ' Only a complete four-byte input publishes a result to the caller.
    output = candidate
    Return True
End Function

Sub Require(ByVal condition As Boolean, ByVal message As String)
    If Not condition Then
        Print message
        End 1
    End If
End Sub

Sub CheckRoundTrip(ByVal original As ULong)
    Dim bytes(0 To 3) As UByte
    Dim As ULong recovered = 77
    Require(EncodeLittleEndian32(original, bytes()), "Encoding failed")
    Require(DecodeLittleEndian32(bytes(), recovered), "Decoding failed")
    Require(recovered = original, "Round-trip value changed")
End Sub

Dim bytes(0 To 3) As UByte
Require(EncodeLittleEndian32(CULng(&h12345678), bytes()), "Example encoding failed")
Require(bytes(0) = &h78 AndAlso bytes(1) = &h56 AndAlso _
        bytes(2) = &h34 AndAlso bytes(3) = &h12, "Unexpected byte order")
Print Hex(bytes(0), 2); " "; Hex(bytes(1), 2); " "; _
      Hex(bytes(2), 2); " "; Hex(bytes(3), 2)

CheckRoundTrip(CULng(0))
CheckRoundTrip(CULng(1))
CheckRoundTrip(CULng(&h12345678))
CheckRoundTrip(CULng(&h80000000))
CheckRoundTrip(CULng(&hFFFFFFFF))

Dim shortBytes(0 To 2) As UByte = {11, 22, 33}
Dim As ULong unchanged = 77
Require(Not EncodeLittleEndian32(1, shortBytes()), "Short output accepted")
Require(shortBytes(0) = 11 AndAlso shortBytes(1) = 22 AndAlso _
        shortBytes(2) = 33, "Rejected encoding changed output")
Require(Not DecodeLittleEndian32(shortBytes(), unchanged), "Short input accepted")
Require(unchanged = 77, "Rejected decoding changed output")

Dim offsetBytes(1 To 4) As UByte = {10, 20, 30, 40}
Require(Not EncodeLittleEndian32(1, offsetBytes()), "Wrong lower bound accepted")
Require(offsetBytes(1) = 10 AndAlso offsetBytes(2) = 20 AndAlso _
        offsetBytes(3) = 30 AndAlso offsetBytes(4) = 40, "Rejected bounds changed bytes")
Require(Not DecodeLittleEndian32(offsetBytes(), unchanged), "Wrong input bounds accepted")
Require(unchanged = 77, "Rejected input bounds changed output")
Print "Explicit byte-format checks passed"
