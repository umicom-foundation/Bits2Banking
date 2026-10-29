# Remember locations without inheriting trust

<h2>What you will learn</h2>
<p>Applications often remember a folder that you chose yesterday. Remembering the
folder is useful, but yesterday's successful read cannot prove that today's files
are unchanged. This lesson explains how Umicom Framework stores learning-library
choices and checks them again before reopening a pack. You will connect a visible
Studio action to the C objects, JSON data and background work that implement it.</p>
<p>You need the ideas of a function, a structure and a pointer. A function performs
one named operation. A structure groups related values. A pointer refers to an
object stored elsewhere in memory. If these are new terms, start with
<a href="../../courses/learning-c/index.html">Learning C</a>, then return here. You can
follow the workflow and diagram without compiling any code.</p>

<h2>1. Start with a real user action</h2>
<p>In Studio, open Guided Learning, then the local learning catalogue. Load a pack
folder and open a guide. In the <strong>Remembered learning libraries</strong>
section, choose <strong>Remember displayed library</strong>. The catalogue keeps
a small record of the pack's absolute root, manifest filename, ID, product, locale
and revision. It does not make a second copy of every lesson.</p>
<p>A <strong>root</strong> is the selected folder beneath which the service reads
files. A <strong>manifest</strong> describes the pack. An <strong>ID</strong> is a
stable name, such as <code>framework.learning</code>, rather than a row number in
the current screen. A <strong>revision</strong> identifies an edition of the pack.
A <strong>locale</strong>, such as <code>en-GB</code>, identifies a language/region.</p>
<p>A row number can change when another entry is removed. For that reason, the
native adapter copies the selected entry before starting background work. It
does not ask the screen which row is selected after the disk operation finishes.
This is the same ownership principle you met in the previous checkpoint lesson.</p>

<h2>2. Give the record one clear owner</h2>
<p>The public header <code>learning_library_choices.h</code> declares an opaque
owner named <code>UmiLearningLibraryChoices</code>. Opaque means a client can use
the pointer and public functions but cannot reach into the private structure.
The implementation can enforce its maximum of 32 entries instead of letting any
caller write past an array boundary.</p>
<pre><code>UmiLearningLibraryChoices *choices = NULL;
UmiStatus status = UmiLearningLibraryChoicesCreate(&amp;choices);
if (status == UMI_STATUS_OK) {
    status = UmiLearningLibraryChoicesRemember(
        choices, admitted_pack, "learning-pack.json");
}
/* Continue only when status is OK. */
UmiLearningLibraryChoicesDestroy(choices);</code></pre>
<p>This is a fragment, not a complete program. <code>admitted_pack</code> must
already refer to a pack accepted by the normal manifest loader.
<code>&amp;choices</code> gives Create the address of the pointer so that it can
return the newly allocated owner. <code>NULL</code> initially means there is no
object. Destroy releases the owner when the client has finished with it.</p>
<p>Remember copies the information it needs. The original pack can therefore be
released without leaving the choices list pointing at freed memory. In contrast,
borrowing <code>pack-&gt;root</code> for a future worker would require the pack to
stay alive for that whole period. Copying a bounded record makes that lifetime
boundary explicit and small.</p>
<p>Read <code>src/teacher/learning_library_choices.c</code>. Find the point where
the candidate entry is validated before it is appended. Notice that a repeated
pack ID returns <code>UMI_STATUS_ALREADY_EXISTS</code>. The code does not silently
replace a location just because another pack uses the same name. Forgetting the
old choice is an explicit separate action.</p>

<h2>3. Separate a memory object from a saved file</h2>
<p>A C structure is not a portable file format. Its layout can contain padding
bytes, and machine representations can differ. The choices codec writes named
JSON fields instead. JSON is a text notation for objects, arrays, strings and
numbers. An object groups named fields between braces; an array lists entries
between square brackets.</p>
<pre><code>{
  "schema": "umicom.learning.libraries",
  "version": 1,
  "libraries": [{
    "root": "C:/Learning/framework-pack",
    "manifest": "learning-pack.json",
    "id": "framework.learning",
    "product": "framework",
    "locale": "en-GB",
    "revision": 3
  }]
}</code></pre>
<p>The path is an example, not a folder that already exists on your computer.
The schema names the format; its version names the rules used to interpret it.
The pack revision is a different number: it describes the learning content, not
the settings format. Keeping these meanings separate avoids accidentally treating
a format change as an update to a course.</p>
<p>The file contains local folder paths. Keep it in a private location outside a
public source repository. It is ordinary text, not an encrypted credential store.
Saving a local path is also not an assessment of the learner, a signed statement
from the course author, or permission to execute its examples.</p>

<h2>4. Admit the whole document before publishing it</h2>
<p>The decoder in <code>learning_library_choices_codec.c</code> calls the shared
bounded JSON tree service. A <strong>bound</strong> is an explicit maximum, such
as 256 KiB of settings or 32 library choices. Bounds stop an input file from
requesting an unlimited amount of memory or work.</p>
<p>Well-formed JSON is only the first check. A JSON number where a root string is
required must still be refused. The codec also rejects unknown fields, repeated
fields, repeated pack IDs, invalid UTF-8, unsupported format versions and paths
that escape the selected root. UTF-8 is the text encoding used to represent
characters as bytes. Rejecting malformed text is different from replacing it
with a similar-looking character and then using the changed path.</p>
<p>The decoder prepares a new owner. It returns that owner only after all entries
are accepted. Suppose the first three entries are valid and the fourth is damaged.
The caller receives a failure and no partial replacement list. A native window
can keep its previous choices until a complete new list is available.</p>
<p>Find <code>ChoiceDecodeRoot</code>. It checks the exact number of expected fields,
then looks up each required field. The shared lookup also detects duplicate
decoded names, so <code>version</code> and <code>ver\u0073ion</code> cannot quietly
stand for two different values. The escape sequence decodes to the same letter
and therefore the same field name.</p>

<figure><svg viewBox="0 0 800 260" role="img" aria-labelledby="choices-title choices-description">
<title id="choices-title">The saved-choice admission boundary</title>
<desc id="choices-description">Decode a settings file into an unpublished candidate. Validate all entries. Publish the candidate only if the complete list is valid. Opening a library happens later through an explicit manifest check.</desc>
<g fill="#edf5fa" stroke="#286783" stroke-width="2">
<rect x="15" y="30" width="220" height="95" rx="8"/><rect x="290" y="30" width="220" height="95" rx="8"/><rect x="565" y="30" width="220" height="95" rx="8"/>
<path d="M235 77h55m-12-8 12 8-12 8M510 77h55m-12-8 12 8-12 8" fill="none"/>
</g><g fill="#173047" font-family="sans-serif" font-size="18" text-anchor="middle">
<text x="125" y="65">Saved JSON</text><text x="125" y="94">Untrusted input</text>
<text x="400" y="65">Candidate choices</text><text x="400" y="94">Validate every entry</text>
<text x="675" y="65">Publish on success</text><text x="675" y="94">Keep old list on failure</text>
<text x="400" y="179">No remembered folder has been opened yet.</text>
<text x="400" y="211">Explicit reopen → read manifest → check identity and compatibility.</text>
</g></svg><figcaption>Loading settings and opening content are different operations.</figcaption></figure>

<h2>5. Reopen without inheriting yesterday's trust</h2>
<p><code>UmiLearningLibraryChoicesReopen</code> reads the manifest from the recorded
root. It requires the same ID, product, locale and revision and checks compatibility
with the host version. A missing file produces a failure. The service does not
look in the current working directory, try a similarly named folder, download a
replacement or run a command to repair the pack.</p>
<p>A remembered revision is not a cryptographic signature. Someone could change a
manifest while keeping its revision number. Reopen does not claim to detect that
history. It admits the current manifest; when the learner opens a declared
resource, the resource loader checks its bytes against that manifest's digest.
A digest is a content fingerprint. It detects changed bytes relative to the
declared fingerprint, but it does not prove who wrote the manifest.</p>
<p>These distinctions matter in many applications. A trading application's remembered
report folder should not become authority to submit an order. A media application's
recent-file list should not become permission to execute a file. A development
tool's recently opened project should not automatically inherit permission to run
its build commands. The learning service provides one concrete example of keeping
a locator separate from authority.</p>

<h2>6. Capture background work before it starts</h2>
<p>The GTK adapter is in
<code>adapters/gtk4/learning_catalogue_libraries.c</code>. Loading settings and
reopening a pack may wait for storage, so those operations use the catalogue's
existing worker. Before dispatch, the adapter copies the filename or clones the
choices owner and captures the selected entry. The worker receives no borrowed
widget and does not read the current text entry halfway through an operation.</p>
<p>A clone is an independent copy with its own lifetime. The window may change a
text field, retire or be destroyed while a request is in progress. The job keeps
what it needs. A weak reference allows completion to check whether a live window
still exists before updating controls. If the window has closed, the result is
discarded from the screen and the job still releases its owned resources.</p>
<p>Saving exclusively creates a new file. If that file already exists, the operation
refuses it. If writing fails after creation, a partial new file may remain and its
receipt says so. Closing a window is not a storage rollback. The user needs an
honest report of what happened, not a message that treats an accepted request as
a completed save.</p>

<h2>7. Read and try the complete example</h2>
<ol>
<li>Open <code>examples/learning_pack_inspector/libraries.c</code> in the Framework
source or installed SDK examples. Read its argument check first.</li>
<li>Find the sequence Load, Create, Remember, Encode, Decode and Reopen. The example
releases earlier owners between these steps to demonstrate independent lifetimes.</li>
<li>After building the SDK example project with its documented CMake instructions,
run <code>umicom-learning-library-choices</code> with an absolute pack folder. The
example project's generated <code>pack</code> folder is suitable.</li>
<li>A successful run prints one remembered choice and the reopened pack ID.
A failure prints its status and returns a nonzero exit code. It does not save a
settings file or execute a course example.</li>
<li>Read <code>tests/learning_pack/test_library_choices.c</code>,
<code>test_library_choices_files.c</code> and
<code>test_catalogue_libraries_gtk4.c</code>. Match a refusal in this lesson to a
regression case and identify what state must remain unchanged.</li>
</ol>
<p>For a first exercise, trace the <code>missing-settings</code> case: why should a
read operation leave the file absent? Next, trace <code>existing-save</code>: why
does a second save not erase the first file? Finally, examine
<code>captured-path</code> in the native test. Explain why editing the path after
dispatch must not redirect the accepted save.</p>

<h2>Check your understanding</h2>
<ol><li>What does remembering a library store, and what does it leave in the original folder?</li>
<li>Why does successful JSON parsing not prove that settings satisfy the application's schema?</li>
<li>Why does a worker need a copied request instead of a pointer to a text entry?</li>
<li>What should the screen keep if the fourth entry of a loaded settings file is invalid?</li>
<li>Why is a saved revision or a content digest not proof of authorship?</li></ol>
<details><summary>Suggested answers</summary><p>The list stores bounded locators and
pack identity; lesson files remain in their folder. A schema adds required names,
types and limits to JSON syntax. A copied request remains stable after the UI
changes. An invalid candidate must not replace the previous list. Revisions are
declared labels, and a digest compares content against a declared fingerprint;
neither authenticates the source by itself.</p></details>

<h2>Read the real Framework sources</h2>
<ul>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/teacher/learning_library_choices.h">Public remembered-library contract</a></li>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/src/teacher/learning_library_choices_codec.c">Strict settings codec</a></li>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/adapters/gtk4/learning_catalogue_libraries.c">Native captured requests and controls</a></li>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/examples/learning_pack_inspector/libraries.c">Complete C example</a></li>
</ul>


[Previous: Store checkpoints on a worker](18-store-checkpoints-on-a-worker.md) · [Course index](index.md)

[Next: Preserve structure when reading code](20-preserve-structure-when-reading-code.md)
