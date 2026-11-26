' Umicom Bits2Banking
' File: content/labs/languages/reflection-workshop/manual_catalogue.bas
'
' PURPOSE:
'   Combine a FreeBASIC compile-time type query with a reviewed runtime descriptor table.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT

Type Reading
    stationId As Long
    degreesC As Long
End Type

Type FieldDescription
    fieldName As String
    unitName As String
End Type

Dim sample As Reading
sample.stationId = 3
sample.degreesC = 68

' TypeOf asks the compiler for one declaration's type. The initializer
' copies a value. The assignment changes only this separate local.
Dim As TypeOf(sample.degreesC) editable = sample.degreesC
editable = 70

' Maintain public field labels deliberately. This table can expose only
' names and units meant to appear in a settings view.
Dim descriptions(0 To 1) As FieldDescription
descriptions(0).fieldName = "station_id"
descriptions(0).unitName = "station number"
descriptions(1).fieldName = "degrees_c"
descriptions(1).unitName = "degrees Celsius"

For index As Integer = LBound(descriptions) To UBound(descriptions)
    Print descriptions(index).fieldName; " - "; descriptions(index).unitName
Next index
Print "editable local bytes: "; LTrim(Str(SizeOf(editable)))
Print "editable local value: "; LTrim(Str(editable))
Print "stored measurement: "; LTrim(Str(sample.degreesC))
