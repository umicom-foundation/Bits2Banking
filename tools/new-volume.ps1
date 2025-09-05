param(
  [Parameter(Mandatory = $true)]
  [ValidatePattern('^[a-z0-9]+(-[a-z0-9]+)*$')]
  [string]$Slug
)

# Run from repo root; if not, try to find it.
if (-not (Test-Path ".git")) {
  Write-Host "Please run from the repository root (folder containing .git)" -ForegroundColor Yellow
  exit 1
}

$rawDir = Join-Path -Path "raw_docs" -ChildPath $Slug
$dstDir = Join-Path -Path "content\volumes" -ChildPath $Slug
$imgDir = Join-Path -Path $dstDir -ChildPath "images"

# Create folders
New-Item -ItemType Directory -Force -Path $rawDir  | Out-Null
New-Item -ItemType Directory -Force -Path $dstDir  | Out-Null
New-Item -ItemType Directory -Force -Path $imgDir  | Out-Null

# Add placeholder chapter if none exist yet
$placeholder = Join-Path -Path $dstDir -ChildPath "ch00-$Slug.md"
if (-not (Test-Path $placeholder)) {
  @"
---
title: "$Slug — placeholder"
volume: "$Slug"
status: draft
source: "scaffold"
created: $(Get-Date -Format 'yyyy-MM-dd')
updated: $(Get-Date -Format 'yyyy-MM-dd')
tags: []
---

# $Slug (placeholder)

This file is created by tools/new-volume.ps1.  
Upload your chapters to **raw_docs/$Slug/** as `.md`, `.docx`, or `.pdf`.  
The ingest workflow will mirror/convert them here.
"@ | Set-Content -Encoding UTF8 $placeholder
}

Write-Host "Scaffolded:" -ForegroundColor Green
Write-Host "  $rawDir" -ForegroundColor Green
Write-Host "  $dstDir" -ForegroundColor Green
Write-Host "  $imgDir" -ForegroundColor Green
Write-Host "Next: upload files to raw_docs/$Slug/ and push to main." -ForegroundColor Green
