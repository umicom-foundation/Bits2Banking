# Responsive and keyboard-friendly pages

A responsive page adjusts to available space. A usable page also keeps every action visible and reachable when a person uses a keyboard or larger text.

## Let content set the width

A desktop browser may be narrow, and a phone may use enlarged text. Device names alone do not tell you the available reading space. Start with a single readable column, then add columns where the content comfortably fits.

```text
.lesson-grid {
    display: grid;
    grid-template-columns: 1fr;
    gap: 1rem;
}
@media (min-width: 48rem) {
    .lesson-grid {
        grid-template-columns: 1fr 1fr;
    }
}
```

`grid` arranges child boxes into rows and columns. `fr` means a share of available grid space. `gap` leaves space between cells. The media condition applies the two-column rule only when the viewport is wide enough. The example is a learning pattern; choose a breakpoint by checking content rather than assuming all phones have one width.

 <svg viewbox="0 0 700 110" role="img" aria-label="The same lesson content changes arrangement without requiring a second document." style="width:100%;max-width:700px"><title>The same lesson content changes arrangement without requiring a second document.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Narrow: one column</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">More space</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Wide: two columns</text></svg>

The same lesson content changes arrangement without requiring a second document.

## Learn from Bits2Banking

The shared stylesheet defines `.hero-inner`, `.feature-grid` and `.path-grid`. Find their grid declarations and then their media rules. Read both: the first appearance of a class is not the complete story. This is useful when editing the Umicom Framework website too, because a shared component may be used on several pages.

## Keep focus visible

When someone presses Tab, focus moves to the next interactive element. A visible outline communicates that position:

```text
a:focus-visible,
button:focus-visible {
    outline: 3px solid #087784;
    outline-offset: 3px;
}
```

The real stylesheet applies focus styles to links, buttons and disclosure summaries. Do not remove the browser outline unless you provide a visible replacement. A hover style alone does not help keyboard users.

## A skip link has two states

In the real CSS, `.skip` starts off screen and `.skip:focus` places it in view. Press Tab at the top of a lesson to see why. Hiding the link with `display: none` would remove it from normal keyboard navigation, defeating its purpose.

## Use colour with another signal

Do not make “passed” and “failed” differ only by green and red. Display the words too. A focus outline needs enough contrast against surrounding colours. Inspect a contrast calculation when choosing a palette; pleasant-looking colours are not automatically accessible.

## Try these checks

1. Resize your practice page and confirm headings do not overlap.
2. Increase browser zoom and read the whole paragraph.
3. Tab through links and verify the focus indicator is visible.
4. Use a long code line and inspect whether its own region can scroll without forcing the whole page sideways.

A narrow browser preview is not a qualified mobile application. Touch targets, offline storage, device permissions and platform packaging need their own implementation and testing.

---

[Read this lesson in HTML](../../../courses/learning-css/lessons/02-responsive-and-keyboard-friendly-pages.html) · [Learning sequence](../../../start/learning-sequence.md)


## Continue learning

[Continue: A flexible course library](03-a-flexible-course-library.md)

[Previous: Rules, colour and spacing](01-rules-colour-and-spacing.md)
