![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom icon](../../../../assets/branding/umicom.ico)

# Compare a recorded artifact with current bytes

[Previous lesson](qualify-an-exact-test-exit.md)

A SHA-256 digest is a fixed-length text representation derived from file bytes. It helps decide which artifact a previous observation describes.

A filename is a location. Its contents can change while the location stays identical. For repeatable build evidence, retain the expected digest alongside the build and test record, then compute a separate observed digest when inspecting a later artifact.

The C function first checks spelling. Both values must contain exactly 64 lowercase hexadecimal digits. This rejects missing, short or malformed records separately from correctly formed digests for different bytes. A test uses an intentionally changed build-local sample to demonstrate the difference.

The wrapper computes each SHA-256 with the build tool. The C example does not read or hash the file itself. This separation makes the interface clear. A caller needs a trusted source of expected values and a reproducible procedure for observing the current bytes.

Keeping a build result means retaining the preset or configuration, the exact selected file and its observed digest, and the process result. If the next build emits a new file, the older test remains evidence for the earlier artifact. Run a new check before attributing its result to the new file.

Run the rebuilt case and then inspect the generated artifact. Write down what the program observed and why the regression passed. A valid mismatch occurred, which was the expected result. A digest match alone establishes neither a publisher signature nor a successful runtime test.

## Repeat the exercise

```powershell
ctest --test-dir build/studio-evidence --output-on-failure -V -R "^bits[.]studio[.]evidence[.]rebuilt$"
Get-FileHash -Algorithm SHA256 build/studio-evidence/fixtures/rebuilt-artifact.txt
```

The test observes exit 2 and the message evidence differs. The PowerShell command prints the current file digest. PowerShell normally displays uppercase hex while this practice program expects lowercase text.

The rebuilt case owns that fixture inside its build directory. If it has not run, invoke the named test first. Do not replace a stored digest merely to make a comparison pass. Review the new bytes independently before recording a new baseline.

[Back to course](../../../../courses/framework-and-finance/studio-workflows/index.html)

[Next lesson · Read a 32-bit debugger status](read-a-32-bit-debugger-status.md)
