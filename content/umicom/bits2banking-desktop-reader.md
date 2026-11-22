# Read Bits2Banking courses offline

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

[Umicom icon](../assets/branding/umicom.ico)

The Bits2Banking desktop reader uses the same Umicom Framework Learning Catalogue as Studio IDE. Each offline pack lists its guide and lesson files together with their checksums. Keep the complete library together so the catalogue can verify the selected files before opening them.

1. Open the standalone reader. For a source build, use `apps/desktop/README.md` in the Bits2Banking checkout to locate the required Framework SDK and build the executable.
2. In the catalogue, choose the absolute library folder that contains `content` and `learning-packs`. Enter one of the manifest paths below and load the library.
3. Open the course guide, then follow its numbered lessons. You can read the web lesson or its Markdown manuscript in the desktop catalogue. Use the exercise's own compiler, database or browser when it asks you to run a sample.

| Course | Relative path to type in the catalogue |
| --- | --- |
| [Umicom C and C23](../courses/native-statement-calculations/index.html) | `learning-packs/native-statement-calculations.json` |
| [SQL](../courses/sql-statement-reconciliation/index.html) | `learning-packs/sql-statement-reconciliation.json` |
| [Accessible web development](../courses/accessible-statement-review/index.html) | `learning-packs/accessible-statement-review.json` |
| [Go](../courses/go-statement-tools/index.html) | `learning-packs/go-statement-tools.json` |

With `umicom-bits2banking.exe` on `PATH`, you can also select a pack at startup from PowerShell. Replace the library path with your own checkout path.

```powershell
umicom-bits2banking.exe --root 'C:/umicom/Umicom-Bits2Banking' --manifest 'learning-packs/native-statement-calculations.json'
```

If the catalogue reports a missing file, check that you selected the library folder above both `content` and `learning-packs`. If it reports a checksum mismatch, use the lesson and manifest from the same reviewed version of the library.
