# Review a Windows security detection

An antivirus quarantine, an application crash and a Windows reputation warning are different observations. Record the product name, exact detection name, file path and time before changing the build. A familiar filename is not proof that a binary is safe. A detection is also not proof that the source code is malicious.

## 1. Preserve evidence

Keep the original alert and build/test logs in a private local folder. Record the repository revision and whether there were uncommitted source changes. For a file that is still available, these PowerShell commands inspect it without launching it:

~~~powershell
Get-FileHash "C:\umicom\installed\applications\bin\umicom.exe" -Algorithm SHA256
Get-AuthenticodeSignature "C:\umicom\installed\applications\bin\umicom.exe" | Format-List Status,StatusMessage,SignerCertificate,TimeStamperCertificate
~~~

Substitute the exact affected file. SHA-256 identifies its bytes; it does not establish safety. NotSigned describes a signature state, not a malware verdict. If the file is quarantined or absent, record that fact rather than hashing a different rebuild and calling it the same artifact.

Do not change protection settings, exclude an entire development tree or rename executables to avoid detection. Keep quarantined files unexecuted while the cause is investigated.

## 2. Investigate the build

Confirm that source and dependencies came from the intended repositories. Inspect build commands, compiler paths, post-build steps and dependency revisions. Compare the binary's identity with the build that produced it. Keep test programs separate from the files intended for end-user installation.

A source review can identify suspicious operations or ordinary test behaviour, but it cannot prove that an unavailable executable exactly matches that source. Record unknown identities explicitly.

## 3. Request the vendor's review

McAfee provides an official [detection dispute and allowlisting form](https://www.mcafee.com/en-us/consumer-support/dispute-detection-allowlisting.html). Its form accepts reports from customers and software vendors. Supply the exact detection, affected file identity, compiler details and a concise explanation of the program's intended behaviour.

Only submit material you are authorised to share. A vendor submission transfers data outside your computer. Do not attach an entire workspace, private logs, credentials, customer records or research notes. If quarantine prevents access to the sample, ask vendor support for its supported submission procedure. Keep the case number and written outcome.

After a vendor decision or an identified source repair, update protection definitions, rebuild the affected target under normal protection and repeat its exact tests. A new binary has a new identity; keep its result separate. Five unavailable tests do not become five passes merely because a build command completed.

## 4. Prepare public releases

Use a repeatable release build and account for every shipped dependency. Sign final Windows release executables and installers with the organisation's controlled Authenticode identity and an appropriate timestamp, then verify the signatures. Keep signing credentials outside source control. Record hashes after signing, since signing changes the file bytes.

Authenticode identifies a publisher and helps establish provenance. It does not guarantee antivirus approval or immediate SmartScreen reputation. Microsoft explains the distinction in its [SmartScreen guidance for developers](https://learn.microsoft.com/en-us/windows/apps/package-and-deploy/smartscreen-reputation).

Test the signed, packaged result on the intended supported systems with normal protection enabled. Publish only the artifacts covered by that qualification. Keep developer test binaries available for development checks, without presenting them as end-user applications.

Return to [Windows build and run instructions](windows-development.md).
