# Labels and form checks

[Course contents](index.md) · [Previous: Links, illustrations and access](02-links-images-and-access.md)

## What you will learn

Build a small lesson-search form and explain the difference between a visible control and a working service. First complete the two earlier HTML lessons. A form groups information that a visitor wants to send. An input is an editable control. A label tells the visitor what belongs in it.

## Make one complete page

Create a practice folder of your choice. Save this text as `search.html`, using a text editor rather than a word processor. Open the file in a browser. No server or Umicom installation is needed for this demonstration.

```html
<!doctype html>
<html lang="en">
<meta charset="utf-8">
<title>Find a learning topic</title>
<main>
  <h1>Find a learning topic</h1>
  <form action="#results" method="get">
    <label for="topic">Topic to practise</label>
    <input id="topic" name="topic" required minlength="2">
    <button type="submit">Check entry</button>
  </form>
  <p id="results">This practice page checks input; it does not search a catalogue.</p>
</main>
</html>
```

The `for` value matches the input's `id`. Clicking the label should focus that input. The `name` becomes a field name in a submitted request. `required` rejects an empty entry during normal browser submission; `minlength` asks for at least two characters. The button's type says that it submits the form. The `#results` fragment refers to a location in this page, not a database.

## Follow the interaction

```text
Empty entry -> submit -> browser asks for a value
"C"         -> submit -> browser asks for more characters
"HTML"      -> submit -> request allowed; no search engine exists here
```

Try those three cases by typing into the control. The browser's wording varies. Press Tab to reach the control and button without a mouse. A placeholder is not a replacement for a persistent label. Browser checks help people correct mistakes, but a real service must validate received data too: requests can arrive without using this form.

## Exercise and answer

Change the field to request a project name of at least three characters. Which three attributes must still agree? Keep the label's `for` equal to the input's `id`; give `name` a meaningful request field such as `project`. Set `minlength="3"`. The name need not equal the id, because they serve different purposes.

## Connect this to Umicom

Read the real course index linked below. Identify its heading, navigation and ordered lesson links before adding controls to a practice copy. Do not label a button Search unless it reaches a real search implementation. If your page appears as raw text, check that the filename ends in `.html`, not `.html.txt`.

[Review the prerequisite course](../../../courses/learning-computer-architecture/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/learning-html/index.html). Path: `content/courses/learning-html/index.html`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://developer.mozilla.org/en-US/docs/Learn_web_development/Extensions/Forms/Form_validation). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-html/lessons/03-labels-and-form-checks.html).

[Course contents](index.md) · [Previous: Links, illustrations and access](02-links-images-and-access.md)

Sammy Hegab · Umicom Foundation · Original learning material.

[Next: Follow a form to a C service](04-follow-a-form-to-a-c-service.md)
