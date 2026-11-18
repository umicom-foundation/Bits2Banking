'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/block_comments.bas
'
' PURPOSE:
'   Demonstrate nested comments and a logical statement spanning physical lines.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

Dim answer As /' The declaration resumes with its type. '/ Integer = 40

/' Outer explanation.
   /' Inner explanation: tags such as ?> are just comment text. '/
   This line is still in the outer explanation.
'/
answer = answer + /' The expression crosses a physical line
                     while this comment remains open. '/ 2
If answer <> 42 Then End 1
Print "Answer: 42"
Print "Nested comments preserved the statement"
