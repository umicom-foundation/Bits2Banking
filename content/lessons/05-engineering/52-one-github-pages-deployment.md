# 52. Publish one website through GitHub Actions

GitHub Actions runs commands on a temporary computer when changes reach a repository. A **workflow** is a YAML file that describes what to do, when to run and what permissions it needs. We use it to check the educational material, build the site and publish the verified output.

In earlier versions of Bits2Banking, two separate book workflows could publish different output directories to the same GitHub Pages address. If both ran, one publication could replace the other. A single deployment owner avoids that conflict.

## 1. Read the workflow

Open [learning-pages.yml](https://github.com/umicom-foundation/Bits2Banking/blob/main/.github/workflows/learning-pages.yml). Its important steps are:

```text
Checkout educational content and Umicom brand
                   ↓
Prepare existing manuscripts and logo assets
                   ↓
Validate lessons, diagrams and links
                   ↓
BookForge generates the original book catalogue
                   ↓
MkDocs generates the learning website
                   ↓
Combine the two generated sites
                   ↓
Upload the completed site as one Pages artifact
                   ↓
Deploy once, on main
```

This uses the existing BookForge generator instead of rewriting original books. The older workflows still produce downloadable build artifacts, but their old deployment jobs are retained in a disabled state while this workflow controls GitHub Pages.

## 2. Understand three GitHub Actions concepts

An **artifact** is a collection of output files retained by a workflow. A **build job** creates and checks the site. A **deployment job** publishes the resulting artifact. A pull request runs the build and validation but does not publish the proposed changes to the public site.

The workflow requests permission to read source code and, only when needed for deployment, write a GitHub Pages artifact. It does not need a password embedded in Markdown or a manually copied token.

## 3. Try the checks locally

From `C:\umicom\Umicom-Bits2Banking`, first run the existing lesson validation:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" .\tools\validate_learning.py
& ".\.venv\Scripts\python.exe" -m unittest discover `
    -s tests -p "test_learning_portal.py" -v
```

After preparing your sources and building both generators, complete the archive:

```powershell
& ".\.venv\Scripts\python.exe" .\scripts\publish_learning_portal.py assemble --refresh
& ".\.venv\Scripts\python.exe" .\scripts\publish_learning_portal.py verify
```

The archive is generated at `site/archive/books/`. The learning home remains at `site/index.html`. Existing DOCX and PDF formats are copied only when their generators have actually produced those files.

## 4. Inspect your first workflow run

After the repository update is merged and pushed, open the [Bits2Banking Actions page](https://github.com/umicom-foundation/Bits2Banking/actions). Select **Umicom Learning — Website and Book Archive**. Read the build job's messages in order.

A successful build is not a guarantee that every chapter is accurate. Open the site, follow the links, read a complete lesson and inspect the original *Islam: Blueprint for Life* volume. If any build step fails, correct the source or configuration and run the checks again rather than removing the step.

The public website is [Bits to Banking — Umicom Learning](https://umicom-foundation.github.io/Bits2Banking/). Its original book catalogue is published under `/archive/books/` when the unified deployment succeeds.

## 5. What to check before merging

Review the changed workflow, confirm that no old book manuscript or file was deleted, and verify that the old BookForge artifact jobs remain present. The main deployment should be the only active job that calls `actions/deploy-pages`.

The next step in this learning path is to inspect the relationship between your source files, the generated website, the C23 publication manifest and the published GitHub Pages artifact.
