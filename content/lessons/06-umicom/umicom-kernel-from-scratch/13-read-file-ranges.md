# Read a file one bounded part at a time

Use the real Kernel console to choose a starting byte and a maximum amount of output. Learn how a request differs from what the file can actually supply.

## 1. Begin with a file you understand

Read [the console introduction](08-files-at-the-console.md) first. The optional exercise needs a prepared Kernel image and QEMU. You can calculate every example on paper without installing anything. A file is a sequence of bytes. These examples use ASCII text, where each shown character uses one byte; many other writing systems use more than one byte per character.

```text
create /notes/range.txt
write /notes/range.txt "Kernel services"
read /notes/range.txt 7 8
```

Type these at `umicom>`, not in PowerShell. `create` refuses an existing name. `write` replaces an existing file's content; use this new exercise file. The quotation marks keep the space inside one command argument and are not stored in the file.

## 2. Count skipped bytes, starting at zero

| Byte offset | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7–14 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Content | K | e | r | n | e | l | space | services |

An **offset** counts how many bytes precede your starting point. Offset 7 skips `Kernel `. The requested count 8 means “up to eight bytes,” not “finish at byte eight.”

 <svg viewbox="0 0 700 110" role="img" aria-label="The next offset is the starting offset plus the number of bytes actually read." style="width:100%;max-width:700px"><title>The next offset is the starting offset plus the number of bytes actually read.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Skip 7 bytes</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Read up to 8</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Next offset: 15</text></svg>

The next offset is the starting offset plus the number of bytes actually read.

```text
services
file.read offset=7 requested=8 read=8 next=15 eof=yes
```

**EOF** means end of file. This 15-byte file ends at offset 15. The next offset is a position after its final byte, not another character.

## 3. Ask for more than remains

```text
read /notes/range.txt 12 20
```

Offsets 12, 13 and 14 contain `ces`. Expect `read=3 next=15 eof=yes`. The command returns three real bytes; it does not pad the request with invented content.

Try `read /notes/range.txt 15 1`: it returns zero bytes with EOF. Then try `read /notes/range.txt 3 0`: it also returns zero bytes, but `eof=no`. No requested transfer and end of file are different conditions.

## 4. Understand the boundary

The command accepts decimal offsets from 0 through 131072 and a count from 0 through 4096. It rejects negative signs, overflow, trailing letters and larger counts. A count limit bounds work and terminal traffic. It is independent of the larger capacity of a RAM file. Printable output may be longer than the number of source bytes because control bytes are escaped.

A stored escape byte displays as `\x1b`. This prevents file content from controlling the terminal. A zero byte displays as `\x00`. Four printed characters still describe one stored byte. This is inspection, not a lossless file export.

## 5. Follow the implementation

1. [console_shell.c](../../../../../umicom-kernel/kernel/console_shell.c) parses exactly four tokens and checks decimal limits before admitting a range.
2. [console_file_range.inc](../../../../../umicom-kernel/kernel/console_file_range.inc) opens a read/query descriptor, checks the file kind, seeks to the offset and reads bounded chunks.
3. [vfs.c](../../../../../umicom-kernel/kernel/vfs.c) owns descriptor rights and position. The command uses those services rather than accessing file pages directly.
4. The existing close path retains a descriptor if closing fails. A displayed prefix is counted even if a later read fails; errors remain visible.

## 6. Exercise and recovery

Predict `read /notes/range.txt 0 6`. Then compare the output with `cat /notes/range.txt`. The range is `Kernel`, its next offset is 6, and EOF is no. The source stays unchanged.

If the command is unknown, check `help` and the source/image version you built. If the path is missing, use `ls /notes` and recreate only the exercise file. A directory is not a file: `read /notes 0 1` is refused. A range error is corrected by changing the request, not by increasing an internal buffer.

Continue with [Learning C: counts, offsets and progress](../../learning-c/16-counts-offsets-and-progress.md). The [regression cases](../../../../../umicom-kernel/tests/console_shell/range_cases.inc) also cover file boundaries, independent descriptors, partial failures and repeated cleanup. Hardware timing and terminal behaviour require separate runtime evidence.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/13-read-file-ranges.html) · [Learning sequence](../../../start/learning-sequence.md)
