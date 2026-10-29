# Connect keyboard and button help

<h2>What you will learn</h2>
<p>A useful Help button should answer a predictable question. It should not open a
different page merely because a title changed or because the application started
from another folder. In this lesson you will follow the same help request from a
button and from the F1 key into Umicom Framework's local guide reader. You will
also see what happens when the guide is missing or its window has closed.</p>
<p>You can trace the first steps on paper. The practical section uses the complete
C example in <code>examples/native_learning_help</code> in Umicom Framework.
Read the earlier lessons on functions, GTK4 and contextual-help routes if those
terms are unfamiliar. You do not need a network account or private documents for
this exercise.</p>
<h2>1. Separate the question from the page</h2>
<p>A <em>route</em> is a small record that connects a question to its intended
answer. The question has four parts: a product, a language or locale, a kind,
and a key. The answer names a pack and a resource within that pack. A pack is
a set of local files described by a manifest. A resource is one declared file,
such as a guide or source example.</p>
<table><thead><tr><th>Part</th><th>Value in the example</th><th>Meaning</th></tr></thead><tbody>
<tr><td>Product</td><td><code>learning-example</code></td><td>Which application owns the question</td></tr>
<tr><td>Locale</td><td><code>en</code></td><td>The requested guide language</td></tr>
<tr><td>Kind</td><td><code>TOPIC</code></td><td>A general topic rather than a particular command or diagnostic</td></tr>
<tr><td>Key</td><td><code>getting-started</code></td><td>A stable program identity</td></tr>
<tr><td>Pack and resource</td><td><code>framework.native-help-example</code>, <code>guide</code></td><td>The declared answer</td></tr>
</tbody></table>
<p>These identities are literal program data. The application does not insert
an open document's contents, account details or an error's private message into
them. A translated button caption can change without changing its route.</p>
<h2>2. Understand a widget context</h2>
<p>A GTK widget is a part of a window, such as a button, text view or containing
box. A container is the parent of the widgets inside it. This forms a tree.
The native help service can attach a route to a containing widget, called the
<em>context</em>. An explicit Help action begins at its button and walks towards
the parents until it finds the nearest context with a route.</p>
<figure><svg viewBox="0 0 720 270" role="img" aria-labelledby="help-tree-title help-tree-description">
<title id="help-tree-title">Two actions use one copied help policy</title>
<desc id="help-tree-description">A context owns a copied route. Its Help button
and F1 controller both request that route. A weak reference points to a local
catalogue, which resolves the guide from an explicitly loaded pack.</desc>
<rect x="20" y="20" width="330" height="220" rx="12" fill="#e6f0f5" stroke="#23485c"/>
<text x="40" y="50" font-size="18" fill="#173047">Context: copied route</text>
<rect x="40" y="80" width="130" height="55" rx="6" fill="#fff" stroke="#23485c"/>
<text x="55" y="112" font-size="16" fill="#173047">Help button</text>
<rect x="190" y="80" width="140" height="55" rx="6" fill="#fff" stroke="#23485c"/>
<text x="205" y="112" font-size="16" fill="#173047">F1 controller</text>
<text x="40" y="178" font-size="16" fill="#173047">Same product + topic identity</text>
<text x="40" y="210" font-size="15" fill="#173047">No borrowed application pointer</text>
<path d="M350 130H430" stroke="#23485c" stroke-width="3"/>
<path d="M418 122L430 130L418 138" fill="none" stroke="#23485c" stroke-width="3"/>
<text x="365" y="108" font-size="13" fill="#173047">weak</text>
<rect x="435" y="70" width="265" height="125" rx="10" fill="#eef5e7" stroke="#38613c"/>
<text x="455" y="103" font-size="18" fill="#173047">Local catalogue</text>
<text x="455" y="135" font-size="15" fill="#173047">Admitted pack + exact resource</text>
<text x="455" y="166" font-size="15" fill="#173047">Verify bytes before display</text>
</svg><figcaption>Keyboard and button actions share policy; the catalogue owns
the actual loading and reading work.</figcaption></figure>
<p>Suppose an editor panel has its own help context inside a larger workspace.
The editor's route wins. If that route has no matching guide, the service reports
the missing guide instead of quietly opening the workspace's different answer.
This makes the result explainable.</p>
<h2>3. Bind a route without borrowing its lifetime</h2>
<pre><code>UmiStatus status = UmiLearningHelpGtk4Bind(context, panel, &amp;route);</code></pre>
<p><code>context</code> is the containing widget. <code>panel</code> is the shared
learning catalogue. <code>&amp;route</code> means the address of the route record.
The ampersand lets the function read that record. On success the function has
copied the route into its own storage, so it does not depend on the original
record staying on the caller's stack.</p>
<p>A stack variable usually exists only while its function is running.
Saving its address for a later button click would be unsafe. The complete
example avoids that by using a copied policy. It also uses a <em>weak reference</em>
to the catalogue. That reference can report that the catalogue no longer exists,
rather than keeping a closed reader alive just to serve a retained button.</p>
<p>Binding does not load files. The user still chooses and loads the local pack.
It also does not show a window or decide that a project may run code.
Those are separate responsibilities with separate results.</p>
<h2>4. Use the same route for both actions</h2>
<pre><code>static void Help(GtkButton *button, gpointer unused)
{
    (void)unused;
    UmiStatus status = UmiLearningHelpGtk4Open(GTK_WIDGET(button));
    if (status != UMI_STATUS_OK)
        fprintf(stderr, "Help admission: %s\n", umi_status_text(status));
}</code></pre>
<p>This is the button callback from the real example. A <em>callback</em> is a
function GTK calls when an event occurs. <code>GTK_WIDGET</code> treats the button
as its general widget interface, allowing the service to inspect its parents.
The callback has no raw pointer to an application controller and no separate
copy of the route-building logic.</p>
<p>The F1 controller installed by <code>Bind</code> uses the same owned policy.
Modified shortcuts, such as Control+F1, are left to other application handlers.
This lesson's native regression checks emit the controller signal directly;
a real keyboard walkthrough remains a separate interaction check.</p>
<h2>5. Tell acceptance from completion</h2>
<p>Reading a guide may involve a filesystem operation. The catalogue performs
accepted reads on a worker and publishes the result on the GTK thread.
<code>OK</code> from the Help call means the request was accepted. It does not
mean the guide has already appeared. Inspect the catalogue's busy flag and
final status for the completed result.</p>
<p>A missing pack does not start a read. A busy catalogue refuses another request
with <code>BUSY</code>. A closed or retired catalogue refuses with
<code>INVALID_STATE</code>. None of these results should be described as a
successful page display.</p>
<p>Changing a GTK label can notify application observers immediately. Such an
observer might remove the help binding or close a panel while the original
call is still running. The implementation retains its in-flight policy and
blocks recursive dispatch until admission and its notices finish.
The tests include an observer that unbinds itself during a missing-guide notice.</p>
<h2>6. Try the real example</h2>
<ol><li>Install a Framework SDK that includes the native learning catalogue.
Keep its build configuration and installation path with your exercise notes.
A core-only SDK does not provide the graphical component.</li>
<li>Open <code>examples/native_learning_help</code> and read its
<code>CMakeLists.txt</code>. It requires one explicit installed SDK and stages
a local pack whose hashes describe the copied guide and source bytes.</li>
<li>From that example folder, configure a separate build directory, replacing
the example SDK path with your installation:
<pre><code>cmake -S . -B build -G Ninja -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework
cmake --build build --target umicom-native-learning-help</code></pre>
Stop if configuration or compilation reports an error.</li>
<li>Run <code>build/umicom-native-learning-help.exe</code> on Windows or
<code>./build/umicom-native-learning-help</code> on Linux.</li>
<li>Choose Help before loading a pack. Expect a missing-pack notice, not a browser
window. Load the absolute <code>build/pack</code> folder through the catalogue.
Choose Help again and check that the sample guide appears.</li>
<li>Follow the guide's source link. The reader should display the declared
<code>main.c</code> bytes without executing them. Put focus inside the catalogue,
press F1, and check that the guide returns.</li>
<li>Close the window normally. The example retires the catalogue, and accepted
jobs retain the application until their completion cleanup finishes.</li></ol>
<h2>7. Relate it to Studio</h2>
<p>Studio's Guided Learning view offers <strong>Read Studio learning guide</strong>.
Its route names <code>studio.learning-guide</code> and
<code>learning-in-studio</code>. The installed pack is under
<code>share/umicom-studio/learning-pack</code>. Studio supplies those reviewed
identities while Framework owns binding, admission and reading. This is how
a thin application can reuse a substantial shared service.</p>
<p>F1 in that catalogue uses the Studio guide route. This does not imply that
every editor or debugger control has contextual help. Each additional context
needs its own reviewed topic and a complete user workflow check.</p>
<h2>Practice and check your reasoning</h2>
<ol><li>Draw a workspace containing an editor and a Help button. Put one route on
the workspace and another on the editor. Which route should an editor button use?</li>
<li>Predict the result when the nearest route's pack is absent. Explain why
opening an unrelated ancestor guide would hide the actual problem.</li>
<li>Find <code>Release</code>, <code>OpenBinding</code> and
<code>KeyPressed</code> in the implementation. Which object owns the route?
Which reference keeps it alive during callbacks?</li>
<li>Read the <code>unbind-observer</code> regression. Explain why returning from
a label notification cannot mean the original policy is still in its data slot.</li></ol>
<details><summary>Compare your reasoning</summary>
<p>The nearest editor route is authoritative. A missing pack returns a refusal
and leaves the current reader unchanged. The binding owns a copied map.
An additional in-flight reference protects it while observers execute.
Unbinding removes the context's ownership, but that action cannot invalidate
the original call's retained map. The catalogue is weakly held between calls
and strongly held only while a request is being admitted.</p></details>
<h2>Source references</h2><ul>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ui/gtk4/learning_help_binding.h">Native help contract</a></li>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/adapters/gtk4/learning_help_binding.c">Binding ownership and callback implementation</a></li>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/examples/native_learning_help/main.c">Complete native example</a></li>
<li><a href="https://github.com/umicom-foundation/umicom-framework/blob/main/tests/learning_pack/test_help_binding_gtk4.c">Help regression scenarios</a></li></ul>

[Previous: Preserve structure when reading code](20-preserve-structure-when-reading-code.md) · [Course index](index.md)
