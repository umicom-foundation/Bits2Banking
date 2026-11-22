<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-keyword-reference/07-handle-failures-and-shared-work.md

PURPOSE:
Read a deliberate classroom error, then see why shared state needs explicit coordination.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Handle a failure and plan shared work

[Course contents](index.md) · [Previous lesson: Ask the compiler about a type](06-ask-the-compiler-about-types.md) · [Next lesson: Recognise reserved and historical D words](08-recognise-reserved-and-historical-words.md)

Read a deliberate classroom error, then see why shared state needs explicit coordination.

## Read the message and its order

An exception signals a failure that transfers control to a suitable handler. The example raises a fictional missing amount and prints the report. Its finally block then records that the review finished.

## Connect the exercise to the build tools

Use small fixtures for successful input, deliberate failure and cleanup. In Umicom Studio, keep all three results visible when you read a test report. Before expanding a toy example to multiple workers, decide which thread owns each value and how others may access it.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `try` | `try { inspect_entry(); } catch (Exception failure) { writeln(failure.msg); }` | Start a block whose raised exceptions can reach an attached handler. |
| `throw` | `throw new Exception("missing amount");` | Raise an exception with a useful description. |
| `catch` | `catch (Exception failure) { writeln(failure.msg); }` | Handle an exception matching this type. |
| `finally` | `finally { writeln("finished review"); }` | Run the cleanup block when control leaves this try construct according to its control-flow rules. |
| `scope` | `scope(exit) writeln("leaving function");` | Schedule an action when this scope exits. scope also qualifies declarations and parameters. |
| `shared` | `shared int job_count;` | Declare shared state and select appropriate synchronization before accessing it from multiple workers. |
| `synchronized` | `synchronized (lock) { ++count; }` | Protect this block with a suitable shared lock object. Every access needs to follow the same locking contract. |
| `__gshared` | `__gshared int legacy_counter;` | Select global storage without the shared qualifier. Take responsibility for concurrency separately. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
TRY a review of the entry
IF a matching exception is raised, show its message
WHEN leaving the review, show the finish message
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

void inspect_entry()
{
    throw new Exception("missing amount");
}

void main()
{
    try {
        inspect_entry();
    } catch (Exception failure) {
        writeln(failure.msg);
    } finally {
        writeln("finished review");
    }
}
```

```text
dmd -run practice.d
```

Expected output

```text
missing amount
finished review
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Replace the throw with a writeln that prints entry accepted. Which output line still comes from the finally block?

**Check your answer**

The output is `entry accepted` followed by `finished review`. The catch block runs only when its exception is raised.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Lexical grammar and Keywords](https://dlang.org/spec/lex.html)
