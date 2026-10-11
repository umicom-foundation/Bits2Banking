# Episode 11 — Build, verify and publish one learning website

**Duration:** approximately 12–16 minutes.

**Related lessons:** [50. Publish the website and its books](../../lessons/05-engineering/50-publish-learning-and-books-together.md), [51. Verify publication in C23](../../lessons/05-engineering/51-verify-publication-in-c23.md), and [52. GitHub Actions publication](../../lessons/05-engineering/52-one-github-pages-deployment.md).

## 00:00–01:30 — Two sources, one website

**On screen:** Show the `content` and `dropzone` directories in the Bits2Banking repository. Highlight *Islam: Blueprint for Life* without moving any of its source chapters.

**Narration:**

A lesson and a book are related, but they do not have to be produced by the same tool. We write our introductory computing lessons as Markdown pages. MkDocs turns those pages into a website with navigation and search. Our earlier books have their own manuscript files and a BookForge generator. We want readers to reach both forms from the same address.

The important rule is to keep the original authorship and source files intact. The generated website is replaceable. The original manuscripts are not temporary build output.

## 01:30–04:30 — Run the two generators

**On screen:** Open PowerShell in `C:\umicom\Umicom-Bits2Banking`. Show the `.venv` Python path. Run `python scripts/forge_all.py` and `python -m mkdocs build --strict` using the virtual-environment interpreter.

**Narration:**

The first command asks BookForge to build a catalogue of existing books. The second asks MkDocs to build the learning pages. These commands write to different folders: BookForge uses `output/site`, while MkDocs uses `site`.

If a program says a module is missing, do not guess which Python installation it selected. Verify the interpreter path. If a book format requires Pandoc, check that dependency separately. A Markdown website does not magically include a PDF generator.

**On screen:** Open both generated `index.html` files in the file explorer. Explain that an index file is the home page for a directory.

## 04:30–07:00 — Assemble the published site

**On screen:** Run `python scripts/publish_learning_portal.py assemble`, then `verify`. Show `site/archive/books/index.html` and the `downloads` directory.

**Narration:**

We do not merge the two generators by letting them write over one another. Instead, the publication step copies the older book website into its own section of the MkDocs output. The learning home stays where it is, and the book catalogue receives a stable address.

The `verify` command checks that the expected entry pages exist. In the C implementation that follows, we will verify something stronger: the actual contents of every file.

## 07:00–10:00 — Verify integrity in native C23

**On screen:** Show `umicom-education publish manifest --repo ...`, then `publish verify`. Open the resulting `site.sha256` file in a text editor. Point to the digest and filename columns.

**Narration:**

A checksum is evidence about bytes. SHA-256 turns the contents of a file into 256 bits, usually written as 64 hexadecimal characters. If the contents change, the digest is expected to change too.

Our Framework-owned C23 tool reads each file in chunks. It does not load the whole website into memory and it does not need Python to calculate the hashes. It records a sorted inventory, then checks the current site against that record.

**On screen:** Change a disposable copied HTML file, run verification and show a normal reported failure. Restore the test copy. Do not edit a committed manuscript as part of this demonstration.

**Narration:**

The failed check is useful. It tells us that the site changed after its manifest was recorded. We investigate before approving a new inventory. A checksum cannot prove the publisher is trustworthy, but it can reveal unplanned content changes.

## 10:00–13:00 — One GitHub Pages deployment

**On screen:** Open `.github/workflows/learning-pages.yml` and the GitHub Actions interface. Highlight the build job, upload step and single deployment job.

**Narration:**

A workflow is a set of instructions that GitHub executes on a fresh machine. We use one workflow to prepare the historical manuscripts, run checks, build books, build the site, combine the outputs and publish the result.

The older book workflows still build their artifacts. Their independent website deployment is disabled, so a book-only deployment cannot overwrite the learning website. Only the combined website is published.

A pull request can run the build checks without changing the public website. After a reviewed change reaches `main`, the publication job can update GitHub Pages.

## 13:00–15:00 — Review the reader experience

**On screen:** Open the learning home, a hardware chapter, *Islam: Blueprint for Life*, the historical book catalogue and a video-script page. Follow the links to Umicom Framework and Umicom Kernel.

**Narration:**

Our goal is not simply to produce HTML files. A reader should be able to begin with no computing knowledge, follow the explanations, try an exercise and discover the source code that implements what they just learned.

Each new Umicom capability gives us another opportunity to teach. Each improvement to these lessons can be shared with the next person. That is how learning becomes a contribution to others.

**Closing on screen:** Bits2Banking website, Umicom Foundation repository links and the next chapter: computer architecture and memory.
