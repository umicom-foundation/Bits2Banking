# Video 8 — From Markdown to a working website

**Duration:** Approximately 12–16 minutes

**Related reading:** [Prepare a reliable website build environment](../../lessons/05-engineering/43-prepare-a-website-build-environment.md)

## Opening: 0:00–1:30

**Narration:**

When you read an educational webpage, you see formatted text, pictures, menus and links. The author may have written the chapter in Markdown rather than HTML. A publishing tool turns that source into a website. Today we will build Bits to Banking on Windows and use a small C program to serve it locally.

**On screen:** Show a Markdown lesson beside its rendered page in a browser. Point to `content/`, `mkdocs.yml` and `site/` in the repository tree.

## Two separate jobs: 1:30–3:30

**Narration:**

Building and serving are different jobs. The builder reads the source and produces HTML. The server waits for browser requests and sends already-built files back. A server that starts correctly cannot make missing HTML appear; likewise, a successfully built website does not automatically start listening on a network port.

**On screen:** Show `content/index.md → MkDocs → site/index.html → C23 server → browser`. Pause at each arrow and open the corresponding folder or executable.

## The interpreter problem: 3:30–6:30

**Narration:**

Windows can contain several Python installations. Umicom developers often use MSYS2 UCRT64, whose `bin` folder contains a Python interpreter. If that interpreter does not have MkDocs, you may see `No module named mkdocs`. This means the selected Python environment is missing a dependency; it does not mean the C web server is broken.

**On screen:** In PowerShell, run `Get-Command python -All`. Create the repository's `.venv` using `py -3 -m venv .venv`. Install the documented requirements using `.venv\Scripts\python.exe -m pip install -r requirements-docs.txt`.

## Build and preview: 6:30–10:30

**Narration:**

We will deliberately call the virtual environment's Python by its full path so the result does not depend on shell activation. After checking the MkDocs version, build in strict mode. Look for `site/index.html`. Now return to the Umicom Applications repository and build the native education command. Ask it to inspect the environment, build the website and start the loopback preview on port 8765.

**On screen:** Follow the exact commands from the written lesson. Open the Bits to Banking home page and navigate to *Islam: Blueprint for Life* and the C programming lessons.

## Investigating problems: 10:30–13:30

**Narration:**

Errors are evidence. If MkDocs reports a missing page, check the source path and navigation entry. If the server reports that the site was not built, return to the build stage. If the port is in use, choose a different unused local port. Do not delete historical chapters or suppress errors to make a failing build appear successful.

**On screen:** Show the error table from the written lesson and the path `site/index.html`. Demonstrate Ctrl+C to stop the server.

## Closing: 13:30–15:00

**Narration:**

We have used four tools with four responsibilities: Markdown for source text, MkDocs for website generation, C23 for the local web server, and the browser for display. The next lesson applies the same separation to book publishing, where a manifest determines which chapters form a complete volume.

**On screen:** Display the lesson URL, Umicom Framework repository and Bits2Banking repository. End on the next lesson link.
