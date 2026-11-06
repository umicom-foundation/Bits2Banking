# A flexible course library

[Course contents](index.md) · [Previous: Responsive and keyboard-friendly pages](02-responsive-and-keyboard-friendly-pages.md)

## What you will learn

Arrange lesson cards without giving every screen a fixed width. Complete the earlier CSS lessons first. A grid is a layout with rows and columns. A gap is the space between cells. A media query applies rules only when a condition, such as the window width, is true.

## Prepare the practice page

Save the following as `library.html` and open it in a browser. Here the style element holds CSS in the same file so that no stylesheet path can be missing. Later a shared stylesheet avoids repeating the rules across pages.

```html
<!doctype html>
<html lang="en">
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Learning library</title>
<style>
body { font: 1rem/1.6 sans-serif; margin: 1rem; }
.library { display: grid; gap: 1rem; grid-template-columns: 1fr; }
article { padding: 1rem; border: 1px solid #526879; }
@media (min-width: 40rem) {
  .library { grid-template-columns: repeat(2, minmax(0, 1fr)); }
}
</style>
<main>
  <h1>Choose a subject</h1>
  <div class="library">
    <article><h2>HTML</h2><p>Structure and meaning.</p></article>
    <article><h2>CSS</h2><p>Spacing and presentation.</p></article>
  </div>
</main>
</html>
```

`1fr` means one share of the available grid space. `repeat(2, ...)` asks for two equal columns. `minmax(0, 1fr)` lets a column shrink; it does not guarantee that unbroken text inside it will wrap. `rem` relates measurements to the root font size, so text settings influence the layout more naturally than a fixed photograph-sized canvas.

## Observe and explain

Narrow the window: the cards should form one column. Widen it beyond the query's threshold: they should form two. Increase browser zoom and notice when the effective space becomes too small. The reading order remains HTML then CSS in both arrangements. CSS should not reverse a meaningful lesson sequence just to fill a gap.

```text
Narrow: HTML -> CSS vertically
Wide:   HTML | CSS horizontally
Source order: unchanged
```

## Exercise and answer

Add a third card for JavaScript. Why is the second row partly empty on a wide display? There are three items and two columns. The third item begins a new row. This is expected, not a missing item. Do not hide that card to make the layout symmetrical.

## Connect this to Umicom

Open the real learning stylesheet below and find its colour variables and `.logo img` rule. Those shared rules keep identity and sizing consistent. Change only your practice page during this exercise. If no layout changes appear, first check your selector spelling and saved file before adding more CSS.

[Review the prerequisite course](../../../courses/learning-html/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/assets/umicom-learning.css). Path: `content/courses/assets/umicom-learning.css`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_grid_layout). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-css/lessons/03-a-flexible-course-library.html).

[Course contents](index.md) · [Previous: Responsive and keyboard-friendly pages](02-responsive-and-keyboard-friendly-pages.md)

Sammy Hegab · Umicom Foundation · Original learning material.
