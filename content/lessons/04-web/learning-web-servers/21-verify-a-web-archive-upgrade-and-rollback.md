<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/21-verify-a-web-archive-upgrade-and-rollback.md

PURPOSE:
Rehearse a web archive upgrade and rollback using archive hashes and release markers.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Verify a web archive upgrade and rollback

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

An upgrade replaces the archive selected for an application. A rollback selects the previous archive again. Both copies can have the same name, so check the file’s identity as well as the release label stored inside it.

This rehearsal works with files. It uses the static practice page from [Make a web page and its stylesheet](01-make-a-page-and-stylesheet.md), with the same archive name used by the [Tomcat exercise](04-deploy-a-war-on-tomcat.md) and [WildFly exercise](05-deploy-the-same-war-on-wildfly.md).

## 1. Set up a rehearsal folder

Open PowerShell in `web-servers-lab`, the folder that contains `public` from the first lesson. Use the same PowerShell window for all three steps. The `jar` command from your JDK should be available.

```powershell
$practicePage = Join-Path $PWD.Path 'public'
$rehearsal = Join-Path $PWD.Path ('war-rehearsal-' + [Guid]::NewGuid().ToString('N'))
$stagedPage = Join-Path $rehearsal 'site'
$previous = Join-Path $rehearsal 'previous'
$candidate = Join-Path $rehearsal 'candidate'
$selected = Join-Path $rehearsal 'selected'

New-Item -ItemType Directory -Path $rehearsal -ErrorAction Stop | Out-Null
New-Item -ItemType Directory -Path $stagedPage, $previous, $candidate, $selected -ErrorAction Stop | Out-Null
$pageFiles = @('index.html', 'site.css', 'umicom-wordmark.svg', 'umicom.ico')
$pagePaths = $pageFiles | ForEach-Object { Join-Path $practicePage $_ }
Copy-Item -LiteralPath $pagePaths -Destination $stagedPage -ErrorAction Stop
```

The four copies go into `site` inside the new rehearsal folder. The original page stays available in `public`. If a copy fails, check that you opened PowerShell in `web-servers-lab` and completed the first lesson.

## 2. Create two archives with the same name

Give each release a different `release.txt`. Package the same page with each marker. A hash is a fingerprint of the file’s bytes. Record the SHA-256 hash of each archive so you can tell the two files apart.

```powershell
Set-Content -LiteralPath (Join-Path $previous 'release.txt') -Value 'practice-1' -Encoding ascii -ErrorAction Stop
Set-Content -LiteralPath (Join-Path $candidate 'release.txt') -Value 'practice-2' -Encoding ascii -ErrorAction Stop
$previousWar = Join-Path $previous 'btb-statement.war'
$candidateWar = Join-Path $candidate 'btb-statement.war'

jar --create --file $previousWar -C $stagedPage . -C $previous release.txt
if ($LASTEXITCODE -ne 0) { throw 'Could not build the previous archive.' }
jar --create --file $candidateWar -C $stagedPage . -C $candidate release.txt
if ($LASTEXITCODE -ne 0) { throw 'Could not build the candidate archive.' }

$previousHash = (Get-FileHash -LiteralPath $previousWar -Algorithm SHA256 -ErrorAction Stop).Hash
$candidateHash = (Get-FileHash -LiteralPath $candidateWar -Algorithm SHA256 -ErrorAction Stop).Hash
"Package bytes differ $($previousHash -ne $candidateHash)"
```

```text
Package bytes differ True
```

The archives have different contents even though each is named `btb-statement.war`. The exact hash will depend on the archive you built. Use the two hashes you just calculated for the copy checks.

## 3. Verify the upgrade, then the rollback

Copy the candidate into `selected` and check the copy. Then put the previous archive in the same place and repeat the check. The helper extracts only `release.txt` into a fresh folder each time, so each result comes from the archive just selected.

```powershell
function Read-RehearsalRelease([string]$archivePath) {
    $inspection = Join-Path $rehearsal ('inspect-' + [Guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Path $inspection -ErrorAction Stop | Out-Null
    Push-Location -LiteralPath $inspection -ErrorAction Stop
    try {
        jar --extract --file $archivePath release.txt
        if ($LASTEXITCODE -ne 0) { throw 'Could not read the release file.' }
        Get-Content -LiteralPath 'release.txt' -ErrorAction Stop
    } finally {
        Pop-Location
    }
}

$selectedWar = Join-Path $selected 'btb-statement.war'
Copy-Item -LiteralPath $candidateWar -Destination $selectedWar -ErrorAction Stop
$selectedHash = (Get-FileHash -LiteralPath $selectedWar -Algorithm SHA256 -ErrorAction Stop).Hash
"Upgrade copy matches candidate $($selectedHash -eq $candidateHash)"
"Upgrade marker $(Read-RehearsalRelease $selectedWar)"

Copy-Item -LiteralPath $previousWar -Destination $selectedWar -Force -ErrorAction Stop
$selectedHash = (Get-FileHash -LiteralPath $selectedWar -Algorithm SHA256 -ErrorAction Stop).Hash
"Rollback copy matches previous $($selectedHash -eq $previousHash)"
"Rollback marker $(Read-RehearsalRelease $selectedWar)"
```

```text
Upgrade copy matches candidate True
Upgrade marker practice-2
Rollback copy matches previous True
Rollback marker practice-1
```

If a hash check shows `False` or a marker differs, compare the source path in `Copy-Item` with the two folders you created. The previous and candidate archives remain available for another check.

## 4. Check a release on a practice server

For a later practice deployment, include a `release.txt` marker in the application files before you build each archive. Start the deployment check with the archive hash. After the server finishes the change, check the release marker served under the application’s context path. In the `/btb-statement` example, that would be `/btb-statement/release.txt`. Compare its response body with the marker you expected, then check the application routes for that release. Repeat both response checks after a rollback.

The archives in this rehearsal contain the static page and its assets. Use the application archive from the deployment lessons when you need to check their Java servlet.

[Previous lesson](20-keep-links-inside-an-application-context.md) · [Course index](index.md) · [Next lesson](22-read-which-methods-a-web-route-allows.md)
