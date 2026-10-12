# Bits2Banking | Sammy Hegab, Umicom Foundation | MIT
# UPDATE 28: Append navigation and release notes only after exact preflight.
# Never rewrite, reorder or remove an existing page or original book chapter.
[CmdletBinding()]
param(
    [string]$RepositoryRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$utf8Strict = New-Object System.Text.UTF8Encoding($false, $true)
$utf8Output = New-Object System.Text.UTF8Encoding($false)

function Read-RepositoryText {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path -PathType Leaf)) {
        throw "Missing required source: $Path"
    }
    return [System.IO.File]::ReadAllText($Path, $utf8Strict)
}

function Write-RepositoryText {
    param([string]$Path, [string]$Text)
    # File.WriteAllText creates a complete UTF-8 file without a PowerShell BOM.
    # There is no write until all three proposed replacements pass preflight.
    [System.IO.File]::WriteAllText($Path, $Text, $utf8Output)
}

$repo = (Resolve-Path -LiteralPath $RepositoryRoot).Path
$navPath = Join-Path $repo 'mkdocs.yml'
$roadmapPath = Join-Path $repo 'ROADMAP_MAJOR_UPDATES.md'
$readmePath = Join-Path $repo 'labs/native/http-loopback-server/README.md'
$guidePath = Join-Path $repo 'labs/native/http-loopback-server/UPDATE_28_NONBLOCKING_GUIDE.md'

$lessonFiles = @(
    '167-why-nonblocking-io-matters.md',
    '168-build-a-c23-select-reactor.md',
    '169-monotonic-timeouts-and-graceful-shutdown.md',
    '170-test-and-diagnose-the-nonblocking-server.md',
    '171-connect-reactors-to-umicom-service-ownership.md'
)
foreach ($filename in $lessonFiles) {
    $path = Join-Path $repo "content/lessons/05-engineering/$filename"
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
        throw "Missing Update 28 lesson: $path"
    }
}
foreach ($name in @(
    '58-two-clients-one-nonblocking-reactor.md',
    '59-deadlines-and-graceful-http-shutdown.md'
)) {
    if (-not (Test-Path -LiteralPath (Join-Path $repo "content/videos/scripts/$name") -PathType Leaf)) {
        throw "Missing Update 28 video script: $name"
    }
}
if (-not (Test-Path -LiteralPath $guidePath -PathType Leaf)) {
    throw 'Missing Update 28 native laboratory guide.'
}

$nav = Read-RepositoryText $navPath
$roadmap = Read-RepositoryText $roadmapPath
$readme = Read-RepositoryText $readmePath
$newline = if ($nav.Contains("`r`n")) { "`r`n" } else { "`n" }
$roadmapNewline = if ($roadmap.Contains("`r`n")) { "`r`n" } else { "`n" }
$readmeNewline = if ($readme.Contains("`r`n")) { "`r`n" } else { "`n" }

$anchor = '      - "Video 57. Bounded admission and service ownership": videos/scripts/57-bounded-admission-and-service-ownership.md'
$navMarker = '  - "Nonblocking networking, deadlines and graceful shutdown":'
$navAddition = @(
    '',
    '  - "Nonblocking networking, deadlines and graceful shutdown":',
    '      - "167. Why nonblocking I/O matters": lessons/05-engineering/167-why-nonblocking-io-matters.md',
    '      - "168. Build a C23 select reactor": lessons/05-engineering/168-build-a-c23-select-reactor.md',
    '      - "169. Monotonic timeouts and graceful shutdown": lessons/05-engineering/169-monotonic-timeouts-and-graceful-shutdown.md',
    '      - "170. Test and diagnose a nonblocking server": lessons/05-engineering/170-test-and-diagnose-the-nonblocking-server.md',
    '      - "171. Connect reactors to Umicom services": lessons/05-engineering/171-connect-reactors-to-umicom-service-ownership.md',
    '      - "Video 58. Two clients, one C23 reactor": videos/scripts/58-two-clients-one-nonblocking-reactor.md',
    '      - "Video 59. Deadlines and graceful shutdown": videos/scripts/59-deadlines-and-graceful-http-shutdown.md'
) -join $newline

$navChanged = $false
if (-not $nav.Contains($navMarker)) {
    if ($nav.Split([string[]]@($anchor), [System.StringSplitOptions]::None).Count -ne 2) {
        throw 'Navigation anchor changed or duplicated. Review mkdocs.yml manually; nothing has been written.'
    }
    $nav = $nav.Replace($anchor, $anchor + $navAddition)
    $navChanged = $true
}

$roadmapMarker = '## Update 28 — Nonblocking networking, timeouts and graceful shutdown'
$roadmapAddition = @'

## Update 28 — Nonblocking networking, timeouts and graceful shutdown

**Status:** Teaching-source batch delivered for host qualification (October 2026).

- Optional C23 single-threaded `select()` reactor; default blocking listener unchanged.
- Bounded eight-client admission; nonblocking receive/send; no new worker thread.
- Monotonic idle (3 s) and total (10 s) connection budgets; graceful quiescence.
- Existing HTTP parser, fixed routes, static root, cache ETag and response accounting reused.
- Lessons 167–171, Videos 58–59, three SVGs, native policy tests and optional socket integration.
- Existing sixteen HTTP CTests remain; new expected count is eighteen without Python or nineteen with Python 3.
- Windows UCRT64, strict MkDocs and real console Ctrl+C remain explicit host acceptance gates.

**Next:** bounded asynchronous handoff, worker ownership contracts and controlled completion/cancellation; do not introduce a production web stack into Bits2Banking.
'@
$roadmapChanged = $false
if (-not $roadmap.Contains($roadmapMarker)) {
    $roadmap = $roadmap.TrimEnd([char[]]@("`r", "`n")) + $roadmapAddition.Replace("`n", $roadmapNewline) + $roadmapNewline
    $roadmapChanged = $true
}

$readmeMarker = '## Update 28 — Nonblocking readiness, deadlines and graceful shutdown'
$readmeAddition = @'

## Update 28 — Nonblocking readiness, deadlines and graceful shutdown

The original blocking server remains the default. Update 28 adds an **optional**
`--nonblocking` mode with an eight-connection `select()` reactor, three-second
idle deadline, ten-second total deadline and bounded graceful shutdown.
It reuses the earlier routing, rooted static files, HEAD, ETag and response
progress contracts. See `UPDATE_28_NONBLOCKING_GUIDE.md` in this directory.
No worker threads, public binding, TLS or authenticated financial endpoints
have been introduced. Follow Lessons 167–171 for source walkthroughs.
'@
$readmeChanged = $false
if (-not $readme.Contains($readmeMarker)) {
    $readme = $readme.TrimEnd([char[]]@("`r", "`n")) + $readmeAddition.Replace("`n", $readmeNewline) + $readmeNewline
    $readmeChanged = $true
}

# Publish each entire reviewed buffer. A failure in preflight above cannot
# leave partially written files; users can also inspect git diff before commit.
if ($navChanged) { Write-RepositoryText $navPath $nav }
if ($roadmapChanged) { Write-RepositoryText $roadmapPath $roadmap }
if ($readmeChanged) { Write-RepositoryText $readmePath $readme }
Write-Host "Update 28: navigation updated=$navChanged, roadmap updated=$roadmapChanged, guide linked=$readmeChanged"
Write-Host 'Review git diff, run the C23 CTests, then build the MkDocs site with --strict.'
