' Umicom Bits2Banking
' File: content/labs/languages/reflection-workshop/practice/exact_type_choice.bas
'
' PURPOSE:
'   Compare a matching and an incompatible FreeBASIC declared type during compilation.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT

Dim degrees As Long = 68
Dim fractionalDegrees As Double = 68.5

' The field adapter requires the exact Long declaration. The preprocessor
' chooses the report statement before the application runs.
#if TypeOf(degrees) = TypeOf(Long)
    Print "first member: admitted"
#else
    Print "first member: refused"
#endif

#if TypeOf(fractionalDegrees) = TypeOf(Long)
    Print "second member: admitted"
#else
    Print "second member: refused"
#endif
