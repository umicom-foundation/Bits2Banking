# Connect a button to a shared rule

[Course contents](index.md) · [Previous: Widgets and the event loop](01-widgets-and-the-event-loop.md)

## From a click to a result

Continue with the same window. A signal is GTK's notification that something happened. A callback is a function registered to receive that notification. In `window.c`, find the `clicked` connection and the callback named `Completed`.

```text
Click -> clicked signal -> Completed
                        -> BtbActivityAdvance
                        -> status check -> update label
```

Read the callback signature. GTK supplies the button and the connected user data. The callback retrieves the window's retained state instead of using a pointer to a local variable that has already disappeared. Callback parameters must match the signal's expected types; a cast does not repair an incompatible function.

## Separate rule and presentation

The callback asks `BtbActivityAdvance` for the next value. That function is shared by the console and window example. Only after checking its result does the window show the new count. Read `activity.h` to find the rule's limit and failure promise.

Do not create a second counting rule inside the button handler. The same principle applies when a Media button starts a job or a Studio command saves a document: the interface requests an operation and reports the engine's result.

## Check the interaction

With the example running, click once: expect 1. Click again: expect 2. Move keyboard focus to the button using Tab and activate it with Space: expect one further increment. Record the actual outcome. If nothing happens, inspect the signal connection, whether the control is sensitive and whether the event loop is blocked. A disabled button and a disconnected callback can look similar but have different causes.

## Exercise and answer

Write down four checks before editing: initial count, mouse activation, keyboard activation and closing the window. Then compare the shared rule's test for the maximum count. A UI check proves that input reaches a command; the rule test checks accepted values. Both are needed.

The existing callback holds a window reference while using its state and releases it afterward. That balances ownership during work; it is not permission to keep raw widget pointers indefinitely. Long-running work should not occupy this callback until completion. Later lessons introduce worker results returned to the UI thread and cancellation when the owning window closes.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/window.c). Path: `labs/native/framework-activity/window.c`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://docs.gtk.org/gtk4/getting_started.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-gtk4/lessons/02-connect-a-button-to-a-shared-rule.html).

[Course contents](index.md) · [Previous: Widgets and the event loop](01-widgets-and-the-event-loop.md)

Sammy Hegab · Umicom Foundation · Original learning material.
