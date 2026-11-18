<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/03-text-input-and-validation.md

PURPOSE:
Text input, strings and validation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Text input, strings and validation

[Course contents](index.md)
Input is data supplied while the program runs. It can be empty, misspelled or unexpectedly large. A String stores text and manages its own storage. It is not the same representation as a C char pointer. Keep user input as text until you have checked what it means.

~~~basic
Dim As String answer
Line Input "Choose chat or media: ", answer
answer = LCase(Trim(answer))
If answer = "chat" Then
    Print "Selected the chat lesson"
ElseIf answer = "media" Then
    Print "Selected the media lesson"
Else
    Print "Please type chat or media"
End If
~~~

1. Save as input.bas, compile and run it from the terminal.
2. Type chat and press Enter. Expect the chat message.
3. Run again and type spaces around MEDIA. Trim removes surrounding spaces and LCase produces lowercase text for this simple command comparison.
4. Run again with an empty line or an unknown word. Expect the help message; it must not start any application or remote request.

Line Input reads a line into answer. A prompt is the text explaining what to enter. If, Then, ElseIf, Else and End If form a decision. Only one matching branch runs. LCase and Trim are library functions, not new syntax invented by the application. Parentheses enclose their arguments. Nesting LCase(Trim(answer)) applies Trim first.

Strings can contain non-ASCII text, but character count and byte count are different concepts. Do not assume Len reports human-perceived characters for UTF-8 data. C APIs commonly consume explicit UTF-8 bytes and lengths. If you convert text to a number, check the whole accepted syntax and range; a conversion that accepts an initial numeric prefix does not prove the entire input was valid.

Never paste a user’s answer into a shell command to execute it. This small menu chooses between fixed branches. An Umicom application should use a registered Framework command and validate its arguments, rather than interpreting arbitrary text as executable code.


## Practice

Add a third fixed choice named lessons. Test all three valid choices, the empty string and a misspelling. The desired result is one clear response per run. If every answer selects chat, inspect the comparison and branch structure; do not change the data until the program appears to work.


## Continue learning

[Previous: Names, values and number types](02-names-values-and-number-types.md) · [Course contents](index.md) · [Next: Expressions, comparisons and decisions](04-expressions-decisions-and-operators.md)
