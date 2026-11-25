<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/125-choose-typed-values-in-the-c-console.md

PURPOSE:
Choose typed values in the C console

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Choose typed values in the C console

Imagine a status lamp for a practice application. The lamp uses a flag, a small value that says whether it should be on. Open the typed Umicom C console when you want the session to remember that a local is a Boolean, which holds false or true.

## 1. Choose the mode before sending any lines

A console session keeps accepted local values while you feed it lines. In the typed console, the declaration below gives `flag` the `bool` type. The console converts the nonzero `-7` to the stored value `1`. A zero initializer stores `0`. This conversion to the two Boolean values is called **normalization**.

~~~c
bool flag=-7;
~~~

~~~text
umicom-c script --typed --stdin
~~~

Put `--typed` immediately after `script`. The `--stdin` option reads standard input, the text supplied to the command. The checked console transcript in the next lesson starts with this exact declaration and reports `ok`.

~~~text
WHEN the selected console is typed
    IF the initializer is zero, store 0
    OTHERWISE, store 1
KEEP the declared type and stored value for the following lines
~~~

## 2. Keep an older console input working

Some existing console scripts use the letters `bool` as the name of an integer. Save the following two lines as `legacy-name.ucs`, a plain text file, and feed them to the default console.

~~~c
int bool=42;
return bool;
~~~

~~~powershell
Get-Content -Raw -LiteralPath './legacy-name.ucs' | umicom-c script --stdin
~~~

The check printed both lines below. The first acknowledges the declaration. The second displays the integer stored under the name `bool`.

~~~text
ok
42
~~~

## 3. Predict three stored values

On paper, start three separate typed sessions. Use `-7`, `0` and `15` in the flag declaration. Write the stored values beside them. Your answers should be `1`, `0` and `1`. Then circle `--typed` in the first command above and label that choice in a future console test. Keeping the mode visible makes it easier to tell which rule produced a value.

[Course contents](index.md) · [Previous lesson · Store a value in an unsigned byte](124-store-a-value-in-an-unsigned-byte.md) · [Next lesson · Keep the accepted value during a console preview](126-keep-the-accepted-value-during-a-console-preview.md) · [Measure a Boolean literal without reading its value](123-measure-a-boolean-literal-without-reading-its-value.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/125-choose-typed-values-in-the-c-console.html)
