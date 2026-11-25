<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/54-read-a-versioned-field-after-checking-its-type.md

PURPOSE:
Read a versioned field after checking its type

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read a versioned field after checking its type

A complete line can still hold the wrong kind of value. JSON can store a number, a string such as `"1"`, or a Boolean such as `true`. In this exercise, you will check the kind before letting a value into the reader's small D record.

## 1. Meet the practice report

These records are the saved synthetic output of the Umicom C console exercise that watches slot zero. The four `step` records describe completed source steps. The fifth record gives the value returned by the practice program. The stored C fixture produced these records in both of its checked compiler lanes. This exercise concerns a D reader for those saved bytes.

~~~json
{"schema":1,"event":"step","number":1,"stepKind":"statement","firstLine":2,"firstColumn":3,"endLine":2,"endColumn":13,"instructions":2,"ok":true}
{"schema":1,"event":"step","number":2,"stepKind":"statement","firstLine":3,"firstColumn":3,"endLine":3,"endColumn":9,"instructions":2,"ok":true}
{"schema":1,"event":"step","number":3,"stepKind":"statement","firstLine":4,"firstColumn":3,"endLine":4,"endColumn":11,"instructions":4,"ok":true}
{"schema":1,"event":"step","number":4,"stepKind":"return","firstLine":5,"firstColumn":3,"endLine":5,"endColumn":12,"instructions":2,"ok":true}
{"schema":1,"event":"result","value":42,"instructions":10}
~~~

Look first at `schema`. A schema is the agreed set of fields and their meanings. All five records give it the number 1. Change a copy to `"schema":"1"` and circle the quotation marks. The string and the number have different types, so the reader will refuse the copy. A missing `schema` field also produces a refusal.

## 2. Keep the checked fields

The following helper reads one bounded line from the preceding lesson. It uses `JSONType` to inspect the values produced by `parseJSON`. Each step has a number, kind, instruction count and Boolean outcome. Each result has a signed return value and a total instruction count. Other fields in the saved report, such as source positions, remain available for a later reader that needs them.

~~~d
import std.json : JSONType, JSONValue, parseJSON;

struct ReportRecord
{
    string event;
    long number;
    string stepKind;
    long instructions;
    bool ok;
    long value;
}

JSONValue reportField(JSONValue node, string key)
{
    // Look up a present key before reading its value.
    auto fields = node.object;
    auto found = key in fields;
    if (found is null)
        throw new Exception("Missing field: " ~ key);
    return *found;
}

long reportInteger(JSONValue field)
{
    // Admit integers representable by the signed type the reader uses.
    if (field.type == JSONType.integer)
        return field.integer;
    if (field.type == JSONType.uinteger && field.uinteger <= cast(ulong) long.max)
        return cast(long) field.uinteger;
    throw new Exception("Expected a signed-range integer.");
}

string reportString(JSONValue field)
{
    // Read the string accessor only after checking the value kind.
    if (field.type != JSONType.string)
        throw new Exception("Expected a string.");
    return field.str;
}

ReportRecord decodeRecord(string line)
{
    auto node = parseJSON(line);
    if (node.type != JSONType.object || reportInteger(reportField(node, "schema")) != 1)
        throw new Exception("Expected a version 1 report object.");

    ReportRecord record;
    record.event = reportString(reportField(node, "event"));
    record.instructions = reportInteger(reportField(node, "instructions"));
    if (record.instructions < 0 || record.instructions > 1000000)
        throw new Exception("Instructions outside the practice range.");

    // Keep the required fields for the selected event.
    if (record.event == "step")
    {
        record.number = reportInteger(reportField(node, "number"));
        record.stepKind = reportString(reportField(node, "stepKind"));
        auto outcome = reportField(node, "ok");
        if (record.number < 1 || record.number > 32 ||
            (record.stepKind != "statement" && record.stepKind != "condition" &&
             record.stepKind != "iteration" && record.stepKind != "return") ||
            (outcome.type != JSONType.true_ && outcome.type != JSONType.false_))
            throw new Exception("Unexpected step fields.");
        record.ok = outcome.boolean;
    }
    else if (record.event == "result")
        record.value = reportInteger(reportField(node, "value"));
    else
        throw new Exception("Unknown report event.");
    return record;
}
~~~

## 3. Compare three small changes

The first saved line gives a `step` with number 1, kind `statement`, 2 instructions, and a true outcome. The last line gives a `result` with value 42 and 10 instructions. A step with `"ok":"true"` now refuses because the word in quotation marks is a string. A step with an event name your reader has never seen also refuses. Keep each modified line separate so you can say which rule caught it.

The next lesson checks how several records become one complete preview.

[Phobos parseJSON](https://dlang.org/library/std/json/parse_json.html) · [D JSONValue fields](https://dlang.org/library/std/json/json_value.html) · [D JSONType values](https://dlang.org/library/std/json/json_type.html)

[Course contents](index.md) · [Previous lesson · Count complete report lines within a byte limit](53-count-complete-report-lines-within-a-byte-limit.md) · [Next lesson · Keep the previous preview when a new record fails](55-keep-the-previous-preview-when-a-record-fails.md) · [Related lesson · Read versioned interpreter reports](../../05-engineering/building-a-compiler-in-c/96-read-versioned-interpreter-reports.md) · [Related lesson · Admit values before exhaustive state dispatch](51-admit-values-before-exhaustive-state-dispatch.md) · [HTML edition](../../../courses/learning-d/lessons/54-read-a-versioned-field-after-checking-its-type.html)
