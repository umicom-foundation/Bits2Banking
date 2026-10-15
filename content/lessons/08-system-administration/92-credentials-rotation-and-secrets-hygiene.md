# Chapter 92 — Credential rotation and secrets hygiene

**Bits to Banking · System Administration From Zero · Stage 7**  
**Prerequisite:** Chapters 76–77 and 85–91. **Safety:** Never enter a real password, token or private key in this lesson.

## What is a credential?

A **credential** is something an identity uses to authenticate, such as a password, private key or client certificate. A **secret** is protected information that must not be exposed to unapproved people or processes. **Credential rotation** replaces an existing credential with another and, after verification, retires the old one. Rotation may be scheduled, required by policy or triggered by suspected compromise.

Changing a secret is not as simple as editing a value in a text file. A service may have several consumers: a database adapter, a monitoring collector, a scheduled task and a backup process. If one still uses the old credential, a partially rotated system can fail after the change. An administrator must know the dependency map, responsible owner, approved change window, secure distribution mechanism, test procedures and rollback or recovery conditions.

![Credentials belong to identities and approved service scopes](../../assets/diagrams/sysadmin-identity-lifecycle-update44.svg)

## Why shell commands can be dangerous for secrets

Command history, process information, terminal recordings, incident screenshots and Git history can retain text that was typed. Never put production passwords, tokens or private key material in a `README`, PowerShell command, environment-variable dump or support message. Approved credentials should be accessed through the operating system's supported protected store or Umicom Framework secret-provider contract, with appropriate audit and least privilege.

This chapter teaches the **plan** for rotation, not a live credential-changing command. You can learn the architecture and review steps without storing any secret value.

## Windows: inspect possible dependent services, read only

```powershell
Get-Service | Select-Object -First 8 Name, Status, StartType
Get-ScheduledTask | Select-Object -First 8 TaskName, TaskPath
```

These lists can help a reviewer ask which scheduled jobs may depend on the service, but they do not reveal all cloud identities or hidden credential sources. Don't publish actual task names from a confidential environment.

## Linux: inspect unit and timer names, read only

```bash
systemctl list-unit-files --type=service --no-pager | head -n 10
systemctl list-timers --all --no-pager | head -n 10
```

These commands make no identity changes. A server that does not run systemd may require another inspection mechanism. No password is displayed or used in the exercise.

## Worked example: a fictional Umicom Notes credential

A Notes service accesses a training database. The owner proposes rotation. The design includes a new credential issued through an authorised secret store, a short overlap where consumers switch, independent verification of Notes save/load and backup jobs, and a defined revocation of the old credential. The reviewer records a change ticket and approval. If any consumer is forgotten, the change remains incomplete.

The statement “rotation plan reviewed” is **not evidence that rotation actually occurred**. A production system requires trustworthy provider and audit evidence. The native C23 laboratory developed in Update 44 deliberately models claimed review flags so learners understand this distinction.

## Practice: produce a rotation runbook without secrets

Write six headings: *scope*, *dependencies*, *approval*, *secure handoff*, *verification*, *revocation and recovery*. Under each, describe who is responsible and what evidence will be produced. Use only fictional identities such as `NotesService` and `CheckerB`. Do not invent a password or API token.

**Question:** Why should the old credential eventually be revoked? **Answer:** So a lost or compromised previous credential cannot continue to authenticate indefinitely.

**Question:** Why not print all environment variables when debugging? **Answer:** The output may contain credentials and other private configuration.

**Troubleshooting:** If a service stops after rotation in a real organisation, stop further changes, preserve error evidence and escalate to the approved service owner. Do not paste the new or old secret into a chat for diagnosis.

**Umicom connection:** Security, configuration and secrets are reusable Framework concerns. Bits2Banking may teach a safe scenario but must not create new script-based secret stores or application-local authentication bypasses.

**Next:** Chapter 93 — certificates, expiry and trust.
