<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/114-watch-one-integer-slot.md

PURPOSE:
Watch one integer slot

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Watch one integer slot

Use a **watch** when you want the interpreter to pause after a value changes. In this lesson, you will follow one integer from its first value to the number the program returns. Keep a pencil and paper nearby. You can make every prediction before opening a terminal.

## 1. Follow the first slot

A **slot** is a numbered place where the interpreter keeps an integer. The checked interpreter starts numbering at 0 and accepts slot numbers through 31. Before a slot has a value, it is **uninitialized**. Giving a slot the value 0 initializes it just as giving it the value 6 does. A slot number can hold values from different declarations at different points in a larger program. Here there is one variable, `x`, in slot 0.

Save this complete C program as `watch-practice.c`.

~~~c
int main(void) {
  int x = 6;
  x = 6;
  x += 36;
  return x;
}
~~~

Read each line inside the braces. The declaration gives `x` its first value, 6. The next assignment writes 6 again. The addition on the following line makes 42. The return reports that value. Before you run it, write down two moments when a watch should stop and one moment when it should keep going.

## 2. Watch, pause and ask again

In a terminal in the practice file’s folder, start the checked interpreter with the pause option. If the command is unavailable, use the location of your built Umicom C executable and verify that you are in the folder with the practice file.

~~~powershell
umicom-c interpret watch-practice.c --step
~~~

Enter these commands one at a time at the interpreter prompt. Wait for the next prompt after each of the first two commands.

~~~text
watch 0
watch 0
run
~~~

1. The first `watch 0` resumes execution and pauses after the declaration gives slot 0 the value 6. The next prompt points at line 3.
2. The second `watch 0` arms a fresh watch. Writing 6 again keeps the value equal, so execution continues. Adding 36 changes the value, so the next prompt points at line 5, where the return is waiting.
3. Enter `run` to finish. If you enter `quit` at that prompt instead, the earlier step records remain and the program reports cancellation before return.

The watch is **one shot**. It turns off after its first hit. During a pause, you can use `slots` to check the values or `show` to read the waiting source line. The watch observes completed successful source steps. A write that leaves the observed value equal has no watch notice.

## 3. Keep the two output streams separate

**Standard output**, also called **stdout**, carries the normal trace and returned value. This is the complete standard output for the example. The two numbers around each colon give a source line and a column, starting at 1. For example, `4:3` means line 4, column 3.

~~~text
Step 1: statement 2:3-2:13, 2 instructions, success
Step 2: statement 3:3-3:9, 2 instructions, success
Step 3: statement 4:3-4:11, 4 instructions, success
Step 4: return 5:3-5:12, 2 instructions, success
Result: 42
Instructions: 10
~~~

**Standard error**, also called **stderr** or the diagnostic stream, carries the prompts and watch notices. It can carry useful information about a successful run. The two messages below appear alongside the prompts.

~~~text
Slot 0 initialized to 6.
Slot 0 changed from 6 to 42.
~~~

The assignment of 6 still appears as Step 2 in standard output. The watch continued through it. That separation lets a person use the prompts while a tool reads the ordinary step and result records. If another tool needs one JSON record per output line, the interpreter also supports `--jsonl`.

## 4. Make two predictions

- **Try an unused slot.** Start a fresh session and type `watch 31`. This program never uses that slot. Expect `Slot 31 did not initialize or change before return.` on the diagnostic stream and `Result: 42` on standard output.
- **Try less fuel.** Add `--max-steps 1` to the command and type `watch 0` at the first prompt. **Fuel** is the limit on the interpreter’s smaller instructions. The first declaration needs two instructions, so this run stops with `instruction budget exhausted` before it can finish the declaration. Expect a failed first step, no watch hit and no returned value. The watch does not increase the budget.

If you enter `watch 32`, check the slot range message and try a number from 0 through 31. The invalid command leaves the interpreter at its current pause.

## 5. Trace the same idea in Umicom pseudocode

The Umicom pseudocode form starts at 6 and goes straight to the addition. Read it aloud or save it as `watch-practice.txt`.

~~~text
BEGIN
  LET x = 6;
  x = x + 36;
  RETURN x;
END
~~~

Use `umicom-c pseudocode watch-practice.txt --step --jsonl` with the same two watches and `run`. You should see both watch notices on the diagnostic stream. Predict the returned value before you read the last standard-output record. This version has no separate assignment of 6 a second time, so it reports three completed steps and eight instructions.

~~~json
{"schema":1,"event":"result","value":42,"instructions":8}
~~~

The same habit helps when reading results for Umicom Studio IDE. Keep the trace of what ran separate from the paused view of what the program is about to do.

[Course contents](index.md) · [Previous lesson · Compare signed integers between C and D](113-compare-signed-integers-between-c-and-d.md) · [Related lesson · Inspect paused integer slots](110-inspect-paused-integer-slots.md) · [Related lesson · Separate instruction fuel from wall-clock time](59-separate-instruction-fuel-from-wall-clock-time.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/114-watch-one-integer-slot.html) · [C23 keyword reference](../../03-native-code/c23-keyword-reference/index.md)

[Next lesson · Translate short-circuit conditions across C23 and D](115-translate-short-circuit-conditions-across-c-and-d.md)
