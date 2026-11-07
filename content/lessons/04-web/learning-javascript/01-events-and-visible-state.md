# Events and visible state

JavaScript can react to actions in a browser page. In the task-board lab, submitting a form changes a list of task titles.

## Find the three elements

Read `content/labs/task-board/board.js`. The first lines locate a form, a text input and a list:

```text
const form = document.querySelector("#task-form");
const input = document.querySelector("#task-title");
const list = document.querySelector("#task-list");
let tasks = [];
```

`document` represents the current HTML document. `querySelector` searches it using a CSS selector. A hash selects an ID. If no element matches, the result is `null`. The lab relies on its matching HTML and correct script-loading order; a reusable component must check its required elements.

`const` means the binding will not be reassigned; it does not make the referenced object immutable. `let` permits reassignment. Square brackets create an array, which is an ordered collection. Here each item is a string: a sequence of text.

## Follow one submission

```text
form.addEventListener("submit", event => {
    event.preventDefault();
    const title = input.value.trim();
    if (!title) return;
    tasks.push(title);
    renderTasks();
});
```

This is a shortened extract; the actual lab also saves and clears the input. `addEventListener` registers a function for later. The function does not run merely because it was registered. The event arrives when the form is submitted. `preventDefault` stops the normal form navigation, `trim` removes leading and trailing whitespace, and `push` appends a title.

 <svg viewbox="0 0 700 110" role="img" aria-label="The event changes the model, then rendering turns the model into visible elements." style="width:100%;max-width:700px"><title>The event changes the model, then rendering turns the model into visible elements.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Submit form</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Update tasks array</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Render list</text></svg>

The event changes the model, then rendering turns the model into visible elements.

## Render text safely

```text
const item = document.createElement("li");
item.textContent = task;
list.appendChild(item);
```

`createElement` creates a list item. `textContent` sets its text rather than interpreting the task as markup. `appendChild` attaches it. The real `renderTasks` first calls `replaceChildren`, then rebuilds the list from the array. Rendering twice therefore does not append a duplicate visual copy of every task.

## Connect to native Umicom code

Studio also separates a command from the presented controls. Its C runtime routes menu and toolbar actions through shared services. JavaScript is useful for learning browser events here; it does not replace the C23 service layer or grant a website permission to execute native commands.

## Trace on paper

1. Begin with an empty tasks array.
2. Submit “Read Kernel entry Assembly”. Write the new array.
3. Submit three spaces. Explain why nothing is added.
4. Render twice. Count the final list items.

<details>

<summary>Answer</summary>

There is one title and one visible list item. Whitespace is rejected after trimming; rendering replaces the old children before rebuilding. This is different from appending every task repeatedly.

</details>

---

[Read this lesson in HTML](../../../courses/learning-javascript/lessons/01-events-and-visible-state.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Local storage and untrusted data](02-local-storage-and-untrusted-data.md)
