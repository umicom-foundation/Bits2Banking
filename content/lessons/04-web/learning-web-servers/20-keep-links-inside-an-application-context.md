<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/20-keep-links-inside-an-application-context.md

PURPOSE:
Compare page-relative and host-root links when an application has a context path.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Keep links inside an application context

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

A page can load its stylesheet on a site at `/` and lose it when the same page moves into an application. Check the address the link produces before looking for a missing file.

In [Make a web page and its stylesheet](01-make-a-page-and-stylesheet.md), `index.html` and `site.css` sit in the same folder. The [Tomcat deployment](04-deploy-a-war-on-tomcat.md) and [WildFly deployment](05-deploy-the-same-war-on-wildfly.md) put that page and stylesheet in `btb-statement.war`. In both examples `/btb-statement` is the context path, the part of the URL that identifies which application should handle the request.

## 1. Read the link on the page

```html
<link rel="stylesheet" href="site.css">
<a href="summary">Read the summary</a>
```

Both `href` values start in the directory of the page. The stylesheet sits beside `index.html`. The `summary` address asks the deployed application for the servlet response introduced in the Tomcat lesson.

A leading slash changes where the path starts. `href="/site.css"` starts at the host’s root, the first slash after the host name.

## 2. Calculate the addresses in PowerShell

Copy the whole block into PowerShell. `[Uri]::new` combines a base address and a link. `.AbsoluteUri` shows the resulting full address. These practice names end in `.test` and the commands only calculate text.

```powershell
$rootPage = [Uri]'http://reports.example.test/index.html'
$tomcatPage = [Uri]'http://tomcat.example.test/btb-statement/index.html'
$wildflyPage = [Uri]'http://wildfly.example.test/btb-statement/'

[Uri]::new($rootPage, 'site.css').AbsoluteUri
[Uri]::new($rootPage, '/site.css').AbsoluteUri
[Uri]::new($tomcatPage, 'site.css').AbsoluteUri
[Uri]::new($tomcatPage, '/site.css').AbsoluteUri
[Uri]::new($wildflyPage, 'site.css').AbsoluteUri
[Uri]::new($wildflyPage, 'summary').AbsoluteUri
```

```text
http://reports.example.test/site.css
http://reports.example.test/site.css
http://tomcat.example.test/btb-statement/site.css
http://tomcat.example.test/site.css
http://wildfly.example.test/btb-statement/site.css
http://wildfly.example.test/btb-statement/summary
```

## 3. Check the context path

The first two addresses agree because the page is at the root. Compare the third and fourth addresses. The link with no leading slash keeps `/btb-statement/`. The link starting with `/` asks for a stylesheet at the host root. The final two links start in the WildFly page’s directory. The final slash makes `btb-statement` part of that directory.

If your result drops `/btb-statement/`, check the leading slash in `href` and the page address you used as the base. When the page address ends with the application name, keep the final slash for a directory base or include the actual page name. A base ending in `/btb-statement` treats that last segment like a filename and replaces it with `site.css`.

[URI reference resolution examples](https://www.rfc-editor.org/rfc/rfc3986#section-5.4.1) · [Previous lesson](19-tell-which-apache-site-answered.md) · [Next lesson](21-verify-a-web-archive-upgrade-and-rollback.md) · [Course index](index.md)
