'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/swap_values.bas
'
' PURPOSE:
'   Follow separate scalar, pointer and string exchanges without implying object copies or transactions.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

' Same-type scalars keep the exchange easy to inspect.
Dim first As Long = 6
Dim second As Long = 42
Swap first, second
If first <> 42 OrElse second <> 6 Then End 1
Print "values="; first; ","; second

' An address identifies storage. Swapping addresses does not swap that storage.
Dim leftView As Long Ptr = @first
Dim rightView As Long Ptr = @second
Swap leftView, rightView
If leftView <> @second OrElse rightView <> @first Then End 2
If first <> 42 OrElse second <> 6 Then End 3
*leftView = 9
If first <> 42 OrElse second <> 9 OrElse *rightView <> 42 Then End 4
Print "after pointer write="; first; ","; second

' Variable-length strings exchange their runtime descriptors. Both variables
' still own ordinary strings; this is not a portable C structure operation.
Dim activeName As String = "preview"
Dim nextName As String = "export"
Swap activeName, nextName
If activeName <> "export" OrElse nextName <> "preview" Then End 5
Print "names=["; activeName; "] ["; nextName; "]"

' Same-variable exchange leaves its value unchanged. Do not generalize this
' exercise to side-effecting expressions or concurrently accessed objects.
Swap first, first
If first <> 42 Then End 6
Print "same variable="; first
End 0
