# 13. CSS: make the task board clear and usable

**CSS** (Cascading Style Sheets) controls the presentation of an HTML document: spacing, colours, text sizes, borders and layouts. It does not change the meaning of the HTML elements. A heading remains a heading even when CSS makes it look different.

We will give the task board a comfortable reading width, improve the form and make it usable on smaller screens.

## Create `board.css`

Save the following beside `board.html`:

```css
:root {
  font-family: system-ui, sans-serif;
  color: #15283b;
  background: #f4f7fa;
}

body {
  max-width: 760px;
  margin: 0 auto;
  padding: 24px;
  line-height: 1.6;
}

header, section {
  background: white;
  border: 1px solid #dce4ec;
  border-radius: 12px;
  padding: 24px;
  margin-bottom: 20px;
}

h1 { margin-top: 0; }

form { display: grid; gap: 12px; }

input, button {
  font: inherit;
  padding: 10px 12px;
  border-radius: 7px;
}

input { border: 1px solid #66798b; }

button {
  color: white;
  background: #165a8d;
  border: 0;
  cursor: pointer;
}

button:hover { background: #10466d; }

button:focus-visible, input:focus-visible {
  outline: 3px solid #e09b2d;
  outline-offset: 2px;
}

li { padding: 6px 0; }
```

Refresh `board.html`. The content is now centred, the form fields have clear spacing and keyboard focus is visible. The text remains readable if you resize the browser.

## Understand the rules

A CSS **selector** chooses the elements to style. For example, `button` selects buttons, `h1` selects top-level headings, and `:focus-visible` applies when a control should show a keyboard-focus indicator. Each rule uses **properties** and **values** such as `padding: 24px`.

The **box model** describes how an element occupies space: content, padding, border and margin. Padding separates content from the element's border. Margin separates the element from others.

`display: grid` arranges the form's children in a column. Later, a wider Kanban board could use CSS Grid to place **To do**, **In progress**, **Review** and **Done** columns side by side.

## Make a two-column layout when space allows

Add this to the end of `board.css`:

```css
@media (min-width: 680px) {
  form {
    grid-template-columns: 1fr auto;
    align-items: end;
  }

  form label { grid-column: 1 / -1; }
}
```

The `@media` condition applies these rules only when the viewing area is at least 680 CSS pixels wide. This is an example of **responsive design**: the layout adapts to the available space rather than assuming every user has the same screen.

## Try it

Change the page background, increase the section padding or change the button colour. Refresh and observe one change at a time. Keep text readable and ensure that keyboard focus remains visible.

The final appearance is not a substitute for usability. A task button that looks attractive but cannot be operated with the keyboard still needs work.

**Next:** [Add task-board behaviour with JavaScript](14-javascript.md).
