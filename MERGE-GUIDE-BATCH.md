# Umicom Bits2Banking — Educational Batch 233–248 / 125–136

**Source baseline:** `umicom-foundation/Bits2Banking` `main` at `0059e9c1d078b28d9ad0ff168ce85fcf4a8fd6de` (observed on 26 October 2026).  
**Author / course lead:** Sammy Hegab · Umicom Foundation.  
**Scope:** Bits2Banking course and educational records only. No Framework C23 implementation or public APIs are replaced in this release.

## Contents

- **LLM from Scratch, Lessons 233–248:** 16 new canonical Markdown manuscripts under `content/lessons/10-native-ai/` and 16 matching browser HTML pages under `content/courses/llm-from-scratch/lessons/`.
- **Mathematics for AI, Units 125–136:** 12 new canonical Markdown manuscripts under `content/lessons/11-maths-for-ai/` and 12 HTML companions under `content/courses/maths-for-ai/lessons/`.
- **Two new HTML navigation/reading paths** at the course roots. Open them directly after copying.
- **Four additional video scripts/storyboards**, two for each course, under `content/videos/scripts/`.
- **Three knowledge records:** reading shortlist, proposed fixture dataset plan and TSV Markdown-to-HTML/paired-lesson relationships. All training rights are explicitly unassessed.
- **Manifest and merge guide**, including expected destinations and SHA-256 file inventory.

## Source-preserving merge

The ZIP root is `Umicom-Bits2Banking/`. Compare that folder to `C:\umicom\Umicom-Bits2Banking` using Beyond Compare. Every educational content file in the ZIP is **new** relative to the observed source baseline. No older lesson, homepage, catalogue, author credit, comment, source file or diagram is included for replacement. **Copy new files only; never synchronise deletions.**

The immediately preceding HTML learning paths are intentionally unmodified. This release creates a new self-contained navigation entry point and links *back* to the preceding routes. Since legacy course homepages are preserved, they may not yet expose the new route until the existing Framework-owned navigation publisher is run or a future source-preserving catalogue update is reviewed. This is intentional, not evidence of lost course content.

## Open in PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
Start-Process ".\content\courses\llm-from-scratch\single-query-attention-learning-path.html"
Start-Process ".\content\courses\maths-for-ai\single-query-attention-mathematics.html"
```

## Validate the merge

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status --short
(Get-ChildItem ".\content\lessons\10-native-ai" -File -Filter "*.md" | Where-Object { $_.BaseName -match "^(23[3-9]|24[0-8])-" }).Count
(Get-ChildItem ".\content\courses\llm-from-scratch\lessons" -File -Filter "*.html" | Where-Object { $_.BaseName -match "^(23[3-9]|24[0-8])-" }).Count
(Get-ChildItem ".\content\lessons\11-maths-for-ai" -File -Filter "*.md" | Where-Object { $_.BaseName -match "^(12[5-9]|13[0-6])-" }).Count
(Get-ChildItem ".\content\courses\maths-for-ai\lessons" -File -Filter "*.html" | Where-Object { $_.BaseName -match "^(12[5-9]|13[0-6])-" }).Count
```

Expected counts: `16`, `16`, `12`, `12`. Verify links in a browser, then run **existing** repository content validation if available. New Markdown-to-HTML relation records are proposed and do not override the existing reviewed knowledge registry.

## Commit / push (only after review)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status --short
git add -A
git diff --cached --check
git diff --cached --name-only
git diff --cached --stat
git commit -m "docs(education): extend single-query attention and mathematics courses"
git push origin main
```

