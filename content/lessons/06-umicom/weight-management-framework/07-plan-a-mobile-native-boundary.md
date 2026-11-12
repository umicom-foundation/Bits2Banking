<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/weight-management-framework/07-plan-a-mobile-native-boundary.md

PURPOSE:
Keep a mobile client tied to the shared C contract

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep a mobile client tied to the shared C contract

## Before you begin
Understand the C client and draft/save distinction. This is a mobile integration planning lesson. The course does not yet ship an Android APK or iOS application.

## Separate the portable code from the host
The kilogram parser and weight schema are C. A mobile build still needs a target ABI, compatible Framework dependencies, platform lifecycle handling, storage policy and a real interface.

Android's NDK can build native libraries. NativeActivity provides a native activity entry and lifecycle callbacks; it does not supply this course's form editor. See the [NDK concepts guide](https://developer.android.com/ndk/guides/concepts) and [NativeActivity reference](https://developer.android.com/ndk/reference/group/native-activity).

1. Choose one platform and CPU ABI for the first qualification.
2. Inventory which Framework application dependencies can be cross-compiled for that target.
3. Keep the domain functions in the existing shared library.
4. Add a platform bridge only for requirements the portable C API cannot satisfy.

A Java or Kotlin interface is not required merely because Gradle participates in packaging. If a selected platform API requires a language bridge, document that concrete boundary and keep the observation logic in C.

## Lifecycle exercise
Trace an edit while the application moves to the background and its process later disappears. A raw pointer to UmiStructuredForm cannot be restored into a different process. Use an owned serialized draft through the existing snapshot contract and validate its schema when restoring.

~~~text
Visible edit -> owned draft snapshot -> platform storage acknowledgement
New process -> load permitted snapshot -> validate schema -> rebuild view
~~~

## Expected result
Your design identifies who owns every buffer, when it is released, and which acknowledged bytes can survive process loss. A successful desktop executable is not evidence that an ARM mobile build links or handles lifecycle events.

## Recovery
If a snapshot is incomplete or uses an unknown schema, retain it for an explicit recovery flow instead of treating it as an empty successful log. If a delayed callback arrives after its screen retires, reject the stale context rather than touching released view memory.

The next implementation milestone is a reviewed platform layout and one reproducible native mobile build with synthetic fixtures. Signing, device installation, background behavior and store distribution remain independent qualification tasks.


[Course contents](index.md) · [Previous lesson](06-connect-an-authorized-web-host.md) · [Next lesson](08-qualify-the-whole-observation-workflow.md)
