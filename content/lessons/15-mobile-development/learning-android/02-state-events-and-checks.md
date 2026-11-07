# Connect a button to visible Android screen state

A screen has state: information needed to describe what it displays now. An event is something that happens, such as a button click. We will connect an event to a state change and observe the resulting text.

## Setup recap

Install Android Studio and its SDK, create an **Empty Activity** Compose project with package `org.umicom.learning`, and launch the template on a virtual or connected Android device. The [setup lesson](01-install-and-launch.md) explains each step. This lesson introduces the Kotlin syntax it uses; [Learning Kotlin](../../02-programming/learning-kotlin/index.md) provides slower terminal exercises.

## 1. Add the example without losing the template

1. Copy the generated `MainActivity.kt` into a notes folder **outside** `app/src`, naming the copy `MainActivity.template.txt`. This keeps the template for comparison without compiling a duplicate class.
2. Open [the complete learning example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/mobile/android-lesson-counter/MainActivity.kt) and replace the active file's contents with it. Retain its header.
3. Confirm that the first package declaration is `package org.umicom.learning`, matching the project created in this course. If you selected a different package, adapt that declaration to your project.
4. Build and run. The first screen should show `Completed: 0 of 3`, an enabled completion button and a disabled reset button.

The example uses the Compose and Material dependencies supplied by the template. Do not paste arbitrary dependency versions from another project if imports fail; first confirm that the project uses the Compose Empty Activity template and that its synchronisation succeeded.

## 2. Read the activity

`class MainActivity : ComponentActivity()` declares a class based on Android's activity support. Android calls `onCreate` when it creates this activity. The call to `super.onCreate(savedInstanceState)` lets the base implementation perform its work. `setContent` supplies the Compose screen. `MaterialTheme` provides consistent text and control styling within that screen.

`@Composable` marks `LessonCounter` as a function that describes Compose UI. `Column` arranges its children vertically. `Text` displays a string. `Modifier.padding(...)` requests space around the contents. The `dp` unit expresses density-independent spacing, so a value represents a similar physical size across different screen densities.

## 3. Read the state and event together

```kotlin
var completed by rememberSaveable { mutableStateOf(0) }
Button(onClick = { if (completed < 3) completed += 1 }, enabled = completed < 3) {
    Text("Complete a practice lesson")
}
```

`var` permits changes. `mutableStateOf(0)` creates observable state initially holding zero. With `by`, Kotlin's property delegation lets reads and assignments use the contained value directly. `rememberSaveable` retains a saveable value across supported activity recreation. It is not a durable course-progress database.

`onClick` receives a block of work to run later. `completed += 1` adds one and stores the result. When observed state changes, Compose can run the screen description again, called recomposition. The new text is based on the new count. `enabled = completed < 3` disables completion at the limit; the callback checks the limit as well. The reset callback assigns zero.

Follow the sequence: **tap → callback → count changes → screen updates**. Creating a button without a callback would stop this sequence at the first step.

## 4. Check visible behaviour

| Action | Expected observation |
| --- | --- |
| Fresh launch | Count 0; reset disabled |
| Tap completion once | Count 1; reset enabled |
| Tap completion twice more | Count 3; completion disabled |
| Tap disabled completion | Count stays 3 |
| Rotate device at count 2 | Count remains 2 after recreation |
| Tap reset | Count 0; completion enabled; reset disabled |

Record actual results. A screenshot of the initial screen does not establish that these events work. After clearing app data or uninstalling, expect a new practice state. Do not depend on this demonstration for permanent learner records.

## 5. Trace the related Umicom design

In [Framework activity.c](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/activity.c), a shared C function owns a counting contract; console and GTK4 frontends use it. In a future Android Umicom client, reusable production rules and persistence belong in Framework, accessed through an explicit service or native binding. The present counter is a local teaching example so that the event sequence can be studied without that extra infrastructure.

## Exercise and answer

Change the practice limit from 3 to 5 consistently in the displayed text, the `enabled` condition and the callback guard. After five taps the count should stop at 5. If only the text changes, the old condition still stops at 3. This is a reason to centralise a repeated rule in a named value or shared service as an example grows.

[Previous lesson](01-install-and-launch.md) · [Course contents](index.md) · [Compose state reference](https://developer.android.com/develop/ui/compose/state)

[Next lesson: Connect an Android screen to an existing C model](03-connect-an-existing-c-model.md)
