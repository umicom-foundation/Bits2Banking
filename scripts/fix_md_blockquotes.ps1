# Removes blank lines inside blockquotes (MD028)
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location (Resolve-Path "$root\..")

# Pick the same set CI lints
$files = Get-ChildItem -Recurse -Include *.md -File `
  | Where-Object { $_.FullName -notmatch "\\(volumes|book|site|\.github\\ISSUE_TEMPLATE)\\"
                   -and $_.Name -ne "PULL_REQUEST_TEMPLATE.md" }

foreach ($f in $files) {
  $lines = Get-Content $f.FullName -Raw -Encoding UTF8 -NewLine "`n" -ErrorAction Stop
  $arr = $lines -split "`n"

  $result = New-Object System.Collections.Generic.List[string]
  $prevWasQuote = $false

  foreach ($line in $arr) {
    $isQuote = $line -match '^\s*>'
    # If previous line was a quote and this is an empty line, drop it (MD028)
    if ($prevWasQuote -and ($line.Trim() -eq '')) { continue }

    $result.Add($line)
    $prevWasQuote = $isQuote
    if (-not $isQuote) { $prevWasQuote = $false }
  }

  # Write back with UTF-8 BOM to be Windows-friendly
  [System.IO.File]::WriteAllText($f.FullName, ($result -join "`n"), [System.Text.UTF8Encoding]::new($true))
}

Write-Host "✅ Fixed blockquote blanks in $($files.Count) Markdown file(s)."

