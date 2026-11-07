<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/03-numbers-files-and-checks.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Numbers, file writes and useful checks

[Course contents](index.md) · [Previous: Overlapping memory and ownership](02-overlap-and-ownership.md)

## Safety includes the edges of a program
An editor can have a bounded text buffer and still mishandle a huge numeric command or overwrite a file unexpectedly. This lesson follows two boundaries: text-to-number conversion and saving work.

## Prepare
Build the text-editor lab with [the course commands](index.md). Open main.c, editor.c and check_session.cmake. Use a new practice directory for each save exercise.

## Parse a position without overflowing
The terminal command insert expects a non-negative byte position. ReadIndex accepts digits and checks before multiplying the accumulated result by ten:
~~~c
if (result > (SIZE_MAX - digit) / 10U) return 0;
result = result * 10U + digit;
~~~
SIZE_MAX is the largest value representable by size_t, the unsigned type used for sizes. The check establishes that the next arithmetic step fits. Checking only after overflowing would be too late.

A minus sign is rejected. A valid number still needs a separate document-position check. The text 900 may be a valid number while being outside a three-byte document.

## Save to an explicit path
The save command passes the path chosen by the user to BtbEditorSaveNew. The model opens it with wbx: binary writing with exclusive creation. If a file already exists, this operation must fail rather than replace it.

The function checks the write count, flushing and closing. A successful open alone does not prove that all bytes reached the destination. The dirty flag is cleared only when the operation reports success.

## Know the limit
If writing fails after creation, a partial new file may remain. Inspect it before retrying with another path. This teaching implementation does not promise atomic replacement or recovery after power loss. Production code needs the Framework persistence facilities and a documented recovery policy.

## Try a controlled failure
1. Append abc and save to a new path.
2. Start another session and append different text.
3. Attempt to save to the same path.
4. Expect an error.
5. Open the original file and confirm that it still contains abc.

The process check automates this scenario in its own unique directory. It also rejects a negative erase position. The test retains its files to help investigate failures.

## Exercise and answer
Why must an error leave the document dirty? Because the user still needs to save or explicitly discard the current work. A failed write must not pretend that the new document has been preserved.

## A review checklist you can explain
Check ranges before arithmetic, preserve state on rejected operations, document who owns input buffers, and test successful as well as failing paths. Compiler warnings, sanitizers and static analysis can add evidence where supported. None replaces understanding the code or proves the absence of all defects.

## Connect to Umicom
Compare the lab's explicit-path save with Framework document and storage services. Use the shared production service when extending an application; keep this small implementation as an educational model.

## Read a whole command before acting
A line can be longer than the buffer that receives it. A zero byte can also appear in redirected input even though ordinary typing does not produce it. If a reader uses only strlen, it stops counting at that zero and may accidentally accept a command prefix.

ReadCommand in main.c counts bytes with getchar. It marks an oversized line or a zero byte invalid and consumes the rest of the line. Only a complete accepted line reaches the command dispatcher. Draining the rejected line prevents its tail from becoming a second command.

For a trace, imagine a buffer with room for seven input bytes and a terminator. The line append abc has ten bytes. The reader must refuse the entire line rather than execute append a. The real program uses a larger command buffer, but the rule is identical. check_session.cmake checks a 2200-character command followed by a valid save; the saved file must retain its earlier text.

## Source map
Read `labs/native/text-editor/main.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Overlapping memory and ownership](02-overlap-and-ownership.md)

[Continue: Define a failure boundary for a borrowed stream](04-borrowed-streams-and-failure-boundaries.md)
