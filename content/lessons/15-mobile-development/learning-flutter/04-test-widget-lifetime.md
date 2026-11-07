<!--
Umicom Bits2Banking
File: content/lessons/15-mobile-development/learning-flutter/04-test-widget-lifetime.md

PURPOSE:
Explain the lesson: Test an interface across rebuilds and restarts.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test an interface across rebuilds and restarts

## Test what the user can observe

A widget test creates an interface in Flutter's test environment, performs an interaction and checks visible results. It is faster and narrower than a full device test. It does not replace checking the application on the intended screen, operating system and input method.

The counter already has a test for completion and reset. The lifetime tests add two promises: a theme rebuild preserves a mounted count, and disposing the practice screen does not pretend that temporary state was saved.

## Setup recap

Follow the [counter lab README](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-lesson-counter/README.md). Copy the supplied test files into the practice project's test directory. Keep the generated template test as a separate example, but run the named counter tests because the template expects a different application.

## Read a test interaction

~~~dart
await tester.tap(find.text('Complete a practice lesson'));
await tester.pump();
expect(find.text('Completed: 1 of 3'), findsOneWidget);
~~~

`await` waits for the simulated action. `pump` lets Flutter process a frame. `find.text` identifies visible text, and `expect` compares the observation with the stated matcher.

After the first click, the test rebuilds the same counter under a dark theme using the same key. The count must remain one. It then resets and checks zero.

## Lab

1. Run the two named tests using the README command.
2. Read the test that removes the application and replaces it with SizedBox.shrink.
3. Follow the later creation of LearningApp.
4. Confirm that the expected count is zero, because the old state was disposed.
5. Change one expected count in a practice copy and confirm a failure is reported.
6. Restore the expected result.

The key labels a widget's identity within its parent's reconciliation process. It is not a database identifier and does not persist data across application restarts.

## Exercise and explanation

Why test disposal separately from reset? Reset is an application command. Disposal is a lifetime event. A bug in either path can leave a different visible result.

## Go beyond the widget test

On a real device, check text scaling, keyboard or assistive navigation, rotation where supported and closing/reopening the app. If persistent progress is added later, add storage-failure and recovery tests rather than changing this temporary-state example's claims silently.

The [official Flutter interaction-testing guide](https://docs.flutter.dev/cookbook/testing/widget/tap-drag) explains simulated taps and frame updates. Keep executed results separate from authored test source.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-lesson-counter/lifetime_test.dart). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-state-rebuild-and-disposal.md)

