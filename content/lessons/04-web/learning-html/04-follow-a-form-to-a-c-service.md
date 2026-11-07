<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/04-follow-a-form-to-a-c-service.md

PURPOSE:
  Present "Follow a form to a C service" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow a form to a C service

An HTML form gathers named values and sends a request. The local web-service example serves a small page containing one. We will connect the visible field to the C callback that receives its bytes.

Source to open: `Umicom-Applications/framework/examples/web/local_service.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\Umicom-Applications\framework\examples\web\local_service.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../Umicom-Applications/framework/examples/web/local_service.c'
```

## Understand the idea

The form has method post and action /api/echo. The method describes the request operation; the action identifies its destination on the same server. The input name message becomes a key in the submitted data. A label explains a field to the reader. The required and maxlength attributes guide browser input, while the service remains responsible for admitting received requests.

```text
labelled input → POST /api/echo → request body → Echo → plain-text response
```

## Work through the lab

1. Find Home and read only the HTML strings first. Sketch the label, input and Send button. C's adjacent string literals become one response body.
2. Find the form's method, action and the input's name. On paper enter Hello world and predict message=Hello+world in ordinary form encoding.
3. Find Echo. It returns the request bytes as text/plain; it does not parse a message object, save a file or execute a command.
4. Compare the page request with the form submission: opening / displays HTML; posting to /api/echo displays encoded text. Write one check for each visible result.

## Expected result

The echo response retains the form-encoded body, including the field name. Seeing a plus sign in place of a space is expected for this form encoding.

## If the result differs

If source shows escaped quotes, remember you are reading a C string representing HTML. If a page opens as a local file, its action cannot reach this example server. Use the preceding service lesson's local launch instructions for executable practice.

## Explain it yourself

Does maxlength=200 guarantee that the server never receives a longer value?

<details>
<summary>Worked explanation</summary>

No. Another client can construct its own request. Browser guidance helps users, while server-side limits and validation protect the service boundary.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-html/lessons/04-follow-a-form-to-a-c-service.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](03-labels-and-form-checks.md) · [Course contents](index.md)

[Continue: Make a loading page understandable](05-buttons-status-and-a-loading-page.md)
