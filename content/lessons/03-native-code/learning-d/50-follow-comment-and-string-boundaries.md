<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/50-follow-comment-and-string-boundaries.md

PURPOSE:
Follow comment and string boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Follow comment and string boundaries

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `comment_boundaries.d` in `labs/languages/native-language-boundary` in the course checkout. Use a plain-text editor. Find a comment marker inside a quoted string and one in source text. Predict which one the scanner will consume as a comment.

## The same characters can be code or data

A compiler does not interpret every character in a file as an instruction. It first identifies words, punctuation, strings and comments. A string stores text as a value. A comment explains source without becoming an executable expression. A lexical scanner tracks these boundaries. This lesson uses a small D program and Umicom C’s separate source-region inspector to show why a delimiter inside text must not be mistaken for a command.

1. Open labs/languages/native-language-boundary/comment_boundaries.d in Bits2Banking. It is a standalone D example, not a program for the bounded Umicom C integer compiler.
2. Review the earlier lesson on bytes and code points. The examples here use ASCII characters so their byte positions are easy to count.
3. Write down where each string and comment starts and ends before attempting a build.


## Compare escaped text with raw text

Ordinary double-quoted D strings interpret escape sequences. A backslash can introduce an escape, so representing a literal backslash requires the appropriate escaped spelling. An r-prefixed string and a backtick string keep their content raw. Backticks make embedded double quotes convenient. These are spelling choices for text values; they do not request code execution.

~~~d
enum string rawPath = r"C:\courses\umicom";
enum string escapedPath = "C:\\courses\\umicom";
static assert(rawPath == escapedPath);
~~~


## Read the declarations one part at a time

Here enum declares a compile-time constant value. string names a sequence of immutable characters. The equals sign initializes that value. A semicolon ends the declaration. static assert asks the D compiler to reject the program if its condition is false during compilation. The equality comparison checks the text values, not whether the two source spellings look alike. This example can therefore catch a misspelled escape before main runs.


## Track nested comments with a depth counter

D has line comments, non-nesting slash-star block comments and nesting slash-plus comments. Inside a nesting comment, each slash-plus opens another level and each plus-slash closes one. Quotes there are comment content, so an apparent quoted marker still affects nesting. A scanner can track the depth with one counter instead of recursive calls.

~~~text
start outside comment: depth 0
read /+              : depth 1
read another /+      : depth 2
read +/              : depth 1
read final +/        : depth 0, resume ordinary source
~~~


## Build the standalone D example

Use an installed D compiler such as DMD for this file. The commands below assume dmd is on PATH. The example has been authored for the lesson; if a D compiler is unavailable, source inspection is not an execution pass. The program uses the D runtime for output and exceptions and is not a BetterC-only program.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd -checkaction=context comment_boundaries.d -of=comment_boundaries.exe
& ".\comment_boundaries.exe"
~~~


## Expected output

No model, network service or other compiler is started by the program. The displayed delimiter is ordinary output data.

~~~text
Raw and escaped paths contain the same bytes.
Show "quotes", ?> and /+ as text.
Source text is data unless a separate compiler or evaluator is invoked.
~~~


## Inspect a D envelope with Umicom C

Umicom C has an experimental regions command that classifies spans in a file containing explicit language tags. The new D tag is lowercase <?d followed by whitespace and closed by ?>. Classification reports the original byte offset and length. It does not compile the D code, resolve imports or link a D runtime. The integer compiler continues to refuse such a mixed envelope.

~~~powershell
Set-Location "C:\umicom\umicom-c"
cmake --preset windows-ucrt64-debug
cmake --build --preset windows-ucrt64-debug
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" regions examples/d_regions.umc
~~~


## Understand the bounded inspector’s support

A full D compiler handles more syntax than this envelope inspector. The inspector protects ordinary quoted strings and characters, r-prefixed and backtick raw strings, ordinary comments and nested slash-plus comments. Its nesting bound is 32, which is an Umicom envelope limit, not a claimed D language limit. q-delimited or token strings, x-prefixed hex strings and i-prefixed interpolation are refused explicitly. Keep those forms in separate D files and use the D compiler.


| Operation | What it establishes |
| --- | --- |
| D compiler accepts comment_boundaries.d | The standalone D source fits that compiler’s supported language and toolchain |
| Umicom C regions accepts d_regions.umc | The documented lexical subset has bounded, identifiable spans |
| Umicom C check refuses d_regions.umc | The bounded integer compiler has not acquired a D frontend |
| A course link check passes | The educational files and references are connected; it does not execute D |


## Preserve errors and original positions

If a comment never closes, reporting an apparently valid region would hide the real cause. The inspector returns zero published regions and points to the opening comment. If nesting exceeds its bound, it identifies the opening marker that exceeds the limit. Unsupported string forms get their own diagnostic. Consumers must ignore any partial array contents when the returned count is zero after failure.


## Practice without confusing classification with execution

Make one change at a time and predict which tool should reject it.

1. Remove one backslash from the escaped path. Check whether the D compiler rejects an invalid escape or the compile-time equality assertion fails.
2. Add a balanced nested slash-plus comment and confirm the surrounding code remains unchanged.
3. Remove the outer comment terminator from a copy of the envelope. Expect an unterminated-comment diagnostic and no published regions.
4. Put ?> inside the raw string. Expect the inspector to retain it inside the same D span.
5. Replace a raw string with a q-token string in an envelope copy. Expect an explicit unsupported-form diagnostic, even if a D compiler could compile that form in a separate .d file.
6. Explain why adding lexical support does not provide reflection, machine-code generation or cross-language calling. Those need separate compiler and ABI work.


## Extend a tool only after identifying its layer

Studio can use lexical spans for navigation or presentation, while a compiler service checks syntax and an ABI boundary connects compiled modules. Keeping these roles separate prevents a colored editor tab from being advertised as executable language support. Framework remains the reusable application service boundary; this change lives in Umicom C’s existing scanner rather than duplicating a compiler inside each application.


## Reference


- [D lexical reference: comments and string forms](https://dlang.org/spec/lex.html)


[Previous: Constrain operator templates and test their meaning](49-constrain-operator-templates-and-test-their-meaning.md)

[Next: Admit values before exhaustive state dispatch](51-admit-values-before-exhaustive-state-dispatch.md)
