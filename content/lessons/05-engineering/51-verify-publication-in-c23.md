# 51. Verify a published website using C23 and SHA-256

A website build can complete without errors and still contain missing, unexpected or altered files. Before publication, it is useful to record exactly what was built. The Umicom Education tool creates a **manifest**: a text file recording the SHA-256 digest of each regular file in the generated website.

A digest is a short result calculated from the contents of a file. If a file's bytes change, the SHA-256 value will almost certainly change. This helps detect unintended differences, but it is not a digital signature and does not prove who created the file.

## 1. Inspect the output before recording it

After building the combined website, open PowerShell in the Applications repository:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
```

Create a manifest:

```powershell
& $Education publish manifest --repo $Books
```

The command walks the `site/` directory, reads files in bounded chunks and uses **the Framework's existing SHA-256 implementation**. It writes a sorted list into `output/native-publication/site.sha256`.

A typical line resembles:

```text
ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad  index.html
```

This example hash is the SHA-256 of the three-byte text `abc`; your real home page will have a different digest. The double space separates the 64 hexadecimal digits from the relative filename.

## 2. Verify the same website

Run the read-only verification command:

```powershell
& $Education publish verify --repo $Books
```

The tool checks the full generated directory again. It rejects missing files, added files, changed content and symbolic links or junctions. It does not rebuild, repair or upload anything.

Try the same commands again without changing any files. The manifest operation should recognise that the stored inventory is already identical.

## 3. Understand a refused change

Change a practice copy of a generated HTML page, not a real publication. Run `publish verify` again. It should fail because the current file no longer matches the recorded digest.

Now try `publish manifest` without `--refresh`. The tool refuses to replace a different manifest automatically. Review the changed files, restore or rebuild the intended website and confirm the change. Only then use:

```powershell
& $Education publish manifest --repo $Books --refresh
& $Education publish verify --repo $Books
```

The `--refresh` option changes the **manifest**, not the website source. It does not approve the change on your behalf or upload anything to GitHub.

## 4. Read the C23 implementation

Open [the publication service](https://github.com/umicom-foundation/umicom-framework/blob/main/src/education/publication.c) and [its public contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/education/publication.h).

Look for three responsibilities. The scanner enumerates ordinary files below `site/`. The digest reader feeds the existing `UmiSha256Update` interface with chunks instead of loading a whole document into memory. The verifier compares the complete ordered inventory with the recorded manifest.

Find the `PubFree` function. Explain why every filename allocated while collecting entries must be freed, including when reading fails. Find the code that refuses a changed manifest unless refresh has been selected. Explain which files the operation may write.

## 5. Build and test the native implementation

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" `
    -R "framework.education.publication_manifest" --output-on-failure
```

The test uses disposable files. It checks identical outputs, changed bytes, additional files, refusal to overwrite a differing manifest and, where the platform supports it, refusal of symlinks. It must not change any of your real books.

## 6. Apply this idea elsewhere

A build can record hashes for installer files, data exports, generated reports or other outputs. Checksums can detect accidental alterations, but release authenticity also requires a trusted signing and verification process.

[Continue to GitHub Actions and publishing](52-one-github-pages-deployment.md).
