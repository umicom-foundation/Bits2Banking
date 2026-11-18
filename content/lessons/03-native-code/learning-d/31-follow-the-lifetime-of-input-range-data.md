<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/31-follow-the-lifetime-of-input-range-data.md

PURPOSE:
Follow the lifetime of input-range data

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Follow the lifetime of input-range data

[Course contents](index.md)

## Why a line can stop meaning what you expect

A program can read one record, keep a view of its characters and then advance to the next record. If the reader reuses the same buffer, that earlier view is no longer a stable saved record. Garbage collection does not decide whether the bytes still represent the information you intended to keep. This lesson makes ownership visible in a small D file reader and connects that idea to C callbacks and Framework data import.

You will count four lines in an original ASCII fixture and keep only the first nonempty line. The code is supplied as a language exercise for a real D compiler. It uses normal D runtime and standard-library facilities. It is not BetterC, not a replacement for the native Framework importer, and not a claim that D compiled successfully in the development environment used to author the lesson.


## Prepare the file and expected results

1. Find labs/languages/native-language-boundary/line-fixture.txt. Read it without changing it.
2. Write the four records on paper: apple, an empty record, pear and plum.
3. Count three nonempty records. Add the ASCII text lengths: five plus four plus four is thirteen.
4. Write the saved record expected after the loop: apple. The final value must still be apple even though the reader visited later lines.

A record is an item chosen by the file format. Here one line is one record. A line ending separates records but is not counted as record text. A byte is a storage unit; a character is a text concept. The fixture deliberately uses ASCII so that the thirteen letters also occupy thirteen bytes. Do not transfer that counting assumption to arbitrary Unicode text.


## Read the entry point and imports

~~~d
module line_records;
import std.stdio : File, stderr, writeln;
import std.exception : enforce;

int main(string[] args)
{
    if (args.length != 2) {
        stderr.writeln("Usage: line_records path-to-small-ascii-file");
        return 2;
    }
    return inspect(args[1]);
}
~~~

module names this source unit. Selective imports bring the listed names into scope. args is a slice of argument strings; args[0] identifies the program and args[1] is the path supplied by the user. The length check occurs before indexing. A return value from main becomes a process status. The example chooses zero for success, one for a read-related failure and two for incorrect usage.


## Understand a range without memorizing its implementation

An input range represents a sequence that can be consumed in order. It offers the current item and a way to advance. D foreach can consume such a range directly. File.byLine supplies lines through this interface. Its returned row storage may be reused when the range advances. Retain an explicit copy when a row must survive that advance; use byLineCopy when independent storage is required for every line. Consult the standard-library reference for the selected compiler version.

~~~d
foreach (borrowed; input.byLine()) {
    auto row = borrowed;
    if (row.length != 0 && row[$ - 1] == '\r')
        row = row[0 .. $ - 1];
    // Inspect row during this iteration.
}
~~~

borrowed is a name chosen to remind us of the lifetime contract. auto asks the compiler to infer a type; it does not allocate a fresh string or clone data. Assigning borrowed to row copies a slice descriptor. A descriptor describes an address and a length. The two slices still refer to the same character storage. The slice expression changes the visible portion; it does not copy the bytes.


## Make the line-ending policy explicit

The example opens the file in binary mode using rb, so it handles an optional carriage return explicitly after the line-feed separator has been removed. The length test protects the final-element access. In an index or slice, $ refers to the length of that indexed array. row[$ - 1] is its last element; row[0 .. $ - 1] excludes that element. The half-open upper bound is not included.

This rule is for the small LF/CRLF ASCII fixture. It is not an arbitrary text-encoding detector, and a carriage return that is meaningful content would need a different format policy. State normalization rules before processing documents for training. Otherwise two tools may silently disagree about record contents and checksums.


## Own only the record you need to retain

~~~d
string firstNonempty;
// Inside the nonempty-record branch:
if (firstNonempty.length == 0)
    firstNonempty = row.idup;
~~~

idup makes an independent immutable copy. string is an alias for immutable character data accessed through a slice. The program retains only the first nonempty record, so it pays for one intentional copy instead of storing all lines. Later reader activity cannot overwrite that saved value through the reusable input buffer. This is a semantic ownership decision, not merely a performance trick.

Replacing row.idup with a cast to an immutable string would not establish independent storage. A cast changes what the compiler is told; it does not make a new allocation or remove an existing mutable alias. The earlier lessons on const views and immutable copies explain that difference. Prefer an explicit copy when the required contract is ownership of stable data.


## Keep acceptance limits honest

~~~d
enforce(lineCount < 16 && row.length <= 128,
        "Teaching record limit exceeded");
++lineCount;
textBytes += row.length;
~~~

enforce checks a runtime condition and raises an exception when it is false. The limit allows at most sixteen accepted records, each at most 128 bytes after the stated line-ending adjustment. size_t is the unsigned type used for lengths and counts. The accepted total is at most 2048 bytes, so these particular counters have a small explicit bound.

The reader has already obtained the line before this condition runs. It may have allocated enough memory for a much larger line. Consequently, this is a limit on accepted content, not a pre-allocation ceiling or a proof that the process cannot run out of memory. Streamed iteration and bounded input are separate properties. Production importers need bounded reads and clearly defined oversized-record behavior. Keep this demonstration on the tiny supplied fixture.


## Separate the main error from cleanup

The inspect function keeps an opened flag and a result status. Opening and reading occur inside try. A catch(Exception error) block reports a recoverable exception and sets a failure status. After that block finishes, the code explicitly closes an opened file in a separate try/catch. A close failure is reported without pretending that an earlier read succeeded.

~~~d
if (opened) {
    try { input.close(); }
    catch (Exception error) {
        stderr.writeln("Close failure: ", error.msg);
        result = 1;
    }
}
~~~

This structure does not throw a second cleanup exception while another exception is unwinding. It also keeps all success printing after cleanup. The program does not catch every possible fatal runtime error: recoverable Exception handling is not a promise to survive memory exhaustion or corrupted process state. A file resource and a garbage-collected array have different lifetimes; one must not be used as an excuse to ignore the other.


## Compile and run the original exercise

1. Open a shell in the native-language-boundary lab directory. Confirm that dmd identifies the D compiler you installed.
2. Compile line_records.d to an executable. Stop if compilation fails; do not run a previously built executable and call that a check of the new source.
3. Run with line-fixture.txt and inspect the process status.
4. Run with a deliberately nonexistent path and inspect the error and nonzero status.
5. If you use LDC or GDC, use that compiler’s documented output and runtime options. Do not assume an unrelated command with the same short name is a D compiler.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary
dmd -g -of=line-records-d.exe line_records.d
& ".\line-records-d.exe" ".\line-fixture.txt"
$LASTEXITCODE
& ".\line-records-d.exe" ".\missing-fixture.txt"
$LASTEXITCODE
~~~

The supplied fixture should produce Lines=4 Nonempty=3 Text bytes=13 followed by First nonempty=apple, with status zero. On Linux, choose an executable name without the Windows suffix if preferred and invoke it with ./line_records. No compiler or runtime pass is implied by these expected values; record the version and actual result when you execute the exercise.


## Transfer the idea across the C boundary

A Framework callback can receive a pointer and a length that remain valid only during the callback. Saving that pointer for later does not transfer ownership. The same reasoning used for borrowed D rows applies: either finish processing while the view is valid or copy into storage whose lifetime the receiver owns. A garbage collector cannot extend the lifetime of a C allocation owned and freed by another component.

Keep reusable import, validation and model-training behavior in the native Framework service. D can be a teaching client or an explicitly justified integration boundary, using a verified C ABI. Do not expose a D slice descriptor or managed string as if it were automatically a portable C structure. The previous interoperability lessons cover scalar widths, pointer-plus-count interfaces and release responsibilities.


## Try boundary cases

1. Read an empty fixture and a fixture containing one blank line. Explain why the counters differ.
2. Read a CRLF copy and compare its accepted text-byte count with the LF copy under this lesson’s normalization rule.
3. Try a small seventeen-line copy and inspect the limit failure. Explain why the loop is streaming but the input policy is still checked after each read.
4. Explain why retaining the first line requires a copy but counting it during the loop does not.
5. Design an interface comment for a C callback that lends a byte span only until return. Include whether the receiver may retain the pointer and who releases copied storage.


## Further reading

- [Original D reader](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/line_records.d)
- [D std.stdio reference](https://dlang.org/phobos/std_stdio.html)
- [Shared small fixture](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/line-fixture.txt)

[Previous: State the effects of a binary reader](30-state-the-effects-of-a-binary-reader.md)
<!-- The initial exercise commands shared line_records.exe across two languages. Distinct output names below prevent accidental cross-language executable reuse. Earlier output name: line_records.exe. -->

[Next: Publish results deliberately with ref and out](32-publish-results-with-ref-and-out.md)
