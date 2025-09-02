<# 
build.ps1 — helper tasks for Bits2Banking (Windows PowerShell)
Usage examples:
  .\build.ps1 install
  .\build.ps1 build
  .\build.ps1 docs
  .\build.ps1 lint
  .\build.ps1 clean
#>

param(
  [Parameter(Mandatory=$false, Position=0)]
  [ValidateSet('install','build','docs','lint','clean','help')]
  [string]$Task = 'help'
)

function Write-Header($msg) {
  Write-Host "==> $msg" -ForegroundColor Cyan
}

function Install-Deps {
  Write-Header "Upgrading pip and installing dependencies"
  python -m pip install --upgrade pip
  if (Test-Path -LiteralPath "requirements.txt") {
    python -m pip install -r requirements.txt
  } else {
    python -m pip install python-docx
  }
  Write-Host "Install done." -ForegroundColor Green
}

function Build-Volume0 {
  Write-Header "Building Volume 0 DOCX"
  python scripts\make_volume0_from_md.py
}

function Build-Docs {
  Write-Header "Building MkDocs site"
  python -m pip install mkdocs mkdocs-material | Out-Null
  mkdocs build --strict
}

function Lint-All {
  Write-Header "Running markdownlint-cli2 (if available)"
  if (Get-Command markdownlint-cli2 -ErrorAction SilentlyContinue) {
    markdownlint-cli2
  } else {
    Write-Host "markdownlint-cli2 not installed (skipping)." -ForegroundColor Yellow
  }

  Write-Header "Running typos (if available)"
  if (Get-Command typos -ErrorAction SilentlyContinue) {
    typos .
  } else {
    Write-Host "typos not installed (skipping)." -ForegroundColor Yellow
  }
}

function Clean-All {
  Write-Header "Cleaning generated artifacts"
  if (Test-Path -LiteralPath "site") { Remove-Item -Recurse -Force site }
  if (Test-Path -LiteralPath "volumes") { Get-ChildItem volumes -Filter *.docx -ErrorAction SilentlyContinue | Remove-Item -Force }
  Write-Host "Cleaned." -ForegroundColor Green
}

switch ($Task) {
  'install' { Install-Deps }
  'build'   { Build-Volume0 }
  'docs'    { Build-Docs }
  'lint'    { Lint-All }
  'clean'   { Clean-All }
  default {
    Write-Host "Tasks:"
    Write-Host "  install  - Upgrade pip and install dependencies"
    Write-Host "  build    - Build Volume 0 DOCX"
    Write-Host "  docs     - Build MkDocs site to ./site"
    Write-Host "  lint     - Run markdown and typos linters (if installed)"
    Write-Host "  clean    - Remove generated artifacts (volumes/*.docx, site/)"
    Write-Host ""
    Write-Host "Examples:"
    Write-Host "  .\build.ps1 install"
    Write-Host "  .\build.ps1 build"
  }
}
