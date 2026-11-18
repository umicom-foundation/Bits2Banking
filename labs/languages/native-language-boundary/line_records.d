/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/line_records.d
 *
 * PURPOSE:
 *   Teach reusable line-range storage, explicit retained copies and file error handling.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module line_records;
import std.stdio : File, stderr, writeln;
import std.exception : enforce;

/* A line can allocate before its length is inspected. The limits below bound
 * accepted records, not peak process memory. Use only small teaching fixtures. */
int inspect(string filename)
{
    File input;
    bool opened = false;
    int result = 0;
    size_t lineCount = 0, nonemptyCount = 0, textBytes = 0;
    string firstNonempty;
    try {
        input.open(filename, "rb");
        opened = true;
        foreach (borrowed; input.byLine()) {
            // In binary mode a CRLF record retains CR after the LF separator.
            auto row = borrowed;
            if (row.length != 0 && row[$ - 1] == '\r') row = row[0 .. $ - 1];
            enforce(lineCount < 16 && row.length <= 128, "Teaching record limit exceeded");
            ++lineCount;
            textBytes += row.length;
            if (row.length != 0) {
                ++nonemptyCount;
                // byLine may reuse its buffer on the next iteration. Own the
                // one record retained here; do not collect borrowed slices.
                if (firstNonempty.length == 0) firstNonempty = row.idup;
            }
        }
    } catch (Exception error) {
        stderr.writeln("Read/open/limit failure: ", error.msg);
        result = 1;
    }
    // Keep close failure separate from a prior error; do not throw from cleanup
    // while another exception is unwinding. No borrowed row is used here.
    if (opened) {
        try { input.close(); }
        catch (Exception error) {
            stderr.writeln("Close failure: ", error.msg);
            result = 1;
        }
    }
    if (result == 0) {
        writeln("Lines=", lineCount, " Nonempty=", nonemptyCount, " Text bytes=", textBytes);
        writeln("First nonempty=", firstNonempty);
    }
    return result;
}
int main(string[] args)
{
    if (args.length != 2) {
        stderr.writeln("Usage: line_records path-to-small-ascii-file");
        return 2;
    }
    return inspect(args[1]);
}
