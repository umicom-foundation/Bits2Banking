<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/33-admit-enumerated-states-before-dispatch.md

PURPOSE:
Admit enumerated states before exhaustive dispatch

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Admit enumerated states before exhaustive dispatch

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `explicit_job_states.d` in `labs/languages/native-language-boundary` in the course checkout. Find a byte that represents a job state and one with no matching state. Predict which case updates the output and which preserves the starting value.

## Replace unexplained numbers with named states

A job can be queued, running, complete or failed. A name makes that meaning easier to review than an unexplained number in every condition. The example defines JobState with the D enum keyword and an unsigned-byte base type. Its assigned values are 0, 2, 5 and 9. The gaps are deliberate. They let us demonstrate that a byte between the smallest and largest value is not necessarily a valid state. These values are an original teaching protocol, not an existing Umicom job-file format.

~~~d
enum JobState : ubyte {
    queued = 0,
    running = 2,
    complete = 5,
    failed = 9
}
~~~


## Inspect declarations at compile time

The import from std.traits provides EnumMembers. EnumMembers!JobState describes the declared enum members. The exclamation mark supplies a template argument; it is not logical negation here. Its length supplies the count constant, and static assert checks that this exercise currently contains four states. static foreach expands one printing statement per declared member during compilation. The resulting program still performs its output when it runs. This is a small use of reflection: code inspects declared type information rather than maintaining a second hand-written list of those members. Reflection does not automatically validate input bytes or implement state transitions.


## Read raw input before assigning a state

The decodeState function receives a ubyte and a ref JobState result. ubyte is an unsigned byte, so its ordinary values range from zero to 255. ref allows the function to refer to the caller's existing state without resetting it on entry. The function uses an ordinary switch over the raw byte. Four cases assign a corresponding named state and return true. The default case returns false without writing result. This is an allowlist: only the explicitly admitted values become states. A range test such as raw <= 9 would incorrectly accept 1, 3, 4, 6, 7 and 8.


## Trace the unchanged-on-refusal guarantee

The caller initializes selected to JobState.failed and tries to decode the byte 3. That byte lies inside the overall numeric span but has no declared meaning. decodeState returns false, and selected must remain failed. Keeping the old result is useful when parsing a replacement record: the application can report refusal without displaying half-parsed new state. It must also pay attention to the returned bool. Ignoring false and continuing as though failed were a newly decoded value would be a caller error. A preserved sentinel proves a storage rule, not that the failed input was accepted.


## Explain the function attributes in context

The small decode and label functions are marked @safe, pure, nothrow and @nogc. The code is intended to remain within the compiler's safe subset, avoid mutable global dependencies, avoid ordinary exception throwing and avoid garbage-collected allocation. These are constraints checked on these functions and their calls. They do not turn an entire program into a safety-certified application or guarantee that arbitrary memory obtained from C is valid. main uses normal D runtime output. Returning string literals from label does not require building a fresh message buffer in that function. Review the earlier effects and ownership lessons before adding file or network operations to these constrained helpers.


## Test all 256 byte values

The unittest block loops through uint values from zero up to but excluding 256. The loop bounds make each cast to ubyte representable. Before each trial, state is reset to failed. Expected acceptance is true only for 0, 2, 5 and 9. For accepted bytes, converting the named value back to uint must recover the input and its label must be nonempty. For refused bytes, the sentinel must be unchanged. Enumerating this small input space is stronger than testing one good value and one bad value. It still proves only this decoder, not a complete file format or job lifecycle.


## Build the exercise with checks enabled

Open PowerShell in the native-language-boundary laboratory directory. Use an installed DMD compiler for the command below. -unittest includes the test block; -g retains debugging information; -of chooses a distinct output filename. Stop on compilation errors. Keep assertions enabled and do not substitute a release option that disables the checks being studied. This example has been authored for the D toolchain; the separate C regression results do not validate it.

~~~powershell
dmd -unittest -g -of=explicit-job-states-d.exe explicit_job_states.d
& .\explicit-job-states-d.exe
~~~

1. Predict the four numbered labels before running.
2. Compile the complete source, including its unit tests.
3. Run the new executable only after successful compilation.
4. Expect Declared states: 4, the four labels, and Refused byte 3; preserved: failed.


## Study a controlled extension

In a separate copy, add cancelled=12 to JobState. First compile without changing anything else. The member-count static assertion and the exhaustive label function should require attention. Update the deliberate count and label case, then add raw-byte admission for 12 and adjust the expected acceptance in the test. These are separate responsibilities: declaration, presentation, input validation and regression expectation. Reflection keeps the printing list synchronized, but it does not decide whether an old file version is allowed to contain the new value. A real protocol would need its own version and compatibility rules.


## Use the idea through a C Framework boundary

Framework can retain a C-owned table of supported states, their stable numeric codes and display metadata. An optional D client can expose named enum values and use compile-time reflection to check its own wrapper coverage. The two representations still need a reviewed mapping and ABI tests. Do not serialize a compiler's object memory and assume it is a portable file. Do not pass an enum cast as proof that a provider's status was understood. Keep reusable job-state validation in Framework, while each application chooses how to display refusal and recovery.


## Separate state labels from legal transitions

Knowing that running is a valid state does not mean every transition into it is allowed. A job might move from queued to running but require a new attempt before moving from failed to running. This lesson validates one state code and names it; it does not validate previous-state history, job identity, concurrency, permissions or retry policy. As a follow-up exercise, draw a table with one row for each starting state and one column for each destination. Mark allowed changes and explain who owns them. Implement transition checks as a separate contract rather than hiding them inside a label function.


## Further reading

- [D language reference: enums](https://dlang.org/spec/enum.html)

## Further reading

- [D language reference: final switch](https://dlang.org/spec/statement.html#FinalSwitchStatement)

[Previous: Publish results deliberately with ref and out](32-publish-results-with-ref-and-out.md)

[Next: Distinguish lazy evaluation from caching](34-distinguish-lazy-evaluation-from-caching.md)
