<!--
Umicom Bits2Banking
File: content/lessons/learning-c/22-open-read-and-close-a-file.md

PURPOSE:
Explain the lesson: Open, read and close a file.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Open, read and close a file

## What you will make

You will run a small command that reads a file and prints a checksum. A file is stored data identified by a path. A stream is the C library object through which a program reads that data. A checksum is calculated from the file's bytes; it helps compare two copies.

## Prepare the tools

Use a text editor, a C23 compiler, CMake, Ninja and an installed Umicom Framework base SDK. The [checksum lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/README.md) gives separate PowerShell and Bash commands. Start in the Bits2Banking checkout, configure its checksum lab, build it, and stop if either step reports an error. Nothing in this lesson requires the Studio IDE.

## Read one lifetime

Open `main.c`. The program expects one filename after the command name. C includes the command itself in `argc`, so the required count is two. It opens the chosen file in binary read mode:

~~~c
FILE *stream = fopen(argv[1], "rb");
if (stream == NULL) {
    perror("Cannot open input file");
    return EXIT_FAILURE;
}
~~~

A pointer identifies an object; `NULL` means opening did not provide one. Never call the reader through a failed open. The letter `b` requests binary mode so Windows text translation does not change the bytes being compared.

~~~text
argument -> open -> read/check -> close -> print
              failure -> report and stop
~~~

The same function that opens the stream closes it. The checksum adapter borrows it temporarily. Closing releases the stream; the pointer must not be used afterwards.

## Lab

1. Open the lab's README in an editor and save it.
2. Run the checksum executable with that README's path, in quotes.
3. Expect one line containing 64 hexadecimal characters.
4. Run with no path. Expect a usage message and a nonzero exit code.
5. Run with a nonexistent path. Expect an open error and no checksum.
6. Add one character to a disposable copy of the README and compare both digests.

Do not edit the input while the program reads it. This reader does not freeze a filesystem snapshot.

## Troubleshooting

If a path contains spaces, quote the whole argument. A missing file is different from a missing executable: check which path the message names. If Windows shows a permissions error, choose a file you own. This exercise needs read access, not administrator access.

## Exercise and explanation

Why is the digest printed after `fclose`? Closing can itself fail. The caller waits until its complete file operation succeeds before reporting success. Framework provides the hash calculation; this small caller is responsible for the user's path and the stream lifetime.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](23-chunks-eof-and-read-errors.md)


[Previous lesson](21-follow-a-rejected-call.md)
