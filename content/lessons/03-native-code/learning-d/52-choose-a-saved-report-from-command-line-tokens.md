<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/52-choose-a-saved-report-from-command-line-tokens.md

PURPOSE:
Choose a saved report from command-line tokens

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Choose a saved report from command-line tokens

An editor can give a little tool the name of a saved report. The name might contain spaces. In this lesson, you will follow each command-line argument as a separate value and decide whether the tool has enough information to begin. You can start with four slips of paper.

## 1. Follow the argument list

D can give the entry function the signature `int main(string[] args)`. Read `string[]` as “a list of strings.” Usually the first item names the executable. The following items are the arguments the operating system handed to the program.

Place these four items on the desk.

~~~text
Position 0  review
Position 1  --limit
Position 2  2
Position 3  Example Run.jsonl
~~~

Keep the last item on one slip. It is one report name. In a terminal, quotation marks around a path with spaces help the shell pass it as one argument. The program receives the path as a single string. Compare that with C's argument count and array of pointers. D's array already carries its length.

## 2. Ask Phobos to read options

**Phobos** is the D standard library. Its `getopt` function recognizes named options and sets the values you give it. With `uint limit = 8;`, the expression `getopt(args, "limit", &limit)` sets the limit to 2. The ampersand passes the address of the variable so the library can update it. The recognized option and its value leave the list. Here the two remaining strings are the executable name and the report path.

The reader also needs the separately observed producer exit. A **producer** is the program that wrote the report. For this offline exercise, the caller supplies its recorded code as `--producer-exit 0`. Add those two tokens before the file name. Keep the report and exit observation together in your notes.

~~~d
import std.getopt : getopt;

struct Options
{
    string path;
    uint detailLimit = 8;
    int producerExit = -1;
    bool showDetails;
    bool helpWanted;
}

Options readOptions(string[] args)
{
    Options options;
    // Bind only the options this small reader handles.
    auto parsed = getopt(args, "limit", &options.detailLimit,
        "producer-exit", &options.producerExit, "details", &options.showDetails);
    options.helpWanted = parsed.helpWanted;
    if (options.helpWanted)
        return options;

    // Admit one remaining path and the separate producer evidence before reading.
    if (args.length != 2 || args[1].length == 0 ||
        options.detailLimit < 1 || options.detailLimit > 32 ||
        options.producerExit < 0 || options.producerExit > 255)
        throw new Exception("Provide one report, a limit from 1 to 32, and a producer exit from 0 to 255.");
    options.path = args[1];
    return options;
}
~~~

## 3. Predict a useful refusal

The successful paper case leaves one path, detail limit 2, and producer exit 0. Add a second path and predict what happens. Three remaining items include the executable, so the reader will stop before opening a file. If you omit `--producer-exit`, the initial value of -1 stays in place and the same admission check refuses it. Help can be requested without a report.

The optional `--details` view shows up to the selected number of steps. The reader checks every record before it shows any details. Keep the difference in mind when a Studio project gives a report path to a tool.

[D console entry point and arguments](https://dlang.org/spec/function.html#main) · [Phobos getopt](https://dlang.org/library/std/getopt/getopt.html)

[Course contents](index.md) · [Previous lesson · Admit values before exhaustive state dispatch](51-admit-values-before-exhaustive-state-dispatch.md) · [Next lesson · Count complete report lines within a byte limit](53-count-complete-report-lines-within-a-byte-limit.md) · [Related lesson · Install D and compile a first program](01-install-and-run.md) · [HTML edition](../../../courses/learning-d/lessons/52-choose-a-saved-report-from-command-line-tokens.html)
