<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/104-keep-the-exact-filename-on-windows.md

PURPOSE:
Keep the exact filename on Windows

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep the exact filename on Windows

A source file has two kinds of text. Its **filename** lets the operating system find it. The **source bytes** are what a compiler reads after opening it. An ordinary C file can contain the same source whether the filename uses English, Greek or other characters.

## Keep the name through each layer

1. The terminal gives the name to the process.
2. The Windows C runtime makes that argument available to the command-line tool.
3. The file API opens or creates the exact requested path.
4. The compiler reads the source bytes and reports any source error separately.

On supported Windows releases, an application manifest can select a UTF-8 active code page for that hosted process. The supported Umicom C MinGW build embeds this setting alongside the existing icon. The tested profile starts at Windows 10 version 1903 and retains the same Umicom artwork. [Windows UTF-8 code pages](https://learn.microsoft.com/en-us/windows/apps/design/globalizing/use-utf8-code-page)

## Run a tiny program from a new practice directory

The source in this exercise contains ordinary ASCII. The path contains other characters. The program returns 42 so the result is easy to recognize. Confirm you have the current hosted Windows build and that the practice folder is new. Stop at the first unsuccessful command.

~~~powershell
New-Item -ItemType Directory -Path 'filename-practice' -ErrorAction Stop
Set-Location 'filename-practice'
$source = '計算-π.c'
$object = '出力-π.umcb'
$encoding = [Text.UTF8Encoding]::new($false)
[IO.File]::WriteAllText((Join-Path $PWD $source), 'int main(void) { return 6 * 7; }', $encoding)
umicom-c interpret $source
umicom-c compile $source $object
umicom-c exec $object
~~~

Expect `Result: 42` from the interpreted and bytecode executions. Check the output name in the directory. Run the compile command again without changing the output path. The compiler should refuse to replace the earlier bytecode. The existing file remains available to execute.

## Locate a name problem before editing C

If the interpreter reports that it cannot read a file, check that the terminal and the operating system show the same name. Compare an ASCII-name copy with the same contents. If the file opens and the compiler reports a line and column, investigate its source text instead. A correct name does not decide which source characters the language admits.

Studio and other Umicom clients can present the original user path with the compiler’s result. In release evidence, keep filename admission, compile success, output creation policy and embedded visual assets as separate checks.

[Course contents](index.md) · [Previous: Translate whitespace that both languages admit](103-translate-whitespace-that-both-languages-admit.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/104-keep-the-exact-filename-on-windows.html)

[Next lesson · Translate hexadecimal and binary](105-translate-hexadecimal-and-binary.md)
