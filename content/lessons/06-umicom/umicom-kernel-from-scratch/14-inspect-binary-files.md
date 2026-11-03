# Inspect file bytes in hexadecimal

A file can contain text, an executable program or bytes that have no printable character. The Kernel console can show those bytes without asking a terminal to interpret them.

## What a byte view tells us

A **byte** is a small stored value. Here it has eight binary digits, called bits, and can represent a whole number from 0 to 255. Text gives some values a character meaning. An executable gives bytes a different meaning. Looking at a file does not run it.

 <svg viewbox="0 0 700 110" role="img" aria-label="The same checked reader supplies text and byte views. Only presentation changes." style="width:100%;max-width:700px"><title>The same checked reader supplies text and byte views. Only presentation changes.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">File bytes</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Checked VFS read</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Hexadecimal rows</text></svg>

The same checked reader supplies text and byte views. Only presentation changes.

## 1. Prepare a small file

Use the prepared console image described in [the console lesson](08-files-at-the-console.md). The following are guest console commands, not PowerShell commands. Choose a fresh path; `write` replaces existing contents.

```text
create /notes/bytes.txt
write /notes/bytes.txt "AB"
stat /notes/bytes.txt
hex /notes/bytes.txt 0 2
```

The byte row begins with `00000000  41 42` and ends with `|AB|`. The final line is:

```text
file.hex offset=0 requested=2 read=2 next=2 eof=yes
```

`41` and `42` are hexadecimal representations of decimal 65 and 66. Those byte values represent A and B in ASCII, a character encoding. The offset on the left is hexadecimal. The command arguments and summary values are decimal. Offset zero means the first byte, not an empty file.

## 2. Read one byte, then the end

```text
hex /notes/bytes.txt 1 1
hex /notes/bytes.txt 2 1
```

The first request shows offset `00000001`, byte `42` and character B. The second prints no byte row and reports `read=0 next=2 eof=yes`. Reaching the end is not a read error.

## 3. Understand the columns

| Column | Meaning |
| --- | --- |
| Eight digits at the left | The position of this row's first byte in the file. |
| Pairs of digits | Up to sixteen bytes, in file order. Padding leaves missing positions blank. |
| Between vertical bars | Printable ASCII characters. A dot replaces every other byte value. |

A dot in this view does not mean the file contains a dot. It may represent a zero byte, a control byte, or part of a non-ASCII encoding. Use the hexadecimal pairs to know the exact values.

## 4. Follow real Kernel code

Open `umicom-kernel/kernel/console_file_range.inc`. `UmicomShellInspectRange` opens a descriptor with read and query rights, checks that the object is a file, seeks to the requested offset, and reads bounded chunks. `UmicomShellHexRow` turns a row into printable characters. It does not read the disk or allocate pages.

Short reads can split a row. A sixteen-byte row buffer keeps its partial contents until enough bytes arrive, the requested range ends, or a read fails. A real prefix from a failed read is shown and counted before the error is reported. There is no hidden retry.

## 5. Try a refused request

```text
hex /notes/bytes.txt 0 4097
```

The console refuses this request: the maximum is 4096 source bytes per command. Choose another bounded range after a successful command if the file is longer. A negative offset, a malformed number or a missing path is not repaired by guessing.

## Check your understanding

1. Why does the second command in step 2 produce no row?
2. Does a dot in the character column prove the original byte was 46?
3. If a request for 35 bytes reads 3 before an error, what should `read` and `next` show when the starting offset is 10?

<details>

<summary>Worked answers</summary>

The file contains only two bytes, at offsets 0 and 1. Offset 2 is its end. A dot can be a replacement, so inspect the pair: decimal 46 is hexadecimal 2e. The partial result must report read=3 and next=13, together with the error. It must not claim 35 bytes were read.

</details>

Continue with [the C lesson on bits and hexadecimal](../../learning-c/17-bits-and-hexadecimal.md). The automated checks in `umicom-kernel/tests/console_shell/hex_cases.inc` cover every possible byte value and preserve the source file.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/14-inspect-binary-files.html) · [Learning sequence](../../../start/learning-sequence.md)
