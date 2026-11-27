<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/19-tell-which-apache-site-answered.md

PURPOSE:
Identify the Apache virtual host that handled a request using a shared practice access log.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Tell which Apache site answered

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

In [lesson 18](18-serve-two-apache-sites-on-one-port.md), North and Annex each have their own document root, the folder where Apache looks for pages. Both sites use `/index.html`. When the sites share an access log, read the site name before deciding which folder to check. You can do the exercise entirely in PowerShell.

## 1. Find the field that identifies the site

If you still have the file from [lesson 11](11-follow-a-request-in-an-access-log.md), open PowerShell in that practice folder and read its first line.

```powershell
Get-Content -LiteralPath practice-access.log -TotalCount 1
```

The first row of the original exercise looks like this.

```text
127.0.0.1 - - [20/Nov/2026:14:00:01 +0000] "GET /statement/summary HTTP/1.1" 200 32
```

The line starts with the client's address. Apache's Common Log Format has no site-name field. If the practice logs for multiple sites use this format, look for separate log files or check whether a shared log adds a field for the site name.

An Apache `LogFormat` can put `%v` at the start of each line. `%v` prints the configured `ServerName` of the site that handled the request. Lesson 18 set `ServerName` to `north.example.test` and `annex.example.test`. This example format puts that name first and keeps the familiar fields from lesson 11. `%>s` records the final HTTP status.

```apache
LogFormat "%v %h %l %u %t \"%r\" %>s %b" site_access
```

## 2. Read three practice rows

Copy the whole block into one PowerShell session. Keep the closing `'@` at the start of its own line. These fictional rows use the format above. PowerShell keeps them in memory.

```powershell
$sample = @'
north.example.test 127.0.0.1 - - [27/Nov/2026:09:20:01 +0000] "GET /index.html HTTP/1.1" 200 412
annex.example.test 127.0.0.1 - - [27/Nov/2026:09:20:03 +0000] "GET /index.html HTTP/1.1" 404 196
annex.example.test 127.0.0.1 - - [27/Nov/2026:09:21:03 +0000] "GET /index.html HTTP/1.1" 200 419
'@
$rows = $sample -split '\r?\n'
```

Find the first space in each row. Everything before it is the site name. The commands below take that first field, group the names and print the number of rows in each group.

```powershell
$rows |
    ForEach-Object { ($_ -split ' ', 2)[0] } |
    Group-Object |
    Sort-Object Name |
    ForEach-Object { '{0}: {1}' -f $_.Name, $_.Count }
```

```text
annex.example.test: 2
north.example.test: 1
```

## 3. Follow the request on the site that answered

Print the Annex rows. The space after `annex.example.test` marks the end of the site name.

```powershell
$rows | Where-Object { $_.StartsWith('annex.example.test ') }
```

```text
annex.example.test 127.0.0.1 - - [27/Nov/2026:09:20:03 +0000] "GET /index.html HTTP/1.1" 404 196
annex.example.test 127.0.0.1 - - [27/Nov/2026:09:21:03 +0000] "GET /index.html HTTP/1.1" 200 419
```

At `09:20:03`, Annex returned 404 for `/index.html`. In the layout from lesson 18, check `annex-site/index.html` and Annex's `DocumentRoot`. The same path returned 200 on North, so looking only at North's page would miss the Annex result. At `09:21:03` the Annex request succeeded. These rows show when each result occurred. To find out what changed, check the site's files or configuration history.

If the filter gives no output for this sample, re-run the block that creates `$rows` in the same PowerShell session and compare the spelling of the site name. Before using the filter on a classroom log, follow Apache's `CustomLog` setting to the file and check which format it uses. The filter assumes the configured site name is at the start of the row, followed by a space.

[Apache manual on logging for virtual hosts](https://github.com/apache/httpd/blob/2.4.x/docs/manual/logs.xml) · [Apache `LogFormat` reference](https://github.com/apache/httpd/blob/2.4.x/docs/manual/mod/mod_log_config.xml)

[Previous lesson](18-serve-two-apache-sites-on-one-port.md) · [Next lesson](20-keep-links-inside-an-application-context.md) · [Course index](index.md)
