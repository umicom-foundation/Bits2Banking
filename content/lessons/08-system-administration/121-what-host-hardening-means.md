# Chapter 121 — Make a computer safer by understanding what it needs

*System Administration From Zero · Stage 10 · Umicom Foundation*

Imagine you have just been given a computer that will run a fictional Umicom Notes service. Its purpose is simple: accept notes from authorised users and save them safely. Before putting it into regular use, you would like to reduce the chance that an avoidable mistake or attack interrupts it.

This is called **host hardening**. A *host* is the computer running a service. *Hardening* means reducing unnecessary ways that the computer might be misused or fail. It is not the same as installing one antivirus program and declaring the job complete.

## Start by asking what the computer should do

A Notes computer may need a supported operating system, the Umicom application, the local storage it uses and access to approved users. It might **not** need a remote desktop service, unused web servers or accounts belonging to former colleagues.

An administrator should not disable things at random. They first identify what is present, what is required and who owns each service. Switching off an unfamiliar process can break the application just as easily as leaving an unnecessary one enabled can create risk.

For now, we will **observe, not change** the computer. You need no administrator rights.

## Look at the Windows computer in front of you

Open PowerShell 7. If you are unsure which version is open, type:

```powershell
$PSVersionTable.PSVersion
```

You should see a version number. If it begins with 7, you are using PowerShell 7. Next, enter:

```powershell
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion, OsArchitecture
```

This asks Windows to report the edition, version and architecture. Those details help decide whether a security update or application build is appropriate. A missing field is not proof of a fault; Windows editions and reporting methods differ.

Now inspect some running services without changing them:

```powershell
Get-Service | Select-Object -First 10 Name, Status, StartType
```

A service can be **Running** or **Stopped**; its start type describes how it is configured to begin. Do not treat *Stopped* as automatically bad—many legitimate services start only when needed.

## The same first look on Linux

Open a terminal on a Linux machine you own or are permitted to inspect:

```bash
uname -a
systemctl list-units --type=service --state=running --no-pager
```

`uname` reports system and kernel information. `systemctl` lists currently running systemd services on systems that use systemd. A different Linux environment may use another service manager.

## Your small hardening review

Choose one computer and write three lines: **What is this computer for? What software is essential? What looks unfamiliar and needs checking?** Record your observations, not guessed problems. The next step would be to ask the responsible person before changing configuration.

**Remember:** good hardening is careful reduction of unnecessary exposure while preserving the system's intended job.
