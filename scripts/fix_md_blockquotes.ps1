# Fix Markdown MD028: remove blank lines that appear BETWEEN two blockquote lines.
# Compatible with Windows PowerShell 5.1

# Go to repo root
Set-Location (Resolve-Path (Join-Path $PSScriptRoot '..'))

# Pick the same set CI lints
$files = Get-ChildItem -Recurse -File -Filter *.md |
  Where-Object { $_.FullName -notmatch '\\(volumes|book|site|\.github\\ISSUE_TEMPLATE)\\' -and $_.Name -ne 'PULL_REQUEST_TEMPLATE.md' }

$changedCount = 0

foreach ($f in $files) {
  # Read as a single string (no -NewLine in PS 5.1)
  $text = Get-Content -LiteralPath $f.FullName -Raw -Encoding UTF8

  # Split on CRLF or LF (no capture)
  $lines = $text -split '(?:`r`n|`n)'

  $out = New-Object System.Collections.Generic.List[string]
  $modified = $false
  for ($i = 0; $i -lt $lines.Count; $i++) {
    $line = $lines[$i]

    # If this line is blank AND the previous line starts with '>' AND the next line starts with '>'
    if ($line.Trim() -eq '' -and $i -gt 0 -and $i -lt ($lines.Count - 1)) {
      $prev = $lines[$i - 1]
      $next = $lines[$i + 1]
      if ($prev -match '^\s*>' -and $next -match '^\s*>') {
        $modified = $true
        continue  # drop the blank line between two quoted lines
      }
    }

    $out.Add($line)
  }

  if ($modified) {
    $newText = ($out -join "`r`n")
    # Write back as UTF-8 with BOM (Windows-friendly)
    [System.IO.File]::WriteAllText($f.FullName, $newText, [System.Text.UTF8Encoding]::new($true))
    $changedCount++
  }
}

Write-Host "Fixed MD028 blockquote blanks in $changedCount Markdown file(s)."
