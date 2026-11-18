'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/pixel_grid.bas
'
' PURPOSE:
'   Traverse explicit row, column and channel bounds in a small original RGB grid.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------


Dim pixels(0 To 1, 0 To 1, 0 To 2) As UByte
' Keep initialization visible; no image decoder or memory-layout cast is used.
For row As Integer = LBound(pixels, 1) To UBound(pixels, 1)
    For column As Integer = LBound(pixels, 2) To UBound(pixels, 2)
        For channel As Integer = LBound(pixels, 3) To UBound(pixels, 3)
            pixels(row, column, channel) = 0
        Next channel
    Next column
Next row
pixels(0, 0, 0) = 255
pixels(0, 1, 1) = 255
pixels(1, 0, 2) = 255
For channel As Integer = 0 To 2
    pixels(1, 1, channel) = 255
Next channel

Dim pixelCount As ULong = 0
Dim channelTotal As ULong = 0
Dim expected(0 To 1, 0 To 1) As ULong = {{255, 255}, {255, 765}}
For row As Integer = LBound(pixels, 1) To UBound(pixels, 1)
    For column As Integer = LBound(pixels, 2) To UBound(pixels, 2)
        Dim pixelTotal As ULong = 0
        For channel As Integer = LBound(pixels, 3) To UBound(pixels, 3)
            pixelTotal += pixels(row, column, channel)
        Next channel
        If pixelTotal <> expected(row, column) Then End 1
        Print "row="; row; " column="; column; " channel sum="; pixelTotal
        channelTotal += pixelTotal
        pixelCount += 1
    Next column
Next row
If UBound(pixels, 0) <> 3 OrElse pixelCount <> 4 OrElse channelTotal <> 1530 Then End 2
Print "Four pixels checked; total channel sum="; channelTotal
' Index dimensions describe this example's meaning. A C/SDK byte boundary
' needs its own explicit channel order, stride and lifetime contract.
End 0
