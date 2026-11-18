' -----------------------------------------------------------------------------
'  * Umicom Bits2Banking
'  * File: labs/languages/native-language-boundary/named_constants.bas
'  *
'  * PURPOSE:
'  *   Use typed FreeBASIC constant expressions for reviewed limits while keeping runtime inputs separate.
'  *
'  * AUTHOR AND ORGANISATION:
'  * Sammy Hegab
'  * Umicom Foundation
'  *
'  * LICENCE:
'  * MIT
'  *--------------------------------------------------------------------------
' 
' 
Option Explicit

Const As Long UnitsPerBox = 6
Const As Long MaximumBoxes = 100
Const As Long MaximumUnits = UnitsPerBox * MaximumBoxes

Function TryUnits(ByVal boxes As Long, ByRef units As Long) As Boolean
    ' Validate before arithmetic and before publishing to the caller.
    If boxes < 0 OrElse boxes > MaximumBoxes Then Return False
    Dim As Long candidate = boxes * UnitsPerBox
    units = candidate
    Return True
End Function

Dim As Long boxes = 7
Dim As Long units = -1
If Not TryUnits(boxes, units) OrElse units <> 42 Then End 1
Print "Accepted units:"; units
Print "Declared upper bound:"; MaximumUnits
units = 73
If TryUnits(MaximumBoxes + 1, units) OrElse units <> 73 Then End 1
Print "Rejected count left the output unchanged."

' In a separate learning copy, try UnitsPerBox = 8 and compile again.
' A Const declaration is not a mutable variable or a live spreadsheet formula.
