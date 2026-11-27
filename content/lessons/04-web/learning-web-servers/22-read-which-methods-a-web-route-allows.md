<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/22-read-which-methods-a-web-route-allows.md

PURPOSE:
Read which methods a web route allows

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read which methods a web route allows

A request names the action and the path. `GET /handout.txt` asks to read your practice handout. `POST /handout.txt` asks that same path to handle a submission. You will run a small C23 program that calls the existing Umicom Framework file handler and prints what it returns for each request.

## 1. Prepare the exercise

1. Start PowerShell in your C development environment. Check that your C23 compiler, CMake and Ninja are available. You also need an installed Umicom Framework SDK with its web target.
2. Save [read_route_methods.c](../../../labs/web-method-response/read_route_methods.c) and [CMakeLists.txt](../../../labs/web-method-response/CMakeLists.txt) together in a fresh practice folder. Open that folder in PowerShell.
3. Create a site folder with one text file. Keep `missing.txt` absent for the final comparison.

```powershell
New-Item -ItemType Directory -Name site
Set-Content -LiteralPath .\site\handout.txt -Value 'Practice handout.'
$siteRoot = (Resolve-Path -LiteralPath .\site).Path
```

The first two commands create one file for the handler to find. The final command records the full folder path.

## 2. Build and run the C23 example

Run each command after the previous one succeeds. Supply the installation folder you normally use for the Framework SDK when prompted.

```powershell
$sdkRoot = Read-Host 'Full path of the installed Umicom Framework SDK'
cmake -S . -B build -G Ninja "-DCMAKE_PREFIX_PATH=$sdkRoot"
cmake --build .\build
.\build\read-route-methods.exe $siteRoot
```

The program calls the handler directly in the same process for each practice request.

Expect these rows.

```text
GET /handout.txt 200 -
HEAD /handout.txt 200 -
POST /handout.txt 405 GET, HEAD
GET /missing.txt 404 -
```

Each row lists the method, path, status and optional `Allow` header in order. A dash marks a response where this header is absent. `HEAD` asks for the metadata a normal read would return. An HTTP server sends only the response headers for HEAD.

## 3. Explain the refusal

1. Find the row with status `405`. The handler knows `POST` and refuses it for this file route. The `Allow` field lists the two methods the route handles.
2. Find the `404` row. `GET` is accepted on the file route, and this specific file is absent.
3. Create `missing.txt` and run the program again to check your explanation.

```powershell
Set-Content -LiteralPath .\site\missing.txt -Value 'Another practice handout.'
.\build\read-route-methods.exe $siteRoot
```

The last row now shows `GET /missing.txt 200 -`. The `POST` row still reports `405` with `GET, HEAD`.

If CMake cannot find the SDK, check that the installation folder contains the Framework package. If the first `GET` returns `404`, check that the file is inside the folder printed by `$siteRoot`, and that it is named `handout.txt`.

## Use the result in Umicom

Keep the allowed actions in the route that owns them. The handler can then answer with its chosen status and allowed methods. A client can show a specific explanation based on both fields. Use the [missing page lesson](../../../courses/learning-web-servers/lessons/13-set-a-message-for-a-missing-page.html) to practise the distinct file-not-found response.

- [HTTP semantics for Allow](https://www.rfc-editor.org/rfc/rfc9110.html#name-allow)
- [HTTP semantics for 405](https://www.rfc-editor.org/rfc/rfc9110.html#name-405-method-not-allowed)

[Previous lesson](21-verify-a-web-archive-upgrade-and-rollback.md) · [Course index](index.md) · [Browser edition](../../../courses/learning-web-servers/lessons/22-read-which-methods-a-web-route-allows.html)
