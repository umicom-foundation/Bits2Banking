# Links, illustrations and access

A useful course lets a learner find the next step, return to earlier explanations and understand diagrams without relying only on colour.

## Resolve a relative path

In a lesson stored at `learning-riscv/lessons/01-registers-and-memory.html`, `../index.html` means move up one directory to the course contents. A **relative** path starts from the current file's directory. An absolute web address starts from a named website.

```text
<nav aria-label="Lesson navigation">
  <a href="../index.html">Course contents</a>
  <a href="02-programs-and-privileges.html">Next lesson</a>
</nav>
```

`a` creates a link and `href` holds its destination. The visible text should explain the destination. A generic “click here” gives little help when someone scans a page or hears a list of links.

 <svg viewbox="0 0 700 110" role="img" aria-label="The two dots in ../index.html select the parent directory before looking for the index file." style="width:100%;max-width:700px"><title>The two dots in ../index.html select the parent directory before looking for the index file.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Lesson directory</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Parent course</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Course index</text></svg>

The two dots in ../index.html select the parent directory before looking for the index file.

## Make navigation available without a mouse

Bits2Banking pages place a “Skip to content” link before the main navigation. It points to the element whose `id` is `main`:

```text
<a class="skip" href="#main">Skip to content</a>
<main id="main">...</main>
```

The hash marks a location within the page. IDs should be unique in that document. Press Tab to move through interactive elements, then Enter to follow a link. A clear focus outline shows where keyboard input will act. Never make a link reachable only by hovering a mouse.

## Describe an illustration

An image needs an explanation of what it contributes. A decorative image can use empty alternative text; a meaningful diagram needs words that communicate its point. Our register diagrams also include a visible caption and nearby step-by-step text. Colour reinforces the relationship; it does not carry the whole explanation.

```text
<figure>
  <img src="register-flow.svg"
       alt="The operation moves from a0 to a7 before ECALL.">
  <figcaption>Register roles change at the service boundary.</figcaption>
</figure>
```

This fragment requires an actual `register-flow.svg` file. Do not paste it and assume the file will appear. The existing RISC-V lesson embeds its SVG drawing directly, so it has no separate image dependency.

## Display code as text

To show `<main>` rather than create a main element, write `&lt;main&gt;` in the source. The escaped brackets are text. This distinction matters when teaching code or displaying imported user content.

## Check the result

1. Follow every previous, next and course-content link.
2. Use Tab and Enter without touching the mouse.
3. Read the page at a narrow width and with enlarged text.
4. Explain the diagram without seeing its colours.

If a local link fails, compare the destination with the actual directory names, including letter case. A path that happens to work on one filesystem may fail on a case-sensitive server. These checks complement automated checks; neither alone proves that every learner can use the page.

---

[Read this lesson in HTML](../../../courses/learning-html/lessons/02-links-images-and-access.html) · [Learning sequence](../../../start/learning-sequence.md)
