<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/18-serve-two-apache-sites-on-one-port.md

PURPOSE:
Use Apache’s configuration listing to follow two site names to separate document roots.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Serve two Apache sites on one port

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Two practice sites can share the same server and port. Give each site a name and a folder. Then check that Apache sends a different page when the request names the other site.

Start with [Serve files with Apache HTTP Server](03-serve-files-with-apache-http-server.md). Use its separate practice installation on port 8180. Stop that console instance before editing its configuration.

## 1. Make two practice folders

Open PowerShell and copy the earlier page with its stylesheet and brand assets into two folders.

```powershell
$lab = Join-Path $env:USERPROFILE 'web-servers-lab'
$north = Join-Path $lab 'north-site'
$annex = Join-Path $lab 'annex-site'
New-Item -ItemType Directory -Force -Path $north, $annex
$original = @(Get-ChildItem -LiteralPath "$lab/public" -File |
    Where-Object Name -in @('index.html', 'site.css', 'umicom-wordmark.svg', 'umicom.ico'))
if ($original.Count -ne 4) { throw 'Complete the page and stylesheet exercise first.' }
$original | Copy-Item -Destination $north
$original | Copy-Item -Destination $annex
$north.Replace('\','/')
$annex.Replace('\','/')
```

Open the two new `index.html` files in the editor. Set the visible heading in one to **North branch notice** and in the other to **Annex branch notice**. Save both, then copy the printed paths for the configuration.

## 2. Name both sites

In your practice Apache folder, add `conf/extra/umicom-sites.conf` with the following text. Replace each sample folder path with the printed path for that site.

```apache
<VirtualHost 127.0.0.1:8180>
    ServerName north.example.test
    DocumentRoot "C:/Users/YourName/web-servers-lab/north-site"
    <Directory "C:/Users/YourName/web-servers-lab/north-site">
        Options -Indexes
        AllowOverride None
        Require local
    </Directory>
</VirtualHost>

<VirtualHost 127.0.0.1:8180>
    ServerName annex.example.test
    DocumentRoot "C:/Users/YourName/web-servers-lab/annex-site"
    <Directory "C:/Users/YourName/web-servers-lab/annex-site">
        Options -Indexes
        AllowOverride None
        Require local
    </Directory>
</VirtualHost>
```

Open the practice `conf/httpd.conf`. Keep its single active `Listen 127.0.0.1:8180` line and add this include at the end.

```apache
Include conf/extra/umicom-sites.conf
```

Each `VirtualHost` block describes one site. `ServerName` is the name used in the request. `DocumentRoot` is the directory where Apache starts looking for its pages.

## 3. Check the syntax and the site list

Set `$apache` to the same extracted practice installation you used earlier.

```powershell
$apache = 'C:/learning/Apache24'
& "$apache/bin/httpd.exe" -d $apache -f 'conf/httpd.conf' -t
& "$apache/bin/httpd.exe" -d $apache -f 'conf/httpd.conf' -S
```

The first command should show `Syntax OK`. In the second output, find both names under the same address and port. If either is missing, confirm the include line points to the file you saved.

## 4. Request each site

Start the practice instance in its window.

```powershell
& "$apache/bin/httpd.exe" -d $apache -f 'conf/httpd.conf'
```

In another PowerShell window, send both requests to the same local address. The Host header carries the name that Apache should look up.

```powershell
curl.exe --noproxy 127.0.0.1 --fail --silent --show-error -H 'Host: north.example.test:8180' http://127.0.0.1:8180/index.html
curl.exe --noproxy 127.0.0.1 --fail --silent --show-error -H 'Host: annex.example.test:8180' http://127.0.0.1:8180/index.html
```

Confirm that each response contains its own heading. On this address and port, a name that matches neither site uses the first listed site. If both results show the first heading, compare the name you typed with the spelling printed by `-S`. A 403 means you should check the matching directory block, and a 404 means you should check that site's folder for `index.html`.

Press Ctrl+C in the Apache window when finished. [Apache name-based hosts](https://httpd.apache.org/docs/2.4/vhosts/name-based.html) · [Apache command options](https://github.com/apache/httpd/blob/2.4.x/docs/manual/programs/httpd.xml)

[Previous lesson](17-read-form-choices-in-native-c.md) · [Next lesson](19-tell-which-apache-site-answered.md) · [Web server course](index.md)
