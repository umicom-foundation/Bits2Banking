<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-zig/03-call-the-shared-c-model.md

PURPOSE:
Explain the lesson: Call the shared C model.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Call the shared C model

Zig can call a C function through an external declaration. This lets another front end reuse a model that already defines the application behavior.

## Setup recap

This lab targets Zig 0.15.2. Check `zig version` and read labs/languages/zig-activity/README.md. Its commands compile the existing C bridge and activity model with the Zig caller.

Open activity.zig beside labs/native/activity-adapters/bridge.h. You do not need an Android emulator or microcontroller for this host example.

## 1. Match the interface

BtbActivityNext takes a C int and returns a C int. The Zig declaration uses c_int, making the intended boundary explicit.

The external declaration tells the compiler that an implementation will be provided during linking. It does not create an implementation.

The model itself remains in C. Avoid copying its capacity rule into every language-specific screen.

## 2. Translate the result

The bridge returns a negative value when it refuses an advance. The Zig wrapper converts this into error.Refused. Otherwise it returns the successful next count.

The wrapper's return type combines ActivityError with c_int. This is an error union: the result is either a value or an error.

The wrapper does not mutate the caller's current value. A screen can update its display only after receiving success.

## 3. Follow one request

For current equal to 999, the bridge calls the C model and returns 1000. For current equal to 1000, the model refuses another advance and the wrapper reports an error.

For a negative input, the bridge refuses before conversion to unsigned. Find that check in bridge.c.

## Exercise and recovery

Draw three boxes: Zig wrapper, C bridge and C model. Label each arrow with its input or output representation.

Explain which layer owns the application limit and which layer translates refusal into a language-specific form.

If the linker cannot find BtbActivityNext, compare your command with the README's C source list. An external declaration alone cannot satisfy that missing implementation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/zig-activity/activity.zig). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](04-handle-an-error-and-continue.md)


[Previous: Return an explicit error](02-return-an-explicit-error.md)
