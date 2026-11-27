<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/16-send-a-read-only-choice-with-a-form.md

PURPOSE:
Teach how named HTML controls produce a query on a read-only GET request.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Send a read-only choice with a form

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Choose a site and a report period. The browser puts both choices in the address, where you can read them or copy a link to the same selection.

Start with [Read an HTTP request and response](02-read-an-http-exchange.md). You need a practice folder, a browser and the local C example used in [Serve an XHTML document](15-serve-an-xhtml-document.md).

## 1. Save the two pages

Open PowerShell in your practice folder and create the two folders the pages use.

```powershell
New-Item -ItemType Directory -Force labs/web-statement-site, assets/branding
```

Save the [choice form](../../../labs/web-statement-site/query-form.html) as `labs/web-statement-site/query-form.html` and the [result page](../../../labs/web-statement-site/query-result.html) as `labs/web-statement-site/query-result.html`. Put the approved `umicom-wordmark.svg` and `umicom.ico` in `assets/branding`. Use the same assets as [the first website exercise](01-make-a-page-and-stylesheet.md).

Serve the practice folder on port 8093 with the local C example from the previous lesson. Open `http://127.0.0.1:8093/labs/web-statement-site/query-form.html` in your browser.

## 2. Read the form before submitting it

Open the form source in a text editor and find these attributes.

- `action="query-result.html"` gives the browser the next file to request.
- `method="get"` keeps this choice in the address.
- The two controls have `name` values `site` and `period`. Each name is paired with the selected value in the address.
- Each `label` names the matching control with its `for` attribute. Select the label or press Tab to find the control without guessing what it does.

## 3. Make two choices and compare the addresses

Choose **North Office**, leave **This week** selected and press **Open review page**. The address ends with:

```text
query-result.html?site=North+Office&period=week
```

The question mark starts the query. The ampersand separates the two choices. In this form encoding, the plus sign stands for a space.

Go back. Choose **North + Annex** and **This month**, then submit the form again. The address now ends with:

```text
query-result.html?site=North+%2B+Annex&period=month
```

The browser writes a literal plus as `%2B`. See how it differs from the plus signs for spaces.

## 4. Check what the result actually proves

Both choices open the same result document. The static page shows how to read the address. It has no report selection logic. In an application, code would read the `site` and `period` parameters and choose the matching report.

If you serve the two pages with the local C example, you can compare the responses directly.

```powershell
$first = curl.exe --fail --silent --show-error 'http://127.0.0.1:8093/labs/web-statement-site/query-result.html?site=North+Office&period=week'
if ($LASTEXITCODE -ne 0) { throw 'The first request failed.' }
$second = curl.exe --fail --silent --show-error 'http://127.0.0.1:8093/labs/web-statement-site/query-result.html?site=North+%2B+Annex&period=month'
if ($LASTEXITCODE -ne 0) { throw 'The second request failed.' }
($first -join "`n") -ceq ($second -join "`n")
```

Expect `True`. If a request returns 404, check that the server root contains `labs/web-statement-site/query-result.html` and that the port and file name match. URLs can be retained in history or logs. Use public filter choices in this exercise and keep passwords and private values out of the query.

The HTML standard describes [form controls and their names](https://html.spec.whatwg.org/multipage/forms.html#forms). The URL standard describes [form encoding](https://url.spec.whatwg.org/#application/x-www-form-urlencoded).

[Previous lesson](15-serve-an-xhtml-document.md) · [Next lesson](17-read-form-choices-in-native-c.md) · [Web server course](index.md)
