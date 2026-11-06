# Responsive columns and reading order

[Course contents](index.md) · [Previous: Classes and reusable components](01-classes-and-components.md)

## What you will learn

Use the stylesheet from lesson 1 to make two columns become one on a smaller screen. Responsive means adapting to available space. Bootstrap's grid uses a row containing columns. A breakpoint is a threshold where a different set of layout rules starts applying.

## Change the practice page

Inside the existing main element, after the outline paragraph, insert this block. Keep the page's stylesheet link and viewport declaration.

```html
<section aria-labelledby="subjects">
  <h2 id="subjects">Subjects</h2>
  <div class="row g-3">
    <div class="col-12 col-md-6">
      <article class="card h-100"><div class="card-body">
        <h3>HTML</h3><p>Describe the meaning of a page.</p>
      </div></article>
    </div>
    <div class="col-12 col-md-6">
      <article class="card h-100"><div class="card-body">
        <h3>CSS</h3><p>Arrange and style that page.</p>
      </div></article>
    </div>
  </div>
</section>
```

`col-12` spans the grid's twelve available parts. `col-md-6` takes six of those parts from the medium breakpoint upward, so two columns fit across. `g-3` supplies gutters, the spacing between columns and rows. `h-100` lets the cards fill their column heights. These are toolkit conventions, not new HTML elements.

## Check the result

At a narrow width expect HTML above CSS. On a sufficiently wide screen expect them beside one another. Zoom to 200 percent and check for clipped text and unwanted horizontal scrolling. Then navigate the links with Tab. A layout that looks correct at one width is not enough evidence of usability.

```text
Small width:  [HTML: 12 parts]
              [CSS:  12 parts]
Medium up:    [HTML: 6] [CSS: 6]
```

## Exercise and answer

Add JavaScript as a third column and use `col-md-4` for all three. Three groups of four fill twelve parts. At narrow widths each must retain `col-12`. Explain why changing only the visible order can be confusing: the keyboard and document reading sequence may still follow the original source order.

## Connect this to Umicom

Compare this grid with the real learning stylesheet's responsive rules. Both should keep the subject sequence understandable. When a card overflows, inspect its content, column nesting and viewport first; do not mask important text with a fixed height. A later lesson will add interactive navigation with its JavaScript dependency and focus checks.

[Review the prerequisite course](../../../courses/learning-css/index.html).


## Source and further reading

[Read the related Umicom example](../../../courses/assets/umicom-learning.css). Path: `content/courses/assets/umicom-learning.css`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://getbootstrap.com/docs/5.3/getting-started/introduction/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-bootstrap/lessons/02-responsive-columns.html).

[Course contents](index.md) · [Previous: Classes and reusable components](01-classes-and-components.md)

Sammy Hegab · Umicom Foundation · Original learning material.
