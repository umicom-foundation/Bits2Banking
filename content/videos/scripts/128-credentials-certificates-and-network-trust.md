# Episode 128 — Credentials, certificates and network trust

**Bits2Banking · Umicom Foundation · 7–9 minutes**  
**Companion:** System Administration Chapters 91–93; identity, security review and certificate diagrams.

## Goal

Define a credential, rotation, public/private keys, certificate expiry and the security boundary between a connected client and a trusted service.

### 00:00–02:00 — A credential is not an ordinary setting

**Visual:** A diagram shows a fictional NotesService identity requesting a secret reference from a protected provider. No secret value appears.

**Narration:** “A credential may be a password, private key or client certificate. It can prove identity. The secret value must not be copied into the source code, a Git commit, a PowerShell command or a support screenshot. Rotation requires a plan for every dependent process and a way to verify that the old credential is no longer needed.”

**Instruction:** Invite learners to write a rotation checklist containing owner, dependencies, secure replacement, test and revocation. This is a paper exercise; we never create an actual password.

### 02:00–04:10 — Certificates are about the right peer

**Visual:** Client → server certificate → issuing certificate authority → trusted root. Labels show hostname and validity dates.

**Narration:** “TLS encrypts traffic, but an encrypted connection to the wrong server is still the wrong connection. The client checks the expected host identity, the chain of trust and the time validity. A changed or untrusted certificate warning deserves investigation, not a click-through.”

**Live observation:** Show `Get-Date` and a limited `Get-ChildItem Cert:\CurrentUser\My` metadata query in Windows or `date -Is` and `openssl version` on Linux. Stress that local certificate metadata is not proof of a remote endpoint's certificate and private keys must not be exported.

### 04:10–06:10 — Firewalls and listeners

**Visual:** A listener, firewall and remote client as separate blocks. One route is drawn as unverified.

**Narration:** “A service listening locally is not the same as a firewall allowing the expected traffic. And an allowed connection is not permission to read a confidential record. Different tools answer different questions.”

Demonstrate a *read-only* local `ss -lnt` on an authorised Linux system or `Get-NetFirewallProfile` on Windows if the command is available. Avoid showing internal IPs or sensitive account details.

### 06:10–08:00 — What would make you stop?

Ask: “A service returns a certificate identity warning. A patch is planned. Someone suggests disabling verification to get past the error. What should you do?”

**Suggested answer:** Stop the connection, record the warning safely, verify the intended host through a separate trusted channel, and ask the responsible owner. Do not weaken TLS or install an unknown root certificate.

**Accessibility:** Display commands separately from prompts; explain every new term aloud; use captions for all output.
