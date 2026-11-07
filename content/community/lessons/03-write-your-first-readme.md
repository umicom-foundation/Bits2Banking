# Write and read your first Markdown file

Create a README, add a sentence and open it in a text editor.

**Before you start:** PowerShell and Notepad. Use a new practice folder you own. If you followed lesson 2, enter Umicom-Practice/notes-practice in your user folder.

[Community learning route](../index.md) · [Printable HTML](../handouts/03-write-your-first-readme.html)

## What are we creating?

A text file stores characters: letters, numbers and punctuation. Source code is text, but so are project notes. A README explains a project to someone arriving for the first time. Markdown is a way to add simple structure to text, such as a heading starting with #. Its file extension is .md.

A text editor changes these characters. A word processor can also store fonts and page layouts. We use plain text here so the same document can be read in a terminal, an editor or a repository website.

## 1. Check before writing

```powershell
Get-Location
Test-Path -LiteralPath ".\README.md"
```

Test-Path returns True if the file already exists and False if it does not. Continue only in your practice folder. If README.md already contains useful work, open it with Notepad instead of running the next command.

## 2. Create the note

```powershell
Set-Content -LiteralPath ".\README.md" -Value "# My Umicom Notes project" -Encoding utf8
Get-Content -LiteralPath ".\README.md"
```

Set-Content writes the given text. It replaces the existing contents if the file already exists. -LiteralPath treats the path as written, without wildcard matching. -Value is the text to write. UTF-8 is a text encoding: an agreed way of storing characters as bytes. The quotation marks enclose the text; they are not written into this file.

You should see # My Umicom Notes project. In a Markdown viewer, # followed by a space becomes a heading. In PowerShell it remains readable plain text.

## 3. Add another line

```powershell
Add-Content -LiteralPath ".\README.md" -Value "This project is for practising files, Git and C." -Encoding utf8
Get-Content -LiteralPath ".\README.md"
```

Add-Content appends to the end. It does not replace the first line. This difference matters: choosing the wrong write command can remove text you intended to keep.

## 4. Open it in an editor

```powershell
notepad ".\README.md"
```

Add a blank line and a sentence describing what you want your Notes application to do. Save and close the editor. Run Get-Content again. If you installed Visual Studio Code, code ".\README.md" is another way to open the same file.

## If the result is unexpected

If Notepad suggests creating a new file although you already wrote one, check the location and spelling. If text appears twice, Add-Content may have run twice. Open the practice file in the editor and remove only the unwanted duplicate. Do not recreate the whole project.

## Your turn

Add a heading called What I learned and two short lines below it. Explain Set-Content and Add-Content in your own words.

## Continue when you are ready

[Previous: Make a folder for your practice work](02-make-a-practice-folder.md) · [Next: Copy, rename and preview a deletion](04-copy-and-preview-changes.md)

[Explore the related course](../../courses/introduction-to-programming/index.html). You can finish this exercise without leaving this page.

[Video teaching script](../video-scripts/03-write-your-first-readme.md) · [Short community message](../messages/03-write-your-first-readme.md)
