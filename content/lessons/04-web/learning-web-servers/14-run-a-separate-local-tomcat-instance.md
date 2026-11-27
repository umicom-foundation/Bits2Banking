<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/14-run-a-separate-local-tomcat-instance.md

PURPOSE:
Separate the Tomcat program files from one local instance's settings and applications.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Run a separate local Tomcat instance

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Suppose you want a place to try a deployment without changing the Tomcat files you normally use. Start a new local instance with its own configuration, applications and logs. Both instances can use the same Tomcat program files.

Use PowerShell 7, a JDK and the unpacked [Tomcat 11 Core ZIP](https://tomcat.apache.org/download-11.cgi). Build `btb-statement.war` using [the first Tomcat exercise](04-deploy-a-war-on-tomcat.md). Keep its full path handy.

## 1. Create the practice instance

Open PowerShell in the unpacked Tomcat directory. `Get-ChildItem -Name` should show `bin`, `conf` and `lib`. Run these commands using a new sibling directory called `tomcat-practice`.

```powershell
$env:CATALINA_HOME = (Get-Location).Path
$env:CATALINA_BASE = Join-Path (Split-Path -Parent $env:CATALINA_HOME) 'tomcat-practice'
New-Item -ItemType Directory -Path $env:CATALINA_BASE
Copy-Item -LiteralPath "$env:CATALINA_HOME/conf" -Destination "$env:CATALINA_BASE/conf" -Recurse
New-Item -ItemType Directory -Path "$env:CATALINA_BASE/logs", "$env:CATALINA_BASE/temp", "$env:CATALINA_BASE/webapps", "$env:CATALINA_BASE/work"
```

If the first `New-Item` says the folder already exists, choose a different unused name on the preceding line and try again. `CATALINA_HOME` supplies the program. `CATALINA_BASE` identifies this instance's working files. Keep these variables in this PowerShell window for the rest of the exercise.

## 2. Give the practice instance its own local address

Open the copy at `$env:CATALINA_BASE/conf/server.xml` in an editor. Find the active `Connector` that uses `protocol="HTTP/1.1"`. Change its port to `18080`, add `address="127.0.0.1"` and leave its other attributes in place. Your file should have an active opening element similar to this one.

```xml
<Connector port="18080" protocol="HTTP/1.1"
           address="127.0.0.1"
           connectionTimeout="20000" redirectPort="8443" />
```

Change the outer `Server` element's port from `8005` to `-1` and save the copy. This exercise runs Tomcat in the foreground so you can stop it from the same console. Leave the host's `appBase="webapps"` in place. A connector accepts connections for the named address and port. The address `127.0.0.1` keeps this exercise on your own computer. [Tomcat HTTP connector](https://tomcat.apache.org/tomcat-11.0-doc/config/http.html) · [Tomcat server configuration](https://tomcat.apache.org/tomcat-11.0-doc/config/server.html)

## 3. Add the web archive and check the configuration

Replace `C:/path/to/btb-statement.war` with the full path to your archive and run these commands.

```powershell
Copy-Item -LiteralPath 'C:/path/to/btb-statement.war' -Destination "$env:CATALINA_BASE/webapps/btb-statement.war"
& "$env:CATALINA_HOME/bin/catalina.bat" configtest
```

Check `$LASTEXITCODE` immediately after `configtest`. A zero means Tomcat finished its configuration check. It still needs to run and serve the application before you can confirm the deployment.

## 4. Start the classroom instance and look for two results

```powershell
& "$env:CATALINA_HOME/bin/catalina.bat" run
```

Leave that window running. In a second PowerShell window, request the application's page and its servlet.

```powershell
curl.exe -i http://127.0.0.1:18080/btb-statement/index.html
curl.exe -i http://127.0.0.1:18080/btb-statement/summary
```

Both requests should return HTTP 200. The first shows your statement page. The second shows `2 entries reviewed.` Return to the first window and press Ctrl+C to stop the practice instance. If the terminal asks you to confirm, follow the displayed prompt.

If the server reports that the address is in use, stop the practice command, choose another unused port in its own configuration file and update both URLs. If the application returns 404, check the copied archive filename and look for a deployment message in the first console or inside the practice `logs` folder.

An Umicom Webserver instance can follow the same design by keeping the executable separate from the selected configuration, content and logs. Two instances can then use different directories and addresses while sharing the same executable. [Tomcat running guide](https://tomcat.apache.org/tomcat-11.0-doc/RUNNING.txt)

[Previous lesson](13-set-a-message-for-a-missing-page.md) · [Next lesson](15-serve-an-xhtml-document.md) · [Web server course](index.md) · [Web development in simple steps](../../../simple-steps/course-guides/web-development-and-servers.md)
