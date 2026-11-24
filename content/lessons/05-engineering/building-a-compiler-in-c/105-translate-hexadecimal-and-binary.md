<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/105-translate-hexadecimal-and-binary.md

PURPOSE:
Translate hexadecimal and binary

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Translate hexadecimal and binary

The same whole number can be written in different ways. Decimal uses ten digits. Binary uses two, and hexadecimal uses sixteen. Each place to the left is worth one more power of that base. A **literal** is the written number in a program.

| Spelling | How to read it | Value |
| --- | --- | --- |
| <code>42</code> | Four tens and two ones | 42 |
| <code>0x2A</code> | Two sixteens and ten ones. The letter A stands for ten. | 42 |
| <code>0b101010</code> | 32 + 8 + 2 | 42 |

## Predict which bits survive a mask

The AND operator keeps a bit when it is set in both values. The mask <code>0B111111</code> sets the six lowest bits. It keeps every bit used to represent 42.

~~~text
VALUE ← READ hexadecimal 2A
LOW_SIX ← READ binary 111111
RETURN the bits set in both VALUE and LOW_SIX
~~~

In C23, an empty parameter list in a function definition means it takes no arguments. Save the function as <code>answer.c</code>.

~~~c
int answer() { return 0x2A & 0B111111; }
~~~

In Java, the method belongs to a class. The prefix letters and digits express the same two values.

~~~java
public final class UmicomAnswer {
    public static int answer() {
        return 0x2A & 0B111111;
    }
}
~~~

## Translate in both directions

1. Open PowerShell in a new practice folder and save the C source above as <code>answer.c</code>. Use the current Umicom C CLI on your <code>PATH</code>. Save the Java listing in your notes so the translation can create its own output file.
2. Ask the checked Umicom translator to generate Java. Open <code>UmicomAnswer.java</code> and locate the two prefixes. Compare the function body with your notes.
3. Translate the result back to C. Compare the body of <code>answer-roundtrip.c</code> with the original. Expect the same digits and AND operator. The returned C function uses the explicit <code>(void)</code> convention.

~~~powershell
umicom-c translate c-to-java answer.c UmicomAnswer.java
umicom-c translate java-to-c UmicomAnswer.java answer-roundtrip.c
~~~

For an additional check, add <code>int main(void) { return answer() == 42 ? 0 : 1; }</code> to a practice copy of the result. Compile that copy with a C23 compiler and expect exit code zero. A Java caller can make the same comparison using <code>UmicomAnswer.answer()</code>.

## Explore a refusal without losing your answer

Change the returned value in a separate C source file to <code>0x80000000</code>. Use a fresh output name. Expect a diagnostic from the translator because the common positive range ends at <code>0x7FFFFFFF</code>. With 32-bit <code>int</code>, Java gives that high-bit spelling a negative signed value and C can give it an unsigned type. The checked translation keeps the smaller range so callers get the same meaning.

C23 can put an apostrophe between digits. Java uses an underscore. Use unseparated digits in this common spelling profile. A missing tool or an existing destination also produces an error. Check the command and its diagnostic, then choose a fresh result filename before repeating the valid exercise.

The Umicom C lexer already owns the digit and range rules. Translation uses that same lexer and adds a spelling check for both targets. A Studio translation view can use the public compiler service and show the same refusal alongside the original source.

[C23 integer constants](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf) · [Java integer literals](https://docs.oracle.com/javase/specs/jls/se25/html/jls-3.html#jls-3.10.1)

[Course contents](index.md) · [Previous lesson · Keep the exact filename on Windows](104-keep-the-exact-filename-on-windows.md) · [Related lesson · Translate whitespace that both languages admit](103-translate-whitespace-that-both-languages-admit.md) · [Earlier lesson · Admit decimal literals without overflow](14-admit-decimal-literals-without-overflow.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/105-translate-hexadecimal-and-binary.html)

[Next lesson · Translate a checked local update](106-translate-a-checked-local-update.md)
