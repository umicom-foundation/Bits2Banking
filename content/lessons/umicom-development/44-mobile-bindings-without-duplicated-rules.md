<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/44-mobile-bindings-without-duplicated-rules.md

PURPOSE:
Explain the lesson: Connect mobile screens without copying the rule.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Connect mobile screens without copying the rule

## Before you begin

This is an architecture lab with two optional platform exercises. Android execution needs Android Studio, an SDK, NDK, CMake and an emulator or device. iPhone execution needs a Mac, Xcode and an iOS Simulator runtime. Each platform lab README starts with an unchanged template application.

## Compare the boundaries

On Android, Kotlin calls a native declaration through the Java Native Interface, usually called JNI. On iPhone, Swift calls a C declaration exposed by a bridging header. Both paths end at `BtbActivityNext`, which calls the existing activity rule.

~~~text
Kotlin -> JNI function -> C bridge -> activity model
Swift  -> C declaration ---------> C bridge -> activity model
~~~

The native language owns the screen. C owns the shared operation. This avoids translating and maintaining the same rule independently in Kotlin and Swift.

## Inspect the Android adapter

Its function name identifies a package, class and method. Renaming only the Kotlin package breaks that connection. The JNI environment pointer is valid for its calling context; this example neither saves it nor sends it to another thread.

## Inspect the iPhone adapter

The bridging header makes the declaration visible to Swift. Compiling `bridge.c` and `activity.c` into the target supplies the implementation. Seeing a declaration is not the same as linking a function body.

## Lab

1. Draw each platform's call path.
2. Mark where the input representation changes.
3. Find the single file deciding the activity limit.
4. List platform-specific files and shared files separately.
5. Choose one platform and follow its README before attempting the other.

## Expected result and limits

Each screen should show one accepted increment per tap. A host C test checks the rule but not the mobile packaging or lifecycle. An emulator result does not establish behavior on every physical device.

When integration fails, first identify whether the error happened while compiling, linking, loading the library or calling the function. That distinction gives a much smaller place to investigate.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-framework-activity/activity_jni.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](43-call-c-from-a-browser.md) · [Next lesson](45-sampled-buttons-on-small-devices.md)

