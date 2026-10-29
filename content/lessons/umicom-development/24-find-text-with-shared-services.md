# Find text with shared Framework services

Read the accompanying [Umicom source example](https://github.com/umicom-foundation/umicom-framework/blob/main/adapters/gtk4/learning_catalogue_find.c). Match its revision to your checkout before comparing behavior.


<!-- Preserved initial caption for review; the same controls now support verified source.
A long guide needs a way to find a word without reading every paragraph again. In this lesson you will follow a real feature in Umicom Framework: Find in this guide. The native learning catalogue uses the same literal-search service as document editors. This shows how one checked rule can support different applications while each window keeps control of its own state.
-->
A long guide needs a way to find a word without reading every paragraph again. In this lesson you will follow a real feature in Umicom Framework: Find in this resource. The native learning catalogue uses the same literal-search service as document editors. This shows how one checked rule can support different applications while each window keeps control of its own state.


Read [Introduction to GTK4](05-introduction-to-gtk4.md) and [Preserve structure when reading code](20-preserve-structure-when-reading-code.md) if windows, callbacks or reading models are new. You can complete the paper exercises without building software. The complete console example is in `examples/reading_search` in Framework; the native adapter is `adapters/gtk4/learning_catalogue_find.c`.


## 1. Decide what is being searched


A guide starts as HTML source. Tags such as `<h1>` describe a heading. The reading model turns that source into visible text and metadata, which is information describing that text. A position in the HTML source is usually not the same position in the displayed guide: tags have been removed, entities decoded and spacing organized.


Find searches the reading model's text. It does not search the HTML tags, a hidden script, another file or every course on disk. Catalogue search is different: it searches resource titles and topics. Giving these actions different names helps users understand why one result can exist in the catalogue while another exists inside an open guide.


The example contains two visible occurrences, `Framework` and `framework`, plus a word inside a script element. The reading projection omits script content. That third occurrence therefore cannot become a visible search result. No script is executed while preparing the projection.


## 2. Reuse a rule instead of copying an algorithm


The shared operation is `UmiEditorSearchNavigate`, declared in `umicom/editor/search_engine.h`. Its name records its original module, but its contract accepts ordinary text buffers rather than an editor window. It can therefore serve a guide reader too. The native catalogue links the Editor service and calls it; it does not keep a second matching algorithm with slightly different rules.


```c
UmiEditorSearchOptions options = {
    UMI_EDITOR_SEARCH_CASE_ASCII_INSENSITIVE, 0, 0, 0U
};
UmiEditorSearchMatch match;
int wrapped = 0;
UmiStatus status = UmiEditorSearchNavigate(
    text, text_bytes, query, query_bytes,
    &options, start, 0, 1, &match, &wrapped);
```


This excerpt assumes the named text buffers and byte counts already exist. The complete example supplies them. The first zero after `start` requests forward navigation. The following one permits wrapping. The ampersand operator, as in `&match`, passes the address of storage where the operation can write its result. Read that result only when the returned status is `UMI_STATUS_OK`.


Literal search treats every query character as itself. A period matches a period; it does not mean any character. The selected option ignores case for ASCII A–Z letters. It does not remove accents, translate words or normalize Unicode spellings. Exact rules are easier to reuse than a vague promise to find something similar.


## 3. Distinguish bytes from character positions


A byte is a small unit of stored data. UTF-8 represents some characters with one byte and others with several. A C string ends at a zero byte; `strlen` counts its preceding bytes. It does not count displayed letters. GTK text positions count Unicode characters, and a character position is not always the same as a visible symbol formed from several characters.


<svg viewBox="0 0 840 290" role="img" aria-labelledby="offset-title offset-desc"><title id="offset-title">Bytes and character positions for A space Omega space B</title><desc id="offset-desc">The six UTF-8 bytes are 41, 20, CE, A9, 20, 42. Omega uses two bytes. B starts at byte offset five and character offset four.</desc><g font-family="system-ui,sans-serif" fill="#203047"><text x="20" y="35" font-size="22">Text: A Ω B</text><text x="20" y="80" font-size="18">Byte offsets</text><text x="20" y="195" font-size="18">Character offsets</text></g><g fill="#edf5f8" stroke="#315c74"><rect x="190" y="55" width="95" height="85"/><rect x="285" y="55" width="95" height="85"/><rect x="380" y="55" width="95" height="85"/><rect x="475" y="55" width="95" height="85"/><rect x="570" y="55" width="95" height="85"/><rect x="665" y="55" width="95" height="85"/></g><g text-anchor="middle" font-family="monospace" font-size="21" fill="#203047"><text x="238" y="82">0</text><text x="333" y="82">1</text><text x="428" y="82">2</text><text x="523" y="82">3</text><text x="618" y="82">4</text><text x="713" y="82">5</text><text x="238" y="119">41</text><text x="333" y="119">20</text><text x="428" y="119">CE</text><text x="523" y="119">A9</text><text x="618" y="119">20</text><text x="713" y="119">42</text><text x="238" y="196">0: A</text><text x="333" y="196">1: ␠</text><text x="475" y="196">2: Ω</text><text x="618" y="196">3: ␠</text><text x="713" y="196">4: B</text></g><path d="M380 150H570" stroke="#b43a45" stroke-width="4"/><text x="20" y="260" font-family="system-ui,sans-serif" font-size="18" fill="#203047">The search result uses bytes. The window converts the range before selecting it.</text></svg>


Trace the diagram: B begins at byte 5, but at character position 4. Passing 5 directly as a GTK character position would point after B. The adapter uses `g_utf8_pointer_to_offset` to convert the match's byte boundaries. In the other direction, it uses `g_utf8_offset_to_pointer` to convert the current cursor position into a starting byte offset.


The displayed text and query must be valid UTF-8 before this conversion. A query has a separate 255-byte limit. The entry's character limit alone is insufficient, because 255 non-ASCII characters can occupy more than 255 bytes. The API checks the bytes even when the request comes from code instead of the entry.


## 4. Define Next, Previous and wrapping


A selected match has a beginning and an end. Find next begins after the selected range, so it does not immediately select the same occurrence again. Without a selection, it begins at the cursor. Find previous searches before the beginning of the selection or cursor. When the chosen direction reaches an end, wrapping continues from the other end once.


In the console example, the first search selects the first visible occurrence. The next starts at `match.offset + match.byte_count` and reaches the second. A third search wraps to the first. The program checks those expectations and prints the range and wrap flag. A missing query returns `NOT_FOUND`; it does not invent a location or overwrite the caller's result.


## 5. Keep the document owner alive


`UmiBrowserReadingDocumentText` returns borrowed text. Borrowed means the caller may read it while its owner exists, but must not free it or keep using it after the document is destroyed. The console example finishes every search before calling `UmiBrowserReadingDocumentDestroy`.


The native reader adds another lifetime boundary. Selecting text can immediately invoke a callback registered by other window code. This can happen during the function call, without another thread. The adapter holds a reference to the catalogue and marks it busy while it changes the selection. Another catalogue operation requested by such a callback returns `BUSY`. Retirement remains allowed, so closing the panel prevents later scrolling.


This guard protects the shared destination, not merely the Find button. Otherwise a callback could enter through Help, history or another control while the first operation was still publishing its result. The search itself does not add history, change the guide's bytes or grant permission to run source code.


## 6. Follow the actual implementation


- Read `include/umicom/editor/search_engine.h`. Identify the input byte lengths, starting position and output match.


- Open `src/editor/search_engine.c` and find `UmiEditorSearchNavigate`. Follow its forward, backward and wrap branches with two matches on paper.


- Read `adapters/gtk4/learning_catalogue_find.c`. Locate query validation, byte conversion, the shared call and the busy boundary.


- Read `tests/learning_pack/test_catalogue_find_gtk4.c`. Compare the Unicode, no-match, history and reentrant-observer cases. Authored tests describe expected behaviour; only execution establishes their result.


- Inspect `examples/reading_search/main.c`. Its standalone CMake project links the installed Browser and Editor components. It needs an explicit SDK prefix and does not compile Framework source into the example.



## 7. Try the interface after building your checkout

- Open Guided Learning in Studio and explicitly load the product's learning pack.

- Open a structured guide and wait until loading finishes.

- Press Ctrl+F inside the catalogue, enter a visible word, and press Enter.

- Use Find next and Find previous; observe the selected text and wrap message.

- <!-- Preserved earlier limitation for review: Try a word that is absent. The previous selection should remain. Open a source example: this version reports no structured-guide match instead of searching its fallback notice. -->Try a word that is absent. The previous selection should remain. Open a verified UTF-8 source example and search for a function name. The reader searches the source snapshot already shown, including its comments. It does not execute it. Image and invalid-text notices remain outside Find.


The console example, native interaction and installed-package check answer different questions. A console pass does not prove keyboard focus or window lifetime behaviour. Keep the relevant results with the source revision used for your own build.



## Source examples use the same search engine

A source example has no HTML projection. The worker first verifies its declared digest and UTF-8 bytes, then transfers the displayed allocation to the reader. Find borrows those owned bytes. Its match offsets are source byte positions; GTK still needs character positions. When navigation succeeds, the next selection replaces that allocation. If verification fails during reload, the previous allocation and revision remain intact. A message explaining invalid text is not the source and is never searched.

## Check your understanding

**Why search the projection rather than the original HTML?**

The selected positions must describe visible text. Tags, decoded entities and omitted content make source offsets different from reading offsets.

**Why does the third example search wrap?**

There are only two visible matches. Its start is after the second, so the permitted wrap finds the first. The hidden script text is not part of the reading projection.

**Does a busy flag prevent every possible programming error?**

No. It enforces this catalogue's supported mutation contract during observable changes. It does not validate arbitrary external edits to its widgets or make the whole application memory-safe.


[Previous: Carry image pixels from a worker to a window](23-carry-image-pixels-to-a-window.md) · [Next: Validate a tool connection](25-validate-a-tool-connection.md) · [Course contents](index.md)

Sammy Hegab · Umicom Foundation · MIT.

## Apply the idea

<details>
<summary>Search after a rejected reload</summary>
<p>The reader shows source revision A. Reloading revision B fails verification. Which text should Find inspect?</p>
<p><strong>Explanation:</strong> The accepted text of revision A, if that reader remains open. A failed reload must not pair revision B offsets with revision A text. Search the owned displayed snapshot; do not search the failure notice as if it were source.</p>
</details>
