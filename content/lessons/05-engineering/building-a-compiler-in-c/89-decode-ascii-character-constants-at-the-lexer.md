<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/89-decode-ascii-character-constants-at-the-lexer.md

PURPOSE:
Decode ASCII character constants at the lexer

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Decode ASCII character constants at the lexer

[Course contents](index.md)

## Give a quoted mark an integer meaning

A computer stores numbers. A character encoding assigns numbers to text characters so that programs can agree on their meaning. ASCII assigns 65 to uppercase A and 42 to the star. In this lesson you will follow a quoted character through source text, a token, an instruction and a returned integer. Umicom C accepts this deliberately bounded ASCII form. It does not yet provide a char storage type, strings, general Unicode character constants or a complete C23 compiler.


## Start with four different kinds of object

An apostrophe in a source file is a byte. A lexer recognizes a pair of apostrophes and the permitted content between them as one token. A token describes a piece of source for the parser. An instruction is an operation the runtime will execute. Keeping those objects separate prevents a source spelling feature from unnecessarily expanding the virtual machine.


| Object | Our example | What it means |
| --- | --- | --- |
| Source bytes | '*' | Opening quote, star, closing quote |
| Integer token | value=42, length=3 | One value with a source span |
| Instruction | PUSH 42 | Place the existing integer on the evaluation stack |
| Program result | 42 | Return the integer; do not print a star glyph |


## Read the complete smallest program

main names the entry function. int declares its result type, and void describes the accepted no-parameter entry form. The braces enclose the body. return supplies its final value. The quoted star is a character constant; the semicolon terminates the return statement. Without quotes, a star is an operator and cannot stand alone as this expression.

~~~c
int main(void) {
    return '*';
}
~~~


## Configure and compile the tool first

Open PowerShell in the Umicom C checkout. These commands select the UCRT64 toolchain and the matching Windows preset. Configuration writes the build rules; building creates the compiler executable. Run commands separately and stop at an unexpected error, because a failed build can leave an older executable in place. The example already lives in examples/ascii_characters.uc.

~~~powershell
Set-Location "C:\umicom\umicom-c"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-debug
cmake --build --preset windows-ucrt64-debug --parallel 2
.\build\windows-ucrt64-debug\bin\umicom-c.exe check examples/ascii_characters.uc
~~~


## Predict the instruction budget

Check should accept two instructions. PUSH stores the integer 42 on the evaluation stack. RETURN takes it as the result. Fuel limits the number of executed instructions, not the number of characters in the source or elapsed milliseconds. With two units, run should print Result: 42 and Instructions: 2. With one, it should refuse before publishing a result because RETURN has not executed.

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe run examples/ascii_characters.uc --max-steps 2
.\build\windows-ucrt64-debug\bin\umicom-c.exe run examples/ascii_characters.uc --max-steps 1
~~~


## Use escapes for values you cannot type directly

An escape starts with a backslash inside the quotes. Its source spelling contains several bytes, but the lexer converts it into one integer. For example, backslash followed by n represents the ASCII line-feed value 10. It does not insert a raw line break into the source token. A quoted backslash needs another backslash, and a quoted apostrophe needs a preceding backslash. The implementation maps each accepted spelling explicitly so that a host compiler’s char signedness cannot change the language value.


| Spelling | Decoded integer | Meaning |
| --- | --- | --- |
| '\n' | 10 | Line feed |
| '\r' | 13 | Carriage return |
| '\t' | 9 | Horizontal tab |
| '\\' | 92 | Backslash |
| '\'' | 39 | Apostrophe |
| '\0' | 0 | Zero value, not an empty token |


## Understand base eight and base sixteen

Octal notation uses digits zero through seven. Each position is worth eight times the position to its right. Hexadecimal uses digits zero through nine and A through F, with sixteen times the weight per position. In an octal escape, backslash 101 means 1×64 + 0×8 + 1, which is 65. In a hexadecimal escape, backslash x41 means 4×16 + 1, also 65. Both represent uppercase A. These forms are useful when the source must make an exact encoded value visible.

~~~c
int main(void) {
    return 'A' + '\101' + '\x41';
}
~~~


## Apply the bounded numeric contract

The preceding expression returns 195, because it adds three integers equal to 65. Each individual character constant must still lie between zero and 127. Octal accepts one to three digits. Hexadecimal uses a lowercase x prefix followed by at least one digit; either letter case is accepted for the digits themselves. Hexadecimal scans the entire digit run before expecting the closing quote. Long leading-zero escapes remain limited by the source-byte budget. The arithmetic result of a larger expression follows the existing checked integer rules, rather than being limited to ASCII.


## Check range before multiplying

Suppose the decoded value so far is value, the next digit is digit and the base is radix. The next value would be value×radix+digit. Before performing that calculation, the lexer checks whether value exceeds (127-digit)/radix. A refusal at that point avoids computing an overflowing intermediate. This is a reusable technique for parsers: validate the next operation’s bounds before it changes state. It is different from multiplying first and hoping to detect overflow afterward.


## Follow source ownership through the helper

Open src/lexer.c and find ascii_character. The lexer receives a borrowed source span with an explicit length. Borrowed means the caller owns the bytes and must keep them alive during the call. The helper advances only while an index is inside that length. It remembers the opening quote for diagnostics, consumes the closing quote, and emits an existing integer token. It neither allocates a string nor stores a pointer for later execution. The parser and emitter can therefore reuse their ordinary integer path.


## Keep lookalike spellings distinct

A quote inside an already-started number has a different job: 1'000 is a numeric digit separator. A quote at the beginning of a token starts a character constant. The lexer already knows which rule owns the current token. It must not scan comment markers inside a valid constant as if they were source comments: the quoted slash and star are just integer values. Two adjacent character constants without an operator are refused; they do not concatenate into a string.

~~~c
int main(void) {
    return '/' + '*';
}
~~~


## Make malformed examples deliberately

Use a separate scratch source and change one item at a time. Empty quotes have no value. Two letters contain too many values for this profile. An unknown escape has no defined interpretation. A raw non-ASCII byte is outside the direct-character rule. Unicode prefixes and escapes are unsupported rather than silently reduced to a byte. Keep the original examples so that a refused experiment cannot be mistaken for a failed baseline.


| Input | Why it is refused |
| --- | --- |
| '' | No character |
| 'ab' | More than one character |
| '\q' | Unknown escape |
| '\200' | Octal value 128 exceeds 127 |
| '\x80' | Hexadecimal value 128 exceeds 127 |
| '\0000' | Fourth octal digit remains before closing quote |
| u8'A' | Unsupported character-prefix grammar |


## Separate source names from literal content

In int main(void){int A=1;return 'A';}, A is a local variable name in the declaration. Inside the quotes it is literal content, not a reference to that local. The source-warning collector must report the local as never read. A string search for the letter A would produce the wrong answer. Correct warnings use the compiler’s token and name-resolution rules.


## Reuse the existing saved representation

Compile writes the integer instructions into the existing format-1 bytecode representation. The PUSH source offset continues to point at the opening quote, so diagnostics can identify the original spelling. No new wire opcode is needed. Use a fresh filename because compile refuses to overwrite an existing artifact. Then execute that artifact with fuel two and compare the result to the source run.

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe compile examples/ascii_characters.uc build/ascii-lesson.umcb
.\build\windows-ucrt64-debug\bin\umicom-c.exe exec build/ascii-lesson.umcb --max-steps 2
.\build\windows-ucrt64-debug\bin\umicom-c.exe trace-bytecode build/ascii-lesson.umcb
~~~


## Check the component that actually parses

UMC_FEATURE_ASCII_CHARACTER_LITERALS has value 33554432. Query umc_compiler_profile(UMC_PROFILE_FEATURES) and test that bit before offering the syntax through an editor integration. The runtime-only profile must not claim this parser feature, because it sees integer records and never reads the quotes. A newer header alone cannot update an older linked library. Compiler identity, runtime identity and source identity are separate facts.


## Run regression checks and explain their limits

The tests cover every direct printable ASCII value, numeric escape values zero through 127, malformed spans, long escapes, source offsets, warnings, fuel and bytecode round trips. They also preserve numeric digit-separator behavior. Passing these cases establishes the bounded implementation exercised by the selected build; it is not proof of Unicode support or a complete C23 conformance suite.

~~~powershell
ctest --test-dir build/windows-ucrt64-debug -R "umicom.c.(ascii-characters|cli-ascii-characters|profile|cli-profile)" --output-on-failure --no-tests=error
~~~


## Try a small text rule without pretending it is Unicode

Create an int local c initialized to uppercase A. Inside a braced if, check c >= 'A' and c <= 'Z', then add 'a' - 'A'. Return c and predict 97. Change the input to a digit and predict that it remains unchanged. This rule uses the contiguous ASCII letter ranges. It does not handle accented letters, language-sensitive casing, Unicode normalization or text encoding conversion. Keeping the limitation explicit is part of designing a trustworthy language feature.


[Previous: Parse an empty statement without emitting code](88-parse-an-empty-statement-without-emitting-code.md)

[Next: Parse initialized declaration lists without changing the virtual machine](90-parse-initialized-declaration-lists.md)
