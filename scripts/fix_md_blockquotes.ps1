# Fix Markdown MD028 for Windows PowerShell 5.1:
#  - Remove physical blank lines between two blockquote lines
#  - Remove "blank blockquote" lines like '>' or '>   ' inside a blockquote

Set-Location (Resolve-Path (Join-Path $PSScriptRoot '..'))

$files = Get-ChildItem -Recurse -File -Filter *.md |
  Where-Object {
    ($_.FullName -notmatch '\\(volumes|book|site|\.github\\ISSUE_TEMPLATE)\\') -and
    ($_.Name -ne 'PULL_REQUEST_TEMPLATE.md')
  }

$changedCount = 0

foreach ($f in $files) {
  $text = Get-Content -LiteralPath $f.FullName -Raw -Encoding UTF8

  # 1) Remove a physical blank line between two blockquote lines
  $pattern1 = [regex]::new('(?m)(^\s*>.*\r?\n)\s*\r?\n(\s*>)')
  do {
    $old = $text
    $text = $pattern1.Replace($text, '${1}${2}')
  } while ($text -ne $old)

  # 2) Remove a blank blockquote line ('>' or '>   ') inside a blockquote
  $pattern2 = [regex]::new('(?m)^\s*>\s*\r?\n(?=\s*>)')
  do {
    $old = $text
    $text = $pattern2.Replace($text, '')
  } while ($text -ne $old)

  if ($text -ne (Get-Content -LiteralPath $f.FullName -Raw -Encoding UTF8)) {
    [System.IO.File]::WriteAllText($f.FullName, $text, [System.Text.UTF8Encoding]::new($true))
    $changedCount++
  }
}

Write-Host "Fixed MD028 blockquote blanks in $changedCount Markdown file(s)."
