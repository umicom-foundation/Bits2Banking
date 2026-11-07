<!--
Umicom Bits2Banking
File: content/lessons/learning-c/23-chunks-eof-and-read-errors.md

PURPOSE:
Explain the lesson: Read a file in bounded chunks.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a file in bounded chunks

## The idea

A large file need not fit into one large memory allocation. Read a piece, process it, and reuse the same buffer for the next piece. The buffer in this lab holds 4,096 bytes. A byte is a unit of storage; the returned count says how many bytes were actually obtained.

## Setup recap

Prepare the checksum project using its [PowerShell or Bash guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/README.md). You need a C23 compiler and the installed Framework base SDK. Open `checksum.c` before running the tests. The test program creates temporary files, so it needs a writable temporary directory.

## Follow the loop

~~~c
const size_t count = fread(buffer, 1, sizeof buffer, stream);
~~~

`sizeof buffer` is its capacity. The element size is one, so `count` is a byte count. Only those bytes are passed to Framework. Using the full capacity on a short final read would include unrelated old bytes.

~~~text
file size 4097
read 1: count 4096 -> process 4096 bytes
read 2: count    1 -> process    1 byte
end of file       -> finish digest
~~~

A short read and an error are different observations. `ferror` checks the error indicator; `feof` checks the end-of-file indicator. The adapter checks errors before publishing a digest. If a read makes no progress without reporting end-of-file, it refuses the operation instead of spinning forever.

For an exact 4,096-byte file, the first read can fill the whole buffer without setting EOF. A later read discovers the end. That extra read is normal.

## Lab

1. Draw a table of reads for lengths 0, 1, 4095, 4096 and 4097.
2. Locate those boundary lengths in `test_checksum.c`.
3. Run the registered checks using the lab guide.
4. Compare the README digest with the operating system's SHA-256 utility.
5. In a separate exercise copy, reduce the buffer capacity to 7, rebuild, and compare the same input again.

The checksum should stay the same because the byte sequence stayed the same. Record actual results rather than assuming the exercise succeeded.

## Common mistakes

Do not use `while (!feof(stream))` as evidence that the next read will succeed: EOF is discovered by reading. Do not use `strlen` on arbitrary file bytes; a zero byte can appear inside a binary file. Do not call a function on a closed stream to manufacture a read error; that is invalid use, not a useful test.

## Exercise and explanation

Does a failed read guarantee that the stream position is unchanged? No. Some input may have been consumed. This adapter preserves the output buffer on failure, but it cannot undo earlier reads.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/checksum.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](22-open-read-and-close-a-file.md) · [Next lesson](24-status-values-and-complete-results.md)

