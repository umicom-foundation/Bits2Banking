# A page with meaning

HTML describes the structure and meaning of a web page. A browser reads this text and presents headings, paragraphs, links and other elements.

## See the page and its source

Open the Learning RISC-V course in Bits2Banking. Its heading is visible on screen; the file also contains tags that describe that heading. A **tag** is a marker between angle brackets. An **element** includes an opening tag, its content and usually a closing tag.

```text
<h1>Learning RISC-V</h1>
<p>Follow a real Kernel service request.</p>
```

`h1` means the main heading. `p` means a paragraph. The slash in `</p>` marks its end. Spaces and indentation help people read source, but they are not a substitute for the element boundaries.

 <svg viewbox="0 0 700 110" role="img" aria-label="The browser interprets structure and exposes it visually and to assistive technology." style="width:100%;max-width:700px"><title>The browser interprets structure and exposes it visually and to assistive technology.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">HTML source</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Browser document</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Readable lesson</text></svg>

The browser interprets structure and exposes it visually and to assistive technology.

## Create a complete small page

In a separate practice folder, save the following text as `kernel-notes.html`. The extension is part of the filename; check that an editor did not silently append `.txt`.

```text
<!doctype html>
<html lang="en-GB">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>My Kernel notes</title>
</head>
<body>
  <main>
    <h1>Reading an environment call</h1>
    <p>The Umicom program places an operation number in a7.</p>
    <ol>
      <li>Read the C function declaration.</li>
      <li>Follow the Assembly register moves.</li>
      <li>Inspect the returned value.</li>
    </ol>
  </main>
</body>
</html>
```

1. `doctype` selects modern HTML interpretation.
2. `lang` identifies the language used in the page, helping pronunciation and language tools.
3. `head` contains metadata. The title appears in the browser tab; it is distinct from the visible heading.
4. `charset` selects UTF-8 text encoding. Encoding is the agreed interpretation of bytes as characters.
5. `main` identifies the main content; `ol` is an ordered list and each `li` is one item.

Double-click the saved page to inspect it locally. Expected result: one heading, one paragraph and a numbered list. This opens a document, not a public server. If you see raw tags, check the file extension and which application opened it.

## Connect to Umicom

Compare this structure with `content/courses/learning-riscv/index.html`. The real page adds navigation and a shared stylesheet. Changing HTML does not change the Kernel executable. The educational page explains code; it is not the code being executed.

Exercise: add a second-level heading called “Return value” and a paragraph explaining `a0`. Use `h2`, rather than selecting a heading because its default font looks convenient. Styling comes next.

---

[Read this lesson in HTML](../../../courses/learning-html/lessons/01-a-page-with-meaning.html) · [Learning sequence](../../../start/learning-sequence.md)
