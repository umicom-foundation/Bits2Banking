<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/05-untrusted-sizes-and-representations.md

PURPOSE:
Explain the lesson: Check representations before crossing a platform boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check representations before crossing a platform boundary

## One value, several representations

An Android or iPhone screen calls a small C adapter in this lab. The screen represents its count as a signed integer; the shared activity model uses an unsigned count. Signed integers can represent negative values. Unsigned values cannot represent them in the same way.

## Setup recap

The [adapter lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/README.md) can be built as a host C project with the Framework base SDK. You do not need a phone to inspect its model checks. Actual mobile execution also needs the platform setup in the Android or iPhone course.

## Reject before converting

Read `BtbActivityNext`. It checks for a negative input before converting to the unsigned model representation. Casting first would change a negative value into a large unsigned value and conceal why the input was invalid.

~~~text
signed input -> reject negatives -> call bounded model
             -> accept only valid result -> return signed answer
~~~

The shared model permits counts from zero to one thousand and refuses another increment at the limit. The adapter uses a negative return to indicate refusal. It never returns a wrapped count as progress.

## Lab

1. Trace inputs -1, 0, 999 and 1000 through the adapter.
2. Predict outputs -1, 1, 1000 and -1.
3. Inspect tests for the smallest and largest signed integers.
4. Read the Android JNI wrapper's range check before its conversion to C `int`.
5. Build and run the host adapter tests using the guide.
6. Record mobile behaviour separately if you later run a device build.

Host tests establish the adapter behaviour for that host build. They do not prove that a mobile library loads or that its method names match.

## Troubleshooting

If a screen displays a negative progress count, it probably treated the error sentinel as a valid answer. Check the result before updating visible state. If the native function is never reached, investigate library loading or the binding name first; changing arithmetic will not repair a missing binding.

## Exercise

Would changing the C model limit to a value larger than a signed mobile integer be just a UI adjustment? No. The boundary contract and tests would need review. The accepted range must be representable on both sides.

## Connect to Framework

Keep the domain limit in the shared model. Each adapter checks its incoming representation and translates the outcome. Do not reproduce the entire progress rule independently in Kotlin, Swift and JavaScript.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/bridge.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-borrowed-streams-and-failure-boundaries.md)


[Next: Replace two fields as one complete change](06-two-fields-one-commit.md)
