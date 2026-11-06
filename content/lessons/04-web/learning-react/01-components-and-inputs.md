# Components and their inputs

[Course contents](index.md) · [Next: Clicks and visible state](02-clicks-and-visible-state.md)

## What you will learn

A component is a reusable part of a screen. In React a function can describe that part. Props are values passed into the component by its parent. Before starting, learn HTML elements and JavaScript functions, objects and imports. React is a JavaScript view library; it is not a C compiler or a replacement for Umicom Framework's engine.

## Use a prepared React editor

Open the editable example in the official React introduction. Replace its `App.js` contents with the following. That environment already provides the tools which transform JSX, the HTML-like syntax inside JavaScript. Saving JSX as an ordinary `.html` file will not run it.

```jsx
function LessonCard({ title, minutes }) {
  return (
    <article>
      <h2>{title}</h2>
      <p>Suggested study time: {minutes} minutes</p>
    </article>
  );
}

export default function App() {
  return (
    <main>
      <h1>My learning plan</h1>
      <LessonCard title="Learning C" minutes={20} />
      <LessonCard title="Learning HTML" minutes={15} />
    </main>
  );
}
```

`LessonCard` starts with a capital letter so JSX treats it as our component. The braces around `title` insert a JavaScript value. `minutes={20}` supplies a number, while the quoted title supplies text. Destructuring in the parameter list extracts two properties from the incoming props object. `export default` identifies the component this example environment should load.

## Read the data flow

```text
App -> title and minutes -> LessonCard -> heading and paragraph
```

Expect two articles with different titles and study times. Change the second duration to 25 and observe only its text change. Both articles use the same function; copying the function for every lesson would make future corrections harder.

## Exercise and answer

Add a third card called Learning CSS lasting 18 minutes. Add another `LessonCard` in App with those two props. Do not change the component's hard-coded text for one particular course. Props let one presentation describe different data.

## Connect this to Umicom

Read the linked activity-window C source after the example. It similarly constructs presentation around separately owned behaviour. This is an architectural comparison, not a claim that this React page already connects to native Framework services. If the editor reports a JSX error, check that all tags close and the function returns one enclosing element.

[Review the prerequisite course](../../../courses/learning-javascript/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/window.c). Path: `labs/native/framework-activity/window.c`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://react.dev/learn). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-react/lessons/01-components-and-inputs.html).

[Course contents](index.md) · [Next: Clicks and visible state](02-clicks-and-visible-state.md)

Sammy Hegab · Umicom Foundation · Original learning material.
