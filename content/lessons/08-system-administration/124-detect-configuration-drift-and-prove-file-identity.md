# Chapter 124 — How can you tell whether a configuration file changed?

*System Administration From Zero · Stage 10 · Umicom Foundation*

Imagine two Umicom Notes computers that are supposed to behave the same way. One works; the other fails to start. They run the same application version, but someone changed a configuration file on the second machine.

A **configuration** is a collection of settings used by software. **Configuration drift** means that the effective settings have moved away from an agreed, known baseline. Some changes are intentional; others are accidental. The administrator's task is to find out which.

## Make a small controlled example

We will work only with a fictional text file under your own profile. Open PowerShell and type:

```powershell
New-Item -ItemType Directory -Force -Path "$HOME\UmicomLearning\Config" | Out-Null
Set-Location "$HOME\UmicomLearning\Config"
Set-Content ".\notes-settings.txt" "mode=training"
Get-FileHash ".\notes-settings.txt" -Algorithm SHA256
```

The final command calculates a **SHA-256 checksum**. It is a long hexadecimal value derived from the file's contents. Copy the hash into your practice notes.

Now make an intentional change:

```powershell
Set-Content ".\notes-settings.txt" "mode=review"
Get-FileHash ".\notes-settings.txt" -Algorithm SHA256
```

The checksum should be different because the file's bytes changed. A checksum is useful evidence of file identity, but it does not tell you **who** made the change or whether the change was authorised.

## Comparing meaning, not just bytes

Two configuration files can have different checksums because of line endings, whitespace or comments even when a program interprets their settings in the same way. Sometimes a one-character difference changes the application's behaviour; sometimes it does not. An administrator should compare the actual settings and the approved release, not treat every checksum change as a security incident.

Version control helps here. Git can show *which lines* changed and when they were committed. We do not need to introduce new scripts to teach that. A later stage can use existing Umicom Framework configuration and repository-review facilities.

## On Linux

For a file you own, a similar read-only check is:

```bash
sha256sum "$HOME/example-file.txt"
```

Replace the example with the path of a file you actually created. On systems without `sha256sum`, use the platform's approved checksum tool. Do not edit production configuration just to complete a lesson.

## A real administrative decision

A service stops working after an update. The new configuration hash differs from the stored release manifest. What should you do first? Record the observed file, compare it with the approved version and investigate the cause. Do **not** overwrite it immediately, because that can destroy evidence or remove an intentional local setting.

**Exercise:** Why is a matching SHA-256 hash helpful, and why is it not enough to claim a system is healthy?

**Answer:** Matching hashes strongly indicate matching file bytes, but health also depends on running services, credentials, network access, data and correct business results.
