<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/03-serve-files-with-apache-http-server.md

PURPOSE:
Configure and observe a local Apache HTTP Server instance serving the practice page.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Serve files with Apache HTTP Server

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

Apache HTTP Server, also called `httpd`, listens for HTTP requests. With a document root set to your practice folder, it can read and send its HTML, CSS and images as static files. The document root is the starting directory for paths served by that configuration.

## Prepare a Windows practice copy

1. Complete [the page exercise](01-make-a-page-and-stylesheet.md). Check that `index.html`, `site.css`, `umicom-wordmark.svg` and `umicom.ico` are in `public`.
2. Use a recent Apache HTTP Server 2.4 Windows ZIP from a distributor listed on the [Apache binary packages page](https://downloads.apache.org/httpd/binaries/). The Apache project publishes source releases, and the binary providers list their own runtime requirements. Follow the selected provider's verification and prerequisite instructions. Unpack into a new directory for this exercise and use a copy that is independent of any existing Apache service.
3. In PowerShell, set `$apache` to your extracted folder, the one containing `bin\httpd.exe` and `conf\httpd.conf`. The example path is a placeholder you can replace.

    ```powershell
    $lab = Join-Path $env:USERPROFILE "web-servers-lab"
    $apache = "C:\learning\Apache24"
    Test-Path "$apache\bin\httpd.exe"
    Test-Path "$apache\conf\httpd.conf"
    $apache.Replace('\','/')
    "$lab/public".Replace('\','/')
    ```

    The first two results should be `True`. Copy the two paths printed below them for the configuration.

4. Open the practice copy of `conf\httpd.conf`. If it defines `SRVROOT`, update its quoted value to the Apache folder printed above. Otherwise update the quoted `ServerRoot` value. Keep the bundle's loaded modules and its existing log configuration. Replace the active `Listen` value with `127.0.0.1:8180` and leave any example listeners commented. Set `ServerName` to `127.0.0.1:8180`. Update the old document root and its matching directory block to use your printed `public` path. The selected directives will resemble this configuration.

    ```apache
    Listen 127.0.0.1:8180
    ServerName 127.0.0.1:8180
    DocumentRoot "C:/Users/YourName/web-servers-lab/public"
    <Directory "C:/Users/YourName/web-servers-lab/public">
        Options -Indexes
        AllowOverride None
        Require local
    </Directory>
    ```

    `Listen` makes the server bind to this computer's loopback address. `Require local` sets the access rule for this folder. `Options -Indexes` prevents Apache generating a directory listing if an index page is missing. Use the exact printed path in both quoted places. Keep the server configuration and logs outside the public folder.

## Check, run and stop

1. Test the configuration in PowerShell.

    ```powershell
    & "$apache\bin\httpd.exe" -d $apache -f "conf/httpd.conf" -t
    ```

    Expect `Syntax OK`. If the test reports a file and line, reopen the configuration at that line. A configuration syntax check does not check whether the port is already occupied.

2. Start the practice server in the current terminal and leave that window open.

    ```powershell
    & "$apache\bin\httpd.exe" -d $apache -f "conf/httpd.conf"
    ```

3. From a second PowerShell window, request the page and stylesheet.

    ```powershell
    curl.exe -i http://127.0.0.1:8180/index.html
    curl.exe -I http://127.0.0.1:8180/site.css
    ```

    Expect both to return `200`. Open `http://127.0.0.1:8180/index.html` in a browser and compare it with the earlier file view.

4. In the Apache window, press **Ctrl+C** to stop this console instance. Request the page again to confirm the practice listener has stopped.

If the address is already in use, choose another unused local port and change it in `Listen`, `ServerName` and each URL. If Apache starts but returns `403`, check the matching `<Directory>` path and rule. If it returns `404`, check the document root and filename.

[Apache on Windows](https://httpd.apache.org/docs/2.4/platform/windows.html) · [Listening addresses](https://httpd.apache.org/docs/2.4/bind.html) · [DocumentRoot](https://httpd.apache.org/docs/2.4/mod/core.html#documentroot) · [httpd command options](https://httpd.apache.org/docs/2.4/programs/httpd.html)

[Previous, read an HTTP exchange](02-read-an-http-exchange.md) · [Course](index.md) · [Next, deploy a Java web archive on Tomcat](04-deploy-a-war-on-tomcat.md)
