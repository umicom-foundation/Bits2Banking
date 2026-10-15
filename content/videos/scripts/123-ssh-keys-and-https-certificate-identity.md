# Episode 123 — SSH Keys and HTTPS Certificate Identity

**Bits2Banking · Umicom Foundation · Target: 10–12 minutes**  
**Related chapters:** 75, 76 and 80.

## Why this episode exists

A beginner may hear “key”, “certificate” and “fingerprint” and assume they describe the same object. This video distinguishes an SSH server host key, a person's private/public authentication key pair and an HTTPS server certificate.

## Demonstration plan

**Opening:** Show [key-separation diagram](../../assets/diagrams/sysadmin-ssh-keys-update43.svg). Describe private-key material as something that must remain private; the public portion may be registered only with the authorised service owner. Explain that keys alone do not grant access.

**PowerShell:** In an expressly chosen training folder, first use `Test-Path` to ensure `practice_ed25519` is absent. Only then run the optional `ssh-keygen -t ed25519 -f $Key -C "umicom-training-only"`. Show two filenames and `ssh-keygen -lf "$Key.pub"`; never print the private-key contents. The instructor may skip generation on shared or child-access machines.

**HTTPS:** Show [TLS identity diagram](../../assets/diagrams/sysadmin-tls-identity-update43.svg). In a permitted environment, `curl.exe --head https://example.org/` demonstrates a request with normal TLS verification enabled. Emphasise that `--insecure` is never a recommended beginner fix.

## Guided discussion

Present two fictional warnings: “remote SSH host identification has changed” and “HTTPS certificate hostname does not match”. The safe response to both is stop and verify the expected identity through an authorised route, not suppress the warning. Explain that a valid HTTPS connection still cannot prove the correctness of a financial transaction.

## Closing questions

Which key must never be uploaded? Who approves the public key? What does a certificate's SAN describe? Why does the ability to encrypt a conversation not necessarily prove that the destination is trustworthy?

**Viewer exercise:** Draw three separate identity checks and give one failure condition for each. Do not include real keys or credentials.
