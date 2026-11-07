<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-android/07-check-values-before-conversion.md

PURPOSE:
Explain the lesson: Check values before crossing the C boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check values before crossing the C boundary

## Prepare
Open the Android activity example and its shared bridge source in an editor. The reading exercise needs no emulator. For execution, follow the lab README's Android Studio, NDK and Compose setup and run the unchanged template before adding native sources.

A **signed integer** can represent negative and nonnegative values. The shared activity model uses an unsigned count. A negative input must be rejected before it is converted to that model's type.

## Read the guard
The JNI entry point checks:
~~~c
if (current < 0 || current > 1000) return (jint)-1;
~~~
The `||` operator means either condition is enough to reject the input. Only then does the adapter call the C bridge with a converted value. The bridge performs its own boundary check, and the model decides whether a valid count can advance.

The value 1000 is representable and meaningful, but the activity is full. It is therefore useful to distinguish “invalid count” from “valid count with no remaining capacity,” even though this deliberately small platform bridge maps both failures to -1.

## Trace cases
Make a table for -1, 0, 999, 1000 and 1001. Expected public bridge results are -1, 1, 1000, -1 and -1. Include the displayed count before and after a refused update: the screen must not replace it with -1.

## Extend thoughtfully
**Exercise:** design a richer return contract that can distinguish invalid input from full capacity. Write the fields and caller behaviour first; do not put a second activity policy into Kotlin. A reusable product API belongs in Framework, with the platform adapter translating its result.

## Recover from surprising results
Check the input's type and range at the earliest boundary. Do not silence conversion warnings with an unchecked cast. Host bridge checks, emulator calls and screen behaviour are separate observations; record which one you actually exercised.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-activity/activity_jni.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-package-and-library-identity.md) · [Next lesson](08-state-through-screen-recreation.md)

