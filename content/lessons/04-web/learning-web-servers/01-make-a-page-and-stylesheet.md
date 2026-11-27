<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/01-make-a-page-and-stylesheet.md

PURPOSE:
Create and check a practice web page with separate HTML, CSS and supplied artwork.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Make a web page and its stylesheet

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

Make a page that shows the same practice result throughout this course. It represents a fictional statement with two entries. You can build it without a server.

## Create the files

1. Open PowerShell. Create a folder for this course, then open it in File Explorer.

    ```powershell
    $lab = Join-Path $env:USERPROFILE "web-servers-lab"
    New-Item -ItemType Directory -Path "$lab\public" -Force
    Invoke-Item "$lab\public"
    ```

2. Save the approved [Umicom SVG wordmark](../../../assets/branding/umicom-wordmark.svg) and [Umicom ICO icon](../../../assets/branding/umicom.ico) into that `public` folder. Use the two filenames shown in the HTML.
3. Open a text editor. Save the following as `index.html` in `public`. If the editor asks for a file type, choose **All files** so it keeps the `.html` extension.

    ```html
    <!doctype html>
    <html lang="en">
    <head>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <title>Statement practice</title>
      <link rel="icon" href="umicom.ico">
      <link rel="stylesheet" href="site.css">
    </head>
    <body>
      <main>
        <img src="umicom-wordmark.svg" width="220" alt="Umicom Foundation">
        <h1>Statement practice</h1>
        <p>Two entries reviewed.</p>
      </main>
    </body>
    </html>
    ```

4. In the same folder, save this as `site.css`.

    ```css
    body {
      font-family: "Segoe UI", sans-serif;
      color: #172d42;
      background: #f4f7fa;
    }

    main {
      max-width: 36rem;
      margin: 2rem auto;
      padding: 1.5rem;
      background: white;
    }

    img {
      max-width: 100%;
      height: auto;
    }
    ```

5. Open the saved page from PowerShell.

    ```powershell
    Invoke-Item "$lab\public\index.html"
    ```

You should see the Umicom wordmark, the heading **Statement practice** and **Two entries reviewed.** The address begins with `file:` because the browser opened a file on this computer.

## Change one thing

1. In `site.css`, change the body background from `#f4f7fa` to `#e4eff9`.
2. Save the stylesheet and refresh the page.
3. Check that the colour changes and that the heading and statement still say the same thing.

HTML describes the page's content and structure. CSS describes its presentation. JavaScript can add interactions when a page needs them.

If the browser shows the HTML as text, list the files with `Get-ChildItem "$lab\public" | Select-Object Name`. Check for `index.html.txt` or `site.css.txt` and correct the filename in your practice folder.

[Course](index.md) · [Next, read an HTTP exchange](02-read-an-http-exchange.md) · [More HTML](../learning-html/index.md) · [More CSS](../learning-css/index.md) · [Add JavaScript later](../learning-javascript/index.md)
