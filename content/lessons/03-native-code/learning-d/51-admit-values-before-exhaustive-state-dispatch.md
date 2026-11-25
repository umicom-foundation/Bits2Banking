<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/51-admit-values-before-exhaustive-state-dispatch.md

PURPOSE:
Admit values before exhaustive state dispatch

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Admit values before exhaustive state dispatch

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `exhaustive_states.d` in `labs/languages/native-language-boundary` in the course checkout. Choose a valid state number and a byte with no named state. Trace what validates the byte before the exhaustive switch sees it.

## A named state describes one fact

Imagine a launcher with four observations: a request is queued, a process has been created, an application has acknowledged readiness, or startup has failed. These observations are different. A process can exist before its first window appears. A useful program keeps those facts separate instead of showing success too early. This laboratory models the distinctions with values only; it does not start a process or implement an application readiness protocol.

1. Open labs/languages/native-language-boundary/exhaustive_states.d. Review the earlier enum, function, ref parameter and unittest lessons.
2. Write four cards on paper: queued, created, ready and failed. Put created before ready.
3. Consider a program that starts but never displays a window. It has evidence for created, but you must not silently promote it to ready.


## Give states explicit names and numbers

enum declares a named type with named members. LaunchState is the type name, uint is its unsigned 32-bit base type, and each assignment gives a member an explicit number. These numbers are a tiny invented protocol for the exercise. A protocol is an agreed representation exchanged between components. The gaps leave room for future decisions; they do not prove an unknown number is safe.

~~~d
enum LaunchState : uint { queued = 10, created = 20, ready = 30, failed = 40 }
~~~


## Separate representation from meaning


| Received number | Accepted state | Meaning in this exercise |
| --- | --- | --- |
| 10 | queued | The request is waiting |
| 20 | created | A process exists; readiness is not established |
| 30 | ready | A separate readiness acknowledgement exists |
| 40 | failed | The attempted startup failed |
| 0, 11 or any other number | Refused | Keep the previous accepted output |


## Decode external values with an ordinary switch

tryDecodeState receives a raw number and a reference to the caller’s output. candidate is local temporary storage. Each recognized number assigns it and uses break to leave the switch. default returns false before publication. Only accepted values reach output = candidate. This lets the caller distinguish refusal from a successful new value without overwriting the old state.

~~~d
bool tryDecodeState(uint raw, ref LaunchState output) @safe pure nothrow @nogc
{
    LaunchState candidate;
    switch (raw) {
        case 10: candidate = LaunchState.queued; break;
        case 20: candidate = LaunchState.created; break;
        case 30: candidate = LaunchState.ready; break;
        case 40: candidate = LaunchState.failed; break;
        default: return false;
    }
    output = candidate;
    return true;
}


~~~


## Read the function promises


| Declaration | Meaning here |
| --- | --- |
| bool | The result reports acceptance or refusal |
| uint raw | The function receives a copy of the external number |
| ref LaunchState output | Success may update the caller’s variable |
| @safe | The compiler applies D memory-safety restrictions |
| pure | The function has no unrestricted global side effects; a ref output can still change |
| nothrow | The function does not throw an Exception |
| @nogc | The function cannot require D garbage-collector allocation |


## Trace one refused update

1. The caller initializes current to LaunchState.ready. That is an explicit value, not an assumption about the enum’s default.
2. The caller supplies raw value 11. None of the recognized numeric cases matches.
3. default returns false. The assignment to output is never reached.
4. The test checks both facts: the result is false and current still equals ready.
5. A real user interface should also indicate the refusal. Retaining old data is not permission to present it as a fresh response.


## Map admitted states exhaustively

A final switch has no default branch and requires every member of a named enum to appear. It also excludes case ranges and runtime case expressions. Our mapping returns a different string for each observation. Adding a new member therefore requires a deliberate mapping decision. This is a compile-time completeness check, not validation of arbitrary external integers.

~~~d
string labelFor(LaunchState state) @safe pure nothrow @nogc
{
    final switch (state) {
        case LaunchState.queued: return "request queued";
        case LaunchState.created: return "process created; readiness unknown";
        case LaunchState.ready: return "application readiness acknowledged";
        case LaunchState.failed: return "startup failed";
    }
}

~~~


## Why an unchecked cast is insufficient

D permits an explicit cast from a base integer to an enum. That operation is not the admission function above. Do not use cast(LaunchState)raw as proof that a network message or file contains a recognized state. An exhaustive mapping is useful after admission. Unknown values need a checked boundary and a clear error path before the mapping is called.

~~~d
// Do not replace input validation with this cast:
// auto state = cast(LaunchState)raw;

LaunchState accepted = LaunchState.queued;
if (tryDecodeState(20, accepted)) {
    // It is now appropriate to call labelFor(accepted).
}
~~~


## Use reflection to enumerate a test domain

EnumMembers is a library template that exposes the enum’s named members. static foreach expands the enclosed test statements at compile time for each member. The assertions still execute when the test program runs. They check decoding and a nonempty label for every declared member. Reflection helps enumerate cases; it does not invent a correct meaning for a new state.

~~~d
unittest {
    LaunchState current = LaunchState.ready;
    assert(!tryDecodeState(0, current) && current == LaunchState.ready);
    assert(!tryDecodeState(11, current) && current == LaunchState.ready);
    assert(!tryDecodeState(uint.max, current) && current == LaunchState.ready);
    static foreach (member; EnumMembers!LaunchState) {
        assert(tryDecodeState(cast(uint)member, current));
        assert(current == member);
        assert(labelFor(current).length != 0);
    }
    assert(labelFor(LaunchState.created) != labelFor(LaunchState.ready));
}

~~~


## Keep three checks distinct


| Check | What it detects | What it cannot establish |
| --- | --- | --- |
| final switch completeness | A declared enum member lacks a case | Whether the chosen label is truthful |
| Decoder refusal tests | Unknown numbers are admitted or corrupt prior output | Whether every external message is authentic |
| created differs from ready assertion | Two important observations become the same label | Whether a real application created a usable window |


## Compile the standalone teaching program

Use the D compiler selected in the setup lesson. The following DMD command enables unittest blocks and warnings. The sample remains uncompiled in the current mirror environment. Stop on a compiler error before running the executable; avoid -release while learning because assertions are part of this exercise.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary
dmd -unittest -w -ofexhaustive_states.exe exhaustive_states.d
.\exhaustive_states.exe
~~~


## Understand the expected output

main decodes the invented number 20 and prints its label. It never starts another program. The unittest blocks are normally quiet on success; a failed assertion interrupts the run. This expected text therefore demonstrates the value mapping only.

~~~text
Umicom D state example: process created; readiness unknown
~~~


## Try an intentional completeness failure

1. Add cancelled = 50 to LaunchState and compile without editing labelFor. The compiler should report the missing enum case.
2. Add a case for cancelled with a suitable label. Then review the decoder: do you intend to accept protocol value 50? Add that decision explicitly.
3. The reflective test now visits cancelled and will expose a decoder that still refuses its value. Run with -unittest to exercise the assertions.
4. Add a refusal test for 51. Verify both a false result and preservation of the previous accepted output.
5. Do not add default to final switch merely to silence a missing-case error. Use ordinary switch for open-ended external input and final switch for an intentionally closed internal mapping.


## Apply the boundary in Umicom projects

The primary Framework services remain C23. A D teaching client can decode its own explicit wire representation and call a reviewed C interface. Match the interface’s actual integer widths and documented status codes; these four invented values are not Framework ABI constants. In an asynchronous workflow, track request acceptance, native creation, readiness and failure from their respective evidence sources. Exhaustive syntax cannot supply an observation that the program never collected.


## Recovery and further exploration

1. If dmd is not recognized, check the earlier setup and compiler PATH instructions. Do not substitute the Umicom C compiler and claim it supports complete D compilation.
2. If a ref argument is rejected, supply a mutable variable rather than an immutable value or a temporary expression.
3. If an @nogc diagnostic appears after an edit, inspect the operation you added. Building a new dynamic string differs from returning an existing string literal.
4. Keep a small table of external numeric values beside your decoder and review changes to it as protocol changes, independently of source enum ordering.


## Language references


- [D language reference: final switch](https://dlang.org/spec/statement.html#FinalSwitchStatement)
- [D language reference: named enums and conversions](https://dlang.org/spec/enum.html)


[Previous: Follow comment and string boundaries](50-follow-comment-and-string-boundaries.md)

[Next lesson · Choose a saved report from command-line tokens](52-choose-a-saved-report-from-command-line-tokens.md)
