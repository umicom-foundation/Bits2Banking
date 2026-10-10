# Umicom Bits to Banking — prepare the original book pages and Framework branding.
# Author: Sammy Hegab / Umicom Foundation
# Preservation: source manuscripts and canonical Framework assets are never edited.
param(
    [string]$BrandSource = "",
    [switch]$Refresh
)
$ErrorActionPreference = "Stop"
$repositoryRoot = Split-Path -Parent $PSScriptRoot
Set-Location $repositoryRoot
$arguments = @("tools/prepare_learning_site.py")
if ($BrandSource) { $arguments += @("--brand-source", $BrandSource) }
if ($Refresh) { $arguments += "--refresh" }
& python @arguments
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
