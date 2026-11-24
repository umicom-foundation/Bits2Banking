<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/48-check-export-and-download-headers.md

PURPOSE:
Check export and download headers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check export and download headers

A file can hold numbers, a printable page or an archive containing several items. Its **media type** is the label a web server puts in the response header named `Content-Type`. Use one fictional export to check four labels before handing a course page to another reader. You can predict the labels on paper before using a preview.

## Draw the two columns on paper

Write the headings **label** and **amount_cents**. Write `demo` in the first column of the next row and `1250` in the second. Cents are whole numbers here. The label identifies the exercise and contains no account information.

CSV means **comma-separated values**. Each line is a row, and the comma marks the boundary between columns in this example.

~~~text
label,amount_cents
demo,1250
~~~

TSV means **tab-separated values**. The same two rows contain a tab character between the fields. A tab is one character even when your editor shows it as several spaces.

### 1. Choose a practice document root

Work in a private copy of an approved, branded Bits2Banking export. Its document root is the directory containing `index.html`. Use a practice copy with fresh names for all four files.

### 2. Create the two small tables

Open PowerShell. Enter the full absolute path to the practice document root at the prompt. The commands insert actual tabs in the TSV file.

~~~powershell
$ExportRoot = Read-Host 'Enter the full path to the practice document root'
Set-Content -LiteralPath (Join-Path $ExportRoot 'balances.csv') -Encoding ascii -Value @(
    'label,amount_cents'
    'demo,1250'
)
$Tab = [char]9
Set-Content -LiteralPath (Join-Path $ExportRoot 'balances.tsv') -Encoding ascii -Value @(
    "label${Tab}amount_cents"
    "demo${Tab}1250"
)
~~~

### 3. Add the two course downloads

In that same practice directory, place a genuine small course PDF named `lesson.pdf` and a genuine small offline archive named `offline-pack.zip`. Use approved learning material you have permission to serve. Give each resource its correct filename and format. The rooted preview’s ordinary response limit is 1 MiB per file.

## Read a HEAD response before downloading

An HTTP request tells the server which action you want and which path it should look up. **GET** returns the metadata and the representation bytes. **HEAD** ends after the metadata. The rooted preview can include a `Content-Length` giving the file length that the corresponding GET would send.

Use the local static preview built from the current Framework checkout. When you are ready to run your own preview, select the same practice directory in the first PowerShell window. Use the full executable path on Windows if the command is absent from your search path.

~~~powershell
umicom-web-local-service-example --port 8080 --root "$ExportRoot"
~~~

Once your practice preview is running, use a second PowerShell window for the following commands. `curl.exe --head` sends HEAD. The address `127.0.0.1` means this computer.

~~~powershell
$PracticeSite = 'http://127.0.0.1:8080'
curl.exe --head --show-error "$PracticeSite/balances.csv"
curl.exe --head --show-error "$PracticeSite/balances.tsv"
curl.exe --head --show-error "$PracticeSite/lesson.pdf"
curl.exe --head --show-error "$PracticeSite/offline-pack.zip"
~~~

Read the HTTP status line before looking at the headers. For these existing, small files in the current rooted preview, expect status `200`. Then compare `Content-Type` with the table. The name on the left of the colon identifies the header. The value on the right names the media type.

| Resource | Expected Content-Type value |
| --- | --- |
| `balances.csv` | `text/csv` |
| `balances.tsv` | `text/tab-separated-values` |
| `lesson.pdf` | `application/pdf` |
| `offline-pack.zip` | `application/zip` |

~~~text
SEND HEAD for the practice file
READ the status line
IF the status is not 200, RECORD it and CHECK the file or route
OTHERWISE, READ Content-Type
COMPARE the declared media type with the expected value
RECORD the file name, status and media type
~~~

The type describes what the server has declared. A separate file check confirms that the spreadsheet importer reads the correct delimiter or that the course PDF or ZIP opens in a tool you trust. A matching header by itself does not prove that the format is valid.

## Practise finding a mismatch

1. Predict the result for a fresh practice copy named `balances.csv.backup`. The final suffix is `.backup`, so this preview declares its usual fallback `application/octet-stream`. The comma or tab characters in the stored text stay as they were.
2. If a requested file returns `404`, first check the exact name and the selected document root. If a file is too large for the ordinary preview, choose a smaller course resource before retrying. If the preview returns the fallback type for one of the four named formats, check the actual final suffix and that the running copy contains the current media type registry.
3. Write a four-row check result for a practice Umicom TMS export page or a Bits2Banking download page. Keep the observed header and any separate file check as two pieces of evidence.

[HTTP HEAD semantics](https://www.rfc-editor.org/rfc/rfc9110.html#section-9.3.2) · [IANA media type registry](https://www.iana.org/assignments/media-types/)

[Course contents](index.md) · [Previous lesson · Read media types from filename extensions](47-read-media-types-from-filename-extensions.md) · [Related lesson · Request a single byte range](44-request-a-single-byte-range.md) · [Umicom WebServer practice guide](../../../umicom/native-statement-web-lab.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/48-check-export-and-download-headers.html)

[Next lesson · Read status codes before deciding what to do](49-read-status-codes-before-deciding.md)
