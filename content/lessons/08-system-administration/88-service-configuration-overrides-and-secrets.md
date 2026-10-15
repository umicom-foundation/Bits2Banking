# Chapter 88 — Service configuration, overrides and secrets

**Bits to Banking · System Administration From Zero · Stage 7**  
**Prerequisite:** Chapters 85–87. **Safety:** The only new file in this chapter is a fictional text file in your own training directory.

## Why does the same program behave differently on two computers?

The compiled **executable** contains program code. **Configuration** selects values such as a folder path, a log level or a listening address. **Runtime state** describes what the program is currently doing. **Secrets** are sensitive values—passwords, private keys and access tokens—that require separate protection. A settings file is not automatically a suitable place to store secrets.

Applications can combine defaults, installation settings, user or workspace configuration, environment variables and command-line options. The **precedence rule** specifies which source wins when two sources provide different values. A good program makes effective values and their origins inspectable, while preventing an ordinary user override from quietly defeating centrally enforced security policy.

![Approved configuration compared with observed state](../../assets/diagrams/sysadmin-configuration-baseline-update44.svg)

## Worked example: the Notes training listener

A classroom service is supposed to bind to `127.0.0.1`, the IPv4 **loopback** address. An administrator notices a proposed setting of `0.0.0.0`, which in the context of a listening socket requests all local IPv4 interfaces. That is a meaningful exposure change. It requires review; the student does not start the service with the unapproved value and does not edit the firewall.

## Windows PowerShell 7 — create a safe practice file

These commands create an ordinary **fictional** text file under your own home directory. They do not change Windows service configuration.

```powershell
$Practice = Join-Path $HOME 'UmicomLearning\SecurityOps'
New-Item -ItemType Directory -Path $Practice -Force | Out-Null
Set-Content -LiteralPath (Join-Path $Practice 'notes-training.conf') -Value 'listen_address=127.0.0.1','log_level=info'
Get-Content -LiteralPath (Join-Path $Practice 'notes-training.conf')
```

Expected content:

```text
listen_address=127.0.0.1
log_level=info
```

`New-Item` creates the folder; `Set-Content` creates or replaces the **named practice file**; `Get-Content` displays it. The training directory may already exist, so confirm its contents before re-running a command that replaces a file.

## Linux — create the same practice content

```bash
mkdir -p "$HOME/UmicomLearning/SecurityOps"
printf 'listen_address=127.0.0.1\nlog_level=info\n' > "$HOME/UmicomLearning/SecurityOps/notes-training.conf"
cat "$HOME/UmicomLearning/SecurityOps/notes-training.conf"
```

The redirection `>` overwrites the named practice file. Never replace real `/etc` service configurations while following a classroom example. The Linux shell is used interactively, not to deliver an application script.

## What a production change would require

Before changing a real Umicom service, identify its **source revision**, approved configuration schema, actual precedence order, service owner, deployment environment, control approvals, compatible rollback plan and user-facing acceptance tests. A hash of an intended file does not prove that a running process actually loaded that file.

Do not copy `secrets.env`, private keys or actual production `.env` files into this folder, a lesson or a repository. Real software should use approved Framework secrets and configuration services.

## Your exercise

Add a harmless `notes_directory=practice-data` line to the training file, then read it back. Write a review note explaining what this value would mean if an application were designed to support it. Is the directory created? **No**: the line is text only. Does the example start a network server? **No**.

## Troubleshooting and review

If PowerShell reports that the path does not exist, check `$Practice` using `Test-Path` and inspect your home directory with `Get-ChildItem`. If Linux reports Permission denied for your own practice folder, do not reach for `sudo` automatically; inspect the location and its owner first.

**Question:** Is `0.0.0.0` equivalent to `127.0.0.1` as a listening address? **Answer:** No. Loopback is limited to the local machine; all-interface binding can expose a service to additional network paths.

**Question:** Why should production secrets not be pasted into shell commands? **Answer:** Terminal history, process listings, logs and screenshots may reveal them.

**Umicom connection:** Reuse Framework configuration and runtime manifest contracts; applications remain thin consumers. This lesson creates no new production configuration tool.

**Next:** Chapter 89 — baselines, SHA-256 and configuration drift.
