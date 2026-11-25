<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/128-read-a-signed-cast-in-complete-c.md

PURPOSE:
Read a signed cast in complete C

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read a signed cast in complete C

Imagine that a shelf held 45 books and you handed out three. The expression `onShelf - handedOut` calculates how many remain. A **cast** asks the language to treat the result as a particular type. A **signed integer** can represent negative numbers as well as zero and positive numbers.

## 1. Say which type you intend

Save the program as `signed-cast.c`. The first pair of parentheses after `return` names a type. The second pair groups the subtraction. The cast applies to the value of the whole group.

~~~c
int main(void)
{
    int onShelf = 45;
    int handedOut = 3;
    return (signed int)(onShelf - handedOut);
}
~~~

~~~text
umicom-c interpret signed-cast.c
~~~

The result is `42`. Make a copy named `reordered-cast.c` and change only `(signed int)` to `(int signed)`. The value stays `42`. In this checked complete-C program, both spellings choose the same signed integer type as `(int)`. This example uses the compiler's bounded integer profile.

~~~text
SUBTRACT the number handed out from the shelf count
TREAT the result as a signed integer
RETURN the result
~~~

## 2. Compare generated instructions

The interpreter gives immediate feedback. To keep files for later use, compile both versions to different output names. Run these commands in a practice directory where those two output files are absent.

~~~powershell
umicom-c compile signed-cast.c signed-cast.umcb
umicom-c compile reordered-cast.c reordered-cast.umcb
umicom-c exec signed-cast.umcb
umicom-c exec reordered-cast.umcb
Get-FileHash -Algorithm SHA256 signed-cast.umcb,reordered-cast.umcb
~~~

Both output files return `42`. Their hashes also match in this exercise. The casts have the same length and type, so swapping the two words keeps the source positions aligned and generates the same checked instructions. A hash summarizes the exact bytes of a file. A matching result alone only tells you the outcome of one run.

If a command refuses to write an existing output file, choose a new filename. If the interpreter diagnoses the type words, check that the command is using the intended Umicom C release and that the two type words are inside their own parentheses. Read the reported line and column before changing the arithmetic.

## 3. Put parentheses around the intended value

Compare `(onShelf - handedOut)` with `(signed int)(onShelf - handedOut)`. The first only groups the expression. The second also says which type to use. Try setting `handedOut` to 50 in a new copy. Predict the result before running it. Because the result is signed, `45 - 50` gives `-5` in this profile.

In Umicom Studio, try inspecting the expression first and then building a separate artifact. Keep the source, expected value and generated file name together so someone else can repeat the check. The related signed local types lesson shows where the same type words appear in a declaration.

[Course contents](index.md) · [Previous lesson · Submit a typed script as one block](127-submit-a-typed-script-as-one-block.md) · [Related lesson · Read equivalent signed local types](120-read-equivalent-signed-local-types.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/128-read-a-signed-cast-in-complete-c.html)
