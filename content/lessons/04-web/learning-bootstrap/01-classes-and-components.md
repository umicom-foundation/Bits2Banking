# Classes and reusable components

[Course contents](index.md) · [Next: Responsive columns and reading order](02-responsive-columns.md)

## What you will learn

Bootstrap is a collection of styles and optional JavaScript components. It does not replace HTML. A class is a name on an element that a stylesheet can match. Complete Learning HTML and the first CSS lessons before starting; otherwise a toolkit's short class names hide the ideas you need to understand.

## Prepare a local example

Download the compiled Bootstrap 5.3 CSS from the official introduction. Extract it and place `bootstrap.min.css` beside a new `index.html` in a practice folder. Keep the download's licence. No JavaScript is needed for this first page. A minified stylesheet contains compressed formatting; it is still CSS.

```html
<!doctype html>
<html lang="en">
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="bootstrap.min.css">
<title>Course information</title>
<main class="container py-4">
  <article class="card">
    <div class="card-body">
      <h1 class="card-title">Learning C</h1>
      <p class="card-text">Start with values, decisions and functions.</p>
      <a class="btn btn-primary" href="#outline">Read the outline</a>
    </div>
  </article>
  <h2 id="outline" class="mt-4">Outline</h2>
  <p>Read one program, change one value, explain the result.</p>
</main>
</html>
```

Open the file in a browser. `container` constrains the main area's width; `py-4` adds vertical padding. The card classes supply a reusable presentation. The link is still an anchor, even when it looks like a button: it navigates to the outline. Keyboard activation should reach the same destination.

## Trace the dependency

```text
HTML element + class name -> matching CSS rule -> visible presentation
HTML anchor + href       -> browser navigation
```

Rename the stylesheet temporarily in your practice folder and reload. The presentation changes, but the heading and link remain meaningful. Restore the filename. This separates missing styles from broken navigation.

## Exercise and answer

Add a second card for Learning HTML. Give it a different outline id and matching fragment link. Reusing an id would make the destination ambiguous. Do not add a button that claims to enrol anyone: this page has no enrolment service.

## Connect this to Umicom

Bits2Banking already has its own shared stylesheet, linked below. Study its reusable classes alongside this practice page. Learning a toolkit does not require replacing the Umicom theme or loading another stylesheet into every product.

[Review the prerequisite course](../../../courses/learning-css/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/assets/umicom-learning.css). Path: `content/courses/assets/umicom-learning.css`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://getbootstrap.com/docs/5.3/getting-started/introduction/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-bootstrap/lessons/01-classes-and-components.html).

[Course contents](index.md) · [Next: Responsive columns and reading order](02-responsive-columns.md)

Sammy Hegab · Umicom Foundation · Original learning material.
