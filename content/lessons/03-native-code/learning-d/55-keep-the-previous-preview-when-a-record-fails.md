<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/55-keep-the-previous-preview-when-a-record-fails.md

PURPOSE:
Keep the previous preview when a new record fails

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep the previous preview when a new record fails

A preview already shows a completed report with the value 42. You open another saved report. Its first two records decode and the third ends halfway through a JSON field. Practise reporting the third line while keeping the earlier preview available.

## Prepare

Draw two boxes on paper. Label the first box Saved preview and write 42 in it. Label the second box Candidate and leave it empty for the records that pass before the refusal.

## Decode into a local array

The framing function has already split the input into individual lines. Each line can still contain malformed JSON. Build a local array from the lines. The caller receives that array only when the whole decoding loop finishes.

~~~d
import std.conv : to;

ReportRecord[] decodeReport(string[] lines)
{
    // Publish the array only after every line has decoded.
    ReportRecord[] candidate;
    foreach (offset, line; lines)
    {
        try
        {
            candidate ~= decodeRecord(line);
        }
        catch (Exception problem)
        {
            // Convert the zero-based array offset to a report line number.
            throw new Exception("Line " ~ to!string(offset + 1)
                ~ ": " ~ problem.msg);
        }
    }
    return candidate;
}
~~~

The operator `~=` appends one decoded record. The `catch` block adds the report line number to the original message and passes the failure to the caller. Phobos documents `JSONException` for malformed JSON and `ConvException` for input numbers outside the parser's native types. A quoted schema such as `"1"` can parse successfully and still fail the field check in `decodeRecord`. [D try statements](https://dlang.org/spec/statement.html#try-statement) · [Phobos JSON parsing](https://dlang.org/library/std/json/parse_json.html)

## Trace a refusal

Treat the following as three newline-terminated records in a practice file. The newline after the third record completes the frame. The JSON on that line is incomplete.

~~~json
{"schema":1,"event":"step","number":1,"stepKind":"statement","firstLine":2,"firstColumn":3,"endLine":2,"endColumn":13,"instructions":2,"ok":true}
{"schema":1,"event":"step","number":2,"stepKind":"statement","firstLine":3,"firstColumn":3,"endLine":3,"endColumn":9,"instructions":2,"ok":true}
{"schema":1,"event":
~~~

1. Line 1 gives the candidate one record.
2. Line 2 gives the candidate two records.
3. At line 3, the caller receives an exception whose message starts with `Line 3:`. Keep the earlier preview showing 42 and publish no summary for this attempted report.

On paper, replace the third line with `{"schema":1,"event":"result","value":42,"instructions":4}`. Decoding now produces three typed records. Pass them to the next lesson's checks before replacing the preview. In a saved report, the caller uses both the decoded records and the separately recorded producer exit status.

[Course contents](index.md) · [Previous lesson · Read a versioned field after checking its type](54-read-a-versioned-field-after-checking-its-type.md) · [Next lesson · Match a final result with its producer status](56-match-a-final-result-with-its-producer-status.md) · [Related lesson · Trace an exception partway through a batch](10-trace-an-exception-partway-through-a-batch.md) · [HTML edition](../../../courses/learning-d/lessons/55-keep-the-previous-preview-when-a-record-fails.html)
