<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/110-inspect-paused-integer-slots.md

PURPOSE:
Inspect paused integer slots

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Inspect paused integer slots

An interpreter can pause before it runs a statement. At that moment,
the machine may already have stored values from earlier statements.
A **slot** is a numbered place used by the checked machine to keep an
integer. Reading a slot lets you see the value that exists now.

## Inspect before each change

Save this as `pause.c` in a fresh practice folder.

~~~c
int main(void) {
    int total = 40;
    total += 2;
    return total;
}
~~~

1. Run `umicom-c interpret pause.c --step` in PowerShell.
2. Type `slots` at the first pause. Expect
   `No initialized integer slots.` The declaration is still pending.
3. Type `next`, then `slots`. Expect `local[0]=40`.
4. Type `next`, then `slots` again. Expect `local[0]=42`.
   Type `run` to finish and look for `Result: 42`.

Try `slots` twice at one pause. The values and the next source
position stay the same. Type `show` to see the pending source statement.
Slot numbers describe the machine storage. Use the source preview to
identify which declaration or update you are studying.

## Repeat with pseudocode

Save this example as `pause.txt`.

~~~text
BEGIN
    LET total = 40;
    total = total + 2;
    RETURN total;
END
~~~

Run `umicom-c pseudocode pause.txt --step --jsonl`. Use the same
commands and expect the same slot values beside the prompts. JSON Lines
means each standard-output line contains one complete record. The three
step records and the result record still go to standard output. Slot
values go to the diagnostic stream with the prompts.

~~~json
{"schema":1,"event":"result","value":42,"instructions":8}
~~~

The example shows how a client such as Umicom Studio IDE can use the
compiler’s read-only snapshot service to inspect a paused program. A
different client can read the completed trace without having to parse the
human-readable pause messages.

[Course contents](index.md) · [Previous lesson · Translate an initialized local between C and D](109-translate-an-initialized-local-between-c-and-d.md) · [Related lesson · Count reached source statements](107-count-reached-source-statements.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/110-inspect-paused-integer-slots.html)

[Next lesson · Translate checked shifts between C and D](111-translate-checked-shifts-between-c-and-d.md)
