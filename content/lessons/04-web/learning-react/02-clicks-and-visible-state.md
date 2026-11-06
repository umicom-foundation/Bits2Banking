# Clicks and visible state

[Course contents](index.md) · [Previous: Components and their inputs](01-components-and-inputs.md)

## What you will learn

State is information a component remembers between renders. Rendering means calculating what its screen should show. An event handler is a function called in response to an action such as a click. We will make a study counter that changes visibly, then explain its limits.

## Replace the practice component

Use the same prepared editor as lesson 1. This complete example replaces App.js:

```jsx
import { useState } from 'react';

export default function App() {
  const [completed, setCompleted] = useState(0);
  function recordExercise() {
    setCompleted(previous => previous + 1);
  }
  return (
    <main>
      <h1>Practice counter</h1>
      <p aria-live="polite">Completed: {completed}</p>
      <button onClick={recordExercise}>Record one exercise</button>
    </main>
  );
}
```

`useState(0)` supplies an initial value and a function that requests an update. The arrow function receives the previous value and returns the next. Pass `recordExercise` to `onClick`; writing `recordExercise()` there would call it during rendering instead of waiting for a click. `aria-live` lets assistive technology announce the changed text without moving keyboard focus.

## Trace one interaction

```text
Initial state 0 -> click -> updater receives 0 -> next state 1 -> text becomes 1
```

Click three times and expect 3. Press Tab to focus the button, then activate it with the keyboard. Reload the example and observe that the count returns to 0. Component state alone is not saved progress. Persistent learning records need an explicit service and storage policy.

## Exercise and answer

Add a Reset button whose handler calls `setCompleted(0)`. Check 0, one click, reset, another click. Expect 0, 1, 0, 1. A button's appearance is not evidence that its event is connected; observing the resulting state is the essential check.

## Connect this to Umicom

In the activity-window source, find `Completed`, its signal connection and `BtbActivityAdvance`. The C example applies a bounded shared rule before updating a label. Our React counter deliberately teaches local state only. A future web client should call the shared engine for authoritative progress, show failures and avoid showing success before the engine accepts the change. If the screen repeatedly rerenders, first look for an accidentally called handler in JSX.

[Review the prerequisite course](../../../courses/learning-javascript/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/window.c). Path: `labs/native/framework-activity/window.c`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://react.dev/learn). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-react/lessons/02-clicks-and-visible-state.html).

[Course contents](index.md) · [Previous: Components and their inputs](01-components-and-inputs.md)

Sammy Hegab · Umicom Foundation · Original learning material.
