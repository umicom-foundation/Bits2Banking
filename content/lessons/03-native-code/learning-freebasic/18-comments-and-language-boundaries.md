<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/18-comments-and-language-boundaries.md

PURPOSE:
Distinguish comments, strings and language boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Distinguish comments, strings and language boundaries

[Course contents](index.md)
A source file contains instructions for a computer and explanations for its reader. A comment is an explanation that the language processor does not execute as an instruction. A string is data that the program can use. The same characters can mean different things depending on which context they appear in. This lesson uses FreeBASIC comments, then connects that idea to Umicom C’s experimental source-region scanner.


## 1. Read the complete small BASIC example

Open labs/languages/native-language-boundary/comments.bas. It is a separate FreeBASIC program, not a tagged Umicom source envelope. The named-field comment at its beginning identifies the file, purpose, author and licence. Keep those notices when adapting the exercise. The program’s only state is an integer named total and a string named label. It performs no file, network or model operation.

REM is a statement that starts a comment. FreeBASIC keywords are case-insensitive, so rEm has the same meaning. A colon separates statements on one line: the addition runs first, then the comment begins. An apostrophe starts a comment for the rest of the line too. The apparent assignment to 999 appears after an apostrophe and does not execute. Inside double quotes, the letters REM and symbols ?> are ordinary string data. The expected final integer is five.

~~~basic
Dim As Integer total = 2
REM This is comment text, including ?> and <?java.
total = total + 3 : rEm This is another comment.
' total = 999 does not execute here.
Dim As String label = "REM ?> is text inside a string"
~~~


## 2. Make a prediction before running

1. On paper, write total = 2 for the declaration.
2. Skip the REM line because it is a comment.
3. Add three, obtaining five. Stop interpreting that line as executable code when its REM statement starts.
4. Skip the apostrophe comment, including its apparent assignment.
5. Copy the characters between the double quotes into the string label. They are data, even though some resemble other syntax.

This is a small example of lexical context. Lexical analysis is the stage that identifies words, symbols, comments and literals in source text. A parser then checks how language elements form statements. Type checking asks whether operations make sense for their values. Finding where a comment ends does not provide all of those later stages.


## 3. Compile the independent BASIC program

Use your actual checkout location. Run one command at a time and stop on failure. The example includes a check that total equals five and label has the expected text. It exits with a nonzero code if either check fails. The expected successful output follows. FreeBASIC compilation is separate qualification; this material does not claim that a D, C or Umicom C test executes this BASIC program.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -version
fbc -lang fb -w all -exx comments.bas -x comments.exe
.\comments.exe
~~~

~~~text
REM ?> is text inside a string
Comment checks passed
~~~


## 4. Compare an executable source file with an envelope

Umicom C’s regions command can identify explicitly tagged language regions. A region is a range of bytes with a language label. It is useful when planning an editor or a future frontend dispatcher. The current scanner does not compile BASIC, execute Java, share variables between languages or turn a tag into a compiler. Do not put the following envelope into comments.bas and expect FreeBASIC to accept the tags.

The opening tag selects BASIC boundary-scanning rules. The closing delimiter on the last line ends the region. The earlier closing-looking symbols are protected by REM comments. This exact text has one BASIC region. Complete example files may also contain untagged headers and whitespace regions, so a different region count is not automatically a failure.

~~~text
<?basic
  REM These ?> and <?java symbols belong to the comment.
  PRINT 42 : rEm This ?> remains in a comment too.
?>
~~~


## 5. Know the scanner’s narrow REM rule

The scanner recognizes REM case-insensitively at the start of a line or after a colon, permitting leading spaces and tabs. The three letters must be followed by whitespace or by the end of the admitted source span. The comment ends at a carriage return or line feed. These are explicit boundary rules, not a full implementation of every FreeBASIC grammar feature. BASIC line continuation and block comments remain outside this scanner’s contract.

These strings do not start a REM comment under the documented scanner rule. The first three are not the complete keyword with its required boundary. PRINT REM does not put REM at a statement start. REM?> lacks the required following whitespace or end-of-span boundary. The scanner can classify text that a full BASIC compiler would reject. Classification success therefore must not be reported as syntactic or semantic validity.

~~~text
REMEMBER = 1
rem_value = 1
REM$ = 1
PRINT REM
REM?>
~~~


## 6. Inspect a complete envelope with Umicom C

Use the executable from your configured Umicom C build; change the build directory if necessary. The command prints language names, byte offsets and lengths and a classification-only notice. An offset is a count of bytes from the beginning of the original input. A length is the number of bytes in that region. Comments remain in those original bytes; the scanner does not rewrite the file. This differs from a line number or a Unicode character count.

~~~powershell
Set-Location "C:\umicom\umicom-c"
.\build\bin\umicom-c.exe regions .\examples\basic_comments.umc
~~~


## 7. Understand borrowed spans and failed output

The native umc_source_regions API receives a pointer and a length. The length defines exactly which bytes may be read; it does not require a terminating NUL after that span. The API rejects a NUL within the admitted source. Returned regions contain offsets and lengths, not owned copies of the source. Callers keep the source alive while using the ranges. On failure, output count is zero and partially written region entries must not be consumed. This is an ownership rule that an editor or SDK consumer must preserve.


## 8. Try small experiments safely

1. In a practice copy of comments.bas, move total = 999 before the apostrophe. Predict the new total and explain why the existing check should fail. Restore the original after observing the difference.
2. Change REM to mixed case in a comment. Its meaning should not change. Change the string contents instead and predict which assertion will fail.
3. In a practice envelope, put the only closing delimiter after REM on the same line. The scanner should report a missing closing delimiter because that delimiter is comment text.
4. Put a genuine closing delimiter on a new line. Inspect the regions again and check that comments retained their original byte positions.
5. Explain why successfully discovering a BASIC region cannot establish that PRINT, arrays, file operations or C calls in that region are implemented by Umicom C.


## 9. Connect this to useful project work

An IDE can use language boundaries to select highlighting, associate diagnostics with original source positions or decide which external tool should inspect a separate module. Before executing anything, it still needs an explicit toolchain, supported grammar, ownership contract and tested calling convention. For current Umicom projects, use the earlier fixed-width C boundary exercises for independently compiled FreeBASIC modules. Preserve the Framework C implementation as the reusable service owner.


## 10. Troubleshoot the correct layer

If the fbc command is missing, resolve the FreeBASIC toolchain first. If Umicom C regions reports a missing closing delimiter, inspect comments and quoted strings before counting visible tag symbols. If a tagged file fails under Umicom C run, that is expected: executable mixed-language envelopes are unsupported. Do not suppress the diagnostic or replace the source with guessed translations. Keep the two independent workflows and their evidence separate.


## Further reading

- [FreeBASIC manual: REM](https://www.freebasic.net/wiki/wikka.php?wakka=KeyPgRem)
- [FreeBASIC manual: comments](https://www.freebasic.net/wiki/wikka.php?wakka=ProPgComments)

[Previous: Encode a portable four-byte record](17-encode-a-portable-binary-record.md)

[Next: Combine options with checked bit masks](19-combine-options-with-checked-bit-masks.md)
