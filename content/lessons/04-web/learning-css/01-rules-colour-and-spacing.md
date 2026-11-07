# Rules, colour and spacing

CSS describes how a document is presented. HTML provides the structure; CSS chooses spacing, colours, type and layout.

## Read one rule

```text
p {
    color: #192c3e;
    line-height: 1.74;
}
```

`p` is the **selector**: it selects paragraph elements. The braces surround declarations. Each declaration has a property, a colon and a value, followed by a semicolon. `color` controls text colour. `line-height` controls the height of a line box; a unitless value scales with the element's font size.

The real Bits2Banking stylesheet, `content/courses/assets/umicom-learning.css`, puts its main colours in custom properties:

```text
:root {
    --ink: #192c3e;
    --paper: #fff;
}
body {
    color: var(--ink);
    background: var(--paper);
}
```

`:root` selects the root element. A name beginning with two hyphens is a custom property. `var(--ink)` uses its value. The name helps us change a shared choice consistently, but it is not a C variable and has no connection to Kernel memory.

 <svg viewbox="0 0 700 110" role="img" aria-label="A rule affects matching elements without changing their underlying meaning." style="width:100%;max-width:700px"><title>A rule affects matching elements without changing their underlying meaning.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">HTML element</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Matching CSS rule</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Presented content</text></svg>

A rule affects matching elements without changing their underlying meaning.

## Attach a stylesheet

Save `notes.css` beside the HTML file from Learning HTML. Add the following element inside its head:

```text
<link rel="stylesheet" href="notes.css">
```

Now put this CSS in that file:

```text
body { margin: 0; font-family: sans-serif; line-height: 1.6; }
main { max-width: 65ch; margin: auto; padding: 1rem; }
h1 { color: #203247; }
code { font-family: monospace; }
```

`margin` is space outside a box; `padding` is space inside it. `rem` is relative to the root font size. `ch` is based on the width of the zero character in the chosen font. `max-width` limits long lines without forcing a wide fixed page on a small screen.

## Why “cascading”?

Several rules may match the same element. The browser resolves them using origin, importance, layers, selector specificity and order, among other rules. At this stage, compare two ordinary rules with the same selector: the later declaration wins for the same property. Avoid using `!important` as the first response to every unexpected result.

## Practise with the real course

1. Find `.simple-page` in the shared stylesheet. A dot selects a class.
2. Find a lesson element using `class="simple-page"`.
3. On your practice page, add a class called `source-note` and give it padding and a border.
4. Change only the practice stylesheet, then reload your practice page.

Expected result: presentation changes while the same words and headings remain. If nothing changes, check the stylesheet path and selector spelling. Do not remove meaningful headings just to make the page look different.

---

[Read this lesson in HTML](../../../courses/learning-css/lessons/01-rules-colour-and-spacing.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Responsive and keyboard-friendly pages](02-responsive-and-keyboard-friendly-pages.md)
