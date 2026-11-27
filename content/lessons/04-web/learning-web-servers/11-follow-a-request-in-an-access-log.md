<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/11-follow-a-request-in-an-access-log.md

PURPOSE:
Read a simple request and status from a practice access log.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for the original lesson. Linked references retain their own terms.
-->

# Follow a request in an access log

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg)

An access log records the request a web server received and the result it returned. Find a single request in a practice log and compare it with the request you meant to make. This works in PowerShell without starting a web server.

## 1. Write three practice records

Open PowerShell in the practice folder you created for this course. Copy the entire block, including the first and last lines. It creates a practice file with three fictional requests.

```powershell
$accessSample = @'
127.0.0.1 - - [20/Nov/2026:14:00:01 +0000] "GET /statement/summary HTTP/1.1" 200 32
127.0.0.1 - - [20/Nov/2026:14:00:03 +0000] "GET /statements/summary HTTP/1.1" 404 16
127.0.0.1 - - [20/Nov/2026:14:00:05 +0000] "GET /statement/summary HTTP/1.1" 200 32
'@
Set-Content -LiteralPath practice-access.log -Value $accessSample
```

Type `Get-Content -LiteralPath practice-access.log`. You should see three lines. The request appears inside quotes. The first number after the closing quote is the HTTP status. The second number is the size of the response body in bytes.

## 2. Find the request that returned 404

```powershell
Select-String -LiteralPath practice-access.log -SimpleMatch '" 404 '
```

The result shows line 2. Its path is `/statements/summary`, with an extra **s**. The successful requests use `/statement/summary` and return 200. In a real application, compare the requested path with the route the application serves. The access log gives you the exact request to check.

## 3. Check the successful route

```powershell
Select-String -LiteralPath practice-access.log -SimpleMatch '"GET /statement/summary HTTP/1.1" 200 '
```

The result shows lines 1 and 3. Add one similar successful line to your practice file and repeat the command. It should now find three successful requests.

## 4. Find where your own server records requests

- Apache HTTP Server uses `CustomLog` to select an access log and its format. If the configured path is relative, look under Apache’s `ServerRoot`. [Apache access log](https://httpd.apache.org/docs/2.4/logs.html#accesslog)
- Tomcat uses an Access Log Valve. Its configured `directory` is relative to `CATALINA_BASE` unless it is written as an absolute path. The log can be buffered, so the newest record may take time to appear. [Tomcat Access Log Valve](https://tomcat.apache.org/tomcat-11.0-doc/config/valve.html#Access_Log_Valve)
- In JBoss EAP 8.1, the Undertow host controls access logging. Start by checking the host’s access-log directory and pattern in your approved local configuration. [JBoss EAP host access logging](https://docs.redhat.com/en/documentation/red_hat_jboss_enterprise_application_platform/8.1/html/configuration_guide/reference_material)

If a search finds nothing in a real log, first confirm that the selected log is for the server that answered your request. Check that access logging is enabled and that the current format records the path and status. Use your practice file when sharing an example. Live logs can include addresses and details of requests.

[HTTP request and response](02-read-an-http-exchange.md) · [Previous lesson](10-choose-the-servlet-api-for-your-server.md) · [Course index](index.md)
