# Build a counter and test its buttons

This lesson connects a screen event to state and checks the visible result. A widget test runs a small Flutter interface in a controlled test environment, finds controls, interacts with them and checks the resulting widget tree. It complements testing the actual application on a device.

## Setup recap

Install Flutter, open a new terminal, run `flutter doctor`, and create a project named `lesson_counter`. Confirm the template runs on a browser or another configured device. The [first lesson](01-install-and-run.md) includes exact PowerShell and bash commands. You need no previous Dart course; the key syntax is explained below.

## 1. Place the example files

1. Save copies of the generated `lib/main.dart` and `test/widget_test.dart` in a notes folder outside `lib` and `test`. Use a `.txt` suffix for those reference copies.
2. Replace `lib/main.dart` with [the complete counter source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-lesson-counter/main.dart).
3. Preserve the old template test in place as `test/widget_test.dart.example`. Its original assertions describe the original template and should not run against the new screen.
4. Save [counter_test.dart](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/flutter-lesson-counter/counter_test.dart) as `test/counter_test.dart`.
5. Confirm that `pubspec.yaml` names the package `lesson_counter`. The test imports `package:lesson_counter/main.dart`; if you intentionally chose another package name, adjust that import accordingly.

## 2. Read the screen's ownership

`main()` starts the application with `runApp`. `LearningApp` is a `StatelessWidget`: its configuration has no mutable counter. It returns a `MaterialApp` containing the counter screen and theme.

`LessonCounter` is a `StatefulWidget`. Its associated State object owns `completed`, initially zero. `build` describes the current screen. `Scaffold` provides a page layout, `AppBar` a title area, `Column` a vertical arrangement and `Text` visible words.

The completion button's `onPressed` is a callback, a function retained for a later event. It becomes `null` when the count reaches 3, making the button disabled. Otherwise, the callback changes the count inside `setState`, notifying Flutter that its description must be rebuilt. The guard inside the callback also prevents advancing beyond 3.

The reset button assigns zero in another `setState`. This sample's state is temporary. It is not a durable course-progress store and does not synchronise with another device.

## 3. Run and inspect the screen

From the project folder:

```text
flutter analyze
flutter test test/counter_test.dart
flutter run -d chrome
```

The same commands work in PowerShell and bash; select a device listed by `flutter devices`. `analyze` examines source diagnostics. `test` runs the selected checks. `run` launches an interactive application. Stop and investigate the first failing stage.

At launch expect `Completed: 0 of 3`. After three completion clicks expect 3 and a disabled completion button. After reset expect 0 and a disabled reset button. These are expected outcomes, not evidence that every deployment target has been qualified.

## 4. Follow the automated test

`testWidgets` supplies a test environment. `pumpWidget(const LearningApp())` mounts the application. `find.text(...)` locates displayed text. `expect(..., findsOneWidget)` requires exactly one match. `tester.tap(...)` sends a tap; `pump()` processes a frame after the state change.

The test performs three taps, checking 1, 2 and 3 in order. It inspects the completion button's callback at the limit and requires `null`. Finally it taps reset, checks zero and verifies completion is enabled again. Thus it checks both text and interaction state, not just whether the screen can be created.

## 5. Connect the idea to Umicom

Compare the screen with [the shared C activity example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/activity.c). For production Umicom clients, reusable policy and persistent data belong in Framework. A Flutter frontend would need a reviewed service or native binding; this teaching screen does not yet implement one. Its local state exists to make one event sequence understandable.

## Exercise and worked answer

In a separate practice copy, make the reset callback assign 1 instead of 0. The final text expectation should fail. Restore zero and rerun the selected test. Passing this widget test checks the described behaviour; still check keyboard operation, scaling and layout on each actual deployment target.

For the test API used here, see the [official Flutter widget-testing guide](https://docs.flutter.dev/cookbook/testing/widget/introduction).

[Previous lesson](01-install-and-run.md) · [Course contents](index.md) · [Framework Development](../../umicom-development/index.md)

[Continue: Understand state, rebuilds and disposal](03-state-rebuild-and-disposal.md)
