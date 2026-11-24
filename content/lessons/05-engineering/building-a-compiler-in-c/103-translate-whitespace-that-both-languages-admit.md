<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/103-translate-whitespace-that-both-languages-admit.md

PURPOSE:
Translate whitespace that both languages admit

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Translate whitespace that both languages admit

Two programs can look identical in an editor and contain different bytes. A **lexer** divides those bytes into words, operators and other tokens that the language understands. A space between tokens can change how the lexer separates them. Some spaces are difficult to see.

## Compare the C and Java rules

| Byte | Name | C23 at a token boundary | Java at a token boundary |
| --- | --- | --- | --- |
| `20` | Ordinary space | Admitted | Admitted |
| `0C` | Form feed | Admitted | Admitted |
| `0B` | Vertical tab | Admitted | Outside the Java whitespace list |

The common translator can only carry syntax whose meaning is known in both supported profiles. It accepts form feed between admitted tokens. It refuses vertical tab in the common profile. Comment text has its own portable spelling rules because compilers can process continuations and escapes before reading a comment. [C23 working draft](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf) · [Java lexical structure](https://docs.oracle.com/javase/specs/jls/se25/html/jls-3.html#jls-3.6)

## Compare both directions using one function

The supported C function returns `6 * 7`. The hosted Java edition returns the same integer from its matching static method. First create a fresh practice directory in a terminal where `umicom-c` is available. Stop if the directory already exists so you keep any previous work.

~~~powershell
New-Item -ItemType Directory -Path 'shared-spacing-practice' -ErrorAction Stop
Set-Location 'shared-spacing-practice'
$spacing = [char]0x0C
$text = "int answer(void) { return 6${spacing}*7; }"
[IO.File]::WriteAllText((Join-Path $PWD 'spacing.c'), $text + [Environment]::NewLine)
umicom-c translate c-to-java spacing.c UmicomAnswer.java
umicom-c translate java-to-c UmicomAnswer.java spelling-back.c
~~~

Expect a successful exit from both commands and two new output files. The target compiler may choose a different visual spacing style. Compare the order of `6`, `*` and `7` in both functions. The arithmetic result remains 42.

## Compare two spellings for an empty parameter list

The parentheses after a function name describe the values it accepts. In C23, `int answer()` and `int answer(void)` both declare zero parameters. Java's matching no-input method uses `answer()`. The Umicom C translator accepts both C spellings and uses the explicit `void` form when it generates C.

1. Work in a fresh folder so the practice files from the previous section stay available.
2. Save this C definition as `answer.c`.

~~~c
int answer() { return (10 + 4) * 3; }
~~~

3. Run the two translation commands.

~~~powershell
umicom-c translate c-to-java answer.c UmicomAnswer.java
umicom-c translate java-to-c UmicomAnswer.java answer-roundtrip.c
~~~

4. Compare both generated functions. Expect `public static int answer()` in Java and `int answer(void)` in C. The expression still returns 42.
5. Change the original C definition to `int answer(void)` and translate in a new folder. Compare the generated Java files. The two accepted input spellings produce the same Java.
6. Try `int answer(int input)` with an unused target filename. Expect a diagnostic. Restore one of the zero-parameter spellings before continuing.

~~~text
DEFINE a function named answer with zero parameters
RETURN (10 + 4) times 3
~~~

Calling one of these functions returns a value to its caller. For a console exercise, print that return value in the caller. The process status is a separate indication of whether the run succeeded. [WG14 C23 working draft, function declarators](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)

## Diagnose a refusal without replacing a previous file

In the practice folder, make a second input using `[char]0x0B` in the same location and give the requested output an unused filename. Expect a source-location refusal. Inspect the input as bytes to identify the invisible character. Replace it with an ordinary space in a practice copy and try a fresh output path. Keep the files from the first successful translation for comparison.

For a Studio translation tool, the compiler owns token admission and reports the original position. A UI can display that position and the destination path. An existing document stays useful while the user repairs the next input.

[Course contents](index.md) · [Previous: Require a complete debugger command](102-require-a-complete-debugger-command.md) · [Next: Keep the exact filename on Windows](104-keep-the-exact-filename-on-windows.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/103-translate-whitespace-that-both-languages-admit.html)
