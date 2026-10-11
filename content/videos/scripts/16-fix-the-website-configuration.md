# Video 16 — Fix a broken website configuration

**Duration:** Approximately 11–14 minutes  
**Related chapter:** [Fix a broken MkDocs website configuration](../../lessons/05-engineering/63-repair-a-mkdocs-configuration.md)  
**Code repository:** [Bits2Banking](https://github.com/umicom-foundation/Bits2Banking)

## 00:00–01:30 — What the error means

**On screen:** PowerShell in `C:\umicom\Umicom-Bits2Banking`; a failed MkDocs message.

**Narration:**

A website can have perfectly good lessons and still fail to open. The pages may be present, the illustrations may be saved, and the Python environment may be working. But if the website builder cannot understand its configuration file, the website will not be generated.

In this episode, we will investigate a real kind of problem from the Bits2Banking educational project. MkDocs reported that it expected the end of a YAML collection and then found something unexpected. The error mentioned two lines in a file called `mkdocs.yml`.

Before we change anything, notice what **did** work: our C web-server tool found the Python interpreter and attempted to build the site. When MkDocs refused to parse the configuration, the server did not start. This is the correct outcome. Serving an old or incomplete website and reporting success would make debugging harder.

We are going to inspect the configuration, understand the indentation, check the original book chapters and rebuild the site.

## 01:30–04:00 — Read the YAML hierarchy

**On screen:** Open `mkdocs.yml` in a source-code editor; highlight `nav:` and the two course titles.

**Narration:**

YAML is a text format used to describe structured settings. Its most important visual feature is indentation. The spaces at the beginning of a line tell the reader which item belongs inside another item.

Here is our navigation. Under `nav:` there is a course called *Volume 1 — Islam: Blueprint for Life*. Beneath it are chapters such as *Introduction to Islam* and *History of Money*. After its chapters comes a second course, *Computer fundamentals*.

The two course headings are equal members of the navigation list, so they must start at the same indentation. In this file, each heading begins with two spaces and a hyphen. The individual chapter entries use six spaces because they belong to their course. The spaces are meaningful; they are not decoration.

Suppose a merge accidentally adds spaces to the second course. The YAML parser can no longer reconcile that line with the list it has been reading. It reports where parsing failed, which might be several lines after the line that introduced the mistake.

We must not solve this by deleting the Islam volume. Those chapters represent previous work and remain part of our educational journey. We correct the structure and preserve the content.

## 04:00–06:00 — Locate the error precisely

**On screen:** Run PowerShell commands one at a time.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
Get-Content ".\mkdocs.yml" | Select-Object -Skip 59 -First 28
```

**Narration:**

This command shows the lines around the reported problem. `Get-Content` reads the file without changing it. `Select-Object` lets us choose the relevant part of the output. We can now compare the leading spaces before each course title.

The project also includes a navigation checker. It uses the project's installed Python environment and reports the line and column of a YAML error. The checker never edits the configuration file.

```powershell
$Python = ".\.venv\Scripts\python.exe"
& $Python ".\tools\check_mkdocs_config.py" --syntax-only
```

If the file is valid, we should see an OK message for the YAML syntax. If not, we can read the exact failure context and fix the indentation in the editor.

## 06:00–08:30 — Check links and build the website

**On screen:** Run the full checker and MkDocs.

```powershell
& $Python ".\tools\check_mkdocs_config.py"
& $Python -m mkdocs build --strict
Test-Path ".\site\index.html"
```

**Narration:**

The full checker does more than read YAML. It checks that the chapter files named in the navigation actually exist. It detects duplicate entries and confirms that the ten original Islam volume chapters remain in order.

A syntax check is only the first gate. Next, MkDocs must render the Markdown pages. The `--strict` option makes warnings important: a broken internal link must be investigated rather than silently accepted as a harmless detail.

If the build succeeds, PowerShell should print `True` when we ask whether `site/index.html` exists. That file is the website's generated home page. The Markdown files in `content/` are still the editable source.

## 08:30–11:00 — Preview using the native C server

**On screen:** Show the application and its browser preview.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education serve --repo $Books --port 8765
```

**Narration:**

Now the native Umicom Education application can serve the generated website locally. Open `http://127.0.0.1:8765/` in the browser. Find the computing lessons, then find the original *Islam: Blueprint for Life* volume. Make sure both open and the illustrations load.

We have followed the problem from a parser error to a working website without removing old chapters or bypassing the build. That process — read the evidence, correct the smallest cause, test the result — is a useful habit across every programming language.

## 11:00–End — Practice

**On screen:** Show a copy of `mkdocs.yml` and the written chapter.

**Narration:**

For practice, make a separate copy of the configuration and deliberately indent one course incorrectly. Run the checker against the copy and read the reported lines. Then put the indentation back and confirm that the syntax check succeeds. You do not need to damage the real website to learn how its failure looks.

The complete chapter, commands and source files are available through the Bits2Banking website and repository. We Value Each Other and Together Everyone Achieves More. Share the reason for a fix, not just the corrected line, so someone else can learn from it.
