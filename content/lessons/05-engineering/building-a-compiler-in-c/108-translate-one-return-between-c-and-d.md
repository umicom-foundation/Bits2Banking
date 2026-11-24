<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/108-translate-one-return-between-c-and-d.md

PURPOSE:
Translate one return between C and D

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Translate one return between C and D

A **function** groups steps that can be called from another part of a program. The two functions in this exercise return one integer. You can compare their punctuation and verify the same arithmetic after translation.

## Read the number before translating

Hexadecimal <code>0x20</code> means 32. Binary <code>0b1010</code> means 10. These two numbers have separate bits set. The OR operator <code>|</code> keeps a bit when either number contains it, so the answer is 42.

~~~text
START a function with no parameters
RETURN the bits set in 32 OR 10
~~~

Save this C23 function as <code>answer.c</code> in a fresh practice folder.

~~~c
int answer(void) { return 0x20 | 0b1010; }
~~~

The generated D function keeps the same expression and uses an empty parameter list.

~~~d
int answer() {
    return 0x20 | 0b1010;
}
~~~

## Compare two outputs and use a caller

1. Open PowerShell in the practice folder. Use a current Umicom C CLI with both D directions available in its help.
2. Run the two commands. Open both new files. Verify the expression and the difference between empty parentheses in D and the explicit C <code>(void)</code> convention.
3. Add a separate C caller containing <code>int answer(void);</code> and <code>int main(void) { return answer() == 42 ? 0 : 1; }</code>. Build it with the regenerated C file. Expect the caller to exit with code 0.

~~~powershell
umicom-c translate c-to-d answer.c answer.d
umicom-c translate d-to-c answer.d answer-roundtrip.c
~~~

If you already have DMD for Windows, save this optional caller as <code>verify.d</code>. The file <code>answer.d</code> supplies the default module name <code>answer</code>.

~~~d
import answer : answer;

int main() {
    return answer() == 42 ? 0 : 1;
}
~~~

~~~powershell
dmd verify.d answer.d -of=verify-d.exe
.\verify-d.exe
$LASTEXITCODE
~~~

Expect exit code 0 after a successful build. If DMD cannot find the module, confirm both files are together and the generated file is named <code>answer.d</code>. If the translator refuses a module header or a local variable, restore the earlier one-return example and choose a fresh output name.

This checked profile accepts one signed integer return expression. The example connects the Umicom C translation service with the D language reference. An editor can show each emitted file and keep the original source available.

[D function declarations](https://dlang.org/spec/function.html) · [D module names](https://dlang.org/spec/module.html) · [DMD on Windows](https://dlang.org/dmd-windows.html)

[Course contents](index.md) · [Previous lesson · Count reached source statements](107-count-reached-source-statements.md) · [Related lesson · Translate hexadecimal and binary](105-translate-hexadecimal-and-binary.md) · [Earlier lesson · Translate a checked local update](106-translate-a-checked-local-update.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/108-translate-one-return-between-c-and-d.html) · [D keyword reference](../../03-native-code/d-keyword-reference/index.md)

The following exercise shows the checked function entry with initialized integer locals and an update.

[Next lesson · Translate an initialized local between C and D](109-translate-an-initialized-local-between-c-and-d.md)
