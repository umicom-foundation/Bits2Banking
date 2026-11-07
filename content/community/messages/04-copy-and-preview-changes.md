# Copy, rename and preview a deletion

Let us practise on the copy only. Type -> Remove-Item -LiteralPath ".\README-backup.md" -WhatIf
Now type -> Test-Path -LiteralPath ".\README-backup.md"
It should still say True. -WhatIf described the deletion without doing it.

[Full steps, explanations and recovery help](../lessons/04-copy-and-preview-changes.md)
