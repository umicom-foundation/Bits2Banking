# Preview the learning website on Windows

The course uses Markdown files, which are plain-text files that can be read and edited in any text editor. MkDocs converts those files into a browsable website.

## Open your local repository

If you already cloned the repository, open PowerShell and enter:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
```

The branch should be `main` in an ordinary checkout. `git status` tells you whether you have local changes that have not been committed.

## Install the website tools

Check Python:

```powershell
python --version
```

Install the packages needed to build the website:

```powershell
python -m pip install -r ".\requirements-docs.txt"
```

## Check and preview the lessons

First check chapter links and diagrams:

```powershell
python ".\tools\validate_learning.py"
```

Then build the website:

```powershell
python -m mkdocs build --strict
```

This creates a local `site` directory containing the generated website. It does not publish anything to GitHub.

For a browser preview, run:

```powershell
python -m mkdocs serve
```

Open the local address displayed by MkDocs in your browser. The preview updates when you save a Markdown file. Press **Ctrl+C** in PowerShell to stop the preview server.

## Review your changes

```powershell
git status
git diff --check
git diff --stat
```

The generated `site` directory is ignored by Git. Your contribution should normally contain the Markdown lesson, illustration or source-code example you edited—not a second copy of the built website.

To send a contribution to the project maintainers, continue with [Your first pull request](../lessons/05-engineering/17-first-pull-request.md).
