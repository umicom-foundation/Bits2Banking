<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/53-count-complete-report-lines-within-a-byte-limit.md

PURPOSE:
Count complete report lines within a byte limit

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Count complete report lines within a byte limit

A file contains bytes. A line in a saved report has an ending you can recognize. This lesson takes a small array of bytes and returns a list of complete lines. It gives the reader a firm place to stop before it starts interpreting the fields.

## Prepare

Draw one box for each byte on a strip of paper. Give the line ending its own box or pair of boxes. Use the small text examples below to count bytes and mark where the reader must stop.

## 1. Write down the three limits

Our practice reader accepts at most 4,096 file bytes, 256 bytes in a line before its ending, and 32 lines. Its fixtures use plain ASCII, the familiar byte codes for characters such as digits and braces. They use line feed, written `\n`, or carriage return followed by line feed, written `\r\n`. Both endings separate one record from the next. The local exercise requires a final line feed so you can recognize the last boundary.

When the completed reader opens a practice file, it will ask `std.file.read` for up to 4,097 bytes. A length of 4,097 is enough to detect an input above the cap. The example below works with an already supplied array to let you trace it on paper.

## 2. Count bytes, then keep each line

An **offset** is the number of bytes from the start of the array. `start` holds the offset of the current line. When the loop reaches a line feed, it finds the end of the record and copies the bytes between the two offsets. The slice includes its first offset and stops before its last. `.idup` makes a separate immutable copy.

~~~d
enum size_t reportByteLimit = 4096;
enum size_t reportLineLimit = 256;
enum size_t reportRecordLimit = 32;

string[] frameReport(const(void)[] raw)
{
    const bytes = cast(const(ubyte)[]) raw;
    // Check the file boundary before looking at its final byte.
    if (bytes.length == 0 || bytes.length > reportByteLimit || bytes[$ - 1] != '\n')
        throw new Exception("Expected a bounded report ending in a line feed.");

    string[] lines;
    size_t start = 0;
    foreach (offset, byteValue; bytes)
    {
        // Only LF and CRLF end lines in these ASCII practice reports.
        if (byteValue == '\r')
        {
            if (offset + 1 >= bytes.length || bytes[offset + 1] != '\n')
                throw new Exception("Expected a line feed after carriage return.");
        }
        else if (byteValue == '\n')
        {
            size_t end = offset;
            if (end > start && bytes[end - 1] == '\r')
                --end;
            if (end == start || end - start > reportLineLimit ||
                lines.length == reportRecordLimit)
                throw new Exception("Blank line or report limit exceeded.");
            // Retain an owned line so later parsing can read it independently.
            auto text = cast(const(char)[]) bytes[start .. end];
            lines ~= text.idup;
            start = offset + 1;
        }
        else if (byteValue != '\t' && (byteValue < 0x20 || byteValue > 0x7E))
            throw new Exception("Expected ASCII report text.");
    }
    return lines;
}
~~~

## 3. Test the boundaries on paper

Take the two lines `{"schema":1}` and `{"schema":1}`. Each has twelve bytes before its ending.

| Change | Expected result |
| --- | --- |
| Add LF after each line | 26 input bytes and two returned lines, each twelve bytes |
| Use CRLF after each line | 28 input bytes and the same two returned lines |
| Remove the last LF | Refuse the unfinished final record |
| Add a blank line between records | Refuse the empty record |

These are framing examples. The next exercise decides whether the fields in a complete line describe an accepted event. Keep the same input caps when those checks are added.

[D arrays and slices](https://dlang.org/spec/arrays.html) · [Phobos bounded file read](https://dlang.org/library/std/file/read.html)

[Course contents](index.md) · [Previous lesson · Choose a saved report from command-line tokens](52-choose-a-saved-report-from-command-line-tokens.md) · [Next lesson · Read a versioned field after checking its type](54-read-a-versioned-field-after-checking-its-type.md) · [Related lesson · Follow the lifetime of input-range data](31-follow-the-lifetime-of-input-range-data.md) · [Related lesson · Separate text bytes, code points and display](39-separate-text-bytes-code-points-and-display.md) · [HTML edition](../../../courses/learning-d/lessons/53-count-complete-report-lines-within-a-byte-limit.html)
