# Check an Apache configuration copy

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Check a working configuration, see what happens when one setting has no value, then check a repaired copy. Use the Windows practice download from [Serve files with Apache HTTP Server](03-serve-files-with-apache-http-server.md). Finish that lesson through `Syntax OK` and stop its practice server before starting here.

## Check a copy of the working settings

1. Open PowerShell and set `$apache` to your extracted practice folder. Change the example path if yours is elsewhere.
2. Enter these lines in order. If `syntax-practice` already exists, use a new folder name before copying.

```powershell
$apache = 'C:\learning\Apache24'
$practice = Join-Path $apache 'syntax-practice'
New-Item -ItemType Directory -Path $practice -ErrorAction Stop
$good = Join-Path $practice 'working.conf'
Copy-Item -LiteralPath "$apache\conf\httpd.conf" -Destination $good
& "$apache\bin\httpd.exe" -d $apache -f $good -t
$LASTEXITCODE
```

You should see `Syntax OK` from Apache and `0` from PowerShell. `-d` sets the starting server root for relative paths. `-f` names the configuration copy. `-t` reads its settings and exits after checking them.

## Find a missing value

1. Make another copy and add `ServerName` on its own line without a value.
2. Run the same check with this filename. Read the filename, line and directive Apache reports.

```powershell
$faulty = Join-Path $practice 'missing-value.conf'
Copy-Item -LiteralPath $good -Destination $faulty
Add-Content -LiteralPath $faulty -Value '', 'ServerName'
& "$apache\bin\httpd.exe" -d $apache -f $faulty -t
$LASTEXITCODE
```

A missing value gives a syntax error and a nonzero exit code. Keep this file so you can compare the reported line with the repaired copy.

## Recheck the repaired settings

1. Copy the known working settings to `repaired.conf`.
2. Check that copy and compare the result with the missing-value version.

```powershell
$repaired = Join-Path $practice 'repaired.conf'
Copy-Item -LiteralPath $good -Destination $repaired
& "$apache\bin\httpd.exe" -d $apache -f $repaired -t
$LASTEXITCODE
```

Expect `Syntax OK` and `0` again. A syntax check is one part of preparing a server configuration. After an actual start or reload, an HTTP check can confirm that the expected site responds on its configured port. The same difference matters in Umicom Webserver when a candidate configuration is checked before applying it.

[Return to the Web Servers course](index.md) · [Read an HTTP exchange](02-read-an-http-exchange.md) · [Apache httpd command reference](https://httpd.apache.org/docs/2.4/en/programs/httpd.html)
