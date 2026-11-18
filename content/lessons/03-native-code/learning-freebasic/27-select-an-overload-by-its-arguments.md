<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/27-select-an-overload-by-its-arguments.md

PURPOSE:
Select an overload by its arguments and preserve refused output

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Select an overload by its arguments and preserve refused output

[Course contents](index.md)

## Start with two ways to ask the same question

A byte count describes how many stored bytes an operation would use. Sometimes you already have a numeric count. Sometimes you have a piece of text and want its stored length. These are different inputs to the same general question. Our exercise provides two functions named TryByteCount. One receives an unsigned number; the other receives a counted String. Both try to publish a 32-bit unsigned result. The name begins with Try because refusal is an expected result. A count that does not fit is not silently shortened. This small exercise performs no allocation, file write or model download.


## Read every word in the declarations

Declare tells the compiler that the function's body will be supplied later. Function introduces a procedure that returns a value. TryByteCount is our chosen name. The parentheses hold the parameter list. ByVal amount passes a numeric value to the procedure. ByRef result lets the procedure refer to the caller's result variable. As names a type. ULong is the unsigned 32-bit storage used by this example's result contract. ULongInt is the wider unsigned integer input. String is FreeBASIC's counted text type. The final As Integer describes a success indicator. Zero means refused; the example returns minus one for success. The caller should test zero versus nonzero rather than treating success as the byte count.


## Keep units visible

A number alone does not tell you whether it counts bytes, characters, pixels or tokens. The input variable named requested is already a number of bytes. The text overload uses Len to obtain the length of the counted String. This lesson treats that storage as bytes. It does not promise a Unicode character count, a screen width or the number of tokens produced by an LLM tokenizer. The six ASCII letters in Umicom happen to occupy six bytes, so this first fixture avoids encoding distractions. Review the earlier text-and-bytes lesson before using accented characters or an embedded zero.


## Admit the value before converting it

The largest 32-bit unsigned integer is 4,294,967,295. Our named constant MAX_WIRE_BYTES records that limit in the wider ULongInt type. A comparison first checks whether amount is greater than the limit. On refusal, Return 0 exits before the caller's result is changed. Only an admitted value is converted using CULng and assigned. The wider type matters because it lets the test represent 4,294,967,296, which is one beyond the result limit. Converting that value first and checking afterwards would have lost the information needed to reject it.

~~~basic
If amount > MAX_WIRE_BYTES Then Return 0
result = CULng(amount)
Return -1
~~~


## Reuse the numeric rule from the text overload

The text implementation asks Len for the stored length, converts that nonnegative length to ULongInt with CULngInt, and calls TryByteCount again. That explicit numeric expression selects the numeric overload. The second call therefore reuses the same range admission and output-publication rule. We do not maintain a second copy of the limit test for strings. This is a small example of keeping one owner for reusable behavior. In a production Umicom application, the equivalent service should live in Framework and the language client should translate its own values into the reviewed C contract.

~~~basic
Function TryByteCount(ByRef text As String, ByRef result As ULong) As Integer
    Return TryByteCount(CULngInt(Len(text)), result)
End Function
~~~


## Trace the caller's variables

The example begins with payload containing Umicom, result containing 71 and requested containing 42. Passing payload selects the text overload and changes result to 6. Passing requested selects the numeric overload and changes result to 42. The maximum accepted value is checked next. Before the oversized request, result is deliberately reset to 71. The request is refused and result must still be 71. That old value is a sentinel: a recognizable marker used to prove that failure did not publish partial work. Finally an empty String is accepted with length zero. Empty input and invalid input are different cases.


## Compile the source and inspect the output

Open PowerShell in labs/languages/native-language-boundary within Bits2Banking. The fbc command must refer to an installed FreeBASIC compiler. The -lang fb option selects the normal FreeBASIC dialect; the source is not written for the older QB dialect. The -w all option requests compiler warnings. The -x option chooses an output executable name. Run the commands separately and stop if compilation fails. Do not run an older executable after a failed build.

~~~powershell
fbc -lang fb -w all overloaded_byte_count.bas -x overloaded-byte-count-basic.exe
& .\overloaded-byte-count-basic.exe
~~~

1. Read both declarations before the function bodies.
2. Predict which declaration each typed variable will select.
3. Compile the complete source file.
4. Run it and check the four displayed outcomes: text 6, requested 42, preserved 71, empty 0.


## Distinguish source review from execution

The exercise includes explicit failure exits for each expectation, but writing those checks does not mean they have passed. It requires a real FreeBASIC compile and run. The separate C laboratory in this folder validates its own C boundary only. It cannot establish FreeBASIC overload resolution, runtime String behavior or generated executable compatibility. Keep the compiler version and command with any result you record. If fbc is not recognized, use the installation lesson and verify the compiler path first; changing the source will not repair a missing tool.


## Diagnose ambiguity deliberately

An ambiguous call means the compiler cannot choose one acceptable meaning under its resolution rules. Start by examining the declared types at the call site. Do not respond by deleting an overload or adding arbitrary conversions until the diagnostic disappears. Decide the intended units and value range, then choose a suitable variable type or a checked conversion. Our program uses named, explicitly typed variables to make selection readable. If two operations have materially different side effects, separate procedure names may communicate the contract better than one overloaded name. Short names are not automatically better interfaces.


## Keep the C boundary explicit

A C linker resolves exported symbol names. It does not perform FreeBASIC overload selection on a String descriptor. Do not expose these BASIC functions as an assumed Framework ABI. A production bridge should use distinct reviewed C entry points or one explicitly tagged request, fixed-width numeric fields, clear pointer-length pairs and a documented ownership rule. Translate the String's bytes while the string remains alive; do not let C retain a pointer to temporary storage. This exercise teaches overloads without claiming that a BASIC compiler or runtime is required by Framework.


## Practice without hiding a failed case

Set requested to zero and predict success with result zero. Set it to MAX_WIRE_BYTES and predict the largest accepted result. Set it to MAX_WIRE_BYTES plus one and predict refusal with the previous result preserved. Replace payload with an empty string and explain why that is accepted. In a separate copy, move the assignment above the range test and observe which sentinel assertion should catch the mistake. Restore the original after studying the failure. Write down whether each observation came from reasoning, compiler output or an actual run.


## Further reading

- [FreeBASIC manual: OVERLOAD](https://freebasic.net/wiki/KeyPgOverload)

[Previous: Follow construction and destruction through a scope](26-follow-construction-and-destruction.md)

[Next: Guard a read with short-circuit operators](28-guard-a-read-with-short-circuit-operators.md)
