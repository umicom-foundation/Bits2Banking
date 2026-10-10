# 12. HTML: give a web application structure

A web page is more than the colours and pictures you see in a browser. It contains a structure that describes the meaning of its content. **HTML** (HyperText Markup Language) gives that structure names: heading, paragraph, navigation, form, label, button, table and many others.

We will begin a small **Umicom Task Board**. Its first version shows tasks and provides a form for adding new ones. CSS will improve its appearance in the next chapter, and JavaScript will make it interactive.

## Create `board.html`

Save this file in a folder named `task-board`:

```html
<!doctype html>
<html lang="en-GB">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Umicom Task Board</title>
  <link rel="stylesheet" href="board.css">
  <script src="board.js" defer></script>
</head>
<body>
  <header>
    <h1>Umicom Task Board</h1>
    <p>Keep track of work from idea to completion.</p>
  </header>

  <main>
    <section aria-labelledby="new-task-heading">
      <h2 id="new-task-heading">Add a task</h2>
      <form id="task-form">
        <label for="task-title">Task description</label>
        <input id="task-title" name="title" required maxlength="120">
        <button type="submit">Add task</button>
      </form>
    </section>

    <section aria-labelledby="tasks-heading">
      <h2 id="tasks-heading">Tasks</h2>
      <ul id="task-list">
        <li>Read the next Umicom lesson</li>
      </ul>
    </section>
  </main>
</body>
</html>
```

Open `board.html` in your browser. The page works as a document even before you add CSS or JavaScript. You can read the headings, see the list and type into the input. The button will not yet save the task because the programme that handles it has not been written.

## Understand the elements

`<!doctype html>` identifies a modern HTML document. `<head>` contains information about the page, such as its title and character encoding. `<body>` contains the visible document content. `<header>`, `<main>` and `<section>` describe meaningful regions that help browsers, assistive technologies and readers navigate the page.

A `<label>` identifies what an input field is for. The label's `for="task-title"` connects it to `id="task-title"`. The `required` attribute asks the browser to check that a value has been entered, and `maxlength="120"` limits the text field's length. These browser checks improve the experience; they are **not a substitute for validation on a server**.

The `<link>` element loads `board.css`, and `<script ... defer>` loads `board.js` after the HTML has been parsed. Those files do not exist yet; we create them in the next two chapters.

## Inspect the document

Right-click a heading in the browser and select **Inspect**. Developer tools show the element's HTML and later its applied CSS. You can see that the heading is text inside an `h1` element, not merely a large font.

Try changing the heading to `Project Work Board` and refreshing the page. The browser shows your new text. You have made your first web-page edit.

## When to use HTML

HTML is not a general-purpose programming language: it describes document structure. JavaScript adds behaviour, CSS adds visual styling, and server-side languages such as PHP can generate or process content. In Umicom applications, web frontends may also communicate with services provided through framework-owned APIs.

**Next:** [Use CSS to lay out the task board](13-css.md).
