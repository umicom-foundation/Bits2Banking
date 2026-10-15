# Chapter 127 — Why a secure connection needs a trusted certificate

*System Administration From Zero · Stage 10 · Umicom Foundation*

When you visit a secure website, your browser needs a way to check that it is talking to the intended server, not merely an impostor. A **TLS certificate** helps establish the server's identity through a trusted cryptographic chain.

A certificate is not a password. It contains information such as the subject, permitted uses, validity period and public key. The corresponding private key must be protected by its owner.

## What can go wrong?

A certificate might expire, be issued for the wrong hostname or chain to an issuer the client does not trust. A computer with a wildly incorrect clock may also report a validity problem. Sometimes the server is configured to present an incomplete certificate chain.

The safe response is to investigate. **Do not click past unexpected security warnings or turn off certificate verification** simply to make an application connect.

## Find a local certificate without changing anything

Open PowerShell and inspect a small sample of certificates in your own user's personal certificate store:

```powershell
Get-ChildItem Cert:\CurrentUser\My |
    Select-Object -First 5 Subject, NotBefore, NotAfter, Thumbprint
```

The store may be empty. That is normal on some computers. `NotBefore` and `NotAfter` mark the certificate's validity interval. A **thumbprint** is a fingerprint of the certificate; it can help identify the exact certificate being discussed.

For certificates used by websites and enterprise services, administrators also check hostname matching, trust-chain status, revocation policy and whether the private key is stored securely. An expiry date alone does not establish trust.

## Linux inspection

If your Linux machine has OpenSSL installed, you can inspect a certificate file that you are authorised to read:

```bash
openssl x509 -in practice-certificate.pem -noout -subject -dates
```

Replace the filename with a genuine **non-sensitive public certificate** in your practice area. The command will report an error if the file is missing or not a valid certificate. It should never require you to copy somebody's private key.

## A realistic Umicom incident

Suppose the Umicom Notes client can no longer connect to its authorised service after midnight. Logs report a TLS verification failure. The administrator compares the current time, hostname, certificate validity and trusted issuer chain before considering a controlled certificate renewal.

**Exercise:** Name three reasons a TLS connection can fail even if the server process is running.

**Suggested answer:** expired or not-yet-valid certificate; hostname mismatch; untrusted or incomplete certification chain. Network failures can also prevent the connection before certificate verification begins.
