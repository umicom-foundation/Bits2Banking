# Preserve structure when reading code

<h2>What you will learn</h2>
<p>A guide can contain instructions, source code, a diagram and links. A reading application must preserve enough structure for those things to remain understandable. In this lesson you will follow the real Umicom Framework reading model from an HTML byte buffer to the text shown in Studio's Guided Learning view. You will learn why a byte position is not always a character position, why a displayed link is not permission to open it, and why a failed replacement should leave the previous page intact.</p>
<p>You can begin with paper and a pencil. You do not need to install an editor to follow the first examples. When the lesson uses a C term, its meaning is explained before the term is used in a larger example. If you want more practice with variables and functions, visit <a href="../../courses/learning-c/index.html">Learning C</a>.</p>

<h2>1. Compare source with presentation</h2>
<p><strong>Source</strong> is the original information stored in a file or a program's memory. <strong>Presentation</strong> is the form shown to a person. The following HTML source describes a heading and a code sample:</p>
<pre><code>&lt;h2 id="source"&gt;A small C function&lt;/h2&gt;
&lt;pre&gt;&lt;code&gt;int answer(void)
{
    return 42;
}&lt;/code&gt;&lt;/pre&gt;</code></pre>
<p>An HTML <strong>tag</strong> gives meaning to text. The opening <code>&lt;h2&gt;</code> and closing <code>&lt;/h2&gt;</code> surround a heading. The <code>pre</code> element asks the reader to preserve spacing. The <code>code</code> element says that the enclosed text is a code example. The <code>id</code> value gives this section a name that another link can target.</p>
<p>The C function is named <code>answer</code>. <code>int</code> says its result is an integer. <code>void</code> inside the parentheses means it accepts no arguments. Braces contain its statements, and <code>return 42;</code> supplies the result. Indentation does not change this function's C meaning, but it makes its structure easier to see. A reader that collapses all whitespace would turn the sample into one crowded line. Other languages and command examples may depend on line boundaries more directly.</p>
<p>Umicom keeps the original verified bytes and creates a separate reading projection. A <strong>projection</strong> is a representation chosen for a particular use. It can add reading structure without modifying the original file.</p>

<h2>2. Give the reading model an owner</h2>
<p>The public contract is <code>umicom/browser/reading_document.h</code>. Its <code>UmiBrowserReadingDocument</code> type owns the resulting text, ranges, links and section positions. A caller creates one object, reads it, and eventually destroys it.</p>
<pre><code>UmiBrowserReadingDocument *document = NULL;
UmiStatus status = UmiBrowserReadingDocumentCreate(
    html, sizeof(html) - 1U, &amp;document);
if (status != UMI_STATUS_OK) {
    return 1;
}
const char *text = UmiBrowserReadingDocumentText(document);
printf("%s\n", text);
UmiBrowserReadingDocumentDestroy(document);</code></pre>
<p>A <strong>pointer</strong> refers to an object in memory. <code>document</code> initially contains <code>NULL</code>, meaning that it does not refer to an object. Passing <code>&amp;document</code> gives the function a place to put the newly created pointer. <code>sizeof(html) - 1U</code> excludes the terminating zero byte of a C string array. The final <code>U</code> on the number denotes an unsigned integer constant.</p>
<p>A <strong>status</strong> is an explicit result describing success or refusal. Always inspect it before using the result. The creation function clears its output on refusal. Use a separate output pointer when you already own another model; do not overwrite the only pointer to an object that still needs to be destroyed.</p>
<p>The <code>text</code> pointer is <strong>borrowed</strong>: it points into the model's memory. It remains usable while the model is alive. It must not be read after the final destroy call. By contrast, a link structure copied through <code>UmiBrowserReadingDocumentLinkAt</code> contains ordinary copied values. Destroying the model does not erase those copied values.</p>

<svg viewBox="0 0 820 240" role="img" aria-labelledby="ownership-title ownership-desc"><title id="ownership-title">Two independent objects and one borrowed view</title><desc id="ownership-desc">An original source buffer supplies bytes to a reading model. The model owns text and metadata. A borrowed text pointer points into the model and must not outlive it.</desc>
<g fill="#edf5f8" stroke="#315c74" stroke-width="2"><rect x="10" y="30" width="210" height="120" rx="8"/><rect x="300" y="30" width="240" height="120" rx="8"/><rect x="620" y="30" width="190" height="120" rx="8"/></g>
<g fill="#203047" font-size="21" text-anchor="middle"><text x="115" y="70">Source buffer</text><text x="115" y="105">original bytes</text><text x="420" y="70">Reading model</text><text x="420" y="105">owned text + ranges</text><text x="715" y="70">Text pointer</text><text x="715" y="105">borrowed access</text></g>
<g stroke="#315c74" stroke-width="3"><path d="M220 90H294m-12-8 12 8-12 8"/><path d="M620 90H546m12-8-12 8 12 8"/></g>
<text x="410" y="210" text-anchor="middle" fill="#203047" font-size="19">Destroy the model only after its readers have finished.</text></svg>

<h2>3. Describe a range precisely</h2>
<p>A <strong>range</strong> identifies a part of the reading text. The model's span structure contains a starting byte position, a byte length and a kind such as heading or code. A heading also records its level. A frontend can display the same range differently without changing its meaning. A native desktop view can apply a bold text tag; a terminal could print a separate heading line.</p>
<p>Consider the UTF-8 text <code>Ω Guide</code>. <strong>UTF-8</strong> is a way to encode characters as bytes. Ordinary English letters use one byte each. The Greek capital omega uses two bytes. The space therefore starts at byte position 2 but character position 1. Counting the visible characters and counting bytes are different operations.</p>
<table><thead><tr><th>Visible item</th><th>Starting byte</th><th>Starting character</th></tr></thead><tbody><tr><td>Ω</td><td>0</td><td>0</td></tr><tr><td>space</td><td>2</td><td>1</td></tr><tr><td>G</td><td>3</td><td>2</td></tr></tbody></table>
<p>The native adapter validates UTF-8 before creating reading structure. It then converts model byte positions to the character offsets required by GTK. Passing a byte position directly to a character-based API could place the cursor after the wrong letter. This is why the regression case named <code>unicode</code> contains a real multi-byte character before its target section.</p>
<p>The core model is deliberately byte-oriented and has no GUI dependency. It refuses embedded zero bytes and prohibited ASCII control bytes, but the frontend remains responsible for UTF-8 validation. A documented boundary is more useful than assuming that every byte array is already displayable text.</p>

<h2>4. Treat a link as data first</h2>
<p>A link contains a caption and a target. For <code>&lt;a href="example.c"&gt;Read source&lt;/a&gt;</code>, the caption is <em>Read source</em> and the target is <code>example.c</code>. Extracting those values must not open the file. A guide may also contain a remote URL, an undeclared local file or a path that tries to escape its pack.</p>
<ol><li>The reading model records the target without using it.</li><li>The catalogue lists the caption and target in Reading controls.</li><li>The learner explicitly chooses Open selected reading link.</li><li>The learning navigation service checks the target against its local path rules and the admitted pack manifest.</li><li>Only a permitted resource is read, verified and presented.</li></ol>
<p>This separation keeps parsing, policy and action distinct. A <strong>parser</strong> recognises the structure of input. A <strong>policy</strong> decides what the application permits. An <strong>action</strong> performs work. Allowing a parser to perform actions while reading untrusted input would make its side effects difficult to understand.</p>
<p>The Umicom offline profile refuses remote schemes, parent traversal, query strings and undeclared resources. It does not launch a browser as a fallback. A section link such as <code>#source</code> stays in the current resource. An absent section is reported instead of pretending that the jump succeeded.</p>

<h2>5. Bound work and preserve the old page</h2>
<p>A <strong>bound</strong> is an explicit maximum. This model limits source bytes, reading text, ranges, links, anchors and nesting depth. Deeply nested markup can otherwise exhaust a call stack, and a huge number of links can consume more memory than a small reading panel should own.</p>
<p>Creation either returns a complete model or refuses the input. It does not return an apparently complete page with silently missing ranges. If the restricted profile cannot represent a document, the catalogue keeps its earlier bounded plain-text conversion as an explicit fallback. A fallback is described as such in the result message.</p>
<p>Allocation failure is treated differently. An <strong>allocation</strong> reserves memory for an object. If it fails while preparing a replacement reading model, the native workflow keeps the previous reader and its history. It does not advance history while leaving old text on screen. The allocation-failure fixture injects that failure at the actual model creation boundary; it is not merely a test of a separate imitation.</p>
<p>Images currently become descriptions such as <code>[Image: Ownership flow]</code>. A missing description is labelled explicitly. This text view does not draw image pixels, reproduce CSS layouts or execute page scripts. These limits are part of the supported behaviour, not hidden assumptions.</p>

<h2>6. Follow the real implementation</h2>
<ol><li>Read the public contract in <code>include/umicom/browser/reading_document.h</code>. Identify which results are copied and which are borrowed.</li>
<li>Open <code>src/browser/reading_document_tokens.c</code>. Find how a quoted attribute containing <code>&gt;</code> differs from the tag's closing angle bracket.</li>
<li>Open <code>src/browser/reading_document_builder.c</code>. Trace one heading and one preformatted block. Find the capacity check before each append.</li>
<li>Open <code>adapters/gtk4/learning_catalogue_reading.c</code>. Locate the conversion from byte offsets to GTK character offsets.</li>
<li>Read <code>examples/reading_document/main.c</code>. This complete installed-SDK example prints a reading projection and inspects a local section link.</li></ol>
<p>Use the <a href="../../umicom/windows-development.md">Windows development guide</a> when preparing tools. The example's CMake project requires the installed Framework SDK's absolute prefix and the <code>browser</code> component. Its successful exit means its own checked reading example succeeded; it does not establish that every native workflow or every HTML document works.</p>

<h2>Practice and review</h2>
<ol><li>On paper, count the bytes and characters before <code>G</code> in <code>Ω Guide</code>. Explain why the numbers differ.</li>
<li>Add an image with useful alternative text to a copy of a guide. Predict the text projection before opening it.</li>
<li>Compare a local declared link, an undeclared filename and a remote URL. Explain the expected policy result for each.</li>
<li>Read the <code>changed-resource</code> native regression. Explain why the old reading structure must remain usable after the digest check fails.</li>
<li>Read <code>retire-publication</code>. Why must a callback that closes a panel prevent later control updates?</li></ol>
<details><summary>Suggested reasoning</summary><p>Omega occupies two bytes but one Unicode character. Image descriptions are text metadata, not decoded pixels. A declared local link may be admitted; missing resources and remote addresses are refused. A failed candidate must not replace an earlier complete reading state. GTK notifications can call application code during publication, so the publisher must check retirement again before continuing to touch controls.</p></details>
<h2>Source references</h2><ul>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/browser/reading_document.h">Reading document contract</a></li>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/src/browser/reading_document_builder.c">Bounded projection implementation</a></li>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/tests/browser/test_reading_document.c">Core refusal and formatting cases</a></li>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/tests/learning_pack/test_catalogue_reading_gtk4.c">Native reading workflow cases</a></li></ul>

[Previous: Remember locations without inheriting trust](19-remember-locations-without-inheriting-trust.md) · [Course index](index.md)

[Next: Connect keyboard and button help](21-connect-keyboard-and-button-help.md)
